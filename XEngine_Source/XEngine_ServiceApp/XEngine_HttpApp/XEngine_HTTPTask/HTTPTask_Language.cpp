#include "../XEngine_Hdr.h"


BOOL XEngine_HTTPTask_Language(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nReplyType, int nConvertType)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	TCHAR tszMsgBuffer[4096];
	TCHAR tszPktBuffer[4096];
	XENGINE_LANGUAGEINFO st_LanguageInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(&st_LanguageInfo, '\0', sizeof(XENGINE_LANGUAGEINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	
	st_LanguageInfo.enLanguageType = (ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE)nConvertType;
	OPenSsl_Codec_UrlDeCodec(lpszMsgBuffer, _tcslen(lpszMsgBuffer), st_LanguageInfo.tszSourceStr);
	if (ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_S2T == nConvertType)
	{
		ModuleHelp_Language_ConvertZh(st_OPenccConfig.tszFiles2t, st_LanguageInfo.tszSourceStr, st_LanguageInfo.tszDestStr);
	}
	else if (ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_T2S == nConvertType)
	{
		ModuleHelp_Language_ConvertZh(st_OPenccConfig.tszFilet2s, st_LanguageInfo.tszSourceStr, st_LanguageInfo.tszDestStr);
	}
	else if (ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_S2TW == nConvertType)
	{
		ModuleHelp_Language_ConvertZh(st_OPenccConfig.tszFiles2tw, st_LanguageInfo.tszSourceStr, st_LanguageInfo.tszDestStr);
	}
	//打包发送
	if (0 == nReplyType)
	{
		ModuleProtocol_Packet_LanguageQuery(tszPktBuffer, &nPktLen, &st_LanguageInfo);
	}
	else
	{
		ModuleProtocol_Packet_LanguageQuery2(tszPktBuffer, &nPktLen, &st_LanguageInfo);
	}
	RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求语言转换成功,原始语言:%s,目标语言%s"), lpszClientAddr, st_LanguageInfo.tszSourceStr, st_LanguageInfo.tszDestStr);
	return TRUE;
}