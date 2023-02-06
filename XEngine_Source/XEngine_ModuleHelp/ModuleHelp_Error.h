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
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_ISEXIST 0xD2001         //用户已经存在
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_MALLOC 0xD2002          //申请内存失败
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_PARAMENT 0xD2003        //获取用户信息失败,参数错误
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND 0xD2004        //没有找到用户
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTPUBADDRR 0xD2005     //公网IP地址没有找到
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTPRIADDR 0xD2006      //私有网络IP地址没有找到
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOLIST 0xD2007          //没有数据存在
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_THREAD 0xD2008          //创建线程失败
//////////////////////////////////////////////////////////////////////////
//                        分布式锁错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_PARAMENT 0xD3001       //参数错误
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_MALLOC 0xD3002         //申请内存失败
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_EXIST 0xD3003          //已经存在
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_NOTFOUND 0xD3004       //没有找到锁
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_LOCKED 0xD3005         //已锁定
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_STATUS 0xD3006         //解锁状态错误
//////////////////////////////////////////////////////////////////////////
//                        二维码错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_PARAMENT 0xD4001      //参数错误
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_FAILED 0xD4002        //处理失败
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_WRITE 0xD4003         //写入失败
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_EMPTY 0xD4004         //空的数据
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_NOTQR 0xD4005         //不是QR
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_NOTSUPPORT 0xD4006    //暂时不支持
//////////////////////////////////////////////////////////////////////////
//                       套接字测试错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_PARAMRT 0xD5001   //参数错误
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_MALLOC 0xD5002    //申请内存失败
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_THREAD 0xD5003    //创建线程失败
#define ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_NOTFOUND 0xD5004  //没有找到