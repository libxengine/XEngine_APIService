#include "pch.h"
#include "Plugin_Meter.h"
/********************************************************************
//    Created:     2022/11/01  13:40:13
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Meter\Plugin_Meter\Plugin_Meter.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Meter\Plugin_Meter
//    File Base:   Plugin_Meter
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     计量转换器
//    History:
*********************************************************************/
CPlugin_Meter::CPlugin_Meter()
{
}
CPlugin_Meter::~CPlugin_Meter()
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
bool CPlugin_Meter::PluginCore_Init(XPVOID lParam)
{
	Meter_IsErrorOccur = false;

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
void CPlugin_Meter::PluginCore_UnInit()
{
	Meter_IsErrorOccur = false;
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
void CPlugin_Meter::PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc)
{
	Meter_IsErrorOccur = false;

	ptszPluginName = (XCHAR *)"meter";
	ptszPluginVersion = (XCHAR*)"1.0.0.1001";
	ptszPluginAuthor = (XCHAR*)"xengine";
	ptszPluginDesc = (XCHAR*)"";
}
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CPlugin_Meter::PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	Meter_IsErrorOccur = false;

	if ((NULL == pInt_HTTPCode) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		Meter_IsErrorOccur = true;
		Meter_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_METER_PARAMENT;
		return false;
	}
	XCHAR tszKeyName[128];
	XCHAR tszParamType[128];
	XCHAR tszParamValue[128];
	XCHAR tszParamSource[128];
	
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	memset(tszKeyName, '\0', sizeof(tszKeyName));
	memset(tszParamType, '\0', sizeof(tszParamType));
	memset(tszParamSource, '\0', sizeof(tszParamSource));
	memset(tszParamValue, '\0', sizeof(tszParamValue));

	//http://192.168.1.8:5501/api?function=meter&type=0&source=0&value=10
	BaseLib_String_GetKeyValue((*pppHDRList)[1], "=", tszKeyName, tszParamType);
	BaseLib_String_GetKeyValue((*pppHDRList)[2], "=", tszKeyName, tszParamSource);
	BaseLib_String_GetKeyValue((*pppHDRList)[3], "=", tszKeyName, tszParamValue);

	if (0 == _ttxoi(tszParamType))
	{
		Plugin_Meter_LengthConvert(_ttxoi(tszParamSource), _ttxoll(tszParamValue), &st_JsonObject);
	}
	else if (1 == _ttxoi(tszParamType))
	{
		Plugin_Meter_TemperatureConvert(_ttxoi(tszParamSource), _ttxoll(tszParamValue), &st_JsonObject);
	}
	else if (2 == _ttxoi(tszParamType))
	{
		Plugin_Meter_PowerConvert(_ttxoi(tszParamSource), _ttxoll(tszParamValue), &st_JsonObject);
	}
	else if (3 == _ttxoi(tszParamType))
	{
		Plugin_Meter_SpeedConvert(_ttxoi(tszParamSource), _ttxoll(tszParamValue), &st_JsonObject);
	}
	
	st_JsonObject["tszParamType"] = _ttxoi(tszParamType);
	st_JsonObject["tszParamSource"] = _ttxoi(tszParamSource);
	st_JsonObject["tszParamValue"] = _ttxof(tszParamValue);

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
bool CPlugin_Meter::Plugin_Meter_LengthConvert(int nSource, __int64x nValue, Json::Value *pSt_JsonObject)
{
	Meter_IsErrorOccur = false;

	Json::Value st_JsonObejct;
	if (ENUM_APISERVICE_PLUGIN_METER_LENGTH_KILOMETRE == nSource)
	{
		st_JsonObejct["metre"] = double(nValue * 1000);
		st_JsonObejct["decimeter"] = double(nValue * 10000);
		st_JsonObejct["centimeter"] = double(nValue * 100000);
		st_JsonObejct["millimeter"] = double(nValue * 1000000);
		st_JsonObejct["micrometer"] = double(nValue * 1000000000);

		st_JsonObejct["li"] = double(nValue * 2);
		st_JsonObejct["zhang"] = double(nValue * 300);
		st_JsonObejct["chi"] = double(nValue * 3000);
		st_JsonObejct["cun"] = double(nValue * 30000);
		st_JsonObejct["fen"] = double(nValue * 300000);

		st_JsonObejct["nauticalmile"] = double(nValue * 0.539956803456);
		st_JsonObejct["mile"] = double(nValue * 0.621371);
		st_JsonObejct["yard"] = double(nValue * 1093.6133);
		st_JsonObejct["inch"] = double(nValue * 39370.079);
		st_JsonObejct["fur"] = double(nValue * 4.9709695);
		st_JsonObejct["foot"] = double(nValue * 3280.8399);
	}
	else if (ENUM_APISERVICE_PLUGIN_METER_LENGTH_METRE == nSource)
	{
		st_JsonObejct["kilometre"] = double(nValue * 0.001);
		st_JsonObejct["decimeter"] = double(nValue * 10);
		st_JsonObejct["centimeter"] = double(nValue * 100);
		st_JsonObejct["millimeter"] = double(nValue * 1000);
		st_JsonObejct["micrometer"] = double(nValue * 1000000);

		st_JsonObejct["li"] = double(nValue * 0.002);
		st_JsonObejct["zhang"] = double(nValue * 0.3);
		st_JsonObejct["chi"] = double(nValue * 3);
		st_JsonObejct["cun"] = double(nValue * 30);
		st_JsonObejct["fen"] = double(nValue * 300);

		st_JsonObejct["nauticalmile"] = double(nValue * 0.0005399568);
		st_JsonObejct["mile"] = double(nValue * 0.00062137119);
		st_JsonObejct["yard"] = double(nValue * 1.0936133);
		st_JsonObejct["inch"] = double(nValue * 39.370079);
		st_JsonObejct["fur"] = double(nValue * 0.0049709695);
		st_JsonObejct["foot"] = double(nValue * 3.2808399);
	}
	else if (ENUM_APISERVICE_PLUGIN_METER_LENGTH_DECIMETER == nSource)
	{
		st_JsonObejct["kilometre"] = double(nValue * 0.0001);
		st_JsonObejct["metre"] = double(nValue * 0.1);
		st_JsonObejct["centimeter"] = double(nValue * 10);
		st_JsonObejct["millimeter"] = double(nValue * 100);
		st_JsonObejct["micrometer"] = double(nValue * 100000);

		st_JsonObejct["li"] = double(nValue * 0.0002);
		st_JsonObejct["zhang"] = double(nValue * 0.03);
		st_JsonObejct["chi"] = double(nValue * 0.3);
		st_JsonObejct["cun"] = double(nValue * 3);
		st_JsonObejct["fen"] = double(nValue * 30);

		st_JsonObejct["nauticalmile"] = double(nValue * 0.00005399568);
		st_JsonObejct["mile"] = double(nValue * 0.000062137119);
		st_JsonObejct["yard"] = double(nValue * 0.10936133);
		st_JsonObejct["inch"] = double(nValue * 3.9370079);
		st_JsonObejct["fur"] = double(nValue * 0.00049709695);
		st_JsonObejct["foot"] = double(nValue * 0.32808399);
	}
	(*pSt_JsonObject)["Length"] = st_JsonObejct;
	return true;
}
bool CPlugin_Meter::Plugin_Meter_TemperatureConvert(int nSource, __int64x nValue, Json::Value* pSt_JsonObject)
{
	Meter_IsErrorOccur = false;

	Json::Value st_JsonObejct;
	if (ENUM_APISERVICE_PLUGIN_METER_TEMPERATURE_C == nSource)
	{
		st_JsonObejct["fahrenheit"] = double(nValue * 33.8);
		st_JsonObejct["kelvin"] = double(nValue * 274.15);
		st_JsonObejct["rankine"] = double(nValue * 493.46999999999997);
		st_JsonObejct["degree"] = double(nValue * 0.8);
	}
	(*pSt_JsonObject)["Temperature"] = st_JsonObejct;
	return true;
}
bool CPlugin_Meter::Plugin_Meter_PowerConvert(int nSource, __int64x nValue, Json::Value* pSt_JsonObject)
{
	Meter_IsErrorOccur = false;

	Json::Value st_JsonObejct;
	if (ENUM_APISERVICE_PLUGIN_METER_POWER_W == nSource)
	{
		st_JsonObejct["kw"] = double(nValue * 0.001);
		st_JsonObejct["hp"] = double(nValue * 0.001341);
		st_JsonObejct["ps"] = double(nValue * 0.00136);
	}
	(*pSt_JsonObject)["Power"] = st_JsonObejct;
	return true;
}
bool CPlugin_Meter::Plugin_Meter_SpeedConvert(int nSource, __int64x nValue, Json::Value* pSt_JsonObject)
{
	Meter_IsErrorOccur = false;

	Json::Value st_JsonObejct;
	if (ENUM_APISERVICE_PLUGIN_METER_SPEED_KNOT == nSource)
	{
		st_JsonObejct["mile"] = double(nValue * 1.1488500000000001);
		st_JsonObejct["kilometer"] = double(nValue * 1.85);
	}
	else if (ENUM_APISERVICE_PLUGIN_METER_POWER_MILE == nSource)
	{
		st_JsonObejct["knot"] = double(nValue * 00.8702702702702703);
		st_JsonObejct["kilometer"] = double(nValue * 1.61);
	}
	else
	{
		st_JsonObejct["knot"] = double(nValue * 00.5405405405405405);
		st_JsonObejct["kilometer"] = double(nValue * 00.621);
	}
	(*pSt_JsonObject)["Power"] = st_JsonObejct;
	return true;
}