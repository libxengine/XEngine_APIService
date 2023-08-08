#include "../XEngine_Hdr.h"


bool HTTPTask_TaskGet_Reload(LPCXSTR lpszClientAddr, LPCXSTR lpszOPCode)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	XCHAR tszMsgBuffer[4096];
	XCHAR tszPktBuffer[4096];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	if (0 == _ttxoi(lpszOPCode))
	{
		XEngine_Configure_Parament(0, NULL, &st_ServiceConfig);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求操作配置重载成功,操作的配置:%s"), lpszClientAddr, lpszOPCode);
	}
	else if (1 == _ttxoi(lpszOPCode))
	{

	}
	return true;
}