#pragma once
/********************************************************************
//    Created:     2022/10/27  16:15:22
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_ZIPCode\ModuleDatabase_ZIPCode.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_ZIPCode
//    File Base:   ModuleDatabase_ZIPCode
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     邮政编码地址信息数据库
//    History:
*********************************************************************/


class CModuleDatabase_ZIPCode
{
public:
	CModuleDatabase_ZIPCode();
	~CModuleDatabase_ZIPCode();
public:
	XBOOL ModuleDatabase_ZIPCode_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector);
	XBOOL ModuleDatabase_ZIPCode_Destory();
	XBOOL ModuleDatabase_ZIPCode_QueryZIPCode(XENGINE_ZIPINFO* pSt_ZIPInfo);
	XBOOL ModuleDatabase_ZIPCode_QueryName(XENGINE_ZIPINFO* pSt_ZIPInfo);
protected:
	XBOOL ModuleDatabase_ZIPCode_QueryParentByID(int nParentID, XCHAR* ptszParentStr, int* pInt_ParentID = NULL);
	XBOOL ModuleDatabase_ZIPCode_QueryParentByName(LPCXSTR lpszName, int* pInt_ParentID = NULL);
private:
	XNETHANDLE xhDBSQL;
};