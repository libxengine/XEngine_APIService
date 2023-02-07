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
//linux::g++ -std=c++17 -Wall -g APPClient_QRExample.cpp -o APPClient_QRExample.exe -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_NetHelp -lXEngine_BaseLib -lNetHelp_APIClient
//macos::g++ -std=c++17 -Wall -g APPClient_QRExample.cpp -o APPClient_QRExample.exe -lXEngine_BaseLib -lNetHelp_APIClient

#define QRCODE_BUFFER_SIZE 1024 * 1024 * 10

LPCTSTR lpszFileName = _T("D:\\XEngine_APIService\\XEngine_APPClient\\x64\\Debug\\1.png");

int test_create()
{
	int nLen = 0;
	int nCode = 0;
	LPCTSTR lpszAPIUrl = _T("http://127.0.0.1:5501/api?function=qrcode&params1=0");

	Json::Value st_JsonRoot;
	st_JsonRoot["tszMsgBuffer"] = lpszAPIUrl;
	st_JsonRoot["tszFmtBuffer"] = ".png";

	TCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_T("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	FILE* pSt_File = fopen(lpszFileName, "wb");
	if (NULL != pSt_File)
	{
		fwrite(ptszMsgBuffer, 1, nLen, pSt_File);
		fclose(pSt_File);
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	return 0;
}
int test_parse()
{
	int nCode = 0;
	TCHAR* ptszMsgBuffer = (TCHAR*)malloc(QRCODE_BUFFER_SIZE);

	LPCTSTR lpszAPIUrl = _T("http://127.0.0.1:5501/api?function=qrcode&params1=1");
	FILE* pSt_File = fopen(lpszFileName, "rb");
	if (NULL != pSt_File)
	{
		LPCTSTR lpszCustomHdr = _T("Content-Type: image/png\r\n");
		memset(ptszMsgBuffer, '\0', QRCODE_BUFFER_SIZE);
		int nRet = fread(ptszMsgBuffer, 1, QRCODE_BUFFER_SIZE, pSt_File);
		
		TCHAR* ptszBodyBuffer = NULL;
		if (!APIClient_Http_Request(_T("POST"), lpszAPIUrl, ptszMsgBuffer, &nCode, &ptszBodyBuffer, &nRet, lpszCustomHdr))
		{
			printf("发送投递失败！\n");
			return 0;
		}
		printf("接受到数据,大小:%d,内容:%s\n", nRet, ptszBodyBuffer);
		BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszBodyBuffer);
	}
	return 0;
}

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	test_create();
	test_parse();

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}