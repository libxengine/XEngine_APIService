#pragma once
/********************************************************************
//    Created:     2022/02/28  14:21:45
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Define.h
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol
//    File Base:   ModuleProtocol_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出协议模块定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModuleProtocol_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                         导出的数据库操作函数                         */
/************************************************************************/
/********************************************************************
函数名称：ModuleProtocol_Packet_IPQuery
函数功能：IP地址查询打包协议
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_IPAddrInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的IP地址信息
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.五：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleProtocol_Packet_IPQuery(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IPADDRINFO * pSt_IPAddrInfo, int nCode = 0, LPCTSTR lpszMsgBuffer = NULL);
/********************************************************************
函数名称：ModuleProtocol_Packet_IPQuery2
函数功能：IP查询打包函数另一种方式
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_IPAddrInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的IP地址信息
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleProtocol_Packet_IPQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IPADDRINFO* pSt_IPAddrInfo, int nCode = 0);