#include "pch.h"
#include "ModuleDatabase_SQlite/ModuleDatabase_SQlite.h"
/********************************************************************
//    Created:     2022/02/28  13:26:15
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleDatabase\pch.cpp
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleDatabase
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出函数实现
//    History:
*********************************************************************/
DWORD DBModule_IsErrorOccur = FALSE;
BOOL DBModule_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleDatabase_SQlite m_DBSQlite;
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModuleDB_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return DBModule_dwErrorCode;
}
/************************************************************************/
/*                         导出的数据库操作函数                         */
/************************************************************************/
extern "C" BOOL ModuleDatabase_SQlite_Init(LPCTSTR lpszSQLFile)
{
	return m_DBSQlite.ModuleDatabase_SQlite_Init(lpszSQLFile);
}
extern "C" BOOL ModuleDatabase_SQlite_Destory()
{
	return m_DBSQlite.ModuleDatabase_SQlite_Destory();
}
extern "C" BOOL ModuleDatabase_SQlite_IPV4Query(XENGINE_IPADDRINFO * pSt_IPAddrInfo, LPCTSTR lpszIPAddr)
{
	return m_DBSQlite.ModuleDatabase_SQlite_IPV4Query(pSt_IPAddrInfo, lpszIPAddr);
}
extern "C" BOOL ModuleDatabase_SQlite_IPV6Query(XENGINE_IPADDRINFO * pSt_IPAddrInfo, LPCTSTR lpszIPAddr)
{
	return m_DBSQlite.ModuleDatabase_SQlite_IPV6Query(pSt_IPAddrInfo, lpszIPAddr);
}