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
XHTHREAD XCALLBACK HTTPTask_TastPost_Thread(XPVOID lParam)
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
		XENGINE_MANAGEPOOL_TASKEVENT** ppSst_ListAddr;
		//获得编号1的所有待处理任务的客户端列表(也就是客户端发送过来的数据已经组好了一个包,需要我们处理)
		HttpProtocol_Server_GetPoolEx(xhHTTPPacket, nThreadPos, &ppSst_ListAddr, &nListCount);
		//先循环客户端
		for (int i = 0; i < nListCount; i++)
		{
			//再循环客户端拥有的任务个数
			for (int j = 0; j < ppSst_ListAddr[i]->nPktCount; j++)
			{
				int nSDLen = 0;                                    //客户端发送的数据大小,不包括头
				int nHDRCount = 0;
				XCHAR* ptszMsgBuffer = NULL;                         //客户端发送的数据
				XCHAR** pptszListHdr;
				RFCCOMPONENTS_HTTP_REQPARAM st_HTTPReqparam;        //客户端的请求参数

				memset(&st_HTTPReqparam, '\0', sizeof(RFCCOMPONENTS_HTTP_REQPARAM));
				//得到一个指定客户端的完整数据包
				if (HttpProtocol_Server_GetMemoryEx(xhHTTPPacket, ppSst_ListAddr[i]->tszClientAddr, &ptszMsgBuffer, &nSDLen, &st_HTTPReqparam, &pptszListHdr, &nHDRCount))
				{
					//在另外一个函数里面处理数据
					HTTPTask_TastPost_Handle(&st_HTTPReqparam, ppSst_ListAddr[i]->tszClientAddr, ptszMsgBuffer, nSDLen, pptszListHdr, nHDRCount);
					//释放内存
					BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMsgBuffer);
					BaseLib_Memory_Free((XPPPMEM)&pptszListHdr, nHDRCount);
				}
			}
		}
		BaseLib_Memory_Free((XPPPMEM)&ppSst_ListAddr, nListCount);
	}
	return 0;
}
bool HTTPTask_TastPost_Verification(RFCCOMPONENTS_HTTP_REQPARAM* pSt_HTTPParam, LPCXSTR lpszClientAddr, XCHAR** pptszHDRList, int nHDRCount)
{
	//http验证
	int nVType = 0;
	int nSDLen = 0;
	XCHAR tszSDBuffer[XPATH_MAX] = {};
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};

	st_HDRParam.nHttpCode = 401;
	st_HDRParam.bIsClose = true;
	st_HDRParam.bAuth = true;
	//打包验证信息
	int nHDRLen = 0;
	XCHAR tszHDRBuffer[XPATH_MAX] = {};
	if (1 == st_ServiceConfig.st_XVerifcation.nVType)
	{
		Verification_HTTP_BasicServerPacket(tszHDRBuffer, &nHDRLen);
	}
	else
	{
		XCHAR tszNonceStr[64] = {};
		XCHAR tszOpaqueStr[64] = {};
		Verification_HTTP_DigestServerPacket(tszHDRBuffer, &nHDRLen, tszNonceStr, tszOpaqueStr);
	}
	//后去验证方法
	if (!Verification_HTTP_GetType(pptszHDRList, nHDRCount, &nVType))
	{
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, NULL, 0, tszHDRBuffer);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,用户验证失败,验证方式:%d,错误:%lX"), lpszClientAddr, st_ServiceConfig.st_XVerifcation.nVType, Verification_GetLastError());
		return false;
	}
	//验证方式是否一致
	if (st_ServiceConfig.st_XVerifcation.nVType != nVType)
	{
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, NULL, 0, tszHDRBuffer);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,用户验证失败,验证方式错误,请求:%d,需求:%d"), lpszClientAddr, nVType, st_ServiceConfig.st_XVerifcation.nVType);
		return false;
	}
	bool bRet = false;

	if (_tcsxlen(st_ServiceConfig.st_XVerifcation.tszAPIAuth) > 0)
	{
		int nHTTPCode = 0;
		int nMSGLen = 0;
		XCLIENT_APIHTTP st_APIHttp = {};
		XCHAR* ptszMSGBuffer = NULL;
		if (!APIClient_Http_Request(_X("GET"), st_ServiceConfig.st_XVerifcation.tszAPIAuth, NULL, &nHTTPCode, &ptszMSGBuffer, &nMSGLen, NULL, NULL, &st_APIHttp))
		{
			st_HDRParam.nHttpCode = 500;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, NULL, 0, tszHDRBuffer);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,用户验证失败,GET请求验证服务:%s 失败,错误码:%lX"), lpszClientAddr, st_ServiceConfig.st_XVerifcation.tszAPIAuth, APIClient_GetLastError());
			return false;
		}
		if (200 != nHTTPCode)
		{
			st_HDRParam.nHttpCode = 500;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, NULL, 0, tszHDRBuffer);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,用户验证失败,GET请求验证服务:%s 失败,错误:%d"), lpszClientAddr, st_ServiceConfig.st_XVerifcation.tszAPIAuth, nHTTPCode);
			return false;
		}
		XENGINE_PROTOCOL_USERAUTH st_UserAuth = {};
		if (!ModuleProtocol_Parse_Verifcation(ptszMSGBuffer, nSDLen, st_UserAuth.tszUserName, st_UserAuth.tszUserPass))
		{
			st_HDRParam.nHttpCode = 500;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, NULL, 0, tszHDRBuffer);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,用户验证失败,返回内容:%s 错误,无法继续"), lpszClientAddr, ptszMSGBuffer);
			BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);
			return false;
		}
		BaseLib_Memory_FreeCStyle((XPPMEM)&ptszMSGBuffer);

		if (1 == nVType)
		{
			bRet = Verification_HTTP_Basic(st_UserAuth.tszUserName, st_UserAuth.tszUserPass, pptszHDRList, nHDRCount);
		}
		else if (2 == nVType)
		{
			bRet = Verification_HTTP_Digest(st_UserAuth.tszUserName, st_UserAuth.tszUserPass, pSt_HTTPParam->tszHttpMethod, pptszHDRList, nHDRCount);
		}
	}
	else
	{
		if (1 == nVType)
		{
			bRet = Verification_HTTP_Basic(st_ServiceConfig.st_XVerifcation.tszUserName, st_ServiceConfig.st_XVerifcation.tszUserPass, pptszHDRList, nHDRCount);
		}
		else if (2 == nVType)
		{
			bRet = Verification_HTTP_Digest(st_ServiceConfig.st_XVerifcation.tszUserName, st_ServiceConfig.st_XVerifcation.tszUserPass, pSt_HTTPParam->tszHttpMethod, pptszHDRList, nHDRCount);
		}
	}

	if (!bRet)
	{
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam, NULL, 0, tszHDRBuffer);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,用户验证失败,验证处理错误,可能用户密码登信息不匹配,类型:%d"), lpszClientAddr, nVType);
		return false;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,HTTP验证类型:%d 通过"), lpszClientAddr, nVType);
	return true;
}

