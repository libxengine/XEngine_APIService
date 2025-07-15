#include "../XEngine_Hdr.h"

bool RFCTask_DNS_Parse(LPCXSTR lpszClientAddr, LPCXSTR lpszMSGBuffer, int nMSGLen)
{
	int nSDLen = 0;
	int nRequestID = 0;
	XCHAR tszSDBuffer[4096] = {};
	XENGINE_DNSPROTOCOL st_DNSRequest = {};
	
	if (!DNSProtocol_Parse_Header(lpszMSGBuffer, nMSGLen, &nRequestID, &st_DNSRequest))
	{
		DNSProtocol_Packet_Error(tszSDBuffer, &nSDLen, nRequestID, &st_DNSRequest, XENGINE_DNSPROTOCOL_QUERY_QUESTION_STATUS_FORMAT);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("DNS客户端:%s,发送的DNS协议不正确"), lpszClientAddr);
		return false;
	}

	if (XENGINE_DNSPROTOCOL_QUERY_QUESTION_TYPE_A == st_DNSRequest.st_QueryInfo.nNameType)
	{
		int nListCount = 0;
		XENGINE_DNSADDRINFO** ppSt_DNSAddr;
		if (ModuleHelp_DNSAddr_FindA(st_DNSRequest.tszNameStr, &ppSt_DNSAddr, &nListCount))
		{
			//找到A记录
			XENGINE_DNSPROTOCOL** ppSt_DNSAnswer;
			BaseLib_Memory_Malloc((XPPPMEM)&ppSt_DNSAnswer, nListCount, sizeof(XENGINE_DNSPROTOCOL));
			for (int i = 0; i < nListCount; i++)
			{
				ppSt_DNSAnswer[i]->nTTL = ppSt_DNSAddr[i]->nTTL;
				ppSt_DNSAnswer[i]->st_QueryInfo.nNameType = ppSt_DNSAddr[i]->nType;
				ppSt_DNSAnswer[i]->st_QueryInfo.nNameClass = XENGINE_DNSPROTOCOL_QUERY_QUESTION_CLASS_IN;
				_tcsxcpy(ppSt_DNSAnswer[i]->tszNameStr, ppSt_DNSAddr[i]->tszDNSName);
				_tcsxcpy(ppSt_DNSAnswer[i]->tszAddrStr, ppSt_DNSAddr[i]->tszDNSAddr);
			}
			DNSProtocol_Packet_REPHeader(tszSDBuffer, &nSDLen, nRequestID, &st_DNSRequest, &ppSt_DNSAnswer, nListCount);
			BaseLib_Memory_Free((XPPPMEM)&ppSt_DNSAnswer, nListCount);
		}
	}
	else if (XENGINE_DNSPROTOCOL_QUERY_QUESTION_TYPE_PTR == st_DNSRequest.st_QueryInfo.nNameType)
	{
		int nIPVer = 0;
		int nListCount = 1;
		XCHAR tszIPStr[256] = {};
		XENGINE_DNSADDRINFO st_DNSAddr = {};
		XENGINE_DNSPROTOCOL** ppSt_DNSAnswer;

		DNSProtocol_Help_PTRStr(st_DNSRequest.tszNameStr, tszIPStr, &nIPVer);
		BaseLib_Memory_Malloc((XPPPMEM)&ppSt_DNSAnswer, nListCount, sizeof(XENGINE_DNSPROTOCOL));

		if (ModuleHelp_DNSAddr_FindPtr(tszIPStr, &st_DNSAddr))
		{
			ppSt_DNSAnswer[0]->nTTL = st_DNSAddr.nTTL;
			ppSt_DNSAnswer[0]->st_QueryInfo.nNameType = st_DNSAddr.nType;
			ppSt_DNSAnswer[0]->st_QueryInfo.nNameClass = XENGINE_DNSPROTOCOL_QUERY_QUESTION_CLASS_IN;
			_tcsxcpy(ppSt_DNSAnswer[0]->tszNameStr, st_DNSAddr.tszDNSAddr);
			_tcsxcpy(ppSt_DNSAnswer[0]->tszAddrStr, st_DNSAddr.tszDNSName);
		}
		DNSProtocol_Packet_REPHeader(tszSDBuffer, &nSDLen, nRequestID, &st_DNSRequest, &ppSt_DNSAnswer, nListCount);
		BaseLib_Memory_Free((XPPPMEM)&ppSt_DNSAnswer, nListCount);
	}
	
	NetCore_UDPXCore_SendEx(xhDNSSocket, lpszClientAddr, tszSDBuffer, nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("DNS客户端:%s,发送DNS协议给服务器,处理成功"), lpszClientAddr);

	return true;
}