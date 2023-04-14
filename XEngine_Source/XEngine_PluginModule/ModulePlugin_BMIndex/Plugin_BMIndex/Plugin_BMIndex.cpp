#include "pch.h"
#include "Plugin_BMIndex.h"
/********************************************************************
//    Created:     2022/07/20  16:37:26
//    File Name:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_BMIndex\Plugin_BMIndex\Plugin_BMIndex.cpp
//    File Path:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_BMIndex\Plugin_BMIndex
//    File Base:   Plugin_BMIndex
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     标准身高体重
//    History:
*********************************************************************/
CPlugin_BMIndex::CPlugin_BMIndex()
{
}
CPlugin_BMIndex::~CPlugin_BMIndex()
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
XBOOL CPlugin_BMIndex::PluginCore_Init(XPVOID lParam)
{
	BMIndex_IsErrorOccur = FALSE;

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
void CPlugin_BMIndex::PluginCore_UnInit()
{
	BMIndex_IsErrorOccur = FALSE;
}
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CPlugin_BMIndex::PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	BMIndex_IsErrorOccur = FALSE;

	if ((NULL == pInt_HTTPCode) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		BMIndex_IsErrorOccur = TRUE;
		BMIndex_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_BMINDEX_PARAMENT;
		return FALSE;
	}
	XCHAR tszKeyName[128];
	XCHAR tszParamHigh[128];
	XCHAR tszParamWeight[128];

	memset(tszKeyName, '\0', sizeof(tszKeyName));
	memset(tszParamHigh, '\0', sizeof(tszParamHigh));
	memset(tszParamWeight, '\0', sizeof(tszParamWeight));

	BaseLib_OperatorString_GetKeyValue((*pppHDRList)[1], "=", tszKeyName, tszParamHigh);
	BaseLib_OperatorString_GetKeyValue((*pppHDRList)[2], "=", tszKeyName, tszParamWeight);
	Plugin_Timezone_BMIndex(tszParamHigh, tszParamWeight, ptszMsgBuffer, pInt_MsgLen);
	*pInt_HTTPCode = 200;
	
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////
XBOOL CPlugin_BMIndex::Plugin_Timezone_BMIndex(LPCXSTR lpszHigh, LPCXSTR lpszWeight, XCHAR* ptszMsgBufer, int* pInt_Len)
{
	BMIndex_IsErrorOccur = FALSE;

	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	double dlHigh = _ttxof(lpszHigh);
	double dlWeight = _ttxof(lpszWeight);
	double dlValue = dlWeight / (dlHigh * dlHigh);
	if (dlValue < 18.5)
	{
		st_JsonObject["Result"] = "偏瘦";
	}
	else if ((dlValue >= 18.5) && (dlValue <= 23.9))
	{
		st_JsonObject["Result"] = "正常";
	}
	else if ((dlValue >= 24) && (dlValue <= 27.9))
	{
		st_JsonObject["Result"] = "超重";
	}
	else if ((dlValue >= 28) && (dlValue < 30))
	{
		st_JsonObject["Result"] = "肥胖";
	}
	else if ((dlValue >= 30) && (dlValue < 40))
	{
		st_JsonObject["Result"] = "重度肥胖";
	}
	else if (dlValue >= 40)
	{
		st_JsonObject["Result"] = "极重度肥胖";
	}
	st_JsonObject["flValue"] = dlValue;
	st_JsonObject["flWeight"] = dlWeight;
	st_JsonObject["flHigh"] = dlHigh;

	st_JsonRoot["data"] = st_JsonObject;
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_Len = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBufer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_Len);
	return TRUE;
}