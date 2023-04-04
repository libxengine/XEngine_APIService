#pragma once
/********************************************************************
//    Created:     2022/11/30  16:16:35
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_LibCore\ModulePlugin_LibCore.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_LibCore
//    File Base:   ModulePlugin_LibCore
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     插件核心架构定义
//    History:
*********************************************************************/
typedef XBOOL(*FPCall_PluginCore_Init)(XPVOID lParam);
typedef void(*FPCall_PluginCore_UnInit)();
typedef XBOOL(*FPCall_PluginCore_Call)(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer, int nMsgLen);
typedef DWORD(*FPCall_PluginCore_GetLastError)();

typedef struct 
{
	HMODULE mhFile;
	XCHAR tszModuleFile[MAX_PATH];

	XBOOL(*fpCall_PluginCore_Init)(XPVOID lParam);
	void(*fpCall_PluginCore_UnInit)();
	XBOOL(*fpCall_PluginCore_Call)(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer, int nMsgLen);
	DWORD(*fpCall_PluginCore_GetLastError)();
}PLUGINCORE_FRAMEWORK, * LPPLUGINCORE_FRAMEWORK;

class CModulePlugin_LibCore
{
public:
	CModulePlugin_LibCore();
	~CModulePlugin_LibCore();
public:
	XBOOL ModulePlugin_LibCore_Init();
	XBOOL ModulePlugin_LibCore_Push(XNETHANDLE* pxhModule, LPCXSTR lpszPluginFile, XPVOID lParam = NULL);
	XBOOL ModulePlugin_LibCore_Exec(XNETHANDLE xhModule, XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer = NULL, int nMsgLen = 0);
	XBOOL ModulePlugin_LibCore_Destroy();
protected:
	XBOOL ModulePlugin_LibCore_Add(XNETHANDLE xhNet, LPCXSTR lpszPluginFile, XPVOID lParam = NULL);
private:
	XBOOL bIsInit;
private:
	shared_mutex st_csStl;
private:
	unordered_map<XNETHANDLE, PLUGINCORE_FRAMEWORK> stl_MapFrameWork;
};
