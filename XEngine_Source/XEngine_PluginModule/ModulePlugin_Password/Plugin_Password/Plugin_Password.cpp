#include "pch.h"
#include "Plugin_Password.h"
/********************************************************************
//    Created:     2022/04/21  15:52:19
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Password\Plugin_Password\Plugin_Password.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Password\Plugin_Password
//    File Base:   Plugin_Password
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     密码生成类
//    History:
*********************************************************************/
CPlugin_Password::CPlugin_Password()
{
}
CPlugin_Password::~CPlugin_Password()
{
}
//////////////////////////////////////////////////////////////////////////
//                       公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：PluginCore_Init
函数功能：初始化插件模块
 参数.一：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：N
  意思：自定义参数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CPlugin_Password::PluginCore_Init(LPVOID lParam)
{
	Pass_IsErrorOccur = FALSE;

    return TRUE;
}
/********************************************************************
函数名称：PluginCore_UnInit
函数功能：卸载插件
返回值
  类型：无
  意思：
备注：
*********************************************************************/
void CPlugin_Password::PluginCore_UnInit()
{
	Pass_IsErrorOccur = FALSE;
}
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CPlugin_Password::PluginCore_Call(TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBuffer, int nMsgLen)
{
	Pass_IsErrorOccur = FALSE;

	if ((NULL == pInt_HTTPCode) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		Pass_IsErrorOccur = TRUE;
		Pass_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PASS_PARAMENT;
		return FALSE;
	}
	TCHAR tszKeyName[128];
	TCHAR tszParamType[128];
	TCHAR tszParamLength[128];
	TCHAR tszPassword[MAX_PATH];
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	memset(tszKeyName, '\0', sizeof(tszKeyName));
	memset(tszParamType, '\0', sizeof(tszParamType));
	memset(tszParamLength, '\0', sizeof(tszParamLength));
	memset(tszPassword, '\0', sizeof(tszPassword));

	BaseLib_OperatorString_GetKeyValue((*pppHDRList)[1], "=", tszKeyName, tszParamType);
	BaseLib_OperatorString_GetKeyValue((*pppHDRList)[2], "=", tszKeyName, tszParamLength);
	Plugin_Password_Creator(tszParamType, tszParamLength, tszPassword);

	st_JsonObject["tszParamType"] = tszParamType;
	st_JsonObject["tszParamLength"] = tszParamLength;
	st_JsonObject["tszPassword"] = tszPassword;
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_HTTPCode = 200;
	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////
BOOL CPlugin_Password::Plugin_Password_Creator(LPCTSTR lpszPassType, LPCTSTR lpszLength, TCHAR* ptszPassStr)
{
	Pass_IsErrorOccur = FALSE;

	int nType = _ttoi(lpszPassType);
	int nLen = _ttoi(lpszLength);
	TCHAR tszPassBuffer[MAX_PATH];

	memset(tszPassBuffer, '\0', MAX_PATH);
	if (0 == nType)
	{
		BaseLib_OperatorHandle_CreateStr(tszPassBuffer, nLen);
	}
	else if (1 == nType)
	{
		for (int i = 0; i < nLen; i++)
		{
			_stprintf(&tszPassBuffer[i], _T("%d"), rand() % 9);
		}
	}
	else if (2 == nType)
	{
		for (int i = 0; i < nLen; i++)
		{
			_stprintf(&tszPassBuffer[i], _T("%c"), (rand() % 26) + 65);
		}
	}
	return TRUE;
}