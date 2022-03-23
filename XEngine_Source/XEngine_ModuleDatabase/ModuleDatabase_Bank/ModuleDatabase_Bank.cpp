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
BOOL CModuleDatabase_Bank::ModuleDatabase_Bank_Init(LPCTSTR lpszSQLFile)
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
函数名称：ModuleDatabase_Bank_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleDatabase_Bank::ModuleDatabase_Bank_Destory()
{
	DBModule_IsErrorOccur = FALSE;

	DataBase_SQLite_Close(xhSQL);
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_Bank_Query
函数功能：通过银行缩写获得银行名称
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要查询的内容
 参数.二：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出查询到的内容
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleDatabase_Bank::ModuleDatabase_Bank_Query(LPCTSTR lpszMsgBuffer, TCHAR* ptszMsgBuffer)
{
    DBModule_IsErrorOccur = FALSE;

    if ((NULL == lpszMsgBuffer) || (NULL == ptszMsgBuffer))
    {
        DBModule_IsErrorOccur = TRUE;
        DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_BANK_PARAMENT;
        return FALSE;
    }
    //查询
    int nLine = 0;
    int nRow = 0;
    TCHAR** pptszResult;
    TCHAR tszSQLStatement[1024];

    memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));
	_stprintf(tszSQLStatement, _T("SELECT * FROM `BankCard` WHERE tszBankAbridge = '%s'"), lpszMsgBuffer);
	if (!DataBase_SQLite_GetTable(xhSQL, tszSQLStatement, &pptszResult, &nLine, &nRow))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return FALSE;
	}
	if (nLine <= 0)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_BANK_NOTFOUND;
		return FALSE;
	}
	_tcscpy(ptszMsgBuffer, pptszResult[nRow + 1]);

	DataBase_SQLite_FreeTable(pptszResult);
	return TRUE;
}