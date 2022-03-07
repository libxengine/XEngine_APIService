#include "pch.h"
#include "ModuleDatabase_IDCard/ModuleDatabase_IDCard.h"
#include "ModuleDatabase_IPInfo/ModuleDatabase_IPInfo.h"
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
CModuleDatabase_IPInfo m_IPAddr;
CModuleDatabase_IDCard m_IDCard;
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
/*                         导出的IP地址操作函数                         */
/************************************************************************/
extern "C" BOOL ModuleDatabase_IPInfo_Init(LPCTSTR lpszSQLFile)
{
	return m_IPAddr.ModuleDatabase_IPInfo_Init(lpszSQLFile);
}
extern "C" BOOL ModuleDatabase_IPInfo_Destory()
{
	return m_IPAddr.ModuleDatabase_IPInfo_Destory();
}
extern "C" BOOL ModuleDatabase_IPInfo_IPV4Query(XENGINE_IPADDRINFO * pSt_IPAddrInfo, LPCTSTR lpszIPAddr)
{
	return m_IPAddr.ModuleDatabase_IPInfo_IPV4Query(pSt_IPAddrInfo, lpszIPAddr);
}
extern "C" BOOL ModuleDatabase_IPInfo_IPV6Query(XENGINE_IPADDRINFO * pSt_IPAddrInfo, LPCTSTR lpszIPAddr)
{
	return m_IPAddr.ModuleDatabase_IPInfo_IPV6Query(pSt_IPAddrInfo, lpszIPAddr);
}
/************************************************************************/
/*                         导出的身份证地址操作函数                     */
/************************************************************************/
extern "C" BOOL ModuleDatabase_IDCard_Init(LPCTSTR lpszSQLFile)
{
	return m_IDCard.ModuleDatabase_IDCard_Init(lpszSQLFile);
}
extern "C" BOOL ModuleDatabase_IDCard_Destory()
{
	return m_IDCard.ModuleDatabase_IDCard_Destory();
}
extern "C" BOOL ModuleDatabase_IDCard_QueryRegion(XENGINE_IDREGION * pSt_IDRegion, XENGINE_IDCARDINFO * pSt_IDInfo)
{
	return m_IDCard.ModuleDatabase_IDCard_QueryRegion(pSt_IDRegion, pSt_IDInfo);
}