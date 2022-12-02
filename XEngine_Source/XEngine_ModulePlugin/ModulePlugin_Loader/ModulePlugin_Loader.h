#pragma once
/********************************************************************
//    Created:     2022/04/20  16:35:38
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_Loader\ModulePlugin_Loader.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_Loader
//    File Base:   ModulePlugin_Loader
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     插件加载工具
//    History:
*********************************************************************/
typedef struct
{
	TCHAR tszModuleFile[MAX_PATH];
	TCHAR tszModuleMethod[MAX_PATH];
	XNETHANDLE xhToken;
	int nType;
}PLUGINCORE_LOADER, * LPPLUGINCORE_LOADER;

class CModulePlugin_Loader
{
public:
	CModulePlugin_Loader();
	~CModulePlugin_Loader();
public:
	BOOL ModulePlugin_Loader_Insert(LPCTSTR lpszModuleMethod, LPCTSTR lpszModuleName, int nType = 0);
	BOOL ModulePlugin_Loader_Find(LPCTSTR lpszMethodName, int* pInt_Type);
	BOOL ModulePlugin_Loader_Exec(LPCTSTR lpszMethodName, TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen);
	BOOL ModulePlugin_Loader_Destory();
protected:
private:
	shared_mutex st_Locker;
private:
	unordered_map<string, PLUGINCORE_LOADER> stl_MapLoader;
};
