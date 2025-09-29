#include "../XEngine_Hdr.h"

static bool bRecord = false;
static XHANDLE xhVideo = NULL;
static XHANDLE xhAudio = NULL;
static XHANDLE xhSound = NULL;
static XHANDLE xhScreen = NULL;
static XHANDLE xhPacket = NULL;
static XHANDLE xhAudioFifo = NULL;
static XNETHANDLE xhFilter = 0;

void XCALLBACK HTTPTask_TaskPost_CBVideo(AVCODEC_VIDEO_MSGBUFFER* pSt_MSGBuffer, XPVOID lParam)
{
	int nListCount = 0;
	AVCODEC_VIDEO_MSGBUFFER** ppSt_MSGBuffer;
	pSt_MSGBuffer->st_TimeStamp = {};
	VideoCodec_Stream_EnCodec(xhVideo, pSt_MSGBuffer, &ppSt_MSGBuffer, &nListCount);
	for (int i = 0; i < nListCount; i++)
	{
		AVFormat_Packet_StreamWrite(xhPacket, 0, ppSt_MSGBuffer[i]->st_MSGBuffer.unData.ptszMSGBuffer, ppSt_MSGBuffer[i]->st_MSGBuffer.nMSGLen[0], &ppSt_MSGBuffer[i]->st_TimeStamp);
		BaseLib_Memory_MSGFree(&ppSt_MSGBuffer[i]->st_MSGBuffer);
	}
	BaseLib_Memory_Free((XPPPMEM)&ppSt_MSGBuffer, nListCount);
}
void XCALLBACK HTTPTask_TaskPost_CBAudio(AVCODEC_AUDIO_MSGBUFFER* pSt_MSGBuffer, XPVOID lParam)
{
	int nListCount = 0;
	AVCODEC_AUDIO_MSGBUFFER** ppSt_MSGBuffer;
	AVFilter_Audio_Cvt(xhFilter, pSt_MSGBuffer, &ppSt_MSGBuffer, &nListCount);
	for (int i = 0; i < nListCount; i++)
	{
		AudioCodec_Help_FifoSend(xhAudioFifo, ppSt_MSGBuffer[i]);
		while (true)
		{
			AVCODEC_AUDIO_MSGBUFFER st_MSGBuffer = {};
			if (!AudioCodec_Help_FifoRecv(xhAudioFifo, &st_MSGBuffer))
			{
				break;
			}
			int nAudioCount = 0;
			AVCODEC_AUDIO_MSGBUFFER** ppSt_AudioBuffer;
			AudioCodec_Stream_EnCodec(xhAudio, &st_MSGBuffer, &ppSt_AudioBuffer, &nAudioCount);
			for (int j = 0; j < nAudioCount; j++)
			{
				AVFormat_Packet_StreamWrite(xhPacket, 1, ppSt_AudioBuffer[j]->st_MSGBuffer.unData.ptszMSGArray[0], ppSt_AudioBuffer[j]->st_MSGBuffer.nMSGLen[0], &ppSt_AudioBuffer[j]->st_TimeStamp);
				BaseLib_Memory_MSGFree(&ppSt_AudioBuffer[j]->st_MSGBuffer);
			}
			BaseLib_Memory_Free((XPPPMEM)&ppSt_AudioBuffer, nAudioCount);
		}
		BaseLib_Memory_MSGFree(&ppSt_MSGBuffer[i]->st_MSGBuffer);
	}
	BaseLib_Memory_Free((XPPPMEM)&ppSt_MSGBuffer, nListCount);
}

