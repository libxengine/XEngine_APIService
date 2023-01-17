#include "pch.h"
#include "ModulePlugin_APIPhone/ModulePlugin_APIPhone.h"
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
BOOL Phone_IsErrorOccur = FALSE;
DWORD Phone_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModulePlugin_APIPhone m_PluginPhone;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD PluginCore_GetLastError()
{
	return Phone_dwErrorCode;
}
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
extern "C" BOOL PluginCore_Init(LPVOID lParam)
{
	return m_PluginPhone.PluginCore_Init(lParam);
}
extern "C" void PluginCore_UnInit()
{
	m_PluginPhone.PluginCore_UnInit();
}
extern "C" BOOL PluginCore_Call(TCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBuffer, int nMsgLen)
{
	return m_PluginPhone.PluginCore_Call(pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen, lpszMsgBuffer, nMsgLen);
}