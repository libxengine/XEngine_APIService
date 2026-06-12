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
bool Meter_IsErrorOccur = false;
XLONG Meter_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CPlugin_Meter m_PluginMeter;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG PluginCore_GetLastError()
{
	return Meter_dwErrorCode;
}
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
extern "C" bool PluginCore_Init(XENGINE_PLUGINPARAM *pSt_PluginParameter)
{
	return m_PluginMeter.PluginCore_Init(pSt_PluginParameter);
}
extern "C" void PluginCore_UnInit()
{
	m_PluginMeter.PluginCore_UnInit();
}
extern "C" int PluginCore_RegisterType()
{
	return m_PluginMeter.PluginCore_RegisterType();
}
extern "C" void PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc)
{
	return m_PluginMeter.PluginCore_GetInfo(ptszPluginName, ptszPluginVersion, ptszPluginAuthor, ptszPluginDesc);
}
extern "C" bool PluginCore_Call(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer, int nMsgLen, XCHAR*** pppInputParameters, int nInputPCount, XCHAR*** pppOutputParameters, int* pInt_OutputPCount)
{
	return m_PluginMeter.PluginCore_Call(ptszMsgBuffer, pInt_MsgLen, lpszMsgBufer, nMsgLen, pppInputParameters, nInputPCount, pppOutputParameters, pInt_OutputPCount);
}