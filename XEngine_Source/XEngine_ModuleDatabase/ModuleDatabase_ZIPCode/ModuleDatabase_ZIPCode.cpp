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
XBOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector)
{
	DBModule_IsErrorOccur = FALSE;

	if (NULL == pSt_DBConnector)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return FALSE;
	}
#ifdef _MSC_BUILD
	LPCXSTR lpszStrCharset = _T("gbk");
#else
	LPCXSTR lpszStrCharset = _T("utf8");
#endif
	//连接数据库
	_tcscpy(pSt_DBConnector->tszDBName, _T("XEngine_APIInfo"));
	if (!DataBase_MySQL_Connect(&xhDBSQL, pSt_DBConnector, 5, TRUE, lpszStrCharset))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_ZIPCode_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_Destory()
{
	DBModule_IsErrorOccur = FALSE;

	DataBase_MySQL_Close(xhDBSQL);
	return TRUE;
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
XBOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryZIPCode(XENGINE_ZIPINFO* pSt_ZIPInfo)
{
	DBModule_IsErrorOccur = FALSE;

	//查询
	__int64u nLine = 0;
	__int64u nRow = 0;
	XNETHANDLE xhTable = 0;
	XCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_stprintf(tszSQLStatement, _T("SELECT * FROM `AdministrativeArea` WHERE zip_code = %d"), pSt_ZIPInfo->nZipCode);
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
	//三个级别 省->市->区/县
	_tcscpy(pSt_ZIPInfo->tszPinYin, pptszResult[6]);
	pSt_ZIPInfo->nLevel = _ttoi(pptszResult[5]);
	pSt_ZIPInfo->nAreaCode = _ttoi(pptszResult[7]);
	pSt_ZIPInfo->dlLng = _ttof(pptszResult[10]);
	pSt_ZIPInfo->dlLat = _ttof(pptszResult[11]);
	if (3 == pSt_ZIPInfo->nLevel)
	{
		//获取上级节点
		int nParentID = 0;
		_tcscpy(pSt_ZIPInfo->tszCounty, pptszResult[2]);
		ModuleDatabase_ZIPCode_QueryParentByID(_ttoi(pptszResult[1]), pSt_ZIPInfo->tszCity, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszProvincer, &nParentID);
	}
	else if (2 == pSt_ZIPInfo->nLevel)
	{
		_tcscpy(pSt_ZIPInfo->tszCity, pptszResult[2]);
		ModuleDatabase_ZIPCode_QueryParentByID(_ttoi(pptszResult[1]), pSt_ZIPInfo->tszProvincer);
	}
	else
	{
		_tcscpy(pSt_ZIPInfo->tszProvincer, pptszResult[2]);
	}

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return TRUE;
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
XBOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryName(XENGINE_ZIPINFO* pSt_ZIPInfo)
{
	DBModule_IsErrorOccur = FALSE;

	if (NULL == pSt_ZIPInfo)
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

	if ((_tcslen(pSt_ZIPInfo->tszCounty) > 0) && (_tcslen(pSt_ZIPInfo->tszCity) == 0))
	{
		int nParentID = 0;
		ModuleDatabase_ZIPCode_QueryParentByName(pSt_ZIPInfo->tszCounty, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszCity, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszProvincer, &nParentID);

		_stprintf(tszSQLStatement, _T("SELECT * FROM `AdministrativeArea` WHERE name = '%s'"), pSt_ZIPInfo->tszCounty);
	}
	else if ((_tcslen(pSt_ZIPInfo->tszCounty) == 0) && (_tcslen(pSt_ZIPInfo->tszCity) > 0))
	{
		int nParentID = 0;
		ModuleDatabase_ZIPCode_QueryParentByName(pSt_ZIPInfo->tszCity, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszProvincer, &nParentID);

		_stprintf(tszSQLStatement, _T("SELECT * FROM `AdministrativeArea` WHERE name = '%s'"), pSt_ZIPInfo->tszCity);
	}
	else
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTSET;
		return FALSE;
	}
	//查询内容
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
	pSt_ZIPInfo->nLevel = _ttoi(pptszResult[5]);
	pSt_ZIPInfo->nAreaCode = _ttoi(pptszResult[7]);
	pSt_ZIPInfo->nZipCode = _ttoi(pptszResult[8]);
	pSt_ZIPInfo->dlLng = _ttof(pptszResult[10]);
	pSt_ZIPInfo->dlLat = _ttof(pptszResult[11]);
	_tcscpy(pSt_ZIPInfo->tszPinYin, pptszResult[6]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return TRUE;
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
XBOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryParentByID(int nParentID, XCHAR* ptszParentStr, int* pInt_ParentID /* = NULL */)
{
	DBModule_IsErrorOccur = FALSE;

	if (NULL == ptszParentStr)
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
	_stprintf(tszSQLStatement, _T("SELECT * FROM `AdministrativeArea` WHERE id = %d"), nParentID);
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
	
	if (NULL != pInt_ParentID)
	{
		*pInt_ParentID = _ttoi(pptszResult[1]);
	}
	_tcscpy(ptszParentStr, pptszResult[3]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return TRUE;
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
XBOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryParentByName(LPCXSTR lpszName, int* pInt_ParentID /* = NULL */)
{
	DBModule_IsErrorOccur = FALSE;

	if (NULL == lpszName)
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
	_stprintf(tszSQLStatement, _T("SELECT * FROM `AdministrativeArea` WHERE name = '%s'"), lpszName);
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
	if (NULL != pInt_ParentID)
	{
		*pInt_ParentID = _ttoi(pptszResult[1]);
	}
	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return TRUE;
}