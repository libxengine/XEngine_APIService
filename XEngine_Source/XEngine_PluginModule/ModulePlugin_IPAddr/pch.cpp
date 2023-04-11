#include "pch.h"
#include "ModulePlugin_Interface/ModulePlugin_Interface.h"
/********************************************************************
//    Created:     2023/01/10  11:24:04
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_IPAddr\pch.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_IPAddr
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
XBOOL IPAddr_IsErrorOccur = XFALSE;
XLONG IPAddr_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModulePlugin_Interface m_PluginIPAddr;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG PluginCore_GetLastError()
{
	return IPAddr_dwErrorCode;
}
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
extern "C" XBOOL PluginCore_Init(XPVOID lParam)
{
	return m_PluginIPAddr.PluginCore_Init(lParam);
}
extern "C" void PluginCore_UnInit()
{
	m_PluginIPAddr.PluginCore_UnInit();
}
extern "C" XBOOL PluginCore_Call(XCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	return m_PluginIPAddr.PluginCore_Call(pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen, lpszMsgBuffer, nMsgLen);
}