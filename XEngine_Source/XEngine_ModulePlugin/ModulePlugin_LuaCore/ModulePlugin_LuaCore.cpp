#include "pch.h"
#include "ModulePlugin_LuaCore.h"
/********************************************************************
//    Created:     2022/11/30  16:18:24
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_LuaCore\ModulePlugin_LuaCore.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_LuaCore
//    File Base:   ModulePlugin_LuaCore
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     LUA脚本你插件
//    History:
*********************************************************************/
CModulePlugin_LuaCore::CModulePlugin_LuaCore()
{
    bIsInit = FALSE;
}
CModulePlugin_LuaCore::~CModulePlugin_LuaCore()
{
}
//////////////////////////////////////////////////////////////////////////
//                       公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModulePlugin_LuaCore_Init
函数功能：初始化插件核心系统
返回值
  类型：逻辑型
  意思：是否成功初始化
备注：
*********************************************************************/
BOOL CModulePlugin_LuaCore::ModulePlugin_LuaCore_Init()
{
    ModulePlugin_IsErrorOccur = FALSE;
    //判断是否初始化
    if (bIsInit)
    {
        ModulePlugin_IsErrorOccur = TRUE;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_ISINITED;
        return FALSE;
    }
    //启动线程
    bIsInit = TRUE;
    return TRUE;
}
/********************************************************************
函数名称：ModulePlugin_LuaCore_Push
函数功能：添加一个标准的插件到插件框架中
 参数.一：pxhModule
  In/Out：Out
  类型：模块句柄
  可空：N
  意思：导出一个加载成功的模块句柄
 参数.二：lpszPluginFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：插件模块路径
 参数.三：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：自定义输入输出参数
返回值
  类型：逻辑型
  意思：是否成功添加
备注：
*********************************************************************/
BOOL CModulePlugin_LuaCore::ModulePlugin_LuaCore_Push(XNETHANDLE* pxhModule, LPCTSTR lpszPluginFile, LPVOID lParam)
{
    ModulePlugin_IsErrorOccur = FALSE;

    if (!BaseLib_OperatorHandle_Create(pxhModule))
    {
        ModulePlugin_IsErrorOccur = TRUE;
        ModulePlugin_dwErrorCode = BaseLib_GetLastError();
        return FALSE;
    }
    if (!ModulePlugin_LuaCore_Add(*pxhModule, lpszPluginFile, lParam))
    {
        return FALSE;
    }
    return TRUE;
}
/********************************************************************
函数名称：ModulePlugin_LuaCore_Exec
函数功能：执行一次
 参数.一：xhModule
  In/Out：In
  类型：句柄
  可空：N
  意思：输入模块句柄
 参数.二：pppHDRList
  In/Out：In
  类型：三级指针
  可空：N
  意思：HTTP请求的URL参数列表
 参数.三：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：输入列表个数
 参数.四：pInt_HTTPCode
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出返回的HTTPCODE值
 参数.五：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出负载的内容
 参数.六：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出内容大小
 参数.七：lpszMsgBufer
  In/Out：Out
  类型：常量字符指针
  可空：Y
  意思：输入负载内容
 参数.八：nMsgLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输入负载大小
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModulePlugin_LuaCore::ModulePlugin_LuaCore_Exec(XNETHANDLE xhModule, TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBufer /* = NULL */, int nMsgLen /* = 0 */)
{
    ModulePlugin_IsErrorOccur = FALSE;

    st_csStl.lock_shared();
	//执行指定插件函数
	unordered_map<XNETHANDLE, PLUGINCORE_LUAFRAMEWORK>::const_iterator stl_MapIterator = stl_MapFrameWork.find(xhModule);
	if (stl_MapIterator == stl_MapFrameWork.end())
	{
		ModulePlugin_IsErrorOccur = TRUE;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_NOTFOUND;
		st_csStl.unlock_shared();
		return FALSE;
	}

	if (0 == lua_getglobal(stl_MapIterator->second.pSt_LuaState, "PluginCore_Call1"))
	{
		return FALSE;
	}

    lua_pushstring(stl_MapIterator->second.pSt_LuaState, "1");
    lua_pushstring(stl_MapIterator->second.pSt_LuaState, "2");
    lua_pushinteger(stl_MapIterator->second.pSt_LuaState, 3);
    int nRet = lua_pcall(stl_MapIterator->second.pSt_LuaState, 3, 0, 0);

    lua_getglobal(stl_MapIterator->second.pSt_LuaState, "pInt_HTTPCode");
    *pInt_HTTPCode = lua_tonumber(stl_MapIterator->second.pSt_LuaState, -1);
    lua_pop(stl_MapIterator->second.pSt_LuaState, -1);

    lua_getglobal(stl_MapIterator->second.pSt_LuaState, "pInt_MsgLen");
    *pInt_MsgLen = lua_tonumber(stl_MapIterator->second.pSt_LuaState, -1);
    lua_pop(stl_MapIterator->second.pSt_LuaState, -1);

	lua_getglobal(stl_MapIterator->second.pSt_LuaState, "ptszMsgBuffer");
	LPCTSTR lpszStr = lua_tostring(stl_MapIterator->second.pSt_LuaState, -1);
	lua_pop(stl_MapIterator->second.pSt_LuaState, -1);
    /*
	lua_newtable(stl_MapIterator->second.pSt_LuaState);
	for (int i = 0; i < nListCount; i++)
	{
		TCHAR tszStrKey[64];
		TCHAR tszStrValue[64];

		memset(tszStrKey, '\0', sizeof(tszStrKey));
		memset(tszStrValue, '\0', sizeof(tszStrValue));
		BaseLib_OperatorString_GetKeyValue((*pppHDRList)[i], "=", tszStrKey, tszStrValue);

		lua_pushstring(stl_MapIterator->second.pSt_LuaState, tszStrKey);
		lua_pushstring(stl_MapIterator->second.pSt_LuaState, tszStrValue);
		lua_settable(stl_MapIterator->second.pSt_LuaState, -3);
	}
	lua_pushnumber(stl_MapIterator->second.pSt_LuaState, nListCount);

    int nRet = 0;
	if (NULL == lpszMsgBufer)
	{
		lua_pushstring(stl_MapIterator->second.pSt_LuaState, "");
        lua_pushinteger(stl_MapIterator->second.pSt_LuaState, 0);

        nRet = lua_pcall(stl_MapIterator->second.pSt_LuaState, 7, 1, 0);
	}
    else
	{
		lua_pushstring(stl_MapIterator->second.pSt_LuaState, lpszMsgBufer);
		lua_pushinteger(stl_MapIterator->second.pSt_LuaState, nMsgLen);

        nRet = lua_pcall(stl_MapIterator->second.pSt_LuaState, 7, 1, 0);
	}
	*/
    st_csStl.unlock_shared();

    return TRUE;
}
/********************************************************************
函数名称：ModulePlugin_LuaCore_Destroy
函数功能：销毁插件核心并且清理资源
返回值
  类型：逻辑型
  意思：是否成功销毁
备注：
*********************************************************************/
BOOL CModulePlugin_LuaCore::ModulePlugin_LuaCore_Destroy()
{
    ModulePlugin_IsErrorOccur = FALSE;

    //判断是否初始化
    if (!bIsInit)
    {
        return TRUE;
    }
    bIsInit = FALSE;
    //清理STL元素空间
    st_csStl.lock();
    unordered_map<XNETHANDLE, PLUGINCORE_LUAFRAMEWORK>::iterator stl_MapIterator = stl_MapFrameWork.begin();
    for (; stl_MapIterator != stl_MapFrameWork.end(); stl_MapIterator++)
    {
        lua_getglobal(stl_MapIterator->second.pSt_LuaState, "PluginCore_UnInit");
		lua_pcall(stl_MapIterator->second.pSt_LuaState, 0, 0, 0);

        lua_close(stl_MapIterator->second.pSt_LuaState);
    }
    stl_MapFrameWork.clear();
    st_csStl.unlock();

    return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModulePlugin_LuaCore_Add
函数功能：添加一个指定模块到插件核心系统当中
 参数.一：xhNet
  In/Out：In
  类型：模块句柄
  可空：N
  意思：输入一个新的模块句柄
 参数.二：lpszPluginFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：插件模块路径
 参数.三：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：自定义输入输出参数
返回值
  类型：逻辑型
  意思：是否成功执行
备注：
*********************************************************************/
BOOL CModulePlugin_LuaCore::ModulePlugin_LuaCore_Add(XNETHANDLE xhNet, LPCTSTR lpszPluginFile, LPVOID lParam)
{
    ModulePlugin_IsErrorOccur = FALSE;

    if (NULL == lpszPluginFile)
    {
        ModulePlugin_IsErrorOccur = TRUE;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_PARAMENT;
        return FALSE;
    }
    PLUGINCORE_LUAFRAMEWORK st_LuaCore;
    memset(&st_LuaCore, '\0', sizeof(PLUGINCORE_LUAFRAMEWORK));

    st_LuaCore.pSt_LuaState = luaL_newstate();
    _tcscpy(st_LuaCore.tszModuleFile, lpszPluginFile);

    if (NULL == st_LuaCore.pSt_LuaState)
	{
		return FALSE;
	}
	luaL_openlibs(st_LuaCore.pSt_LuaState);

    if (0 != luaL_loadfile(st_LuaCore.pSt_LuaState, lpszPluginFile))
    {
        return FALSE;
    }
    if (0 != lua_pcall(st_LuaCore.pSt_LuaState, 0, 0, 0))
    {
        return FALSE;
    }

    if (0 == lua_getglobal(st_LuaCore.pSt_LuaState, "PluginCore_Init"))
    {
        return FALSE;
    }
    if (NULL == lParam)
    {
		if (LUA_OK != lua_pcall(st_LuaCore.pSt_LuaState, 0, 1, 0))
		{
			return FALSE;
		}
    }
    else
    {
		lua_pushlightuserdata(st_LuaCore.pSt_LuaState, lParam);
		if (LUA_OK != lua_pcall(st_LuaCore.pSt_LuaState, 1, 1, 0))
		{
			return FALSE;
		}
    }
    if (!lua_toboolean(st_LuaCore.pSt_LuaState, -1))
    {
        return FALSE;
    }

    st_csStl.lock();
    stl_MapFrameWork.insert(make_pair(xhNet, st_LuaCore));
    st_csStl.unlock();
    return TRUE;
}