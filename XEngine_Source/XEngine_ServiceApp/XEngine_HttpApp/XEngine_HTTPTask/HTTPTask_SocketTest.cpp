#include "../XEngine_Hdr.h"

void CALLBACK XEngine_HTTPTask_CBSocketTest(XNETHANDLE xhToken, LPCSTR lpszAddr, int nPort, __int64x nNumber, __int64x nFailed, __int64x nSuccess, int nStatus, LPVOID lParam)
{
	XENGINE_SOCKETTEST* pSt_SocketTest = (XENGINE_SOCKETTEST*)lParam;
	int nMsgLen = 0;
	TCHAR tszMsgBuffer[4096];
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));

	if (0 == pSt_SocketTest->nType)
	{
		//每次都报告
		ModuleProtocol_Packet_TestReport(tszMsgBuffer, &nMsgLen, xhToken, lpszAddr, nPort, nNumber, nFailed, nSuccess, nStatus);
		if (_tcslen(pSt_SocketTest->tszAPIUrl) > 0)
		{
			APIClient_Http_Request("POST", pSt_SocketTest->tszAPIUrl, tszMsgBuffer);
		}
	}
	else if ((1 == pSt_SocketTest->nType) && (0 == nStatus))
	{
		//成功报告
		ModuleProtocol_Packet_TestReport(tszMsgBuffer, &nMsgLen, xhToken, lpszAddr, nPort, nNumber, nFailed, nSuccess, nStatus);
		if (_tcslen(pSt_SocketTest->tszAPIUrl) > 0)
		{
			APIClient_Http_Request("POST", pSt_SocketTest->tszAPIUrl, tszMsgBuffer);
		}
	}
	else if ((2 == pSt_SocketTest->nType) && (1 == nStatus))
	{
		//失败报告
		ModuleProtocol_Packet_TestReport(tszMsgBuffer, &nMsgLen, xhToken, lpszAddr, nPort, nNumber, nFailed, nSuccess, nStatus);
		if (_tcslen(pSt_SocketTest->tszAPIUrl) > 0)
		{
			APIClient_Http_Request("POST", pSt_SocketTest->tszAPIUrl, tszMsgBuffer);
		}
	}
	else
	{
		if (2 == nStatus)
		{
			//结束报告
			ModuleProtocol_Packet_TestReport(tszMsgBuffer, &nMsgLen, xhToken, lpszAddr, nPort, nNumber, nFailed, nSuccess, nStatus);
			if (_tcslen(pSt_SocketTest->tszAPIUrl) > 0)
			{
				APIClient_Http_Request("POST", pSt_SocketTest->tszAPIUrl, tszMsgBuffer);
			}
		}
	}
}
BOOL XEngine_HTTPTask_SocketTest(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	int nRVLen = 0;
	TCHAR tszSDBuffer[4096];
	TCHAR tszRVBuffer[4096];
	XENGINE_SOCKETTEST *pSt_SocketTest = new XENGINE_SOCKETTEST;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));
	memset(tszRVBuffer, '\0', sizeof(tszRVBuffer));
	memset(pSt_SocketTest, '\0', sizeof(XENGINE_SOCKETTEST));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭

	ModuleProtocol_Parse_SocketTest(lpszMsgBuffer, nMsgLen, pSt_SocketTest);
	//0创建,1删除
	if (0 == nType)
	{
		if (pSt_SocketTest->bConn)
		{
			ModuleHelp_SocketTest_StartConnect(&pSt_SocketTest->xhToken, &pSt_SocketTest->st_SocketConn, XEngine_HTTPTask_CBSocketTest, pSt_SocketTest);
		}
		else
		{
			memcpy(&pSt_SocketTest->st_SocketData.st_REConnect, &pSt_SocketTest->st_SocketConn, sizeof(MODULEHELP_SOCKETTEST_RECONNECT));
			ModuleHelp_SocketTest_StartDatas(&pSt_SocketTest->xhToken, &pSt_SocketTest->st_SocketData, XEngine_HTTPTask_CBSocketTest, pSt_SocketTest->bTCP, pSt_SocketTest);
		}
		ModuleProtocol_Packet_TestReply(tszRVBuffer, &nRVLen, pSt_SocketTest->xhToken);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求创建套接字测试成功,句柄:%lld,地址:%s:%d,TCP:%d,测试类型:%d"), lpszClientAddr, pSt_SocketTest->xhToken, pSt_SocketTest->st_SocketConn.tszAddr, pSt_SocketTest->st_SocketConn.nPort, pSt_SocketTest->bTCP, pSt_SocketTest->bConn);
	}
	else
	{
		if (pSt_SocketTest->bConn)
		{
			ModuleHelp_SocketTest_StopConnect(pSt_SocketTest->xhToken);
		}
		else
		{
			ModuleHelp_SocketTest_StopDatas(pSt_SocketTest->xhToken);
		}
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求销毁套接字测试成功,句柄:%lld"), lpszClientAddr, pSt_SocketTest->xhToken);
		delete pSt_SocketTest;
		pSt_SocketTest = NULL;
	}
	return TRUE;
}