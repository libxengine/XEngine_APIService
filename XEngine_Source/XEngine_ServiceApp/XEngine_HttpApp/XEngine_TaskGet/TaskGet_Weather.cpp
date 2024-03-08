#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_WeatherInfo(LPCXSTR lpszClientAddr, LPCXSTR lpszAddrCode)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	int nBLen = 0;
	XCHAR* ptszBodyBuffer;
	XCHAR tszMsgBuffer[4096];
	XCHAR tszPktBuffer[4096];
	XCHAR tszUrlBuffer[MAX_PATH];
	XENGINE_WEATHERINFO st_WeatherInfo = {};
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(tszUrlBuffer, '\0', MAX_PATH);

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	_xstprintf(tszUrlBuffer, st_ServiceConfig.st_XApi.tszWeatherUrl, lpszAddrCode);
	APIClient_Http_Request(_X("GET"), tszUrlBuffer, NULL, NULL, &ptszBodyBuffer, &nBLen);

	XCHAR tszGBKStr[1024] = {};
#ifdef _MSC_BUILD
	BaseLib_OperatorCharset_UTFToAnsi(ptszBodyBuffer, tszGBKStr, &nBLen);
#else
	_tcsxcpy(tszGBKStr, ptszBodyBuffer);
#endif
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
	//解析JSON信息
	if (!ModuleProtocol_Parse_Weather(tszGBKStr, nBLen, &st_WeatherInfo))
	{
		ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, 404, _X("address id is incorrect"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的实时天气信息错误,可能ID:%s,不正确"), lpszClientAddr, lpszAddrCode);
		return false;
	}
	//打包发送
	ModuleProtocol_Packet_Weather(tszPktBuffer, &nPktLen, &st_WeatherInfo);
#ifdef _MSC_BUILD
	XCHAR tszUTFStr[1024] = {};
	BaseLib_OperatorCharset_AnsiToUTF(tszPktBuffer, tszUTFStr, &nPktLen);
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszUTFStr, nPktLen);
#else
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
#endif
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的实时天气信息成功,查询ID:%s"), lpszClientAddr, lpszAddrCode);
	return true;
}