bool HTTPTask_TastPost_Handle(RFCCOMPONENTS_HTTP_REQPARAM* pSt_HTTPParam, LPCXSTR lpszClientAddr, LPCXSTR lpszMSGBuffer, int nMSGLen, XCHAR** pptszHDRList, int nHDRCount)
{
	bool bVerification = false;
	int nSDLen = 4096;
	int nRVLen = 4096;
	LPCXSTR lpszMethodPost = _X("POST");
	LPCXSTR lpszMethodGet = _X("GET");
	XCHAR tszSDBuffer[4096] = {};
	XCHAR tszRVBuffer[4096] = {};
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	XCHAR** pptszList;
	XCHAR tszUrlName[128];
	int nListCount = 0;

	memset(tszUrlName, '\0', sizeof(tszUrlName));

	XCHAR tszUrlBuffer[XPATH_MAX] = {};
	XCHAR tszGBKBuffer[XPATH_MAX] = {};
	Cryption_Codec_UrlDeCodec(pSt_HTTPParam->tszHttpUri, _tcsxlen(pSt_HTTPParam->tszHttpUri), tszUrlBuffer);
#ifdef _MSC_BUILD
	int nCLen = _tcsxlen(tszUrlBuffer);
	BaseLib_Charset_UTFToAnsi(tszUrlBuffer, tszGBKBuffer, &nCLen);
#else
	_tcsxcpy(tszGBKBuffer, pSt_HTTPParam->tszHttpUri);
#endif
	//得到URL参数个数
	HttpProtocol_ServerHelp_GetParament(tszGBKBuffer, &pptszList, &nListCount, tszUrlName);
	if (nListCount < 1)
	{
		//是不是代理转发
		if (HTTPTask_TaskPost_SLProxy(lpszClientAddr, tszGBKBuffer, &pptszHDRList, nHDRCount))
		{
			return true;
		}
		st_HDRParam.nHttpCode = 404;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		BaseLib_Memory_Free((XPPPMEM)&pptszList, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, tszGBKBuffer);
		return false;
	}
	//http验证
	if (st_ServiceConfig.st_XVerifcation.bEnable)
	{
		//全面验证
		if (!HTTPTask_TastPost_Verification(pSt_HTTPParam, lpszClientAddr, pptszHDRList, nHDRCount))
		{
			return false;
		}
		bVerification = true;
	}

	XCHAR tszKey[XPATH_MAX];
	XCHAR tszValue[XPATH_MAX];
	LPCXSTR lpszFuncName = _X("api");
	LPCXSTR lpszParamFuncKey = _X("function");
	//get
	LPCXSTR lpszParamIDCard = _X("id");
	LPCXSTR lpszParamBank = _X("bank");
	LPCXSTR lpszParamTranslation = _X("translation");
	LPCXSTR lpszParamLocker = _X("lock");
	LPCXSTR lpszParamReload = _X("reload");
	LPCXSTR lpszParamWeather = _X("weather");
	LPCXSTR lpszParamRegion = _X("region");
	LPCXSTR lpszParamOil = _X("oil");
	LPCXSTR lpszParamPhone = _X("phone");
	LPCXSTR lpszParamIPAddr = _X("ip");
	LPCXSTR lpszParamMacInfo = _X("mac");
	//post
	LPCXSTR lpszParamP2PClient = _X("p2p");
	LPCXSTR lpszParamZIPCode = _X("zipcode");
	LPCXSTR lpszParamXLog = _X("log");
	LPCXSTR lpszParamQRCode = _X("qrcode");
	LPCXSTR lpszParamSocket = _X("socket");
	LPCXSTR lpszParamDTest = _X("dtest");
	LPCXSTR lpszParamShortLink = _X("slink");
	LPCXSTR lpszParamWordFilter = _X("wordfilter");
	LPCXSTR lpszParamBack = _X("back");
	LPCXSTR lpszParamImage = _X("image");
	LPCXSTR lpszParamDeamon = _X("deamon");
	LPCXSTR lpszParamMachine = _X("machine");

	memset(tszKey, '\0', XPATH_MAX);
	memset(tszValue, '\0', XPATH_MAX);

	if (0 != _tcsxnicmp(lpszFuncName, tszUrlName, _tcsxlen(lpszFuncName)))
	{
		st_HDRParam.nHttpCode = 404;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		BaseLib_Memory_Free((XPPPMEM)&pptszList, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, tszGBKBuffer);
		return false;
	}
	//获得函数名
	BaseLib_String_GetKeyValue(pptszList[0], "=", tszKey, tszValue);
	if (0 != _tcsxnicmp(lpszParamFuncKey, tszKey, _tcsxlen(lpszParamFuncKey)))
	{
		st_HDRParam.nHttpCode = 404;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		BaseLib_Memory_Free((XPPPMEM)&pptszList, nListCount);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,发送的URL请求参数不正确:%s"), lpszClientAddr, tszGBKBuffer);
		return false;
	}
	//首先处理插件
	int nPluginType = 0;
	if (ModulePlugin_Loader_Find(tszValue, &nPluginType))
	{
		XEngine_PluginTask_Handle(tszValue, lpszClientAddr, lpszMSGBuffer, nMSGLen, &pptszList, nListCount, nPluginType);
		return true;
	}
	if (0 == _tcsxnicmp(lpszMethodPost, pSt_HTTPParam->tszHttpMethod, _tcsxlen(lpszMethodPost)))
	{
		if (0 == _tcsxnicmp(lpszParamP2PClient, tszValue, _tcsxlen(lpszParamP2PClient)))
		{
			//是不是P2P
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			HTTPTask_TastPost_P2PClient(lpszClientAddr, lpszMSGBuffer, nMSGLen, _ttxoi(tszValue));
		}
		else if (0 == _tcsxnicmp(lpszParamZIPCode, tszValue, _tcsxlen(lpszParamZIPCode)))
		{
			//邮政信息:http://app.xyry.org:5501/api?function=zipcode&params1=0
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			HTTPTask_TastPost_PostCode(lpszClientAddr, lpszMSGBuffer, nMSGLen, _ttxoi(tszValue));
		}
		else if (0 == _tcsxnicmp(lpszParamXLog, tszValue, _tcsxlen(lpszParamXLog)))
		{
			//日志信息:http://app.xyry.org:5501/api?function=log&params1=0
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			HTTPTask_TastPost_LogInfo(lpszClientAddr, lpszMSGBuffer, nMSGLen, _ttxoi(tszValue));
		}
		else if (0 == _tcsxnicmp(lpszParamQRCode, tszValue, _tcsxlen(lpszParamQRCode)))
		{
			//二维码生成:http://app.xyry.org:5501/api?function=qrcode&params1=0 或者 1
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			HTTPTask_TaskPost_QRCode(lpszClientAddr, lpszMSGBuffer, nMSGLen, _ttxoi(tszValue));
		}
		else if (0 == _tcsxnicmp(lpszParamSocket, tszValue, _tcsxlen(lpszParamSocket)))
		{
			//网络测试:http://app.xyry.org:5501/api?function=socket&params1=0 或者 1
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			HTTPTask_TastPost_SocketTest(lpszClientAddr, lpszMSGBuffer, nMSGLen, _ttxoi(tszValue));
		}
		else if (0 == _tcsxnicmp(lpszParamDTest, tszValue, _tcsxlen(lpszParamDTest)))
		{
			//数据测试:http://app.xyry.org:5501/api?function=dtest&params1=0 或者 1
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			HTTPTask_TastPost_DTest(lpszClientAddr, lpszMSGBuffer, nMSGLen, _ttxoi(tszValue));
		}
		else if (0 == _tcsxnicmp(lpszParamShortLink, tszValue, _tcsxlen(lpszParamShortLink)))
		{
			//短连接:http://app.xyry.org:5501/api?function=slink&params1=0 
			XCHAR tszType[64];
			memset(tszType, '\0', sizeof(tszType));

			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszType);
			HTTPTask_TaskPost_ShortLink(lpszClientAddr, lpszMSGBuffer, nMSGLen, _ttxoi(tszType));
		}
		else if (0 == _tcsxnicmp(lpszParamWordFilter, tszValue, _tcsxlen(lpszParamWordFilter)))
		{
			//敏感词:http://app.xyry.org:5501/api?function=wordfilter&params1=0 
			XCHAR tszType[64];
			memset(tszType, '\0', sizeof(tszType));

			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszType);
			HTTPTask_TastPost_WordFilter(lpszClientAddr, lpszMSGBuffer, nMSGLen, _ttxoi(tszType));
		}
		else if (0 == _tcsxnicmp(lpszParamBack, tszValue, _tcsxlen(lpszParamBack)))
		{
			//后台管理接口:http://app.xyry.org:5501/api?function=back&params1=0
			XCHAR tszType[64];
			memset(tszType, '\0', sizeof(tszType));
			//单独验证
			if (st_ServiceConfig.st_XVerifcation.st_VerSwitch.bBackService && !bVerification)
			{
				if (!HTTPTask_TastPost_Verification(pSt_HTTPParam, lpszClientAddr, pptszHDRList, nHDRCount))
				{
					return false;
				}
			}
			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszType);
			HTTPTask_TaskPost_BackService(lpszClientAddr, lpszMSGBuffer, nMSGLen, _ttxoi(tszType));
		}
		else if (0 == _tcsxnicmp(lpszParamImage, tszValue, _tcsxlen(lpszParamImage)))
		{
			//图像处理接口:http://app.xyry.org:5501/api?function=image&params1=0
			HTTPTask_TaskPost_Image(lpszClientAddr, lpszMSGBuffer, nMSGLen, &pptszList, nListCount);
		}
		else if (0 == _tcsxnicmp(lpszParamDeamon, tszValue, _tcsxlen(lpszParamDeamon)))
		{
			//守护进程接口:http://app.xyry.org:5501/api?function=deamon&params1=0
			if (st_ServiceConfig.st_XVerifcation.st_VerSwitch.bDeamon && !bVerification)
			{
				if (!HTTPTask_TastPost_Verification(pSt_HTTPParam, lpszClientAddr, pptszHDRList, nHDRCount))
				{
					return false;
				}
			}
			HTTPTask_TaskPost_Deamon(lpszClientAddr, lpszMSGBuffer, nMSGLen);
		}
		else if (0 == _tcsxnicmp(lpszParamMachine, tszValue, _tcsxlen(lpszParamMachine)))
		{
			//信息收集接口:http://app.xyry.org:5501/api?function=machine&params1=0
			XCHAR tszType[64];
			memset(tszType, '\0', sizeof(tszType));

			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszType);
			HTTPTask_TastPost_Machine(lpszClientAddr, lpszMSGBuffer, nMSGLen, _ttxoi(tszType));
		}
		else
		{
			st_HDRParam.nHttpCode = 404;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,发送的请求不支持:%s，内容:\r\n%s"), lpszClientAddr, tszGBKBuffer, lpszMSGBuffer);
		}
	}
	else if (0 == _tcsxnicmp(lpszMethodGet, pSt_HTTPParam->tszHttpMethod, _tcsxlen(lpszMethodGet)))
	{
		if (0 == _tcsxnicmp(lpszParamReload, tszValue, _tcsxlen(lpszParamReload)))
		{
			//是不是配置重载
			memset(tszKey, '\0', sizeof(tszKey));
			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			HTTPTask_TaskGet_Reload(lpszClientAddr, tszValue);
		}
		else if (0 == _tcsxnicmp(lpszParamIDCard, tszValue, _tcsxlen(lpszParamIDCard)))
		{
			//是不是身份证查询
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			HTTPTask_TaskGet_IDCard(lpszClientAddr, tszValue);
		}
		else if (0 == _tcsxnicmp(lpszParamBank, tszValue, _tcsxlen(lpszParamBank)))
		{
			//是不是银行卡信息
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszValue, '\0', sizeof(tszValue));
			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			HTTPTask_TaskGet_BankInfo(lpszClientAddr, tszValue);
		}
		else if (0 == _tcsxnicmp(lpszParamTranslation, tszValue, _tcsxlen(lpszParamTranslation)))
		{
			//是不是翻译
			XCHAR tszMSGBuffer[2048] = {};
			XCHAR tszSrcBuffer[64] = {};
			XCHAR tszDstBuffer[64] = {};

			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszMSGBuffer);
			BaseLib_String_GetKeyValue(pptszList[2], "=", tszKey, tszSrcBuffer);
			BaseLib_String_GetKeyValue(pptszList[3], "=", tszKey, tszDstBuffer);
			HTTPTask_TaskGet_Translation(lpszClientAddr, tszMSGBuffer, tszSrcBuffer, tszDstBuffer);
		}
		else if (0 == _tcsxnicmp(lpszParamLocker, tszValue, _tcsxlen(lpszParamLocker)))
		{
			//是不是分布式锁
			XCHAR tszLockToken[128];
			XCHAR tszLockType[64];
			
			memset(tszKey, '\0', sizeof(tszKey));
			memset(tszLockToken, '\0', sizeof(tszLockToken));
			memset(tszLockType, '\0', sizeof(tszLockType));

			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszLockToken);
			BaseLib_String_GetKeyValue(pptszList[2], "=", tszKey, tszLockType);
			HTTPTask_TaskGet_Locker(lpszClientAddr, _ttxoll(tszLockToken), (ENUM_XENGINE_APISERVICE_LOCKER_TYPE)_ttxoi(tszLockType));
		}
		else if (0 == _tcsxnicmp(lpszParamWeather, tszValue, _tcsxlen(lpszParamWeather)))
		{
			//天气:http://127.0.0.1:5501/api?function=weather&params1=110101
			XCHAR tszIDAddr[128] = {};

			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszIDAddr);
			HTTPTask_TaskGet_WeatherInfo(lpszClientAddr, tszIDAddr);
		}
		else if (0 == _tcsxnicmp(lpszParamRegion, tszValue, _tcsxlen(lpszParamRegion)))
		{
			//地区ID:http://127.0.0.1:5501/api?function=region&type=1&params=省份&params=市区&params=县级
			int nType = 0;
			memset(tszValue, '\0', sizeof(tszValue));

			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			nType = _ttxoi(tszValue);
			if (0 == nType)
			{
				memset(tszValue, '\0', sizeof(tszValue));
				BaseLib_String_GetKeyValue(pptszList[2], "=", tszKey, tszValue);
				HTTPTask_TaskGet_IDRegion(lpszClientAddr, nType, tszValue, NULL, NULL);
			}
			else
			{
				if (2 == nListCount)
				{
					XCHAR tszProvincerStr[32] = {};
					BaseLib_String_GetKeyValue(pptszList[2], "=", tszKey, tszProvincerStr);
					HTTPTask_TaskGet_IDRegion(lpszClientAddr, nType, tszProvincerStr, NULL, NULL);
				}
				else if (3 == nListCount)
				{
					XCHAR tszProvincerStr[32] = {};
					XCHAR tszCityStr[32] = {};
					BaseLib_String_GetKeyValue(pptszList[2], "=", tszKey, tszProvincerStr);
					BaseLib_String_GetKeyValue(pptszList[3], "=", tszKey, tszCityStr);

					HTTPTask_TaskGet_IDRegion(lpszClientAddr, nType, tszProvincerStr, tszCityStr, NULL);
				}
				else
				{
					XCHAR tszProvincerStr[32] = {};
					XCHAR tszCityStr[32] = {};
					XCHAR tszCountyStr[32] = {};
					BaseLib_String_GetKeyValue(pptszList[2], "=", tszKey, tszProvincerStr);
					BaseLib_String_GetKeyValue(pptszList[3], "=", tszKey, tszCityStr);
					BaseLib_String_GetKeyValue(pptszList[4], "=", tszKey, tszCountyStr);

					HTTPTask_TaskGet_IDRegion(lpszClientAddr, nType, tszProvincerStr, tszCityStr, tszCountyStr);
				}
			}
		}
		else if (0 == _tcsxnicmp(lpszParamOil, tszValue, _tcsxlen(lpszParamOil)))
		{
			//油价:http://127.0.0.1:5501/api?function=oil&param=地区
			memset(tszValue, '\0', sizeof(tszValue));

			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszValue);
			HTTPTask_TaskGet_Oil(lpszClientAddr, tszValue);
		}
		else if ((0 == _tcsxnicmp(lpszParamPhone, tszValue, _tcsxlen(lpszParamPhone))) || (0 == _tcsxnicmp(lpszParamIPAddr, tszValue, _tcsxlen(lpszParamIPAddr))) || (0 == _tcsxnicmp(lpszParamMacInfo, tszValue, _tcsxlen(lpszParamMacInfo))))
		{
			//phone:http://127.0.0.1:5501/api?function=phone&param=1369943
			//ip:http://127.0.0.1:5501/api?function=ip&param=117.172.221.14&language=en
			//mac:http://127.0.0.1:5501/api?function=mac&param=00:00:0C
			memset(tszSDBuffer, '\0', sizeof(tszSDBuffer));

			BaseLib_String_GetKeyValue(pptszList[1], "=", tszKey, tszSDBuffer);
			if (nListCount <= 2)
			{
				HTTPTask_TaskGet_APIModule(lpszClientAddr, tszValue, tszSDBuffer, NULL);
			}
			else
			{
				XCHAR tszTPStr[128] = {};
				BaseLib_String_GetKeyValue(pptszList[2], "=", tszKey, tszTPStr);
				HTTPTask_TaskGet_APIModule(lpszClientAddr, tszValue, tszSDBuffer, tszTPStr);
			}
		}
		else
		{
			st_HDRParam.nHttpCode = 404;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszSDBuffer, &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,发送的请求不支持:%s，内容:\r\n%s"), lpszClientAddr, tszGBKBuffer, lpszMSGBuffer);
		}
	}
	else
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _X("HTTP客户端:%s,协议错误"), lpszClientAddr);
	}
	BaseLib_Memory_Free((XPPPMEM)&pptszList, nListCount);
	return true;
}