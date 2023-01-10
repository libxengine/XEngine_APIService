#pragma once
/********************************************************************
//    Created:     2022/03/04  14:23:55
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_IDCard\ModuleDatabase_IDCard.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_IDCard
//    File Base:   ModuleDatabase_IDCard
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     身份证信息数据库操作
//    History:
*********************************************************************/


class CModuleDatabase_IDCard
{
public:
	CModuleDatabase_IDCard();
	~CModuleDatabase_IDCard();
public:
	BOOL ModuleDatabase_IDCard_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector);
	BOOL ModuleDatabase_IDCard_Destory();
	BOOL ModuleDatabase_IDCard_QueryRegion(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo);
protected:
	BOOL ModuleDatabase_IDCard_QueryProvincer(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo);
	BOOL ModuleDatabase_IDCard_QueryCity(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo);
	BOOL ModuleDatabase_IDCard_QueryCounty(XENGINE_IDREGION* pSt_IDRegion, XENGINE_IDCARDINFO* pSt_IDInfo);
private:
	XNETHANDLE xhDBSQL;
};