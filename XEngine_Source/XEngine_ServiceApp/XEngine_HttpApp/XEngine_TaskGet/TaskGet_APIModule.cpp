#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_APIModule(LPCXSTR lpszClientAddr, LPCXSTR lpszQueryType, LPCXSTR lpszQueryStr, LPCXSTR lpszTPStr)
{
	int nMsgLen = 4096;
	XCHAR tszMsgBuffer[4096] = {};

	if (!st_ServiceConfig.st_XAPIModule.bEnable)
	{
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_DISABLE, _X("function is closed"));
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 功能已经被服务器关闭,无法继续"), lpszClientAddr, lpszQueryType, lpszQueryStr);
		return false;
	}

	LPCXSTR lpszQueryPhone = _X("phone");
	LPCXSTR lpszQueryIPAddr = _X("ip");
	LPCXSTR lpszQueryMacInfo = _X("mac");

	if (0 == _tcsxnicmp(lpszQueryPhone, lpszQueryType, _tcsxlen(lpszQueryPhone)))
	{
		XENGINE_PHONEINFO st_PhoneInfo = {};

		_tcsxcpy(st_PhoneInfo.tszPhoneNumber, lpszQueryStr);

		if (!APIModule_PhoneNumber_Query(&st_PhoneInfo))
		{
			ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_NOTFOUND, _X("not found"));
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 失败,错误码:%lX"), lpszClientAddr, lpszQueryType, lpszQueryStr, APIPhone_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_PhoneInfo(tszMsgBuffer, &nMsgLen, &st_PhoneInfo);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 成功"), lpszClientAddr, lpszQueryType, lpszQueryStr);
	}
	else if (0 == _tcsxnicmp(lpszQueryIPAddr, lpszQueryType, _tcsxlen(lpszQueryIPAddr)))
	{
		XENGINE_IPADDRINFO st_IPAddr = {};

		_tcsxcpy(st_IPAddr.tszIPAddr, lpszQueryStr);

		if (!APIModule_IPAddr_Query(&st_IPAddr, lpszTPStr))
		{
			ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_NOTFOUND, _X("not found"));
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 失败,错误码:%lX"), lpszClientAddr, lpszQueryType, lpszQueryStr, APIPhone_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_IPAddr(tszMsgBuffer, &nMsgLen, &st_IPAddr);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 成功"), lpszClientAddr, lpszQueryType, lpszQueryStr);
	}
	else if (0 == _tcsxnicmp(lpszQueryMacInfo, lpszQueryType, _tcsxlen(lpszQueryMacInfo)))
	{
		XENGINE_MACADDRINFO st_MACInfo = {};
		_tcsxcpy(st_MACInfo.tszMACPrefix, lpszQueryStr);

		if (!APIModule_MACInfo_Query(&st_MACInfo))
		{
			ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_NOTFOUND, _X("not found"));
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 失败,错误码:%lX"), lpszClientAddr, lpszQueryType, lpszQueryStr, APIPhone_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_MacInfo(tszMsgBuffer, &nMsgLen, &st_MACInfo);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 成功"), lpszClientAddr, lpszQueryType, lpszQueryStr);
	}
	else
	{
		ModuleProtocol_Packet_Common(tszMsgBuffer, &nMsgLen, ERROR_XENGINE_PROTOCL_HTTP_NOTSUPPORT, _X("not support"));
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 失败,不支持的查询类型"), lpszClientAddr, lpszQueryType, lpszQueryStr);
	}
	return true;
}