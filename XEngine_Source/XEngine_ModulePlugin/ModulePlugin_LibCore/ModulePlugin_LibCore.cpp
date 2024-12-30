#include "pch.h"
#include "ModulePlugin_LibCore.h"
/********************************************************************
//    Created:     2022/11/30  16:16:54
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_LibCore\ModulePlugin_LibCore.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_LibCore
//    File Base:   ModulePlugin_LibCore
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     插件核心架构实现
//    History:
*********************************************************************/
CModulePlugin_LibCore::CModulePlugin_LibCore()
{
    bIsInit = false;
}
CModulePlugin_LibCore::~CModulePlugin_LibCore()
{
}
//////////////////////////////////////////////////////////////////////////
//                       公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModulePlugin_LibCore_Init
函数功能：初始化插件核心系统
返回值
  类型：逻辑型
  意思：是否成功初始化
备注：
*********************************************************************/
bool CModulePlugin_LibCore::ModulePlugin_LibCore_Init()
{
    ModulePlugin_IsErrorOccur = false;
    //判断是否初始化
    if (bIsInit)
    {
        ModulePlugin_IsErrorOccur = true;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_ISINITED;
        return false;
    }
    //启动线程
    bIsInit = true;
    return true;
}
/********************************************************************
函数名称：ModulePlugin_LibCore_Push
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
bool CModulePlugin_LibCore::ModulePlugin_LibCore_Push(XNETHANDLE* pxhModule, LPCXSTR lpszPluginFile, XPVOID lParam)
{
    ModulePlugin_IsErrorOccur = false;

    if (!BaseLib_Handle_Create(pxhModule))
    {
        ModulePlugin_IsErrorOccur = true;
        ModulePlugin_dwErrorCode = BaseLib_GetLastError();
        return false;
    }
    if (!ModulePlugin_LibCore_Add(*pxhModule, lpszPluginFile, lParam))
    {
        return false;
    }
    return true;
}
/********************************************************************
函数名称：ModulePlugin_LibCore_Exec
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
bool CModulePlugin_LibCore::ModulePlugin_LibCore_Exec(XNETHANDLE xhModule, XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBufer /* = NULL */, int nMsgLen /* = 0 */)
{
    ModulePlugin_IsErrorOccur = false;

    st_csStl.lock_shared();
	//执行指定插件函数
	unordered_map<XNETHANDLE, PLUGINCORE_FRAMEWORK>::const_iterator stl_MapIterator = stl_MapFrameWork.find(xhModule);
	if (stl_MapIterator == stl_MapFrameWork.end())
	{
		ModulePlugin_IsErrorOccur = true;
		ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_NOTFOUND;
		st_csStl.unlock_shared();
		return false;
	}
    if (!stl_MapIterator->second.fpCall_PluginCore_Call(pppHDRList, nListCount, pInt_HTTPCode, ptszMsgBuffer, pInt_MsgLen, lpszMsgBufer, nMsgLen))
	{
		ModulePlugin_IsErrorOccur = true;
		ModulePlugin_dwErrorCode = stl_MapIterator->second.fpCall_PluginCore_GetLastError();
		st_csStl.unlock_shared();
		return false;
	}
    st_csStl.unlock_shared();

    return true;
}
/********************************************************************
函数名称：ModulePlugin_LibCore_Destroy
函数功能：销毁插件核心并且清理资源
返回值
  类型：逻辑型
  意思：是否成功销毁
备注：
*********************************************************************/
bool CModulePlugin_LibCore::ModulePlugin_LibCore_Destroy()
{
    ModulePlugin_IsErrorOccur = false;

    //判断是否初始化
    if (!bIsInit)
    {
        return true;
    }
    bIsInit = false;
    //清理STL元素空间
    st_csStl.lock();
    unordered_map<XNETHANDLE, PLUGINCORE_FRAMEWORK>::iterator stl_MapIterator = stl_MapFrameWork.begin();
    for (; stl_MapIterator != stl_MapFrameWork.end(); stl_MapIterator++)
    {
        stl_MapIterator->second.fpCall_PluginCore_UnInit();
#ifdef _MSC_BUILD
        FreeLibrary(stl_MapIterator->second.mhFile);
#else
        dlclose(stl_MapIterator->second.mhFile);
#endif
    }
    stl_MapFrameWork.clear();
    st_csStl.unlock();
    return true;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModulePlugin_LibCore_Add
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
bool CModulePlugin_LibCore::ModulePlugin_LibCore_Add(XNETHANDLE xhNet, LPCXSTR lpszPluginFile, XPVOID lParam)
{
    ModulePlugin_IsErrorOccur = false;

    if (NULL == lpszPluginFile)
    {
        ModulePlugin_IsErrorOccur = true;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_PARAMENT;
        return false;
    }
    PLUGINCORE_FRAMEWORK st_FrameWork;
    st_FrameWork.mhFile = 0;
    memset(st_FrameWork.tszModuleFile, '\0', sizeof(st_FrameWork.tszModuleFile));
    //打开一个模块
#ifdef _MSC_BUILD
    st_FrameWork.mhFile = LoadLibraryA(lpszPluginFile);
#else
    st_FrameWork.mhFile = dlopen(lpszPluginFile, RTLD_LAZY);
#endif
    if (NULL == st_FrameWork.mhFile)
    {
        ModulePlugin_IsErrorOccur = true;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_OPENDL;
        return false;
    }
    //开始查找模块中的函数
#ifdef _MSC_BUILD
    st_FrameWork.fpCall_PluginCore_Init = (FPCall_PluginCore_Init)GetProcAddress(st_FrameWork.mhFile, "PluginCore_Init");
#else
    * (void**)(&st_FrameWork.fpCall_PluginCore_Init) = dlsym(st_FrameWork.mhFile, _X("PluginCore_Init"));
#endif
    if (NULL == st_FrameWork.fpCall_PluginCore_Init)
    {
#ifdef _MSC_BUILD
        FreeLibrary(st_FrameWork.mhFile);
#else
        dlclose(st_FrameWork.mhFile);
#endif
        ModulePlugin_IsErrorOccur = true;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_FPINIT;
        return false;
    }
#ifdef _MSC_BUILD
    st_FrameWork.fpCall_PluginCore_UnInit = (FPCall_PluginCore_UnInit)GetProcAddress(st_FrameWork.mhFile, "PluginCore_UnInit");
#else
    * (void**)(&st_FrameWork.fpCall_PluginCore_UnInit) = dlsym(st_FrameWork.mhFile, _X("PluginCore_UnInit"));
#endif
    if (NULL == st_FrameWork.fpCall_PluginCore_UnInit)
    {
#ifdef _MSC_BUILD
        FreeLibrary(st_FrameWork.mhFile);
#else
        dlclose(st_FrameWork.mhFile);
#endif
        ModulePlugin_IsErrorOccur = true;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_FPUNINIT;
        return false;
    }
#ifdef _MSC_BUILD
    st_FrameWork.fpCall_PluginCore_Call = (FPCall_PluginCore_Call)GetProcAddress(st_FrameWork.mhFile, "PluginCore_Call");
#else
    * (void**)(&st_FrameWork.fpCall_PluginCore_Call) = dlsym(st_FrameWork.mhFile, _X("PluginCore_Call"));
#endif
    if (NULL == st_FrameWork.fpCall_PluginCore_Call)
    {
#ifdef _MSC_BUILD
        FreeLibrary(st_FrameWork.mhFile);
#else
        dlclose(st_FrameWork.mhFile);
#endif
        ModulePlugin_IsErrorOccur = true;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_FPCALL;
        return false;
    }
#ifdef _MSC_BUILD
    st_FrameWork.fpCall_PluginCore_GetLastError = (FPCall_PluginCore_GetLastError)GetProcAddress(st_FrameWork.mhFile, _X("PluginCore_GetLastError"));
#else
    * (void**)(&st_FrameWork.fpCall_PluginCore_GetLastError) = dlsym(st_FrameWork.mhFile, _X("PluginCore_GetLastError"));
#endif
    if (NULL == st_FrameWork.fpCall_PluginCore_GetLastError)
    {
#ifdef _MSC_BUILD
        FreeLibrary(st_FrameWork.mhFile);
#else
        dlclose(st_FrameWork.mhFile);
#endif
        ModulePlugin_IsErrorOccur = true;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_FPERROR;
        return false;
    }
    //初始化内部模块
    if (!st_FrameWork.fpCall_PluginCore_Init(lParam))
    {
#ifdef _MSC_BUILD
        FreeLibrary(st_FrameWork.mhFile);
#else
        dlclose(st_FrameWork.mhFile);
#endif
        ModulePlugin_IsErrorOccur = true;
        ModulePlugin_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PLUGIN_INIT;
        return false;
    }
    _tcsxcpy(st_FrameWork.tszModuleFile, lpszPluginFile);

    //添加模块属性到STL函数中
    st_csStl.lock();
    stl_MapFrameWork.insert(make_pair(xhNet, st_FrameWork));
    st_csStl.unlock();
    return true;
}