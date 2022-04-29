#include "pch.h"
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
BOOL Zodiac_IsErrorOccur = FALSE;
DWORD Zodiac_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CPlugin_Zodiac m_PluginZodiac;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD PluginCore_GetLastError()
{
	return Zodiac_dwErrorCode;
}
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
extern "C" BOOL PluginCore_Init(LPVOID lParam)
{
	return m_PluginZodiac.PluginCore_Init(lParam);
}
extern "C" BOOL PluginCore_UnInit()
{
	return m_PluginZodiac.PluginCore_UnInit();
}
extern "C" BOOL PluginCore_Call(TCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR * ptszMsgBuffer, int* pInt_MsgLen)
{
	return m_PluginZodiac.PluginCore_Call(pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen);
}