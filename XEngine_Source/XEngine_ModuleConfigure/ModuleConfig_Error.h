#pragma once
/********************************************************************
//    Created:     2021/12/02  16:15:47
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure\ModuleConfig_Error.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure
//    File Base:   ModuleConfig_Error
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     配置模块导出错误
//    History:
*********************************************************************/
#define ERROR_MODULE_CONFIGURE_JSON_PARAMENT 0xA0001                 //参数错误
#define ERROR_MODULE_CONFIGURE_JSON_OPENFILE 0xA0002                 //打开文件失败
#define ERROR_MODULE_CONFIGURE_JSON_PARSE 0xA0003                    //解析JSON失败
#define ERROR_MODULE_CONFIGURE_JSON_XMAX 0xA0004                     //读取XMAX配置失败 
#define ERROR_MODULE_CONFIGURE_JSON_XTIME 0xA0005                    //读取XTIME配置失败
#define ERROR_MODULE_CONFIGURE_JSON_XLOG 0xA0006                     //读取XHANDLE配置失败
#define ERROR_MODULE_CONFIGURE_JSON_XDB 0xA0007                      //数据库配置错误
#define ERROR_MODULE_CONFIGURE_JSON_XPLUGIN 0xA0008                  //插件配置错误
#define ERROR_MODULE_CONFIGURE_JSON_XVER 0xA0009                     //版本配置文件读取错误
#define ERROR_MODULE_CONFIGURE_JSON_MALLOC 0xA000A                   //申请内存失败
#define ERROR_MODULE_CONFIGURE_JSON_XAPI 0xA000B                     //API配置失败
#define ERROR_MODULE_CONFIGURE_JSON_XCONFIG 0xA000C                  //配置文件配置加载失败
#define ERROR_MODULE_CONFIGURE_JSON_XSLINK 0xA000D                   //短连接配置错误
#define ERROR_MODULE_CONFIGURE_JSON_XVERICATION 0xA000E              //验证配置错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_MODULE_CONFIGURE_FILE_PARAMENT 0xA1001                 //参数错误
#define ERROR_MODULE_CONFIGURE_FILE_OPENFILE 0xA1002                 //打开文件失败
#define ERROR_MODULE_CONFIGURE_FILE_PARSE 0xA1003                    //解析错误
#define ERROR_MODULE_CONFIGURE_FILE_BASE 0xA1004                     //基础信息不存在
#define ERROR_MODULE_CONFIGURE_JSON_PLUGIN 0xA1005                   //插件信息不存在