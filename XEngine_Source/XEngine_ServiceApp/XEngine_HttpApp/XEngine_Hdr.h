﻿#pragma once
//加载系统头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <thread>
#include <string>
#include <list>
#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <arpa/inet.h>
#endif
using namespace std;
//加载XEngine头文件
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Core/NetCore_Define.h>
#include <XEngine_Include/XEngine_Core/NetCore_Error.h>
#include <XEngine_Include/XEngine_Core/ManagePool_Define.h>
#include <XEngine_Include/XEngine_Core/ManagePool_Error.h>
#include <XEngine_Include/XEngine_Core/OPenSsl_Define.h>
#include <XEngine_Include/XEngine_Core/OPenSsl_Error.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Error.h>
#include <XEngine_Include/XEngine_HelpComponents/DataBase_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/DataBase_Error.h>
#include <XEngine_Include/XEngine_RfcComponents/HttpProtocol_Define.h>
#include <XEngine_Include/XEngine_RfcComponents/HttpProtocol_Error.h>
#include <XEngine_Include/XEngine_NetHelp/APIClient_Define.h>
#include <XEngine_Include/XEngine_NetHelp/APIClient_Error.h>
#include <XEngine_Include/XEngine_SystemSdk/ProcFile_Define.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Define.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Error.h>
//加载项目相关头文件
#include "../../XEngine_UserProtocol.h"
#include "../../XEngine_ModuleConfigure/ModuleConfig_Define.h"
#include "../../XEngine_ModuleConfigure/ModuleConfig_Error.h"
#include "../../XEngine_ModuleDatabase/ModuleDB_Define.h"
#include "../../XEngine_ModuleDatabase/ModuleDB_Error.h"
#include "../../XEngine_ModuleProtocol/ModuleProtocol_Define.h"
#include "../../XEngine_ModuleProtocol/ModuleProtocol_Error.h"
#include "../../XEngine_ModuleHelp/ModuleHelp_Define.h"
#include "../../XEngine_ModuleHelp/ModuleHelp_Error.h"
#include "../../XEngine_ModulePlugin/ModulePlugin_Define.h"
#include "../../XEngine_ModulePlugin/ModulePlugin_Error.h"
//加载自己的头文件
#include "XEngine_Configure.h"
#include "XEngine_Network.h"
#include "XEngine_HTTPTask.h"
#include "XEngine_PluginTask.h"
#include "XEngine_HTTPTask/HTTPTask_IDCard.h"
#include "XEngine_HTTPTask/HTTPTask_Bank.h"
#include "XEngine_HTTPTask/HTTPTask_Language.h"
#include "XEngine_HTTPTask/HTTPTask_Translation.h"
#include "XEngine_HTTPTask/HTTPTask_Locker.h"
#include "XEngine_HTTPTask/HTTPTask_OPtions.h"
#include "XEngine_HTTPTask/HTTPTask_P2PClient.h"
#include "XEngine_HTTPTask/HTTPTask_PostCode.h"
#include "XEngine_HTTPTask/HTTPTask_Log.h"
#include "XEngine_HTTPTask/HTTPTask_QRCode.h"
#include "XEngine_HTTPTask/HTTPTask_SocketTest.h"
/********************************************************************
//    Created:     2022/01/20  14:42:06
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp\XEngine_Hdr.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp
//    File Base:   XEngine_Hdr
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     公用头文件
//    History:
*********************************************************************/
#define XENGIEN_APISERVICE_BUFFER_SIZE (1024 * 1024 * 10)

extern XBOOL bIsRun;
extern XHANDLE xhLog;
//HTTP服务器
extern XHANDLE xhHTTPSocket;
extern XHANDLE xhHTTPHeart;
extern XHANDLE xhHTTPPacket;
extern XHANDLE xhHTTPPool;
//配置文件
extern XENGINE_SERVICECONFIG st_ServiceConfig;
extern XENGINE_OPENCCCONFIG st_OPenccConfig;
extern XENGINE_QRCODECONFIG st_QRCodeConfig;
extern XENGINE_PLUGINCONFIG st_PluginLibConfig;
extern XENGINE_PLUGINCONFIG st_PluginLuaConfig;
//连接库
#ifdef _MSC_BUILD
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib,"../../x64/Debug/XEngine_ModuleConfigure.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_ModuleDatabase.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_ModuleProtocol.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_ModuleHelp.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_ModulePlugin.lib")
#else
#pragma comment(lib,"../../x64/Release/XEngine_ModuleConfigure.lib")
#pragma comment(lib,"../../x64/Release/XEngine_ModuleDatabase.lib")
#pragma comment(lib,"../../x64/Release/XEngine_ModuleProtocol.lib")
#pragma comment(lib,"../../x64/Release/XEngine_ModuleHelp.lib")
#pragma comment(lib,"../../x64/Release/XEngine_ModulePlugin.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib,"../../Debug/XEngine_ModuleConfigure.lib")
#pragma comment(lib,"../../Debug/XEngine_ModuleDatabase.lib")
#pragma comment(lib,"../../Debug/XEngine_ModuleProtocol.lib")
#pragma comment(lib,"../../Debug/XEngine_ModuleHelp.lib")
#pragma comment(lib,"../../Debug/XEngine_ModulePlugin.lib")
#else
#pragma comment(lib,"../../Release/XEngine_ModuleConfigure.lib")
#pragma comment(lib,"../../Release/XEngine_ModuleDatabase.lib")
#pragma comment(lib,"../../Release/XEngine_ModuleProtocol.lib")
#pragma comment(lib,"../../Release/XEngine_ModuleHelp.lib")
#pragma comment(lib,"../../Release/XEngine_ModulePlugin.lib")
#endif
#endif
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib.lib")
#pragma comment(lib,"XEngine_Core/XEngine_Core.lib")
#pragma comment(lib,"XEngine_Core/XEngine_ManagePool.lib")
#pragma comment(lib,"XEngine_Core/XEngine_OPenSsl.lib")
#pragma comment(lib,"XEngine_HelpComponents/HelpComponents_XLog.lib")
#pragma comment(lib,"XEngine_RfcComponents/RfcComponents_HttpProtocol.lib")
#pragma comment(lib,"XEngine_NetHelp/NetHelp_APIClient.lib")
#pragma comment(lib,"XEngine_SystemSdk/XEngine_SystemApi")
#pragma comment(lib,"Ws2_32.lib")
#endif