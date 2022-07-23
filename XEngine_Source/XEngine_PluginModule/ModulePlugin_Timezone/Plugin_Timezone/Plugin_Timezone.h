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
	TCHAR tszTimeCountry[MAX_PATH];
}MODULEPLUGIN_TIMEZONE;


class CPlugin_Timezone
{
public:
	CPlugin_Timezone();
	~CPlugin_Timezone();
public:
	BOOL PluginCore_Init(LPVOID lParam);
	BOOL PluginCore_UnInit();
	BOOL PluginCore_Call(TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBuffer, int nMsgLen);
protected:
	BOOL Plugin_Timezone_Count(TCHAR* ptszMsgBufer, int* pInt_Len);
	BOOL Plugin_Timezone_List(LPCTSTR lpszConvert, TCHAR* ptszMsgBufer, int* pInt_Len);
	BOOL Plugin_Timezone_Convert(LPCTSTR lpszConvert, LPCTSTR lpszTimeStr, TCHAR* ptszMsgBufer, int* pInt_Len);
private:
	unordered_map<string, MODULEPLUGIN_TIMEZONE> stl_MapTimezone;
};
