#include "pch.h"
#include "ModuleDatabase_IDCard/ModuleDatabase_IDCard.h"
#include "ModuleDatabase_Bank/ModuleDatabase_Bank.h"
#include "ModuleDatabase_ZIPCode/ModuleDatabase_ZIPCode.h"
#include "ModuleDatabase_XLog/ModuleDatabase_XLog.h"
#include "ModuleDatabase_ShortLink/ModuleDatabase_ShortLink.h"
#include "ModuleDatabase_WordFilter/ModuleDatabase_WordFilter.h"
#include "ModuleDatabase_Machine/ModuleDatabase_Machine.h"
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
bool DBModule_IsErrorOccur = false;
XLONG DBModule_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleDatabase_IDCard m_IDCard;
CModuleDatabase_Bank m_Bank;
CModuleDatabase_ZIPCode m_ZIPCode;
CModuleDatabase_XLog m_XLog;
CModuleDatabase_ShortLink m_ShortLink;
CModuleDatabase_WordFilter m_WordFilter;
CModuleDatabase_Machine m_MachineInfo;
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
extern "C" bool ModuleDatabase_IDCard_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_IDCard.ModuleDatabase_IDCard_Init(pSt_DBConnector);
}
extern "C" bool ModuleDatabase_IDCard_Destory()
{
	return m_IDCard.ModuleDatabase_IDCard_Destory();
}
extern "C" bool ModuleDatabase_IDCard_QueryRegion(XENGINE_IDREGION * pSt_IDRegion, XENGINE_IDCARDINFO * pSt_IDInfo)
{
	return m_IDCard.ModuleDatabase_IDCard_QueryRegion(pSt_IDRegion, pSt_IDInfo);
}
extern "C" bool ModuleDatabase_IDCard_QueryByAddr(XENGINE_IDREGION * pSt_IDRegion, int* pInt_IDNumber)
{
	return m_IDCard.ModuleDatabase_IDCard_QueryByAddr(pSt_IDRegion, pInt_IDNumber);
}
/************************************************************************/
/*                         导出的银行卡信息函数                         */
/************************************************************************/
extern "C" bool ModuleDatabase_Bank_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_Bank.ModuleDatabase_Bank_Init(pSt_DBConnector);
}
extern "C" bool ModuleDatabase_Bank_Destory()
{
	return m_Bank.ModuleDatabase_Bank_Destory();
}
extern "C" bool ModuleDatabase_Bank_Query(XENGINE_BANKINFO * pSt_BankInfo)
{
	return m_Bank.ModuleDatabase_Bank_Query(pSt_BankInfo);
}
/************************************************************************/
/*                         导出的邮编行政信息函数                       */
/************************************************************************/
extern "C" bool ModuleDatabase_ZIPCode_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_Init(pSt_DBConnector);
}
extern "C" bool ModuleDatabase_ZIPCode_Destory()
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_Destory();
}
extern "C" bool ModuleDatabase_ZIPCode_QueryZIPCode(XENGINE_ZIPINFO * pSt_ZIPInfo)
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_QueryZIPCode(pSt_ZIPInfo);
}
extern "C" bool ModuleDatabase_ZIPCode_QueryName(XENGINE_ZIPINFO * pSt_ZIPInfo)
{
	return m_ZIPCode.ModuleDatabase_ZIPCode_QueryName(pSt_ZIPInfo);
}
/************************************************************************/
/*                         导出的日志服务数据库函数                     */
/************************************************************************/
extern "C" bool ModuleDatabase_XLog_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_XLog.ModuleDatabase_XLog_Init(pSt_DBConnector);
}
extern "C" bool ModuleDatabase_XLog_Destory()
{
	return m_XLog.ModuleDatabase_XLog_Destory();
}
extern "C" bool ModuleDatabase_XLog_Create(LPCXSTR lpszTableName)
{
	return m_XLog.ModuleDatabase_XLog_Create(lpszTableName);
}
extern "C" bool ModuleDatabase_XLog_Insert(XENGINE_XLOGINFO * pSt_XLogInfo)
{
	return m_XLog.ModuleDatabase_XLog_Insert(pSt_XLogInfo);
}
extern "C" bool ModuleDatabase_XLog_Query(XENGINE_XLOGINFO * **pppSt_XLogInfo, int* pInt_ListCount, LPCXSTR lpszTableName, LPCXSTR lpszTimeStart, LPCXSTR lpszTimeEnd)
{
	return m_XLog.ModuleDatabase_XLog_Query(pppSt_XLogInfo, pInt_ListCount, lpszTableName, lpszTimeStart, lpszTimeEnd);
}
extern "C" bool ModuleDatabase_XLog_Delete(LPCXSTR lpszTableName)
{
	return m_XLog.ModuleDatabase_XLog_Delete(lpszTableName);
}
extern "C" bool ModuleDatabase_XLog_Show(XCHAR * **ppptszList, int* pInt_ListCount)
{
	return m_XLog.ModuleDatabase_XLog_Show(ppptszList, pInt_ListCount);
}
/************************************************************************/
/*                         导出的短连接数据库函数                       */
/************************************************************************/
extern "C" bool ModuleDatabase_ShortLink_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_ShortLink.ModuleDatabase_ShortLink_Init(pSt_DBConnector);
}
extern "C" bool ModuleDatabase_ShortLink_Destory()
{
	return m_ShortLink.ModuleDatabase_ShortLink_Destory();
}
extern "C" bool ModuleDatabase_ShortLink_Insert(XENGINE_SHORTLINK * pSt_SLinkInfo)
{
	return m_ShortLink.ModuleDatabase_ShortLink_Insert(pSt_SLinkInfo);
}
extern "C" bool ModuleDatabase_ShortLink_Query(XENGINE_SHORTLINK * pSt_SLinkInfo)
{
	return m_ShortLink.ModuleDatabase_ShortLink_Query(pSt_SLinkInfo);
}
extern "C" bool ModuleDatabase_ShortLink_Delete(XENGINE_SHORTLINK * pSt_SLinkInfo)
{
	return m_ShortLink.ModuleDatabase_ShortLink_Delete(pSt_SLinkInfo);
}
/************************************************************************/
/*                         导出的敏感词过滤数据库函数                   */
/************************************************************************/
extern "C" bool ModuleDatabase_WordFilter_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_WordFilter.ModuleDatabase_WordFilter_Init(pSt_DBConnector);
}
extern "C" bool ModuleDatabase_WordFilter_Destory()
{
	return m_WordFilter.ModuleDatabase_WordFilter_Destory();
}
extern "C" bool ModuleDatabase_WordFilter_Query(XENGINE_WORDFILTER * pSt_WordFilter)
{
	return m_WordFilter.ModuleDatabase_WordFilter_Query(pSt_WordFilter);
}
extern "C" bool ModuleDatabase_WordFilter_Insert(XENGINE_WORDFILTER * pSt_WordFilter)
{
	return m_WordFilter.ModuleDatabase_WordFilter_Insert(pSt_WordFilter);
}
extern "C" bool ModuleDatabase_WordFilter_Delete(XENGINE_WORDFILTER * pSt_WordFilter)
{
	return m_WordFilter.ModuleDatabase_WordFilter_Delete(pSt_WordFilter);
}
/************************************************************************/
/*                         导出的机器信息收集数据库函数                 */
/************************************************************************/
extern "C" bool ModuleDatabase_Machine_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector)
{
	return m_MachineInfo.ModuleDatabase_Machine_Init(pSt_DBConnector);
}
extern "C" bool ModuleDatabase_Machine_Destory()
{
	return m_MachineInfo.ModuleDatabase_Machine_Destory();
}
extern "C" bool ModuleDatabase_Machine_Insert(XENGINE_MACHINEINFO * pSt_MachineInfo)
{
	return m_MachineInfo.ModuleDatabase_Machine_Insert(pSt_MachineInfo);
}
extern "C" bool ModuleDatabase_Machine_Query(XENGINE_MACHINEINFO * pSt_MachineInfo)
{
	return m_MachineInfo.ModuleDatabase_Machine_Query(pSt_MachineInfo);
}
extern "C" bool ModuleDatabase_Machine_Delete(XENGINE_MACHINEINFO * pSt_MachineInfo)
{
	return m_MachineInfo.ModuleDatabase_Machine_Delete(pSt_MachineInfo);
}