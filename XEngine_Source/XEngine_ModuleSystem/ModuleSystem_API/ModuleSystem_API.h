#pragma once
/********************************************************************
//    Created:     2023/09/06  13:49:59
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem\ModuleSystem_API\ModuleSystem_API.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem\ModuleSystem_API
//    File Base:   ModuleSystem_API
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     系统API函数库
//    History:
*********************************************************************/

class CModuleSystem_API
{
public:
	CModuleSystem_API();
	~CModuleSystem_API();
public:
	bool ModuleSystem_API_AutoStart(bool bIsAuto = true);
protected:
private:
};