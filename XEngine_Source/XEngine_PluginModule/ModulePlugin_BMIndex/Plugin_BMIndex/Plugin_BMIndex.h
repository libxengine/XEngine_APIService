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
	bool PluginCore_Init(XENGINE_PLUGINPARAM *pSt_PluginParameter);
	void PluginCore_UnInit();
	void PluginCore_GetInfo(XCHAR* ptszPluginName, XCHAR* ptszPluginVersion, XCHAR* ptszPluginAuthor, XCHAR* ptszPluginDesc);
	bool PluginCore_Call(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer = NULL, int nMsgLen = 0, XCHAR*** pppInputParameters = NULL, int nInputPCount = 0, XCHAR*** pppOutputParameters = NULL, int* pInt_OutputPCount = NULL);
protected:
	bool Plugin_Timezone_BMIndex(LPCXSTR lpszHigh, LPCXSTR lpszWeight, XCHAR* ptszMsgBufer, int* pInt_Len);
private:
};
