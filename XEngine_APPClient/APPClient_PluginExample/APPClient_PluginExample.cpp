#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_NetHelp/NetHelp_APIHelp")
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_ProtocolHdr.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_NetHelp/APIHelp_Define.h>
#include <XEngine_Include/XEngine_NetHelp/APIHelp_Error.h>

//需要优先配置XEngine
//WINDOWS支持VS2022 x64 debug 编译调试
//linux::g++ -std=c++17 -Wall -g APPClient_PluginExample.cpp -o APPClient_PluginExample.exe -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_NetHelp -lXEngine_BaseLib -lNetHelp_APIHelp
//macos::g++ -std=c++17 -Wall -g APPClient_PluginExample.cpp -o APPClient_PluginExample.exe -lXEngine_BaseLib -lNetHelp_APIHelp

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	int nLen = 0;
	TCHAR* ptszMsgBuffer = NULL;
	LPCTSTR lpszPassUrl = _T("http://127.0.0.1:5501/api?function=pass&params1=1&params2=4");
	if (!APIHelp_HttpRequest_Get(lpszPassUrl, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	LPCTSTR lpszZodiacUrl = _T("http://127.0.0.1:5501/api?function=zodiac&params1=19880121");
	if (!APIHelp_HttpRequest_Get(lpszZodiacUrl, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	LPCTSTR lpszTimeUrl = _T("http://127.0.0.1:5501/api?function=timezone&params1=1&params2=1-20");
	if (!APIHelp_HttpRequest_Get(lpszTimeUrl, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	LPCTSTR lpszBmiUrl = _T("http://127.0.0.1:5501/api?function=bmindex&params1=1.78&params2=62");
	if (!APIHelp_HttpRequest_Get(lpszBmiUrl, &ptszMsgBuffer, &nLen))
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