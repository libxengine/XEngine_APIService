#include "pch.h"
#include "ModuleDatabase_XLog.h"
/********************************************************************
//    Created:     2023/01/11  13:49:59
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_XLog\ModuleDatabase_XLog.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_XLog
//    File Base:   ModuleDatabase_XLog
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     日志服务数据库
//    History:
*********************************************************************/
CModuleDatabase_XLog::CModuleDatabase_XLog()
{
}
CModuleDatabase_XLog::~CModuleDatabase_XLog()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_XLog_Init
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
bool CModuleDatabase_XLog::ModuleDatabase_XLog_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_DBConnector)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	//连接数据库
	_tcsxcpy(pSt_DBConnector->tszDBName, _X("XEngine_APILog"));
	if (!DataBase_MySQL_Connect(&xhDBSQL, pSt_DBConnector))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_XLog_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_XLog::ModuleDatabase_XLog_Destory()
{
	DBModule_IsErrorOccur = false;

	DataBase_MySQL_Close(xhDBSQL);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_XLog_Create
函数功能：创建一个日志服务表
 参数.一：lpszTableName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：创建的名称
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_XLog::ModuleDatabase_XLog_Create(LPCXSTR lpszTableName)
{
	DBModule_IsErrorOccur = false;

	if (NULL == lpszTableName)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[4096];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("CREATE TABLE IF NOT EXISTS `%s` ("
	"`ID` int NOT NULL AUTO_INCREMENT,"
	"`tszFileName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL DEFAULT NULL COMMENT '文件名',"
	"`tszFuncName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL DEFAULT NULL COMMENT '函数名',"
	"`nLogLine` int NULL DEFAULT NULL COMMENT '第几行',"
	"`nLogLevel` int NULL DEFAULT NULL COMMENT '打印级别',"
	"`tszLogBuffer` varchar(8196) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '日志信息',"
	"`tszLogTime` datetime NOT NULL COMMENT '日志时间',"
		"PRIMARY KEY (`ID`) USING BTREE"
	") ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;"), lpszTableName);

#ifdef _MSC_BUILD
	int nUTFLen = 0;
	XCHAR tszUTFQuery[4096] = {};
	BaseLib_Charset_AnsiToUTF(tszSQLStatement, tszUTFQuery, &nUTFLen);
	if (!DataBase_MySQL_Execute(xhDBSQL, tszUTFQuery))
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
函数名称：ModuleDatabase_XLog_Insert
函数功能：查询身份证位置信息
 参数.一：pSt_IDRegion
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要插入的日志信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_XLog::ModuleDatabase_XLog_Insert(XENGINE_XLOGINFO* pSt_XLogInfo)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_XLogInfo)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[11240];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("INSERT INTO `%s` (tszFileName,tszFuncName,nLogLine,nLogLevel,tszLogBuffer,tszLogTime) VALUES('%s','%s',%d,%d,'%s','%s')"), pSt_XLogInfo->tszTableName, pSt_XLogInfo->st_ProtocolLog.tszFileName, pSt_XLogInfo->st_ProtocolLog.tszFuncName, pSt_XLogInfo->st_ProtocolLog.nLogLine, pSt_XLogInfo->st_ProtocolLog.nLogLevel, pSt_XLogInfo->tszLogBuffer, pSt_XLogInfo->st_ProtocolLog.tszLogTimer);
	
