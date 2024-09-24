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
#include <io.h>
#include <shlobj.h>
#else
#include <unistd.h>
#endif
#endif //PCH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Define.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Error.h>
#include "ModuleSystem_Define.h"
#include "ModuleSystem_Error.h"
/********************************************************************
//    Created:     2023/09/06  13:52:47
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem\pch.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem
//    File Base:   pch
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     公用头文件
//    History:
*********************************************************************/
extern bool ModuleSystem_IsErrorOccur;
extern XLONG ModuleSystem_dwErrorCode;

#ifdef _MSC_BUILD
#pragma comment(lib, "shell32.lib")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_SystemSdk/XEngine_SystemApi")
#endif