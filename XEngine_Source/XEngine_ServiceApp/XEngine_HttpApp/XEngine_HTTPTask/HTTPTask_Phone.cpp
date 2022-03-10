#include "../XEngine_Hdr.h"


BOOL XEngine_HTTPTask_PhoneInfo(LPCTSTR lpszClientAddr, LPCTSTR lpszPhoneNumber, int nType)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	TCHAR tszMsgBuffer[4096];
	TCHAR tszPktBuffer[4096];
	XENGINE_PHONEINFO st_PhoneInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(tszPktBuffer, '\0', sizeof(tszPktBuffer));
	memset(&st_PhoneInfo, '\0', sizeof(XENGINE_PHONEINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭

	st_PhoneInfo.nPhoneNumber = _ttoi64(lpszPhoneNumber);
	ModuleDatabase_Phone_Query(lpszPhoneNumber, &st_PhoneInfo);
	//打包发送
	if (0 == nType)
	{
		ModuleProtocol_Packet_PhoneQuery(tszPktBuffer, &nPktLen, &st_PhoneInfo);
	}
	else
	{
		ModuleProtocol_Packet_PhoneQuery2(tszPktBuffer, &nPktLen, &st_PhoneInfo);
	}
	RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
	XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送电话信息获取请求给服务器,查询号码:%s"), lpszClientAddr, lpszPhoneNumber);
	return TRUE;
}