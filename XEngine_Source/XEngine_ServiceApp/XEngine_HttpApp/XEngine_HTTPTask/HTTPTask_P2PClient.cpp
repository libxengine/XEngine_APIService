#include "../XEngine_Hdr.h"

BOOL XEngine_HTTPTask_P2PClient(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, int unOperatorCode)
{
	int nSDLen = 4096;
	int nRVLen = 4096;
	TCHAR tszSDBuffer[4096];
	TCHAR tszRVBuffer[MAX_PATH];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));
	memset(tszRVBuffer, '\0', sizeof(tszRVBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	if (XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQLOGIN == unOperatorCode)
	{
		XENGINE_P2XP_PEERINFO st_ClientPeer;
		memset(&st_ClientPeer, '\0', sizeof(XENGINE_P2XP_PEERINFO));

		if (!ModuleProtocol_Parse_P2PClient(lpszMsgBuffer, nMsgLen, &st_ClientPeer.st_PeerAddr))
		{
			ModuleProtocol_Packet_P2PCommon(tszRVBuffer, &nRVLen, 400, "协议错误");
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,处理登录错误,解析协议失败,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
			return FALSE;
		}
		//如果没有填充公用地址,用他的连接地址代替,外网服务器都可以这样做
		if (_tcslen(st_ClientPeer.st_PeerAddr.tszPublicAddr) <= 0)
		{
			_tcscpy(st_ClientPeer.st_PeerAddr.tszPublicAddr, lpszClientAddr);
			BaseLib_OperatorIPAddr_SegAddr(st_ClientPeer.st_PeerAddr.tszPublicAddr, NULL);
		}
		//获取外网IP所在位置
		ModuleDatabase_IPInfo_IPV4Query(&st_ClientPeer.st_IPAddrInfo, st_ClientPeer.st_PeerAddr.tszPublicAddr);

		st_ClientPeer.st_PeerTimer.dwUserTime = time(NULL);
		st_ClientPeer.st_PeerTimer.dwKeepAlive = time(NULL);
		st_ClientPeer.bIsLogin = TRUE;
		_tcscpy(st_ClientPeer.st_PeerAddr.tszConnectAddr, lpszClientAddr);
		if (!ModuleHelp_P2PClient_Add(&st_ClientPeer))
		{
			ModuleProtocol_Packet_P2PCommon(tszRVBuffer, &nRVLen, 500, "内部错误");
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,处理登录错误,设置用户信息失败,错误码:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
			return FALSE;
		}
		ModuleProtocol_Packet_P2PCommon(tszSDBuffer, &nSDLen);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,处理用户登录请求成功,用户名:%s"), lpszClientAddr, st_ClientPeer.st_PeerAddr.tszUserName);
	}
	else if (XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQLANLIST == unOperatorCode)
	{
		XENGINE_P2XPPEER_PROTOCOL st_P2PProtocol;
		memset(&st_P2PProtocol, '\0', sizeof(XENGINE_P2XPPEER_PROTOCOL));

		if (!ModuleProtocol_Parse_P2PClient(lpszMsgBuffer, nMsgLen, &st_P2PProtocol))
		{
			ModuleProtocol_Packet_P2PCommon(tszRVBuffer, &nRVLen, 400, "协议错误");
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,列表请求失败,协议解析错误,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
			return FALSE;
		}
		//请求同步列表
		if (_tcslen(st_P2PProtocol.tszPrivateAddr) > 0)
		{
			int nListCount = 0;
			XENGINE_P2XPPEER_PROTOCOL** ppSt_ListClients;
			if (!ModuleHelp_P2PClient_GetLan(&st_P2PProtocol, &ppSt_ListClients, &nListCount))
			{
				ModuleProtocol_Packet_P2PCommon(tszRVBuffer, &nRVLen, 500, "内部错误");
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
				XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,列表请求失败,请求同步局域网列表失败,公有地址:%s,私有地址:%s,错误码:%lX"), lpszClientAddr, st_P2PProtocol.tszPublicAddr, st_P2PProtocol.tszPrivateAddr, ModuleHelp_GetLastError());
				return FALSE;
			}
			ModuleProtocol_Packet_P2PLan(tszSDBuffer, &nSDLen, &ppSt_ListClients, nListCount);
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			BaseLib_OperatorMemory_Free((XPPPMEM)&ppSt_ListClients, nListCount);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求同步局域网列表成功,公有地址:%s,私有地址:%s"), lpszClientAddr, st_P2PProtocol.tszPublicAddr, st_P2PProtocol.tszPrivateAddr);
		}
		else
		{
			//公网下所有列表
			int nListCount = 0;
			TCHAR** ppszClientList;
			list<XENGINE_P2XPPEER_PROTOCOL> stl_ListClient;
			if (ModuleHelp_P2PClient_GetLList(st_P2PProtocol.tszPublicAddr, &ppszClientList, &nListCount))
			{
				for (int i = 0; i < nListCount; i++)
				{
					int nLanCount = 0;
					XENGINE_P2XPPEER_PROTOCOL** ppSt_ListClients;
					memset(st_P2PProtocol.tszPrivateAddr, '\0', sizeof(st_P2PProtocol.tszPrivateAddr));

					_tcscpy(st_P2PProtocol.tszPrivateAddr, ppszClientList[i]);

					if (ModuleHelp_P2PClient_GetLan(&st_P2PProtocol, &ppSt_ListClients, &nLanCount))
					{
						for (int j = 0; j < nLanCount; j++)
						{
							stl_ListClient.push_back(*ppSt_ListClients[j]);
						}
						BaseLib_OperatorMemory_Free((XPPPMEM)&ppSt_ListClients, nLanCount);
					}
				}
				BaseLib_OperatorMemory_Free((XPPPMEM)&ppszClientList, nListCount);
			}
			ModuleProtocol_Packet_P2PWLan(tszRVBuffer, &nRVLen, &stl_ListClient);
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求同步公有局域网列表成功,公有地址:%s"), lpszClientAddr, st_P2PProtocol.tszPublicAddr);
		}
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求了一条未知的子协议：%lX"), lpszClientAddr, unOperatorCode);
	}
	return TRUE;
}