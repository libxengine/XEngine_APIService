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
BOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_Init(LPCTSTR lpszSQLFile)
{
	DBModule_IsErrorOccur = FALSE;
	//打开数据库
	if (!DataBase_SQLite_Open(&xhSQL, lpszSQLFile))
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
BOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_Destory()
{
	DBModule_IsErrorOccur = FALSE;

	DataBase_SQLite_Close(xhSQL);
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
BOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryZIPCode(XENGINE_ZIPINFO* pSt_ZIPInfo)
{
	DBModule_IsErrorOccur = FALSE;

	//查询
	int nLine = 0;
	int nRow = 0;
	TCHAR** pptszResult;
	TCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_stprintf(tszSQLStatement, _T("SELECT * FROM `hy_area` WHERE zip_code = %d"), pSt_ZIPInfo->nZipCode);
	if (!DataBase_SQLite_GetTable(xhSQL, tszSQLStatement, &pptszResult, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_ZIPCODE_NOTFOUND;
		return FALSE;
	}
	int nFliedValue = nRow;
	//三个级别 省->市->区/县
	_tcscpy(pSt_ZIPInfo->tszPinYin, pptszResult[nFliedValue + 6]);
	pSt_ZIPInfo->nLevel = _ttoi(pptszResult[nFliedValue + 5]);
	pSt_ZIPInfo->nAreaCode = _ttoi(pptszResult[nFliedValue + 7]);
	pSt_ZIPInfo->dlLng = _ttof(pptszResult[nFliedValue + 10]);
	pSt_ZIPInfo->dlLat = _ttof(pptszResult[nFliedValue + 11]);
	if (3 == pSt_ZIPInfo->nLevel)
	{
		//获取上级节点
		int nParentID = 0;
		_tcscpy(pSt_ZIPInfo->tszCounty, pptszResult[nFliedValue + 2]);
		ModuleDatabase_ZIPCode_QueryParentByID(_ttoi(pptszResult[nFliedValue + 1]), pSt_ZIPInfo->tszCity, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszProvincer, &nParentID);
	}
	else if (2 == pSt_ZIPInfo->nLevel)
	{
		int nParentID = 0;
		_tcscpy(pSt_ZIPInfo->tszCity, pptszResult[nFliedValue + 2]);
		ModuleDatabase_ZIPCode_QueryParentByID(_ttoi(pptszResult[nFliedValue + 1]), pSt_ZIPInfo->tszProvincer);
	}
	else
	{
		_tcscpy(pSt_ZIPInfo->tszProvincer, pptszResult[nFliedValue + 2]);
	}

	DataBase_SQLite_FreeTable(pptszResult);
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
BOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryName(XENGINE_ZIPINFO* pSt_ZIPInfo)
{
	DBModule_IsErrorOccur = FALSE;

	if (NULL == pSt_ZIPInfo)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_ZIPCODE_PARAMENT;
		return FALSE;
	}
	//查询
	int nLine = 0;
	int nRow = 0;
	TCHAR** pptszResult;
	TCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	if ((_tcslen(pSt_ZIPInfo->tszCounty) > 0) && (_tcslen(pSt_ZIPInfo->tszCity) == 0))
	{
		int nParentID = 0;
		ModuleDatabase_ZIPCode_QueryParentByName(pSt_ZIPInfo->tszCounty, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszCity, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszProvincer, &nParentID);

		_stprintf(tszSQLStatement, _T("SELECT * FROM `hy_area` WHERE name = '%s'"), pSt_ZIPInfo->tszCounty);
	}
	else if ((_tcslen(pSt_ZIPInfo->tszCounty) == 0) && (_tcslen(pSt_ZIPInfo->tszCity) > 0))
	{
		int nParentID = 0;
		ModuleDatabase_ZIPCode_QueryParentByName(pSt_ZIPInfo->tszCity, &nParentID);
		ModuleDatabase_ZIPCode_QueryParentByID(nParentID, pSt_ZIPInfo->tszProvincer, &nParentID);

		_stprintf(tszSQLStatement, _T("SELECT * FROM `hy_area` WHERE name = '%s'"), pSt_ZIPInfo->tszCity);
	}
	else
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_ZIPCODE_NOTSET;
		return FALSE;
	}
	//查询内容
	if (!DataBase_SQLite_GetTable(xhSQL, tszSQLStatement, &pptszResult, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_ZIPCODE_NOTFOUND;
		return FALSE;
	}
	int nFliedValue = nRow;
	pSt_ZIPInfo->nLevel = _ttoi(pptszResult[nFliedValue + 5]);
	pSt_ZIPInfo->nAreaCode = _ttoi(pptszResult[nFliedValue + 7]);
	pSt_ZIPInfo->nZipCode = _ttoi(pptszResult[nFliedValue + 8]);
	pSt_ZIPInfo->dlLng = _ttof(pptszResult[nFliedValue + 10]);
	pSt_ZIPInfo->dlLat = _ttof(pptszResult[nFliedValue + 11]);
	_tcscpy(pSt_ZIPInfo->tszPinYin, pptszResult[nFliedValue + 6]);

	DataBase_SQLite_FreeTable(pptszResult);
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
BOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryParentByID(int nParentID, TCHAR* ptszParentStr, int* pInt_ParentID /* = NULL */)
{
	DBModule_IsErrorOccur = FALSE;

	if (NULL == ptszParentStr)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_ZIPCODE_PARAMENT;
		return FALSE;
	}
	//查询
	int nLine = 0;
	int nRow = 0;
	TCHAR** pptszResult;
	TCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_stprintf(tszSQLStatement, _T("SELECT * FROM `hy_area` WHERE id = %d"), nParentID);
	if (!DataBase_SQLite_GetTable(xhSQL, tszSQLStatement, &pptszResult, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_ZIPCODE_NOTFOUND;
		return FALSE;
	}
	int nFliedValue = nRow;
	if (NULL != pInt_ParentID)
	{
		*pInt_ParentID = _ttoi(pptszResult[nFliedValue + 1]);
	}
	_tcscpy(ptszParentStr, pptszResult[nFliedValue + 3]);

	DataBase_SQLite_FreeTable(pptszResult);
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
BOOL CModuleDatabase_ZIPCode::ModuleDatabase_ZIPCode_QueryParentByName(LPCTSTR lpszName, int* pInt_ParentID /* = NULL */)
{
	DBModule_IsErrorOccur = FALSE;

	if (NULL == lpszName)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_ZIPCODE_PARAMENT;
		return FALSE;
	}
	//查询
	int nLine = 0;
	int nRow = 0;
	TCHAR** pptszResult;
	TCHAR tszSQLStatement[1024];

	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_stprintf(tszSQLStatement, _T("SELECT * FROM `hy_area` WHERE name = '%s'"), lpszName);
	if (!DataBase_SQLite_GetTable(xhSQL, tszSQLStatement, &pptszResult, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_ZIPCODE_NOTFOUND;
		return FALSE;
	}
	int nFliedValue = nRow;
	if (NULL != pInt_ParentID)
	{
		*pInt_ParentID = _ttoi(pptszResult[nFliedValue + 1]);
	}
	DataBase_SQLite_FreeTable(pptszResult);
	return TRUE;
}