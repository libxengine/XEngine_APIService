#include "../XEngine_Hdr.h"

bool HTTPTask_TaskPost_QRCode(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭
#if (0 == _XENGINE_BUILD_SWITCH_QRDECODEC)
	int nMLen = 0;
	XCHAR tszMSGBuffer[MAX_PATH] = {};

	st_HDRParam.nHttpCode = 501;
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMSGBuffer, &nMLen, &st_HDRParam);
	XEngine_Network_Send(lpszClientAddr, tszMSGBuffer, nMLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求二维码操作失败,服务器没有启用此功能"), lpszClientAddr);
#else
	int nSDLen = 0;
	int nRVLen = 0;
	XCHAR* ptszSDBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_MAX);
	XCHAR* ptszRVBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_MAX);
	XENGINE_QRCODE st_QRCode;
	
	memset(ptszSDBuffer, '\0', XENGINE_MEMORY_SIZE_MAX);
	memset(ptszRVBuffer, '\0', XENGINE_MEMORY_SIZE_MAX);
	memset(&st_QRCode, '\0', sizeof(XENGINE_QRCODE));
	//0创建,1解析
	if (0 == nType)
	{
		ModuleProtocol_Parse_QRCode(lpszMsgBuffer, nMsgLen, &st_QRCode);
		_tcsxcpy(st_HDRParam.tszMimeType, st_QRCode.tszFmtBuffer + 1);

		if (ModuleHelp_QRCode_QREncodecMemory(st_QRCode.tszMsgBuffer, ptszRVBuffer, &nRVLen, st_QRCode.tszFmtBuffer))
		{
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam, ptszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求创建二维码成功,创建的二维码数据:%s"), lpszClientAddr, st_QRCode.tszMsgBuffer);
		}
		else
		{
			st_HDRParam.nHttpCode = 501;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求创建二维码失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
		}
	}
	else
	{
		if (ModuleHelp_QRCode_QRDecodecMemory(lpszMsgBuffer, nMsgLen, ptszRVBuffer, st_QRCodeConfig.tszProtoDetect, st_QRCodeConfig.tszModelDetect, st_QRCodeConfig.tszProtoSr, st_QRCodeConfig.tszModelSr))
		{
			nRVLen = _tcsxlen(ptszRVBuffer);
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam, ptszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求二维码解析成功,解析的数据:%s"), lpszClientAddr, ptszRVBuffer);
		}
		else
		{
			st_HDRParam.nHttpCode = 501;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求二维码解析失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
		}
	}
	free(ptszRVBuffer);
	free(ptszSDBuffer);
	ptszRVBuffer = NULL;
	ptszSDBuffer = NULL;
#endif
	return true;
}