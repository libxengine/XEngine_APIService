#pragma once
//加载系统头文件
#include <windows.h>
#include <tchar.h>
#include <list>
#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;
//加载XEngine头文件
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_BaseLib/BaseSafe_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseSafe_Error.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Error.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Define.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Error.h>
//加载模块头文件
#include "../../XEngine_ModuleConfigure/ModuleConfig_Define.h"
#include "../../XEngine_ModuleConfigure/ModuleConfig_Error.h"
//加载自己的头文件
#include "XEngine_Configure.h"
/********************************************************************
//    Created:     2025/04/10  13:57:08
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ServiceApp\XEngine_APIServiceApp\XEngine_CommHdr.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ServiceApp\XEngine_APIServiceApp
//    File Base:   XEngine_CommHdr
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     公用头文件
//    History:
*********************************************************************/
extern bool bIsRun;
extern XHANDLE xhLog;
//配置文件
extern XENGINE_SERVICECONFIG st_ServiceConfig;
//连接库
#ifdef _MSC_BUILD
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseSafe")
#pragma comment(lib,"XEngine_HelpComponents/HelpComponents_XLog")
#pragma comment(lib,"XEngine_SystemSdk/XEngine_SystemApi")
#ifdef _DEBUG
#ifdef _M_X64
#pragma comment(lib,"../../x64/Debug/XEngine_ModuleConfigure.lib")
#elif _M_ARM64
#pragma comment(lib,"../../ARM64/Debug/XEngine_ModuleConfigure.lib")
#elif _M_IX86
#pragma comment(lib,"../../Debug/XEngine_ModuleConfigure.lib")
#endif
#else
#ifdef _M_X64
#pragma comment(lib,"../../x64/Release/XEngine_ModuleConfigure.lib")
#elif _M_ARM64
#pragma comment(lib,"../../ARM64/Release/XEngine_ModuleConfigure.lib")
#elif _M_IX86
#pragma comment(lib,"../../Release/XEngine_ModuleConfigure.lib")
#endif
#endif
#endif