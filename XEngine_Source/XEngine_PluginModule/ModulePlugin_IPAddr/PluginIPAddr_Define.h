#pragma once
/********************************************************************
//    Created:     2023/01/10  11:24:55
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_IPAddr\PluginIPAddr_Define.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_IPAddr
//    File Base:   PluginIPAddr_Define
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     IP地址操作导出定义
//    History:
*********************************************************************/
//IP地址信息
typedef struct
{
	XCHAR tszIPAddr[128];       //IP地址
	XCHAR tszIPCountry[128];    //国家/地区
	XCHAR tszIPProvince[128];   //省/自治区
	XCHAR tszIPCity[128];       //市
	XCHAR tszIPCounty[128];     //县
	XCHAR tszIPAddress[128];    //详细地址
	XCHAR tszIPISP[128];        //运营商
}XENGINE_IPADDRINFO;
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD PluginCore_GetLastError();
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