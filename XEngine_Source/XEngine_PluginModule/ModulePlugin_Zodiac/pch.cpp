﻿#include "pch.h"
#include "Plugin_Zodiac/Plugin_Zodiac.h"
/********************************************************************
//    Created:     2022/04/21  10:46:38
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Zodiac\pch.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Zodiac
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
bool Zodiac_IsErrorOccur = false;
XLONG Zodiac_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CPlugin_Zodiac m_PluginZodiac;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG PluginCore_GetLastError()
{
	return Zodiac_dwErrorCode;
}
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
extern "C" bool PluginCore_Init(XENGINE_PLUGINPARAM *pSt_PluginParameter)
{
	return m_PluginZodiac.PluginCore_Init(pSt_PluginParameter);
}
extern "C" void PluginCore_UnInit()
{
	m_PluginZodiac.PluginCore_UnInit();
}
extern "C" void PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc)
{
	return m_PluginZodiac.PluginCore_GetInfo(ptszPluginName, ptszPluginVersion, ptszPluginAuthor, ptszPluginDesc);
}
extern "C" bool PluginCore_Call(XCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	return m_PluginZodiac.PluginCore_Call(pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen, lpszMsgBuffer, nMsgLen);
}