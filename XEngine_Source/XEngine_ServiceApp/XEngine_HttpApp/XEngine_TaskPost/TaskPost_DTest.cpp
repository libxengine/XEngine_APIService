#include "../XEngine_Hdr.h"

XBOOL HTTPTask_TastPost_DTest(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	XCHAR tszSDBuffer[4096];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	//0发什么返回什么,1 仅仅返回确认
	if (0 == nType)
	{
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, lpszMsgBuffer, nMsgLen);
	}
	else
	{
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam);
	}
	XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求数据用例测试成功,请求的大小:%d,请求的类型:%d"), lpszClientAddr, nMsgLen, nType);
	return TRUE;
}