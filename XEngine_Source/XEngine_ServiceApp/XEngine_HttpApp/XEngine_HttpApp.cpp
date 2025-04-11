#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/01/20  14:43:07
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp\XEngine_HttpApp.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp
//    File Base:   XEngine_HttpApp
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     主要入口函数
//    History:
*********************************************************************/
bool bIsRun = false;
bool bIsTest = false;
XHANDLE xhLog = NULL;
//HTTP服务器
XHANDLE xhHTTPSocket = NULL;
XHANDLE xhRFCSocket = NULL;
XHANDLE xhHTTPHeart = NULL;
XHANDLE xhHTTPPacket = NULL;
XHANDLE xhHTTPPool = NULL;
//线程
unique_ptr<thread> pSTDThread_Deamon = NULL;
//配置文件
XENGINE_SERVICECONFIG st_ServiceConfig;
XENGINE_PLUGINCONFIG st_PluginLibConfig;
XENGINE_PLUGINCONFIG st_PluginLuaConfig;
XENGINE_DEAMONAPPLIST st_DeamonAppConfig;

void ServiceApp_Stop(int signo)
{
	if (bIsRun)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("服务器退出..."));
		bIsRun = false;
		//销毁HTTP资源
		NetCore_TCPXCore_DestroyEx(xhHTTPSocket);
		NetCore_UDPXCore_DestroyEx(xhRFCSocket);
		SocketOpt_HeartBeat_DestoryEx(xhHTTPHeart);
		HttpProtocol_Server_DestroyEx(xhHTTPPacket);
		ManagePool_Thread_NQDestroy(xhHTTPPool);
		//销毁数据库
		ModuleDatabase_IDCard_Destory();
		ModuleDatabase_Bank_Destory();
		ModuleDatabase_ZIPCode_Destory();
		ModuleDatabase_XLog_Destory();
		ModuleDatabase_ShortLink_Destory();
		ModuleDatabase_WordFilter_Destory();
		ModuleDatabase_Machine_Destory();
		ModuleDatabase_OilInfo_Destory();
		//销毁其他
		APIModule_IPAddr_UnInit();
		APIModule_MACInfo_UnInit();
		APIModule_PhoneNumber_UnInit();
		ModulePlugin_Loader_Destory();
		ModuleHelp_P2PClient_Destory();
		ModuleHelp_ImageGet_TextDestory();
		//销毁日志资源
		HelpComponents_XLog_Destroy(xhLog);
		//销毁线程
		if (NULL != pSTDThread_Deamon)
		{
			pSTDThread_Deamon->join();
		}
	}
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	exit(0);
}
#ifdef _MSC_BUILD
LONG WINAPI Coredump_ExceptionFilter(EXCEPTION_POINTERS* pExceptionPointers)
{
	static int i = 0;
	XCHAR tszFileStr[MAX_PATH] = {};
	XCHAR tszTimeStr[128] = {};
	BaseLib_Time_TimeToStr(tszTimeStr);
	_xstprintf(tszFileStr, _X("./XEngine_Coredump/dumpfile_%s_%d.dmp"), tszTimeStr, i++);

	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_FATAL, _X("主程序:软件崩溃,写入dump:%s"), tszFileStr);

	HANDLE hDumpFile = CreateFileA(tszFileStr, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE != hDumpFile)
	{
		MINIDUMP_EXCEPTION_INFORMATION st_DumpInfo = {};
		st_DumpInfo.ExceptionPointers = pExceptionPointers;
		st_DumpInfo.ThreadId = GetCurrentThreadId();
		st_DumpInfo.ClientPointers = TRUE;

		// 写入 dump 文件
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &st_DumpInfo, NULL, NULL);
		CloseHandle(hDumpFile);
	}
	return EXCEPTION_EXECUTE_HANDLER;
}
#endif
//LINUX守护进程
static int ServiceApp_Deamon()
{
#ifndef _MSC_BUILD
	pid_t nPID = 0;
	int nStatus = 0;
	nPID = fork();
	if (nPID > 0)
	{
		exit(0);
	}

	close(2);
	while (1)
	{
		nPID = fork();
		if (nPID < 0)
		{
			exit(1);
		}
		if (nPID == 0)
		{
			return 0;
		}
		waitpid(nPID, &nStatus, 0);
		sleep(1);
	}
#endif
	return 0;
}

