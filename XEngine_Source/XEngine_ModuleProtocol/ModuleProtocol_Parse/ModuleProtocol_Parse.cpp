#include "pch.h"
#include "ModuleProtocol_Parse.h"
/********************************************************************
//    Created:     2022/03/03  11:10:04
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Parse\ModuleProtocol_Parse.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Parse
//    File Base:   ModuleProtocol_Parse
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     协议解析类
//    History:
*********************************************************************/
CModuleProtocol_Parse::CModuleProtocol_Parse()
{
}
CModuleProtocol_Parse::~CModuleProtocol_Parse()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleProtocol_Parse_IDCard
函数功能：ID身份证号码解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的身份证
 参数.二：pSt_IDInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出ID身份证编码信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Parse::ModuleProtocol_Parse_IDCard(LPCTSTR lpszMsgBuffer, XENGINE_IDCARDINFO* pSt_IDInfo)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == lpszMsgBuffer) || (NULL == pSt_IDInfo))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}
	if (_tcslen(lpszMsgBuffer) != 18)
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_LEN;
		return FALSE;
	}
	int nPos = 0;
	TCHAR tszTmpBuffer[16];
	//是否是身份证号码
	for (int i = 0; i < 17; i++)
	{
		if (!isdigit(lpszMsgBuffer[i]))
		{
			ModuleProtocol_IsErrorOccur = TRUE;
			ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_FMT;
			return FALSE;
		}
	}
	_tcscpy(pSt_IDInfo->tszIDNumber, lpszMsgBuffer);
	//提取行政区域
	memset(tszTmpBuffer, '\0', sizeof(tszTmpBuffer));
	memcpy(tszTmpBuffer, lpszMsgBuffer + nPos, 2);
	pSt_IDInfo->nIDProvince = _ttoi(tszTmpBuffer);
	nPos += 2;

	memset(tszTmpBuffer, '\0', sizeof(tszTmpBuffer));
	memcpy(tszTmpBuffer, lpszMsgBuffer + nPos, 2);
	pSt_IDInfo->nIDCity = _ttoi(tszTmpBuffer);
	nPos += 2;

	memset(tszTmpBuffer, '\0', sizeof(tszTmpBuffer));
	memcpy(tszTmpBuffer, lpszMsgBuffer + nPos, 2);
	pSt_IDInfo->nIDCounty = _ttoi(tszTmpBuffer);
	nPos += 2;
	//提取生日
	memset(tszTmpBuffer, '\0', sizeof(tszTmpBuffer));
	memcpy(tszTmpBuffer, lpszMsgBuffer + nPos, 4);
	pSt_IDInfo->nBirthYear = _ttoi(tszTmpBuffer);
	nPos += 4;

	memset(tszTmpBuffer, '\0', sizeof(tszTmpBuffer));
	memcpy(tszTmpBuffer, lpszMsgBuffer + nPos, 2);
	pSt_IDInfo->nBirthMonth = _ttoi(tszTmpBuffer);
	nPos += 2;

	memset(tszTmpBuffer, '\0', sizeof(tszTmpBuffer));
	memcpy(tszTmpBuffer, lpszMsgBuffer + nPos, 2);
	pSt_IDInfo->nBirthDay = _ttoi(tszTmpBuffer);
	nPos += 2;
	//提取派出所编码
	memset(tszTmpBuffer, '\0', sizeof(tszTmpBuffer));
	memcpy(tszTmpBuffer, lpszMsgBuffer + nPos, 2);
	pSt_IDInfo->nPoliceID = _ttoi(tszTmpBuffer);
	nPos += 2;
	//提取性别
	memset(tszTmpBuffer, '\0', sizeof(tszTmpBuffer));
	memcpy(tszTmpBuffer, lpszMsgBuffer + nPos, 1);
	pSt_IDInfo->nSex = _ttoi(tszTmpBuffer);
	nPos += 1;
	//提取校验码
	memset(tszTmpBuffer, '\0', sizeof(tszTmpBuffer));
	memcpy(tszTmpBuffer, lpszMsgBuffer + nPos, 1);
	pSt_IDInfo->nCheck = _ttoi(tszTmpBuffer);
	nPos += 1;
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Parse_Bank
函数功能：银行卡解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的内容
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入解析大小
 参数.三：pSt_BankInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析好的内容
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Parse::ModuleProtocol_Parse_Bank(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_BANKINFO* pSt_BankInfo)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == lpszMsgBuffer) || (0 == nMsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//开始解析配置文件
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMsgBuffer, lpszMsgBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_JSON;
		return FALSE;
	}
	//{"messages":[{"errorCodes":"CARD_BIN_NOT_MATCH","name":"cardNo"}],"validated":false,"stat":"ok","key":"62215546546546"}
	//{"cardType":"DC","bank":"CMB","key":"62215546546546"messages":[],"validated":true,"stat":"ok"}
	if (!st_JsonRoot["validated"].asBool())
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_VALIDATE;
		return FALSE;
	}
	LPCTSTR lpszTypeDC = _T("DC");
	LPCTSTR lpszTypeCC = _T("CC");
	if (0 == _tcsncmp(lpszTypeDC, st_JsonRoot["cardType"].asCString(), _tcslen(lpszTypeDC)))
	{
		pSt_BankInfo->enBankType = ENUM_XENGINE_APISERVICE_BANK_TYPE_DC;
	}
	else if (0 == _tcsncmp(lpszTypeCC, st_JsonRoot["cardType"].asCString(), _tcslen(lpszTypeCC)))
	{
		pSt_BankInfo->enBankType = ENUM_XENGINE_APISERVICE_BANK_TYPE_CC;
	}
	else
	{
		pSt_BankInfo->enBankType = ENUM_XENGINE_APISERVICE_BANK_TYPE_BC;
	}
	_tcscpy(pSt_BankInfo->tszBankAbridge, st_JsonRoot["bank"].asCString());
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Parse_Translation
函数功能：翻译解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的内容
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入解析大小
 参数.三：pSt_LanguageInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析好的内容
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Parse::ModuleProtocol_Parse_Translation(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == lpszMsgBuffer) || (0 == nMsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//开始解析配置文件
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMsgBuffer, lpszMsgBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_JSON;
		return FALSE;
	}
	//{"type":"ZH_CN2EN","errorCode":0,"elapsedTime":1,"translateResult":[[{"src":"计算","tgt":"To calculate"}]]}
	if (0 != st_JsonRoot["errorCode"].asInt())
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_VALIDATE;
		return FALSE;
	}
	Json::Value st_JsonTranslation = st_JsonRoot["translateResult"];

	_tcscpy(pSt_LanguageInfo->tszSourceStr, st_JsonTranslation[0][0]["src"].asCString());
	_tcscpy(pSt_LanguageInfo->tszDestStr, st_JsonTranslation[0][0]["tgt"].asCString());
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Parse_P2PClient
函数功能：P2P客户端请求解析函数
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pSt_P2XPPeer
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析后的节点信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Parse::ModuleProtocol_Parse_P2PClient(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_P2XPPEER_PROTOCOL* pSt_P2XPPeer)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == lpszMsgBuffer) || (NULL == pSt_P2XPPeer))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	Json::CharReaderBuilder st_JsonBuild;
	Json::CharReader* pSt_JsonReader(st_JsonBuild.newCharReader());

	JSONCPP_STRING st_JsonError;
	//解析JSON
	if (!pSt_JsonReader->parse(lpszMsgBuffer, lpszMsgBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_JSON;
		return FALSE;
	}
	delete pSt_JsonReader;
	pSt_JsonReader = NULL;

	if (!st_JsonRoot["tszUserName"].isNull())
	{
		_tcscpy(pSt_P2XPPeer->tszUserName, st_JsonRoot["tszUserName"].asCString());
	}
	if (!st_JsonRoot["tszPrivateAddr"].isNull())
	{
		_tcscpy(pSt_P2XPPeer->tszPrivateAddr, st_JsonRoot["tszPrivateAddr"].asCString());
	}
	if (!st_JsonRoot["tszPublicAddr"].isNull())
	{
		_tcscpy(pSt_P2XPPeer->tszPublicAddr, st_JsonRoot["tszPublicAddr"].asCString());
	}
	if (!st_JsonRoot["dwConnectType"].isNull())
	{
		pSt_P2XPPeer->dwConnectType = st_JsonRoot["dwConnectType"].asInt();
	}
	if (!st_JsonRoot["dwPeerType"].isNull())
	{
		pSt_P2XPPeer->dwPeerType = st_JsonRoot["dwPeerType"].asInt();
	}
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Parse_ZIPCode
函数功能：解析邮政地址信息
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pSt_ZIPInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析后的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Parse::ModuleProtocol_Parse_ZIPCode(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_ZIPINFO* pSt_ZIPInfo)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == lpszMsgBuffer) || (NULL == pSt_ZIPInfo))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_ReaderBuilder;
	//解析JSON
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_ReaderBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMsgBuffer, lpszMsgBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}

	if (!st_JsonRoot["tszProvincer"].isNull())
	{
		_tcscpy(pSt_ZIPInfo->tszProvincer, st_JsonRoot["tszProvincer"].asCString());
	}
	if (!st_JsonRoot["tszCity"].isNull())
	{
		_tcscpy(pSt_ZIPInfo->tszCity, st_JsonRoot["tszCity"].asCString());
	}
	if (!st_JsonRoot["tszCounty"].isNull())
	{
		_tcscpy(pSt_ZIPInfo->tszCounty, st_JsonRoot["tszCounty"].asCString());
	}

	if (!st_JsonRoot["nZipCode"].isNull())
	{
		pSt_ZIPInfo->nZipCode = st_JsonRoot["nZipCode"].asInt();
	}
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Parse_XLog
函数功能：解析日志信息
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入数据大小
 参数.三：pSt_XLogInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析的日志信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Parse::ModuleProtocol_Parse_XLog(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_XLOGINFO* pSt_XLogInfo)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == lpszMsgBuffer) || (NULL == pSt_XLogInfo))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_ReaderBuilder;
	//解析JSON
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_ReaderBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMsgBuffer, lpszMsgBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}

	if (!st_JsonRoot["tszTableName"].isNull())
	{
		_tcscpy(pSt_XLogInfo->tszTableName, st_JsonRoot["tszTableName"].asCString());
	}
	if (!st_JsonRoot["tszLogBuffer"].isNull())
	{
		_tcscpy(pSt_XLogInfo->tszLogBuffer, st_JsonRoot["tszLogBuffer"].asCString());
	}
	if (!st_JsonRoot["nLogSize"].isNull())
	{
		pSt_XLogInfo->nLogSize = st_JsonRoot["nLogSize"].asInt();
	}
	if (!st_JsonRoot["tszTimeStart"].isNull())
	{
		_tcscpy(pSt_XLogInfo->tszTimeStart, st_JsonRoot["tszTimeStart"].asCString());
	}
	if (!st_JsonRoot["tszTimeEnd"].isNull())
	{
		_tcscpy(pSt_XLogInfo->tszTimeEnd, st_JsonRoot["tszTimeEnd"].asCString());
	}
	if (!st_JsonRoot["tszFileName"].isNull())
	{
		_tcscpy(pSt_XLogInfo->st_ProtocolLog.tszFileName, st_JsonRoot["tszFileName"].asCString());
	}
	if (!st_JsonRoot["tszFuncName"].isNull())
	{
		_tcscpy(pSt_XLogInfo->st_ProtocolLog.tszFuncName, st_JsonRoot["tszFuncName"].asCString());
	}
	if (!st_JsonRoot["tszLogTimer"].isNull())
	{
		_tcscpy(pSt_XLogInfo->st_ProtocolLog.tszLogTimer, st_JsonRoot["tszLogTimer"].asCString());
	}
	if (!st_JsonRoot["nLogLine"].isNull())
	{
		pSt_XLogInfo->st_ProtocolLog.nLogLine = st_JsonRoot["nLogLine"].asInt();
	}
	if (!st_JsonRoot["nLogLevel"].isNull())
	{
		pSt_XLogInfo->st_ProtocolLog.nLogLevel = st_JsonRoot["nLogLevel"].asInt();
	}
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Parse_QRCode
函数功能：二维码协议解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入数据大小
 参数.三：pSt_QRCode
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Parse::ModuleProtocol_Parse_QRCode(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_QRCODE* pSt_QRCode)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == lpszMsgBuffer) || (NULL == pSt_QRCode))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_ReaderBuilder;
	//解析JSON
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_ReaderBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMsgBuffer, lpszMsgBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}

	if (!st_JsonRoot["tszMsgBuffer"].isNull())
	{
		_tcscpy(pSt_QRCode->tszMsgBuffer, st_JsonRoot["tszMsgBuffer"].asCString());
	}
	if (!st_JsonRoot["tszFmtBuffer"].isNull())
	{
		_tcscpy(pSt_QRCode->tszFmtBuffer, st_JsonRoot["tszFmtBuffer"].asCString());
	}
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Parse_SocketTest
函数功能：套接字测试协议解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：pSt_SocketTest
 参数.三：pSt_QRCode
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Parse::ModuleProtocol_Parse_SocketTest(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_SOCKETTEST* pSt_SocketTest)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == lpszMsgBuffer) || (NULL == pSt_SocketTest))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_ReaderBuilder;
	//解析JSON
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_ReaderBuilder.newCharReader());
	if (!pSt_JsonReader->parse(lpszMsgBuffer, lpszMsgBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return FALSE;
	}

	if (!st_JsonRoot["tszAPIUrl"].isNull())
	{
		_tcscpy(pSt_SocketTest->tszAPIUrl, st_JsonRoot["tszAPIUrl"].asCString());
	}
	if (!st_JsonRoot["xhToken"].isNull())
	{
		pSt_SocketTest->xhToken = st_JsonRoot["xhToken"].asInt64();
	}
	if (!st_JsonRoot["bTCP"].isNull())
	{
		pSt_SocketTest->bTCP = st_JsonRoot["bTCP"].asBool();
	}
	if (!st_JsonRoot["bConn"].isNull())
	{
		pSt_SocketTest->bConn = st_JsonRoot["bConn"].asBool();
	}
	//链接
	if (!st_JsonRoot["tszAddr"].isNull())
	{
		_tcscpy(pSt_SocketTest->st_SocketConn.tszAddr, st_JsonRoot["tszAddr"].asCString());
	}
	if (!st_JsonRoot["nPort"].isNull())
	{
		pSt_SocketTest->st_SocketConn.nPort = st_JsonRoot["nPort"].asInt();
	}
	if (!st_JsonRoot["nCloseWaitContTime"].isNull())
	{
		pSt_SocketTest->st_SocketConn.nCloseWaitContTime = st_JsonRoot["nCloseWaitContTime"].asInt();
	}
	if (!st_JsonRoot["nConnectCount"].isNull())
	{
		pSt_SocketTest->st_SocketConn.nConnectCount = st_JsonRoot["nConnectCount"].asInt();
	}
	if (!st_JsonRoot["nConnectTest"].isNull())
	{
		pSt_SocketTest->st_SocketConn.nConnectTest = st_JsonRoot["nConnectTest"].asInt();
	}
	if (!st_JsonRoot["nContWaitTime"].isNull())
	{
		pSt_SocketTest->st_SocketConn.nContWaitTime = st_JsonRoot["nContWaitTime"].asInt();
	}
	//数据
	if (!st_JsonRoot["tszSDBuffer"].isNull())
	{
		_tcscpy(pSt_SocketTest->st_SocketData.tszSDBuffer, st_JsonRoot["tszSDBuffer"].asCString());
	}
	if (!st_JsonRoot["tszRVBuffer"].isNull())
	{
		_tcscpy(pSt_SocketTest->st_SocketData.tszRVBuffer, st_JsonRoot["tszRVBuffer"].asCString());
	}
	if (!st_JsonRoot["nRVLen"].isNull())
	{
		pSt_SocketTest->st_SocketData.nRVLen = st_JsonRoot["nRVLen"].asInt();
	}
	if (!st_JsonRoot["nSDLen"].isNull())
	{
		pSt_SocketTest->st_SocketData.nSDLen = st_JsonRoot["nSDLen"].asInt();
	}
	return TRUE;
}