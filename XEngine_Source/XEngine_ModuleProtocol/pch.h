// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

#ifdef _MSC_BUILD
// 添加要在此处预编译的标头
#include "framework.h"
#include <tchar.h>
#else
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#endif
#endif //PCH_H
#include <stdio.h>
#include <errno.h>
#include <list>
#include <unordered_map>
#include <json/json.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_NetHelp/APIAddr_Define.h>
#include <XEngine_Include/XEngine_NetHelp/APIAddr_Error.h>
#include <XEngine_Include/XEngine_SystemSdk/ProcFile_Define.h>
#include <XEngine_Include/XEngine_AVCodec/AVCollect_Define.h>
#include <XEngine_Include/XEngine_AVCodec/VideoCodec_Define.h>
#include <XEngine_Include/XEngine_AVCodec/AVHelp_Define.h>
#include "../XEngine_DependLibrary/XEngine_IPMacData/XEngine_Source/XIPMac_CommHdr.h"
#include "../XEngine_DependLibrary/XEngine_PhoneData/Source/XPhone_CommHdr.h"
using namespace std;
#include "../XEngine_UserProtocol.h"
#include "ModuleProtocol_Define.h"
#include "ModuleProtocol_Error.h"
/********************************************************************
//    Created:     2022/02/28  14:11:33
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol\pch.h
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol
//    File Base:   pch
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     公用头文件
//    History:
*********************************************************************/
extern bool ModuleProtocol_IsErrorOccur;
extern XLONG ModuleProtocol_dwErrorCode;


#ifdef _MSC_BUILD
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_NetHelp/NetHelp_APIAddr")
#ifdef _DEBUG
#ifdef _M_X64
#pragma comment(lib,"../x64/Debug/jsoncpp")
#elif _M_ARM64
#pragma comment(lib,"../ARM64/Debug/jsoncpp")
#elif _M_IX86
#pragma comment(lib,"../Debug/jsoncpp")
#endif
#else
#ifdef _M_X64
#pragma comment(lib,"../x64/Release/jsoncpp")
#elif _M_ARM64
#pragma comment(lib,"../ARM64/Release/jsoncpp")
#elif _M_IX86
#pragma comment(lib,"../Release/jsoncpp")
#endif
#endif
#endif