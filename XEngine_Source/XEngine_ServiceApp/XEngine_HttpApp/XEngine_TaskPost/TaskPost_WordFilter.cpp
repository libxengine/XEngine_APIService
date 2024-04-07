#include "../XEngine_Hdr.h"

bool HTTPTask_TastPost_WordFilter(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	int nRVLen = 0;
	XCHAR tszSDBuffer[4096];
	XCHAR tszRVBuffer[4096];
	XENGINE_WORDFILTER st_WordFilter;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));
	memset(tszRVBuffer, '\0', sizeof(tszRVBuffer));
	memset(&st_WordFilter, '\0', sizeof(XENGINE_WORDFILTER));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭
	ModuleProtocol_Parse_WordFilter(lpszMsgBuffer, nMsgLen, &st_WordFilter);

	if (!st_ServiceConfig.st_XSql.bEnable)
	{
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen, 501, _X("function is closed"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的敏感词操作功能已经被服务器关闭,无法继续"), lpszClientAddr);
		return false;
	}
	if (0 == nType)
	{
		ModuleDatabase_WordFilter_Insert(&st_WordFilter);
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求插入一条敏感词成功,敏感词:%s,"), lpszClientAddr, st_WordFilter.tszWordsFrom);
	}
	else if (1 == nType)
	{
		ModuleDatabase_WordFilter_Delete(&st_WordFilter);
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求删除一条敏感词成功,敏感词:%s"), lpszClientAddr, st_WordFilter.tszWordsFrom);
	}
	else
	{
		if (!ModuleDatabase_WordFilter_Query(&st_WordFilter))
		{
			ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen, 404, "not found");
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求查询一条敏感词:%s 失败,错误码:%lX"), lpszClientAddr, st_WordFilter.tszWordsFrom, ModuleDB_GetLastError());
		}
		ModuleProtocol_Packet_WordFilter(tszRVBuffer, &nRVLen, &st_WordFilter);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求查询一条敏感词成功,敏感词:%s,过滤词:%s,级别:%d"), lpszClientAddr, st_WordFilter.tszWordsFrom, st_WordFilter.tszWordsTo, st_WordFilter.nLevel);
	}
	return true;
}