#include "../XEngine_Hdr.h"

bool RFCTask_Stun_Parse(LPCXSTR lpszClientAddr, LPCXSTR lpszMSGBuffer, int nMSGLen)
{
	int nRVLen = 0;
	int nSDLen = 0;
	XCHAR tszRVBuffer[4096] = {};
	XCHAR tszSDBuffer[4096] = {};

	int nListCount = 0;
	RFCCOMPONENTS_NATATTR** ppSt_ListAttr;
	RFCCOMPONENTS_NATSTUN st_NatClient = {}; 
	
	if (!NatProtocol_StunNat_Parse(lpszMSGBuffer, nMSGLen, &st_NatClient, &ppSt_ListAttr, &nListCount))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("RFC客户端:%s,发送不正确的STUN协议给服务器,不做处理"), lpszClientAddr);
		return false;
	}
	if (RFCCOMPONENTS_NATCLIENT_PROTOCOL_STUN_CLASS_REQUEST == st_NatClient.wOPClass && RFCCOMPONENTS_NATCLIENT_PROTOCOL_STUN_ATTR_MAPPED_ADDRESS == st_NatClient.wOPMethod)
	{
		int nIPPort = 0;
		int nXLen = 0;
		int nDLen = 0;
		int nNLen = 0;
		int nHLen = 0;
		XCHAR tszIPAddr[128] = {};
		_tcsxcpy(tszIPAddr, lpszClientAddr);
		BaseLib_OperatorIPAddr_SegAddr(tszIPAddr, &nIPPort);

		NatProtocol_StunNat_BuildMapAddress(tszRVBuffer, &nXLen, tszIPAddr, nIPPort, true);
		nRVLen += nXLen;
		NatProtocol_StunNat_BuildMapAddress(tszRVBuffer + nRVLen, &nDLen, tszIPAddr, nIPPort, false);
		nRVLen += nDLen;
#if (XENGINE_VERSION_KERNEL >= 8) && (XENGINE_VERSION_MAIN >= 31)
		int nOLen = 0;
		NatProtocol_StunNat_BuildOriginAddress(tszRVBuffer + nRVLen, &nOLen, st_ServiceConfig.tszIPAddr, st_ServiceConfig.nRFCPort);
		nRVLen += nOLen;
#endif
		NatProtocol_StunNat_BuildAttr(tszRVBuffer + nRVLen, &nNLen, RFCCOMPONENTS_NATCLIENT_PROTOCOL_STUN_ATTR_SERVERNAME, XENGINE_NAME_STR, _tcsxlen(XENGINE_NAME_STR));
		nRVLen += nNLen;
		nSDLen = nRVLen;
		NatProtocol_StunNat_Packet(tszSDBuffer, &nSDLen, (LPCXSTR)st_NatClient.byTokenStr, RFCCOMPONENTS_NATCLIENT_PROTOCOL_STUN_CLASS_RESPONSE, RFCCOMPONENTS_NATCLIENT_PROTOCOL_STUN_ATTR_MAPPED_ADDRESS, tszRVBuffer);
		NetCore_UDPXCore_SendEx(xhRFCSocket, lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("RFC客户端:%s,发送STUN映射请求给服务器,处理成功"), lpszClientAddr);
	}
	else
	{
#if (XENGINE_VERSION_KERNEL >= 8) && (XENGINE_VERSION_MAIN >= 31)
		NatProtocol_StunNat_BuildError(tszRVBuffer, &nRVLen, _X("bad request or not support"));
		nSDLen = nRVLen;
		NatProtocol_StunNat_Packet(tszSDBuffer, &nSDLen, (LPCXSTR)st_NatClient.byTokenStr, RFCCOMPONENTS_NATCLIENT_PROTOCOL_STUN_CLASS_ERROR, 1, tszRVBuffer);
		NetCore_UDPXCore_SendEx(xhRFCSocket, lpszClientAddr, tszSDBuffer, nSDLen);
#endif
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("RFC客户端:%s,发送不正确的STUN协议给服务器,类型类型:%d-%d,不做处理"), lpszClientAddr, st_NatClient.wOPClass, st_NatClient.wOPMethod);
		return false;
	}
	return true;
}