#include "../XEngine_Hdr.h"


BOOL XEngine_HTTPTask_IPInfo(LPCTSTR lpszClientAddr, LPCTSTR lpszIPAddr, int nType)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	TCHAR tszMsgBuffer[4096];
	TCHAR tszPktBuffer[4096];
	XENGINE_IPADDRINFO st_IPAddrInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(&st_IPAddrInfo, '\0', sizeof(XENGINE_IPADDRINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	int nIPVer = 0;
	BaseLib_OperatorIPAddr_GetIPVer(lpszIPAddr, &nIPVer);

	if (AF_INET == nIPVer)
	{
		if (!ModuleDatabase_IPInfo_IPV4Query(&st_IPAddrInfo, lpszIPAddr))
		{
			if (0 == nType)
			{
				ModuleProtocol_Packet_IPQuery(tszPktBuffer, &nPktLen, NULL, 1001, _T("ip is incorrent"));
			}
			else
			{
				ModuleProtocol_Packet_IPQuery2(tszPktBuffer, &nPktLen, NULL, 1001);
			}
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求的IP地址不正确:%s"), lpszClientAddr, lpszIPAddr);
			return FALSE;
		}
	}
	else
	{
		if (!ModuleDatabase_IPInfo_IPV6Query(&st_IPAddrInfo, lpszIPAddr))
		{
			if (0 == nType)
			{
				ModuleProtocol_Packet_IPQuery(tszPktBuffer, &nPktLen, NULL, 1010, _T("not found"));
			}
			else
			{
				ModuleProtocol_Packet_IPQuery2(tszPktBuffer, &nPktLen, NULL, 1010);
			}
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求的IP地址不正确:%s"), lpszClientAddr, lpszIPAddr);
			return FALSE;
		}
	}
	//通过此函数来打包成我们要发送的数据,就是打包成一条标准的HTTP协议
	if (0 == nType)
	{
		ModuleProtocol_Packet_IPQuery(tszPktBuffer, &nPktLen, &st_IPAddrInfo);
	}
	else
	{
		ModuleProtocol_Packet_IPQuery2(tszPktBuffer, &nPktLen, &st_IPAddrInfo);
	}
	RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	//打包完毕后才能发送给客户端
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送IP地址信息获取请求给服务器,查询地址:%s"), lpszClientAddr, lpszIPAddr);
	return TRUE;
}