#include "../XEngine_Hdr.h"


BOOL XEngine_HTTPTask_BankInfo(LPCTSTR lpszClientAddr, LPCTSTR lpszBankNumber, int nType)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	int nBLen = 0;
	TCHAR* ptszBodyBuffer;
	TCHAR tszMsgBuffer[4096];
	TCHAR tszPktBuffer[4096];
	TCHAR tszUrlBuffer[MAX_PATH];
	XENGINE_BANKINFO st_BankInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(tszUrlBuffer, '\0', MAX_PATH);
	memset(&st_BankInfo, '\0', sizeof(XENGINE_BANKINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭

	_tcscpy(st_BankInfo.tszBankNumber, lpszBankNumber);
	_stprintf(tszUrlBuffer, st_ServiceConfig.st_XApi.tszBankUrl, lpszBankNumber);
	APIHelp_HttpRequest_Get(tszUrlBuffer, &ptszBodyBuffer, &nBLen);
	//解析JSON信息
	if (!ModuleProtocol_Parse_Bank(ptszBodyBuffer, nBLen, &st_BankInfo))
	{
		if (0 == nType)
		{
			ModuleProtocol_Packet_BankQuery(tszPktBuffer, &nPktLen, NULL, 1001, _T("banknumber is corrent"));
		}
		else
		{
			ModuleProtocol_Packet_BankQuery2(tszPktBuffer, &nPktLen, NULL, 1001);
		}
		BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求的银行卡号码错误:%s"), lpszClientAddr, lpszBankNumber);
		return FALSE;
	}
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
	//查询对应名称
	if (!ModuleDatabase_Bank_Query(&st_BankInfo))
	{
		if (0 == nType)
		{
			ModuleProtocol_Packet_BankQuery(tszPktBuffer, &nPktLen, NULL, 1010, _T("not found"));
		}
		else
		{
			ModuleProtocol_Packet_BankQuery2(tszPktBuffer, &nPktLen, NULL, 1010);
		}
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求的银行卡信息没有找到:%s"), lpszClientAddr, lpszBankNumber);
		return FALSE;
	}
	//打包发送
	if (0 == nType)
	{
		ModuleProtocol_Packet_BankQuery(tszPktBuffer, &nPktLen, &st_BankInfo);
	}
	else
	{
		ModuleProtocol_Packet_BankQuery2(tszPktBuffer, &nPktLen, &st_BankInfo);
	}
	RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送银行卡信息获取请求给服务器,查询号码:%s"), lpszClientAddr, lpszBankNumber);
	return TRUE;
}