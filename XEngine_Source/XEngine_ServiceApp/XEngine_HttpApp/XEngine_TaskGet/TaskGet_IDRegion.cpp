#include "../XEngine_Hdr.h"

bool HTTPTask_TaskGet_IDRegion(LPCXSTR lpszClientAddr, int nType, LPCXSTR lpszProvincerStr, LPCXSTR lpszCityStr, LPCXSTR lpszCountyStr)
{
	int nMsgLen = 4096;
	XCHAR tszMsgBuffer[4096] = {};
	
	XENGINE_IDREGION st_IDRegion = {};
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};    //发送给客户端的参数

	if (0 == nType)
	{
		XENGINE_IDCARDINFO st_IDInfo = {};
		_stxscanf(lpszProvincerStr, _X("%2hd%2hd%2hd"), &st_IDInfo.nIDProvince, &st_IDInfo.nIDCity, &st_IDInfo.nIDCounty);
		ModuleDatabase_IDCard_QueryRegion(&st_IDRegion, &st_IDInfo);
		ModuleProtocol_Packet_IDRegion(tszMsgBuffer, &nMsgLen, &st_IDRegion, _ttxoi(lpszProvincerStr));
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的行政区域ID转换地址成功,ID:%s,转换内容:%s-%s-%s"), lpszClientAddr, lpszProvincerStr, st_IDRegion.tszProvincer, st_IDRegion.tszCity, st_IDRegion.tszCounty);
	}
	else
	{
		int nIDRegion = 0;
		_tcsxcpy(st_IDRegion.tszProvincer, lpszProvincerStr);
		if (NULL != lpszCityStr)
		{
			_tcsxcpy(st_IDRegion.tszCity, lpszCityStr);
		}
		if (NULL != lpszCountyStr)
		{
			_tcsxcpy(st_IDRegion.tszCounty, lpszCountyStr);
		}
		ModuleDatabase_IDCard_QueryByAddr(&st_IDRegion, &nIDRegion);
		ModuleProtocol_Packet_IDRegion(tszMsgBuffer, &nMsgLen, &st_IDRegion, nIDRegion);
#ifdef _MSC_BUILD
		XCHAR tszUTFBuffer[1024] = {};
		int nULen = _tcsxlen(tszMsgBuffer);
		BaseLib_Charset_AnsiToUTF(tszMsgBuffer, tszUTFBuffer, &nULen);
		XEngine_Network_Send(lpszClientAddr, tszUTFBuffer, nULen);
#else
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
#endif 
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求的行政区域地址转ID成功,地址:%s-%s-%s,ID:%d"), lpszClientAddr, st_IDRegion.tszProvincer, st_IDRegion.tszCity, st_IDRegion.tszCounty, nIDRegion);
	}
	return true;
}