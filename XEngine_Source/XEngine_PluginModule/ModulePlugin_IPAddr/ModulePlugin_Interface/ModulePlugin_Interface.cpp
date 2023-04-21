#include "pch.h"
#include "ModulePlugin_Interface.h"
/********************************************************************
//    Created:     2023/01/10  11:09:33
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_IPAddr\ModulePlugin_Interface\ModulePlugin_Interface.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_IPAddr\ModulePlugin_Interface
//    File Base:   ModulePlugin_Interface
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     IP地址类
//    History:
*********************************************************************/
CModulePlugin_Interface::CModulePlugin_Interface()
{
}
CModulePlugin_Interface::~CModulePlugin_Interface()
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
bool CModulePlugin_Interface::PluginCore_Init(XPVOID lParam)
{
	IPAddr_IsErrorOccur = false;

	const char* db_path = "./XEngine_DBFile/ip2region.xdb";
	// 1、从 db_path 初始化 xdb 查询对象
	int err = xdb_new_with_file_only(&st_DBSearch, db_path);
	if (err != 0) 
	{
		printf("failed to create xdb searcher from `%s` with errno=%d\n", db_path, err);
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
void CModulePlugin_Interface::PluginCore_UnInit()
{
	IPAddr_IsErrorOccur = false;
	xdb_close(&st_DBSearch);
}
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_Interface::PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	IPAddr_IsErrorOccur = false;

	if ((NULL == pInt_HTTPCode) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		IPAddr_IsErrorOccur = true;
		IPAddr_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_IPADDR_PARAMENT;
		return false;
	}
	XCHAR tszKeyName[128];
	XCHAR tszMsgBuffer[128];
	XENGINE_IPADDRINFO st_IPAddr;
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	memset(tszKeyName, '\0', sizeof(tszKeyName));
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(&st_IPAddr, '\0', sizeof(XENGINE_IPADDRINFO));

	BaseLib_OperatorString_GetKeyValue((*pppHDRList)[1], "=", tszKeyName, st_IPAddr.tszIPAddr);
	if (0 != xdb_search_by_string(&st_DBSearch, st_IPAddr.tszIPAddr, tszMsgBuffer, sizeof(tszMsgBuffer)))
	{
		IPAddr_IsErrorOccur = true;
		IPAddr_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_IPADDR_NOTFOUND;
		return false;
	}
	//中国|0|内蒙古|通辽市|联通
	_stxscanf(tszMsgBuffer, _X("%[^|]|%[^|]|%[^|]|%[^|]|%[^|]"), st_IPAddr.tszIPCountry, st_IPAddr.tszIPCounty, st_IPAddr.tszIPProvince, st_IPAddr.tszIPCity, st_IPAddr.tszIPISP);
	st_JsonObject["tszIPAddr"] = st_IPAddr.tszIPAddr;
	st_JsonObject["tszIPCountry"] = st_IPAddr.tszIPCountry;
	st_JsonObject["tszIPProvince"] = st_IPAddr.tszIPProvince;
	st_JsonObject["tszIPCity"] = st_IPAddr.tszIPCity;
	st_JsonObject["tszIPCounty"] = st_IPAddr.tszIPCounty;
	st_JsonObject["tszIPAddress"] = st_IPAddr.tszIPAddress;
	st_JsonObject["tszIPISP"] = st_IPAddr.tszIPISP;

	st_JsonRoot["data"] = st_JsonObject;
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_HTTPCode = 200;
	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}