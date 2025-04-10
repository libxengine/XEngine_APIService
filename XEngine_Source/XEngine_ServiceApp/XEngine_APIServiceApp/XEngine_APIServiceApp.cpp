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
XENGINE_SERVICECONFIG st_ServiceConfig = {};
// 服务名称，使用 constexpr 替代宏定义
constexpr LPCWSTR SERVICE_NAME = L"XEngine_APIService";
// 全局变量
SERVICE_STATUS st_ServiceStatus = { 0 };
SERVICE_STATUS_HANDLE st_hServiceStatusHandle = nullptr;
// 函数声明
void WINAPI XEngine_ServiceCtrlHandler(DWORD dwControl);
void WINAPI XEngine_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
void XEngine_InstallService();
void XEngine_UninstallService();
// 主函数
int wmain(int argc, wchar_t* argv[])
{
	//初始化参数
	if (!XEngine_Configure_Parament(argc, argv))
	{
		return 0;
	}

	if (argc > 1)
	{
		if (_wcsicmp(argv[1], L"install") == 0)
		{
			XEngine_InstallService();
			return 0;
		}
		else if (_wcsicmp(argv[1], L"uninstall") == 0)
		{
			XEngine_UninstallService();
			return 0;
		}
	}

	SERVICE_TABLE_ENTRYW ServiceTable[] =
	{
		{ const_cast<LPWSTR>(SERVICE_NAME), (LPSERVICE_MAIN_FUNCTIONW)XEngine_ServiceMain },
		{ nullptr, nullptr }
	};

	if (!StartServiceCtrlDispatcherW(ServiceTable))
	{
		std::wcerr << L"StartServiceCtrlDispatcher failed (" << GetLastError() << L")\n";
		return 1;
	}
	return 0;
}

// 服务主函数
void WINAPI XEngine_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	// 初始化服务状态
	st_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	st_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	st_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	st_ServiceStatus.dwWin32ExitCode = 0;
	st_ServiceStatus.dwServiceSpecificExitCode = 0;
	st_ServiceStatus.dwCheckPoint = 0;
	st_ServiceStatus.dwWaitHint = 0;

	// 注册服务控制处理程序
	st_hServiceStatusHandle = RegisterServiceCtrlHandlerW(SERVICE_NAME, XEngine_ServiceCtrlHandler);
	if (NULL == st_hServiceStatusHandle)
	{
		throw std::runtime_error("RegisterServiceCtrlHandler failed");
	}

	// 服务启动完成
	st_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	if (!SetServiceStatus(st_hServiceStatusHandle, &st_ServiceStatus))
	{
		throw std::runtime_error("SetServiceStatus failed");
	}

	// 服务主循环（示例）
	while (st_ServiceStatus.dwCurrentState == SERVICE_RUNNING)
	{
		Sleep(1000); // 模拟服务工作
		// 在这里添加你的服务逻辑
	}
	try
	{
		
	}
	catch (const std::exception& e)
	{
		std::wcerr << L"ServiceMain exception: " << e.what() << L"\n";
		st_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(st_hServiceStatusHandle, &st_ServiceStatus);
	}
}

// 服务控制处理函数
void WINAPI XEngine_ServiceCtrlHandler(DWORD dwControl)
{
	switch (dwControl)
	{
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
		st_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(st_hServiceStatusHandle, &st_ServiceStatus);
		break;
	default:
		break;
	}
}

// 安装服务
void XEngine_InstallService()
{
	try
	{
		wchar_t szPath[MAX_PATH];
		if (!GetModuleFileNameW(nullptr, szPath, MAX_PATH))
		{
			throw std::runtime_error("GetModuleFileName failed");
		}

		auto hSCManager = std::unique_ptr<std::remove_pointer_t<SC_HANDLE>, decltype(&CloseServiceHandle)>(
			OpenSCManagerW(nullptr, nullptr, SC_MANAGER_CREATE_SERVICE),
			CloseServiceHandle
		);
		if (!hSCManager)
		{
			throw std::runtime_error("OpenSCManager failed");
		}

		auto hService = std::unique_ptr<std::remove_pointer_t<SC_HANDLE>, decltype(&CloseServiceHandle)>(CreateServiceW(hSCManager.get(), SERVICE_NAME, L"My Modern Service",SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,szPath, nullptr, nullptr, nullptr, nullptr, nullptr),CloseServiceHandle
		);
		if (!hService)
		{
			throw std::runtime_error("CreateService failed");
		}

		std::wcout << L"Service installed successfully\n";
	}
	catch (const std::exception& e)
	{
		std::wcerr << L"XEngine_InstallService exception: " << e.what() << L"\n";
	}
}

// 卸载服务
void XEngine_UninstallService()
{
	try
	{
		auto hSCManager = std::unique_ptr<std::remove_pointer_t<SC_HANDLE>, decltype(&CloseServiceHandle)>(OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS), CloseServiceHandle);
		if (!hSCManager)
		{
			throw std::runtime_error("OpenSCManager failed");
		}
		auto hService = std::unique_ptr<std::remove_pointer_t<SC_HANDLE>, decltype(&CloseServiceHandle)>(OpenServiceW(hSCManager.get(), SERVICE_NAME, DELETE), CloseServiceHandle);
		if (!hService)
		{
			throw std::runtime_error("OpenService failed");
		}

		if (!DeleteService(hService.get()))
		{
			throw std::runtime_error("DeleteService failed");
		}
		std::wcout << L"Service uninstalled successfully\n";
	}
	catch (const std::exception& e)
	{
		std::wcerr << L"XEngine_UninstallService exception: " << e.what() << L"\n";
	}
}