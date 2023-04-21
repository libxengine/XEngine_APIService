#pragma once
/********************************************************************
//    Created:     2023/01/10  11:09:11
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_IPAddr\ModulePlugin_Interface\ModulePlugin_Interface.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_IPAddr\ModulePlugin_Interface
//    File Base:   ModulePlugin_Interface
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     IP地址类
//    History:
*********************************************************************/

class CModulePlugin_Interface
{
public:
	CModulePlugin_Interface();
	~CModulePlugin_Interface();
public:
	bool PluginCore_Init(XPVOID lParam);
	void PluginCore_UnInit();
	bool PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen);
protected:
private:
	xdb_searcher_t st_DBSearch;
};
