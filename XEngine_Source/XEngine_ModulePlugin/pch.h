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
#include <lua.hpp>
#else
#include <dlfcn.h>

#ifdef __linux__
#ifdef _CENTOS
#include <lua/lua.hpp>
#else
#include <lua5.3/lua.hpp>
#endif
#else
#include <lua/lua.hpp>
#endif
#endif

#endif //PCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <list>
#include <thread>
#include <memory>
#include <shared_mutex>
#include <unordered_map>
using namespace std;
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include "ModulePlugin_Define.h"
#include "ModulePlugin_Error.h"
/********************************************************************
//    Created:     2022/04/20  16:17:24
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\pch.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin
//    File Base:   pch
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     插件核心公有头文件
//    History:
*********************************************************************/
extern bool ModulePlugin_IsErrorOccur;
extern XLONG ModulePlugin_dwErrorCode;

#ifdef _MSC_BUILD
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#endif