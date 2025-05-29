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
bool CPlugin_Password::PluginCore_Init(XPVOID lParam)
{
	Pass_IsErrorOccur = false;

    return true;
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
	Pass_IsErrorOccur = false;
}
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CPlugin_Password::PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	Pass_IsErrorOccur = false;

	if ((NULL == pInt_HTTPCode) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		Pass_IsErrorOccur = true;
		Pass_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PASS_PARAMENT;
		return false;
	}
	XCHAR tszKeyName[128];
	XCHAR tszParamType[128];
	XCHAR tszParamLength[128];
	XCHAR tszPassword[XPATH_MAX];
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	memset(tszKeyName, '\0', sizeof(tszKeyName));
	memset(tszParamType, '\0', sizeof(tszParamType));
	memset(tszParamLength, '\0', sizeof(tszParamLength));
	memset(tszPassword, '\0', sizeof(tszPassword));

	BaseLib_String_GetKeyValue((*pppHDRList)[1], "=", tszKeyName, tszParamType);
	BaseLib_String_GetKeyValue((*pppHDRList)[2], "=", tszKeyName, tszParamLength);
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
	return true;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////
bool CPlugin_Password::Plugin_Password_Creator(LPCXSTR lpszPassType, LPCXSTR lpszLength, XCHAR* ptszPassStr)
{
	Pass_IsErrorOccur = false;

	int nType = _ttxoi(lpszPassType);
	int nLen = _ttxoi(lpszLength);
	if (0 == nType)
	{
		BaseLib_Handle_CreateStr(ptszPassStr, nLen);
	}
	else if (1 == nType)
	{
		BaseLib_Handle_CreateStr(ptszPassStr, nLen, 1);
	}
	else if (2 == nType)
	{
		BaseLib_Handle_CreateStr(ptszPassStr, nLen, 2);
	}
	return true;
}