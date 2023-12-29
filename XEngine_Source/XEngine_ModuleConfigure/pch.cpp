﻿#include "pch.h"
#include "ModuleConfigure_Json/ModuleConfigure_Json.h"
/********************************************************************
//    Created:     2021/12/02  16:20:26
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure\pch.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出函数实现
//    History:
*********************************************************************/
bool Config_IsErrorOccur = false;
XLONG Config_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////
CModuleConfigure_Json m_ConfigJson;
//////////////////////////////////////////////////////////////////////
//                        导出函数定义
//////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleConfigure_GetLastError(int* pInt_ErrorCode)
{
	if (pInt_ErrorCode != NULL)
	{
		*pInt_ErrorCode = errno;
	}
	return Config_dwErrorCode;
}
/************************************************************************/
/*                        配置文件读取                                  */
/************************************************************************/
extern "C" bool ModuleConfigure_Json_File(LPCXSTR lpszConfigFile, XENGINE_SERVICECONFIG * pSt_ServerConfig)
{
	return m_ConfigJson.ModuleConfigure_Json_File(lpszConfigFile, pSt_ServerConfig);
}
extern "C" bool ModuleConfigure_Json_QRCodeFile(LPCXSTR lpszConfigFile, XENGINE_QRCODECONFIG * pSt_QRCodeConfig)
{
	return m_ConfigJson.ModuleConfigure_Json_QRCodeFile(lpszConfigFile, pSt_QRCodeConfig);
}
extern "C" bool ModuleConfigure_Json_PluginFile(LPCXSTR lpszConfigFile, XENGINE_PLUGINCONFIG * pSt_PluginConfig)
{
	return m_ConfigJson.ModuleConfigure_Json_PluginFile(lpszConfigFile, pSt_PluginConfig);
}
extern "C" bool ModuleConfigure_Json_DeamonList(LPCXSTR lpszConfigFile, XENGINE_DEAMONAPPLIST * pSt_AppConfig)
{
	return m_ConfigJson.ModuleConfigure_Json_DeamonList(lpszConfigFile, pSt_AppConfig);
}