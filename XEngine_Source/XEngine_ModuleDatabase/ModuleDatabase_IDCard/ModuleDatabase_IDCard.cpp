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
bool CModuleDatabase_IDCard::ModuleDatabase_IDCard_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector)
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
函数名称：ModuleDatabase_IDCard_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_IDCard::ModuleDatabase_IDCard_Destory()
{
	DBModule_IsErrorOccur = false;

	DataBase_MySQL_Close(xhDBSQL);
	return true;
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
bool CModuleDatabase_IDCard::ModuleDatabase_IDCard_QueryRegion(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo)
{
	DBModule_IsErrorOccur = false;

	ModuleDatabase_IDCard_QueryProvincer(pSt_IDRegion, pSt_IDInfo);
	ModuleDatabase_IDCard_QueryCity(pSt_IDRegion, pSt_IDInfo);
	ModuleDatabase_IDCard_QueryCounty(pSt_IDRegion, pSt_IDInfo);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_IDCard_QueryByAddr
函数功能：查询地址对应的区域ID
 参数.一：pSt_IDRegion
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出查询到的位置信息
 参数.二：pInt_IDNumber
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出对应ID
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_IDCard::ModuleDatabase_IDCard_QueryByAddr(XENGINE_IDREGION* pSt_IDRegion, int* pInt_IDNumber)
{
	DBModule_IsErrorOccur = false;

	if ((NULL == pSt_IDRegion) || (NULL == pInt_IDNumber))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	//查询
	__int64u nLine = 0;
	__int64u nRow = 0;
	int nProvincer = 0;
	int nCity = 0;
	int nCounty = 0;
	XNETHANDLE xhTable = 0;
	XCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_xstprintf(tszSQLStatement, _X("SELECT * FROM `RegionID` WHERE name = '%s'"), pSt_IDRegion->tszProvincer);

#ifdef _MSC_BUILD
	XCHAR tszUTFBuffer[1024] = {};
	int nULen = _tcsxlen(tszSQLStatement);
	BaseLib_OperatorCharset_AnsiToUTF(tszSQLStatement, tszUTFBuffer, &nULen);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszUTFBuffer, &nLine, &nRow))
#else
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nLine, &nRow))
#endif
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
		return false;
	}
	XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);
	nProvincer = _ttxoi(pptszResult[0]);
	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);

	if (_tcsxlen(pSt_IDRegion->tszCity) > 0)
	{
		memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
		_xstprintf(tszSQLStatement, _X("SELECT * FROM `RegionID` WHERE name = '%s' AND parentCode = %d"), pSt_IDRegion->tszCity, nProvincer);

#ifdef _MSC_BUILD
		XCHAR tszUTFBuffer[1024] = {};
		int nULen = _tcsxlen(tszSQLStatement);
		BaseLib_OperatorCharset_AnsiToUTF(tszSQLStatement, tszUTFBuffer, &nULen);
		if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszUTFBuffer, &nLine, &nRow))
#else
		if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nLine, &nRow))
#endif
		{
			DBModule_IsErrorOccur = true;
			DBModule_dwErrorCode = DataBase_GetLastError();
			return false;
		}
		if (nLine <= 0)
		{
			DBModule_IsErrorOccur = true;
			DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
			return false;
		}
		XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);
		nCity = _ttxoi(pptszResult[0]);
		DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	}
	
	if (_tcsxlen(pSt_IDRegion->tszCounty) > 0)
	{
		memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
		_xstprintf(tszSQLStatement, _X("SELECT * FROM `RegionID` WHERE name = '%s' AND parentCode = %d"), pSt_IDRegion->tszCounty, nCity);

#ifdef _MSC_BUILD
		XCHAR tszUTFBuffer[1024] = {};
		int nULen = _tcsxlen(tszSQLStatement);
		BaseLib_OperatorCharset_AnsiToUTF(tszSQLStatement, tszUTFBuffer, &nULen);
		if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszUTFBuffer, &nLine, &nRow))
#else
		if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nLine, &nRow))
#endif
		{
			DBModule_IsErrorOccur = true;
			DBModule_dwErrorCode = DataBase_GetLastError();
			return false;
		}
		if (nLine <= 0)
		{
			DBModule_IsErrorOccur = true;
			DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
			return false;
		}
		XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);
		nCounty = _ttxoi(pptszResult[0]);
		DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	}

	if (0 == nCounty && 0 == nCity)
	{
		*pInt_IDNumber = nProvincer;
	}
	else if (0 == nCounty && 0 != nCity)
	{
		*pInt_IDNumber = nCity;
	}
	else
	{
		*pInt_IDNumber = nCounty;
	}
	
	return true;
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
bool CModuleDatabase_IDCard::ModuleDatabase_IDCard_QueryProvincer(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo)
{
    DBModule_IsErrorOccur = false;

    if ((NULL == pSt_IDRegion) || (NULL == pSt_IDInfo))
    {
        DBModule_IsErrorOccur = true;
        DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
        return false;
    }
    //查询
	__int64u nLine = 0;
	__int64u nRow = 0;
	XNETHANDLE xhTable = 0;
    XCHAR tszSQLStatement[1024];

    memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_xstprintf(tszSQLStatement, _X("SELECT * FROM `RegionID` WHERE code = '%02d0000'"), pSt_IDInfo->nIDProvince);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
		return false;
	}
	XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);
	_tcsxcpy(pSt_IDRegion->tszProvincer, pptszResult[1]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
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
bool CModuleDatabase_IDCard::ModuleDatabase_IDCard_QueryCity(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo)
{
	DBModule_IsErrorOccur = false;

	if ((NULL == pSt_IDRegion) || (NULL == pSt_IDInfo))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	//查询
	__int64u nLine = 0;
	__int64u nRow = 0;
	XNETHANDLE xhTable = 0;
	XCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_xstprintf(tszSQLStatement, _X("SELECT * FROM `RegionID` WHERE code = '%02d%02d00'"), pSt_IDInfo->nIDProvince, pSt_IDInfo->nIDCity);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
		return false;
	}
	XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);
	_tcsxcpy(pSt_IDRegion->tszCity, pptszResult[1]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
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
bool CModuleDatabase_IDCard::ModuleDatabase_IDCard_QueryCounty(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo)
{
	DBModule_IsErrorOccur = false;

	if ((NULL == pSt_IDRegion) || (NULL == pSt_IDInfo))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	//查询
	__int64u nLine = 0;
	__int64u nRow = 0;
	XNETHANDLE xhTable = 0;
	XCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_xstprintf(tszSQLStatement, _X("SELECT * FROM `RegionID` WHERE code = '%02d%02d%02d'"), pSt_IDInfo->nIDProvince, pSt_IDInfo->nIDCity, pSt_IDInfo->nIDCounty);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
		return false;
	}
	XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);
	_tcsxcpy(pSt_IDRegion->tszCounty, pptszResult[1]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}