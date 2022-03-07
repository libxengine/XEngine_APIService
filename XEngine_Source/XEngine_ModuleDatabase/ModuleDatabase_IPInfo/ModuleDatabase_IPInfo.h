#pragma once
/********************************************************************
//    Created:     2022/03/04  14:24:30
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_IPInfo\ModuleDatabase_IPInfo.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_IPInfo
//    File Base:   ModuleDatabase_IPInfo
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     IP数据库信息操作
//    History:
*********************************************************************/


class CModuleDatabase_IPInfo
{
public:
	CModuleDatabase_IPInfo();
	~CModuleDatabase_IPInfo();
public:
	BOOL ModuleDatabase_IPInfo_Init(LPCTSTR lpszSQLFile);
	BOOL ModuleDatabase_IPInfo_Destory();
	BOOL ModuleDatabase_IPInfo_IPV4Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo, LPCTSTR lpszIPAddr);
	BOOL ModuleDatabase_IPInfo_IPV6Query(XENGINE_IPADDRINFO* pSt_IPAddrInfo, LPCTSTR lpszIPAddr);
private:
	XHDATA xhSQL;
};