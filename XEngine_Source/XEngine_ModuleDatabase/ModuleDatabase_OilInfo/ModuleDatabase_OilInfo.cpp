#include "pch.h"
#include "ModuleDatabase_OilInfo.h"
/********************************************************************
//    Created:     2024/05/08  14:52:14
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_OilInfo\ModuleDatabase_OilInfo.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_OilInfo
//    File Base:   ModuleDatabase_OilInfo
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     油价信息查询接口
//    History:
*********************************************************************/
CModuleDatabase_OilInfo::CModuleDatabase_OilInfo()
{
}
CModuleDatabase_OilInfo::~CModuleDatabase_OilInfo()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_OilInfo_Init
函数功能：初始化数据库
 参数.一：pSt_DBConnector
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：数据数据库信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_OilInfo::ModuleDatabase_OilInfo_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_DBConnector)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	//连接数据库
	_tcsxcpy(pSt_DBConnector->tszDBName, _X("XEngine_APIInfo"));
	if (!DataBase_MySQL_Connect(&xhDBSQL, pSt_DBConnector))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_OilInfo_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_OilInfo::ModuleDatabase_OilInfo_Destory()
{
	DBModule_IsErrorOccur = false;

	DataBase_MySQL_Close(xhDBSQL);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_OilInfo_Query
函数功能：查询数据
 参数.一：pSt_OilInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入查询的信息,输出完整的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_OilInfo::ModuleDatabase_OilInfo_Query(XENGINE_OILINFO* pSt_OilInfo)
{
	DBModule_IsErrorOccur = false;

	if ((NULL == pSt_OilInfo))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	//查询
	XNETHANDLE xhTable = 0;
	__int64u nllLine = 0;
	__int64u nllRow = 0;

	XCHAR tszSQLStatement[1024];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("SELECT * FROM `OilPrice` WHERE tszRegion = '%s'"), pSt_OilInfo->tszCityStr);
#ifdef _MSC_BUILD
	XCHAR tszUTFStr[1024] = {};
	int nSLen = _tcsxlen(tszSQLStatement);
	BaseLib_OperatorCharset_AnsiToUTF(tszSQLStatement, tszUTFStr, &nSLen);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszUTFStr, &nllLine, &nllRow))
#else
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nllLine, &nllRow))
#endif
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	if (nllLine <= 0)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
		return false;
	}
	for (__int64u i = 0; i < nllLine; i++)
	{
		XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);

		if (NULL != pptszResult[0])
		{
			_tcsxcpy(pSt_OilInfo->tszCityStr, pptszResult[0]);
		}
		if (NULL != pptszResult[1])
		{
			pSt_OilInfo->dlValue98 = _ttxof(pptszResult[1]);
		}
		if (NULL != pptszResult[2])
		{
			pSt_OilInfo->dlValue95 = _ttxof(pptszResult[2]);
		}
		if (NULL != pptszResult[3])
		{
			pSt_OilInfo->dlValue92 = _ttxof(pptszResult[3]);
		}
		if (NULL != pptszResult[4])
		{
			pSt_OilInfo->dlValue0 = _ttxof(pptszResult[4]);
		}
		if (NULL != pptszResult[5])
		{
			pSt_OilInfo->dlValue10 = _ttxof(pptszResult[5]);
		}
		if (NULL != pptszResult[6])
		{
			pSt_OilInfo->dlValue20 = _ttxof(pptszResult[6]);
		}
		if (NULL != pptszResult[7])
		{
			pSt_OilInfo->dlValue35 = _ttxof(pptszResult[7]);
		}
		if (NULL != pptszResult[8])
		{
			_tcsxcpy(pSt_OilInfo->tszUPTime, pptszResult[8]);
		}
	}
	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_OilInfo_UPDate
函数功能：更新数据
 参数.一：pSt_OilInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要更新的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_OilInfo::ModuleDatabase_OilInfo_UPDate(XENGINE_OILINFO* pSt_OilInfo)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_OilInfo)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[1024];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("UPDATE `OilPrice` SET 98 = %lf,95 = %lf,92 = %lf,0 = %lf,-10 = %lf,-20 = %lf,-35 = %lf,tszUPTime = 'now()' WHERE tszRegion = '%s'"), pSt_OilInfo->dlValue98, pSt_OilInfo->dlValue95, pSt_OilInfo->dlValue92, pSt_OilInfo->dlValue0, pSt_OilInfo->dlValue10, pSt_OilInfo->dlValue20, pSt_OilInfo->dlValue35, pSt_OilInfo->tszCityStr);

#ifdef _MSC_BUILD
	XCHAR tszUTFStr[1024] = {};
	int nSLen = _tcsxlen(tszSQLStatement);
	BaseLib_OperatorCharset_AnsiToUTF(tszSQLStatement, tszUTFStr, &nSLen);
	if (!DataBase_MySQL_Execute(xhDBSQL, tszUTFStr))
#else
	if (!DataBase_MySQL_Execute(xhDBSQL, tszSQLStatement))
#endif
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}