#pragma once
/********************************************************************
//    Created:     2022/11/30  16:18:00
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_LuaCore\ModulePlugin_LuaCore.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_LuaCore
//    File Base:   ModulePlugin_LuaCore
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     LUA脚本你插件
//    History:
*********************************************************************/
typedef struct
{
	TCHAR tszModuleFile[MAX_PATH];
	lua_State* pSt_LuaState;
}PLUGINCORE_LUAFRAMEWORK;

class CModulePlugin_LuaCore
{
public:
	CModulePlugin_LuaCore();
	~CModulePlugin_LuaCore();
public:
	BOOL ModulePlugin_LuaCore_Init();
	BOOL ModulePlugin_LuaCore_Push(XNETHANDLE* pxhModule, LPCTSTR lpszPluginFile, LPVOID lParam = NULL);
	BOOL ModulePlugin_LuaCore_Exec(XNETHANDLE xhModule, TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBufer = NULL, int nMsgLen = 0);
	BOOL ModulePlugin_LuaCore_Destroy();
protected:
	BOOL ModulePlugin_LuaCore_Add(XNETHANDLE xhNet, LPCTSTR lpszPluginFile, LPVOID lParam = NULL);
private:
	BOOL bIsInit;
private:
	shared_mutex st_csStl;
private:
	unordered_map<XNETHANDLE, PLUGINCORE_LUAFRAMEWORK> stl_MapFrameWork;
};
