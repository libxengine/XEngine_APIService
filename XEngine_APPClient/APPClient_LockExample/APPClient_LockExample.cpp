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
//macos::g++ -std=c++17 -Wall -g APPClient_LockExample.cpp -o APPClient_LockExample.exe -lXEngine_BaseLib -lXClient_APIHelp

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	int nLen = 0;
	LPCXSTR lpszOPenUrl = _X("http://127.0.0.1:5501/api?function=lock&params1=1000106561&params1=1");
	//自己创建打开
	XCHAR* ptszBuffer = NULL;
	if (!APIClient_Http_Request(_X("GET"), lpszOPenUrl, NULL, NULL, &ptszBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBuffer);
	//打开读锁
	LPCXSTR lpszReadUrl = _X("http://127.0.0.1:5501/api?function=lock&params1=1000106561&params2=3");
	if (!APIClient_Http_Request(_X("GET"), lpszReadUrl, NULL, NULL, &ptszBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:\n%s\n", nLen, ptszBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBuffer);
	//打开写锁
	LPCXSTR lpszWriteUrl = _X("http://127.0.0.1:5501/api?function=lock&params1=1000106561&params2=5");
	if (!APIClient_Http_Request(_X("GET"), lpszWriteUrl, NULL, NULL, &ptszBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:\n%s\n", nLen, ptszBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBuffer);
	//释放读锁
	LPCXSTR lpszUNReadUrl = _X("http://127.0.0.1:5501/api?function=lock&params1=1000106561&params2=4");
	if (!APIClient_Http_Request(_X("GET"), lpszUNReadUrl, NULL, NULL, &ptszBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:\n%s\n", nLen, ptszBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBuffer);
	//打开解锁
	if (!APIClient_Http_Request(_X("GET"), lpszWriteUrl, NULL, NULL, &ptszBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:\n%s\n", nLen, ptszBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBuffer);
	//关闭
	LPCXSTR lpszCloseUrl = _X("http://127.0.0.1:5501/api?function=lock&params1=1000106561&params2=2");
	if (!APIClient_Http_Request(_X("GET"), lpszCloseUrl, NULL, NULL, &ptszBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:\n%s\n", nLen, ptszBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBuffer);
#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}