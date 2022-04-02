#pragma once
/********************************************************************
//    Created:     2022/03/04  13:37:09
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Define.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp
//    File Base:   ModuleHelp_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出帮助模块定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModuleHelp_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                         导出的身份证帮助函数                         */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_IDCard_CheckBirth
函数功能：检查身份证号生日
 参数.一：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要检查的身份结构
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleHelp_IDCard_CheckBirth(XENGINE_IDCARDINFO* pSt_IDInfo);
/********************************************************************
函数名称：ModuleHelp_IDCard_CheckBirth
函数功能：检查身份证的校验码是否正确
 参数.一：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要检查的身份结构
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleHelp_IDCard_CheckSum(XENGINE_IDCARDINFO* pSt_IDInfo);
/************************************************************************/
/*                         导出的语言转换帮助函数                       */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_Language_ConvertZh
函数功能：中文语言转换函数
 参数.一：lpszJsonFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的配置文件
 参数.一：lpszSourceStr
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要转换的字符串
 参数.一：ptszDestStr
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的字符串
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleHelp_Language_ConvertZh(LPCTSTR lpszJsonFile, LPCTSTR lpszSourceStr, TCHAR* ptszDestStr);
/********************************************************************
函数名称：ModuleHelp_Translation_Convert
函数功能：翻译类型转换
 参数.一：enTranslationType
  In/Out：In
  类型：枚举型
  可空：N
  意思：输入要转换的类型
 参数.二：ptszTranslationType
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的类型
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleHelp_Translation_Convert(ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE enTranslationType, TCHAR* ptszTranslationType);