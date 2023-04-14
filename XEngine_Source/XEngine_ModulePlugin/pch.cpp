#include "pch.h"
#include "ModulePlugin_LibCore/ModulePlugin_LibCore.h"
#include "ModulePlugin_LuaCore/ModulePlugin_LuaCore.h"
#include "ModulePlugin_Loader/ModulePlugin_Loader.h"
/********************************************************************
//    Created:     2022/04/20  16:39:27
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\pch.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     插件核心导出函数实现
//    History:
*********************************************************************/
XBOOL ModulePlugin_IsErrorOccur = FALSE;
XLONG ModulePlugin_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModulePlugin_LibCore m_PluginLib;
CModulePlugin_LuaCore m_PluginLua;
CModulePlugin_Loader m_PluginLoader;
//////////////////////////////////////////////////////////////////////////
//                       导出函数实现
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModulePlugin_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return ModulePlugin_dwErrorCode;
}
/*********************************************************************************
*                        插件框架导出函数定义                                       *
*********************************************************************************/
extern "C" XBOOL ModulePlugin_LibCore_Init()
{
	return m_PluginLib.ModulePlugin_LibCore_Init();
}
extern "C" XBOOL ModulePlugin_LibCore_Push(XNETHANDLE * pxhModule, LPCXSTR lpszPluginFile, XPVOID lParam)
{
	return m_PluginLib.ModulePlugin_LibCore_Push(pxhModule, lpszPluginFile, lParam);
}
extern "C" XBOOL ModulePlugin_LibCore_Exec(XNETHANDLE xhModule, XCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer, int nMsgLen)
{
	return m_PluginLib.ModulePlugin_LibCore_Exec(xhModule, pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen);
}
extern "C" XBOOL ModulePlugin_LibCore_Destroy()
{
	return m_PluginLib.ModulePlugin_LibCore_Destroy();
}
/*********************************************************************************
*                        LUA插件框架导出函数定义                                 *
*********************************************************************************/
extern "C" XBOOL ModulePlugin_LuaCore_Init()
{
	return m_PluginLua.ModulePlugin_LuaCore_Init();
}
extern "C" XBOOL ModulePlugin_LuaCore_Push(XNETHANDLE * pxhModule, LPCXSTR lpszPluginFile, XPVOID lParam)
{
	return m_PluginLua.ModulePlugin_LuaCore_Push(pxhModule, lpszPluginFile, lParam);
}
extern "C" XBOOL ModulePlugin_LuaCore_Exec(XNETHANDLE xhModule, XCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer, int nMsgLen)
{
	return m_PluginLua.ModulePlugin_LuaCore_Exec(xhModule, pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen, lpszMsgBufer, nMsgLen);
}
extern "C" XBOOL ModulePlugin_LuaCore_Destroy()
{
	return m_PluginLua.ModulePlugin_LuaCore_Destroy();
}
/*********************************************************************************
*                        加载器导出函数定义                                      *
*********************************************************************************/
extern "C" XBOOL ModulePlugin_Loader_Insert(LPCXSTR lpszModuleMethod, LPCXSTR lpszModuleName, int nType)
{
	return m_PluginLoader.ModulePlugin_Loader_Insert(lpszModuleMethod, lpszModuleName, nType);
}
extern "C" XBOOL ModulePlugin_Loader_Find(LPCXSTR lpszMethodName, int* pInt_Type)
{
	return m_PluginLoader.ModulePlugin_Loader_Find(lpszMethodName, pInt_Type);
}
extern "C" XBOOL ModulePlugin_Loader_Exec(LPCXSTR lpszMethodName, XCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR * ptszMsgBuffer, int* pInt_MsgLen)
{
	return m_PluginLoader.ModulePlugin_Loader_Exec(lpszMethodName, pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen);
}
extern "C" XBOOL ModulePlugin_Loader_Destory()
{
	return m_PluginLoader.ModulePlugin_Loader_Destory();
}