int main(int argc, char** argv)
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);

	SetUnhandledExceptionFilter(Coredump_ExceptionFilter);
#ifndef _DEBUG
	if (setlocale(LC_ALL, ".UTF8") == NULL)
	{
		printf("Error setting locale.\n");
		return -1;
	}
#endif
#endif
	bIsRun = true;
	int nRet = -1;
	HELPCOMPONENTS_XLOG_CONFIGURE st_XLogConfig;
	THREADPOOL_PARAMENT** ppSt_ListHTTPParam;

	memset(&st_XLogConfig, '\0', sizeof(HELPCOMPONENTS_XLOG_CONFIGURE));
	memset(&st_ServiceConfig, '\0', sizeof(XENGINE_SERVICECONFIG));
	memset(&st_PluginLibConfig, '\0', sizeof(XENGINE_PLUGINCONFIG));
	memset(&st_PluginLuaConfig, '\0', sizeof(XENGINE_PLUGINCONFIG));

	//初始化参数
	if (!XEngine_Configure_Parament(argc, argv))
	{
		goto XENGINE_SERVICEAPP_EXIT;
	}
	//配置重载
	if (st_ServiceConfig.st_XReload.bReload)
	{
		//重载配置文件后退出
		XCHAR tszAddr[128];
		memset(tszAddr, '\0', sizeof(tszAddr));
		//http://127.0.0.1:5501/api?function=reload&opcode=0
		_xstprintf(tszAddr, _X("http://127.0.0.1:%d/api?function=reload&opcode=%d"), st_ServiceConfig.nHttpPort, st_ServiceConfig.st_XReload.byCode);
		APIClient_Http_Request(_X("GET"), tszAddr);
		return 0;
	}
	//判断是否以守护进程启动
	if (st_ServiceConfig.bDeamon)
	{
		ServiceApp_Deamon();
	}
	//初始日志
	st_XLogConfig.XLog_MaxBackupFile = st_ServiceConfig.st_XLog.nMaxCount;
	st_XLogConfig.XLog_MaxSize = st_ServiceConfig.st_XLog.nMaxSize;
	_tcsxcpy(st_XLogConfig.tszFileName, st_ServiceConfig.st_XLog.tszAPIFile);
	xhLog = HelpComponents_XLog_Init(st_ServiceConfig.st_XLog.nLogLeave, &st_XLogConfig);
	if (NULL == xhLog)
	{
		printf("启动服务中,启动日志失败,错误：%lX", XLog_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	//设置日志打印级别
	HelpComponents_XLog_SetLogPriority(xhLog, st_ServiceConfig.st_XLog.nLogType);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化日志系统成功"));

	signal(SIGINT, ServiceApp_Stop);
	signal(SIGTERM, ServiceApp_Stop);
	signal(SIGABRT, ServiceApp_Stop);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化信号量成功"));

	if (SystemApi_Process_IsAdmin())
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动权限设置为管理员"));
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,启动权限不足,对于进程和后台服务任务可能会执行失败"));
	}

	if (st_ServiceConfig.bHideWnd)
	{
#ifdef _MSC_BUILD
		HWND hWnd = GetConsoleWindow();
		if (NULL == hWnd)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,设置窗口隐藏失败,没有找到句柄"));
		}
		else
		{
			ShowWindow(hWnd, SW_HIDE);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,设置窗口隐藏成功"));
		}
#endif
	}

	if (st_ServiceConfig.st_XImageText.bEnable)
	{
		if (!ModuleHelp_ImageGet_TextInit(st_ServiceConfig.st_XImageText.tszImagePath, st_ServiceConfig.st_XImageText.tszImageLanguage))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化图像文字识别失败,错误：%lX"), ModuleHelp_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,初始化图像文字识别被禁用"));
	}
	//初始化数据库
	if (st_ServiceConfig.st_XSql.bEnable && !bIsTest)
	{
		if (!ModuleDatabase_IDCard_Init((DATABASE_MYSQL_CONNECTINFO*)&st_ServiceConfig.st_XSql))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化ID数据库失败,错误：%lX"), ModuleDB_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化ID数据库成功"));
		if (!ModuleDatabase_Bank_Init((DATABASE_MYSQL_CONNECTINFO*)&st_ServiceConfig.st_XSql))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化银行卡数据库失败,错误：%lX"), ModuleDB_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化银行卡数据库成功"));
		if (!ModuleDatabase_ZIPCode_Init((DATABASE_MYSQL_CONNECTINFO*)&st_ServiceConfig.st_XSql))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化行政邮编信息数据库失败,错误：%lX"), ModuleDB_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化行政邮编信息数据库成功"));
		if (!ModuleDatabase_XLog_Init((DATABASE_MYSQL_CONNECTINFO*)&st_ServiceConfig.st_XSql))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化日志信息数据库失败,错误：%lX"), ModuleDB_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化日志信息数据库成功"));
		if (!ModuleDatabase_ShortLink_Init((DATABASE_MYSQL_CONNECTINFO*)&st_ServiceConfig.st_XSql))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化短连接数据库失败,错误：%lX"), ModuleDB_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化短连接数据库成功"));
		if (!ModuleDatabase_WordFilter_Init((DATABASE_MYSQL_CONNECTINFO*)&st_ServiceConfig.st_XSql))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化敏感词数据库失败,错误：%lX"), ModuleDB_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化敏感词数据库成功"));
		if (!ModuleDatabase_Machine_Init((DATABASE_MYSQL_CONNECTINFO*)&st_ServiceConfig.st_XSql))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化信息收集数据库失败,错误：%lX"), ModuleDB_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化信息收集数据库成功"));
		if (!ModuleDatabase_OilInfo_Init((DATABASE_MYSQL_CONNECTINFO*)&st_ServiceConfig.st_XSql))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化油价查询数据库失败,错误：%lX"), ModuleDB_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化油价查询数据库成功"));
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,数据库操作被禁用,相关ID,银行卡,邮编,日志,短连接,敏感词,信息收集功能也被禁用"));
	}
	//启动HTTP服务相关代码
	if (st_ServiceConfig.nHttpPort > 0)
	{
		//HTTP包处理器
		xhHTTPPacket = HttpProtocol_Server_InitEx(st_ServiceConfig.st_XConfig.tszConfigHTTPCode, st_ServiceConfig.st_XConfig.tszConfigHTTPMime, st_ServiceConfig.st_XMax.nHTTPThread);
		if (NULL == xhHTTPPacket)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化HTTP组包失败,错误：%lX"), HttpProtocol_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化HTTP组包成功,IO线程个数:%d"), st_ServiceConfig.st_XMax.nHTTPThread);
		//启动心跳
		if (st_ServiceConfig.st_XTime.nHTTPTimeOut > 0)
		{
			xhHTTPHeart = SocketOpt_HeartBeat_InitEx(st_ServiceConfig.st_XTime.nHTTPTimeOut, st_ServiceConfig.st_XTime.nTimeCheck, Network_Callback_HTTPHeart);
			if (NULL == xhHTTPHeart)
			{
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化HTTP心跳服务失败,错误：%lX"), NetCore_GetLastError());
				goto XENGINE_SERVICEAPP_EXIT;
			}
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化HTTP心跳服务成功,时间:%d,次数:%d"), st_ServiceConfig.st_XTime.nHTTPTimeOut, st_ServiceConfig.st_XTime.nTimeCheck);
		}
		else
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,HTTP心跳服务被设置为不启用"));
		}
		//网络
		xhHTTPSocket = NetCore_TCPXCore_StartEx(st_ServiceConfig.nHttpPort, st_ServiceConfig.st_XMax.nMaxClient, st_ServiceConfig.st_XMax.nIOThread);
		if (NULL == xhHTTPSocket)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动HTTP网络服务器失败,错误：%lX"), NetCore_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动HTTP网络服务器成功,HTTP端口:%d,IO:%d"), st_ServiceConfig.nHttpPort, st_ServiceConfig.st_XMax.nIOThread);
		NetCore_TCPXCore_RegisterCallBackEx(xhHTTPSocket, Network_Callback_HTTPLogin, Network_Callback_HTTPRecv, Network_Callback_HTTPLeave);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,注册HTTP网络事件成功"));
		//HTTP任务池
		BaseLib_Memory_Malloc((XPPPMEM)&ppSt_ListHTTPParam, st_ServiceConfig.st_XMax.nHTTPThread, sizeof(THREADPOOL_PARAMENT));
		for (int i = 0; i < st_ServiceConfig.st_XMax.nHTTPThread; i++)
		{
			int* pInt_Pos = new int;

			*pInt_Pos = i;
			ppSt_ListHTTPParam[i]->lParam = pInt_Pos;
			ppSt_ListHTTPParam[i]->fpCall_ThreadsTask = HTTPTask_TastPost_Thread;
		}
		xhHTTPPool = ManagePool_Thread_NQCreate(&ppSt_ListHTTPParam, st_ServiceConfig.st_XMax.nHTTPThread);
		if (NULL == xhHTTPPool)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动HTTP线程池服务失败,错误：%lX"), ManagePool_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动HTTP线程池服务成功,启动个数:%d"), st_ServiceConfig.st_XMax.nHTTPThread);
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,HTTP服务没有被启用"));
	}
	//启动RFC标准服务
	if (st_ServiceConfig.nRFCPort > 0)
	{
		//网络
		xhRFCSocket = NetCore_UDPXCore_StartEx(st_ServiceConfig.nRFCPort, st_ServiceConfig.st_XMax.nIOThread);
		if (NULL == xhRFCSocket)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动RFC网络服务器失败,错误：%lX"), NetCore_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动RFC网络服务器成功,RFC端口:%d,IO:%d"), st_ServiceConfig.nRFCPort, st_ServiceConfig.st_XMax.nIOThread);
		NetCore_UDPXCore_RegisterCallBackEx(xhRFCSocket, Network_Callback_RFCRecv);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,注册RFC网络事件成功"));
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,RFC服务没有被启用"));
	}
	//初始化P2P
	if (st_ServiceConfig.st_XTime.nP2PTimeOut > 0)
	{
		if (!ModuleHelp_P2PClient_Init(st_ServiceConfig.st_XTime.nP2PTimeOut, HTTPTask_TastPost_P2PCallback))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动P2P客户端管理器失败,错误：%lX"), ModuleHelp_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动P2P客户端管理器成功,超时时间设置:%d 秒"), st_ServiceConfig.st_XTime.nP2PTimeOut);
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,P2P客户端管理器被设置为禁用"));
	}
	//进程守护
	if (!ModuleConfigure_Json_DeamonList(st_ServiceConfig.st_XConfig.tszConfigDeamon, &st_DeamonAppConfig))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动加载进程守护配置文件失败,错误：%lX"), ModuleConfigure_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动加载进程守护配置文件成功"));
	for (auto stl_ListIterator = st_DeamonAppConfig.stl_ListDeamonApp.begin(); stl_ListIterator != st_DeamonAppConfig.stl_ListDeamonApp.end(); stl_ListIterator++)
	{
		if (stl_ListIterator->bEnable)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,加载守护进程:%s,成功,开始守护进程"), stl_ListIterator->tszAPPName);
		}
		else
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,加载守护进程:%s,成功,此项目未启用"), stl_ListIterator->tszAPPName);
		}
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,加载守护进程列表成功,加载的列表个数:%d"), st_DeamonAppConfig.stl_ListDeamonApp.size());
	pSTDThread_Deamon = make_unique<thread>(HTTPTask_TaskPost_Thread);
	if (NULL == pSTDThread_Deamon)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动进程管理线程失败"));
		goto XENGINE_SERVICEAPP_EXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动进程管理线程成功"));

	//初始化插件配置
	if (st_ServiceConfig.st_XPlugin.bEnable)
	{
		if (!ModuleConfigure_Json_PluginFile(st_ServiceConfig.st_XPlugin.tszPluginLib, &st_PluginLibConfig))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化Lib插件配置文件失败,错误：%lX"), ModuleConfigure_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化Lib插件配置文件成功"));
		if (!ModuleConfigure_Json_PluginFile(st_ServiceConfig.st_XPlugin.tszPluginLua, &st_PluginLuaConfig))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化Lua插件配置文件失败,错误：%lX"), ModuleConfigure_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化Lua插件配置文件成功"));
		//启动插件
		if (!ModulePlugin_Loader_Init())
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化插件系统失败,错误：%lX"), ModulePlugin_GetLastError());
			goto XENGINE_SERVICEAPP_EXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化插件系统成功,开始加载插件"));
		//加载插件
		list<XENGINE_PLUGININFO>::const_iterator stl_ListIterator = st_PluginLibConfig.pStl_ListPlugin->begin();
		for (int i = 1; stl_ListIterator != st_PluginLibConfig.pStl_ListPlugin->end(); stl_ListIterator++, i++)
		{
			if (stl_ListIterator->bEnable)
			{
				if (ModulePlugin_Loader_Insert(stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile, 0))
				{
					XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,加载Lib模块插件中,当前第:%d 个加载成功,方法:%s,路径:%s"), i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile);
				}
				else
				{
					XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,加载Lib模块插件中,当前第:%d 个加载失败,方法:%s,路径:%s,错误:%lX"), i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile, ModulePlugin_GetLastError());
				}
			}
			else
			{
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,加载Lib模块插件中,当前第:%d 个加载失败,因为没有启用,方法:%s,路径:%s"), i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile);
			}
		}
