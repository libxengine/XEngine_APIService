#include "pch.h"
#include "ModuleConfigure_Json/ModuleConfigure_Json.h"
#include "ModuleConfigure_File/ModuleConfigure_File.h"
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
BOOL Config_IsErrorOccur = FALSE;
DWORD Config_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////
CModuleConfigure_Json m_ConfigJson;
CModuleConfigure_File m_ConfigFile;
//////////////////////////////////////////////////////////////////////
//                        导出函数定义
//////////////////////////////////////////////////////////////////////
extern "C" DWORD ModuleConfigure_GetLastError(int* pInt_ErrorCode)
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
extern "C" BOOL ModuleConfigure_Json_File(LPCTSTR lpszConfigFile, XENGINE_SERVICECONFIG * pSt_ServerConfig)
{
	return m_ConfigJson.ModuleConfigure_Json_File(lpszConfigFile, pSt_ServerConfig);
}
extern "C" BOOL ModuleConfigure_Json_OPenccFile(LPCTSTR lpszConfigFile, XENGINE_OPENCCCONFIG * pSt_OPenccConfig)
{
	return m_ConfigJson.ModuleConfigure_Json_OPenccFile(lpszConfigFile, pSt_OPenccConfig);
}
extern "C" BOOL ModuleConfigure_Json_PluginFile(LPCTSTR lpszConfigFile, XENGINE_PLUGINCONFIG * pSt_PluginConfig)
{
	return m_ConfigJson.ModuleConfigure_Json_PluginFile(lpszConfigFile, pSt_PluginConfig);
}
/************************************************************************/
/*                        其他内容读取                                  */
/************************************************************************/
extern "C" BOOL ModuleConfigure_File_OPtion(LPCTSTR lpszConfigFile, XENGINE_OPTIONLIST * pSt_OPtionList)
{
	return m_ConfigFile.ModuleConfigure_File_OPtion(lpszConfigFile, pSt_OPtionList);
}