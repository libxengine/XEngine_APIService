#include "../XEngine_Hdr.h"

BOOL XEngine_HTTPTask_IDCard(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nType)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	TCHAR tszMsgBuffer[4096];
	TCHAR tszPktBuffer[4096];
	XENGINE_IDCARDINFO st_IDCardInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(&st_IDCardInfo, '\0', sizeof(XENGINE_IDCARDINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭

	if (!ModuleProtocol_Parse_IDCard(lpszMsgBuffer, &st_IDCardInfo))
	{
		st_HDRParam.nHttpCode = 406;
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求的身份证编号不正确:%s"), lpszClientAddr, lpszMsgBuffer);
		return FALSE;
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