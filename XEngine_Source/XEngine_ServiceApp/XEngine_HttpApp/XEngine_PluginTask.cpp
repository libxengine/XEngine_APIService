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
XBOOL XEngine_PluginTask_Handle(LPCXSTR lpszMethodName, LPCXSTR lpszClientAddr, LPCXSTR lpszRVBuffer, int nRVLen, XCHAR*** ppptszList, int nListCount, int nPluginType)
{
	int nMsgLen = 0;
	int nPktLen = 0;
	XCHAR tszMsgBuffer[2048];
	XCHAR tszPktBuffer[2048];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParament;

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(&st_HDRParament, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParament.bIsClose = TRUE;
	st_HDRParament.nHttpCode = 200;
	_tcsxcpy(st_HDRParament.tszMimeType, "json");

	if (ModulePlugin_Loader_Exec(lpszMethodName, ppptszList, nListCount, &st_HDRParament.nHttpCode, tszPktBuffer, &nPktLen))
	{
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParament, tszPktBuffer, nPktLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的方法:%s,由%s插件模块处理成功"), lpszClientAddr, lpszMethodName, 0 == nPluginType ? "Lib" : "Lua");
	}
	else
	{
		st_HDRParament.nHttpCode = 400;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParament);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的方法:%s,由%s插件模块处理失败,错误:%lX"), lpszClientAddr, lpszMethodName, 0 == nPluginType ? "Lib" : "Lua", ModulePlugin_GetLastError());
	}
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	return TRUE;
}