bool HTTPTask_TaskPost_BackService(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	int nRVLen = 0;
	int nBSType = 0;
	CXEngine_MemoryPoolEx m_MemorySend(XENGINE_MEMORY_SIZE_MAX);
	CXEngine_MemoryPoolEx m_MemoryRecv(XENGINE_MEMORY_SIZE_MAX);

	XCHAR tszSrcBuffer[XPATH_MAX] = {};
	XCHAR tszDstBuffer[XPATH_MAX] = {};
	XCHAR tszAPIBuffer[XPATH_MAX] = {};
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};    //发送给客户端的参数

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭
	if (!ModuleProtocol_Parse_BackService(lpszMsgBuffer, nMsgLen, tszSrcBuffer, tszDstBuffer, tszAPIBuffer, &nBSType))
	{
		st_HDRParam.nHttpCode = 400;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求后台协议失败,解析协议失败,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
		return false;
	}
	//执行任务
	switch (nType)
	{
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_DOWNFILE:
	{
		XHANDLE xhTask = APIClient_File_Create(tszSrcBuffer, tszDstBuffer);
		if (NULL == xhTask)
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,下载任务处理失败,请求下载地址:%s,下载路径:%s,错误码:%lX"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, APIClient_GetLastError());
			return false;
		}
		if (!APIClient_File_Start(xhTask))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,下载任务处理失败,请求下载地址:%s,下载路径:%s,错误码:%lX"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, APIClient_GetLastError());
			return false;
		}
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);

		XLONG dwRet = 0;
		while (true)
		{
			XCLIENT_APIFILE st_TaskInfo;
			memset(&st_TaskInfo, '\0', sizeof(XCLIENT_APIFILE));

			if (!APIClient_File_Query(xhTask, &st_TaskInfo))
			{
				dwRet = APIClient_GetLastError();
				break;
			}
			if ((ENUM_XCLIENT_APIHELP_FILE_STATUS_INIT != st_TaskInfo.en_DownStatus) && (ENUM_XCLIENT_APIHELP_FILE_STATUS_DOWNLOADDING != st_TaskInfo.en_DownStatus))
			{
				dwRet = APIClient_GetLastError();
				break;
			}
		}
		APIClient_File_Delete(xhTask);
		//完成通知
		if (_tcsxlen(tszAPIBuffer) > 0)
		{
			ModuleProtocol_Packet_BackNotify(m_MemorySend.get(), &nSDLen, (int)dwRet, XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_DOWNFILE, tszSrcBuffer, tszDstBuffer, tszAPIBuffer);
			APIClient_Http_Request(_X("POST"), tszAPIBuffer, m_MemorySend.get());
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:下载任务处理成功,下载地址:%s,保存地址:%s"),lpszClientAddr, tszSrcBuffer, tszDstBuffer);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_DELETEFILE:
		if (-1 == _xtremove(tszSrcBuffer))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:删除文件:%s,任务处理失败,错误码:%d"), lpszClientAddr, tszSrcBuffer, errno);
			return false;
		}
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:删除文件处理成功,删除的文件:%s"), lpszClientAddr, tszSrcBuffer);
		break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_DELETEDIR:
		if (!SystemApi_File_DeleteMutilFolder(tszSrcBuffer))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:删除文件夹:%s 任务处理失败,错误码:%lX"), lpszClientAddr, tszSrcBuffer, SystemApi_GetLastError());
			return false;
		}
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:删除文件夹处理成功,删除的文件夹:%s"), lpszClientAddr, tszSrcBuffer);
		break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_UPFILE:
	{
		XHANDLE xhTask = APIClient_File_Create(tszSrcBuffer, tszDstBuffer, false);
		if (NULL == xhTask)
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:FTP上传任务处理失败,上传的文件:%s,上传的地址:%s,错误码:%lX"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, APIClient_GetLastError());
			return false;
		}
		if (!APIClient_File_Start(xhTask))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,上传任务处理失败,上传的文件:%s,上传的地址:%s,错误码:%lX"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, APIClient_GetLastError());
			return false;
		}
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);

		XLONG dwRet = 0;
		while (true)
		{
			XCLIENT_APIFILE st_TaskInfo;
			memset(&st_TaskInfo, '\0', sizeof(XCLIENT_APIFILE));

			if (!APIClient_File_Query(xhTask, &st_TaskInfo))
			{
				dwRet = APIClient_GetLastError();
				break;
			}
			if (ENUM_XCLIENT_APIHELP_FILE_STATUS_DOWNLOADDING != st_TaskInfo.en_DownStatus && (ENUM_XCLIENT_APIHELP_FILE_STATUS_INIT != st_TaskInfo.en_DownStatus))
			{
				dwRet = APIClient_GetLastError();
				break;
			}
		}
		APIClient_File_Delete(xhTask);
		//完成通知
		if (_tcsxlen(tszAPIBuffer) > 0)
		{
			ModuleProtocol_Packet_BackNotify(m_MemorySend.get(), &nSDLen, (int)dwRet, XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_UPFILE, tszSrcBuffer, tszDstBuffer, tszAPIBuffer);
			APIClient_Http_Request(_X("POST"), tszAPIBuffer, m_MemorySend.get());
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:上传文件处理成功,上传的文件:%s,上传的地址:%s"), lpszClientAddr, tszSrcBuffer, tszDstBuffer);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_GETLIST:
	{
		int nListCount = 0;
		XCHAR** ppszFileList;

		if (!SystemApi_File_EnumFile(tszSrcBuffer, &ppszFileList, &nListCount))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求文件列表:%s 失败,错误码:%lX"), lpszClientAddr, tszSrcBuffer, SystemApi_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_ListFile(m_MemoryRecv.get(), &nRVLen, &ppszFileList, nListCount);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam, m_MemoryRecv.get(), nRVLen);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		BaseLib_Memory_Free((XPPPMEM)&ppszFileList, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:获取文件列表成功,回复个数:%d"), lpszClientAddr, nListCount);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_EXEC:
	{
		XLONG dwProcessID = 0;
		if (!SystemApi_Process_CreateProcess(&dwProcessID, tszSrcBuffer, NULL, nBSType))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求创建进程:%s 失败,错误码:%lX"), lpszClientAddr, tszSrcBuffer, SystemApi_GetLastError());
			return false;
		}
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:请求创建进程成功,进程:%s,PID:%d"), lpszClientAddr, tszSrcBuffer, dwProcessID);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_STOPPROCESS:
	{
		if (!SystemApi_Process_Stop(NULL, nBSType))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求停止进程ID:%d 失败,错误码:%lX"), lpszClientAddr, nBSType, SystemApi_GetLastError());
			return false;
		}
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:请求停止进程成功,进程ID:%ld"), nBSType);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_SHUTDOWN:
	{
		if (!SystemApi_System_Shutdown(nBSType))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求关机失败,错误码:%lX"), lpszClientAddr, SystemApi_GetLastError());
			return false;
		}
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:请求关闭系统成功,关闭方式:%ld"), lpszClientAddr, nBSType);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_ECMD:
		if (-1 == system(tszSrcBuffer))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求执行命令:%s 失败,错误码:%lX"), lpszClientAddr, tszSrcBuffer, SystemApi_GetLastError());
			return false;
		}
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:请求执行命令成功,执行的命令:%s"), lpszClientAddr, tszSrcBuffer);
		break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_REPORT:
	{
		if (0 == nBSType)
		{
			InfoReport_APIMachine_Hardware(m_MemoryRecv.get(), &nRVLen);
		}
		else if (1 == nBSType)
		{
			InfoReport_APIMachine_Software(m_MemoryRecv.get(), &nRVLen);
		}
		else if (2 == nBSType)
		{
			int nACount = 0;
			int nVCount = 0;
			AVHELP_DEVICEINFO** ppSt_AudioList;
			AVHELP_DEVICEINFO** ppSt_VideoList;

			AVHelp_Device_EnumDevice(&ppSt_AudioList, &ppSt_VideoList, &nACount, &nVCount);
			ModuleProtocol_Packet_EnumDevice(m_MemoryRecv.get(), &nRVLen, &ppSt_AudioList, &ppSt_VideoList, nACount, nVCount);
			BaseLib_Memory_Free((void***)&ppSt_AudioList, nACount);
			BaseLib_Memory_Free((void***)&ppSt_VideoList, nVCount);
		}
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam, m_MemoryRecv.get(), nRVLen);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:请求上报信息成功,上报类型:%d"), lpszClientAddr, nBSType);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_RECORDSTART:
	{
		if (bRecord)
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,因为已经在录制中了"), lpszClientAddr);
			return false;
		}
		//屏幕采集
		AVCOLLECT_SCREENINFO st_AVScreen;
		memset(&st_AVScreen, '\0', sizeof(AVCOLLECT_SCREENINFO));

		st_AVScreen.nFrameRate = 24;
		st_AVScreen.nPosX = 0;
		st_AVScreen.nPosY = 0;
		_xstprintf(st_AVScreen.tszVideoSize, _X("%s"), _X("1920x1080"));
