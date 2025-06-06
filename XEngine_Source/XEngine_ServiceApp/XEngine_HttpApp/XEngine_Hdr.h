#pragma once
//加载系统头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <locale.h>
#include <thread>
#include <string>
#include <list>
#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#include <Dbghelp.h>
#else
#include <unistd.h>
#include <pthread.h>
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
#include <XEngine_Include/XEngine_BaseLib/BaseSafe_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseSafe_Error.h>
#include <XEngine_Include/XEngine_Core/NetCore_Define.h>
#include <XEngine_Include/XEngine_Core/NetCore_Error.h>
#include <XEngine_Include/XEngine_Core/ManagePool_Define.h>
#include <XEngine_Include/XEngine_Core/ManagePool_Error.h>
#include <XEngine_Include/XEngine_Core/Cryption_Define.h>
#include <XEngine_Include/XEngine_Core/Cryption_Error.h>
#include <XEngine_Include/XEngine_Client/APIClient_Define.h>
#include <XEngine_Include/XEngine_Client/APIClient_Error.h>
#include <XEngine_Include/XEngine_Client/StreamClient_Define.h>
#include <XEngine_Include/XEngine_Client/StreamClient_Error.h>
#include <XEngine_Include/XEngine_NetHelp/APIAddr_Define.h>
#include <XEngine_Include/XEngine_NetHelp/APIAddr_Error.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Error.h>
#include <XEngine_Include/XEngine_HelpComponents/DataBase_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/DataBase_Error.h>
#include <XEngine_Include/XEngine_RfcComponents/HttpProtocol_Define.h>
#include <XEngine_Include/XEngine_RfcComponents/HttpProtocol_Error.h>
#include <XEngine_Include/XEngine_RfcComponents/NatProtocol_Define.h>
#include <XEngine_Include/XEngine_RfcComponents/NatProtocol_Error.h>
#include <XEngine_Include/XEngine_RfcComponents/NTPProtocol_Define.h>
#include <XEngine_Include/XEngine_RfcComponents/NTPProtocol_Error.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Define.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Error.h>
#include <XEngine_Include/XEngine_AVCodec/AVCollect_Define.h>
#include <XEngine_Include/XEngine_AVCodec/AVCollect_Error.h>
#include <XEngine_Include/XEngine_AVCodec/VideoCodec_Define.h>
#include <XEngine_Include/XEngine_AVCodec/VideoCodec_Error.h>
#include <XEngine_Include/XEngine_AVCodec/AudioCodec_Define.h>
#include <XEngine_Include/XEngine_AVCodec/AudioCodec_Error.h>
#include <XEngine_Include/XEngine_AVCodec/AVHelp_Define.h>
#include <XEngine_Include/XEngine_AVCodec/AVHelp_Error.h>
#include "../../XEngine_Depend/XEngine_Module/XEngine_InfoReport/InfoReport_Define.h"
#include "../../XEngine_Depend/XEngine_Module/XEngine_InfoReport/InfoReport_Error.h"
#include "../../XEngine_DBDepend/XEngine_IPMacData/XEngine_Source/XIPMac_CommHdr.h"
#include "../../XEngine_DBDepend/XEngine_IPMacData/XEngine_Source/XEngine_APIModuleIPMac/APIIPMac_Define.h"
#include "../../XEngine_DBDepend/XEngine_IPMacData/XEngine_Source/XEngine_APIModuleIPMac/APIIPMac_Error.h"
#include "../../XEngine_DBDepend/XEngine_PhoneData/Source/XPhone_CommHdr.h"
#include "../../XEngine_DBDepend/XEngine_PhoneData/Source/C/XEngine_APIModulePhone/APIPhone_Define.h"
#include "../../XEngine_DBDepend/XEngine_PhoneData/Source/C/XEngine_APIModulePhone/APIPhone_Error.h"
//加载项目相关头文件
#include "../../XEngine_BuildSwitch.h"
#include "../../XEngine_UserProtocol.h"
#include "../../XEngine_ModuleConfigure/ModuleConfig_Define.h"
#include "../../XEngine_ModuleConfigure/ModuleConfig_Error.h"
#include "../../XEngine_ModuleDatabase/ModuleDB_Define.h"
#include "../../XEngine_ModuleDatabase/ModuleDB_Error.h"
#include "../../XEngine_ModuleProtocol/ModuleProtocol_Define.h"
#include "../../XEngine_ModuleProtocol/ModuleProtocol_Error.h"
#include "../../XEngine_ModuleSystem/ModuleSystem_Define.h"
#include "../../XEngine_ModuleSystem/ModuleSystem_Error.h"
#include "../../XEngine_ModuleHelp/ModuleHelp_Define.h"
#include "../../XEngine_ModuleHelp/ModuleHelp_Error.h"
#include "../../XEngine_ModulePlugin/ModulePlugin_Define.h"
#include "../../XEngine_ModulePlugin/ModulePlugin_Error.h"
//加载自己的头文件
#include "XEngine_Configure.h"
#include "XEngine_Network.h"
#include "XEngine_HTTPTask.h"
#include "XEngine_PluginTask.h"
//post
#include "XEngine_TaskPost/TaskPost_DTest.h"
#include "XEngine_TaskPost/TaskPost_Log.h"
#include "XEngine_TaskPost/TaskPost_P2PClient.h"
#include "XEngine_TaskPost/TaskPost_PostCode.h"
#include "XEngine_TaskPost/TaskPost_SocketTest.h"
#include "XEngine_TaskPost/TaskPost_QRCode.h"
#include "XEngine_TaskPost/TaskPost_ShortLink.h"
#include "XEngine_TaskPost/TaskPost_WordFilter.h"
#include "XEngine_TaskPost/TaskPost_BackService.h"
#include "XEngine_TaskPost/TaskPost_Image.h"
#include "XEngine_TaskPost/TaskPost_Deamon.h"
#include "XEngine_TaskPost/TaskPost_Machine.h"
//get
#include "XEngine_TaskGet/TaskGet_IDCard.h"
#include "XEngine_TaskGet/TaskGet_Bank.h"
#include "XEngine_TaskGet/TaskGet_Translation.h"
#include "XEngine_TaskGet/TaskGet_Locker.h"
#include "XEngine_TaskGet/TaskGet_Reload.h"
#include "XEngine_TaskGet/TaskGet_Weather.h"
#include "XEngine_TaskGet/TaskGet_IDRegion.h"
#include "XEngine_TaskGet/TaskGet_Oil.h"
#include "XEngine_TaskGet/TaskGet_APIModule.h"
//rfc
#include "XEngine_TaskRfc/RFCTask_Stun.h"
#include "XEngine_TaskRfc/RFCTask_Ntp.h"
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
extern bool bIsRun;
extern bool bIsTest;
extern XHANDLE xhLog;
//HTTP服务器
extern XHANDLE xhHTTPSocket;
extern XHANDLE xhRFCSocket;
extern XHANDLE xhHTTPHeart;
extern XHANDLE xhHTTPPacket;
extern XHANDLE xhHTTPPool;
//线程
extern unique_ptr<thread> pSTDThread_Deamon;
//配置文件
extern XENGINE_SERVICECONFIG st_ServiceConfig;
extern XENGINE_DEAMONAPPLIST st_DeamonAppConfig;
//连接库
#ifdef _MSC_BUILD
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib.lib")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseSafe.lib")
#pragma comment(lib,"XEngine_Core/XEngine_Core.lib")
#pragma comment(lib,"XEngine_Core/XEngine_ManagePool.lib")
#pragma comment(lib,"XEngine_Core/XEngine_Cryption.lib")
#pragma comment(lib,"XEngine_Client/XClient_Stream.lib")
#pragma comment(lib,"XEngine_Client/XClient_APIHelp.lib")
#pragma comment(lib,"XEngine_NetHelp/NetHelp_APIAddr")
#pragma comment(lib,"XEngine_HelpComponents/HelpComponents_XLog.lib")
#pragma comment(lib,"XEngine_RfcComponents/RfcComponents_HttpProtocol.lib")
#pragma comment(lib,"XEngine_RfcComponents/RfcComponents_NatProtocol.lib")
#pragma comment(lib,"XEngine_RfcComponents/RfcComponents_NTPProtocol.lib")
#pragma comment(lib,"XEngine_SystemSdk/XEngine_SystemApi")
#pragma comment(lib,"XEngine_AVCodec/XEngine_AVCollect.lib")
#pragma comment(lib,"XEngine_AVCodec/XEngine_VideoCodec.lib")
#pragma comment(lib,"XEngine_AVCodec/XEngine_AudioCodec.lib")
#pragma comment(lib,"XEngine_AVCodec/XEngine_AVHelp.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Dbghelp.lib")
#ifdef _DEBUG
#ifdef _M_X64
#pragma comment(lib,"../../x64/Debug/XEngine_InfoReport.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_APIModuleIPMac.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_APIModulePhone.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_ModuleConfigure.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_ModuleDatabase.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_ModuleProtocol.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_ModuleSystem.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_ModuleHelp.lib")
#pragma comment(lib,"../../x64/Debug/XEngine_ModulePlugin.lib")
#elif _M_ARM64
#pragma comment(lib,"../../ARM64/Debug/XEngine_InfoReport.lib")
#pragma comment(lib,"../../ARM64/Debug/XEngine_APIModuleIPMac.lib")
#pragma comment(lib,"../../ARM64/Debug/XEngine_APIModulePhone.lib")
#pragma comment(lib,"../../ARM64/Debug/XEngine_ModuleConfigure.lib")
#pragma comment(lib,"../../ARM64/Debug/XEngine_ModuleDatabase.lib")
#pragma comment(lib,"../../ARM64/Debug/XEngine_ModuleProtocol.lib")
#pragma comment(lib,"../../ARM64/Debug/XEngine_ModuleSystem.lib")
#pragma comment(lib,"../../ARM64/Debug/XEngine_ModuleHelp.lib")
#pragma comment(lib,"../../ARM64/Debug/XEngine_ModulePlugin.lib")
#elif _M_IX86
#pragma comment(lib,"../../Debug/XEngine_InfoReport.lib")
#pragma comment(lib,"../../Debug/XEngine_APIModuleIPMac.lib")
#pragma comment(lib,"../../Debug/XEngine_APIModulePhone.lib")
#pragma comment(lib,"../../Debug/XEngine_ModuleConfigure.lib")
#pragma comment(lib,"../../Debug/XEngine_ModuleDatabase.lib")
#pragma comment(lib,"../../Debug/XEngine_ModuleProtocol.lib")
#pragma comment(lib,"../../Debug/XEngine_ModuleSystem.lib")
#pragma comment(lib,"../../Debug/XEngine_ModuleHelp.lib")
#pragma comment(lib,"../../Debug/XEngine_ModulePlugin.lib")
#endif
#else
#ifdef _M_X64
#pragma comment(lib,"../../x64/Release/XEngine_InfoReport.lib")
#pragma comment(lib,"../../x64/Release/XEngine_APIModuleIPMac.lib")
#pragma comment(lib,"../../x64/Release/XEngine_APIModulePhone.lib")
#pragma comment(lib,"../../x64/Release/XEngine_ModuleConfigure.lib")
#pragma comment(lib,"../../x64/Release/XEngine_ModuleDatabase.lib")
#pragma comment(lib,"../../x64/Release/XEngine_ModuleProtocol.lib")
#pragma comment(lib,"../../x64/Release/XEngine_ModuleSystem.lib")
#pragma comment(lib,"../../x64/Release/XEngine_ModuleHelp.lib")
#pragma comment(lib,"../../x64/Release/XEngine_ModulePlugin.lib")
#elif _M_ARM64
#pragma comment(lib,"../../ARM64/Release/XEngine_InfoReport.lib")
#pragma comment(lib,"../../ARM64/Release/XEngine_APIModuleIPMac.lib")
#pragma comment(lib,"../../ARM64/Release/XEngine_APIModulePhone.lib")
#pragma comment(lib,"../../ARM64/Release/XEngine_ModuleConfigure.lib")
#pragma comment(lib,"../../ARM64/Release/XEngine_ModuleDatabase.lib")
#pragma comment(lib,"../../ARM64/Release/XEngine_ModuleProtocol.lib")
#pragma comment(lib,"../../ARM64/Release/XEngine_ModuleSystem.lib")
#pragma comment(lib,"../../ARM64/Release/XEngine_ModuleHelp.lib")
#pragma comment(lib,"../../ARM64/Release/XEngine_ModulePlugin.lib")
#elif _M_IX86
#pragma comment(lib,"../../Release/XEngine_InfoReport.lib")
#pragma comment(lib,"../../Release/XEngine_APIModuleIPMac.lib")
#pragma comment(lib,"../../Release/XEngine_APIModulePhone.lib")
#pragma comment(lib,"../../Release/XEngine_ModuleConfigure.lib")
#pragma comment(lib,"../../Release/XEngine_ModuleDatabase.lib")
#pragma comment(lib,"../../Release/XEngine_ModuleProtocol.lib")
#pragma comment(lib,"../../Release/XEngine_ModuleSystem.lib")
#pragma comment(lib,"../../Release/XEngine_ModuleHelp.lib")
#pragma comment(lib,"../../Release/XEngine_ModulePlugin.lib")
#endif
#endif
#endif