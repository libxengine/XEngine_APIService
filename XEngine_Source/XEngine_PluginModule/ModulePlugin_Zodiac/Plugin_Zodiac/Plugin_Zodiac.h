#pragma once
/********************************************************************
//    Created:     2022/04/21  15:50:04
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Zodiac\Plugin_Zodiac\Plugin_Zodiac.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Zodiac\Plugin_Zodiac
//    File Base:   Plugin_Zodiac
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     星座生肖
//    History:
*********************************************************************/

class CPlugin_Zodiac
{
public:
	CPlugin_Zodiac();
	~CPlugin_Zodiac();
public:
	BOOL PluginCore_Init(LPVOID lParam);
	BOOL PluginCore_UnInit();
	BOOL PluginCore_Call(TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBuffer, int nMsgLen);
protected:
	BOOL Plugin_Zodiac_Chinese(LPCTSTR lpszDate, TCHAR* ptszCZodiac);
	BOOL Plugin_Zodiac_English(LPCTSTR lpszDate, TCHAR* ptszEZodiac);
private:
	string m_StrChinese[12];
};
