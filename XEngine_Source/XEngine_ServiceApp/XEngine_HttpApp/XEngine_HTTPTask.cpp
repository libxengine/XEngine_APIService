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
				if (!RfcComponents_HttpServer_GetMemoryEx(xhHTTPPacket, ppSst_ListAddr[i]->tszClientAddr, &ptszMsgBuffer, &nMsgLen, &st_HTTPReqparam))
				{
					XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,获取数据包失败，错误：%lX"), ppSst_ListAddr[i]->tszClientAddr, HttpServer_GetLastError());
					continue;
				}
				//在另外一个函数里面处理数据
				XEngine_HTTPTask_Handle(&st_HTTPReqparam, ppSst_ListAddr[i]->tszClientAddr, ptszMsgBuffer, nMsgLen);
				//释放内存
				BaseLib_OperatorMemory_FreeCStyle((VOID**)&ptszMsgBuffer);
			}
		}
		BaseLib_OperatorMemory_Free((XPPPMEM)&ppSst_ListAddr, nListCount);
	}
	return 0;
}
BOOL XEngine_HTTPTask_Handle(RFCCOMPONENTS_HTTP_REQPARAM* pSt_HTTPParam, LPCTSTR lpszClientAddr, LPCTSTR lpszRVBuffer, int nRVLen)
{
	int nMsgLen = 4096;
	//LPCTSTR lpszMethodPost = _T("POST");
	LPCTSTR lpszMethodGet = _T("GET");
	TCHAR tszMsgBuffer[4096];
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam;    //发送给客户端的参数

	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memset(&st_HDRParam, '\0', sizeof(RFCCOMPONENTS_HTTP_HDRPARAM));

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = TRUE; //收到回复后就关闭
	if (0 == _tcsnicmp(lpszMethodGet, pSt_HTTPParam->tszHttpMethod, _tcslen(lpszMethodGet)))
	{
		TCHAR** pptszList;
		TCHAR tszUrlName[128];
		int nListCount = 0;

		memset(tszUrlName, '\0', sizeof(tszUrlName));
		//得到URL参数个数
		RfcComponents_HttpHelp_GetParament(pSt_HTTPParam->tszHttpUri, &pptszList, &nListCount, tszUrlName);
		if (nListCount < 3)
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
		LPCTSTR lpszParamFunc1 = _T("function");
		LPCTSTR lpszParamFunc2 = _T("params1");
		LPCTSTR lpszParamValue1 = _T("ip");
		LPCTSTR lpszParamValue2 = _T("id");
		LPCTSTR lpszParamValue3 = _T("phone");
		LPCTSTR lpszParamValue4 = _T("bank");
		LPCTSTR lpszParamValue5 = _T("language");
		LPCTSTR lpszParamValue6 = _T("translation");

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
		if (0 != _tcsnicmp(lpszParamFunc1, tszKey, _tcslen(lpszParamFunc1)))
		{
			st_HDRParam.nHttpCode = 404;
			RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
			BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
			return FALSE;
		}
		//是不是ip查询
		if (0 == _tcsnicmp(lpszParamValue1, tszValue, _tcslen(lpszParamValue1)))
		{
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamFunc2, tszKey, _tcslen(lpszParamFunc2)))
			{
				st_HDRParam.nHttpCode = 404;
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			TCHAR tszGetType[64];

			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszGetType, '\0', sizeof(tszGetType));

			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszGetType);
			XEngine_HTTPTask_IPInfo(lpszClientAddr, tszValue, _ttoi(tszGetType));
		}
		else if (0 == _tcsnicmp(lpszParamValue2, tszValue, _tcslen(lpszParamValue2)))
		{
			//是不是身份证查询
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamFunc2, tszKey, _tcslen(lpszParamFunc2)))
			{
				st_HDRParam.nHttpCode = 404;
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			TCHAR tszGetType[64];

			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszGetType, '\0', sizeof(tszGetType));

			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszGetType);
			XEngine_HTTPTask_IDCard(lpszClientAddr, tszValue, _ttoi(tszGetType));
		}
		else if (0 == _tcsnicmp(lpszParamValue3, tszValue, _tcslen(lpszParamValue3)))
		{
			//是不是电话号码查询
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamFunc2, tszKey, _tcslen(lpszParamFunc2)))
			{
				st_HDRParam.nHttpCode = 404;
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			TCHAR tszGetType[64];

			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszGetType, '\0', sizeof(tszGetType));

			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszGetType);
			XEngine_HTTPTask_PhoneInfo(lpszClientAddr, tszValue, _ttoi(tszGetType));
		}
		else if (0 == _tcsnicmp(lpszParamValue4, tszValue, _tcslen(lpszParamValue4)))
		{
			//是不是银行卡信息
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamFunc2, tszKey, _tcslen(lpszParamFunc2)))
			{
				st_HDRParam.nHttpCode = 404;
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			TCHAR tszGetType[64];

			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszGetType, '\0', sizeof(tszGetType));

			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszGetType);
			XEngine_HTTPTask_BankInfo(lpszClientAddr, tszValue, _ttoi(tszGetType));
		}
		else if (0 == _tcsnicmp(lpszParamValue5, tszValue, _tcslen(lpszParamValue5)))
		{
			//是不是语言转换
			TCHAR tszCvtType[64];
			TCHAR tszGetType[64];

			memset(tszCvtType, '\0', sizeof(tszCvtType));
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			memset(tszGetType, '\0', sizeof(tszGetType));

			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamFunc2, tszKey, _tcslen(lpszParamFunc2)))
			{
				st_HDRParam.nHttpCode = 404;
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			memset(tszKey, '\0', sizeof(tszKey));

			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszGetType);
			BaseLib_OperatorString_GetKeyValue(pptszList[3], "=", tszKey, tszCvtType);
			XEngine_HTTPTask_Language(lpszClientAddr, tszValue, _ttoi(tszGetType), _ttoi(tszCvtType));
		}
		else if (0 == _tcsnicmp(lpszParamValue6, tszValue, _tcslen(lpszParamValue6)))
		{
			//是不是翻译
			TCHAR tszCvtType[64];
			TCHAR tszGetType[64];

			memset(tszCvtType, '\0', sizeof(tszCvtType));
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			memset(tszGetType, '\0', sizeof(tszGetType));

			BaseLib_OperatorString_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			if (0 != _tcsnicmp(lpszParamFunc2, tszKey, _tcslen(lpszParamFunc2)))
			{
				st_HDRParam.nHttpCode = 404;
				RfcComponents_HttpServer_SendMsgEx(xhHTTPPacket, tszMsgBuffer, &nMsgLen, &st_HDRParam);
				XEngine_Network_Send(lpszClientAddr, tszMsgBuffer, nMsgLen);
				BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, pSt_HTTPParam->tszHttpUri);
				return FALSE;
			}
			memset(tszKey, '\0', sizeof(tszKey));

			BaseLib_OperatorString_GetKeyValue(pptszList[2], "=", tszKey, tszGetType);
			BaseLib_OperatorString_GetKeyValue(pptszList[3], "=", tszKey, tszCvtType);
			XEngine_HTTPTask_Translation(lpszClientAddr, tszValue, _ttoi(tszGetType), _ttoi(tszCvtType));;
		}
		BaseLib_OperatorMemory_Free((XPPPMEM)&pptszList, nListCount);
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("HTTP客户端:%s,协议错误"), lpszClientAddr);
	}
	return TRUE;
}