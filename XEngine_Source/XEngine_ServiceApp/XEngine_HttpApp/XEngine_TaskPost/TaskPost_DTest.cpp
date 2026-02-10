#include "../XEngine_Hdr.h"

bool HTTPTask_TastPost_DTest(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	XCHAR tszSDBuffer[4096] = {};

	//0发什么返回什么,1 仅仅返回确认
	if (0 == nType)
	{
		XEngine_Network_Send(lpszClientAddr, lpszMsgBuffer, nSDLen);
	}
	else
	{
		XEngine_Network_Send(lpszClientAddr, NULL, 0);
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求数据用例测试成功,请求的大小:%d,请求的类型:%d,发送的内容:%s"), lpszClientAddr, nMsgLen, nType, lpszMsgBuffer);
	return true;
}