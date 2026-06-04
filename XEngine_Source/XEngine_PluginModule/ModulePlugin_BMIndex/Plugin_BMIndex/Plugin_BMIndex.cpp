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
 参数.一：pSt_PluginParameter
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入插件初始化信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CPlugin_BMIndex::PluginCore_Init(XENGINE_PLUGINPARAM *pSt_PluginParameter)
{
	BMIndex_IsErrorOccur = false;
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
void CPlugin_BMIndex::PluginCore_UnInit()
{
	BMIndex_IsErrorOccur = false;
}
/********************************************************************
函数名称：PluginCore_RegisterType
函数功能：注册类型
返回值
  类型：整数型
  意思：返回注册类型
备注：
*********************************************************************/
int CPlugin_BMIndex::PluginCore_RegisterType()
{
	BMIndex_IsErrorOccur = false;
	return 0;
}
/********************************************************************
函数名称：PluginCore_GetInfo
函数功能：获取插件基础信息函数
 参数.一：ptszPluginName
  In/Out：Out
  类型：字符指针
  可空：N
  意思：处理名称
 参数.二：ptszPluginVersion
  In/Out：Out
  类型：字符指针
  可空：N
  意思：版本号.使用x.x.x.x 格式
 参数.三：ptszPluginAuthor
  In/Out：Out
  类型：字符指针
  可空：N
  意思：作者
 参数.四：ptszPluginDesc
  In/Out：Out
  类型：字符指针
  可空：N
  意思：插件描述
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
void CPlugin_BMIndex::PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc)
{
	BMIndex_IsErrorOccur = false;

	_tcsxcpy(ptszPluginName, "bmindex");
	_tcsxcpy(ptszPluginVersion, "1.0.0.1001");
	_tcsxcpy(ptszPluginAuthor, "xengine");
	_tcsxcpy(ptszPluginDesc, "null");
}
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CPlugin_BMIndex::PluginCore_Call(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer, int nMsgLen, XCHAR*** pppInputParameters, int nInputPCount, XCHAR*** pppOutputParameters, int* pInt_OutputPCount)
{
	BMIndex_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		BMIndex_IsErrorOccur = true;
		BMIndex_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_BMINDEX_PARAMENT;
		return false;
	}
	XCHAR tszKeyName[128] = {};
	XCHAR tszParam1[128] = {};
	XCHAR tszParam2[128] = {};

	BaseLib_String_GetKeyValue((*pppInputParameters)[1], "=", tszKeyName, tszParam1);
	BaseLib_String_GetKeyValue((*pppInputParameters)[2], "=", tszKeyName, tszParam2);

	Plugin_Timezone_BMIndex(tszParam1, tszParam2, ptszMsgBuffer, pInt_MsgLen);
	
	return true;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////
bool CPlugin_BMIndex::Plugin_Timezone_BMIndex(LPCXSTR lpszHigh, LPCXSTR lpszWeight, XCHAR* ptszMsgBufer, int* pInt_Len)
{
	BMIndex_IsErrorOccur = false;

	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	double dlHigh = _ttxof(lpszHigh);
	double dlWeight = _ttxof(lpszWeight);
	double dlValue = dlWeight / (dlHigh * dlHigh);
	if (dlValue < 18.5)
	{
		st_JsonObject["Result"] = "Underweight";	
	}
	else if ((dlValue >= 18.5) && (dlValue <= 23.9))
	{
		st_JsonObject["Result"] = "Normal";
	}
	else if ((dlValue >= 24) && (dlValue <= 27.9))
	{
		st_JsonObject["Result"] = "Overweight";
	}
	else if ((dlValue >= 28) && (dlValue < 30))
	{
		st_JsonObject["Result"] = "Obese";
	}
	else if ((dlValue >= 30) && (dlValue < 40))
	{
		st_JsonObject["Result"] = "Severely obese";
	}
	else if (dlValue >= 40)
	{
		st_JsonObject["Result"] = "Morbidly obese";
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
	return true;
}