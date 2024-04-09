#include "pch.h"
#include "ModuleDatabase_WordFilter.h"
/********************************************************************
//    Created:     2023/08/09  10:57:03
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_WordFilter\ModuleDatabase_WordFilter.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_WordFilter
//    File Base:   ModuleDatabase_WordFilter
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     敏感词过滤器
//    History:
*********************************************************************/
CModuleDatabase_WordFilter::CModuleDatabase_WordFilter()
{
}
CModuleDatabase_WordFilter::~CModuleDatabase_WordFilter()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_WordFilter_Init
函数功能：初始化SQLITE文件系统
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
bool CModuleDatabase_WordFilter::ModuleDatabase_WordFilter_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_DBConnector)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	//连接数据库
	_tcsxcpy(pSt_DBConnector->tszDBName, _X("XEngine_APIWords"));
	if (!DataBase_MySQL_Connect(&xhDBSQL, pSt_DBConnector))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_WordFilter_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_WordFilter::ModuleDatabase_WordFilter_Destory()
{
	DBModule_IsErrorOccur = false;

	DataBase_MySQL_Close(xhDBSQL);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_WordFilter_Query
函数功能：获取敏感词系统
 参数.一：pSt_WordFilter
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的词,输出查询到的敏感词
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_WordFilter::ModuleDatabase_WordFilter_Query(XENGINE_WORDFILTER* pSt_WordFilter)
{
    DBModule_IsErrorOccur = false;

    if (NULL == pSt_WordFilter)
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
	_xstprintf(tszSQLStatement, _X("SELECT * FROM `WordFilter` WHERE tszWordsFrom LIKE '%s'"), pSt_WordFilter->tszWordsFrom);
#ifdef _MSC_BUILD
	XCHAR tszUTFStr[1024] = {};
	int nSLen = _tcsxlen(tszSQLStatement);
	BaseLib_OperatorCharset_AnsiToUTF(tszSQLStatement, tszUTFStr, &nSLen);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszUTFStr, &nLine, &nRow))
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
	
	_tcsxcpy(pSt_WordFilter->tszWordsTo, pptszResult[1]);
	pSt_WordFilter->nLevel = _ttxoi(pptszResult[2]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_WordFilter_Insert
函数功能：查询一条敏感词
 参数.一：pSt_WordFilter
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要操作的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_WordFilter::ModuleDatabase_WordFilter_Insert(XENGINE_WORDFILTER* pSt_WordFilter)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_WordFilter)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[1024];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("INSERT INTO `WordFilter` (tszWordsFrom,tszWordsTo,nLevel) VALUES('%s','%s',%d)"), pSt_WordFilter->tszWordsFrom, pSt_WordFilter->tszWordsTo, pSt_WordFilter->nLevel);

#ifdef _MSC_BUILD
	int nRet = _tcsxlen(tszSQLStatement);
	XCHAR tszUTFStr[1024] = {};
	BaseLib_OperatorCharset_AnsiToUTF(tszSQLStatement, tszUTFStr, &nRet);
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
/********************************************************************
函数名称：ModuleDatabase_WordFilter_Delete
函数功能：删除一条敏感词
 参数.一：pSt_WordFilter
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_WordFilter::ModuleDatabase_WordFilter_Delete(XENGINE_WORDFILTER* pSt_WordFilter)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_WordFilter)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[10240];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("DELETE FROM `WordFilter` WHERE tszWordsFrom = '%s'"), pSt_WordFilter->tszWordsFrom);
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