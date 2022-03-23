#pragma once
/********************************************************************
//    Created:     2022/03/23  09:02:07
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Bank\ModuleDatabase_Bank.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Bank
//    File Base:   ModuleDatabase_Bank
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     银行卡数据库操作
//    History:
*********************************************************************/


class CModuleDatabase_Bank
{
public:
	CModuleDatabase_Bank();
	~CModuleDatabase_Bank();
public:
	BOOL ModuleDatabase_Bank_Init(LPCTSTR lpszSQLFile);
	BOOL ModuleDatabase_Bank_Destory();
	BOOL ModuleDatabase_Bank_Query(XENGINE_BANKINFO* pSt_BankInfo);
protected:
private:
	XHDATA xhSQL;
};