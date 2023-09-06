#include "../XEngine_Hdr.h"

void CALLBACK HTTPTask_TaskPost_Thread()
{
	while (bIsRun)
	{
		//轮询检测进程列表
		for (auto stl_ListIterator = st_DeamonAppConfig.stl_ListDeamonApp.begin(); stl_ListIterator != st_DeamonAppConfig.stl_ListDeamonApp.end(); stl_ListIterator++)
		{
			//是否启用
			if (!stl_ListIterator->bEnable)
			{
				continue;
			}
			//重试次数判断
			if (stl_ListIterator->nErrorTime > st_ServiceConfig.st_XTime.nDeamonTime)
			{
				stl_ListIterator->bEnable = false;
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("服务名：%s，由于超过指定启动失败次数：%d，这个服务检测功能被关闭..."), stl_ListIterator->tszAPPName, st_ServiceConfig.st_XTime.nDeamonTime);
				continue;
			}

			if (stl_ListIterator->nReTime > 0)
			{
				//进程自动重启
				__int64x nNowTime = time(NULL);
				if ((nNowTime - stl_ListIterator->nStartTime) > stl_ListIterator->nReTime)
				{
					XLONG dwProcessId = 0;
					XCHAR tszCmdExe[1024];

					memset(tszCmdExe, '\0', sizeof(tszCmdExe));
					sprintf(tszCmdExe, "%s%s", stl_ListIterator->tszAPPPath, stl_ListIterator->tszAPPName);

					SystemApi_Process_Stop(stl_ListIterator->tszAPPName);
					if (SystemApi_Process_CreateProcess(&dwProcessId, tszCmdExe))
					{
						stl_ListIterator->nStartTime = time(NULL);
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("自动重启,重启进程：%s 成功，进程ID：%d..."), stl_ListIterator->tszAPPName, dwProcessId);
					}
					else
					{
						stl_ListIterator->nErrorTime++;
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("自动重启,重启进程：%s 失败，错误码：%lX..."), stl_ListIterator->tszAPPName, SystemApi_GetLastError());
					}
				}
			}
			else
			{
				//进程不存在才启动
				SYSTEMAPI_PROCESS_INFOMATION st_ProcessInfo;
				memset(&st_ProcessInfo, '\0', sizeof(SYSTEMAPI_PROCESS_INFOMATION));
				if (SystemApi_Process_GetProcessInfo(&st_ProcessInfo, stl_ListIterator->tszAPPName))
				{
					if (ENUM_SYSTEMSDK_PROCFILE_PROCFILE_PROCESS_STATE_ZOMBIE == st_ProcessInfo.en_ProcessState)
					{
#ifndef _MSC_BUILD
						//僵尸进程必须使用waitpid退出
						int nStatus = 0;
						waitpid(st_ProcessInfo.nPid, &nStatus, 0);
#endif
					}
					else
					{
						continue;
					}
				}

				XLONG dwProcessId = 0;
				XCHAR tszCmdExe[1024];

				memset(tszCmdExe, '\0', sizeof(tszCmdExe));
				sprintf(tszCmdExe, "%s%s", stl_ListIterator->tszAPPPath, stl_ListIterator->tszAPPName);

				if (SystemApi_Process_CreateProcess(&dwProcessId, tszCmdExe))
				{
					XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, "崩溃重启,检查到进程不存在,启动进程：%s 成功，进程ID：%d...", stl_ListIterator->tszAPPName, dwProcessId);
			    }
				else
				{
					stl_ListIterator->nErrorTime++;
					XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, "崩溃重启,检查到进程不存在,启动进程：%s 失败，错误码：%lX...", stl_ListIterator->tszAPPName, SystemApi_GetLastError());
				}
			}
		}
		//休眠用户配置的时间
		std::this_thread::sleep_for(std::chrono::seconds(st_ServiceConfig.st_XTime.nTimeCheck));
	}
}
bool HTTPTask_TaskPost_Deamon(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	int nRVLen = 0;
	int nBSType = 0;
	XCHAR* ptszRVBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_MAX);
	XCHAR* ptszSDBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_MAX);
	XCHAR tszSrcBuffer[MAX_PATH];
	XCHAR tszDstBuffer[MAX_PATH];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(ptszRVBuffer, '\0', XENGINE_MEMORY_SIZE_MAX);
	memset(ptszSDBuffer, '\0', XENGINE_MEMORY_SIZE_MAX);
	
	memset(tszSrcBuffer, '\0', sizeof(tszSrcBuffer));
	memset(tszDstBuffer, '\0', sizeof(tszDstBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	if (!ModuleProtocol_Parse_BackService(lpszMsgBuffer, nMsgLen, tszSrcBuffer, tszDstBuffer, &nBSType))
	{
		st_HDRParam.nHttpCode = 400;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求后台协议失败,解析协议失败,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
		return false;
	}
	//执行任务
	if (1 == nType)
	{

	}
	else
	{
		st_HDRParam.nHttpCode = 400;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,下载任务处理失败,请求下载地址:%s,下载路径:%s,错误码:%lX"), lpszClientAddr, tszSrcBuffer, tszDstBuffer, APIClient_GetLastError());
		return false;
	}
	free(ptszRVBuffer);
	free(ptszSDBuffer);
	ptszSDBuffer = NULL;
	ptszRVBuffer = NULL;
	return true;
}