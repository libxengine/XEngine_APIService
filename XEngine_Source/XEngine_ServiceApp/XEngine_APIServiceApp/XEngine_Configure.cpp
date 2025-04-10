#include "XEngine_CommHdr.h"
/********************************************************************
//    Created:     2022/01/20  14:40:45
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp\XEngine_Configure.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp
//    File Base:   XEngine_Configure
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     配置文件操作代码
//    History:
*********************************************************************/
bool XEngine_Configure_Parament(int argc, wchar_t* argv[])
{
	LPCXSTR lpszConfigFile = _X("./XEngine_Config/XEngine_Config.json");

	if (!ModuleConfigure_Json_File(lpszConfigFile, &st_ServiceConfig))
	{
		printf("解析配置文件失败,ModuleConfigure_Json_File:%lX\n", ModuleConfigure_GetLastError());
		return false;
	}

	return true;
}