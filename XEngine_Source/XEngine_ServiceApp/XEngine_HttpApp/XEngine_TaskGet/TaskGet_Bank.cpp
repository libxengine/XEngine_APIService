#include "../XEngine_Hdr.h"


bool HTTPTask_TaskGet_BankInfo(LPCXSTR lpszClientAddr, LPCXSTR lpszBankNumber)
{
	int nMsgLen = 4096;
	int nBLen = 0;
	XCHAR* ptszBodyBuffer = NULL;
	XCHAR tszMsgBuffer[4096] = {};
	XCHAR tszUrlBuffer[XPATH_MAX] = {};
	XENGINE_BANKINFO st_BankInfo = {};

	if (!st_ServiceConfig.st_XSql.bEnable)
	{
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_DISABLE, _X("function is closed"));
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的银行卡查询功能已经被服务器关闭,无法继续"), lpszClientAddr);
		return false;
	}
	_tcsxcpy(st_BankInfo.tszBankNumber, lpszBankNumber);
	_xstprintf(tszUrlBuffer, st_ServiceConfig.st_XApi.tszBankUrl, lpszBankNumber);
	APIClient_Http_Request(_X("GET"), tszUrlBuffer, NULL, NULL, &ptszBodyBuffer, &nBLen);
	//解析JSON信息
	if (!ModuleProtocol_Parse_Bank(ptszBodyBuffer, nBLen, &st_BankInfo))
	{
		BaseLib_Memory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_NOTFOUND, _X("bank number is incorrent"));
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的银行卡号码错误:%s"), lpszClientAddr, lpszBankNumber);
		return false;
	}
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
	//查询对应名称
	if (!ModuleDatabase_Bank_Query(&st_BankInfo))
	{
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_NOTFOUND, _X("bank number is incorrent"));
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的银行卡信息没有找到:%s"), lpszClientAddr, lpszBankNumber);
		return false;
	}
	//打包发送
	ModuleProtocol_Packet_BankQuery(tszMsgBuffer, &nMsgLen, &st_BankInfo);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,发送银行卡信息获取请求给服务器,查询号码:%s"), lpszClientAddr, lpszBankNumber);
	return true;
}