#include "../XEngine_Hdr.h"

bool HTTPTask_TaskPost_BackService(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	int nBSType = 0;
	CXEngine_MemoryPoolEx m_MemorySend(XENGINE_MEMORY_SIZE_MAX);

	XCHAR tszSrcBuffer[XPATH_MAX] = {};
	XCHAR tszDstBuffer[XPATH_MAX] = {};
	XCHAR tszAPIBuffer[XPATH_MAX] = {};

	if (!ModuleProtocol_Parse_BackService(lpszMsgBuffer, nMsgLen, tszSrcBuffer, tszDstBuffer, tszAPIBuffer, &nBSType))
	{
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_JSON, _X("back service payload json failure"));
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
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_INIT, _X("init file download failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,下载任务处理失败,请求下载地址:%s,下载路径:%s,错误码:%lX"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, APIClient_GetLastError());
			return false;
		}
		if (!APIClient_File_Start(xhTask))
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_OPEN, _X("start file download failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,下载任务处理失败,请求下载地址:%s,下载路径:%s,错误码:%lX"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, APIClient_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen);
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
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("delete file failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:删除文件:%s,任务处理失败,错误码:%d"), lpszClientAddr, tszSrcBuffer, errno);
			return false;
		}
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:删除文件处理成功,删除的文件:%s"), lpszClientAddr, tszSrcBuffer);
		break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_DELETEDIR:
		if (!SystemApi_File_DeleteMutilFolder(tszSrcBuffer))
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("delete dir failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:删除文件夹:%s 任务处理失败,错误码:%lX"), lpszClientAddr, tszSrcBuffer, SystemApi_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:删除文件夹处理成功,删除的文件夹:%s"), lpszClientAddr, tszSrcBuffer);
		break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_UPFILE:
	{
		XHANDLE xhTask = APIClient_File_Create(tszSrcBuffer, tszDstBuffer, false);
		if (NULL == xhTask)
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_INIT, _X("init upfile is failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:FTP上传任务处理失败,上传的文件:%s,上传的地址:%s,错误码:%lX"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, APIClient_GetLastError());
			return false;
		}
		if (!APIClient_File_Start(xhTask))
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_OPEN, _X("start upfile is failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,上传任务处理失败,上传的文件:%s,上传的地址:%s,错误码:%lX"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, APIClient_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen);
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
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("enum file is failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求文件列表:%s 失败,错误码:%lX"), lpszClientAddr, tszSrcBuffer, SystemApi_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen);
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
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("create process is failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求创建进程:%s 失败,错误码:%lX"), lpszClientAddr, tszSrcBuffer, SystemApi_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:请求创建进程成功,进程:%s,PID:%d"), lpszClientAddr, tszSrcBuffer, dwProcessID);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_STOPPROCESS:
	{
		if (!SystemApi_Process_Stop(NULL, nBSType))
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("stop process is failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求停止进程ID:%d 失败,错误码:%lX"), lpszClientAddr, nBSType, SystemApi_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:请求停止进程成功,进程ID:%ld"), nBSType);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_SHUTDOWN:
	{
		if (!SystemApi_System_Shutdown(nBSType))
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("shutdown is failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求关机失败,错误码:%lX"), lpszClientAddr, SystemApi_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:请求关闭系统成功,关闭方式:%ld"), lpszClientAddr, nBSType);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_ECMD:
		if (-1 == system(tszSrcBuffer))
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("system command is failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求执行命令:%s 失败,错误码:%lX"), lpszClientAddr, tszSrcBuffer, SystemApi_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:请求执行命令成功,执行的命令:%s"), lpszClientAddr, tszSrcBuffer);
		break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_REPORT:
	{
		if (0 == nBSType)
		{
			InfoReport_APIMachine_Hardware(m_MemorySend.get(), &nSDLen);
		}
		else if (1 == nBSType)
		{
			InfoReport_APIMachine_Software(m_MemorySend.get(), &nSDLen);
		}
		else if (2 == nBSType)
		{
			int nACount = 0;
			int nVCount = 0;
			AVHELP_DEVICEINFO** ppSt_AudioList;
			AVHELP_DEVICEINFO** ppSt_VideoList;

			AVHelp_Device_EnumDevice(&ppSt_AudioList, &ppSt_VideoList, &nACount, &nVCount);
			ModuleProtocol_Packet_EnumDevice(m_MemorySend.get(), &nSDLen, &ppSt_AudioList, &ppSt_VideoList, nACount, nVCount);
			BaseLib_Memory_Free((void***)&ppSt_AudioList, nACount);
			BaseLib_Memory_Free((void***)&ppSt_VideoList, nVCount);
		}
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s:请求上报信息成功,上报类型:%d"), lpszClientAddr, nBSType);
	}
	break;
	case XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_BS_NOTHINGTODO:
		break;
	default:
		ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_NOTSUPPORT, _X("operator command not support"));
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s:请求的操作码不支持,操作码:%d"), lpszClientAddr, nType);
		return false;
	}
	return true;
}