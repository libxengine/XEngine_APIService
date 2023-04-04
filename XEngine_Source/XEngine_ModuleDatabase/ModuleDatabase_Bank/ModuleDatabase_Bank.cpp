#include "pch.h"
#include "ModuleDatabase_Bank.h"
/********************************************************************
//    Created:     2022/03/23  09:02:22
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Bank\ModuleDatabase_Bank.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Bank
//    File Base:   ModuleDatabase_Bank
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     银行卡数据库操作
//    History:
*********************************************************************/
CModuleDatabase_Bank::CModuleDatabase_Bank()
{
}
CModuleDatabase_Bank::~CModuleDatabase_Bank()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_Bank_Init
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
XBOOL CModuleDatabase_Bank::ModuleDatabase_Bank_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector)
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
函数名称：ModuleDatabase_Bank_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleDatabase_Bank::ModuleDatabase_Bank_Destory()
{
	DBModule_IsErrorOccur = FALSE;

	DataBase_MySQL_Close(xhDBSQL);
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_Bank_Query
函数功能：通过银行缩写获得银行名称
 参数.一：pSt_BankInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的名称,输出银行名称
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleDatabase_Bank::ModuleDatabase_Bank_Query(XENGINE_BANKINFO* pSt_BankInfo)
{
    DBModule_IsErrorOccur = FALSE;

    if (NULL == pSt_BankInfo)
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
	_stprintf(tszSQLStatement, _T("SELECT * FROM `BankList` WHERE tszBankAbridge = '%s'"), pSt_BankInfo->tszBankAbridge);
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
	_tcscpy(pSt_BankInfo->tszBankName, pptszResult[2]);

	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return TRUE;
}