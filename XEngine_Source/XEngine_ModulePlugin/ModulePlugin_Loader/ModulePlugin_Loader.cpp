#include "pch.h"
#include "ModulePlugin_Loader.h"
/********************************************************************
//    Created:     2022/04/20  16:36:01
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_Loader\ModulePlugin_Loader.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_Loader
//    File Base:   ModulePlugin_Loader
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     插件加载工具
//    History:
*********************************************************************/
CModulePlugin_Loader::CModulePlugin_Loader()
{
}
CModulePlugin_Loader::~CModulePlugin_Loader()
{
}
//////////////////////////////////////////////////////////////////////////
//                       公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModulePlugin_Loader_Insert
函数功能：插入一个模块到加载器
 参数.一：lpszModuleMethod
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：插件方法名
 参数.二：lpszModuleName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：插件路径
 参数.三：nType
  In/Out：In
  类型：整数型
  可空：Y
  意思：0为lib,1为lua
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModulePlugin_Loader::ModulePlugin_Loader_Insert(LPCXSTR lpszModuleMethod, LPCXSTR lpszModuleName, int nType /* = 0 */)
{
    ModulePlugin_IsErrorOccur = FALSE;

    if ((NULL == lpszModuleMethod) || (NULL == lpszModuleName))
    {
        ModulePlugin_IsErrorOccur = TRUE;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_PARAMENT;
        return FALSE;
    }
    PLUGINCORE_LOADER st_PluginLoader;
    memset(&st_PluginLoader, '\0', sizeof(PLUGINCORE_LOADER));

	st_PluginLoader.nType = nType;
    _tcsxcpy(st_PluginLoader.tszModuleFile, lpszModuleName);
    _tcsxcpy(st_PluginLoader.tszModuleMethod, lpszModuleMethod);

	if (0 == nType)
	{
		if (!ModulePlugin_LibCore_Push(&st_PluginLoader.xhToken, lpszModuleName))
		{
			return FALSE;
		}
	}
	else
	{
		if (!ModulePlugin_LuaCore_Push(&st_PluginLoader.xhToken, lpszModuleName))
		{
			return FALSE;
		}
	}
	
    st_Locker.lock();
    stl_MapLoader.insert(make_pair(lpszModuleMethod, st_PluginLoader));
    st_Locker.unlock();
    return TRUE;
}
/********************************************************************
函数名称：ModulePlugin_Loader_Find
函数功能：查找方法是否注册
 参数.一：lpszMethodName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要执行的方法
 参数.二：pInt_Type
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出获取到的模块类型
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModulePlugin_Loader::ModulePlugin_Loader_Find(LPCXSTR lpszMethodName, int* pInt_Type)
{
	ModulePlugin_IsErrorOccur = FALSE;

	if (NULL == lpszMethodName)
	{
		ModulePlugin_IsErrorOccur = TRUE;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_PARAMENT;
		return FALSE;
	}
	st_Locker.lock_shared();
	unordered_map<string, PLUGINCORE_LOADER>::const_iterator stl_MapIterator = stl_MapLoader.find(lpszMethodName);
	if (stl_MapIterator == stl_MapLoader.end())
	{
		ModulePlugin_IsErrorOccur = TRUE;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_NOTFOUND;
		st_Locker.unlock_shared();
		return FALSE;
	}
	if (NULL != pInt_Type)
	{
		*pInt_Type = stl_MapIterator->second.nType;
	}
	st_Locker.unlock_shared();
	return TRUE;
}
/********************************************************************
函数名称：ModulePlugin_Loader_Exec
函数功能：执行一次插件
 参数.一：lpszMethodName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要执行的方法
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
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModulePlugin_Loader::ModulePlugin_Loader_Exec(LPCXSTR lpszMethodName, XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen)
{
	ModulePlugin_IsErrorOccur = FALSE;

	if (NULL == lpszMethodName)
	{
		ModulePlugin_IsErrorOccur = TRUE;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_PARAMENT;
		return FALSE;
	}
	st_Locker.lock_shared();
	unordered_map<string, PLUGINCORE_LOADER>::const_iterator stl_MapIterator = stl_MapLoader.find(lpszMethodName);
	if (stl_MapIterator == stl_MapLoader.end())
	{
		ModulePlugin_IsErrorOccur = TRUE;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_NOTFOUND;
		st_Locker.unlock_shared();
		return FALSE;
	}

	if (0 == stl_MapIterator->second.nType)
	{
		if (!ModulePlugin_LibCore_Exec(stl_MapIterator->second.xhToken, pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen))
		{
			st_Locker.unlock_shared();
			return FALSE;
		}
	}
	else
	{
		if (!ModulePlugin_LuaCore_Exec(stl_MapIterator->second.xhToken, pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen))
		{
			st_Locker.unlock_shared();
			return FALSE;
		}
	}
	st_Locker.unlock_shared();
	return TRUE;
}
/********************************************************************
函数名称：ModulePlugin_Loader_Destory
函数功能：销毁加载器
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModulePlugin_Loader::ModulePlugin_Loader_Destory()
{
	ModulePlugin_IsErrorOccur = FALSE;

	st_Locker.lock();
	stl_MapLoader.clear();
	st_Locker.unlock_shared();
	return TRUE;
}