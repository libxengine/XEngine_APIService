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
//g++ -std=c++17 -Wall -g APPClient_SocketExample.cpp -o APPClient_SocketExample.exe -I ../../XEngine_Source/XEngine_Depend/XEngine_Module/jsoncpp -L ../../XEngine_Release -lXEngine_BaseLib -lXClient_APIHelp -ljsoncpp -Wl,-rpath=../../XEngine_Release

XNETHANDLE xhToken = 0;
#define QRCODE_BUFFER_SIZE 1024 * 1024 * 10
LPCXSTR lpszFileName = _X("D:\\XEngine_APIService\\XEngine_APPClient\\x64\\Debug\\1.png");

int test_create()
{
	int nLen = 0;
	int nCode = 0;
	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=socket&params1=0");

	Json::Value st_JsonRoot;
	st_JsonRoot["tszAPIUrl"] = "http://127.0.0.1:5501/api?function=report&params1=0";
	st_JsonRoot["bTCP"] = true;
	st_JsonRoot["bConn"] = true;
	st_JsonRoot["tszAddr"] = "127.0.0.1";
	st_JsonRoot["nPort"] = 5501;
	st_JsonRoot["nCloseWaitContTime"] = 2000;
	st_JsonRoot["nConnectCount"] = 2;
	st_JsonRoot["nConnectTest"] = 1;
	st_JsonRoot["nContWaitTime"] = 1000;

	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);

	st_JsonRoot.clear();
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_ReaderBuilder;
	//解析JSON
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_ReaderBuilder.newCharReader());
	if (!pSt_JsonReader->parse(ptszMsgBuffer, ptszMsgBuffer + nLen, &st_JsonRoot, &st_JsonError))
	{
		return 0;
	}
	Json::Value st_JsonObject = st_JsonRoot["data"];
	if (!st_JsonObject["xhToken"].isNull())
	{
		xhToken = st_JsonObject["xhToken"].asInt64();
	}
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}
int test_delete()
{
	int nLen = 0;
	int nCode = 0;
	XCHAR* ptszMsgBuffer;
	Json::Value st_JsonRoot;
	st_JsonRoot["bTCP"] = true;
	st_JsonRoot["bConn"] = true;
	st_JsonRoot["xhToken"] = xhToken;

	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=socket&params1=1");
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	return 0;
}

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	test_create();
	test_delete();

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}