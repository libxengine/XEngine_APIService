#include "../XEngine_Hdr.h"


XBOOL HTTPTask_TaskGet_OPTions(LPCXSTR lpszClientAddr)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	XCHAR tszMsgBuffer[4096];
	XCHAR tszPktBuffer[4096];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = XTRUE; //收到回复后就关闭
	//解析能力配置
	XENGINE_OPTIONLIST st_OPtionList;
	LPCXSTR lpszOPFile = _T("./XEngine_Config/XEngine_OPtionConfig.json");
	FILE* pSt_File = _tfopen(lpszOPFile, _T("rb"));
	if (NULL == pSt_File)
	{
		st_HDRParam.nHttpCode = 404;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,查询服务器能力失败,没有找到配置文件"), lpszClientAddr);
		return XFALSE;
	}
	nPktLen = fread(tszPktBuffer, 1, nPktLen, pSt_File);
	fclose(pSt_File);
	//打包发送
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,查询服务器能力成功"), lpszClientAddr);
	return XTRUE;
}