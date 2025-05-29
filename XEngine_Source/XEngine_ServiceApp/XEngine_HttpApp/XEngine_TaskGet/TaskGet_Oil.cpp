#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_Oil(LPCXSTR lpszClientAddr, LPCXSTR lpszCityStr)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	int nBLen = 0;
	XCHAR* ptszBodyBuffer;
	XCHAR tszMsgBuffer[4096];
	XCHAR tszPktBuffer[4096];
	XCHAR tszUrlBuffer[XPATH_MAX] = {};

	XENGINE_OILINFO st_OilInfo = {};
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	XCHAR tszURLEncoder[XPATH_MAX] = {};
	_xstprintf(tszUrlBuffer, st_ServiceConfig.st_XApi.tszOilUrl, lpszCityStr);

#ifdef _MSC_BUILD
	XCHAR tszUTFEncoder[XPATH_MAX] = {};
	BaseLib_Charset_AnsiToUTF(tszUrlBuffer, tszUTFEncoder);
	Cryption_Codec_UrlEnCodec(tszUTFEncoder, _tcsxlen(tszUTFEncoder), tszURLEncoder);
#else
	Cryption_Codec_UrlEnCodec(tszUrlBuffer, _tcsxlen(tszUrlBuffer), tszURLEncoder);
#endif
	
	APIClient_Http_Request(_X("GET"), tszURLEncoder, NULL, NULL, &ptszBodyBuffer, &nBLen);
	XCHAR tszGBKStr[1024] = {};
#ifdef _MSC_BUILD
	BaseLib_Charset_UTFToAnsi(ptszBodyBuffer, tszGBKStr, &nBLen);
#else
	_tcsxcpy(tszGBKStr, ptszBodyBuffer);
#endif
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
	//解析JSON信息
	if (!ModuleProtocol_Parse_Oil(tszGBKStr, nBLen, &st_OilInfo))
	{
		ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, 404, _X("get oil failed.maybe address is incorrect"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的油价查询错误,可能地址:%s,不正确"), lpszClientAddr, lpszCityStr);
		return false;
	}
	ModuleProtocol_Packet_OilInfo(tszPktBuffer, &nPktLen, &st_OilInfo);
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求油价查询成功,城市名:%s"), lpszClientAddr, lpszCityStr);
	return true;
}