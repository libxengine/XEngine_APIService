#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"jsoncpp")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_NetHelp/NetHelp_APIHelp")
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
#include <XEngine_Include/XEngine_NetHelp/APIHelp_Define.h>
#include <XEngine_Include/XEngine_NetHelp/APIHelp_Error.h>

//需要优先配置XEngine
//WINDOWS支持VS2022 x64 debug 编译调试
//linux::g++ -std=c++17 -Wall -g APPClient_ZIPCodeExample.cpp -o APPClient_ZIPCodeExample.exe -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_NetHelp -lXEngine_BaseLib -lNetHelp_APIHelp
//macos::g++ -std=c++17 -Wall -g APPClient_ZIPCodeExample.cpp -o APPClient_ZIPCodeExample.exe -lXEngine_BaseLib -lNetHelp_APIHelp

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	int nLen = 0;
	int nCode = 0;
	TCHAR tszMsgBuffer[1024];
	LPCTSTR lpszCreateUrl = _T("http://127.0.0.1:5501/api?function=zipcode&params1=0");

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));

	Json::Value st_JsonRoot;
	st_JsonRoot["nZipCode"] = 100010;

	TCHAR* ptszMsgBuffer = NULL;
	if (!APIHelp_HttpRequest_Custom(_T("POST"), lpszCreateUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
#ifdef _MSC_BUILD
	BaseLib_OperatorCharset_UTFToAnsi(ptszMsgBuffer, tszMsgBuffer, &nLen);
	printf("接受到数据,大小:%d,内容:%s\n", nLen, tszMsgBuffer);
#else
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
#endif
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}