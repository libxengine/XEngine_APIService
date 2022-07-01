#ifdef _MSC_BUILD
#include <windows.h>
#include <tchar.h>
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_Core/XEngine_NetXApi")
#pragma comment(lib,"XEngine_NetHelp/NetHelp_APIHelp")
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"../../XEngine_Source/x64/Debug/jsoncpp")
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif
#include <json/json.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Core/NetXApi_Define.h>
#include <XEngine_Include/XEngine_Core/NetXApi_Error.h>
#include <XEngine_Include/XEngine_NetHelp/APIHelp_Define.h>
#include <XEngine_Include/XEngine_NetHelp/APIHelp_Error.h>
#include "../../XEngine_Source/XEngine_UserProtocol.h"

//需要优先配置XEngine
//WINDOWS使用VS2022 x64 debug 编译
//linux使用下面的命令编译
//g++ -std=c++17 -Wall -g APPClient_P2PExample.cpp -o APPClient_P2PExample.exe -I ../../XEngine_Source/XEngine_ThirdPart/jsoncpp -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_Core -L /usr/local/lib/XEngine_Release/XEngine_NetHelp -lXEngine_BaseLib -lXEngine_NetXApi -lNetHelp_APIHelp -ljsoncpp

LPCTSTR lpszUserName = _T("123123aa");
TCHAR tszPublicAddr[128];
TCHAR tszPrivateAddr[128];

int nPort = 5103;
SOCKET m_hSocket;

int APPClient_P2XPLogin()
{
	Json::Value st_JsonRoot;
	LPCTSTR lpszAddr = _T("http://192.168.1.8:5501/api?function=p2p&params1=24577");
	ENUM_XENGINE_NETXAPI_SOCKET_CONNECTTYPE dwNetType;

	memset(tszPublicAddr, '\0', sizeof(tszPublicAddr));
	memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
	//获取网络连接类型
	if (!NetXApi_Socket_GetNetConnectType(&dwNetType))
	{
		return -1;
	}
	int nListCount = 0;
	NETXAPI_CARDINFO** ppSt_APICard;
	NetXApi_Socket_GetCardInfo(&ppSt_APICard, &nListCount, AF_INET);
	APIHelp_NetWork_GetIPNet(tszPublicAddr);
	if (nListCount <= 0)
	{
		return -1;
	}
	//得到IP地址
	strcpy(tszPrivateAddr, ppSt_APICard[0]->tszIPAddr);
	BaseLib_OperatorMemory_Free((XPPPMEM)&ppSt_APICard, nListCount);

	st_JsonRoot["tszUserName"] = lpszUserName;
	st_JsonRoot["tszPrivateAddr"] = tszPrivateAddr;
	st_JsonRoot["tszPublicAddr"] = tszPublicAddr;
	st_JsonRoot["dwConnectType"] = (Json::Value::UInt)dwNetType;
	st_JsonRoot["dwPeerType"] = 0;

	int nMsgLen = 0;
	int nHTTPCode = 0;
	TCHAR* ptszMsgBuffer = NULL;
	if (!APIHelp_HttpRequest_Post(lpszAddr, st_JsonRoot.toStyledString().c_str(), &nHTTPCode, &ptszMsgBuffer, &nMsgLen))
	{
		return -1;
	}
	printf("APPClient_P2XPLogin,&nMsgLen:%d,%s\n", nMsgLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}

int APPClient_P2XPList()
{
	Json::Value st_JsonRoot;
	LPCTSTR lpszAddr = _T("http://192.168.1.8:5501/api?function=p2p&params1=24579");

	st_JsonRoot["tszUserName"] = lpszUserName;
	st_JsonRoot["tszPrivateAddr"] = tszPrivateAddr;
	st_JsonRoot["tszPublicAddr"] = tszPublicAddr;

	int nMsgLen = 0;
	int nHTTPCode = 0;
	TCHAR* ptszMsgBuffer = NULL;
	if (!APIHelp_HttpRequest_Post(lpszAddr, st_JsonRoot.toStyledString().c_str(), &nHTTPCode, &ptszMsgBuffer, &nMsgLen))
	{
		return -1;
	}
	printf("APPClient_P2XPList,&nMsgLen:%d,%s\n", nMsgLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}

int APPClient_P2XPGetUser()
{
	Json::Value st_JsonRoot;
	LPCTSTR lpszAddr = _T("http://192.168.1.8:5501/api?function=p2p&params1=24583");

	st_JsonRoot["tszUserName"] = lpszUserName;
	st_JsonRoot["tszPrivateAddr"] = tszPrivateAddr;
	st_JsonRoot["tszPublicAddr"] = tszPublicAddr;

	int nMsgLen = 0;
	int nHTTPCode = 0;
	TCHAR* ptszMsgBuffer = NULL;
	if (!APIHelp_HttpRequest_Post(lpszAddr, st_JsonRoot.toStyledString().c_str(), &nHTTPCode, &ptszMsgBuffer, &nMsgLen))
	{
		return -1;
	}
	printf("APPClient_P2XPGetUser,&nMsgLen:%d,%s\n", nMsgLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}

int APPClient_P2XPConnect()
{
	Json::Value st_JsonRoot;
	LPCTSTR lpszAddr = _T("http://192.168.1.8:5501/api?function=p2p&params1=24581");

	st_JsonRoot["tszUserName"] = lpszUserName;
	st_JsonRoot["tszPrivateAddr"] = tszPrivateAddr;
	st_JsonRoot["tszPublicAddr"] = tszPublicAddr;

	int nMsgLen = 0;
	int nHTTPCode = 0;
	TCHAR* ptszMsgBuffer = NULL;
	if (!APIHelp_HttpRequest_Post(lpszAddr, st_JsonRoot.toStyledString().c_str(), &nHTTPCode, &ptszMsgBuffer, &nMsgLen))
	{
		return -1;
	}
	printf("APPClient_P2XPConnect,&nMsgLen:%d,%s\n", nMsgLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
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
	//APPClient_P2XPGetUser();
	//APPClient_P2XPConnect();

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}