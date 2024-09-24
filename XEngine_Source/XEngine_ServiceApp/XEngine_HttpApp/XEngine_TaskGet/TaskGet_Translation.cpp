#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_Translation(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, LPCXSTR lpszSrcStr, LPCXSTR lpszDstStr)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	int nBLen = 0;
	XCHAR* ptszBodyBuffer;
	XCHAR tszMsgBuffer[4096];
	XCHAR tszPktBuffer[4096];
	XCHAR tszTypeBuffer[64];
	XENGINE_LANGUAGEINFO st_LanguageInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(tszTypeBuffer, '\0', sizeof(tszTypeBuffer));
	memset(&st_LanguageInfo, '\0', sizeof(XENGINE_LANGUAGEINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	XCHAR tszSignStr[MAX_PATH] = {};
	XCHAR tszMD5Codec[MAX_PATH] = {};
	XCHAR tszMD5Str[MAX_PATH] = {};
	XCHAR tszURLStr[4096] = {};
	XCHAR tszUTFBuffer[2048] = {};

#ifdef _MSC_BUILD
	int nGLen = _tcsxlen(lpszMsgBuffer);
	BaseLib_OperatorCharset_AnsiToUTF(lpszMsgBuffer, tszUTFBuffer, &nGLen);
#else
	_xstrcpy(tszUTFBuffer, lpszMsgBuffer, sizeof(tszUTFBuffer));
#endif

	int nRandomNumber = rand();
	int nLen = _xstprintf(tszSignStr, _X("%s%s%d%s"), st_ServiceConfig.st_XApi.st_TranslationInfo.tszAPPID, tszUTFBuffer, nRandomNumber, st_ServiceConfig.st_XApi.st_TranslationInfo.tszAPPKey);

	OPenSsl_Api_Digest(tszSignStr, (XBYTE*)tszMD5Codec, &nLen);
	for (int i = 0; i < 16; i++)
	{
		XCHAR tszTmpStr[4] = {};
		_xstprintf(tszTmpStr, "%2.2x", (XBYTE)tszMD5Codec[i]);
		_tcsxcat(tszMD5Str, tszTmpStr);
	}
	XCHAR tszLanguageSrc[64] = {};
	XCHAR tszLanauageDst[64] = {};

	ModuleHelp_Translation_Convert((ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE)_ttxoi(lpszSrcStr), tszLanguageSrc);
	ModuleHelp_Translation_Convert((ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE)_ttxoi(lpszDstStr), tszLanauageDst);

	_xstprintf(tszURLStr, _X("%s?appid=%s&q=%s&from=%s&to=%s&salt=%d&sign=%s"), st_ServiceConfig.st_XApi.tszTranslationUrl, st_ServiceConfig.st_XApi.st_TranslationInfo.tszAPPID, tszUTFBuffer, tszLanguageSrc, tszLanauageDst, nRandomNumber, tszMD5Str);
	APIClient_Http_Request(_X("GET"), tszURLStr, NULL, NULL, &ptszBodyBuffer, &nBLen);

	//解析数据
	if (!ModuleProtocol_Parse_Translation(ptszBodyBuffer, nBLen, &st_LanguageInfo))
	{
		ModuleProtocol_Packet_LanguageQuery(tszPktBuffer, &nPktLen, NULL, 1002, _X("translation failed"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的翻译失败,原始字符串:%s,错误数据:%s"), lpszClientAddr, lpszMsgBuffer, ptszBodyBuffer);
		BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
		return false;
	}
	//打包发送
	ModuleProtocol_Packet_LanguageQuery(tszPktBuffer, &nPktLen, &st_LanguageInfo);
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求语言翻译成功,原始语言:%s,目标语言:%s"), lpszClientAddr, st_LanguageInfo.tszFromStr, st_LanguageInfo.tszToStr);
	return true;
}