#if (1 == _XENGINE_BUILD_SWITCH_LUA)
		stl_ListIterator = st_PluginLuaConfig.pStl_ListPlugin->begin();
		for (int i = 1; stl_ListIterator != st_PluginLuaConfig.pStl_ListPlugin->end(); stl_ListIterator++, i++)
		{
			if (stl_ListIterator->bEnable)
			{
				if (ModulePlugin_Loader_Insert(stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile, 1))
				{
					XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,加载Lua模块插件中,当前第:%d 个加载成功,方法:%s,路径:%s"), i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile);
				}
				else
				{
					XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,加载Lua模块插件中,当前第:%d 个加载失败,方法:%s,路径:%s,错误:%lX"), i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile, ModulePlugin_GetLastError());
				}
			}
			else
			{
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,加载Lua模块插件中,当前第:%d 个加载失败,因为没有启用,方法:%s,路径:%s"), i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile);
			}
		}
#else
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,加载Lua模块插件失败,因为LUA编译被关闭"));
#endif
		//展示能力
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,加载的Lib插件:%d 个,Lua插件:%d 个"), st_PluginLibConfig.pStl_ListPlugin->size(), st_PluginLuaConfig.pStl_ListPlugin->size());
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,插件系统被禁用"));
	}
	
	if (st_ServiceConfig.st_XAPIModule.bEnable)
	{
		if (!APIModule_IPAddr_Init(st_ServiceConfig.st_XAPIModule.tszDBIPAddr))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动IP地址数据查询服务:%s 失败，错误：%lX"), st_ServiceConfig.st_XAPIModule.tszDBIPAddr, APIIPMac_GetLastError());
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动IP地址数据查询服务:%s 成功"), st_ServiceConfig.st_XAPIModule.tszDBIPAddr);

		if (!APIModule_MACInfo_Init(st_ServiceConfig.st_XAPIModule.tszDBMac))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动MAC地址数据查询服务:%s 失败，错误：%lX"), st_ServiceConfig.st_XAPIModule.tszDBMac, APIIPMac_GetLastError());
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动MAC地址数据查询服务:%s 成功"), st_ServiceConfig.st_XAPIModule.tszDBMac);

		if (!APIModule_PhoneNumber_Init(st_ServiceConfig.st_XAPIModule.tszDBPhone))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动电话号码数据查询服务:%s 失败，错误：%lX"), st_ServiceConfig.st_XAPIModule.tszDBPhone, APIPhone_GetLastError());
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动电话号码数据查询服务:%s 成功"), st_ServiceConfig.st_XAPIModule.tszDBPhone);
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,数据查询服务没有启用"));
	}
