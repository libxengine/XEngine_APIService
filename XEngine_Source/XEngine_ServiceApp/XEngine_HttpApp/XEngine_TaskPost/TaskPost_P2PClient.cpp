#include "../XEngine_Hdr.h"

void XCALLBACK HTTPTask_TastPost_P2PCallback(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol, XPVOID lParam)
{
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("HTTP客户端,公网:%s,私网:%s,连接:%s,P2XP心跳离开"), pSt_P2PProtocol->tszPublicAddr, pSt_P2PProtocol->tszPrivateAddr, pSt_P2PProtocol->tszConnectAddr);
}
// 处理P2P客户端HTTP请求的统一入口：
// 1) 根据unOperatorCode分发到具体业务流程(登录/登出/列表/打洞等)；
// 2) 解析请求协议并更新P2P客户端状态；
// 3) 通过统一协议回包告知调用方成功或失败；
// 返回值：true表示对应操作处理成功并已回包；false表示处理失败(通常已回错误包并记录日志)。
bool HTTPTask_TastPost_P2PClient(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int unOperatorCode)
{
	int nSDLen = 4096;
	XCHAR tszSDBuffer[4096] = {};

	// 登录请求：解析客户端地址信息，补齐公网地址，写入在线表并回复结果。
	if (XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQLOGIN == unOperatorCode)
	{
		XENGINE_P2XP_PEERINFO st_ClientPeer;
		memset(&st_ClientPeer, '\0', sizeof(XENGINE_P2XP_PEERINFO));

		if (!ModuleProtocol_Parse_P2PClient(lpszMsgBuffer, nMsgLen, &st_ClientPeer.st_PeerAddr))
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, "protocol is error");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,P2P处理登录错误,解析协议失败,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
			return false;
		}
		//如果没有填充公用地址,用他的连接地址代替,外网服务器都可以这样做
		if (_tcsxlen(st_ClientPeer.st_PeerAddr.tszPublicAddr) <= 0)
		{
			_tcsxcpy(st_ClientPeer.st_PeerAddr.tszPublicAddr, lpszClientAddr);
			APIAddr_IPAddr_SegAddr(st_ClientPeer.st_PeerAddr.tszPublicAddr, NULL);
		}
		st_ClientPeer.st_PeerTimer.dwUserTime = time(NULL);
		st_ClientPeer.st_PeerTimer.dwKeepAlive = time(NULL);
		st_ClientPeer.bIsLogin = true;
		_tcsxcpy(st_ClientPeer.st_PeerAddr.tszConnectAddr, lpszClientAddr);
		if (!ModuleHelp_P2PClient_Add(&st_ClientPeer))
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, "add client is failure");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,P2P处理登录错误,设置用户信息失败,错误码:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,P2P处理用户登录请求成功,用户名:%s"), lpszClientAddr, st_ClientPeer.st_PeerAddr.tszUserName);
	}
	// 登出请求：删除指定客户端在线状态并返回处理结果。
	else if (XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQLOGOUT == unOperatorCode)
	{
		XENGINE_P2XPPEER_PROTOCOL st_P2PProtocol;
		memset(&st_P2PProtocol, '\0', sizeof(XENGINE_P2XPPEER_PROTOCOL));

		if (!ModuleProtocol_Parse_P2PClient(lpszMsgBuffer, nMsgLen, &st_P2PProtocol))
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_JSON, "protocol is failure");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,P2P删除请求失败,协议解析错误,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
			return false;
		}
		ModuleHelp_P2PClient_Delete(&st_P2PProtocol);
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,P2P请求删除列表成功,删除地址:%s"), lpszClientAddr, st_P2PProtocol.tszPrivateAddr);
	}
	// 局域网列表请求：查询并返回当前可见的P2P节点列表信息。
	else if (XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQLANLIST == unOperatorCode)
	{
		XENGINE_P2XPPEER_PROTOCOL st_P2PProtocol;
		memset(&st_P2PProtocol, '\0', sizeof(XENGINE_P2XPPEER_PROTOCOL));

		if (!ModuleProtocol_Parse_P2PClient(lpszMsgBuffer, nMsgLen, &st_P2PProtocol))
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_JSON, "protocol is failure");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,P2P列表请求失败,协议解析错误,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
			return false;
		}
		//请求同步列表
		if (_tcsxlen(st_P2PProtocol.tszPrivateAddr) > 0)
		{
			int nListCount = 0;
			XENGINE_P2XPPEER_PROTOCOL** ppSt_ListClients;
			if (!ModuleHelp_P2PClient_GetLan(&st_P2PProtocol, &ppSt_ListClients, &nListCount))
			{
				ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, "get client is failure");
				XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,P2P列表请求失败,请求同步局域网列表失败,公有地址:%s,私有地址:%s,错误码:%lX"), lpszClientAddr, st_P2PProtocol.tszPublicAddr, st_P2PProtocol.tszPrivateAddr, ModuleHelp_GetLastError());
				return false;
			}
			ModuleProtocol_Packet_P2PLan(tszSDBuffer, &nSDLen, &ppSt_ListClients, nListCount);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			BaseLib_Memory_Free((XPPPMEM)&ppSt_ListClients, nListCount);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,P2P请求同步局域网列表成功,公有地址:%s,私有地址:%s"), lpszClientAddr, st_P2PProtocol.tszPublicAddr, st_P2PProtocol.tszPrivateAddr);
		}
		else
		{
			//公网下所有列表
			int nListCount = 0;
			XCHAR** ppszClientList;
			list<XENGINE_P2XPPEER_PROTOCOL> stl_ListClient;
			if (ModuleHelp_P2PClient_GetLList(st_P2PProtocol.tszPublicAddr, &ppszClientList, &nListCount))
			{
				for (int i = 0; i < nListCount; i++)
				{
					int nLanCount = 0;
					XENGINE_P2XPPEER_PROTOCOL** ppSt_ListClients;
					memset(st_P2PProtocol.tszPrivateAddr, '\0', sizeof(st_P2PProtocol.tszPrivateAddr));

					_tcsxcpy(st_P2PProtocol.tszPrivateAddr, ppszClientList[i]);

					if (ModuleHelp_P2PClient_GetLan(&st_P2PProtocol, &ppSt_ListClients, &nLanCount))
					{
						for (int j = 0; j < nLanCount; j++)
						{
							stl_ListClient.push_back(*ppSt_ListClients[j]);
						}
						BaseLib_Memory_Free((XPPPMEM)&ppSt_ListClients, nLanCount);
					}
				}
				BaseLib_Memory_Free((XPPPMEM)&ppszClientList, nListCount);
			}
			ModuleProtocol_Packet_P2PWLan(tszSDBuffer, &nSDLen, &stl_ListClient);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,P2P请求同步公有局域网列表成功,公有地址:%s"), lpszClientAddr, st_P2PProtocol.tszPublicAddr);
		}
	}
	// 外网打洞/互联请求：根据目标信息执行配对与回包通知。
	else if (XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQWLAN == unOperatorCode)
	{
		int nListCount = 0;
		XCHAR** pptszListAddr;

		ModuleHelp_P2PClient_GetWList(&pptszListAddr, &nListCount);
		ModuleProtocol_Packet_P2PWList(tszSDBuffer, &nSDLen, &pptszListAddr, nListCount);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,P2P请求公有地址列表成功,地址个数:%d"), lpszClientAddr, nListCount);
		BaseLib_Memory_Free((XPPPMEM)&pptszListAddr, nListCount);
	}
	else if (XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQHEART == unOperatorCode)
	{
		XENGINE_P2XPPEER_PROTOCOL st_P2XPProtocol;
		memset(&st_P2XPProtocol, '\0', sizeof(XENGINE_P2XPPEER_PROTOCOL));

		if (!ModuleProtocol_Parse_P2PClient(lpszMsgBuffer, nMsgLen, &st_P2XPProtocol))
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_JSON, "protocol is failure");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,P2P处理心跳协议错误,解析协议失败,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
			return false;
		}
		ModuleHelp_P2PClient_Heart(&st_P2XPProtocol);
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,P2P请求心跳成功"), lpszClientAddr);
	}
	else
	{
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_NOTSUPPORT, "protocol not support");
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求了一条未知的子协议：%lX"), lpszClientAddr, unOperatorCode);
	}
	return true;
}