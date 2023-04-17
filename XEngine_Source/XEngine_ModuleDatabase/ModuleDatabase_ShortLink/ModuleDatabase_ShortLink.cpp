#include "pch.h"
#include "ModuleDatabase_ShortLink.h"
/********************************************************************
//    Created:     2023/04/11  10:36:45
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_ShortLink\ModuleDatabase_ShortLink.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_ShortLink
//    File Base:   ModuleDatabase_ShortLink
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     短连接数据库管理器
//    History:
*********************************************************************/
CModuleDatabase_ShortLink::CModuleDatabase_ShortLink()
{
}
CModuleDatabase_ShortLink::~CModuleDatabase_ShortLink()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_ShortLink_Init
函数功能：初始化SQLITE文件系统
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
bool CModuleDatabase_ShortLink::ModuleDatabase_ShortLink_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_DBConnector)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	//连接数据库
	_tcsxcpy(pSt_DBConnector->tszDBName, _X("XEngine_APISLink"));
	if (!DataBase_MySQL_Connect(&xhDBSQL, pSt_DBConnector))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_ShortLink_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_ShortLink::ModuleDatabase_ShortLink_Destory()
{
	DBModule_IsErrorOccur = false;

	DataBase_MySQL_Close(xhDBSQL);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_ShortLink_Insert
函数功能：插入一个短连接到数据库中
 参数.一：pSt_SLinkInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要插入的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_ShortLink::ModuleDatabase_ShortLink_Insert(XENGINE_SHORTLINK* pSt_SLinkInfo)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_SLinkInfo)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[2024];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("INSERT INTO `XEngine_ShortLink` (tszFullUrl,tszShortUrl,tszKeyUrl,tszMapUrl,tszCreateTime) VALUES('%s','%s','%s','%s','%s')"), pSt_SLinkInfo->tszFullUrl, pSt_SLinkInfo->tszShotUrl, pSt_SLinkInfo->tszKeyUrl, pSt_SLinkInfo->tszMapUrl, pSt_SLinkInfo->tszCreateTime);
	if (!DataBase_MySQL_Execute(xhDBSQL, tszSQLStatement))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_ShortLink_Query
函数功能：查询短连接
 参数.一：pSt_SLinkInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入查询的短连接,输出完整的连接
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_ShortLink::ModuleDatabase_ShortLink_Query(XENGINE_SHORTLINK* pSt_SLinkInfo)
{
	DBModule_IsErrorOccur = false;

	if ((NULL == pSt_SLinkInfo))
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
	//名称为,消息名为必填
	_xstprintf(tszSQLStatement, _X("SELECT * FROM `XEngine_ShortLink` WHERE tszMapUrl = '%s'"), pSt_SLinkInfo->tszMapUrl);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nllLine, &nllRow))
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
			pSt_SLinkInfo->nID = _ttxoi(pptszResult[0]);
		}
		if (NULL != pptszResult[1])
		{
			_tcsxcpy(pSt_SLinkInfo->tszFullUrl, pptszResult[1]);
		}
		if (NULL != pptszResult[2])
		{
			_tcsxcpy(pSt_SLinkInfo->tszShotUrl, pptszResult[2]);
		}
		if (NULL != pptszResult[3])
		{
			_tcsxcpy(pSt_SLinkInfo->tszKeyUrl, pptszResult[3]);
		}
		if (NULL != pptszResult[4])
		{
			_tcsxcpy(pSt_SLinkInfo->tszMapUrl, pptszResult[4]);
		}
		if (NULL != pptszResult[5])
		{
			_tcsxcpy(pSt_SLinkInfo->tszCreateTime, pptszResult[5]);
		}
	}
	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_ShortLink_Delete
函数功能：删除短连接
 参数.一：pSt_SLinkInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要删除的短连接
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_ShortLink::ModuleDatabase_ShortLink_Delete(XENGINE_SHORTLINK* pSt_SLinkInfo)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_SLinkInfo)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[1024];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	if (_tcsxlen(pSt_SLinkInfo->tszFullUrl) > 0)
	{
		_xstprintf(tszSQLStatement, _X("DELETE FROM `XEngine_ShortLink` WHERE tszFullUrl = '%s'"), pSt_SLinkInfo->tszFullUrl);
	}
	else
	{
		_xstprintf(tszSQLStatement, _X("DELETE FROM `XEngine_ShortLink` WHERE tszMapUrl = '%s'"), pSt_SLinkInfo->tszMapUrl);
	}
	
	if (!DataBase_MySQL_Execute(xhDBSQL, tszSQLStatement))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}