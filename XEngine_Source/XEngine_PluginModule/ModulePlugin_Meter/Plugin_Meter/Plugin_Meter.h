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
	BOOL PluginCore_Init(LPVOID lParam);
	BOOL PluginCore_UnInit();
	BOOL PluginCore_Call(TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBuffer, int nMsgLen);
protected:
	BOOL Plugin_Meter_LengthConvert(int nSource, __int64x nValue, Json::Value *pSt_JsonObject);
	BOOL Plugin_Meter_TemperatureConvert(int nSource, __int64x nValue, Json::Value* pSt_JsonObject);
	BOOL Plugin_Meter_PowerConvert(int nSource, __int64x nValue, Json::Value* pSt_JsonObject);
	BOOL Plugin_Meter_SpeedConvert(int nSource, __int64x nValue, Json::Value* pSt_JsonObject);
private:
};