#ifdef _MSC_BUILD
		xhScreen = AVCollect_Video_Init("gdigrab", tszDstBuffer, &st_AVScreen, HTTPTask_TaskPost_CBVideo);
#elif __linux__
		xhScreen = AVCollect_Video_Init("x11grab", tszDstBuffer, &st_AVScreen, HTTPTask_TaskPost_CBVideo);
#else
		xhScreen = AVCollect_Video_Init("avfoundation", tszDstBuffer, &st_AVScreen, HTTPTask_TaskPost_CBVideo);
#endif
		if (NULL == xhScreen)
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,屏幕采集器请求失败,错误码:%lX"), lpszClientAddr, AVCollect_GetLastError());
			return false;
		}
		xhPacket = AVFormat_Packet_Init();
		if (!AVFormat_Packet_Output(xhPacket, tszAPIBuffer, _X("flv")))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,推流服务端:%s 连接失败,错误码:%lX"), lpszClientAddr, tszAPIBuffer, AVFormat_GetLastError());
			return false;
		}
		XHANDLE xhVideoCodec = NULL;
		//初始化屏幕编码器
		XENGINE_PROTOCOL_AVINFO st_AVInfo = {};
		AVCollect_Video_GetInfo(xhScreen, &st_AVInfo);
		st_AVInfo.st_VideoInfo.enAVCodec = ENUM_XENGINE_AVCODEC_VIDEO_TYPE_H264;
		xhVideo = VideoCodec_Stream_EnInit(&st_AVInfo.st_VideoInfo);
		if (NULL == xhVideo)
		{
			st_HDRParam.nHttpCode = 500;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,打开编码器视频编码器失败,错误码:%lX"), lpszClientAddr, VideoCodec_GetLastError());
			return false;
		}
		VideoCodec_Stream_GetAVCodec(xhVideo, &xhVideoCodec);
		AVFormat_Packet_StreamCreate(xhPacket, xhVideoCodec);
		BaseLib_Memory_FreeCStyle((XPPMEM)&xhVideoCodec);
		//启用音频
		if (1 == nBSType)
		{
#ifdef _MSC_BUILD
			xhSound = AVCollect_Audio_Init("dshow", tszSrcBuffer, HTTPTask_TaskPost_CBAudio);
#elif __linux__
			xhSound = AVCollect_Audio_Init("alsa", tszSrcBuffer, HTTPTask_TaskPost_CBAudio);
#else
			xhSound = AVCollect_Audio_Init("avfoundation", tszSrcBuffer, HTTPTask_TaskPost_CBAudio);
#endif
			if (NULL == xhSound)
			{
				st_HDRParam.nHttpCode = 400;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频采集器请求失败,错误码:%lX"), lpszClientAddr, AVCollect_GetLastError());
				return false;
			}
			AVCollect_Audio_GetInfo(xhSound, &st_AVInfo);
			AVFILTER_AUDIO_INFO st_AudioFilter = {};
			st_AudioFilter.nIndex = 0;
			st_AudioFilter.st_AudioInfo = st_AVInfo.st_AudioInfo;
			AVCollect_Audio_GetTimeBase(xhSound, &st_AudioFilter.st_AudioTime);
			if (!AVFilter_Audio_Init(&xhFilter, _X("aresample=44100,aformat=sample_fmts=fltp:channel_layouts=stereo"), &st_AudioFilter))
			{
				st_HDRParam.nHttpCode = 400;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频滤镜失败,错误码:%lX"), lpszClientAddr, AVFilter_GetLastError());
				return false;
			}
			st_AVInfo.st_AudioInfo.nSampleRate = 44100;
			st_AVInfo.st_AudioInfo.nSampleFmt = ENUM_AVCODEC_AUDIO_SAMPLEFMT_FLTP;
			st_AVInfo.st_AudioInfo.enAVCodec = ENUM_XENGINE_AVCODEC_AUDIO_TYPE_AAC;
			xhAudio = AudioCodec_Stream_EnInit(&st_AVInfo.st_AudioInfo);
			if (NULL == xhAudio)
			{
				st_HDRParam.nHttpCode = 400;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频采集器请求失败,错误码:%lX"), lpszClientAddr, AudioCodec_GetLastError());
				return false;
			}
			xhAudioFifo = AudioCodec_Help_FifoInit(ENUM_AVCODEC_AUDIO_SAMPLEFMT_FLTP, 2);
			if (NULL == xhAudioFifo)
			{
				st_HDRParam.nHttpCode = 400;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频采集器请求失败,错误码:%lX"), lpszClientAddr, AudioCodec_GetLastError());
				return false;
			}
			XHANDLE xhAudioCodec = NULL;
			AudioCodec_Stream_GetAVCodec(xhAudio, &xhAudioCodec);
			AVFormat_Packet_StreamCreate(xhPacket, xhAudioCodec);
			//使用了滤镜,需要单独设置
			AVCODEC_TIMEBASE st_TimeBase = {};
			st_TimeBase.nDen = 44100;
			st_TimeBase.nNum = 1;
			AVFormat_Packet_TimeBase(xhPacket, 1, &st_TimeBase);
			BaseLib_Memory_FreeCStyle((XPPMEM)&xhAudioCodec);
		}
		bRecord = true;
		AVFormat_Packet_Start(xhPacket);
		AVCollect_Audio_Start(xhSound);
		AVCollect_Video_Start(xhScreen);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,开始屏幕录制,音频:%s,视频:%s 推流:%s 请求成功"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, tszAPIBuffer);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_RECORDSTOP:
	{
		bRecord = false;

		AVCollect_Video_Destory(xhScreen);
		AVCollect_Audio_Destory(xhSound);

		VideoCodec_Stream_Destroy(xhVideo);
		AudioCodec_Stream_Destroy(xhAudio);
		AudioCodec_Help_FifoClose(xhAudioFifo);

		AVFilter_Audio_Destroy(xhFilter);

		AVFormat_Packet_Stop(xhPacket);
		xhScreen = NULL;
		xhSound = NULL;
		xhVideo = NULL;
		xhAudio = NULL;
		xhPacket = NULL;
		
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,停止屏幕录制推流请求成功"), lpszClientAddr);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_NOTHINGTODO:
		break;
	default:
		st_HDRParam.nHttpCode = 400;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求的操作码不支持,操作码:%d"), lpszClientAddr, nType);
		return false;
	}
	return true;
}