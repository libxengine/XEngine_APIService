#include "pch.h"
#include "ModuleDatabase_SQlite.h"
/********************************************************************
//    Created:     2022/02/28  10:14:17
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_SQlite\ModuleDatabase_SQlite.cpp
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_SQlite
//    File Base:   ModuleDatabase_SQlite
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     sqlite操作
//    History:
*********************************************************************/
CModuleDatabase_SQlite::CModuleDatabase_SQlite()
{
}
CModuleDatabase_SQlite::~CModuleDatabase_SQlite()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
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
BOOL CModuleDatabase_SQlite::ModuleDatabase_SQlite_Init(LPCTSTR lpszSQLFile)
{
	DBModule_IsErrorOccur = FALSE;
	//打开数据库
	if (!DataBase_SQLite_Open(&xhSQL, lpszSQLFile))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_SQlite_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleDatabase_SQlite::ModuleDatabase_SQlite_Destory()
{
	DBModule_IsErrorOccur = FALSE;

	DataBase_SQLite_Close(xhSQL);
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_SQlite_IPV4Query
函数功能：查询IPV4地址信息
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
BOOL CModuleDatabase_SQlite::ModuleDatabase_SQlite_IPV4Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo, LPCTSTR lpszIPAddr)
{
    DBModule_IsErrorOccur = FALSE;

    if ((NULL == pSt_IPAddrInfo) && (NULL == lpszIPAddr))
    {
        DBModule_IsErrorOccur = TRUE;
        DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_QUERY_PARAMENT;
        return FALSE;
    }
    //查询
    int nLine = 0;
    int nRow = 0;
    TCHAR** pptszResult;
    TCHAR tszSQLStatement[1024];
	struct in_addr st_Addr;

    memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	memset(&st_Addr, '\0', sizeof(struct in_addr));

	inet_pton(AF_INET, lpszIPAddr, &st_Addr);

	_stprintf(tszSQLStatement, _T("SELECT * FROM `iprange_info` WHERE '%u' BETWEEN ip_start_num AND ip_end_num"), htonl(st_Addr.s_addr));
	if (!DataBase_SQLite_GetTable(xhSQL, tszSQLStatement, &pptszResult, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_QUERY_NOTFOUND;
		return FALSE;
	}
	_tcscpy(pSt_IPAddrInfo->tszIPStart, pptszResult[nRow + 1]);
	_tcscpy(pSt_IPAddrInfo->tszIPEnd, pptszResult[nRow + 3]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPAddr, lpszIPAddr);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPCountry, pptszResult[nRow + 5]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPProvince, pptszResult[nRow + 6]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPCity, pptszResult[nRow + 7]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPCounty, pptszResult[nRow + 8]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPAddress, pptszResult[nRow + 9]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPISP, pptszResult[nRow + 10]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPTime, pptszResult[nRow + 11]);

	DataBase_SQLite_FreeTable(pptszResult);
	return TRUE;
}
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
BOOL CModuleDatabase_SQlite::ModuleDatabase_SQlite_IPV6Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo, LPCTSTR lpszIPAddr)
{
	DBModule_IsErrorOccur = FALSE;

	if ((NULL == pSt_IPAddrInfo) && (NULL == lpszIPAddr))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_QUERY_PARAMENT;
		return FALSE;
	}
	//查询
	int nLine = 0;
	int nRow = 0;
	TCHAR** pptszResult;
	TCHAR tszSQLStatement[1024];
	TCHAR tszIPV6Addr[128];
	XENGINE_LIBADDR st_LibAddr;

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	memset(tszIPV6Addr, '\0', sizeof(tszIPV6Addr));
	memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));

	BaseLib_OperatorIPAddr_IsIPV6Addr(lpszIPAddr, &st_LibAddr);
	BaseLib_OperatorIPAddr_ExpIPV6Addr(&st_LibAddr, tszIPV6Addr, TRUE, FALSE);

	_stprintf(tszSQLStatement, _T("SELECT * FROM `ipv6_range_info` WHERE X'%s' BETWEEN ip_start_num AND ip_end_num"), tszIPV6Addr);
	if (!DataBase_SQLite_GetTable(xhSQL, tszSQLStatement, &pptszResult, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_QUERY_NOTFOUND;
		return FALSE;
	}
	_tcscpy(pSt_IPAddrInfo->tszIPStart, pptszResult[nRow + 1]);
	_tcscpy(pSt_IPAddrInfo->tszIPEnd, pptszResult[nRow + 3]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPAddr, lpszIPAddr);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPCountry, pptszResult[nRow + 5]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPProvince, pptszResult[nRow + 6]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPCity, pptszResult[nRow + 7]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPCounty, pptszResult[nRow + 8]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPAddress, pptszResult[nRow + 9]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPISP, pptszResult[nRow + 10]);
	_tcscpy(pSt_IPAddrInfo->st_IPAddrInfo.tszIPTime, pptszResult[nRow + 11]);

	DataBase_SQLite_FreeTable(pptszResult);
	return TRUE;
}