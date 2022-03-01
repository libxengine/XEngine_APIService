#include "../XEngine_Hdr.h"


BOOL XEngine_HTTPTask_IPInfo(LPCTSTR lpszClientAddr, LPCTSTR lpszIPAddr)
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

	if (!ModuleDatabase_SQlite_IPV4Query(&st_IPAddrInfo, lpszIPAddr))
	{
		st_HDRParam.nHttpCode = 404;
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求的IP地址不正确:%s"), lpszClientAddr, lpszIPAddr);
		return FALSE;
	}
	//通过此函数来打包成我们要发送的数据,就是打包成一条标准的HTTP协议
	ModuleProtocol_Packet_IPQuery(tszPktBuffer, &nPktLen, &st_IPAddrInfo);
	RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	//打包完毕后才能发送给客户端
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送GET请求给服务器"), lpszClientAddr);
	return TRUE;
}