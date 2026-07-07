#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_WeatherInfo(LPCXSTR lpszClientAddr, LPCXSTR lpszAddrCode)
{
	int nPktLen = 4096;
	int nBLen = 0;
	XCHAR* ptszBodyBuffer = NULL;
	XCHAR tszPktBuffer[4096] = {};
	XCHAR tszUrlBuffer[XPATH_MAX] = {};
	XENGINE_WEATHERINFO st_WeatherInfo = {};

	_xstprintf(tszUrlBuffer, st_ServiceConfig.st_XApi.tszWeatherUrl, lpszAddrCode);
	APIClient_Http_Request(_X("GET"), tszUrlBuffer, NULL, NULL, &ptszBodyBuffer, &nBLen);

	XCHAR tszGBKStr[1024] = {};
#ifdef _MSC_BUILD
	BaseLib_Charset_UTFToAnsi(ptszBodyBuffer, tszGBKStr, &nBLen);
#else
	_tcsxcpy(tszGBKStr, ptszBodyBuffer);
#endif
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
	//解析JSON信息
	if (!ModuleProtocol_Parse_Weather(tszGBKStr, nBLen, &st_WeatherInfo))
	{
		ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, ERROR_XENGINE_PROTOCL_HTTP_NOTFOUND, _X("get weather failed.maybe id is incorrect"));
		XEngine_Network_Send(lpszClientAddr, tszPktBuffer, nPktLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的实时天气信息错误,可能ID:%s,不正确"), lpszClientAddr, lpszAddrCode);
		return false;
	}
	//打包发送
	ModuleProtocol_Packet_Weather(tszPktBuffer, &nPktLen, &st_WeatherInfo);
#ifdef _MSC_BUILD
	XCHAR tszUTFStr[1024] = {};
	BaseLib_Charset_AnsiToUTF(tszPktBuffer, tszUTFStr, &nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszUTFStr, nPktLen);
#else
	XEngine_Network_Send(lpszClientAddr, tszPktBuffer, nPktLen);
#endif
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的实时天气信息成功,查询ID:%s"), lpszClientAddr, lpszAddrCode);
	return true;
}