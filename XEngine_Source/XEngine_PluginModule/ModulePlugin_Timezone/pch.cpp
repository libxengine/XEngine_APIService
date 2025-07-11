﻿#include "pch.h"
#include "Plugin_Timezone/Plugin_Timezone.h"
/********************************************************************
//    Created:     2022/07/20  11:44:22
//    File Name:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Timezone\pch.cpp
//    File Path:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Timezone
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
bool Timezone_IsErrorOccur = false;
XLONG Timezone_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CPlugin_Timezone m_PluginTimes;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG PluginCore_GetLastError()
{
	return Timezone_dwErrorCode;
}
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
extern "C" bool PluginCore_Init(XENGINE_PLUGINPARAM *pSt_PluginParameter)
{
	return m_PluginTimes.PluginCore_Init(pSt_PluginParameter);
}
extern "C" void PluginCore_UnInit()
{
	m_PluginTimes.PluginCore_UnInit();
}
extern "C" void PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc)
{
	return m_PluginTimes.PluginCore_GetInfo(ptszPluginName, ptszPluginVersion, ptszPluginAuthor, ptszPluginDesc);
}
extern "C" bool PluginCore_Call(XCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	return m_PluginTimes.PluginCore_Call(pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen, lpszMsgBuffer, nMsgLen);
}