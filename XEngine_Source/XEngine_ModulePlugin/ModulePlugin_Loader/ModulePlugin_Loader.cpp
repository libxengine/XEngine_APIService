﻿#include "pch.h"
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
函数名称：ModulePlugin_Loader_Init
函数功能：初始化插件加载器
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_Loader::ModulePlugin_Loader_Init()
{
	ModulePlugin_LibCore_Init();
	ModulePlugin_LuaCore_Init();

	return true;
}
/********************************************************************
函数名称：ModulePlugin_Loader_Insert
函数功能：插入一个模块到加载器
 参数.一：lpszModuleName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：插件路径
 参数.二：nType
  In/Out：In
  类型：整数型
  可空：N
  意思：0为lib,1为lua
 参数.三：pSt_PluginParameter
  In/Out：In
  类型：数据结构指针
  可空：Y
  意思：输入插件初始化参数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_Loader::ModulePlugin_Loader_Insert(LPCXSTR lpszModuleName, int nType, XENGINE_PLUGINPARAM* pSt_PluginParameter /* = NULL */)
{
    ModulePlugin_IsErrorOccur = false;

    if (NULL == lpszModuleName)
    {
        ModulePlugin_IsErrorOccur = true;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_PARAMENT;
        return false;
    }
    PLUGINCORE_LOADER st_PluginLoader;
    memset(&st_PluginLoader, '\0', sizeof(PLUGINCORE_LOADER));

	st_PluginLoader.nType = nType;
    _tcsxcpy(st_PluginLoader.tszModuleFile, lpszModuleName);

	if (0 == nType)
	{
		if (!ModulePlugin_LibCore_Push(&st_PluginLoader.xhToken, lpszModuleName, pSt_PluginParameter))
		{
			return false;
		}
		ModulePlugin_LibCore_Get(st_PluginLoader.xhToken, st_PluginLoader.tszModuleName, st_PluginLoader.tszModuleVer, st_PluginLoader.tszModuleAuthor, st_PluginLoader.tszModuleDesc);
	}
	else
	{
		if (!ModulePlugin_LuaCore_Push(&st_PluginLoader.xhToken, lpszModuleName, pSt_PluginParameter))
		{
			return false;
		}
		ModulePlugin_LuaCore_Get(st_PluginLoader.xhToken, st_PluginLoader.tszModuleName, st_PluginLoader.tszModuleVer, st_PluginLoader.tszModuleAuthor, st_PluginLoader.tszModuleDesc);
	}
	
    st_Locker.lock();
    stl_MapLoader.insert(make_pair(st_PluginLoader.tszModuleName, st_PluginLoader));
    st_Locker.unlock();
    return true;
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
bool CModulePlugin_Loader::ModulePlugin_Loader_Find(LPCXSTR lpszMethodName, int* pInt_Type)
{
	ModulePlugin_IsErrorOccur = false;

	if (NULL == lpszMethodName)
	{
		ModulePlugin_IsErrorOccur = true;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_PARAMENT;
		return false;
	}
	st_Locker.lock_shared();
	unordered_map<string, PLUGINCORE_LOADER>::const_iterator stl_MapIterator = stl_MapLoader.find(lpszMethodName);
	if (stl_MapIterator == stl_MapLoader.end())
	{
		ModulePlugin_IsErrorOccur = true;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_NOTFOUND;
		st_Locker.unlock_shared();
		return false;
	}
	if (NULL != pInt_Type)
	{
		*pInt_Type = stl_MapIterator->second.nType;
	}
	st_Locker.unlock_shared();
	return true;
}
/********************************************************************
函数名称：ModulePlugin_LibCore_Get
函数功能：获取插件基础信息函数
 参数.一：lpszMethodName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：要操作的模块句柄
 参数.二：ptszPluginName
  In/Out：Out
  类型：字符指针
  可空：N
  意思：处理名称
 参数.三：ptszPluginVersion
  In/Out：Out
  类型：字符指针
  可空：N
  意思：版本号.使用x.x.x.x 格式
 参数.四：ptszPluginAuthor
  In/Out：Out
  类型：字符指针
  可空：N
  意思：作者
 参数.五：ptszPluginDesc
  In/Out：Out
  类型：字符指针
  可空：N
  意思：插件描述
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_Loader::ModulePlugin_Loader_Get(LPCXSTR lpszMethodName, XCHAR* ptszPluginName /* = NULL */, XCHAR* ptszPluginVersion /* = NULL */, XCHAR* ptszPluginAuthor /* = NULL */, XCHAR* ptszPluginDesc /* = NULL */)
{
	ModulePlugin_IsErrorOccur = false;

	if (NULL == ptszPluginName || NULL == ptszPluginVersion || NULL == ptszPluginAuthor || NULL == ptszPluginDesc)
	{
		ModulePlugin_IsErrorOccur = true;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_PARAMENT;
		return false;
	}
	st_Locker.lock_shared();
	unordered_map<string, PLUGINCORE_LOADER>::const_iterator stl_MapIterator = stl_MapLoader.find(lpszMethodName);
	if (stl_MapIterator == stl_MapLoader.end())
	{
		ModulePlugin_IsErrorOccur = true;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_NOTFOUND;
		st_Locker.unlock_shared();
		return false;
	}
	if (NULL != ptszPluginName)
	{
		_tcsxcpy(ptszPluginName, stl_MapIterator->second.tszModuleName);
	}
	if (NULL != ptszPluginVersion)
	{
		_tcsxcpy(ptszPluginVersion, stl_MapIterator->second.tszModuleVer);
	}
	if (NULL != ptszPluginAuthor)
	{
		_tcsxcpy(ptszPluginAuthor, stl_MapIterator->second.tszModuleAuthor);
	}
	if (NULL != ptszPluginDesc)
	{
		_tcsxcpy(ptszPluginDesc, stl_MapIterator->second.tszModuleDesc);
	}
	st_Locker.unlock_shared();
	return true;
}
/********************************************************************
函数名称：ModulePlugin_Loader_GetForModule
函数功能：通过模块名称获取模块信息
 参数.一：lpszModuleName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：要操作的模块名称
 参数.二：ptszPluginName
  In/Out：Out
  类型：字符指针
  可空：N
  意思：处理名称
 参数.三：ptszPluginVersion
  In/Out：Out
  类型：字符指针
  可空：N
  意思：版本号.使用x.x.x.x 格式
 参数.四：ptszPluginAuthor
  In/Out：Out
  类型：字符指针
  可空：N
  意思：作者
 参数.五：ptszPluginDesc
  In/Out：Out
  类型：字符指针
  可空：N
  意思：插件描述
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_Loader::ModulePlugin_Loader_GetForModule(LPCXSTR lpszModuleName, XCHAR* ptszPluginName /* = NULL */, XCHAR* ptszPluginVersion /* = NULL */, XCHAR* ptszPluginAuthor /* = NULL */, XCHAR* ptszPluginDesc /* = NULL */)
{
	ModulePlugin_IsErrorOccur = false;

	bool bFound = false;
	st_Locker.lock_shared();
	for (auto stl_MapIterator = stl_MapLoader.begin(); stl_MapIterator != stl_MapLoader.end(); stl_MapIterator++)
	{
		if (0 == _tcsxnicmp(lpszModuleName, stl_MapIterator->second.tszModuleFile, _tcsxlen(stl_MapIterator->second.tszModuleFile)))
		{
			if (NULL != ptszPluginName)
			{
				_tcsxcpy(ptszPluginName, stl_MapIterator->second.tszModuleName);
			}
			if (NULL != ptszPluginVersion)
			{
				_tcsxcpy(ptszPluginVersion, stl_MapIterator->second.tszModuleVer);
			}
			if (NULL != ptszPluginAuthor)
			{
				_tcsxcpy(ptszPluginAuthor, stl_MapIterator->second.tszModuleAuthor);
			}
			if (NULL != ptszPluginDesc)
			{
				_tcsxcpy(ptszPluginDesc, stl_MapIterator->second.tszModuleDesc);
			}
			bFound = true;
			break;
		}
	}
	st_Locker.unlock_shared();

	if (!bFound)
	{
		ModulePlugin_IsErrorOccur = true;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_NOTFOUND;
		return false;
	}
	return true;
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
bool CModulePlugin_Loader::ModulePlugin_Loader_Exec(LPCXSTR lpszMethodName, XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen)
{
	ModulePlugin_IsErrorOccur = false;

	if (NULL == lpszMethodName)
	{
		ModulePlugin_IsErrorOccur = true;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_PARAMENT;
		return false;
	}
	st_Locker.lock_shared();
	unordered_map<string, PLUGINCORE_LOADER>::const_iterator stl_MapIterator = stl_MapLoader.find(lpszMethodName);
	if (stl_MapIterator == stl_MapLoader.end())
	{
		ModulePlugin_IsErrorOccur = true;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_NOTFOUND;
		st_Locker.unlock_shared();
		return false;
	}

	if (0 == stl_MapIterator->second.nType)
	{
		if (!ModulePlugin_LibCore_Exec(stl_MapIterator->second.xhToken, pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen))
		{
			st_Locker.unlock_shared();
			return false;
		}
	}
	else
	{
		if (!ModulePlugin_LuaCore_Exec(stl_MapIterator->second.xhToken, pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen))
		{
			st_Locker.unlock_shared();
			return false;
		}
	}
	st_Locker.unlock_shared();
	return true;
}
/********************************************************************
函数名称：ModulePlugin_Loader_Destory
函数功能：销毁加载器
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_Loader::ModulePlugin_Loader_Destory()
{
	ModulePlugin_IsErrorOccur = false;

	ModulePlugin_LibCore_Destroy();
	ModulePlugin_LuaCore_Destroy();

	st_Locker.lock();
	stl_MapLoader.clear();
	st_Locker.unlock();
	return true;
}