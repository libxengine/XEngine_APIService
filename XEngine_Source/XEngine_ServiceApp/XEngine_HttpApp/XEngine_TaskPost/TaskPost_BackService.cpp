#include "../XEngine_Hdr.h"

static bool bRecord = false;
static XHANDLE xhSound = NULL;
static XHANDLE xhScreen = NULL;
static XHANDLE xhStream = NULL;
static XHANDLE xhAudioFifo = NULL;

void XCALLBACK HTTPTask_TaskPost_CBVideo(uint8_t* ptszAVBuffer, int nAVLen, AVCOLLECT_TIMEINFO* pSt_TimeInfo, XPVOID lParam)
{
	if (!XClient_StreamPush_LiveVideo(xhStream, ptszAVBuffer, nAVLen))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("屏幕采集器,推流编码失败,需要关闭推流服务,错误码:%lX"), StreamClient_GetLastError());
	}
}
void XCALLBACK HTTPTask_TaskPost_CBAudio(uint8_t* ptszAVBuffer, int nAVLen, AVCOLLECT_TIMEINFO* pSt_TimeInfo, XPVOID lParam)
{
	if (AudioCodec_Help_FifoSend(xhAudioFifo, (LPCXSTR)ptszAVBuffer, nAVLen))
	{
		while (true)
		{
			XBYTE tszAVBuffer[8192] = {};
			if (!AudioCodec_Help_FifoRecv(xhAudioFifo, tszAVBuffer, &nAVLen))
			{
				break;
			}
			if (!XClient_StreamPush_LiveAudio(xhStream, tszAVBuffer, nAVLen))
			{
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("音频采集器,推流编码失败,需要关闭推流服务,错误码:%lX"), StreamClient_GetLastError());
			}
		}
	}
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
		XENGINE_PROTOCOL_AVINFO st_AVInfo;
		memset(&st_AVInfo, '\0', sizeof(XENGINE_PROTOCOL_AVINFO));
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
			xhAudioFifo = AudioCodec_Help_FifoInit(ENUM_AVCODEC_AUDIO_SAMPLEFMT_S16, 2);
			if (NULL == xhAudioFifo)
			{
				st_HDRParam.nHttpCode = 400;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频采集器请求失败,错误码:%lX"), lpszClientAddr, AudioCodec_GetLastError());
				return false;
			}
			st_AVInfo.st_AudioInfo.bEnable = true;
			AVCollect_Audio_GetInfo(xhSound, &st_AVInfo);
			//音频编码参数
			st_AVInfo.st_AudioInfo.enAVCodec = ENUM_XENGINE_AVCODEC_AUDIO_TYPE_AAC;
			st_AVInfo.st_AudioInfo.nSampleFmt = ENUM_AVCODEC_AUDIO_SAMPLEFMT_S16;
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
		AVCollect_Video_GetInfo(xhScreen, &st_AVInfo);
		st_AVInfo.st_VideoInfo.enAVCodec = ENUM_XENGINE_AVCODEC_VIDEO_TYPE_H264;
		xhStream = XClient_StreamPush_LiveInit();
		if (NULL == xhStream)
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,推流:%s 请求失败,错误码:%lX"), lpszClientAddr, tszDstBuffer, StreamClient_GetLastError());
			return false;
		}
		bRecord = true;
		XClient_StreamPush_LiveOutput(xhStream, tszAPIBuffer, _X("flv"));
		XClient_StreamPush_LiveCreate(xhStream, &st_AVInfo);

		AVCODEC_TIMEBASE st_VideoTime = {};
		AVCODEC_TIMEBASE st_AudioTime = {};
		AVCollect_Audio_GetTimeBase(xhSound, &st_AudioTime);
		AVCollect_Video_GetTimeBase(xhScreen, &st_VideoTime);
		XClient_StreamPush_LiveTime(xhStream, &st_VideoTime, &st_AudioTime);

		AVCollect_Audio_Start(xhSound);
		AVCollect_Video_Start(xhScreen);
		XClient_StreamPush_LiveWriteHdr(xhStream);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,开始屏幕录制,音频:%s,视频:%s 推流:%s 请求成功"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, tszAPIBuffer);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_RECORDSTOP:
	{
		if (bRecord)
		{
			AVCollect_Video_Destory(xhScreen);
			AVCollect_Audio_Destory(xhSound);
			XClient_StreamPush_LiveClose(xhStream);
			xhScreen = NULL;
			xhSound = NULL;
			xhStream = NULL;
			bRecord = false;
		}
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