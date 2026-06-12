#include "../XEngine_Hdr.h"

bool HTTPTask_TastPost_WordFilter(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 4096;
	XCHAR tszSDBuffer[4096] = {};
	XENGINE_WORDFILTER st_WordFilter = {};

	ModuleProtocol_Parse_WordFilter(lpszMsgBuffer, nMsgLen, &st_WordFilter);

	if (!st_ServiceConfig.st_XSql.bEnable)
	{
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_DISABLE, _X("function is closed"));
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的敏感词操作功能已经被服务器关闭,无法继续"), lpszClientAddr);
		return false;
	}
	if (0 == nType)
	{
		ModuleDatabase_WordFilter_Insert(&st_WordFilter);
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求插入一条敏感词成功,敏感词:%s"), lpszClientAddr, st_WordFilter.tszWordsFrom);
	}
	else if (1 == nType)
	{
		ModuleDatabase_WordFilter_Delete(&st_WordFilter);
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求删除一条敏感词成功,敏感词:%s"), lpszClientAddr, st_WordFilter.tszWordsFrom);
	}
	else if (2 == nType)
	{
		if (!ModuleDatabase_WordFilter_Query(&st_WordFilter))
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_NOTFOUND, "not found");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求查询一条敏感词:%s 失败,错误码:%lX"), lpszClientAddr, st_WordFilter.tszWordsFrom, ModuleDB_GetLastError());
		}
		ModuleProtocol_Packet_WordFilter(tszSDBuffer, &nSDLen, &st_WordFilter);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求查询一条敏感词成功,敏感词:%s,过滤词:%s,级别:%d"), lpszClientAddr, st_WordFilter.tszWordsFrom, st_WordFilter.tszWordsTo, st_WordFilter.nLevel);
	}
	else
	{
		int nListCount = 0;
		XENGINE_WORDFILTER** ppSt_WordFilter;
		ModuleDatabase_WordFilter_List(&ppSt_WordFilter, &nListCount);
		ModuleProtocol_Packet_WordFilterList(tszSDBuffer, &nSDLen, &ppSt_WordFilter, nListCount);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		BaseLib_Memory_Free((XPPPMEM)&ppSt_WordFilter, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求枚举敏感词列表成功,敏感词个数:%d"), lpszClientAddr, nListCount);
	}
	return true;
}