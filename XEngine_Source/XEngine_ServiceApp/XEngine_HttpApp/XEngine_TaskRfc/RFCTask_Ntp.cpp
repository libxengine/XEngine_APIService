#include "../XEngine_Hdr.h"

bool RFCTask_NTP_Parse(LPCXSTR lpszClientAddr, LPCXSTR lpszMSGBuffer, int nMSGLen)
{
#if (XENGINE_VERSION_KERNEL >= 8) && (XENGINE_VERSION_MAIN >= 31)
	int nSDLen = 0;
	XCHAR tszSDBuffer[4096] = {};
	NTPPROTOCOL_TIMEINFO st_TimeRecv = {};
	NTPPROTOCOL_TIMEINFO st_TimeTras = {};
	NTPProtocol_Packet_TimeConvert(&st_TimeRecv);

	NTPProtocol_Parse_Header(lpszMSGBuffer, nMSGLen, NULL, NULL, NULL, &st_TimeTras);
	NTPProtocol_Packet_REPHeader(tszSDBuffer, &nSDLen, NULL, &st_TimeRecv, &st_TimeTras, st_ServiceConfig.tszIPAddr);
	NetCore_UDPXCore_SendEx(xhRFCSocket, lpszClientAddr, tszSDBuffer, nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("RFC客户端:%s,发送NTP时间同步请求给服务器,处理成功"), lpszClientAddr);
#else
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("RFC客户端:%s,发送NTP时间同步请求给服务器,处理失败,版本不支持"), lpszClientAddr);
#endif

	return true;
}