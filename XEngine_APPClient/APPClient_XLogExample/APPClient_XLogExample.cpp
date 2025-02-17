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
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Client/APIClient_Define.h>
#include <XEngine_Include/XEngine_Client/APIClient_Error.h>

//需要优先配置XEngine
//WINDOWS支持VS2022 x64 debug 编译调试
//g++ -std=c++17 -Wall -g APPClient_XLogExample.cpp -o APPClient_XLogExample.exe -I ../../XEngine_Source/XEngine_Depend/XEngine_Module/jsoncpp -L ../../XEngine_Release -lXEngine_BaseLib -lXClient_APIHelp -ljsoncpp -Wl,-rpath=../../XEngine_Release

LPCXSTR lpszTableName = _X("xengine");

int test_create()
{
	int nLen = 0;
	int nCode = 0;
	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=log&params1=0");

	Json::Value st_JsonRoot;
	st_JsonRoot["tszTableName"] = lpszTableName;

	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	return 0;
}
int test_insert()
{
	int nLen = 0;
	int nCode = 0;
	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=log&params1=1");
	LPCXSTR lpszMsgBuffer = _X("adwdad12d21d123d132rd213d32f23df23rf");

	Json::Value st_JsonRoot;
	Json::StreamWriterBuilder st_JsonBuilder;
	st_JsonRoot["tszTableName"] = lpszTableName;
	st_JsonRoot["tszLogBuffer"] = lpszMsgBuffer;
	st_JsonRoot["nLogSize"] = _tcsxlen(lpszMsgBuffer);

	st_JsonRoot["tszFileName"] = "file.cpp";
	st_JsonRoot["tszFuncName"] = "xengine_file_insert";
	st_JsonRoot["tszLogTimer"] = "2023-01-13 22:10:01";
	st_JsonRoot["nLogLine"] = 102;
	st_JsonRoot["nLogLevel"] = 4;

	st_JsonBuilder["emitUTF8"] = true;

	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	return 0;
}
int test_query()
{
	int nLen = 0;
	int nCode = 0;
	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=log&params1=2");

	Json::Value st_JsonRoot;
	st_JsonRoot["tszTableName"] = lpszTableName;
	st_JsonRoot["tszTimeStart"] = "2023-01-13 22:10:00";
	st_JsonRoot["tszTimeEnd"] = "2023-01-13 22:10:02";

	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	return 0;
}
int test_list()
{
	int nLen = 0;
	int nCode = 0;
	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=log&params1=3");

	Json::Value st_JsonRoot;

	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	return 0;
}
int test_delete()
{
	int nLen = 0;
	int nCode = 0;
	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=log&params1=4");

	Json::Value st_JsonRoot;
	st_JsonRoot["tszTableName"] = lpszTableName;

	XCHAR* ptszMsgBuffer = NULL;
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
	test_insert();
	test_insert();
	test_query();
	test_list();
	test_delete();

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}