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
BOOL XEngine_PluginTask_Handle(LPCTSTR lpszMethodName, LPCTSTR lpszClientAddr, LPCTSTR lpszRVBuffer, int nRVLen, TCHAR*** ppptszList, int nListCount)
{
	int nMsgLen = 0;
	int nPktLen = 0;
	TCHAR tszMsgBuffer[2048];
	TCHAR tszPktBuffer[2048];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParament;

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(&st_HDRParament, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParament.bIsClose = TRUE;
	_tcscpy(st_HDRParament.tszMimeType, "json");

	ModulePlugin_Loader_Exec(lpszMethodName, ppptszList, nListCount, &st_HDRParament.nHttpCode, tszPktBuffer, &nPktLen);
	RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParament, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求的方法:%s,由插件模块处理成功"), lpszClientAddr, lpszMethodName);
	return TRUE;
}