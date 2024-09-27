#ifdef _MSC_BUILD
#include <Windows.h>
#include <tchar.h>
#pragma comment(lib,"Ws2_32")
#pragma comment(lib,"jsoncpp")
#pragma comment(lib,"XEngine_BaseLib/XEngine_BaseLib")
#pragma comment(lib,"XEngine_Client/XClient_APIHelp")
#pragma comment(lib,"XEngine_SystemSdk/XEngine_SystemApi")
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
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Define.h>
#include <XEngine_Include/XEngine_SystemSdk/SystemApi_Error.h>

//需要优先配置XEngine
//WINDOWS支持VS2022 x64 debug 编译调试
//g++ -std=c++17 -Wall -g APPClient_MachineExample.cpp -o APPClient_MachineExample.exe -I ../../XEngine_Source/XEngine_Depend/XEngine_Module/jsoncpp -L ../../XEngine_Release -lXEngine_BaseLib -lXClient_APIHelp -lXEngine_SystemApi -ljsoncpp -Wl,-rpath=../../XEngine_Release


int test_insert()
{
	int nLen = 0;
	int nCode = 0;
	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=machine&params1=0");

	XCHAR tszOSName[128] = {};
	XCHAR tszOSVersion[128] = {};
	XCHAR tszOSBuild[128] = {};
	XCHAR tszComputerName[128] = {};
	XLONG nOSArch = 0;
	SYSTEMAPI_SERIAL_INFOMATION st_SDKSerial = {};
	SystemApi_System_GetSystemVer(tszOSName, tszOSVersion, tszOSBuild, &nOSArch);
	SystemApi_System_GetSysName(NULL, tszComputerName);
	SystemApi_HardWare_GetSerial(&st_SDKSerial);

	Json::Value st_JsonRoot;
	Json::StreamWriterBuilder st_JsonBuilder;
	st_JsonRoot["tszServiceName"] = "XEngine_TestApp";
	st_JsonRoot["tszMachineName"] = tszOSName;
	st_JsonRoot["tszMachineUser"] = "user";
	st_JsonRoot["tszMachineCode"] = st_SDKSerial.tszSystemSerial;
	st_JsonRoot["tszMachineSystem"] = tszComputerName;

	st_JsonBuilder["emitUTF8"] = true;

	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), &nCode, &ptszMsgBuffer, &nLen))
	{
		printf("发送投递失败！\n");
		return 0;
	}
	printf("接受到数据,大小:%d,内容:%s\n", nLen, ptszMsgBuffer);
	BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBuffer);

	return 0;
}
int test_list()
{
	int nLen = 0;
	int nCode = 0;
	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=machine&params1=3");

	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, NULL, &nCode, &ptszMsgBuffer, &nLen))
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
	LPCXSTR lpszAPIUrl = _X("http://127.0.0.1:5501/api?function=machine&params1=1");

	XCHAR tszComputerName[128] = {};
	SystemApi_System_GetSysName(NULL, tszComputerName);

	Json::Value st_JsonRoot;
	st_JsonRoot["tszServiceName"] = "XEngine_TestApp";
	st_JsonRoot["tszMachineSystem"] = tszComputerName;

	XCHAR* ptszMsgBuffer = NULL;
	if (!APIClient_Http_Request(_X("POST"), lpszAPIUrl, st_JsonRoot.toStyledString().c_str(), &nCode, &ptszMsgBuffer, &nLen))
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
	test_insert();
	test_insert();
	test_list();
	test_delete();

#ifdef _MSC_BUILD
	WSACleanup();
#endif
	return 0;
}