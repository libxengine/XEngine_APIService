#include "../XEngine_Hdr.h"

BOOL XEngine_HTTPTask_Translation(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nConvertType)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	int nBLen = 0;
	TCHAR* ptszBodyBuffer;
	TCHAR tszMsgBuffer[4096];
	TCHAR tszPktBuffer[4096];
	TCHAR tszUrlBuffer[MAX_PATH];
	TCHAR tszTypeBuffer[64];
	XENGINE_LANGUAGEINFO st_LanguageInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(tszUrlBuffer, '\0', MAX_PATH);
	memset(tszTypeBuffer, '\0', sizeof(tszTypeBuffer));
	memset(&st_LanguageInfo, '\0', sizeof(XENGINE_LANGUAGEINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	
	st_LanguageInfo.enType = nConvertType;
	//转换类型
	if (!ModuleHelp_Translation_Convert((ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE)nConvertType, tszTypeBuffer))
	{
		ModuleProtocol_Packet_LanguageQuery(tszPktBuffer, &nPktLen, NULL, 1001, _T("type not support"));
		BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求的翻译类型不正确:%d,原始字符串:%s"), lpszClientAddr, nConvertType, lpszMsgBuffer);
		return FALSE;
	}
	_stprintf(tszUrlBuffer, st_ServiceConfig.st_XApi.tszTranslationUrl, tszTypeBuffer, lpszMsgBuffer);
	APIHelp_HttpRequest_Custom(_T("GET"), tszUrlBuffer, NULL, NULL, &ptszBodyBuffer, &nBLen);
	//解析数据
	if (!ModuleProtocol_Parse_Translation(ptszBodyBuffer, nBLen, &st_LanguageInfo))
	{
		ModuleProtocol_Packet_LanguageQuery(tszPktBuffer, &nPktLen, NULL, 1002, _T("translation failed"));
		BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求的翻译失败,类型:%d,原始字符串:%s"), lpszClientAddr, nConvertType, lpszMsgBuffer);
		return FALSE;
	}
	//打包发送
	ModuleProtocol_Packet_LanguageQuery(tszPktBuffer, &nPktLen, &st_LanguageInfo);
	RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求语言翻译成功,原始语言:%s,目标语言:%s"), lpszClientAddr, st_LanguageInfo.tszSourceStr, st_LanguageInfo.tszDestStr);
	return TRUE;
}