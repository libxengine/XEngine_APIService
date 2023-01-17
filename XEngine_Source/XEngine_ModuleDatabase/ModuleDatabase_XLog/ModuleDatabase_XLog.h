#pragma once
/********************************************************************
//    Created:     2023/01/11  13:45:32
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_XLog\ModuleDatabase_XLog.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_XLog
//    File Base:   ModuleDatabase_XLog
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     日志服务数据库
//    History:
*********************************************************************/


class CModuleDatabase_XLog
{
public:
	CModuleDatabase_XLog();
	~CModuleDatabase_XLog();
public:
	BOOL ModuleDatabase_XLog_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector);
	BOOL ModuleDatabase_XLog_Destory();
	BOOL ModuleDatabase_XLog_Create(LPCTSTR lpszTableName);
	BOOL ModuleDatabase_XLog_Insert(XENGINE_XLOGINFO* pSt_XLogInfo);
	BOOL ModuleDatabase_XLog_Query(XENGINE_XLOGINFO*** pppSt_XLogInfo, int* pInt_ListCount, LPCTSTR lpszTableName, LPCTSTR lpszTimeStart, LPCTSTR lpszTimeEnd);
	BOOL ModuleDatabase_XLog_Delete(LPCTSTR lpszTableName);
protected:
private:
	XNETHANDLE xhDBSQL;
};