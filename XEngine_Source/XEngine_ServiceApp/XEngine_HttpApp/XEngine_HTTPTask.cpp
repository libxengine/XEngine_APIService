#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/01/20  14:44:17
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp\XEngine_HTTPTask.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp
//    File Base:   XEngine_HTTPTask
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     HTTP任务处理代码
//    History:
*********************************************************************/
XHTHREAD CALLBACK HTTPTask_TastPost_Thread(XPVOID lParam)
{
	//任务池是编号1开始的.
	int nThreadPos = *(int*)lParam;
	nThreadPos++;

	while (bIsRun)
	{
		//等待编号1的任务池触发一个组完包的事件
		if (!HttpProtocol_Server_EventWaitEx(xhHTTPPacket, nThreadPos))
		{
			continue;
		}
		int nListCount = 0;
		RFCCOMPONENTS_HTTP_PKTCLIENT** ppSst_ListAddr;
		//获得编号1的所有待处理任务的客户端列表(也就是客户端发送过来的数据已经组好了一个包,需要我们处理)
		HttpProtocol_Server_GetPoolEx(xhHTTPPacket, nThreadPos, &ppSst_ListAddr, &nListCount);
		//先循环客户端
		for (int i = 0; i < nListCount; i++)
		{
			//再循环客户端拥有的任务个数
			for (int j = 0; j < ppSst_ListAddr[i]->nPktCount; j++)
			{
				int nMsgLen = 0;                                    //客户端发送的数据大小,不包括头
				XCHAR* ptszMsgBuffer = NULL;                         //客户端发送的数据
				RFCCOMPONENTS_HTTP_REQPARAM st_HTTPReqparam;        //客户端的请求参数

				memset(&st_HTTPReqparam, '\0', sizeof(RFCCOMPONENTS_HTTP_REQPARAM));
				//得到一个指定客户端的完整数据包
				if (HttpProtocol_Server_GetMemoryEx(xhHTTPPacket, ppSst_ListAddr[i]->tszClientAddr, &ptszMsgBuffer, &nMsgLen, &st_HTTPReqparam))
				{
					//在另外一个函数里面处理数据
					HTTPTask_TastPost_Handle(&st_HTTPReqparam, ppSst_ListAddr[i]->tszClientAddr, ptszMsgBuffer, nMsgLen);
					//释放内存
					BaseLib_OperatorMemory_FreeCStyle((VOID**)&ptszMsgBuffer);
				}
			}
		}
		BaseLib_OperatorMemory_Free((XPPPMEM)&ppSst_ListAddr, nListCount);
	}
	return 0;
}
XBOOL HTTPTask_TastPost_Handle(RFCCOMPONENTS_HTTP_REQPARAM* pSt_HTTPParam, LPCXSTR lpszClientAddr, LPCXSTR lpszRVBuffer, int nRVLen)
{
	int nMsgLen = 4096;
	LPCXSTR lpszMethodPost = _T("POST");
	LPCXSTR lpszMethodGet = _T("GET");
	XCHAR tszMsgBuffer[4096];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = XTRUE; //收到回复后就关闭

	XCHAR** pptszList;
	XCHAR tszUrlName[128];
	int nListCount = 0;

	memset(tszUrlName, '\0', sizeof(tszUrlName));
	//得到URL参数个数
	HttpProtocol_ServerHelp_GetParament(pSt_HTTPParam->tszHttpUri, &pptszList, &nListCount, tszUrlName);
	if (nListCount < 1)
	{
		st_HDRParam.nHttpCode = 404;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
		return XFALSE;
	}
	XCHAR tszKey[MAX_PATH];
	XCHAR tszValue[MAX_PATH];
	LPCXSTR lpszFuncName = _T("api");
	LPCXSTR lpszParamFuncKey = _T("function");
	LPCXSTR lpszParamName = _T("params1");
	//get
	LPCXSTR lpszParamOPtions = _T("options");
	LPCXSTR lpszParamIDCard = _T("id");
	LPCXSTR lpszParamBank = _T("bank");
	LPCXSTR lpszParamLanguage = _T("language");
	LPCXSTR lpszParamTranslation = _T("translation");
	LPCXSTR lpszParamLocker = _T("lock");
	//post
	LPCXSTR lpszParamP2PClient = _T("p2p");
	LPCXSTR lpszParamZIPCode = _T("zipcode");
	LPCXSTR lpszParamXLog = _T("log");
	LPCXSTR lpszParamQRCode = _T("qrcode");
	LPCXSTR lpszParamSocket = _T("socket");
	LPCXSTR lpszParamDTest = _T("dtest");
	LPCXSTR lpszParamShortLink = _T("slink");

	memset(tszKey, '\0', MAX_PATH);
	memset(tszValue, '\0', MAX_PATH);

	if (0 != _tcsnicmp(lpszFuncName, tszUrlName, _tcslen(lpszFuncName)))
	{
		st_HDRParam.nHttpCode = 404;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
		return XFALSE;
	}
	//获得函数名
	BaseLib_OperatorString_GetKeyValue(pptszList[0], "=", tszKey, tszValue);
	if (0 != _tcsnicmp(lpszParamFuncKey, tszKey, _tcslen(lpszParamFuncKey)))
	{
		st_HDRParam.nHttpCode = 404;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
		return XFALSE;
	}
	//首先处理插件
	int nPluginType = 0;
	if (ModulePlugin_Loader_Find(tszValue, &nPluginType))
	{
		XEngine_PluginTask_Handle(tszValue, lpszClientAddr, lpszRVBuffer, nRVLen, &pptszList, nListCount, nPluginType);
		return XTRUE;
	}
	if (0 == _tcsnicmp(lpszMethodPost, pSt_HTTPParam->tszHttpMethod, _tcslen(lpszMethodPost)))
	{
		if (0 == _tcsnicmp(lpszParamP2PClient, tszValue, _tcslen(lpszParamP2PClient)))
		{
			//是不是P2P
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return XFALSE;
			}
			HTTPTask_TastPost_P2PClient(lpszClientAddr, lpszRVBuffer, nRVLen, _ttoi(tszValue));
		}
		else if (0 == _tcsnicmp(lpszParamZIPCode, tszValue, _tcslen(lpszParamZIPCode)))
		{
			//邮政信息:http://app.xyry.org:5501/api?function=zipcode&params1=0
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return XFALSE;
			}
			HTTPTask_TastPost_PostCode(lpszClientAddr, lpszRVBuffer, nRVLen, _ttoi(tszValue));
		}
		else if (0 == _tcsnicmp(lpszParamXLog, tszValue, _tcslen(lpszParamXLog)))
		{
			//日志信息:http://app.xyry.org:5501/api?function=log&params1=0
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return XFALSE;
			}
			HTTPTask_TastPost_LogInfo(lpszClientAddr, lpszRVBuffer, nRVLen, _ttoi(tszValue));
		}
		else if (0 == _tcsnicmp(lpszParamQRCode, tszValue, _tcslen(lpszParamQRCode)))
		{
			//二维码生成:http://app.xyry.org:5501/api?function=qrcode&params1=0 或者 1
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return XFALSE;
			}
			HTTPTask_TaskPost_QRCode(lpszClientAddr, lpszRVBuffer, nRVLen, _ttoi(tszValue));
		}
		else if (0 == _tcsnicmp(lpszParamSocket, tszValue, _tcslen(lpszParamSocket)))
		{
			//网络测试:http://app.xyry.org:5501/api?function=socket&params1=0 或者 1
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return XFALSE;
			}
			HTTPTask_TastPost_SocketTest(lpszClientAddr, lpszRVBuffer, nRVLen, _ttoi(tszValue));
		}
		else if (0 == _tcsnicmp(lpszParamDTest, tszValue, _tcslen(lpszParamDTest)))
		{
			//数据测试:http://app.xyry.org:5501/api?function=dtest&params1=0 或者 1
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return XFALSE;
			}
			HTTPTask_TastPost_DTest(lpszClientAddr, lpszRVBuffer, nRVLen, _ttoi(tszValue));
		}
		else if (0 == _tcsnicmp(lpszParamShortLink, tszValue, _tcslen(lpszParamShortLink)))
		{
			//短连接:http://app.xyry.org:5501/api?function=slink&params1=0 
			XCHAR tszType[64];
			memset(tszType, '\0', sizeof(tszType));

			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszType);
			HTTPTask_TaskPost_ShortLink(lpszClientAddr, lpszRVBuffer, nRVLen, _ttoi(tszType));
		}
		else
		{
			st_HDRParam.nHttpCode = 404;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的请求不支持:%s，内容:\r\n%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri, lpszRVBuffer);
		}
	}
	else if (0 == _tcsnicmp(lpszMethodGet, pSt_HTTPParam->tszHttpMethod, _tcslen(lpszMethodGet)))
	{
		if (0 == _tcsnicmp(lpszParamOPtions, tszValue, _tcslen(lpszParamOPtions)))
		{
			//HTTP能力查询
			HTTPTask_TaskGet_OPTions(lpszClientAddr);
		}
		else if (0 == _tcsnicmp(lpszParamIDCard, tszValue, _tcslen(lpszParamIDCard)))
		{
			//是不是身份证查询
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return XFALSE;
			}
			HTTPTask_TaskGet_IDCard(lpszClientAddr, tszValue);
		}
		else if (0 == _tcsnicmp(lpszParamBank, tszValue, _tcslen(lpszParamBank)))
		{
			//是不是银行卡信息
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return XFALSE;
			}
			HTTPTask_TaskGet_BankInfo(lpszClientAddr, tszValue);
		}
		else if (0 == _tcsnicmp(lpszParamLanguage, tszValue, _tcslen(lpszParamLanguage)))
		{
			//是不是语言转换
			XCHAR tszCvtType[64];

			memset(tszCvtType, '\0', sizeof(tszCvtType));
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));

			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return XFALSE;
			}
			memset(tszKey, '\0', sizeof(tszKey));

			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszCvtType);
			HTTPTask_TaskGet_Language(lpszClientAddr, tszValue, _ttoi(tszCvtType));
		}
		else if (0 == _tcsnicmp(lpszParamTranslation, tszValue, _tcslen(lpszParamTranslation)))
		{
			//是不是翻译
			XCHAR tszCvtType[64];

			memset(tszCvtType, '\0', sizeof(tszCvtType));
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));

			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return XFALSE;
			}
			memset(tszKey, '\0', sizeof(tszKey));

			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszCvtType);
			HTTPTask_TaskGet_Translation(lpszClientAddr, tszValue, _ttoi(tszCvtType));
		}
		else if (0 == _tcsnicmp(lpszParamLocker, tszValue, _tcslen(lpszParamLocker)))
		{
			//是不是分布式锁
			XCHAR tszLockToken[128];
			XCHAR tszLockType[64];
			
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszLockToken, '\0', sizeof(tszLockToken));
			memset(tszLockType, '\0', sizeof(tszLockType));

			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszLockToken);
			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszLockType);
			HTTPTask_TaskGet_Locker(lpszClientAddr, _ttoi64(tszLockToken), (ENUM_XENGINE_APISERVICE_LOCKER_TYPE)_ttoi(tszLockType));
		}
		else
		{
			st_HDRParam.nHttpCode = 404;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送的请求不支持:%s，内容:\r\n%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri, lpszRVBuffer);
		}
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("HTTP客户端:%s,协议错误"), lpszClientAddr);
	}
	BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
	return XTRUE;
}