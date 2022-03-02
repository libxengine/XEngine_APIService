#pragma once
/********************************************************************
//    Created:     2022/02/28  10:16:15
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleDatabase\ModuleDB_Define.h
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleDatabase
//    File Base:   ModuleDB_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     数据库操作导出
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModuleDB_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                         导出的数据库操作函数                         */
/************************************************************************/
/********************************************************************
函数名称：ModuleDatabase_SQlite_Init
函数功能：初始化SQLITE文件系统
 参数.一：lpszSQLFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要操作的SQL文件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleDatabase_SQlite_Init(LPCTSTR lpszSQLFile);
/********************************************************************
函数名称：ModuleDatabase_SQlite_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleDatabase_SQlite_Destory();
/********************************************************************
函数名称：ModuleDatabase_SQlite_IPV4Query
函数功能：查询文件信息
 参数.一：pSt_IPAddrInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出IP地址信息结构
 参数.二：lpszIPAddr
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要查询的IPV4
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleDatabase_SQlite_IPV4Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo, LPCTSTR lpszIPAddr);
/********************************************************************
函数名称：ModuleDatabase_SQlite_IPV6Query
函数功能：查询IPV6地址信息
 参数.一：pSt_IPAddrInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出IP地址信息结构
 参数.二：lpszIPAddr
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要查询的地址
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleDatabase_SQlite_IPV6Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo, LPCTSTR lpszIPAddr);