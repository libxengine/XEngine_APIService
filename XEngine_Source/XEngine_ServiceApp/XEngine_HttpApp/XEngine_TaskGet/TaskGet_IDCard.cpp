#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_IDCard(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer)
{
	int nMsgLen = 4096;
	XCHAR tszMsgBuffer[4096];
	XENGINE_IDREGION st_IDRegion = {};
	XENGINE_IDCARDINFO st_IDCardInfo = {};

	if (!st_ServiceConfig.st_XSql.bEnable)
	{
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_DISABLE, _X("function is closed"));
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的ID查询功能已经被服务器关闭,无法继续"), lpszClientAddr);
		return false;
	}
	if (!ModuleProtocol_Parse_IDCard(lpszMsgBuffer, &st_IDCardInfo))
	{
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_NOTFOUND, _X("id number is incorrent"));
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的身份证编号不正确:%s"), lpszClientAddr, lpszMsgBuffer);
		return false;
	}
	//验证身份证是否正确
	if (!ModuleHelp_IDCard_CheckBirth(&st_IDCardInfo))
	{
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_NOTFOUND, _X("id number is incorrent"));
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的身份证验证生日失败:%s"), lpszClientAddr, lpszMsgBuffer);
		return false;
	}
	if (!ModuleHelp_IDCard_CheckSum(&st_IDCardInfo))
	{
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_NOTFOUND, _X("not found"));
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的身份证验证校验码失败:%s"), lpszClientAddr, lpszMsgBuffer);
		return false;
	}
	ModuleDatabase_IDCard_QueryRegion(&st_IDRegion, &st_IDCardInfo);
	ModuleProtocol_Packet_IDQuery(tszMsgBuffer, &nMsgLen, &st_IDCardInfo, &st_IDRegion);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求身份证号码验证与信息查询成功,号码:%s"), lpszClientAddr, lpszMsgBuffer);
	return true;
}