#ifndef _DEBUG
	//发送信息报告
	if (st_ServiceConfig.st_XReport.bEnable && !bIsTest)
	{
		__int64x nTimeNumber = 0;
		if (InfoReport_APIMachine_Send(st_ServiceConfig.st_XReport.tszAPIUrl, st_ServiceConfig.st_XReport.tszServiceName, &nTimeNumber))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动信息报告给API服务器:%s 成功,报告次数:%lld"), st_ServiceConfig.st_XReport.tszAPIUrl, nTimeNumber);
		}
		else
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动信息报告给API服务器:%s 失败，错误：%lX"), st_ServiceConfig.st_XReport.tszAPIUrl, InfoReport_GetLastError());
		}
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,信息报告给API服务器没有启用"));
	}
#endif
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("所有服务成功启动,服务运行中,XEngine版本:%s%s,发行版本次数:%d,当前版本：%s。。。"), BaseLib_Version_XNumberStr(), BaseLib_Version_XTypeStr(), st_ServiceConfig.st_XVer.pStl_ListVer->size(), st_ServiceConfig.st_XVer.pStl_ListVer->front().c_str());
	while (true)
	{
		if (bIsTest)
		{
			nRet = 0;
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

XENGINE_SERVICEAPP_EXIT:
	if (bIsRun)
	{
		if (bIsTest && 0 == nRet)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("服务启动完毕，测试程序退出..."));
		}
		else
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("有服务启动失败,服务器退出..."));
		}
		bIsRun = false;
		//销毁HTTP资源
		NetCore_TCPXCore_DestroyEx(xhHTTPSocket);
		NetCore_UDPXCore_DestroyEx(xhRFCSocket);
		SocketOpt_HeartBeat_DestoryEx(xhHTTPHeart);
		HttpProtocol_Server_DestroyEx(xhHTTPPacket);
		ManagePool_Thread_NQDestroy(xhHTTPPool);
		//销毁数据库
		ModuleDatabase_IDCard_Destory();
		ModuleDatabase_Bank_Destory();
		ModuleDatabase_ZIPCode_Destory();
		ModuleDatabase_XLog_Destory();
		ModuleDatabase_ShortLink_Destory();
		ModuleDatabase_WordFilter_Destory();
		ModuleDatabase_Machine_Destory();
		ModuleDatabase_OilInfo_Destory();
		//销毁其他
		APIModule_IPAddr_UnInit();
		APIModule_MACInfo_UnInit();
		APIModule_PhoneNumber_UnInit();
		ModulePlugin_Loader_Destory();
		ModuleHelp_P2PClient_Destory();
		ModuleHelp_ImageGet_TextDestory();
		//销毁日志资源
		HelpComponents_XLog_Destroy(xhLog);
		//销毁线程
		if (NULL != pSTDThread_Deamon)
		{
			pSTDThread_Deamon->join();
		}
	}
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return nRet;
}