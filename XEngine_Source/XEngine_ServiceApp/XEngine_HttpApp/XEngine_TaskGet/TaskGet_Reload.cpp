#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_Reload(LPCXSTR lpszClientAddr, LPCXSTR lpszOPCode)
{
	int nMsgLen = 4096;
	XCHAR tszMsgBuffer[4096] = {};

	if (0 == _ttxoi(lpszOPCode))
	{
		XEngine_Configure_Parament(0, NULL);
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求操作配置重载成功,操作的配置:%s"), lpszClientAddr, lpszOPCode);
	}
	else if (1 == _ttxoi(lpszOPCode))
	{
		int nLuaCount = 0;
		int nLibCount = 0;
		XCHAR** pptszListFile;
		XENGINE_PLUGINPARAM st_PluginParam = {};
		_tcsxcpy(st_PluginParam.tszAPIVersion, st_ServiceConfig.st_XVer.pStl_ListVer->front().c_str());
		_tcsxcpy(st_PluginParam.tszXEngineVer, BaseLib_Version_XNumberStr());

		PluginExtension_Loader_Destory();
		PluginExtension_Loader_Init();
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求操作配置重载成功,加载插件配置成功"), lpszClientAddr);
		{
			SystemApi_File_EnumFileA(st_ServiceConfig.st_XPlugin.tszLibPlugin, &pptszListFile, &nLibCount, false, 1);
			for (int i = 0; i < nLibCount; i++)
			{
				//加载插件
				PluginExtension_Loader_Insert(pptszListFile[i], 0, &st_PluginParam);
			}
			BaseLib_Memory_Free((XPPPMEM)&pptszListFile, nLibCount);
		}
		{
			SystemApi_File_EnumFileA(st_ServiceConfig.st_XPlugin.tszLuaPlugin, &pptszListFile, &nLuaCount, false, 1);
			for (int i = 0; i < nLuaCount; i++)
			{
				PluginExtension_Loader_Insert(pptszListFile[i], 1, &st_PluginParam);
			}
		}
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求重载插件成功,Lib插件:%d 个,Lua插件:%d 个"), lpszClientAddr, nLibCount, nLuaCount);
	}
	else if (2 == _ttxoi(lpszOPCode))
	{
		st_DeamonAppConfig.stl_ListDeamonApp.clear();
		if (!ModuleConfigure_Json_DeamonList(st_ServiceConfig.st_XConfig.tszConfigDeamon, &st_DeamonAppConfig))
		{
			ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_RELOAD,_X("reload configure failure"));
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求重载进程守护配置文件失败,错误：%lX"), lpszClientAddr, ModuleConfigure_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求重载进程守护配置文件成功"));
	}
	return true;
}