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
			if (stl_ListIterator->nErrorTime >= stl_ListIterator->nReNumber)
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
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("自动重启,重启进程：%s 失败，错误码：%lX..."), stl_ListIterator->tszAPPName, SystemApi_GetLastError());
					}
					stl_ListIterator->nErrorTime++;
				}
			}
			else
			{
				//进程不存在才启动
				SYSTEMAPI_PROCESS_INFOMATION st_ProcessInfo;
				memset(&st_ProcessInfo, '\0', sizeof(SYSTEMAPI_PROCESS_INFOMATION));
				if (SystemApi_Process_GetProcessInfo(&st_ProcessInfo, stl_ListIterator->tszAPPName))
				{
					if (ENUM_SYSTEMAPI_PROCESS_STATUS_ZOMBIE == st_ProcessInfo.en_ProcessState)
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
					XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, "崩溃重启,检查到进程不存在,启动进程：%s 失败，错误码：%lX...", stl_ListIterator->tszAPPName, SystemApi_GetLastError());
				}
				stl_ListIterator->nErrorTime++;
			}
		}
		//休眠用户配置的时间
		std::this_thread::sleep_for(std::chrono::seconds(st_ServiceConfig.st_XTime.nTimeCheck));
	}
}
bool HTTPTask_TaskPost_Deamon(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	int nSDLen = 0;
	XCHAR* ptszSDBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_MAX);
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数
	XENGINE_DEAMONAPPINFO st_DeamonApp;
	
	memset(ptszSDBuffer, '\0', XENGINE_MEMORY_SIZE_MAX);
	
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));
	memset(&st_DeamonApp, '\0', sizeof(XENGINE_DEAMONAPPINFO));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	if (st_ServiceConfig.st_XVerifcation.st_VerSwitch.bDeamon)
	{
		XCHAR tszUserName[MAX_PATH];
		XCHAR tszUserPass[MAX_PATH];

		memset(tszUserName, '\0', sizeof(tszUserName));
		memset(tszUserPass, '\0', sizeof(tszUserPass));

		ModuleProtocol_Parse_Verifcation(lpszMsgBuffer, nMsgLen, tszUserName, tszUserPass);
		if (0 != _tcsxnicmp(st_ServiceConfig.st_XVerifcation.tszUserName, tszUserName, _tcsxlen(st_ServiceConfig.st_XVerifcation.tszUserName)))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求守护协议失败,用户验证失败,用户名错误,提供的用户名:%s"), lpszClientAddr, tszUserName);
			return false;
		}
		if (0 != _tcsxnicmp(st_ServiceConfig.st_XVerifcation.tszUserPass, tszUserPass, _tcsxlen(st_ServiceConfig.st_XVerifcation.tszUserPass)))
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求守护协议失败,解析协议失败,错误码:%lX"), lpszClientAddr, tszUserPass);
			return false;
		}
	}

	if (!ModuleProtocol_Parse_Deamon(lpszMsgBuffer, nMsgLen, st_DeamonApp.tszAPPName, st_DeamonApp.tszAPPPath, &st_DeamonApp.nReTime, &st_DeamonApp.nReNumber, &st_DeamonApp.bEnable))
	{
		st_HDRParam.nHttpCode = 400;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求解析守护协议失败,解析协议失败,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
		return false;
	}

	if (st_DeamonApp.bEnable)
	{
		st_DeamonAppConfig.stl_ListDeamonApp.push_back(st_DeamonApp);
	}
	else
	{
		for (auto stl_ListIterator = st_DeamonAppConfig.stl_ListDeamonApp.begin(); stl_ListIterator != st_DeamonAppConfig.stl_ListDeamonApp.end(); stl_ListIterator++)
		{
			if (0 == _tcsxnicmp(stl_ListIterator->tszAPPName, stl_ListIterator->tszAPPName, _tcsxlen(stl_ListIterator->tszAPPName)) && (0 == _tcsxnicmp(stl_ListIterator->tszAPPPath, st_DeamonApp.tszAPPPath, _tcsxlen(stl_ListIterator->tszAPPPath))))
			{
				SystemApi_Process_Stop(stl_ListIterator->tszAPPName);
				st_DeamonAppConfig.stl_ListDeamonApp.erase(stl_ListIterator);
				break;
			}
		}
	}
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam);
	XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求解析守护协议成功,协议类型:%d,进程名称:%s"), lpszClientAddr, st_DeamonApp.bEnable, st_DeamonApp.tszAPPName);

	free(ptszSDBuffer);
	ptszSDBuffer = NULL;
	return true;
}