#pragma once
/********************************************************************
//    Created:     2022/02/28  14:21:56
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Error.h
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol
//    File Base:   ModuleProtocol_Error
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出协议模块错误
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                        导出的打包错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT 0xC0001  //初始化失败.参数错误
//////////////////////////////////////////////////////////////////////////
//                        导出的解析错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT 0xC0001   //初始化失败.参数错误
#define ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_LEN 0xC0002        //长度错误
#define ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_FMT 0xC0003        //格式错误
#define ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_JSON 0xC0004       //解析JSON失败
#define ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_VALIDATE 0xC0005   //银行卡不正确
#define ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_GETNAME 0xC0006    //获取名称失败