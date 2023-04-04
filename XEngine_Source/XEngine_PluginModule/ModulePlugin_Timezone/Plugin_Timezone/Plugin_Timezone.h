#pragma once
/********************************************************************
//    Created:     2022/07/20  09:56:02
//    File Name:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Timezone\Plugin_Timezone\Plugin_Timezone.h
//    File Path:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Timezone\Plugin_Timezone
//    File Base:   Plugin_Timezone
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     时区工具库
//    History:
*********************************************************************/
typedef struct  
{
	XENGINE_LIBTIMER st_TimeZone;
	XCHAR tszTimeCountry[MAX_PATH];
}MODULEPLUGIN_TIMEZONE;


class CPlugin_Timezone
{
public:
	CPlugin_Timezone();
	~CPlugin_Timezone();
public:
	XBOOL PluginCore_Init(XPVOID lParam);
	void PluginCore_UnInit();
	XBOOL PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen);
protected:
	XBOOL Plugin_Timezone_Count(XCHAR* ptszMsgBufer, int* pInt_Len);
	XBOOL Plugin_Timezone_List(LPCXSTR lpszConvert, XCHAR* ptszMsgBufer, int* pInt_Len);
	XBOOL Plugin_Timezone_Convert(LPCXSTR lpszConvert, LPCXSTR lpszTimeStr, XCHAR* ptszMsgBufer, int* pInt_Len);
private:
	unordered_map<string, MODULEPLUGIN_TIMEZONE> stl_MapTimezone;
};
