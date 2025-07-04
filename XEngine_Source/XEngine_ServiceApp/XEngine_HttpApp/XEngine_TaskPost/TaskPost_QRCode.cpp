#include "../XEngine_Hdr.h"

bool HTTPTask_TaskPost_QRCode(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭
#if (0 == _XENGINE_BUILD_SWITCH_QRDECODEC)
	int nMLen = 0;
	XCHAR tszMSGBuffer[XPATH_MAX] = {};

	st_HDRParam.nHttpCode = 501;
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMSGBuffer, &nMLen, &st_HDRParam);
	XEngine_Network_Send(lpszClientAddr, tszMSGBuffer, nMLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求二维码操作失败,服务器没有启用此功能"), lpszClientAddr);
#else
	int nSDLen = 0;
	int nRVLen = 0;
	XENGINE_QRCODE st_QRCode = {};
	CXEngine_MemoryPoolEx m_MemorySend(XENGINE_MEMORY_SIZE_MAX);
	CXEngine_MemoryPoolEx m_MemoryRecv(XENGINE_MEMORY_SIZE_MAX);

	//0创建,1解析
	if (0 == nType)
	{
		ModuleProtocol_Parse_QRCode(lpszMsgBuffer, nMsgLen, &st_QRCode);
		_tcsxcpy(st_HDRParam.tszMimeType, st_QRCode.tszFmtBuffer + 1);

		if (ModuleHelp_QRCode_QREncodecMemory(st_QRCode.tszMsgBuffer, m_MemoryRecv.get(), &nRVLen, st_QRCode.tszFmtBuffer))
		{
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam, m_MemoryRecv.get(), nRVLen);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求创建二维码成功,创建的二维码数据:%s"), lpszClientAddr, st_QRCode.tszMsgBuffer);
		}
		else
		{
			st_HDRParam.nHttpCode = 501;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求创建二维码失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
		}
	}
	else
	{
		if (ModuleHelp_QRCode_QRDecodecMemory(lpszMsgBuffer, nMsgLen, m_MemoryRecv.get(), st_ServiceConfig.st_XConfig.st_ConfigQRCodec.tszProtoDetect, st_ServiceConfig.st_XConfig.st_ConfigQRCodec.tszModelDetect, st_ServiceConfig.st_XConfig.st_ConfigQRCodec.tszProtoSr, st_ServiceConfig.st_XConfig.st_ConfigQRCodec.tszModelSr))
		{
			nRVLen = _tcsxlen(m_MemoryRecv.get());
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam, m_MemoryRecv.get(), nRVLen);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求二维码解析成功,解析的数据:%s"), lpszClientAddr, m_MemoryRecv.get());
		}
		else
		{
			st_HDRParam.nHttpCode = 501;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求二维码解析失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
		}
	}
#endif
	return true;
}