#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_Locker(LPCXSTR lpszClientAddr, __int64x xhToken, ENUM_XENGINE_APISERVICE_LOCKER_TYPE enLockType)
{
	int nSDLen = 4096;
	XCHAR tszSDBuffer[4096] = {};

	if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_CREATE == enLockType)
	{
		//创建
		XNETHANDLE xhLocker = 0;
		ModuleHelp_Locker_Create(&xhLocker);
		ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhLocker);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求创建锁成功,锁句柄:%lld"), lpszClientAddr, xhLocker);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_OPEN == enLockType)
	{
		//打开
		if (!ModuleHelp_Locker_OPen(xhToken))
		{
			XLONG dwRet = ModuleHelp_GetLastError();
			ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken, dwRet, "request is failed");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求打开锁失败,锁句柄:%lld,错误码:%lX"), lpszClientAddr, xhToken, dwRet);
			return false;
		}
		ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求打开锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_CLOSE == enLockType)
	{
		ModuleHelp_Locker_Close(xhToken);
		ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求关闭锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_READ == enLockType)
	{
		if (!ModuleHelp_Locker_ReadLock(xhToken))
		{
			XLONG dwRet = ModuleHelp_GetLastError();
			ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken, dwRet, "request is failed");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求读加锁失败,锁句柄:%lld,错误码:%lX"), lpszClientAddr, xhToken, dwRet);
			return false;
		}
		ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求读加锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_UNREAD == enLockType)
	{
		if (!ModuleHelp_Locker_ReadUNLock(xhToken))
		{
			XLONG dwRet = ModuleHelp_GetLastError();
			ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken, dwRet, "request is failed");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求读解锁失败,锁句柄:%lld,错误码:%lX"), lpszClientAddr, xhToken, dwRet);
			return false;
		}
		ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求读解锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_WRITE == enLockType)
	{
		if (!ModuleHelp_Locker_WriteLock(xhToken))
		{
			XLONG dwRet = ModuleHelp_GetLastError();
			ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken, dwRet, "request is failed");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求写加锁失败,锁句柄:%lld,错误码:%lX"), lpszClientAddr, xhToken, dwRet);
			return false;
		}
		ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求写加锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else if (ENUM_XENGINE_APISERVICE_LOCKER_TYPE_UNWRITE == enLockType)
	{
		if (!ModuleHelp_Locker_WriteUNLock(xhToken))
		{
			XLONG dwRet = ModuleHelp_GetLastError();
			ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken, dwRet, "request is failed");
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求写解锁失败,锁句柄:%lld,错误码:%lX"), lpszClientAddr, xhToken, dwRet);
			return false;
		}
		ModuleProtocol_Packet_Locker(tszSDBuffer, &nSDLen, xhToken);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求写解锁成功,锁句柄:%lld"), lpszClientAddr, xhToken);
	}
	else
	{
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_NOTSUPPORT, _X("function api not support"));
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("客户端:%s,请求了一条未知的子协议：%d"), lpszClientAddr, enLockType);
	}
	return true;
}