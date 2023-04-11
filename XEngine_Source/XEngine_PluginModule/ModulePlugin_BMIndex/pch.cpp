#include "pch.h"
#include "Plugin_BMIndex/Plugin_BMIndex.h"
/********************************************************************
//    Created:     2022/07/20  19:18:15
//    File Name:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_BMIndex\pch.cpp
//    File Path:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_BMIndex
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
XBOOL BMIndex_IsErrorOccur = XFALSE;
DWORD BMIndex_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CPlugin_BMIndex m_PluginBMIndex;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD PluginCore_GetLastError()
{
	return BMIndex_dwErrorCode;
}
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
extern "C" XBOOL PluginCore_Init(XPVOID lParam)
{
	return m_PluginBMIndex.PluginCore_Init(lParam);
}
extern "C" void PluginCore_UnInit()
{
	m_PluginBMIndex.PluginCore_UnInit();
}
extern "C" XBOOL PluginCore_Call(XCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	return m_PluginBMIndex.PluginCore_Call(pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen, lpszMsgBuffer, nMsgLen);
}