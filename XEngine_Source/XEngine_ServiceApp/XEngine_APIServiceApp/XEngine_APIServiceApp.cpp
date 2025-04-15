#include "XEngine_CommHdr.h"
/********************************************************************
//    Created:     2025/04/10  13:57:58
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ServiceApp\XEngine_APIServiceApp\XEngine_APIServiceApp.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ServiceApp\XEngine_APIServiceApp
//    File Base:   XEngine_APIServiceApp
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     服务代码
//    History:
*********************************************************************/
bool bIsRun = false;
XHANDLE xhLog = NULL;
XLONG dwProcessID = 0;
XENGINE_SERVICECONFIG st_ServiceConfig = {};
// 服务名称，使用 constexpr 替代宏定义
constexpr LPCTSTR XENGINE_SERVICE_NAME = _T("XEngine_APIService");
constexpr LPCTSTR XENGINE_SERVICE_SHOW = _T("XEngine APIService 管理服务");
constexpr LPCTSTR XENGINE_SERVICE_DESCRIPTION = _T("XEngine APIService 数据查询与系统管理接口服务程序");
// 全局变量
SERVICE_STATUS st_ServiceStatus = { 0 };
SERVICE_STATUS_HANDLE hServiceStatusHandle = NULL;
// 函数声明
void WINAPI XEngine_ServiceCtrlHandler(DWORD dwControl);
void WINAPI XEngine_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
void XEngine_InstallService();
void XEngine_UninstallService();

bool XEngine_InitLog()
{
	if (NULL != xhLog)
	{
		return true;
	}
	//初始化参数
	if (!XEngine_Configure_Parament())
	{
		return false;
	}
	//初始日志
	HELPCOMPONENTS_XLOG_CONFIGURE st_XLogConfig = {};
	st_XLogConfig.XLog_MaxBackupFile = st_ServiceConfig.st_XLog.nMaxCount;
	st_XLogConfig.XLog_MaxSize = st_ServiceConfig.st_XLog.nMaxSize;
	_xstrcpy(st_XLogConfig.tszFileName, st_ServiceConfig.st_XLog.tszServiceFile, sizeof(st_XLogConfig.tszFileName));
	xhLog = HelpComponents_XLog_Init(st_ServiceConfig.st_XLog.nLogLeave, &st_XLogConfig);
	if (NULL == xhLog)
	{
		printf("启动服务中,启动日志失败,错误：%lX", XLog_GetLastError());
		return false;
	}
	//设置日志打印级别
	HelpComponents_XLog_SetLogPriority(xhLog, st_ServiceConfig.st_XLog.nLogType);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,初始化日志系统成功"));
	return true;
}
// 主函数
int _tmain(int argc, TCHAR* argv[])
{
#ifndef _DEBUG
	if (setlocale(LC_ALL, ".UTF8") == NULL)
	{
		printf("Error setting locale.\n");
		return -1;
	}
#endif
	XEngine_InitLog();
	if (argc > 1)
	{
		if (0 == _tcsicmp(argv[1], L"-install"))
		{
			XEngine_InstallService();
			return 0;
		}
		else if (0 == _tcsicmp(argv[1], L"-uninstall"))
		{
			XEngine_UninstallService();
			return 0;
		}
	}
	
	SERVICE_TABLE_ENTRY ServiceTable[] =
	{
		{ const_cast<LPTSTR>(XENGINE_SERVICE_NAME), (LPSERVICE_MAIN_FUNCTION)XEngine_ServiceMain },
		{ NULL, NULL }
	};
	if (!StartServiceCtrlDispatcher(ServiceTable))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动服务控制程序失败,错误:%d"), GetLastError());
		return -3;
	}
	return 0;
}