#ifdef _MSC_BUILD
	XCHAR tszUTFStr[10240] = {};
	int nSLen = _tcsxlen(tszSQLStatement);
	BaseLib_Charset_AnsiToUTF(tszSQLStatement, tszUTFStr, &nSLen);
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
函数名称：ModuleDatabase_XLog_Query
函数功能：日志信息查询
 参数.一：pppSt_XLogInfo
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出查询到的数据
 参数.二：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出数据个数
 参数.三：lpszTableName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入表名称
 参数.四：lpszTimeStart
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入开始时间
 参数.五：lpszTimeEnd
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入结束时间
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_XLog::ModuleDatabase_XLog_Query(XENGINE_XLOGINFO*** pppSt_XLogInfo, int* pInt_ListCount, LPCXSTR lpszTableName, LPCXSTR lpszTimeStart, LPCXSTR lpszTimeEnd)
{
	DBModule_IsErrorOccur = false;

	if ((NULL == lpszTableName) || (NULL == lpszTimeStart) || (NULL == lpszTimeEnd))
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
	_xstprintf(tszSQLStatement, _X("SELECT * FROM `%s` WHERE tszLogTime BETWEEN  '%s' AND '%s'"), lpszTableName, lpszTimeStart, lpszTimeEnd);

#ifdef _MSC_BUILD
	XCHAR tszUTFStr[1024] = {};
	int nSLen = _tcsxlen(tszSQLStatement);
	BaseLib_Charset_AnsiToUTF(tszSQLStatement, tszUTFStr, &nSLen);
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
	*pInt_ListCount = (int)nllLine;
	BaseLib_Memory_Malloc((XPPPMEM)pppSt_XLogInfo, (int)nllLine, sizeof(XENGINE_XLOGINFO));
	for (__int64u i = 0; i < nllLine; i++)
	{
		XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);

		_tcsxcpy((*pppSt_XLogInfo)[i]->tszTableName, lpszTableName);
		if (NULL != pptszResult[1])
		{
			_tcsxcpy((*pppSt_XLogInfo)[i]->st_ProtocolLog.tszFileName, pptszResult[1]);
		}
		if (NULL != pptszResult[2])
		{
			_tcsxcpy((*pppSt_XLogInfo)[i]->st_ProtocolLog.tszFuncName, pptszResult[2]);
		}
		if (NULL != pptszResult[3])
		{
			(*pppSt_XLogInfo)[i]->st_ProtocolLog.nLogLine = _ttxoi(pptszResult[3]);
		}
		if (NULL != pptszResult[4])
		{
			(*pppSt_XLogInfo)[i]->st_ProtocolLog.nLogLevel = _ttxoi(pptszResult[4]);
		}
		if (NULL != pptszResult[5])
		{
			_tcsxcpy((*pppSt_XLogInfo)[i]->tszLogBuffer, pptszResult[5]);
		}
		if (NULL != pptszResult[6])
		{
			_tcsxcpy((*pppSt_XLogInfo)[i]->st_ProtocolLog.tszLogTimer, pptszResult[6]);
		}
	}
	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_XLog_Delete
函数功能：删除日志表
 参数.一：lpszTableName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：删除的名称
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_XLog::ModuleDatabase_XLog_Delete(LPCXSTR lpszTableName)
{
	DBModule_IsErrorOccur = false;

	if (NULL == lpszTableName)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[10240];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("DROP TABLE IF EXISTS `%s`"), lpszTableName);
	if (!DataBase_MySQL_Execute(xhDBSQL, tszSQLStatement))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_XLog_Show
函数功能：日志表列举
 参数.一：ppptszList
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出日志数据库里面的表列
 参数.二：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出列个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_XLog::ModuleDatabase_XLog_Show(XCHAR*** ppptszList, int* pInt_ListCount)
{
	DBModule_IsErrorOccur = false;

	//查询
	XNETHANDLE xhTable = 0;
	__int64u nllLine = 0;
	__int64u nllRow = 0;

	XCHAR tszSQLStatement[1024];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	//名称为,消息名为必填
	_xstprintf(tszSQLStatement, _X("SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'XEngine_APILog'"));
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
	*pInt_ListCount = (int)nllLine;
	BaseLib_Memory_Malloc((XPPPMEM)ppptszList, (int)nllLine, XPATH_MAX);
	for (__int64u i = 0; i < nllLine; i++)
	{
		XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);
		_tcsxcpy((*ppptszList)[i], pptszResult[0]);
	}
	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}