#pragma once
/********************************************************************
//    Created:     2022/07/20  16:36:59
//    File Name:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_BMIndex\Plugin_BMIndex\Plugin_BMIndex.h
//    File Path:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_BMIndex\Plugin_BMIndex
//    File Base:   Plugin_BMIndex
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     标准身高体重
//    History:
*********************************************************************/

class CPlugin_BMIndex
{
public:
	CPlugin_BMIndex();
	~CPlugin_BMIndex();
public:
	BOOL PluginCore_Init(LPVOID lParam);
	BOOL PluginCore_UnInit();
	BOOL PluginCore_Call(TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBuffer, int nMsgLen);
protected:
	BOOL Plugin_Timezone_BMIndex(LPCTSTR lpszHigh, LPCTSTR lpszWeight, TCHAR* ptszMsgBufer, int* pInt_Len);
private:
};
