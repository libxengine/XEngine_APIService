#include "XEngine_Hdr.h"
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
bool XEngine_Configure_Parament(int argc, char** argv)
{
	LPCXSTR lpszConfigFile = _X("./XEngine_Config/XEngine_Config.json");
	LPCXSTR lpszVersionFile = _X("./XEngine_Config/XEngine_VersionConfig.json");

	if (NULL != st_ServiceConfig.st_XVer.pStl_ListVer)
	{
		delete st_ServiceConfig.st_XVer.pStl_ListVer;
		st_ServiceConfig.st_XVer.pStl_ListVer = NULL;
	}
	memset(&st_ServiceConfig, '\0', sizeof(XENGINE_SERVICECONFIG));
	if (!ModuleConfigure_Json_File(lpszConfigFile, &st_ServiceConfig))
	{
		printf("解析配置文件失败,ModuleConfigure_Json_File:%lX\n", ModuleConfigure_GetLastError());
		return false;
	}
	if (!ModuleConfigure_Json_VersionFile(lpszVersionFile, &st_ServiceConfig))
	{
		printf("解析配置文件失败,ModuleConfigure_Json_VersionFile:%lX\n", ModuleConfigure_GetLastError());
		return false;
	}

	for (int i = 0; i < argc; i++)
	{
		if ((0 == _tcsxcmp("-h", argv[i])) || (0 == _tcsxcmp("-H", argv[i])))
		{
			XEngine_Configure_Help();
			return false;
		}
		else if (0 == _tcsxcmp("-d", argv[i]))
		{
			st_ServiceConfig.bDeamon = _ttxoi(argv[i + 1]);
		}
		else if (0 == _tcsxcmp("-r", argv[i]))
		{
			st_ServiceConfig.st_XReload.bReload = true;
			st_ServiceConfig.st_XReload.byCode = _ttxoi(argv[i + 1]);
		}
		else if (0 == _tcsxcmp("-t", argv[i]))
		{
			bIsTest = true;
		}
	}

	return true;
}

void XEngine_Configure_Help()
{
	printf(_X("--------------------------启动参数帮助开始--------------------------\n"));
	printf(_X("网络消息队列服务启动参数：程序 参数 参数值，参数是区分大小写的。如果不指定将会加载默认的ini配置文件里面的参数\n"));
	printf(_X("-h or -H：启动参数帮助提示信息\n"));
	printf(_X("-d：1 启用守护进程，2不启用\n"));
	printf(_X("--------------------------启动参数帮助结束--------------------------\n"));
}
