﻿#include "pch.h"
#include "Plugin_Password/Plugin_Password.h"
/********************************************************************
//    Created:     2022/04/21  15:52:56
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Password\pch.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Password
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
bool Pass_IsErrorOccur = false;
XLONG Pass_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CPlugin_Password m_PluginPass;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG PluginCore_GetLastError()
{
	return Pass_dwErrorCode;
}
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
extern "C" bool PluginCore_Init(XENGINE_PLUGINPARAM *pSt_PluginParameter)
{
	return m_PluginPass.PluginCore_Init(pSt_PluginParameter);
}
extern "C" void PluginCore_UnInit()
{
	m_PluginPass.PluginCore_UnInit();
}
extern "C" void PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc)
{
	return m_PluginPass.PluginCore_GetInfo(ptszPluginName, ptszPluginVersion, ptszPluginAuthor, ptszPluginDesc);
}
extern "C" bool PluginCore_Call(XCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	return m_PluginPass.PluginCore_Call(pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen, lpszMsgBuffer, nMsgLen);
}