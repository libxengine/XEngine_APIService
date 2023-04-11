#pragma once
/********************************************************************
//    Created:     2023/01/10  11:39:12
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\PluginPhone_Define.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone
//    File Base:   PluginPhone_Define
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     电话号码查询导出
//    History:
*********************************************************************/
//电话号码类型
typedef enum
{
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_UNKNOWN = 0,	    // 未知，查找失败
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CMCC,			// 中国移动
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CUCC,			// 中国联通
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CTCC,			// 中国电信
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CTCC_V,			// 电信虚拟运营商
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CUCC_V,			// 联通虚拟运营商
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CMCC_V			// 移动虚拟运营商
}ENUM_XENGINE_APISERVICE_PHONE_TYPE;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	XCHAR tszProvincer[64];     //省/自治区/直辖市
	XCHAR tszCity[64];          //市/区     
	__int64x nPhoneNumber;      //电话号码
	int nZipCode;               //邮编
	int nAreaCode;              //区号
	ENUM_XENGINE_APISERVICE_PHONE_TYPE enPhoneType;  //电话号码类型
}XENGINE_PHONEINFO;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG PluginCore_GetLastError();
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
/********************************************************************
函数名称：PluginCore_Init
函数功能：初始化插件模块
 参数.一：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：N
  意思：自定义参数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" XBOOL PluginCore_Init(XPVOID lParam = NULL);
/********************************************************************
函数名称：PluginCore_UnInit
函数功能：卸载插件
返回值
  类型：无
  意思：
备注：
*********************************************************************/
extern "C" void PluginCore_UnInit();
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" XBOOL PluginCore_Call(XCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer = NULL, int nMsgLen = 0);