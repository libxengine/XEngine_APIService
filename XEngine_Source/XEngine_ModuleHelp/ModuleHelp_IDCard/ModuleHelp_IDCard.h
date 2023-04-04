#pragma once
/********************************************************************
//    Created:     2022/03/03  13:59:35
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_IDCard\ModuleHelp_IDCard.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_IDCard
//    File Base:   ModuleHelp_IDCard
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     身份证处理
//    History:
*********************************************************************/


class CModuleHelp_IDCard
{
public:
	CModuleHelp_IDCard();
	~CModuleHelp_IDCard();
public:
	XBOOL ModuleHelp_IDCard_CheckBirth(XENGINE_IDCARDINFO* pSt_IDInfo);
	XBOOL ModuleHelp_IDCard_CheckSum(XENGINE_IDCARDINFO* pSt_IDInfo);
private:
};