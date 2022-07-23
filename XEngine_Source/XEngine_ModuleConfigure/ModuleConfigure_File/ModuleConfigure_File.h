#pragma once
/********************************************************************
//    Created:     2022/07/21  17:07:01
//    File Name:   H:\XEngine_APIService\XEngine_Source\XEngine_ModuleConfigure\ModuleConfigure_File\ModuleConfigure_File.h
//    File Path:   H:\XEngine_APIService\XEngine_Source\XEngine_ModuleConfigure\ModuleConfigure_File
//    File Base:   ModuleConfigure_File
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     文件信息读写
//    History:
*********************************************************************/

class CModuleConfigure_File
{
public:
	CModuleConfigure_File();
	~CModuleConfigure_File();
public:
	BOOL ModuleConfigure_File_OPtion(LPCTSTR lpszConfigFile, XENGINE_OPTIONLIST* pSt_OPtionList);
protected:
private:
};