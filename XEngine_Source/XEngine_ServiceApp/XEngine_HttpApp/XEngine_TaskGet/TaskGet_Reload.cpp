#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_Reload(LPCXSTR lpszClientAddr, LPCXSTR lpszOPCode)
{
	int nMsgLen = 4096;
	XCHAR tszMsgBuffer[4096];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	if (0 == _ttxoi(lpszOPCode))
	{
		XEngine_Configure_Parament(0, NULL);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求操作配置重载成功,操作的配置:%s"), lpszClientAddr, lpszOPCode);
	}
	else if (1 == _ttxoi(lpszOPCode))
	{
		ModulePlugin_Loader_Destory();
		delete st_PluginLibConfig.pStl_ListPlugin;
		delete st_PluginLuaConfig.pStl_ListPlugin;
		st_PluginLibConfig.pStl_ListPlugin = NULL;
		st_PluginLuaConfig.pStl_ListPlugin = NULL;

		ModulePlugin_Loader_Init();
		if (!ModuleConfigure_Json_PluginFile(st_ServiceConfig.st_XPlugin.tszPluginLib, &st_PluginLibConfig))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求操作配置重载失败,加载Lib插件配置失败,错误：%lX"), lpszClientAddr, ModuleConfigure_GetLastError());
			return false;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求操作配置重载成功,加载Lib插件配置成功"), lpszClientAddr);
		if (!ModuleConfigure_Json_PluginFile(st_ServiceConfig.st_XPlugin.tszPluginLua, &st_PluginLuaConfig))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求操作配置重载失败,加载Lua插件配置失败,错误：%lX"), lpszClientAddr, ModuleConfigure_GetLastError());
			return false;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求操作配置重载成功,加载lua插件配置成功"), lpszClientAddr);

		{
			list<XENGINE_PLUGININFO>::const_iterator stl_ListIterator = st_PluginLibConfig.pStl_ListPlugin->begin();
			for (int i = 1; stl_ListIterator != st_PluginLibConfig.pStl_ListPlugin->end(); stl_ListIterator++, i++)
			{
				if (stl_ListIterator->bEnable)
				{
					if (ModulePlugin_Loader_Insert(stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile, 0))
					{
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,重载Lib模块插件中,当前第:%d 个加载成功,方法:%s,路径:%s"), lpszClientAddr, i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile);
					}
					else
					{
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,重载Lib模块插件中,当前第:%d 个加载失败,方法:%s,路径:%s,错误:%lX"), lpszClientAddr, i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile, ModulePlugin_GetLastError());
					}
				}
				else
				{
					XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("HTTP客户端:%s,重载Lib模块插件中,当前第:%d 个加载失败,因为没有启用,方法:%s,路径:%s"), lpszClientAddr, i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile);
				}
			}
		}
		{
			list<XENGINE_PLUGININFO>::const_iterator stl_ListIterator = st_PluginLuaConfig.pStl_ListPlugin->begin();
			for (int i = 1; stl_ListIterator != st_PluginLuaConfig.pStl_ListPlugin->end(); stl_ListIterator++, i++)
			{
				if (stl_ListIterator->bEnable)
				{
					if (ModulePlugin_Loader_Insert(stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile, 1))
					{
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,重载Lua模块插件中,当前第:%d 个加载成功,方法:%s,路径:%s"), lpszClientAddr, i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile);
					}
					else
					{
						XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,重载Lua模块插件中,当前第:%d 个加载失败,方法:%s,路径:%s,错误:%lX"), lpszClientAddr, i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile, ModulePlugin_GetLastError());
					}
				}
				else
				{
					XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("HTTP客户端:%s,重载Lua模块插件中,当前第:%d 个加载失败,因为没有启用,方法:%s,路径:%s"), lpszClientAddr, i, stl_ListIterator->tszPluginMethod, stl_ListIterator->tszPluginFile);
				}
			}
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求重载插件成功,Lib插件:%d 个,Lua插件:%d 个"), lpszClientAddr, st_PluginLibConfig.pStl_ListPlugin->size(), st_PluginLuaConfig.pStl_ListPlugin->size());
	}
	else if (2 == _ttxoi(lpszOPCode))
	{
		memset(&st_OPenccConfig, '\0', sizeof(XENGINE_OPENCCCONFIG));
		//重载OPENCC配置
		if (!ModuleConfigure_Json_OPenccFile(st_ServiceConfig.st_XConfig.tszConfigOPencc, &st_OPenccConfig))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求重载OPenCC配置文件失败,错误：%lX"), lpszClientAddr, ModuleConfigure_GetLastError());
			return false;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求重载OPenCC配置文件:%s 成功"), lpszClientAddr, st_ServiceConfig.st_XConfig.tszConfigOPencc);
	}
	else if (3 == _ttxoi(lpszOPCode))
	{
		memset(&st_QRCodeConfig, '\0', sizeof(XENGINE_QRCODECONFIG));
		if (!ModuleConfigure_Json_QRCodeFile(st_ServiceConfig.st_XConfig.tszConfigQRCode, &st_QRCodeConfig))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求重载二维码配置文件失败,错误：%lX"), lpszClientAddr, ModuleConfigure_GetLastError());
			return false;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求重载二维码配置文件:%s 成功"), lpszClientAddr, st_ServiceConfig.st_XConfig.tszConfigQRCode);
	}
	else if (4 == _ttxoi(lpszOPCode))
	{
		st_DeamonAppConfig.stl_ListDeamonApp.clear();
		if (!ModuleConfigure_Json_DeamonList(st_ServiceConfig.st_XConfig.tszConfigDeamon, &st_DeamonAppConfig))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求重载进程守护配置文件失败,错误：%lX"), lpszClientAddr, ModuleConfigure_GetLastError());
			return false;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求重载进程守护配置文件成功"));
	}
	return true;
}