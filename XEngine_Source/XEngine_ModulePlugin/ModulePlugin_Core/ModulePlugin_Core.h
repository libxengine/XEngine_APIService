#pragma once
/********************************************************************
//    Created:     2022/04/20  16:13:41
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_Core\ModulePlugin_Core.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_Core
//    File Base:   ModulePlugin_Core
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     插件核心架构定义
//    History:
*********************************************************************/
typedef BOOL(*FPCall_PluginCore_Init)(LPVOID lParam);
typedef BOOL(*FPCall_PluginCore_UnInit)();
typedef BOOL(*FPCall_PluginCore_Call)(TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBufer, int nMsgLen);
typedef DWORD(*FPCall_PluginCore_GetLastError)();

typedef struct 
{
	HMODULE mhFile;
	TCHAR tszModuleFile[MAX_PATH];

	BOOL(*fpCall_PluginCore_Init)(LPVOID lParam);
	BOOL(*fpCall_PluginCore_UnInit)();
	BOOL(*fpCall_PluginCore_Call)(TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBufer, int nMsgLen);
	DWORD(*fpCall_PluginCore_GetLastError)();
}PLUGINCORE_FRAMEWORK, * LPPLUGINCORE_FRAMEWORK;

class CModulePlugin_Core
{
public:
	CModulePlugin_Core();
	~CModulePlugin_Core();
public:
	BOOL ModulePlugin_Core_Init();
	BOOL ModulePlugin_Core_Push(XNETHANDLE* pxhModule, LPCTSTR lpszPluginFile, LPVOID lParam = NULL);
	BOOL ModulePlugin_Core_Exec(XNETHANDLE xhModule, TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBufer = NULL, int nMsgLen = 0);
	BOOL ModulePlugin_Core_Destroy();
protected:
	BOOL ModulePlugin_Core_Add(XNETHANDLE xhNet, LPCTSTR lpszPluginFile, LPVOID lParam = NULL);
private:
	BOOL bIsInit;
private:
	shared_mutex st_csStl;
private:
	unordered_map<XNETHANDLE, PLUGINCORE_FRAMEWORK> stl_MapFrameWork;
};
