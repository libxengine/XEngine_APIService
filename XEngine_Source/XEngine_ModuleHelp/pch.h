﻿// pch.h: 这是预编译标头文件。
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
#include <atlconv.h>
#include <WinSock2.h>
#endif
#endif //PCH_H
#include "../XEngine_BuildSwitch.h"
#include <string.h>
#include <errno.h>
#include <thread>
#include <list>
#include <vector>
#include <atomic>
#include <memory>
#include <shared_mutex>
#include <unordered_map>
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/wechat_qrcode.hpp>
#include <qrencode.h>
#endif
using namespace std;
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Client/XClient_Define.h>
#include <XEngine_Include/XEngine_Client/XClient_Error.h>
#include "../XEngine_UserProtocol.h"
#include "ModuleHelp_Define.h"
#include "ModuleHelp_Error.h"
/********************************************************************
//    Created:     2022/03/03  14:01:50
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\pch.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp
//    File Base:   pch
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     公用头文件
//    History:
*********************************************************************/
extern bool ModuleHelp_IsErrorOccur;
extern XLONG ModuleHelp_dwErrorCode;

#ifdef _MSC_BUILD
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_Client/XClient_Socket")
#else
#if __linux__ && !__ANDROID__
#pragma GCC diagnostic ignored "-Wclass-memaccess"
#endif
#endif