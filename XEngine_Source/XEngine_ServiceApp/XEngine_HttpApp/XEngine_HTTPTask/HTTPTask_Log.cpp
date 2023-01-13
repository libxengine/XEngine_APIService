#include "../XEngine_Hdr.h"

BOOL XEngine_HTTPTask_LogInfo(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, int nType)
{
	int nSDLen = 0;
	int nRVLen = 0;
	TCHAR tszSDBuffer[4096];
	TCHAR tszRVBuffer[4096];
	XENGINE_XLOGINFO st_XLogInfo;
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));
	memset(tszRVBuffer, '\0', sizeof(tszRVBuffer));
	memset(&st_XLogInfo, '\0', sizeof(XENGINE_XLOGINFO));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	ModuleProtocol_Parse_XLog(lpszMsgBuffer, nMsgLen, &st_XLogInfo);

	if (0 == nType)
	{
		ModuleDatabase_XLog_Create(st_XLogInfo.tszTableName);
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求日志表创建成功,创建的表:%s,"), lpszClientAddr, st_XLogInfo.tszTableName);
	}
	else if (1 == nType)
	{
		ModuleDatabase_XLog_Insert(&st_XLogInfo);
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求日志插入成功,插入的表:%s,日志大小:%d"), lpszClientAddr, st_XLogInfo.tszTableName, st_XLogInfo.nLogSize);
	}
	else if (2 == nType)
	{
		int nListCount = 0;
		XENGINE_XLOGINFO** ppSt_XLogInfo;
		ModuleDatabase_XLog_Query(&ppSt_XLogInfo, &nListCount, st_XLogInfo.tszTableName, st_XLogInfo.tszTimeStart, st_XLogInfo.tszTimeEnd);
		ModuleProtocol_Packet_Log(tszRVBuffer, &nRVLen, &ppSt_XLogInfo, nListCount);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求日志查询成功,查询的表:%s,查询日期:%s - %s"), lpszClientAddr, st_XLogInfo.tszTableName, st_XLogInfo.tszTimeStart, st_XLogInfo.tszTimeEnd);
	}
	else
	{
		ModuleDatabase_XLog_Delete(st_XLogInfo.tszTableName);
		ModuleProtocol_Packet_Common(tszRVBuffer, &nRVLen);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,请求日志删除成功,删除的表:%s"), lpszClientAddr, st_XLogInfo.tszTableName);
	}
	return TRUE;
}