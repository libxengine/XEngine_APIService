#include "../XEngine_Hdr.h"

bool HTTPTask_TaskPost_SLProxy(LPCXSTR lpszClientAddr, LPCXSTR lpszUriStr, XCHAR*** ppptszHDRList, int nHDRCount)
{
	//是不是代理转发
	bool bFound = false;
	for (int i = 0; i < nHDRCount; i++)
	{
		XCHAR tszKey[XPATH_MAX];
		XCHAR tszValue[XPATH_MAX];

		memset(tszKey, '\0', sizeof(tszKey));
		memset(tszValue, '\0', sizeof(tszValue));

		BaseLib_String_GetKeyValue((*ppptszHDRList)[i], ": ", tszKey, tszValue);
		if (0 == _tcsxnicmp(st_ServiceConfig.st_XShortLink.tszHostUrl, tszValue, _tcsxlen(st_ServiceConfig.st_XShortLink.tszHostUrl)))
		{
			bFound = true;
			break;
		}
	}
	if (!bFound)
	{
		return false;
	}
	int nSDLen = XPATH_4MAX;
	XCHAR tszSDBuffer[XPATH_4MAX] = {};
	XCHAR tszRVBuffer[XPATH_4MAX] = {};
	XENGINE_SHORTLINK st_ShortLink = {};
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};

	_xstprintf(st_ShortLink.tszMapUrl, _X("http://%s%s"), st_ServiceConfig.st_XShortLink.tszHostUrl, lpszUriStr);
	if (!ModuleDatabase_ShortLink_Query(&st_ShortLink))
	{
		return false;
	}
	st_HDRParam.nHttpCode = st_ServiceConfig.st_XShortLink.nHTTPCode; 
	st_HDRParam.bIsClose = true; 

	_xstprintf(tszRVBuffer, _X("Location: %s\r\n"), st_ShortLink.tszFullUrl);
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, NULL, 0, tszRVBuffer);
	NetCore_TCPXCore_SendEx(xhHTTPSocket, lpszClientAddr, tszSDBuffer, nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的短连接地址重定向成功,短连接:%s,长连接:%s"), lpszClientAddr, st_ShortLink.tszMapUrl, st_ShortLink.tszFullUrl);
	return true;
}
bool HTTPTask_TaskPost_ShortLink(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	XCHAR tszSDBuffer[4096];
	XENGINE_SHORTLINK st_ShortLink = {};

	if (!st_ServiceConfig.st_XSql.bEnable)
	{
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_DISABLE, _X("function is closed"));
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的短连接操作功能已经被服务器关闭,无法继续"), lpszClientAddr);
		return false;
	}
	ModuleProtocol_Parse_ShortLink(lpszMsgBuffer, nMsgLen, &st_ShortLink);
	//0生成,1还原,2删除
	if (0 == nType)
	{
		BaseLib_Time_TimeToStr(st_ShortLink.tszCreateTime);
		if (!HttpProtocol_ServerHelp_ShortLink(st_ShortLink.tszFullUrl, st_ShortLink.tszShotUrl, st_ShortLink.tszKeyUrl, st_ShortLink.nLength, st_ShortLink.tszCvtUrl))
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("request create short link is failure"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求生成短连接生成错误,生成的连接:%s,替换的连接:%s,错误码:%lX"), lpszClientAddr, st_ShortLink.tszFullUrl, st_ShortLink.tszCvtUrl, HttpProtocol_GetLastError());
			return false;
		}
		_xstprintf(st_ShortLink.tszMapUrl, _X("%s/%s"), st_ShortLink.tszShotUrl, st_ShortLink.tszKeyUrl);
		if (!ModuleDatabase_ShortLink_Insert(&st_ShortLink))
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("insert shortlink is failure"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求生成短连接插入数据库错误,生成的连接:%s,替换的连接:%s,错误码:%lX"), lpszClientAddr, st_ShortLink.tszFullUrl, st_ShortLink.tszCvtUrl, ModuleDB_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_ShortLink(tszSDBuffer, &nSDLen, &st_ShortLink);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求操作短连接插入成功,完整地址URL:%s,映射URL:%s"), lpszClientAddr, st_ShortLink.tszFullUrl, st_ShortLink.tszMapUrl);
	}
	else if (1 == nType)
	{
		if (!ModuleDatabase_ShortLink_Query(&st_ShortLink))
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("query shortlink is failure"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求获取短连接错误,连接:%s,错误码:%lX"), lpszClientAddr, st_ShortLink.tszMapUrl, ModuleDB_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_ShortLink(tszSDBuffer, &nSDLen, &st_ShortLink);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求操作短连接获取成功,完整地址URL:%s,映射URL:%s"), lpszClientAddr, st_ShortLink.tszFullUrl, st_ShortLink.tszMapUrl);
	}
	else if (2 == nType)
	{
		if (!ModuleDatabase_ShortLink_Delete(&st_ShortLink))
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("delete shortlink is failure"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求删除短连接错误,完整地址:%s,映射地址:%s,错误码:%lX"), lpszClientAddr, st_ShortLink.tszFullUrl, st_ShortLink.tszMapUrl, ModuleDB_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_ShortLink(tszSDBuffer, &nSDLen, &st_ShortLink);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求操作短连接删除成功,完整地址URL:%s,映射URL:%s"), lpszClientAddr, st_ShortLink.tszFullUrl, st_ShortLink.tszMapUrl);
	}
	else
	{
		int nListCount = 0;
		XENGINE_SHORTLINK** ppSt_SLinkInfo;
		ModuleDatabase_ShortLink_List(&ppSt_SLinkInfo, &nListCount);
		ModuleProtocol_Packet_ShortLinkList(tszSDBuffer, &nSDLen, &ppSt_SLinkInfo, nListCount);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		BaseLib_Memory_Free((XPPPMEM)&ppSt_SLinkInfo, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求操作短连接查询成功,查询个数:%d"), lpszClientAddr, nListCount);
	}
	return true;
}