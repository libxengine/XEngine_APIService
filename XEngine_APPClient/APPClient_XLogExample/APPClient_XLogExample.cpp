#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"jsoncpp")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_NetHelp/NetHelp_APIClient")
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
#include <XEngine_Include/XEngine_NetHelp/APIClient_Define.h>
#include <XEngine_Include/XEngine_NetHelp/APIClient_Error.h>

//需要优先配置XEngine
//WINDOWS支持VS2022 x64 debug 编译调试
//linux::g++ -std=c++17 -Wall -g APPClient_XLogExample.cpp -o APPClient_XLogExample.exe -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_NetHelp -lXEngine_BaseLib -lNetHelp_APIClient
//macos::g++ -std=c++17 -Wall -g APPClient_XLogExample.cpp -o APPClient_XLogExample.exe -lXEngine_BaseLib -lNetHelp_APIClient

LPCTSTR lpszTableName = _T("xengine");

int test_create()
{
	int nLen = 0;
	int nCode = 0;
	LPCTSTR lpszAPIUrl = _T("http://127.0.0.1:5501/api?function=log&params1=0");

	Json::Value st_JsonRoot;
	st_JsonRoot["tszTableName"] = lpszTableName;

	TCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_T("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	return 0;
}
int test_insert()
{
	int nLen = 0;
	int nCode = 0;
	LPCTSTR lpszAPIUrl = _T("http://127.0.0.1:5501/api?function=log&params1=1");
	LPCTSTR lpszMsgBuffer = _T("adwdad12d21d123d132rd213d32f23df23rf");

	Json::Value st_JsonRoot;
	Json::StreamWriterBuilder st_JsonBuilder;
	st_JsonRoot["tszTableName"] = lpszTableName;
	st_JsonRoot["tszLogBuffer"] = lpszMsgBuffer;
	st_JsonRoot["nLogSize"] = _tcslen(lpszMsgBuffer);

	st_JsonRoot["tszFileName"] = "file.cpp";
	st_JsonRoot["tszFuncName"] = "xengine_file_insert";
	st_JsonRoot["tszLogTimer"] = "2023-01-13 22:10:01";
	st_JsonRoot["nLogLine"] = 102;
	st_JsonRoot["nLogLevel"] = 4;

	st_JsonBuilder["emitUTF8"] = true;

	TCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_T("POST"), lpszAPIUrl, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	return 0;
}
int test_query()
{
	int nLen = 0;
	int nCode = 0;
	LPCTSTR lpszAPIUrl = _T("http://127.0.0.1:5501/api?function=log&params1=2");

	Json::Value st_JsonRoot;
	st_JsonRoot["tszTableName"] = lpszTableName;
	st_JsonRoot["tszTimeStart"] = "2023-01-13 22:10:00";
	st_JsonRoot["tszTimeEnd"] = "2023-01-13 22:10:02";

	TCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_T("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
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
	LPCTSTR lpszAPIUrl = _T("http://127.0.0.1:5501/api?function=log&params1=3");

	Json::Value st_JsonRoot;
	st_JsonRoot["tszTableName"] = lpszTableName;

	TCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_T("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
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
	test_insert();
	test_insert();
	test_query();
	test_delete();

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}