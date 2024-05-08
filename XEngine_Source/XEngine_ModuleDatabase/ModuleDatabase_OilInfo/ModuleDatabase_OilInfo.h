#pragma once
/********************************************************************
//    Created:     2024/05/08  14:51:51
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_OilInfo\ModuleDatabase_OilInfo.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_OilInfo
//    File Base:   ModuleDatabase_OilInfo
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     油价信息查询接口
//    History:
*********************************************************************/


class CModuleDatabase_OilInfo
{
public:
	CModuleDatabase_OilInfo();
	~CModuleDatabase_OilInfo();
public:
	bool ModuleDatabase_OilInfo_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector);
	bool ModuleDatabase_OilInfo_Destory();
	bool ModuleDatabase_OilInfo_Query(XENGINE_OILINFO* pSt_OilInfo);
	bool ModuleDatabase_OilInfo_UPDate(XENGINE_OILINFO* pSt_OilInfo);
protected:
private:
	XNETHANDLE xhDBSQL;
};