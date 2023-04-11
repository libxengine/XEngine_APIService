#include "pch.h"
#include "ModuleDatabase_IDCard/ModuleDatabase_IDCard.h"
#include "ModuleDatabase_Bank/ModuleDatabase_Bank.h"
#include "ModuleDatabase_ZIPCode/ModuleDatabase_ZIPCode.h"
#include "ModuleDatabase_XLog/ModuleDatabase_XLog.h"
#include "ModuleDatabase_ShortLink/ModuleDatabase_ShortLink.h"
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
XLONG DBModule_IsErrorOccur = XFALSE;
XBOOL DBModule_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleDatabase_IDCard m_IDCard;
CModuleDatabase_Bank m_Bank;
CModuleDatabase_ZIPCode m_ZIPCode;
CModuleDatabase_XLog m_XLog;
CModuleDatabase_ShortLink m_ShortLink;
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleDB_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return DBModule_dwErrorCode;
}
/************************************************************************/
/*                         导出的身份证地址操作函数                     */
/************************************************************************/
extern "C" XBOOL ModuleDatabase_IDCard_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_IDCard.ModuleDatabase_IDCard_Init(pSt_DBConnector);
}
extern "C" XBOOL ModuleDatabase_IDCard_Destory()
{
	return m_IDCard.ModuleDatabase_IDCard_Destory();
}
extern "C" XBOOL ModuleDatabase_IDCard_QueryRegion(XENGINE_IDREGION * pSt_IDRegion, XENGINE_IDCARDINFO * pSt_IDInfo)
{
	return m_IDCard.ModuleDatabase_IDCard_QueryRegion(pSt_IDRegion, pSt_IDInfo);
}
/************************************************************************/
/*                         导出的银行卡信息函数                         */
/************************************************************************/
extern "C" XBOOL ModuleDatabase_Bank_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_Bank.ModuleDatabase_Bank_Init(pSt_DBConnector);
}
extern "C" XBOOL ModuleDatabase_Bank_Destory()
{
	return m_Bank.ModuleDatabase_Bank_Destory();
}
extern "C" XBOOL ModuleDatabase_Bank_Query(XENGINE_BANKINFO * pSt_BankInfo)
{
	return m_Bank.ModuleDatabase_Bank_Query(pSt_BankInfo);
}
/************************************************************************/
/*                         导出的邮编行政信息函数                       */
/************************************************************************/
extern "C" XBOOL ModuleDatabase_ZIPCode_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_Init(pSt_DBConnector);
}
extern "C" XBOOL ModuleDatabase_ZIPCode_Destory()
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_Destory();
}
extern "C" XBOOL ModuleDatabase_ZIPCode_QueryZIPCode(XENGINE_ZIPINFO * pSt_ZIPInfo)
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_QueryZIPCode(pSt_ZIPInfo);
}
extern "C" XBOOL ModuleDatabase_ZIPCode_QueryName(XENGINE_ZIPINFO * pSt_ZIPInfo)
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_QueryName(pSt_ZIPInfo);
}
/************************************************************************/
/*                         导出的日志服务数据库函数                     */
/************************************************************************/
extern "C" XBOOL ModuleDatabase_XLog_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_XLog.ModuleDatabase_XLog_Init(pSt_DBConnector);
}
extern "C" XBOOL ModuleDatabase_XLog_Destory()
{
	return m_XLog.ModuleDatabase_XLog_Destory();
}
extern "C" XBOOL ModuleDatabase_XLog_Create(LPCXSTR lpszTableName)
{
	return m_XLog.ModuleDatabase_XLog_Create(lpszTableName);
}
extern "C" XBOOL ModuleDatabase_XLog_Insert(XENGINE_XLOGINFO * pSt_XLogInfo)
{
	return m_XLog.ModuleDatabase_XLog_Insert(pSt_XLogInfo);
}
extern "C" XBOOL ModuleDatabase_XLog_Query(XENGINE_XLOGINFO * **pppSt_XLogInfo, int* pInt_ListCount, LPCXSTR lpszTableName, LPCXSTR lpszTimeStart, LPCXSTR lpszTimeEnd)
{
	return m_XLog.ModuleDatabase_XLog_Query(pppSt_XLogInfo, pInt_ListCount, lpszTableName, lpszTimeStart, lpszTimeEnd);
}
extern "C" XBOOL ModuleDatabase_XLog_Delete(LPCXSTR lpszTableName)
{
	return m_XLog.ModuleDatabase_XLog_Delete(lpszTableName);
}
/************************************************************************/
/*                         导出的短连接数据库函数                       */
/************************************************************************/
extern "C" XBOOL ModuleDatabase_ShortLink_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_ShortLink.ModuleDatabase_ShortLink_Init(pSt_DBConnector);
}
extern "C" XBOOL ModuleDatabase_ShortLink_Destory()
{
	return m_ShortLink.ModuleDatabase_ShortLink_Destory();
}
extern "C" XBOOL ModuleDatabase_ShortLink_Insert(XENGINE_SHORTLINK * pSt_SLinkInfo)
{
	return m_ShortLink.ModuleDatabase_ShortLink_Insert(pSt_SLinkInfo);
}
extern "C" XBOOL ModuleDatabase_ShortLink_Query(XENGINE_SHORTLINK * pSt_SLinkInfo)
{
	return m_ShortLink.ModuleDatabase_ShortLink_Query(pSt_SLinkInfo);
}
extern "C" XBOOL ModuleDatabase_ShortLink_Delete(XENGINE_SHORTLINK * pSt_SLinkInfo)
{
	return m_ShortLink.ModuleDatabase_ShortLink_Delete(pSt_SLinkInfo);
}