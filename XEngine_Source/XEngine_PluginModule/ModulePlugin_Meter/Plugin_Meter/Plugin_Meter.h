#pragma once
/********************************************************************
//    Created:     2022/11/01  13:39:40
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Meter\Plugin_Meter\Plugin_Meter.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Meter\Plugin_Meter
//    File Base:   Plugin_Meter
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     计量转换器
//    History:
*********************************************************************/

class CPlugin_Meter
{
public:
	CPlugin_Meter();
	~CPlugin_Meter();
public:
	bool PluginCore_Init(XPVOID lParam);
	void PluginCore_UnInit();
	void PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc);
	bool PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen);
protected:
	bool Plugin_Meter_LengthConvert(int nSource, __int64x nValue, Json::Value *pSt_JsonObject);
	bool Plugin_Meter_TemperatureConvert(int nSource, __int64x nValue, Json::Value* pSt_JsonObject);
	bool Plugin_Meter_PowerConvert(int nSource, __int64x nValue, Json::Value* pSt_JsonObject);
	bool Plugin_Meter_SpeedConvert(int nSource, __int64x nValue, Json::Value* pSt_JsonObject);
private:
};
