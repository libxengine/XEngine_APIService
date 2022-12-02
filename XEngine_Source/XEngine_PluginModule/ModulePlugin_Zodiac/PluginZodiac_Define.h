#pragma once
/********************************************************************
//    Created:     2022/04/21  10:50:25
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Zodiac\PluginZodiac_Define.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Zodiac
//    File Base:   PluginZodiac_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     生肖插件导出定义
//    History:
*********************************************************************/
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
extern "C" BOOL PluginCore_Init(LPVOID lParam = NULL);
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
extern "C" BOOL PluginCore_Call(TCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBuffer = NULL, int nMsgLen = 0);