#include "pch.h"
#include "ModuleDatabase_IDCard.h"
/********************************************************************
//    Created:     2022/03/04  14:24:12
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_IDCard\ModuleDatabase_IDCard.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_IDCard
//    File Base:   ModuleDatabase_IDCard
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     身份证信息数据库操作
//    History:
*********************************************************************/
CModuleDatabase_IDCard::CModuleDatabase_IDCard()
{
}
CModuleDatabase_IDCard::~CModuleDatabase_IDCard()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_IDCard_Init
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
XBOOL CModuleDatabase_IDCard::ModuleDatabase_IDCard_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector)
{
	DBModule_IsErrorOccur = FALSE;

	if (NULL == pSt_DBConnector)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return FALSE;
	}
	//连接数据库
	_tcscpy(pSt_DBConnector->tszDBName, _T("XEngine_APIInfo"));
	if (!DataBase_MySQL_Connect(&xhDBSQL, pSt_DBConnector))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_IDCard_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleDatabase_IDCard::ModuleDatabase_IDCard_Destory()
{
	DBModule_IsErrorOccur = FALSE;

	DataBase_MySQL_Close(xhDBSQL);
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_IDCard_QueryRegion
函数功能：查询身份证位置信息
 参数.一：pSt_IDRegion
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出查询到的位置信息
 参数.二：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要查询的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleDatabase_IDCard::ModuleDatabase_IDCard_QueryRegion(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo)
{
	DBModule_IsErrorOccur = FALSE;

	ModuleDatabase_IDCard_QueryProvincer(pSt_IDRegion, pSt_IDInfo);
	ModuleDatabase_IDCard_QueryCity(pSt_IDRegion, pSt_IDInfo);
	ModuleDatabase_IDCard_QueryCounty(pSt_IDRegion, pSt_IDInfo);
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_IDCard_QueryProvincer
函数功能：查询省份信息
 参数.一：pSt_IDRegion
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出所属省份
 参数.二：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要查询的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleDatabase_IDCard::ModuleDatabase_IDCard_QueryProvincer(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo)
{
    DBModule_IsErrorOccur = FALSE;

    if ((NULL == pSt_IDRegion) || (NULL == pSt_IDInfo))
    {
        DBModule_IsErrorOccur = TRUE;
        DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
        return FALSE;
    }
    //查询
	__int64u nLine = 0;
	__int64u nRow = 0;
	XNETHANDLE xhTable = 0;
    XCHAR tszSQLStatement[1024];

    memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_stprintf(tszSQLStatement, _T("SELECT * FROM `RegionID` WHERE code = '%02d0000'"), pSt_IDInfo->nIDProvince);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
		return FALSE;
	}
	XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);
	_tcscpy(pSt_IDRegion->tszProvincer, pptszResult[1]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_IDCard_QueryCity
函数功能：查询市信息
 参数.一：pSt_IDRegion
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出所属市
 参数.二：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要查询的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleDatabase_IDCard::ModuleDatabase_IDCard_QueryCity(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo)
{
	DBModule_IsErrorOccur = FALSE;

	if ((NULL == pSt_IDRegion) || (NULL == pSt_IDInfo))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return FALSE;
	}
	//查询
	__int64u nLine = 0;
	__int64u nRow = 0;
	XNETHANDLE xhTable = 0;
	XCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_stprintf(tszSQLStatement, _T("SELECT * FROM `RegionID` WHERE code = '%02d%02d00'"), pSt_IDInfo->nIDProvince, pSt_IDInfo->nIDCity);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
		return FALSE;
	}
	XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);
	_tcscpy(pSt_IDRegion->tszCity, pptszResult[1]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_IDCard_QueryCounty
函数功能：查询县区信息
 参数.一：pSt_IDRegion
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出所属县区
 参数.二：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要查询的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleDatabase_IDCard::ModuleDatabase_IDCard_QueryCounty(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo)
{
	DBModule_IsErrorOccur = FALSE;

	if ((NULL == pSt_IDRegion) || (NULL == pSt_IDInfo))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return FALSE;
	}
	//查询
	__int64u nLine = 0;
	__int64u nRow = 0;
	XNETHANDLE xhTable = 0;
	XCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_stprintf(tszSQLStatement, _T("SELECT * FROM `RegionID` WHERE code = '%02d%02d%02d'"), pSt_IDInfo->nIDProvince, pSt_IDInfo->nIDCity, pSt_IDInfo->nIDCounty);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
		return FALSE;
	}
	XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);
	_tcscpy(pSt_IDRegion->tszCounty, pptszResult[1]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return TRUE;
}