// 服务主函数
void WINAPI XEngine_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,开始处理服务程序"));
	// 初始化服务状态
	st_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	st_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	st_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	st_ServiceStatus.dwWin32ExitCode = 0;
	st_ServiceStatus.dwServiceSpecificExitCode = 0;
	st_ServiceStatus.dwCheckPoint = 0;
	st_ServiceStatus.dwWaitHint = 1000;
	// 注册服务控制处理程序
	hServiceStatusHandle = RegisterServiceCtrlHandlerW(XENGINE_SERVICE_NAME, XEngine_ServiceCtrlHandler);
	if (NULL == hServiceStatusHandle)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,注册服务控制程序失败,错误:%d"), GetLastError());
		return;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,注册服务控制程序成功"));
	// 服务启动完成
	if (!SetServiceStatus(hServiceStatusHandle, &st_ServiceStatus))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动服务设置状态失败,错误:%d"), GetLastError());
		return;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,设置服务程序状态成功"));
	// 服务启动完成
	st_ServiceStatus.dwCheckPoint = 0;
	st_ServiceStatus.dwWaitHint = 0;
	st_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	st_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	if (!SetServiceStatus(hServiceStatusHandle, &st_ServiceStatus))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,启动服务启动状态失败,错误:%d"), GetLastError());
		return;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("启动服务中,设置服务启动状态成功,服务运行中"));
	bIsRun = true;
	while (bIsRun)
	{
		SYSTEMAPI_PROCESS_INFOMATION st_ProcessInfo = {};
		if (!SystemApi_Process_GetProcessInfo(&st_ProcessInfo, NULL, dwProcessID))
		{
			SystemApi_Process_CreateProcess(&dwProcessID, "./XEngine_HttpApp.exe", "-db 0", st_ServiceConfig.bShowWnd);
		}
		Sleep(1000); 
	}
}
// 服务控制处理函数
void WINAPI XEngine_ServiceCtrlHandler(DWORD dwControl)
{
	switch (dwControl)
	{
	case SERVICE_CONTROL_PAUSE:
		break;
	case SERVICE_CONTROL_CONTINUE:
		st_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		SetServiceStatus(hServiceStatusHandle, &st_ServiceStatus);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,收到命令,继续执行"));
		break;
	case SERVICE_CONTROL_STOP:
		bIsRun = false;
		SystemApi_Process_Stop(NULL, dwProcessID);
		st_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(hServiceStatusHandle, &st_ServiceStatus);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,收到命令,停止运行"));
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		bIsRun = false;
		SystemApi_Process_Stop(NULL, dwProcessID);
		st_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(hServiceStatusHandle, &st_ServiceStatus);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,收到命令,关闭程序"));
		break;
	default:
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,收到无法处理的命令:%d"), dwControl);
		break;
	}
}
// 安装服务
void XEngine_InstallService()
{
	TCHAR tszFilePath[MAX_PATH] = {};
	if (!GetModuleFileName(NULL, tszFilePath, MAX_PATH))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,安装服务失败,获取文件路径失败,错误码:%d"), GetLastError());
		return;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,安装服务中,获取本地路径成功:%s"), tszFilePath);

	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (NULL == hSCManager)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,安装服务失败,打开权限错误,错误码:%d"), GetLastError());
		return;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,安装服务中,打开服务成功"));

	SC_HANDLE hService = CreateService(hSCManager, XENGINE_SERVICE_NAME, XENGINE_SERVICE_SHOW, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, tszFilePath, NULL, NULL, NULL, NULL, NULL);
	if (NULL == hService)
	{
		CloseServiceHandle(hSCManager);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,安装服务失败,创建服务失败,错误码:%d"), GetLastError());
		return;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,安装服务中,创建服务成功"));

	SERVICE_DESCRIPTION st_ServiceDescpition = { };
	st_ServiceDescpition.lpDescription = const_cast<LPTSTR>(XENGINE_SERVICE_DESCRIPTION); // 描述内容
	if (!ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &st_ServiceDescpition))
	{
		CloseServiceHandle(hSCManager);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,安装服务失败,设置服务描述失败,错误码:%d"), GetLastError());
		return;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,安装服务中,设置服务描述内容成功"));

	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,安装服务成功"));
}
// 卸载服务
void XEngine_UninstallService()
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL == hSCManager)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,卸载服务失败,打开权限错误,错误码:%d"), GetLastError());
		return;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,卸载服务中,打开权限成功"));

	SC_HANDLE hService = OpenService(hSCManager, XENGINE_SERVICE_NAME, DELETE);
	if (!hService)
	{
		CloseServiceHandle(hSCManager);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,卸载服务失败,获取权限失败,错误码:%d"), GetLastError());
		return;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,卸载服务中,获取删除权限成功"));

	if (!DeleteService(hService))
	{
		CloseServiceHandle(hSCManager);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("启动服务中,卸载服务失败,删除服务失败,错误码:%d"), GetLastError());
		return;
	}
	CloseServiceHandle(hSCManager);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("服务运行中,卸载服务中,删除服务成功"));
}