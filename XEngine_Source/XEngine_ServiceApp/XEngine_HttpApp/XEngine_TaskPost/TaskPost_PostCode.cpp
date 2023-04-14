#include "../XEngine_Hdr.h"

XBOOL HTTPTask_TastPost_PostCode(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 4096;
	int nRVLen = 4096;
	XCHAR tszSDBuffer[4096];
	XCHAR tszRVBuffer[4096];
	XENGINE_ZIPINFO st_ZIPInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));
	memset(tszRVBuffer, '\0', sizeof(tszRVBuffer));
	memset(&st_ZIPInfo, '\0', sizeof(XENGINE_ZIPINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭

	ModuleProtocol_Parse_ZIPCode(lpszMsgBuffer, nMsgLen, &st_ZIPInfo);
	if (0 == nType)
	{
		ModuleDatabase_ZIPCode_QueryZIPCode(&st_ZIPInfo);
	}
	else
	{
		ModuleDatabase_ZIPCode_QueryName(&st_ZIPInfo);
	}

	ModuleProtocol_Packet_ZIPCode(tszRVBuffer, &nRVLen, &st_ZIPInfo);
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
	XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求查询邮政编码地址信息查询成功,查询邮编;%d,查询地址:%s"), lpszClientAddr, st_ZIPInfo.nZipCode, st_ZIPInfo.tszCounty);
	return TRUE;
}