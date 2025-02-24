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
//g++ -std=c++17 -Wall -g APPClient_APIQueryExample.cpp -o APPClient_APIQueryExample.exe -I ../../XEngine_Source/XEngine_Depend/XEngine_Module/jsoncpp -L ../../XEngine_Release -lXEngine_BaseLib -lXClient_APIHelp -ljsoncpp -Wl,-rpath=../../XEngine_Release

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	int nLen = 0;
	int nCode = 0;
	XCHAR tszMsgBuffer[1024];
	LPCXSTR lpszTypeOne = _X("http://127.0.0.1:5501/api?function=ip&param=117.172.221.14");
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("GET"), lpszTypeOne, NULL, &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
#ifdef _MSC_BUILD
	BaseLib_Charset_UTFToAnsi(ptszMsgBuffer, tszMsgBuffer, &nLen);
	printf("接受到数据,大小:%d,内容:%s\n", nLen, tszMsgBuffer);
#else
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
#endif
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
	//////////////////////////////////////////////////////////////////////////
	nLen = 0;
	nCode = 0;
	LPCXSTR lpszTypeZ = _X("http://127.0.0.1:5501/api?function=mac&param=00:00:0C");
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	if (!APIClient_Http_Request(_X("GET"), lpszTypeZ, NULL, &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
#ifdef _MSC_BUILD
	BaseLib_Charset_UTFToAnsi(ptszMsgBuffer, tszMsgBuffer, &nLen);
	printf("接受到数据,大小:%d,内容:%s\n", nLen, tszMsgBuffer);
#else
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
#endif
	BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}