#include "pch.h"
#include "ModuleDatabase_ZIPCode.h"
/********************************************************************
//    Created:     2022/10/27  16:16:03
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_ZIPCode\ModuleDatabase_ZIPCode.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_ZIPCode
//    File Base:   ModuleDatabase_ZIPCode
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     邮政编码地址信息数据库
//    History:
*********************************************************************/
CModuleDatabase_ZIPCode::CModuleDatabase_ZIPCode()
{
}
CModuleDatabase_ZIPCode::~CModuleDatabase_ZIPCode()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_ZIPCode_Init
函数功能：初始化数据库
 参数.一：pSt_DBConnector
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的数据库
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector)
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
函数名称：ModuleDatabase_ZIPCode_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_Destory()
{
	DBModule_IsErrorOccur = false;

	DataBase_MySQL_Close(xhDBSQL);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_ZIPCode_QueryZIPCode
函数功能：通过邮编查询行政地址信息
 参数.一：pSt_ZIPInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的邮编,输出查询到的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryZIPCode(XENGINE_ZIPINFO* pSt_ZIPInfo)
{
	DBModule_IsErrorOccur = false;

	//查询
	__int64u nLine = 0;
	__int64u nRow = 0;
	XNETHANDLE xhTable = 0;
	XCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_xstprintf(tszSQLStatement, _X("SELECT * FROM `AdministrativeArea` WHERE zip_code = %d"), pSt_ZIPInfo->nZipCode);
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
	//三个级别 省->市->区/县
	_tcsxcpy(pSt_ZIPInfo->tszPinYin, pptszResult[6]);
	pSt_ZIPInfo->nLevel = _ttxoi(pptszResult[5]);
	pSt_ZIPInfo->nAreaCode = _ttxoi(pptszResult[7]);
	pSt_ZIPInfo->dlLng = _ttxof(pptszResult[10]);
	pSt_ZIPInfo->dlLat = _ttxof(pptszResult[11]);
	if (3 == pSt_ZIPInfo->nLevel)
	{
		//获取上级节点
		int nParentID = 0;
		_tcsxcpy(pSt_ZIPInfo->tszCounty, pptszResult[2]);
		ModuleDatabase_ZIPCode_QueryParentByID(_ttxoi(pptszResult[1]), pSt_ZIPInfo->tszCity, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszProvincer, &nParentID);
	}
	else if (2 == pSt_ZIPInfo->nLevel)
	{
		_tcsxcpy(pSt_ZIPInfo->tszCity, pptszResult[2]);
		ModuleDatabase_ZIPCode_QueryParentByID(_ttxoi(pptszResult[1]), pSt_ZIPInfo->tszProvincer);
	}
	else
	{
		_tcsxcpy(pSt_ZIPInfo->tszProvincer, pptszResult[2]);
	}

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_ZIPCode_QueryName
函数功能：通过行政名称查询内容
 参数.一：pSt_ZIPInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的信息,输出查询到的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryName(XENGINE_ZIPINFO* pSt_ZIPInfo)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_ZIPInfo)
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

	if ((_tcsxlen(pSt_ZIPInfo->tszCounty) > 0) && (_tcsxlen(pSt_ZIPInfo->tszCity) == 0))
	{
		int nParentID = 0;
		ModuleDatabase_ZIPCode_QueryParentByName(pSt_ZIPInfo->tszCounty, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszCity, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszProvincer, &nParentID);

		_xstprintf(tszSQLStatement, _X("SELECT * FROM `AdministrativeArea` WHERE name = '%s'"), pSt_ZIPInfo->tszCounty);
	}
	else if ((_tcsxlen(pSt_ZIPInfo->tszCounty) == 0) && (_tcsxlen(pSt_ZIPInfo->tszCity) > 0))
	{
		int nParentID = 0;
		ModuleDatabase_ZIPCode_QueryParentByName(pSt_ZIPInfo->tszCity, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszProvincer, &nParentID);

		_xstprintf(tszSQLStatement, _X("SELECT * FROM `AdministrativeArea` WHERE name = '%s'"), pSt_ZIPInfo->tszCity);
	}
	else
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTSET;
		return false;
	}
	//查询内容
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
	pSt_ZIPInfo->nLevel = _ttxoi(pptszResult[5]);
	pSt_ZIPInfo->nAreaCode = _ttxoi(pptszResult[7]);
	pSt_ZIPInfo->nZipCode = _ttxoi(pptszResult[8]);
	pSt_ZIPInfo->dlLng = _ttxof(pptszResult[10]);
	pSt_ZIPInfo->dlLat = _ttxof(pptszResult[11]);
	_tcsxcpy(pSt_ZIPInfo->tszPinYin, pptszResult[6]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}
//////////////////////////////////////////////////////////////////////////
//                             保护函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_ZIPCode_QueryParentByID
函数功能：通过ID查询父节点信息
 参数.一：nParentID
  In/Out：In
  类型：整数型
  可空：N
  意思：输入要查询的父节点
 参数.二：ptszParentStr
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出查询到的父节点名
 参数.三：pInt_ParentID
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：导出上级节点ID
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryParentByID(int nParentID, XCHAR* ptszParentStr, int* pInt_ParentID /* = NULL */)
{
	DBModule_IsErrorOccur = false;

	if (NULL == ptszParentStr)
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
	_xstprintf(tszSQLStatement, _X("SELECT * FROM `AdministrativeArea` WHERE id = %d"), nParentID);
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
	
	if (NULL != pInt_ParentID)
	{
		*pInt_ParentID = _ttxoi(pptszResult[1]);
	}
	_tcsxcpy(ptszParentStr, pptszResult[3]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_ZIPCode_QueryParentByName
函数功能：通过名称查询父节点信息
 参数.一：lpszName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要查询的名称
 参数.二：pInt_ParentID
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：导出上级节点ID
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryParentByName(LPCXSTR lpszName, int* pInt_ParentID /* = NULL */)
{
	DBModule_IsErrorOccur = false;

	if (NULL == lpszName)
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
	_xstprintf(tszSQLStatement, _X("SELECT * FROM `AdministrativeArea` WHERE name = '%s'"), lpszName);
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
	if (NULL != pInt_ParentID)
	{
		*pInt_ParentID = _ttxoi(pptszResult[1]);
	}
	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}