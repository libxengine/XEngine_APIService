#include "../XEngine_Hdr.h"

BOOL XEngine_HTTPTask_LogInfo(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	int nRVLen = 0;
	TCHAR tszSDBuffer[4096];
	TCHAR tszRVBuffer[4096];
	XENGINE_XLOGINFO st_XLogInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));
	memset(tszRVBuffer, '\0', sizeof(tszRVBuffer));
	memset(&st_XLogInfo, '\0', sizeof(XENGINE_XLOGINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	//解析JSON信息
	ModuleProtocol_Parse_XLog(lpszMsgBuffer, nMsgLen, &st_XLogInfo);
	//写入数据库名称
	ModuleDatabase_XLog_Insert(&st_XLogInfo);
	//打包发送
	ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen);
	RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
	XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送银行卡信息获取请求给服务器"), lpszClientAddr);
	return TRUE;
}