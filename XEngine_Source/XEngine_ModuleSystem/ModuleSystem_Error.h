#pragma once
/********************************************************************
//    Created:     2023/09/06  13:51:12
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem\ModuleHelp_Error.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem
//    File Base:   ModuleHelp_Error
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     模块导出错误
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                            系统函数错误表
//////////////////////////////////////////////////////////////////////////
#define ERROR_MODULE_SYSTEM_API_PARAMENT 0xF0001                          //参数错误
#define ERROR_MODULE_SYSTEM_API_SYSENABLE 0xF0002                         //自动启动服务启用失败
#define ERROR_MODULE_SYSTEM_API_SYSDISABLE 0xF0003                        //禁用自动启动服务失败
#define ERROR_MODULE_SYSTEM_API_GETFILENAME 0xF0004                       //获取自身文件名失败
#define ERROR_MODULE_SYSTEM_API_COINIT 0xF0005                            //打开OLD失败
#define ERROR_MODULE_SYSTEM_API_QUERY 0xF0006                             //查询接口失败