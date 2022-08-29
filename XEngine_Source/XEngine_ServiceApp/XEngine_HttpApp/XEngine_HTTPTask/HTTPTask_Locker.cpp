#include "../XEngine_Hdr.h"

BOOL XEngine_HTTPTask_Locker(LPCTSTR lpszClientAddr, __int64x xhToken, ENUM_XENGINE_APISERVICE_LOCKER_TYPE enLockType)
{
	int nSDLen = 4096;
	int nRVLen = 4096;
	TCHAR tszSDBuffer[4096];
	TCHAR tszRVBuffer[4096];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));
	memset(tszRVBuffer, '\0', sizeof(tszRVBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_CREATE == enLockType)
	{
		//创建
		XNETHANDLE xhToken = 0;
		ModuleHelp_Locker_Create(&xhToken);
		ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求创建锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_OPEN == enLockType)
	{
		//打开
		if (!ModuleHelp_Locker_OPen(xhToken))
		{
			DWORD dwRet = ModuleHelp_GetLastError();
			ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken, dwRet, "request is failed");
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求打开锁失败,锁句柄:%lld,错误码:%lX"), lpszClientAddr, xhToken, dwRet);
			return FALSE;
		}
		ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求打开锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_CLOSE == enLockType)
	{
		ModuleHelp_Locker_Close(xhToken);
		ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求关闭锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_READ == enLockType)
	{
		if (!ModuleHelp_Locker_ReadLock(xhToken))
		{
			DWORD dwRet = ModuleHelp_GetLastError();
			ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken, dwRet, "request is failed");
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求读加锁失败,锁句柄:%lld,错误码:%lX"), lpszClientAddr, xhToken, dwRet);
			return FALSE;
		}
		ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求读加锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_UNREAD == enLockType)
	{
		if (!ModuleHelp_Locker_ReadUNLock(xhToken))
		{
			DWORD dwRet = ModuleHelp_GetLastError();
			ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken, dwRet, "request is failed");
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求读解锁失败,锁句柄:%lld,错误码:%lX"), lpszClientAddr, xhToken, dwRet);
			return FALSE;
		}
		ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求读解锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_WRITE == enLockType)
	{
		if (!ModuleHelp_Locker_WriteLock(xhToken))
		{
			DWORD dwRet = ModuleHelp_GetLastError();
			ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken, dwRet, "request is failed");
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求写加锁失败,锁句柄:%lld,错误码:%lX"), lpszClientAddr, xhToken, dwRet);
			return FALSE;
		}
		ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求写加锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_UNWRITE == enLockType)
	{
		if (!ModuleHelp_Locker_WriteUNLock(xhToken))
		{
			DWORD dwRet = ModuleHelp_GetLastError();
			ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken, dwRet, "request is failed");
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求写解锁失败,锁句柄:%lld,错误码:%lX"), lpszClientAddr, xhToken, dwRet);
			return FALSE;
		}
		ModuleProtocol_Packet_Locker(tszRVBuffer, &nRVLen, xhToken);
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, tszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求写解锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else
	{
		st_HDRParam.nHttpCode = 404;
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("客户端:%s,请求了一条未知的子协议：%d"), lpszClientAddr, enLockType);
	}
	return TRUE;
}