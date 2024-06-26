﻿#include "../XEngine_Hdr.h"

bool HTTPTask_TastPost_LogInfo(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	int nRVLen = 0;
	XCHAR tszSDBuffer[4096];
	XCHAR tszRVBuffer[4096];
	XENGINE_XLOGINFO st_XLogInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));
	memset(tszRVBuffer, '\0', sizeof(tszRVBuffer));
	memset(&st_XLogInfo, '\0', sizeof(XENGINE_XLOGINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭
	ModuleProtocol_Parse_XLog(lpszMsgBuffer, nMsgLen, &st_XLogInfo);

	if (!st_ServiceConfig.st_XSql.bEnable)
	{
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen, 501, _X("function is closed"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的日志操作功能已经被服务器关闭,无法继续"), lpszClientAddr);
		return false;
	}
	if (0 == nType)
	{
		ModuleDatabase_XLog_Create(st_XLogInfo.tszTableName);
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求日志表创建成功,创建的表:%s,"), lpszClientAddr, st_XLogInfo.tszTableName);
	}
	else if (1 == nType)
	{
		ModuleDatabase_XLog_Insert(&st_XLogInfo);
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求日志插入成功,插入的表:%s,日志大小:%d"), lpszClientAddr, st_XLogInfo.tszTableName, st_XLogInfo.nLogSize);
	}
	else if (2 == nType)
	{
		int nListCount = 0;
		XENGINE_XLOGINFO** ppSt_XLogInfo;
		ModuleDatabase_XLog_Query(&ppSt_XLogInfo, &nListCount, st_XLogInfo.tszTableName, st_XLogInfo.tszTimeStart, st_XLogInfo.tszTimeEnd);
		ModuleProtocol_Packet_Log(tszRVBuffer, &nRVLen, &ppSt_XLogInfo, nListCount);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求日志查询成功,查询的表:%s,查询日期:%s - %s,查询条数:%d"), lpszClientAddr, st_XLogInfo.tszTableName, st_XLogInfo.tszTimeStart, st_XLogInfo.tszTimeEnd, nListCount);
	}
	else if (3 == nType)
	{
		int nListCount = 0;
		XCHAR** pptszList;
		ModuleDatabase_XLog_Show(&pptszList, &nListCount);
		ModuleProtocol_Packet_LogShow(tszRVBuffer, &nRVLen, &pptszList, nListCount);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求日志数据库表列举成功,查询到的个数:%d"), lpszClientAddr, nListCount);
	}
	else
	{
		ModuleDatabase_XLog_Delete(st_XLogInfo.tszTableName);
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求日志删除成功,删除的表:%s"), lpszClientAddr, st_XLogInfo.tszTableName);
	}
	return true;
}