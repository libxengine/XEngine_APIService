#include "../XEngine_Hdr.h"

bool HTTPTask_TastPost_LogInfo(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	XCHAR tszSDBuffer[4096] = {};
	XENGINE_XLOGINFO st_XLogInfo = {};

	ModuleProtocol_Parse_XLog(lpszMsgBuffer, nMsgLen, &st_XLogInfo);

	if (!st_ServiceConfig.st_XSql.bEnable)
	{
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_DISABLE, _X("function is closed"));
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的日志操作功能已经被服务器关闭,无法继续"), lpszClientAddr);
		return false;
	}
	if (0 == nType)
	{
		ModuleDatabase_XLog_Create(st_XLogInfo.tszTableName);
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求日志表创建成功,创建的表:%s,"), lpszClientAddr, st_XLogInfo.tszTableName);
	}
	else if (1 == nType)
	{
		ModuleDatabase_XLog_Insert(&st_XLogInfo);
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求日志插入成功,插入的表:%s,日志大小:%d"), lpszClientAddr, st_XLogInfo.tszTableName, st_XLogInfo.nLogSize);
	}
	else if (2 == nType)
	{
		int nListCount = 0;
		XENGINE_XLOGINFO** ppSt_XLogInfo;
		ModuleDatabase_XLog_Query(&ppSt_XLogInfo, &nListCount, st_XLogInfo.tszTableName, st_XLogInfo.tszTimeStart, st_XLogInfo.tszTimeEnd);
		ModuleProtocol_Packet_Log(tszSDBuffer, &nSDLen, &ppSt_XLogInfo, nListCount);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求日志查询成功,查询的表:%s,查询日期:%s - %s,查询条数:%d"), lpszClientAddr, st_XLogInfo.tszTableName, st_XLogInfo.tszTimeStart, st_XLogInfo.tszTimeEnd, nListCount);
	}
	else if (3 == nType)
	{
		int nListCount = 0;
		XCHAR** pptszList;
		ModuleDatabase_XLog_Show(&pptszList, &nListCount);
		ModuleProtocol_Packet_LogShow(tszSDBuffer, &nSDLen, &pptszList, nListCount);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求日志数据库表列举成功,查询到的个数:%d"), lpszClientAddr, nListCount);
	}
	else
	{
		ModuleDatabase_XLog_Delete(st_XLogInfo.tszTableName);
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求日志删除成功,删除的表:%s"), lpszClientAddr, st_XLogInfo.tszTableName);
	}
	return true;
}