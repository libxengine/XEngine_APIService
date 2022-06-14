#pragma once
/********************************************************************
//    Created:     2022/03/04  13:33:35
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Error.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp
//    File Base:   ModuleHelp_Error
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出的错误
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                        导出的身份证错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_IDCARD_PARAMENT 0xD0001     //参数错误
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_IDCARD_FMT 0xD0002          //格式错误
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_IDCARD_SUM 0xD0003          //校验码错误
//////////////////////////////////////////////////////////////////////////
//                        导出的语言转换错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_LANGUAGE_PARAMENT 0xD1001   //参数错误
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_LANGUAGE_FAILED 0xD1002     //处理失败
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_LANGUAGE_NOTSUPPORT 0xD1003 //不支持的类型
//////////////////////////////////////////////////////////////////////////
//                        节点管理器错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_ISEXIST 0xB0E0001       //用户已经存在
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_MALLOC 0xB0E0002        //申请内存失败
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_PARAMENT 0xB0E0010      //获取用户信息失败,参数错误
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND 0xB0E0011      //没有找到用户
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTPUBADDRR 0xB0E0051   //公网IP地址没有找到
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTPRIADDR 0xB0E0052    //私有网络IP地址没有找到
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOLIST 0xB0E0053        //没有数据存在
