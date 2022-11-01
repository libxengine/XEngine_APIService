#include "pch.h"
#include "Plugin_Meter/Plugin_Meter.h"
/********************************************************************
//    Created:     2022/11/01  13:56:17
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Meter\pch.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Meter
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
BOOL Meter_IsErrorOccur = FALSE;
DWORD Meter_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CPlugin_Meter m_PluginMeter;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD PluginCore_GetLastError()
{
	return Meter_dwErrorCode;
}
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
extern "C" BOOL PluginCore_Init(LPVOID lParam)
{
	return m_PluginMeter.PluginCore_Init(lParam);
}
extern "C" BOOL PluginCore_UnInit()
{
	return m_PluginMeter.PluginCore_UnInit();
}
extern "C" BOOL PluginCore_Call(TCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBuffer, int nMsgLen)
{
	return m_PluginMeter.PluginCore_Call(pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen, lpszMsgBuffer, nMsgLen);
}