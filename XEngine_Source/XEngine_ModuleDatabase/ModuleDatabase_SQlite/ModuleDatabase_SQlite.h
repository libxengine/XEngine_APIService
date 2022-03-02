#pragma once
/********************************************************************
//    Created:     2022/02/28  10:13:36
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_SQlite\ModuleDatabase_SQlite.h
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_SQlite
//    File Base:   ModuleDatabase_SQlite
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     SQLITE操作类
//    History:
*********************************************************************/


class CModuleDatabase_SQlite
{
public:
	CModuleDatabase_SQlite();
	~CModuleDatabase_SQlite();
public:
	BOOL ModuleDatabase_SQlite_Init(LPCTSTR lpszSQLFile);
	BOOL ModuleDatabase_SQlite_Destory();
	BOOL ModuleDatabase_SQlite_IPV4Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo, LPCTSTR lpszIPAddr);
	BOOL ModuleDatabase_SQlite_IPV6Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo, LPCTSTR lpszIPAddr);
private:
	XHDATA xhSQL;
};