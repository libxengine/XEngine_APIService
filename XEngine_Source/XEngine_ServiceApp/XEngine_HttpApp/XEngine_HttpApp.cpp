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
XHANDLE xhLog = NULL;
//HTTP服务器
XHANDLE xhHTTPSocket = NULL;
XHANDLE xhHTTPHeart = NULL;
XHANDLE xhHTTPPacket = NULL;
XHANDLE xhHTTPPool = 0;
//配置文件
XENGINE_SERVICECONFIG st_ServiceConfig;
XENGINE_OPENCCCONFIG st_OPenccConfig;
XENGINE_QRCODECONFIG st_QRCodeConfig;
XENGINE_PLUGINCONFIG st_PluginLibConfig;
XENGINE_PLUGINCONFIG st_PluginLuaConfig;

void ServiceApp_Stop(int signo)
{
	if (bIsRun)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("服务器退出..."));
		bIsRun = false;
		//销毁HTTP资源
		NetCore_TCPXCore_DestroyEx(xhHTTPSocket);
		SocketOpt_HeartBeat_DestoryEx(xhHTTPHeart);
		HttpProtocol_Server_DestroyEx(xhHTTPPacket);
		ManagePool_Thread_NQDestroy(xhHTTPPool);
		//销毁数据库
		ModuleDatabase_IDCard_Destory();
		ModuleDatabase_Bank_Destory();
		ModuleDatabase_ZIPCode_Destory();
		ModuleDatabase_XLog_Destory();
		ModuleDatabase_ShortLink_Destory();
		//销毁其他
		ModulePlugin_Loader_Destory();
		ModuleHelp_P2PClient_Destory();
		//销毁日志资源
		HelpComponents_XLog_Destroy(xhLog);
	}
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	exit(0);
}
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
#endif
	bIsRun = true;
	LPCXSTR lpszHTTPMime = _X("./XEngine_Config/HttpMime.types");
	LPCXSTR lpszHTTPCode = _X("./XEngine_Config/HttpCode.types");
	LPCXSTR lpszLogFile = _X("./XEngine_Log/XEngine_HttpApp.Log");
	HELPCOMPONENTS_XLOG_CONFIGURE st_XLogConfig;
	THREADPOOL_PARAMENT** ppSt_ListHTTPParam;

	memset(&st_XLogConfig, '\0', sizeof(HELPCOMPONENTS_XLOG_CONFIGURE));
	memset(&st_ServiceConfig, '\0', sizeof(XENGINE_SERVICECONFIG));
	memset(&st_OPenccConfig, '\0', sizeof(XENGINE_OPENCCCONFIG));
	memset(&st_QRCodeConfig, '\0', sizeof(XENGINE_QRCODECONFIG));
	memset(&st_PluginLibConfig, '\0', sizeof(XENGINE_PLUGINCONFIG));
	memset(&st_PluginLuaConfig, '\0', sizeof(XENGINE_PLUGINCONFIG));

	st_XLogConfig.XLog_MaxBackupFile = 10;
	st_XLogConfig.XLog_MaxSize = 1024000;
	_tcsxcpy(st_XLogConfig.tszFileName, lpszLogFile);
	//初始化参数
	if (!XEngine_Configure_Parament(argc, argv, &st_ServiceConfig))
	{
		return -1;
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
	xhLog = HelpComponents_XLog_Init(HELPCOMPONENTS_XLOG_OUTTYPE_STD | HELPCOMPONENTS_XLOG_OUTTYPE_FILE, &st_XLogConfig);
	if (NULL == xhLog)
	{
		printf("启动服务中,启动日志失败,错误：%lX", XLog_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	//设置日志打印级别
	HelpComponents_XLog_SetLogPriority(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化日志系统成功"));

	signal(SIGINT, ServiceApp_Stop);
	signal(SIGTERM, ServiceApp_Stop);
	signal(SIGABRT, ServiceApp_Stop);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化信号量成功"));

	//初始化OPENCC配置
	if (!ModuleConfigure_Json_OPenccFile(st_ServiceConfig.st_XConfig.tszConfigOPencc, &st_OPenccConfig))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化OPenCC配置文件失败,错误：%lX"), ModuleConfigure_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化OPenCC配置文件:%s 成功"), st_ServiceConfig.st_XConfig.tszConfigOPencc);
	if (!ModuleConfigure_Json_QRCodeFile(st_ServiceConfig.st_XConfig.tszConfigQRCode, &st_QRCodeConfig))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化二维码配置文件失败,错误：%lX"), ModuleConfigure_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化二维码配置文件:%s 成功"), st_ServiceConfig.st_XConfig.tszConfigQRCode);
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
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,插件系统被禁用"));
	}
	//初始化数据库
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
	//启动HTTP服务相关代码
	if (st_ServiceConfig.nHttpPort > 0)
	{
		//HTTP包处理器
		xhHTTPPacket = HttpProtocol_Server_InitEx(lpszHTTPCode, lpszHTTPMime, st_ServiceConfig.st_XMax.nHTTPThread);
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
		BaseLib_OperatorMemory_Malloc((XPPPMEM)&ppSt_ListHTTPParam, st_ServiceConfig.st_XMax.nHTTPThread, sizeof(THREADPOOL_PARAMENT));
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
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("启动服务中,HTTP消息服务没有被启用"));
	}
	//初始化P2P
	if (!ModuleHelp_P2PClient_Init(st_ServiceConfig.st_XTime.nP2PTimeOut, HTTPTask_TastPost_P2PCallback))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动P2P客户端管理器失败,错误：%lX"), ModuleHelp_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,启动P2P客户端管理器成功,超时时间设置:%d 秒"), st_ServiceConfig.st_XTime.nP2PTimeOut);

	//启动插件
	if (!ModulePlugin_Loader_Init())
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,初始化插件系统失败,错误：%lX"), ModulePlugin_GetLastError());
		goto XENGINE_SERVICEAPP_EXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化插件系统成功,开始加载插件"));
	//加载插件
	{
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
	}
	
	{
		list<XENGINE_PLUGININFO>::const_iterator stl_ListIterator = st_PluginLuaConfig.pStl_ListPlugin->begin();
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
	}
	//展示能力
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,加载的Lib插件:%d 个,Lua插件:%d 个"), st_PluginLibConfig.pStl_ListPlugin->size(), st_PluginLuaConfig.pStl_ListPlugin->size());

	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("所有服务成功启动，服务运行中，XEngine版本:%s%s,发行版本次数:%d,当前版本：%s。。。"), BaseLib_OperatorVer_XNumberStr(), BaseLib_OperatorVer_XTypeStr(), st_ServiceConfig.st_XVer.pStl_ListVer->size(), st_ServiceConfig.st_XVer.pStl_ListVer->front().c_str());
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

XENGINE_SERVICEAPP_EXIT:
	if (bIsRun)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("有服务启动失败,服务器退出..."));
		bIsRun = false;
		//销毁HTTP资源
		NetCore_TCPXCore_DestroyEx(xhHTTPSocket);
		SocketOpt_HeartBeat_DestoryEx(xhHTTPHeart);
		HttpProtocol_Server_DestroyEx(xhHTTPPacket);
		ManagePool_Thread_NQDestroy(xhHTTPPool);
		//销毁数据库
		ModuleDatabase_IDCard_Destory();
		ModuleDatabase_Bank_Destory();
		ModuleDatabase_ZIPCode_Destory();
		ModuleDatabase_XLog_Destory();
		ModuleDatabase_ShortLink_Destory();
		//销毁其他
		ModulePlugin_Loader_Destory();
		ModuleHelp_P2PClient_Destory();
		//销毁日志资源
		HelpComponents_XLog_Destroy(xhLog);
	}
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}