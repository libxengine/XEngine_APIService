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
typedef bool(*FPCall_PluginCore_Init)(XPVOID lParam);
typedef void(*FPCall_PluginCore_UnInit)();
typedef bool(*FPCall_PluginCore_Call)(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer, int nMsgLen);
typedef XLONG(*FPCall_PluginCore_GetLastError)();

typedef struct 
{
#ifdef _MSC_BUILD
	HMODULE mhFile;
#else
	void* mhFile;
#endif
	XCHAR tszModuleFile[XPATH_MAX];

	bool(*fpCall_PluginCore_Init)(XPVOID lParam);
	void(*fpCall_PluginCore_UnInit)();
	bool(*fpCall_PluginCore_Call)(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer, int nMsgLen);
	XLONG(*fpCall_PluginCore_GetLastError)();
}PLUGINCORE_FRAMEWORK, * LPPLUGINCORE_FRAMEWORK;

class CModulePlugin_LibCore
{
public:
	CModulePlugin_LibCore();
	~CModulePlugin_LibCore();
public:
	bool ModulePlugin_LibCore_Init();
	bool ModulePlugin_LibCore_Push(XNETHANDLE* pxhModule, LPCXSTR lpszPluginFile, XPVOID lParam = NULL);
	bool ModulePlugin_LibCore_Exec(XNETHANDLE xhModule, XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer = NULL, int nMsgLen = 0);
	bool ModulePlugin_LibCore_Destroy();
protected:
	bool ModulePlugin_LibCore_Add(XNETHANDLE xhNet, LPCXSTR lpszPluginFile, XPVOID lParam = NULL);
private:
	bool bIsInit;
private:
	shared_mutex st_csStl;
private:
	unordered_map<XNETHANDLE, PLUGINCORE_FRAMEWORK> stl_MapFrameWork;
};
