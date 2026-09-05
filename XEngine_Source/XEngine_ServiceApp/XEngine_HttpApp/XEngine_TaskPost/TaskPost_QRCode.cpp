#include "../XEngine_Hdr.h"

bool HTTPTask_TaskPost_QRCode(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
#if (0 == _XENGINE_BUILD_SWITCH_QRDECODEC)
	int nMLen = 0;
	XCHAR tszMSGBuffer[XPATH_MAX] = {};

	ModuleProtocol_Packet_Common(tszMSGBuffer, &nMLen, ERROR_XENGINE_PROTOCL_HTTP_DISABLE, _X("function is closed"));
	XEngine_Network_Send(lpszClientAddr, tszMSGBuffer, nMLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求二维码操作失败,服务器没有启用此功能"), lpszClientAddr);
#else

	int nRVLen = 0;
	XENGINE_QRCODE st_QRCode = {};
	CXEngine_MemoryPoolEx m_MemoryRecv(XENGINE_MEMORY_SIZE_MAX);

	//0创建,1解析
	if (0 == nType)
	{
		ModuleProtocol_Parse_QRCode(lpszMsgBuffer, nMsgLen, &st_QRCode);
		//_tcsxcpy(st_HDRParam.tszMimeType, st_QRCode.tszFmtBuffer + 1);

		if (ModuleHelp_QRCode_QREncodecMemory(st_QRCode.tszMsgBuffer, m_MemoryRecv.get(), &nRVLen, st_QRCode.tszFmtBuffer))
		{
			XEngine_Network_Send(lpszClientAddr, m_MemoryRecv.get(), nRVLen, st_QRCode.tszFmtBuffer);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求创建二维码成功,创建的二维码数据:%s"), lpszClientAddr, st_QRCode.tszMsgBuffer);
		}
		else
		{
			ModuleProtocol_Packet_Common(m_MemoryRecv.get(), &nRVLen, ERROR_XENGINE_PROTOCL_HTTP_CREATE, _X("create qrcode failed"));
			XEngine_Network_Send(lpszClientAddr, m_MemoryRecv.get(), nRVLen, st_QRCode.tszFmtBuffer);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求创建二维码失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
		}
	}
	else
	{
		if (ModuleHelp_QRCode_QRDecodecMemory(lpszMsgBuffer, nMsgLen, m_MemoryRecv.get(), st_ServiceConfig.st_XConfig.st_ConfigQRCodec.tszProtoDetect, st_ServiceConfig.st_XConfig.st_ConfigQRCodec.tszModelDetect, st_ServiceConfig.st_XConfig.st_ConfigQRCodec.tszProtoSr, st_ServiceConfig.st_XConfig.st_ConfigQRCodec.tszModelSr))
		{
			nRVLen = _tcsxlen(m_MemoryRecv.get());
			XEngine_Network_Send(lpszClientAddr, m_MemoryRecv.get(), nRVLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求二维码解析成功,解析的数据:%s"), lpszClientAddr, m_MemoryRecv.get());
		}
		else
		{
			ModuleProtocol_Packet_Common(m_MemoryRecv.get(), &nRVLen, ERROR_XENGINE_PROTOCL_HTTP_PARSE, _X("parse qrcode failed"));
			XEngine_Network_Send(lpszClientAddr, m_MemoryRecv.get(), nRVLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求二维码解析失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
		}
	}
#endif
	return true;
}