#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/01/20  14:44:17
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp\XEngine_HTTPTask.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp
//    File Base:   XEngine_HTTPTask
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     HTTP任务处理代码
//    History:
*********************************************************************/
bool XEngine_PluginTask_Handle(LPCXSTR lpszMethodName, LPCXSTR lpszClientAddr, LPCXSTR lpszRVBuffer, int nRVLen, XCHAR*** ppptszList, int nListCount, int nPluginType)
{
	int nPktLen = 0;
	XCHAR tszPktBuffer[2048] = {};

	if (PluginExtension_Loader_Exec(lpszMethodName, tszPktBuffer, &nPktLen, lpszRVBuffer, nRVLen, ppptszList, nListCount))
	{
		XEngine_Network_Send(lpszClientAddr, tszPktBuffer, nPktLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的方法:%s,由%s插件模块处理成功"), lpszClientAddr, lpszMethodName, 0 == nPluginType ? "Lib" : "Lua");
	}
	else
	{
		ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, 500, _X("plugin process failure"));
		XEngine_Network_Send(lpszClientAddr, tszPktBuffer, nPktLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的方法:%s,由%s插件模块处理失败,错误:%lX"), lpszClientAddr, lpszMethodName, 0 == nPluginType ? "Lib" : "Lua", PluginExtension_GetLastError());
	}
	return true;
}