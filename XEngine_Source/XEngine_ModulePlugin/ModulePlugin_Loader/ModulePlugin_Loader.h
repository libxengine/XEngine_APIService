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
	XCHAR tszModuleFile[MAX_PATH];
	XCHAR tszModuleMethod[MAX_PATH];
	XNETHANDLE xhToken;
	int nType;
}PLUGINCORE_LOADER, * LPPLUGINCORE_LOADER;

class CModulePlugin_Loader
{
public:
	CModulePlugin_Loader();
	~CModulePlugin_Loader();
public:
	bool ModulePlugin_Loader_Init();
	bool ModulePlugin_Loader_Insert(LPCXSTR lpszModuleMethod, LPCXSTR lpszModuleName, int nType = 0);
	bool ModulePlugin_Loader_Find(LPCXSTR lpszMethodName, int* pInt_Type);
	bool ModulePlugin_Loader_Exec(LPCXSTR lpszMethodName, XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen);
	bool ModulePlugin_Loader_Destory();
protected:
private:
	shared_mutex st_Locker;
private:
	unordered_map<string, PLUGINCORE_LOADER> stl_MapLoader;
};
