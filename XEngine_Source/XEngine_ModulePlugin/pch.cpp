#include "pch.h"
#include "ModulePlugin_Core/ModulePlugin_Core.h"
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
BOOL ModulePlugin_IsErrorOccur = FALSE;
DWORD ModulePlugin_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModulePlugin_Core m_PluginCore;
CModulePlugin_Loader m_PluginLoader;
//////////////////////////////////////////////////////////////////////////
//                       导出函数实现
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModulePlugin_GetLastError(int* pInt_SysError)
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
extern "C" BOOL ModulePlugin_Core_Init()
{
	return m_PluginCore.ModulePlugin_Core_Init();
}
extern "C" BOOL ModulePlugin_Core_Push(XNETHANDLE * pxhModule, LPCTSTR lpszPluginFile, LPVOID lParam)
{
	return m_PluginCore.ModulePlugin_Core_Push(pxhModule, lpszPluginFile, lParam);
}
extern "C" BOOL ModulePlugin_Core_Exec(XNETHANDLE xhModule, TCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBufer, int nMsgLen)
{
	return m_PluginCore.ModulePlugin_Core_Exec(xhModule, pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen);
}
extern "C" BOOL ModulePlugin_Core_Destroy()
{
	return m_PluginCore.ModulePlugin_Core_Destroy();
}
/*********************************************************************************
*                        加载器导出函数定义                                      *
*********************************************************************************/
extern "C" BOOL ModulePlugin_Loader_Insert(LPCTSTR lpszModuleMethod, LPCTSTR lpszModuleName)
{
	return m_PluginLoader.ModulePlugin_Loader_Insert(lpszModuleMethod, lpszModuleName);
}
extern "C" BOOL ModulePlugin_Loader_Find(LPCTSTR lpszMethodName)
{
	return m_PluginLoader.ModulePlugin_Loader_Find(lpszMethodName);
}
extern "C" BOOL ModulePlugin_Loader_Exec(LPCTSTR lpszMethodName, TCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR * ptszMsgBuffer, int* pInt_MsgLen)
{
	return m_PluginLoader.ModulePlugin_Loader_Exec(lpszMethodName, pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen);
}
extern "C" BOOL ModulePlugin_Loader_Destory()
{
	return m_PluginLoader.ModulePlugin_Loader_Destory();
}