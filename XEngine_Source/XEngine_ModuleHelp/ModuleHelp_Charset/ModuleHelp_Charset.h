#pragma once
/********************************************************************
//    Created:     2022/03/23  13:54:45
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Charset\ModuleHelp_Charset.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Charset
//    File Base:   ModuleHelp_Charset
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     字符集转换
//    History:
*********************************************************************/


class CModuleHelp_Charset
{
public:
	CModuleHelp_Charset();
	~CModuleHelp_Charset();
public:
	BOOL ModuleHelp_Charset_Convert(LPCTSTR lpszJsonFile, LPCTSTR lpszSourceStr, TCHAR* ptszDestStr);
private:
};