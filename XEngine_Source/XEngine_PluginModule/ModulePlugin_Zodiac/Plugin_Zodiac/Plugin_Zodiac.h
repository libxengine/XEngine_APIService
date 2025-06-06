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
	bool PluginCore_Init(XENGINE_PLUGINPARAM *pSt_PluginParameter);
	void PluginCore_UnInit();
	void PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc);
	bool PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen);
protected:
	bool Plugin_Zodiac_Chinese(LPCXSTR lpszDate, XCHAR* ptszCZodiac);
	bool Plugin_Zodiac_English(LPCXSTR lpszDate, XCHAR* ptszEZodiac);
private:
	string m_StrChinese[12];
};
