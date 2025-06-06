#include "../XEngine_Hdr.h"


bool HTTPTask_TaskGet_BankInfo(LPCXSTR lpszClientAddr, LPCXSTR lpszBankNumber)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	int nBLen = 0;
	XCHAR* ptszBodyBuffer;
	XCHAR tszMsgBuffer[4096];
	XCHAR tszPktBuffer[4096];
	XCHAR tszUrlBuffer[XPATH_MAX];
	XENGINE_BANKINFO st_BankInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(tszUrlBuffer, '\0', XPATH_MAX);
	memset(&st_BankInfo, '\0', sizeof(XENGINE_BANKINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	if (!st_ServiceConfig.st_XSql.bEnable)
	{
		ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, 501, _X("function is closed"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
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
		ModuleProtocol_Packet_BankQuery(tszPktBuffer, &nPktLen, NULL, 1001, _X("banknumber is corrent"));
		BaseLib_Memory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的银行卡号码错误:%s"), lpszClientAddr, lpszBankNumber);
		return false;
	}
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
	//查询对应名称
	if (!ModuleDatabase_Bank_Query(&st_BankInfo))
	{
		ModuleProtocol_Packet_BankQuery(tszPktBuffer, &nPktLen, NULL, 1010, _X("not found"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的银行卡信息没有找到:%s"), lpszClientAddr, lpszBankNumber);
		return false;
	}
	//打包发送
	ModuleProtocol_Packet_BankQuery(tszPktBuffer, &nPktLen, &st_BankInfo);
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,发送银行卡信息获取请求给服务器,查询号码:%s"), lpszClientAddr, lpszBankNumber);
	return true;
}