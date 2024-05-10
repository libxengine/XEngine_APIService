#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_Oil(LPCXSTR lpszClientAddr, LPCXSTR lpszCityStr)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	XCHAR tszMsgBuffer[4096];
	XCHAR tszPktBuffer[4096];
	
	XENGINE_OILINFO st_OilInfo = {};
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	if (!st_ServiceConfig.st_XSql.bEnable)
	{
		ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, 501, _X("function is closed"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的油价查询功能已经被服务器关闭,无法继续"), lpszClientAddr);
		return false;
	}
	_tcsxcpy(st_OilInfo.tszCityStr, lpszCityStr);
	if (!ModuleDatabase_OilInfo_Query(&st_OilInfo))
	{
		ModuleProtocol_Packet_IDQuery(tszPktBuffer, &nPktLen, NULL, NULL, 1001, _X("city name is incorrent"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的油价查询不正确,城市名:%s"), lpszClientAddr, lpszCityStr);
		return false;
	}
	ModuleProtocol_Packet_OilInfo(tszPktBuffer, &nPktLen, &st_OilInfo);
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求油价查询成功,城市名:%s"), lpszClientAddr, lpszCityStr);
	return true;
}