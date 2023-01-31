#include "../XEngine_Hdr.h"

BOOL XEngine_HTTPTask_QRCode(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	int nRVLen = 0;
	TCHAR tszSDBuffer[4096];
	TCHAR tszRVBuffer[4096];
	XENGINE_QRCODE st_QRCode;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));
	memset(tszRVBuffer, '\0', sizeof(tszRVBuffer));
	memset(&st_QRCode, '\0', sizeof(XENGINE_QRCODE));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	ModuleProtocol_Parse_QRCode(lpszMsgBuffer, nMsgLen, &st_QRCode);
	//0创建,1解析
	if (0 == nType)
	{
		_tcscpy(st_HDRParam.tszMimeType, st_QRCode.tszFmtBuffer + 1);
		ModuleHelp_QRCode_QREncodecMemory(st_QRCode.tszMsgBuffer, tszRVBuffer, &nRVLen, st_QRCode.tszFmtBuffer);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求创建二维码成功,创建的二维码数据:%s,"), lpszClientAddr, st_QRCode.tszMsgBuffer);
	}
	else
	{
		ModuleHelp_QRCode_QRDecodecMemory(lpszMsgBuffer, nMsgLen, tszRVBuffer, st_QRCodeConfig.tszProtoDetect, st_QRCodeConfig.tszModelDetect, st_QRCodeConfig.tszProtoSr, st_QRCodeConfig.tszModelSr);
		nRVLen = _tcslen(tszRVBuffer);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求二维码解析成功,解析的数据:%s"), lpszClientAddr, tszRVBuffer);
	}
	return TRUE;
}