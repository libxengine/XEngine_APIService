﻿#ifdef _MSC_BUILD
#include <windows.h>
#include <tchar.h>
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_Client/XClient_APIHelp")
#pragma comment(lib,"XEngine_NetHelp/NetHelp_XSocket")
#pragma comment(lib,"Ws2_32")
#ifdef _WIN64
#pragma comment(lib,"../../XEngine_Source/x64/Debug/jsoncpp")
#else
#pragma comment(lib,"../../XEngine_Source/Debug/jsoncpp")
#endif
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif
#include <json/json.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Client/APIClient_Define.h>
#include <XEngine_Include/XEngine_Client/APIClient_Error.h>
#include <XEngine_Include/XEngine_NetHelp/XSocket_Define.h>
#include <XEngine_Include/XEngine_NetHelp/XSocket_Error.h>
#include "../../XEngine_Source/XEngine_UserProtocol.h"

//需要优先配置XEngine
//WINDOWS使用VS2022 x64 debug 编译
//linux使用下面的命令编译
//g++ -std=c++17 -Wall -g APPClient_P2PExample.cpp -o APPClient_P2PExample.exe -I ../../XEngine_Source/XEngine_Depend/XEngine_Module/jsoncpp -L ../../XEngine_Release -lXEngine_BaseLib -lXEngine_NetXApi -lXClient_APIHelp -ljsoncpp -Wl,-rpath=../../XEngine_Release

LPCXSTR lpszUserName = _X("123123aa");
XCHAR tszPublicAddr[128];
XCHAR tszPrivateAddr[128];

int nPort = 5103;
SOCKET m_hSocket;

BOOL APIHelp_NetWork_GetIPNet(XCHAR* ptszIPAddr)
{
	//获取本地外网IP地址
	int nBLen = 0;
	XCHAR* ptszBody = NULL;
	LPCXSTR lpszUrl = _X("http://members.3322.org/dyndns/getip");
	LPCXSTR lpszHdrBuffer = _X("Connection: close\r\nDNT: 1\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/97.0.4692.71 Safari/537.36 Edg/97.0.1072.55\r\nAccept: text/html\r\nAccept-Language: zh-CN,zh\r\nAccept-Encoding: deflate\r\n");

	if (!APIClient_Http_Request(_X("GET"), lpszUrl, NULL, NULL, &ptszBody, &nBLen, lpszHdrBuffer))
	{
		return FALSE;
	}
	memcpy(ptszIPAddr, ptszBody, nBLen - 1);
	BaseLib_Memory_FreeCStyle((VOID**)&ptszBody);
	return TRUE;
}
int APPClient_P2XPLogin()
{
	Json::Value st_JsonRoot;
	LPCXSTR lpszAddr = _X("http://127.0.0.1:5501/api?function=p2p&params1=24577");
	ENUM_NETHELP_XSOCKET_API_CONNECTTYPE dwNetType;

	memset(tszPublicAddr, '\0', sizeof(tszPublicAddr));
	memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
	//获取网络连接类型
	if (!XSocket_Api_GetNetConnectType(&dwNetType))
	{
		return -1;
	}
	int nListCount = 0;
	XSOCKET_CARDINFO** ppSt_APICard;
	XSocket_Api_GetCardInfo(&ppSt_APICard, &nListCount, AF_INET);
	APIHelp_NetWork_GetIPNet(tszPublicAddr);
	if (nListCount <= 0)
	{
		return -1;
	}
	//得到IP地址
	strcpy(tszPrivateAddr, ppSt_APICard[0]->tszIPAddr);
	BaseLib_Memory_Free((XPPPMEM)&ppSt_APICard, nListCount);

	st_JsonRoot["tszUserName"] = lpszUserName;
	st_JsonRoot["tszPrivateAddr"] = tszPrivateAddr;
	st_JsonRoot["tszPublicAddr"] = tszPublicAddr;
	st_JsonRoot["dwConnectType"] = (Json::Value::UInt)dwNetType;
	st_JsonRoot["dwPeerType"] = 0;

	int nMsgLen = 0;
	int nHTTPCode = 0;
	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAddr, st_JsonRoot.toStyledString().c_str(), &nHTTPCode, &ptszMsgBuffer, &nMsgLen))
	{
		return -1;
	}
	printf("APPClient_P2XPLogin,&nMsgLen:%d,%s\n", nMsgLen, ptszMsgBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}

int APPClient_P2XPList()
{
	Json::Value st_JsonRoot;
	LPCXSTR lpszAddr = _X("http://127.0.0.1:5501/api?function=p2p&params1=24581");

	st_JsonRoot["tszUserName"] = lpszUserName;
	st_JsonRoot["tszPrivateAddr"] = tszPrivateAddr;
	st_JsonRoot["tszPublicAddr"] = tszPublicAddr;

	int nMsgLen = 0;
	int nHTTPCode = 0;
	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAddr, st_JsonRoot.toStyledString().c_str(), &nHTTPCode, &ptszMsgBuffer, &nMsgLen))
	{
		return -1;
	}
	printf("APPClient_P2XPList,&nMsgLen:%d,%s\n", nMsgLen, ptszMsgBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}

int APPClient_P2XPWan()
{
	Json::Value st_JsonRoot;
	LPCXSTR lpszAddr = _X("http://127.0.0.1:5501/api?function=p2p&params1=24583");

	int nMsgLen = 0;
	int nHTTPCode = 0;
	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAddr, NULL, &nHTTPCode, &ptszMsgBuffer, &nMsgLen))
	{
		return -1;
	}
	printf("APPClient_P2XPWan,&nMsgLen:%d,%s\n", nMsgLen, ptszMsgBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}

int APPClient_P2XPLogout()
{
	Json::Value st_JsonRoot;
	LPCXSTR lpszAddr = _X("http://127.0.0.1:5501/api?function=p2p&params1=24579");

	st_JsonRoot["tszUserName"] = lpszUserName;
	st_JsonRoot["tszPrivateAddr"] = tszPrivateAddr;
	st_JsonRoot["tszPublicAddr"] = tszPublicAddr;

	int nMsgLen = 0;
	int nHTTPCode = 0;
	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAddr, st_JsonRoot.toStyledString().c_str(), &nHTTPCode, &ptszMsgBuffer, &nMsgLen))
	{
		return -1;
	}
	printf("APPClient_P2XPLogout,&nMsgLen:%d,%s\n", nMsgLen, ptszMsgBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif

	APPClient_P2XPLogin();
	APPClient_P2XPList();
	APPClient_P2XPWan();
	APPClient_P2XPLogout();

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}