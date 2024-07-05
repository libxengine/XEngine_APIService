#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_APIModule(LPCXSTR lpszClientAddr, LPCXSTR lpszQueryType, LPCXSTR lpszQueryStr)
{
	int nMsgLen = 4096;
	int nPktLen = 4096;
	XCHAR tszMsgBuffer[4096] = {};
	XCHAR tszPktBuffer[4096] = {};
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};    //发送给客户端的参数

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	if (!st_ServiceConfig.st_XAPIModule.bEnable)
	{
		ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, 501, _X("function is closed"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
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
			ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, 404, _X("not found"));
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 失败,错误码:%lX"), lpszClientAddr, lpszQueryType, lpszQueryStr, APIPhone_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_PhoneInfo(tszPktBuffer, &nPktLen, &st_PhoneInfo);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 成功"), lpszClientAddr, lpszQueryType, lpszQueryStr);
	}
	else if (0 == _tcsxnicmp(lpszQueryIPAddr, lpszQueryType, _tcsxlen(lpszQueryIPAddr)))
	{
		XENGINE_IPADDRINFO st_IPAddr = {};

		_tcsxcpy(st_IPAddr.tszIPAddr, lpszQueryStr);

		if (!APIModule_IPAddr_Query(&st_IPAddr))
		{
			ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, 404, _X("not found"));
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 失败,错误码:%lX"), lpszClientAddr, lpszQueryType, lpszQueryStr, APIPhone_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_IPAddr(tszPktBuffer, &nPktLen, &st_IPAddr);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 成功"), lpszClientAddr, lpszQueryType, lpszQueryStr);
	}
	else if (0 == _tcsxnicmp(lpszQueryMacInfo, lpszQueryType, _tcsxlen(lpszQueryMacInfo)))
	{
		XENGINE_MACADDRINFO st_MACInfo = {};
		_tcsxcpy(st_MACInfo.tszMACPrefix, lpszQueryStr);

		if (!APIModule_MACInfo_Query(&st_MACInfo))
		{
			ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, 404, _X("not found"));
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 失败,错误码:%lX"), lpszClientAddr, lpszQueryType, lpszQueryStr, APIPhone_GetLastError());
			return false;
		}
		ModuleProtocol_Packet_MacInfo(tszPktBuffer, &nPktLen, &st_MACInfo);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 成功"), lpszClientAddr, lpszQueryType, lpszQueryStr);
	}
	else
	{
		ModuleProtocol_Packet_Common(tszPktBuffer, &nPktLen, 400, _X("not support"));
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam, tszPktBuffer, nPktLen);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的数据:%s 查询服务:%s 失败,不支持的查询类型"), lpszClientAddr, lpszQueryType, lpszQueryStr);
	}
	return true;
}