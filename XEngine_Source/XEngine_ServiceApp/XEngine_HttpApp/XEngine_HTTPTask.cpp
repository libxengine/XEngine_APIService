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
XHTHREAD CALLBACK XEngine_HTTPTask_Thread(LPVOID lParam)
{
	//任务池是编号1开始的.
	int nThreadPos = *(int*)lParam;
	nThreadPos++;

	while (bIsRun)
	{
		//等待编号1的任务池触发一个组完包的事件
		if (!RfcComponents_HttpServer_EventWaitEx(xhHTTPPacket, nThreadPos))
		{
			continue;
		}
		int nListCount = 0;
		RFCCOMPONENTS_HTTP_PKTCLIENT** ppSst_ListAddr;
		//获得编号1的所有待处理任务的客户端列表(也就是客户端发送过来的数据已经组好了一个包,需要我们处理)
		RfcComponents_HttpServer_GetPoolEx(xhHTTPPacket, nThreadPos, &ppSst_ListAddr, &nListCount);
		//先循环客户端
		for (int i = 0; i < nListCount; i++)
		{
			//再循环客户端拥有的任务个数
			for (int j = 0; j < ppSst_ListAddr[i]->nPktCount; j++)
			{
				int nMsgLen = 0;                                    //客户端发送的数据大小,不包括头
				CHAR* ptszMsgBuffer = NULL;                         //客户端发送的数据
				RFCCOMPONENTS_HTTP_REQPARAM st_HTTPReqparam;        //客户端的请求参数

				memset(&st_HTTPReqparam, '\0', sizeof(RFCCOMPONENTS_HTTP_REQPARAM));
				//得到一个指定客户端的完整数据包
				if (RfcComponents_HttpServer_GetMemoryEx(xhHTTPPacket, ppSst_ListAddr[i]->tszClientAddr, &ptszMsgBuffer, &nMsgLen, &st_HTTPReqparam))
				{
					//在另外一个函数里面处理数据
					XEngine_HTTPTask_Handle(&st_HTTPReqparam, ppSst_ListAddr[i]->tszClientAddr, ptszMsgBuffer, nMsgLen);
					//释放内存
					BaseLib_OperatorMemory_FreeCStyle((VOID**)&ptszMsgBuffer);
				}
			}
		}
		BaseLib_OperatorMemory_Free((XPPPMEM)&ppSst_ListAddr, nListCount);
	}
	return 0;
}
BOOL XEngine_HTTPTask_Handle(RFCCOMPONENTS_HTTP_REQPARAM* pSt_HTTPParam, LPCTSTR lpszClientAddr, LPCTSTR lpszRVBuffer, int nRVLen)
{
	int nMsgLen = 4096;
	LPCTSTR lpszMethodPost = _T("POST");
	LPCTSTR lpszMethodGet = _T("GET");
	TCHAR tszMsgBuffer[4096];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭

	TCHAR** pptszList;
	TCHAR tszUrlName[128];
	int nListCount = 0;

	memset(tszUrlName, '\0', sizeof(tszUrlName));
	//得到URL参数个数
	RfcComponents_HttpHelp_GetParament(pSt_HTTPParam->tszHttpUri, &pptszList, &nListCount, tszUrlName);
	if (nListCount < 1)
	{
		st_HDRParam.nHttpCode = 404;
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
		return FALSE;
	}
	TCHAR tszKey[128];
	TCHAR tszValue[128];
	LPCTSTR lpszFuncName = _T("api");
	LPCTSTR lpszParamFuncKey = _T("function");
	LPCTSTR lpszParamName = _T("params1");
	//get
	LPCTSTR lpszParamOPtions = _T("options");
	LPCTSTR lpszParamIPAddr = _T("ip");
	LPCTSTR lpszParamIDCard = _T("id");
	LPCTSTR lpszParamBank = _T("bank");
	LPCTSTR lpszParamLanguage = _T("language");
	LPCTSTR lpszParamTranslation = _T("translation");
	LPCTSTR lpszParamLocker = _T("lock");
	//post
	LPCTSTR lpszParamP2PClient = _T("p2p");
	LPCTSTR lpszParamCDKey = _T("cdkey");
	LPCTSTR lpszParamZIPCode = _T("zipcode");

	memset(tszKey, '\0', sizeof(tszKey));
	memset(tszValue, '\0', sizeof(tszValue));

	if (0 != _tcsnicmp(lpszFuncName, tszUrlName, _tcslen(lpszFuncName)))
	{
		st_HDRParam.nHttpCode = 404;
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
		return FALSE;
	}
	//获得函数名
	BaseLib_OperatorString_GetKeyValue(pptszList[0], "=", tszKey, tszValue);
	if (0 != _tcsnicmp(lpszParamFuncKey, tszKey, _tcslen(lpszParamFuncKey)))
	{
		st_HDRParam.nHttpCode = 404;
		RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
		BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
		return FALSE;
	}
	//首先处理插件
	int nPluginType = 0;
	if (ModulePlugin_Loader_Find(tszValue, &nPluginType))
	{
		XEngine_PluginTask_Handle(tszValue, lpszClientAddr, lpszRVBuffer, nRVLen, &pptszList, nListCount, nPluginType);
		return TRUE;
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
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			XEngine_HTTPTask_P2PClient(lpszClientAddr, lpszRVBuffer, nRVLen, _ttoi(tszValue));
		}
		else if (0 == _tcsnicmp(lpszParamCDKey, tszValue, _tcslen(lpszParamCDKey)))
		{
			//是不是CDKEY生成器:http://app.xyry.org:5501/api?function=cdkey&params1=0&params2=123456
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			int nOPType = _ttoi(tszValue);
			if (3 == nListCount)
			{
				memset(tszKey, '\0', sizeof(tszKey));
				memset(tszValue, '\0', sizeof(tszValue));
				BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszValue);
				XEngine_HTTPTask_CDKey(lpszClientAddr, lpszRVBuffer, nRVLen, nOPType, tszValue);
			}
			else
			{
				XEngine_HTTPTask_CDKey(lpszClientAddr, lpszRVBuffer, nRVLen, nOPType);
			}
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
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			XEngine_HTTPTask_PostCode(lpszClientAddr, lpszRVBuffer, nRVLen, _ttoi(tszValue));
		}
	}
	else if (0 == _tcsnicmp(lpszMethodGet, pSt_HTTPParam->tszHttpMethod, _tcslen(lpszMethodGet)))
	{
		if (0 == _tcsnicmp(lpszParamOPtions, tszValue, _tcslen(lpszParamOPtions)))
		{
			//HTTP能力查询
			XEngine_HTTPTask_OPTions(lpszClientAddr);
		}
		else if (0 == _tcsnicmp(lpszParamIPAddr, tszValue, _tcslen(lpszParamIPAddr)))
		{
			//是不是ip查询
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			XEngine_HTTPTask_IPInfo(lpszClientAddr, tszValue);
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
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			XEngine_HTTPTask_IDCard(lpszClientAddr, tszValue);
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
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			XEngine_HTTPTask_BankInfo(lpszClientAddr, tszValue);
		}
		else if (0 == _tcsnicmp(lpszParamLanguage, tszValue, _tcslen(lpszParamLanguage)))
		{
			//是不是语言转换
			TCHAR tszCvtType[64];

			memset(tszCvtType, '\0', sizeof(tszCvtType));
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));

			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			memset(tszKey, '\0', sizeof(tszKey));

			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszCvtType);
			XEngine_HTTPTask_Language(lpszClientAddr, tszValue, _ttoi(tszCvtType));
		}
		else if (0 == _tcsnicmp(lpszParamTranslation, tszValue, _tcslen(lpszParamTranslation)))
		{
			//是不是翻译
			TCHAR tszCvtType[64];

			memset(tszCvtType, '\0', sizeof(tszCvtType));
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));

			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamName, tszKey, _tcslen(lpszParamName)))
			{
				st_HDRParam.nHttpCode = 404;
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			memset(tszKey, '\0', sizeof(tszKey));

			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszCvtType);
			XEngine_HTTPTask_Translation(lpszClientAddr, tszValue, _ttoi(tszCvtType));
		}
		else if (0 == _tcsnicmp(lpszParamLocker, tszValue, _tcslen(lpszParamLocker)))
		{
			//是不是分布式锁
			TCHAR tszLockToken[128];
			TCHAR tszLockType[64];
			
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszLockToken, '\0', sizeof(tszLockToken));
			memset(tszLockType, '\0', sizeof(tszLockType));

			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszLockToken);
			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszLockType);
			XEngine_HTTPTask_Locker(lpszClientAddr, _ttoi64(tszLockToken), (ENUM_XENGINE_APISERVICE_LOCKER_TYPE)_ttoi(tszLockType));
		}
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("HTTP客户端:%s,协议错误"), lpszClientAddr);
	}
	BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
	return TRUE;
}