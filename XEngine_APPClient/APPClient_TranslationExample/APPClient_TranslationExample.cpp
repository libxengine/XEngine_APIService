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
//linux::g++ -std=c++17 -Wall -g APPClient_TranslationExample.cpp -o APPClient_TranslationExample.exe -L /usr/local/lib/XEngine_Release/XEngine_BaseLib -L /usr/local/lib/XEngine_Release/XEngine_NetHelp -lXEngine_BaseLib -lNetHelp_APIHelp
//macos::g++ -std=c++17 -Wall -g APPClient_TranslationExample.cpp -o APPClient_TranslationExample.exe -lXEngine_BaseLib -lNetHelp_APIHelp

int main()
{
#ifdef _MSC_BUILD
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
	int nLen = 0;
	TCHAR* ptszMsgBuffer = NULL;
	LPCTSTR lpszUrl = _T("http://127.0.0.1:5501/api?function=translation&params1=中国&params2=0&param3=0");

	if (!APIHelp_HttpRequest_Get(lpszUrl, &ptszMsgBuffer, &nLen))
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