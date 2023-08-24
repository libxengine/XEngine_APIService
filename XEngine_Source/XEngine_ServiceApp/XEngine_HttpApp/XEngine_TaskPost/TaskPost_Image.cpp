﻿#include "../XEngine_Hdr.h"

bool HTTPTask_TaskPost_Image(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR*** ppptszList, int nListCount)
{
	int nSDLen = 0;
	int nRVLen = 0;
	XCHAR tszHTTPKey[64];
	XCHAR tszHTTPVlu[64];
	XCHAR *ptszSDBuffer = (XCHAR *)malloc(XENGIEN_APISERVICE_BUFFER_SIZE);
	XCHAR *ptszRVBuffer = (XCHAR *)malloc(XENGIEN_APISERVICE_BUFFER_SIZE);
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszHTTPKey, '\0', sizeof(tszHTTPKey));
	memset(tszHTTPVlu, '\0', sizeof(tszHTTPVlu));
	memset(ptszSDBuffer, '\0', XENGIEN_APISERVICE_BUFFER_SIZE);
	memset(ptszRVBuffer, '\0', XENGIEN_APISERVICE_BUFFER_SIZE);
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	BaseLib_OperatorString_GetKeyValue((*ppptszList)[1], "=", tszHTTPKey, tszHTTPVlu);
	int nOPCode = _ttxoi(tszHTTPVlu);
	//0获取,1设置
	if (0 == nOPCode)
	{
		XENGINE_IMGBASEATTR st_BaseInfo;
		XENGINE_IMGEXTATTR st_ExtAttr;

		ModuleHelp_ImageGet_Attr(lpszMsgBuffer, nMsgLen, &st_BaseInfo, &st_ExtAttr);
		ModuleProtocol_Packet_ImageAttr(ptszRVBuffer, &nRVLen, &st_BaseInfo, &st_ExtAttr);
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam, ptszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求获取图像信息成功,宽:%d,高:%d,通道:%d"), lpszClientAddr, st_BaseInfo.nWidth, st_BaseInfo.nHeigth, st_BaseInfo.nChannel);
	}
	else
	{
		if (4 < nListCount)
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求设置图像数据失败,因为附加参数不正确,参数个数:%d"), lpszClientAddr, nListCount);
			return false;
		}
		XCHAR tszFileExt[MAX_PATH];
		memset(tszFileExt, '\0', sizeof(tszFileExt));

		memset(tszHTTPVlu, '\0', sizeof(tszHTTPVlu));

		BaseLib_OperatorString_GetKeyValue((*ppptszList)[2], "=", tszHTTPKey, tszHTTPVlu);
		_xstprintf(tszFileExt, _X(".%s"), tszHTTPVlu);

		BaseLib_OperatorString_GetKeyValue((*ppptszList)[3], "=", tszHTTPKey, tszHTTPVlu);
		int nWidth = _ttxoi(tszHTTPVlu);
		if (1 == nOPCode)
		{
			BaseLib_OperatorString_GetKeyValue((*ppptszList)[4], "=", tszHTTPKey, tszHTTPVlu);
			int nHeight = _ttxoi(tszHTTPVlu);

			ModuleHelp_ImageSet_Resolution(lpszMsgBuffer, nMsgLen, tszFileExt, ptszRVBuffer, &nRVLen, nWidth, nHeight);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求设置图像分辨率成功,宽:%d,高:%d"), lpszClientAddr, nWidth, nHeight);
		}
		else if (2 == nOPCode)
		{
			ModuleHelp_ImageSet_ColorCvt(lpszMsgBuffer, nMsgLen, tszFileExt, ptszRVBuffer, &nRVLen, (ENUM_XENGINE_IMAGE_COLOR_INFO)nWidth);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求设置图像颜色空间转换成功,转换的值:%d"), lpszClientAddr, nWidth);
		}
		else if (3 == nOPCode)
		{
			ModuleHelp_ImageSet_Flip(lpszMsgBuffer, nMsgLen, tszFileExt, ptszRVBuffer, &nRVLen, nWidth);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求设置图像翻转成功,翻转的值:%d"), lpszClientAddr, nWidth);
		}
		else if (4 == nOPCode)
		{
			ModuleHelp_ImageSet_Ligth(lpszMsgBuffer, nMsgLen, tszFileExt, ptszRVBuffer, &nRVLen, nWidth);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求设置图像亮度,亮度的值:%d"), lpszClientAddr, nWidth);
		}
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, ptszSDBuffer, &nSDLen, &st_HDRParam, ptszRVBuffer, nRVLen);
		XEngine_Network_Send(lpszClientAddr, ptszSDBuffer, nSDLen);
	}
	free(ptszRVBuffer);
	free(ptszSDBuffer);
	ptszRVBuffer = NULL;
	ptszSDBuffer = NULL;
	return true;
}