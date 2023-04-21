#pragma once
/********************************************************************
//    Created:     2022/03/24  10:27:12
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Language\ModuleHelp_Language.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Language
//    File Base:   ModuleHelp_Language
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     语言转换
//    History:
*********************************************************************/

class CModuleHelp_Language
{
public:
	CModuleHelp_Language();
	~CModuleHelp_Language();
public:
	bool ModuleHelp_Language_ConvertZh(LPCXSTR lpszJsonFile, LPCXSTR lpszSourceStr, XCHAR* ptszDestStr);
	bool ModuleHelp_Translation_Convert(ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE enTranslationType, XCHAR* ptszTranslationType);
private:
};