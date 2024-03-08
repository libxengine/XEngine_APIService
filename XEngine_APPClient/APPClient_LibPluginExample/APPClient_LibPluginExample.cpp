#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_Client/XClient_APIHelp")
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_Client/APIClient_Define.h>
#include <XEngine_Include/XEngine_Client/APIClient_Error.h>

//需要优先配置XEngine
//WINDOWS支持VS2022 x64 debug 编译调试
//macos::g++ -std=c++17 -Wall -g APPClient_LibPluginExample.cpp -o APPClient_LibPluginExample.exe -lXEngine_BaseLib -lXClient_APIHelp

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	int nLen = 0;
	XCHAR* ptszMsgBuffer = NULL;
	LPCXSTR lpszPassUrl = _X("http://127.0.0.1:5501/api?function=pass&params1=1&params2=4");
	if (!APIClient_Http_Request(_X("GET"), lpszPassUrl, NULL, NULL, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	LPCXSTR lpszZodiacUrl = _X("http://127.0.0.1:5501/api?function=zodiac&params1=19880121");
	if (!APIClient_Http_Request(_X("GET"), lpszZodiacUrl, NULL, NULL, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	LPCXSTR lpszTimeUrl = _X("http://127.0.0.1:5501/api?function=timezone&params1=1&params2=1-20");
	if (!APIClient_Http_Request(_X("GET"), lpszTimeUrl, NULL, NULL, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	LPCXSTR lpszBmiUrl = _X("http://127.0.0.1:5501/api?function=bmindex&params1=1.78&params2=62");
	if (!APIClient_Http_Request(_X("GET"), lpszBmiUrl, NULL, NULL, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}