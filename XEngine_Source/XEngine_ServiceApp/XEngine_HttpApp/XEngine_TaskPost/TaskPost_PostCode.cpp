#include "../XEngine_Hdr.h"

bool HTTPTask_TastPost_PostCode(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 4096;
	XCHAR tszSDBuffer[4096] = {};
	XENGINE_ZIPINFO st_ZIPInfo = {};

	if (!st_ServiceConfig.st_XSql.bEnable)
	{
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_DISABLE, _X("function is closed"));
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的邮编查询功能已经被服务器关闭,无法继续"), lpszClientAddr);
		return false;
	}

	ModuleProtocol_Parse_ZIPCode(lpszMsgBuffer, nMsgLen, &st_ZIPInfo);
	if (0 == nType)
	{
		ModuleDatabase_ZIPCode_QueryZIPCode(&st_ZIPInfo);
	}
	else
	{
		ModuleDatabase_ZIPCode_QueryName(&st_ZIPInfo);
	}

	ModuleProtocol_Packet_ZIPCode(tszSDBuffer, &nSDLen, &st_ZIPInfo);
	XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求查询邮政编码地址信息查询成功,查询邮编;%d,查询地址:%s"), lpszClientAddr, st_ZIPInfo.nZipCode, st_ZIPInfo.tszCounty);
	return true;
}