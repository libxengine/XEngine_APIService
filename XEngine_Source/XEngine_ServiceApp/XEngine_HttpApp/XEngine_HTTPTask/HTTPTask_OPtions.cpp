#include "../XEngine_Hdr.h"


BOOL XEngine_HTTPTask_OPTions(LPCTSTR lpszClientAddr)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	TCHAR tszMsgBuffer[4096];
	TCHAR tszPktBuffer[4096];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	//解析能力配置
	XENGINE_OPTIONLIST st_OPtionList;
	LPCTSTR lpszOPFile = _T("./XEngine_Config/XEngine_OPtionConfig.json");
	FILE* pSt_File = _tfopen(lpszOPFile, _T("rb"));
	if (NULL == pSt_File)
	{
		return FALSE;
	}
	nPktLen = fread(tszPktBuffer, 1, nPktLen, pSt_File);
	fclose(pSt_File);
	//打包发送
	RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送银行卡信息获取请求给服务器"), lpszClientAddr);
	return TRUE;
}