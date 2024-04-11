#pragma once
/********************************************************************
//    Created:     2023/08/09  10:56:39
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_WordFilter\ModuleDatabase_WordFilter.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_WordFilter
//    File Base:   ModuleDatabase_WordFilter
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     敏感词过滤器
//    History:
*********************************************************************/


class CModuleDatabase_WordFilter
{
public:
	CModuleDatabase_WordFilter();
	~CModuleDatabase_WordFilter();
public:
	bool ModuleDatabase_WordFilter_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector);
	bool ModuleDatabase_WordFilter_Destory();
	bool ModuleDatabase_WordFilter_Query(XENGINE_WORDFILTER* pSt_WordFilter);
	bool ModuleDatabase_WordFilter_Insert(XENGINE_WORDFILTER* pSt_WordFilter);
	bool ModuleDatabase_WordFilter_Delete(XENGINE_WORDFILTER* pSt_WordFilter);
	bool ModuleDatabase_WordFilter_List(XENGINE_WORDFILTER*** pppSt_WordFilter, int* pInt_ListCount);
protected:
private:
	XNETHANDLE xhDBSQL;
};