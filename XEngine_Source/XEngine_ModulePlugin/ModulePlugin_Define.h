#pragma once
/********************************************************************
//    Created:     2022/04/20  17:22:16
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin\ModulePlugin_Define.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModulePlugin
//    File Base:   ModulePlugin_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     插件导出定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModulePlugin_GetLastError(int* pInt_SysError = NULL);
/*********************************************************************************
*                        插件框架导出函数定义                                    *
*********************************************************************************/
/********************************************************************
函数名称：ModulePlugin_Core_Init
函数功能：初始化插件核心系统
返回值
  类型：逻辑型
  意思：是否成功初始化
备注：
*********************************************************************/
extern "C" BOOL ModulePlugin_Core_Init();
/********************************************************************
函数名称：ModulePlugin_Core_Push
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
extern "C" BOOL ModulePlugin_Core_Push(XNETHANDLE * pxhNet, LPCSTR lpszPluginFile, LPVOID lParam = NULL);
/********************************************************************
函数名称：ModulePlugin_Core_Exec
函数功能：执行插件功能
 参数.一：xhModule
  In/Out：In
  类型：插件句柄
  可空：Y
  意思：要执行的插件句柄，为空执行全部
 参数.二：lPAaram
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：可作为输入输出参数
 参数.三：lPBaram
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：可作为输入输出参数
返回值
  类型：逻辑型
  意思：是否执行成功
备注：参数要么传递NULL，要么传递值，由用户来判断参数是否可用
*********************************************************************/
extern "C" BOOL ModulePlugin_Core_Exec(XNETHANDLE xhModule = 0, LPVOID lPAaram = NULL, LPVOID lPBaram = NULL);
/********************************************************************
函数名称：ModulePlugin_Core_Destroy
函数功能：销毁插件核心并且清理资源
返回值
  类型：逻辑型
  意思：是否成功销毁
备注：
*********************************************************************/
extern "C" BOOL ModulePlugin_Core_Destroy();
/*********************************************************************************
*                        加载器导出函数定义                                      *
*********************************************************************************/
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
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModulePlugin_Loader_Insert(LPCTSTR lpszModuleMethod, LPCTSTR lpszModuleName);
/********************************************************************
函数名称：ModulePlugin_Loader_Exec
函数功能：执行一次插件
 参数.一：lpszMethodName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要执行的方法
 参数.二：lAParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：自定义参数
 参数.三：lAParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：自定义参数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModulePlugin_Loader_Exec(LPCTSTR lpszMethodName, LPVOID lAParam, LPVOID lBParam);
/********************************************************************
函数名称：ModulePlugin_Loader_Destory
函数功能：销毁加载器
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModulePlugin_Loader_Destory();