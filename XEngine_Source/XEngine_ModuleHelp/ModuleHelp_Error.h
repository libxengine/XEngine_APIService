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