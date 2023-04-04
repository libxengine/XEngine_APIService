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
	XBOOL ModuleDatabase_XLog_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector);
	XBOOL ModuleDatabase_XLog_Destory();
	XBOOL ModuleDatabase_XLog_Create(LPCXSTR lpszTableName);
	XBOOL ModuleDatabase_XLog_Insert(XENGINE_XLOGINFO* pSt_XLogInfo);
	XBOOL ModuleDatabase_XLog_Query(XENGINE_XLOGINFO*** pppSt_XLogInfo, int* pInt_ListCount, LPCXSTR lpszTableName, LPCXSTR lpszTimeStart, LPCXSTR lpszTimeEnd);
	XBOOL ModuleDatabase_XLog_Delete(LPCXSTR lpszTableName);
protected:
private:
	XNETHANDLE xhDBSQL;
};