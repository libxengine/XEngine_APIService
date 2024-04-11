#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"jsoncpp")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_Client/XClient_APIHelp")
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <json/json.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Client/APIClient_Define.h>
#include <XEngine_Include/XEngine_Client/APIClient_Error.h>

//需要优先配置XEngine
//WINDOWS支持VS2022 x64 debug 编译调试
//macos::g++ -std=c++17 -Wall -g APPClient_SLinkExample.cpp -o APPClient_SLinkExample.exe -lXEngine_BaseLib -lXClient_APIHelp

XNETHANDLE xhToken = 0;
#define QRCODE_BUFFER_SIZE 1024 * 1024 * 10
LPCXSTR lpszFileName = _X("D:\\XEngine_APIService\\XEngine_APPClient\\x64\\Debug\\1.png");

int test_create()
{
	int nLen = 0;
	int nCode = 0;
	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=slink&params1=0");

	Json::Value st_JsonRoot;
	st_JsonRoot["tszFullUrl"] = "http://bbs.xyry.org/forum.php?mod=viewthread&tid=2&extra=page%3D1";
	st_JsonRoot["tszCvtUrl"] = "http://app.xyry.org:5501";
	st_JsonRoot["nLength"] = 6;

	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}
int test_get()
{
	int nLen = 0;
	int nCode = 0;
	XCHAR* ptszMsgBuffer;
	Json::Value st_JsonRoot;
	st_JsonRoot["tszMapUrl"] = "http://app.xyry.org:5501";

	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=slink&params1=1");
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}
int test_List()
{
	int nLen = 0;
	int nCode = 0;
	XCHAR* ptszMsgBuffer;

	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=slink&params1=3");
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, NULL, &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}
int test_delete()
{
	int nLen = 0;
	int nCode = 0;
	XCHAR* ptszMsgBuffer;
	Json::Value st_JsonRoot;
	st_JsonRoot["tszMapUrl"] = "http://app.xyry.org:5501";

	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=slink&params1=2");
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	test_create();
	test_get();
	test_List();
	test_delete();

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}