#include "pch.h"
#include "ModulePlugin_APIPhone.h"
/********************************************************************
//    Created:     2023/01/09  17:13:39
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\ModulePlugin_APIPhone\ModulePlugin_APIPhone.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\ModulePlugin_APIPhone
//    File Base:   ModulePlugin_APIPhone
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     电话接口类
//    History:
*********************************************************************/
CModulePlugin_APIPhone::CModulePlugin_APIPhone()
{
}
CModulePlugin_APIPhone::~CModulePlugin_APIPhone()
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
bool CModulePlugin_APIPhone::PluginCore_Init(XPVOID lParam)
{
	Phone_IsErrorOccur = false;

	if (!m_DBPhone.ModuleDatabase_Phone_Init(_X("./XEngine_DBFile/phone.dat")))
	{
		return false;
	}
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
void CModulePlugin_APIPhone::PluginCore_UnInit()
{
	Phone_IsErrorOccur = false;

	m_DBPhone.ModuleDatabase_Phone_Destory();
}
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_APIPhone::PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	Phone_IsErrorOccur = false;

	if ((NULL == pInt_HTTPCode) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		Phone_IsErrorOccur = true;
		Phone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PHONE_PARAMENT;
		return false;
	}
	XCHAR tszKeyName[128];
	XCHAR tszKeyValue[128];
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;
	XENGINE_PHONEINFO st_PhoneInfo;

	memset(tszKeyName, '\0', sizeof(tszKeyName));
	memset(tszKeyValue, '\0', sizeof(tszKeyValue));
	memset(&st_PhoneInfo, '\0', sizeof(XENGINE_PHONEINFO));

	BaseLib_OperatorString_GetKeyValue((*pppHDRList)[1], "=", tszKeyName, tszKeyValue);

	st_PhoneInfo.nPhoneNumber = _ttxoll(tszKeyValue);
	if (!m_DBPhone.ModuleDatabase_Phone_Query(tszKeyValue, &st_PhoneInfo))
	{
		return false;
	}
	st_JsonObject["nPhoneNumber"] = (Json::Value::Int64)st_PhoneInfo.nPhoneNumber;
	st_JsonObject["tszProvincer"] = st_PhoneInfo.tszProvincer;
	st_JsonObject["tszCity"] = st_PhoneInfo.tszCity;
	st_JsonObject["nZipCode"] = st_PhoneInfo.nZipCode;
	st_JsonObject["nAreaCode"] = st_PhoneInfo.nAreaCode;

	st_JsonRoot["data"] = st_JsonObject;
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_HTTPCode = 200;
	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}