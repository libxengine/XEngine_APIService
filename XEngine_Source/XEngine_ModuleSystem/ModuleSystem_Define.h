#pragma once
/********************************************************************
//    Created:     2023/09/06  13:50:57
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem\ModuleHelp_Define.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem
//    File Base:   ModuleHelp_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     模块导出定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                        导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleSystem_GetLastError(int* pInt_ErrorCode = NULL);
/************************************************************************/
/*                        系统函数库                                    */
/************************************************************************/
/********************************************************************
函数名称：ModuleSystem_API_AutoStart
函数功能：注册自动启动与服务函数
 参数.一：bIsAuto
  In/Out：In
  类型：逻辑型
  可空：Y
  意思：是否让其自动启动，默认为真，自动启动
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleSystem_API_AutoStart(bool bIsAuto = true);