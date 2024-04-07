#pragma once
/********************************************************************
//    Created:     2024/04/07  10:37:03
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Machine\ModuleDatabase_Machine.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Machine
//    File Base:   ModuleDatabase_Machine
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     机器信息收集数据库
//    History:
*********************************************************************/


class CModuleDatabase_Machine
{
public:
	CModuleDatabase_Machine();
	~CModuleDatabase_Machine();
public:
	bool ModuleDatabase_Machine_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector);
	bool ModuleDatabase_Machine_Destory();
	bool ModuleDatabase_Machine_Insert(XENGINE_MACHINEINFO* pSt_MachineInfo);
	bool ModuleDatabase_Machine_Query(XENGINE_MACHINEINFO* pSt_MachineInfo);
	bool ModuleDatabase_Machine_Delete(XENGINE_MACHINEINFO* pSt_MachineInfo);
protected:
private:
	XNETHANDLE xhDBSQL;
};