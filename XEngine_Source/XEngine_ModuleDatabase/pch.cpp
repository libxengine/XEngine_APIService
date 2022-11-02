#include "pch.h"
#include "ModuleDatabase_IDCard/ModuleDatabase_IDCard.h"
#include "ModuleDatabase_IPInfo/ModuleDatabase_IPInfo.h"
#include "ModuleDatabase_Phone/ModuleDatabase_Phone.h"
#include "ModuleDatabase_Bank/ModuleDatabase_Bank.h"
#include "ModuleDatabase_ZIPCode/ModuleDatabase_ZIPCode.h"
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
CModuleDatabase_Phone m_Phone;
CModuleDatabase_Bank m_Bank;
CModuleDatabase_ZIPCode m_ZIPCode;
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
/************************************************************************/
/*                         导出的电话号码信息函数                       */
/************************************************************************/
extern "C" BOOL ModuleDatabase_Phone_Init(LPCTSTR lpszSQLFile)
{
	return m_Phone.ModuleDatabase_Phone_Init(lpszSQLFile);
}
extern "C" BOOL ModuleDatabase_Phone_Destory()
{
	return m_Phone.ModuleDatabase_Phone_Destory();
}
extern "C" BOOL ModuleDatabase_Phone_Query(LPCTSTR lpszPhoneNumber, XENGINE_PHONEINFO * pSt_PhoneInfo)
{
	return m_Phone.ModuleDatabase_Phone_Query(lpszPhoneNumber, pSt_PhoneInfo);
}
/************************************************************************/
/*                         导出的银行卡信息函数                         */
/************************************************************************/
extern "C" BOOL ModuleDatabase_Bank_Init(LPCTSTR lpszSQLFile)
{
	return m_Bank.ModuleDatabase_Bank_Init(lpszSQLFile);
}
extern "C" BOOL ModuleDatabase_Bank_Destory()
{
	return m_Bank.ModuleDatabase_Bank_Destory();
}
extern "C" BOOL ModuleDatabase_Bank_Query(XENGINE_BANKINFO * pSt_BankInfo)
{
	return m_Bank.ModuleDatabase_Bank_Query(pSt_BankInfo);
}
/************************************************************************/
/*                         导出的邮编行政信息函数                       */
/************************************************************************/
extern "C" BOOL ModuleDatabase_ZIPCode_Init(LPCTSTR lpszSQLFile)
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_Init(lpszSQLFile);
}
extern "C" BOOL ModuleDatabase_ZIPCode_Destory()
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_Destory();
}
extern "C" BOOL ModuleDatabase_ZIPCode_QueryZIPCode(XENGINE_ZIPINFO * pSt_ZIPInfo)
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_QueryZIPCode(pSt_ZIPInfo);
}
extern "C" BOOL ModuleDatabase_ZIPCode_QueryName(XENGINE_ZIPINFO * pSt_ZIPInfo)
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_QueryName(pSt_ZIPInfo);
}