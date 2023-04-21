#include "pch.h"
#include "ModuleProtocol_Packet.h"
/********************************************************************
//    Created:     2022/02/28  14:10:32
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Packet\ModuleProtocol_Packet.cpp
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Packet
//    File Base:   ModuleProtocol_Packet
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     协议打包类
//    History:
*********************************************************************/
CModuleProtocol_Packet::CModuleProtocol_Packet()
{
}
CModuleProtocol_Packet::~CModuleProtocol_Packet()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleProtocol_Packet_Common
函数功能：公用协议打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打好包的缓冲区
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出缓冲区大小
 参数.三：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.四：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入要打包的后续内容
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_Common(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, int nCode /* = 0 */, LPCXSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;

	st_JsonRoot["code"] = 0;
	if (NULL != lpszMsgBuffer)
	{
		st_JsonRoot["msg"] = lpszMsgBuffer;
	}
	*pInt_MsgLen = st_JsonRoot.toStyledString().length();
	memcpy(ptszMsgBuffer, st_JsonRoot.toStyledString().c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_IDQuery
函数功能：ID查询打包为JSON的封包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的ID信息
 参数.四：pSt_IDRegion
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入ID地址信息
 参数.五：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.六：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_IDQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO* pSt_IDInfo, XENGINE_IDREGION* pSt_IDRegion, int nCode /* = 0 */, LPCXSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	if (0 == nCode)
	{
		st_JsonObject["tszIDNumber"] = pSt_IDInfo->tszIDNumber;
		st_JsonObject["nBirthYear"] = pSt_IDInfo->nBirthYear;
		st_JsonObject["nBirthMonth"] = pSt_IDInfo->nBirthMonth;
		st_JsonObject["nBirthDay"] = pSt_IDInfo->nBirthDay;
		st_JsonObject["nPoliceID"] = pSt_IDInfo->nPoliceID;
		st_JsonObject["nSex"] = pSt_IDInfo->nSex / 2 == 0 ? 0 : 1;
		st_JsonObject["nCheck"] = pSt_IDInfo->nCheck;

#ifdef _MSC_BUILD
		int nUTFLen = _tcsxlen(pSt_IDRegion->tszProvincer);
		XCHAR tszUTFBuffer[MAX_PATH];
		memset(tszUTFBuffer, '\0', MAX_PATH);

		BaseLib_OperatorCharset_AnsiToUTF(pSt_IDRegion->tszProvincer, tszUTFBuffer, &nUTFLen);
		st_JsonObject["tszProvincer"] = tszUTFBuffer;

		nUTFLen = _tcsxlen(pSt_IDRegion->tszCity);
		memset(tszUTFBuffer, '\0', MAX_PATH);
		BaseLib_OperatorCharset_AnsiToUTF(pSt_IDRegion->tszCity, tszUTFBuffer, &nUTFLen);
		st_JsonObject["tszCity"] = tszUTFBuffer;

		nUTFLen = _tcsxlen(pSt_IDRegion->tszCounty);
		memset(tszUTFBuffer, '\0', MAX_PATH);
		BaseLib_OperatorCharset_AnsiToUTF(pSt_IDRegion->tszCounty, tszUTFBuffer, &nUTFLen);
		st_JsonObject["tszCounty"] = tszUTFBuffer;
#else
		st_JsonObject["tszProvincer"] = pSt_IDRegion->tszProvincer;
		st_JsonObject["tszCity"] = pSt_IDRegion->tszCity;
		st_JsonObject["tszCounty"] = pSt_IDRegion->tszCounty;
#endif
	}

	st_JsonRoot["code"] = nCode;
	if (NULL == lpszMsgBuffer)
	{
		st_JsonRoot["msg"] = "success";
	}
	else
	{
		st_JsonRoot["msg"] = lpszMsgBuffer;
	}
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_BankQuery
函数功能：银行卡信息查询打包为JSON
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_BankInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.五：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_BankQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_BANKINFO* pSt_BankInfo, int nCode /* = 0 */, LPCXSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	if (0 == nCode)
	{
		st_JsonObject["tszBankNumber"] = pSt_BankInfo->tszBankNumber;
		st_JsonObject["tszBankAbridge"] = pSt_BankInfo->tszBankAbridge;
		st_JsonObject["enBankType"] = pSt_BankInfo->enBankType;

#ifdef _MSC_BUILD
		XCHAR tszUTFBuffer[MAX_PATH];
		memset(tszUTFBuffer, '\0', MAX_PATH);

		int nUTFLen = _tcsxlen(pSt_BankInfo->tszBankName);
		BaseLib_OperatorCharset_AnsiToUTF(pSt_BankInfo->tszBankName, tszUTFBuffer, &nUTFLen);
		st_JsonObject["tszBankName"] = tszUTFBuffer;
#else
		st_JsonObject["tszBankName"] = pSt_BankInfo->tszBankName;
#endif
	}

	st_JsonRoot["code"] = nCode;
	if (NULL == lpszMsgBuffer)
	{
		st_JsonRoot["msg"] = "success";
	}
	else
	{
		st_JsonRoot["msg"] = lpszMsgBuffer;
	}
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_LanguageQuery
函数功能：语言打包为JSON
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_LanguageInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.五：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_LanguageQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo, int nCode /* = 0 */, LPCXSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	if (0 == nCode)
	{
		st_JsonObject["tszSourceStr"] = pSt_LanguageInfo->tszSourceStr;
		st_JsonObject["tszDestStr"] = pSt_LanguageInfo->tszDestStr;
		st_JsonObject["enType"] = pSt_LanguageInfo->enType;
	}

	st_JsonRoot["code"] = nCode;
	if (NULL == lpszMsgBuffer)
	{
		st_JsonRoot["msg"] = "success";
	}
	else
	{
		st_JsonRoot["msg"] = lpszMsgBuffer;
	}
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_Locker
函数功能：分布式锁协议打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入要打包的数据
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.五：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_Locker(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, int nCode, LPCXSTR lpszMsgBuffer)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonObject["xhToken"] = (Json::Value::UInt64)xhToken;

	st_JsonRoot["code"] = nCode;
	if (NULL == lpszMsgBuffer)
	{
		st_JsonRoot["msg"] = "success";
	}
	else
	{
		st_JsonRoot["msg"] = lpszMsgBuffer;
	}
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_ZIPCode
函数功能：打包行政邮编信息协议
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_ZIPInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.五：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_ZIPCode(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_ZIPINFO* pSt_ZIPInfo, int nCode /* = 0 */, LPCXSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	if (0 == nCode)
	{
		st_JsonObject["dlLat"] = pSt_ZIPInfo->dlLat;
		st_JsonObject["dlLng"] = pSt_ZIPInfo->dlLng;
		st_JsonObject["nAreaCode"] = pSt_ZIPInfo->nAreaCode;
		st_JsonObject["nLevel"] = pSt_ZIPInfo->nLevel;
		st_JsonObject["nZipCode"] = pSt_ZIPInfo->nZipCode;
		st_JsonObject["tszCity"] = pSt_ZIPInfo->tszCity;
		st_JsonObject["tszCounty"] = pSt_ZIPInfo->tszCounty;
		st_JsonObject["tszPinYin"] = pSt_ZIPInfo->tszPinYin;
		st_JsonObject["tszProvincer"] = pSt_ZIPInfo->tszProvincer;
	}

	st_JsonRoot["code"] = nCode;
	if (NULL == lpszMsgBuffer)
	{
		st_JsonRoot["msg"] = "success";
	}
	else
	{
		st_JsonRoot["msg"] = lpszMsgBuffer;
	}
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_Log
函数功能：日志信息打包
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pppSt_XLogList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的数据
 参数.四：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：输入打包数据个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_Log(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_XLOGINFO*** pppSt_XLogList, int nListCount)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonArray;
	Json::StreamWriterBuilder st_JsonBuilder;

	for (int i = 0; i < nListCount; i++)
	{
		Json::Value st_JsonObject;

		st_JsonObject["tszTableName"] = (*pppSt_XLogList)[i]->tszTableName;
		st_JsonObject["tszLogBuffer"] = (*pppSt_XLogList)[i]->tszLogBuffer;
		st_JsonObject["nLogSize"] = (*pppSt_XLogList)[i]->nLogSize;

		st_JsonObject["tszFileName"] = (*pppSt_XLogList)[i]->st_ProtocolLog.tszFileName;
		st_JsonObject["tszFuncName"] = (*pppSt_XLogList)[i]->st_ProtocolLog.tszFuncName;
		st_JsonObject["tszLogTimer"] = (*pppSt_XLogList)[i]->st_ProtocolLog.tszLogTimer;
		st_JsonObject["nLogLine"] = (*pppSt_XLogList)[i]->st_ProtocolLog.nLogLine;
		st_JsonObject["nLogLevel"] = (*pppSt_XLogList)[i]->st_ProtocolLog.nLogLevel;
		st_JsonArray.append(st_JsonObject);
	}
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonArray;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_TestReport
函数功能：套接字测试信息打包
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入句柄
 参数.四：lpszIPAddr
  In/Out：In
  类型：常量字符指针
  可空：N
 参数.五：nIPPort
  In/Out：In
  类型：整数型
  可空：N
  意思：测试的端口
 参数.六：nNumber
  In/Out：In
  类型：整数型
  可空：N
  意思：测试的次数
 参数.七：nFailed
  In/Out：In
  类型：整数型
  可空：N
  意思：失败的次数
 参数.八：nSuccess
  In/Out：In
  类型：整数型
  可空：N
  意思：成功的次数
 参数.九：nStatus
  In/Out：In
  类型：整数型
  可空：N
  意思：运行状态
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_TestReport(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, LPCXSTR lpszIPAddr, int nIPPort, __int64x nNumber, __int64x nFailed, __int64x nSuccess, int nStatus)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonObject["lpszIPAddr"] = lpszIPAddr;
	st_JsonObject["nIPPort"] = nIPPort;
	st_JsonObject["xhToken"] = (Json::Value::Int64)xhToken;
	st_JsonObject["nNumber"] = (Json::Value::Int64)nNumber;
	st_JsonObject["nFailed"] = (Json::Value::Int64)nFailed;
	st_JsonObject["nSuccess"] = (Json::Value::Int64)nSuccess;
	st_JsonObject["nStatus"] = nStatus;

	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_TestReply
函数功能：请求返回
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入句柄
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_TestReply(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonObject["xhToken"] = (Json::Value::Int64)xhToken;

	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_ShortLink
函数功能：短连接生成协议打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_ShortLink
  In/Out：In
  类型：数据结构
  可空：N
  意思：输入要打包的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_ShortLink(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_SHORTLINK* pSt_ShortLink)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonObject["tszFullUrl"] = pSt_ShortLink->tszFullUrl;
	st_JsonObject["tszShotUrl"] = pSt_ShortLink->tszShotUrl;
	st_JsonObject["tszKeyUrl"] = pSt_ShortLink->tszKeyUrl;
	st_JsonObject["tszMapUrl"] = pSt_ShortLink->tszMapUrl;
	st_JsonObject["tszCvtUrl"] = pSt_ShortLink->tszCvtUrl;
	st_JsonObject["tszCreateTime"] = pSt_ShortLink->tszCreateTime;

	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_P2PLan
函数功能：响应同步局域网地址列表
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出封装好的缓冲区
 参数.二：pInt_MsgLen
  In/Out：In/Out
  类型：整数型指针
  可空：N
  意思：输入你的缓冲区大小,输出缓冲区真实大小
 参数.三：pppSt_ListClients
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入局域网地址信息列表
 参数.四：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：局域网地址列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_P2PLan(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL*** pppSt_ListClients, int nListCount)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == pppSt_ListClients) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = false;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonArray;
	for (int i = 0; i < nListCount; i++)
	{
		Json::Value st_JsonObject;
		st_JsonObject["ClientUser"] = (*pppSt_ListClients)[i]->tszUserName;
		st_JsonObject["ClientAddr"] = (*pppSt_ListClients)[i]->tszPrivateAddr;
		st_JsonArray.append(st_JsonObject);
	}
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "sucess";
	st_JsonRoot["ClientArray"] = st_JsonArray;
	st_JsonRoot["ClientCount"] = nListCount;

	*pInt_MsgLen = st_JsonRoot.toStyledString().length();
	memcpy(ptszMsgBuffer, st_JsonRoot.toStyledString().c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_P2PWLan
函数功能：响应同步局域网所有地址列表
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出封装好的缓冲区
 参数.二：pInt_MsgLen
  In/Out：In/Out
  类型：整数型指针
  可空：N
  意思：输入你的缓冲区大小,输出缓冲区真实大小
 参数.三：pStl_ListClients
  In/Out：In
  类型：容器指针
  可空：N
  意思：客户端列表
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_P2PWLan(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, list<XENGINE_P2XPPEER_PROTOCOL>* pStl_ListClients)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == pStl_ListClients) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = false;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	unordered_map<string, list<P2XPPROTOCOL_LANPACKET>> stl_MapClient;
	//首先处理公网下的局域网网段列表
	for (auto stl_ListIterator = pStl_ListClients->begin(); stl_ListIterator != pStl_ListClients->end(); stl_ListIterator++)
	{
		XCHAR tszClientAddr[128];
		XENGINE_LIBADDR st_LibAddr;
		P2XPPROTOCOL_LANPACKET st_LANPacket;

		memset(tszClientAddr, '\0', sizeof(tszClientAddr));
		memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
		memset(&st_LANPacket, '\0', sizeof(P2XPPROTOCOL_LANPACKET));
		//分割
		BaseLib_OperatorIPAddr_IsIPV4Addr(stl_ListIterator->tszPrivateAddr, &st_LibAddr);
		_xstprintf(tszClientAddr, _X("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);
		//赋值
		_tcsxcpy(st_LANPacket.tszUsername, stl_ListIterator->tszUserName);
		_tcsxcpy(st_LANPacket.tszClientAddr, stl_ListIterator->tszPrivateAddr);
		//判断是否存在
		unordered_map<string, list<P2XPPROTOCOL_LANPACKET>>::iterator stl_MapIterator = stl_MapClient.find(tszClientAddr);
		if (stl_MapIterator == stl_MapClient.end())
		{
			list<P2XPPROTOCOL_LANPACKET> stl_ListClient;

			stl_ListClient.push_back(st_LANPacket);
			stl_MapClient.insert(make_pair(tszClientAddr, stl_ListClient));
		}
		else
		{
			stl_MapIterator->second.push_back(st_LANPacket);
		}
	}
	//打包成JSON数据
	int nCount = 0;
	Json::Value st_JsonRoot;
	Json::Value st_JsonArray;

	for (auto stl_MapIterator = stl_MapClient.begin(); stl_MapIterator != stl_MapClient.end(); stl_MapIterator++)
	{
		Json::Value st_JsonList;
		for (auto stl_ListIterator = stl_MapIterator->second.begin(); stl_ListIterator != stl_MapIterator->second.end(); stl_ListIterator++)
		{
			Json::Value st_JsonObject;

			nCount++;
			st_JsonObject["ClientUser"] = stl_ListIterator->tszUsername;
			st_JsonObject["ClientAddr"] = stl_ListIterator->tszClientAddr;
			st_JsonList.append(st_JsonObject);
		}
		st_JsonArray["tszLANAddr"] = stl_MapIterator->first.c_str();
		st_JsonArray["tszLANList"] = st_JsonList;
	}
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "sucess";
	st_JsonRoot["ClientArray"] = st_JsonArray;
	st_JsonRoot["ClientCount"] = nCount;

	*pInt_MsgLen = st_JsonRoot.toStyledString().length();
	memcpy(ptszMsgBuffer, st_JsonRoot.toStyledString().c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_P2PUser
函数功能：响应用户查询用户信息的请求协议封包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出封装好的缓冲区
 参数.二：pInt_MsgLen
  In/Out：In/Out
  类型：整数型指针
  可空：N
  意思：输入你的缓冲区大小,输出缓冲区真实大小
 参数.三：pSt_PeerInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入获取到的用户信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_P2PUser(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL* pSt_PeerInfo)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == pSt_PeerInfo) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = false;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonAddr;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonRoot["Code"] = 0;
	st_JsonRoot["msg"] = "sucess";
	st_JsonRoot["dwConnectType"] = (Json::Value::UInt)pSt_PeerInfo->dwConnectType;
	st_JsonRoot["dwPeerType"] = pSt_PeerInfo->dwPeerType;
	st_JsonRoot["tszConnectAddr"] = pSt_PeerInfo->tszConnectAddr;
	st_JsonRoot["tszPrivateAddr"] = pSt_PeerInfo->tszPrivateAddr;
	st_JsonRoot["tszPublicAddr"] = pSt_PeerInfo->tszPublicAddr;
	st_JsonRoot["tszUserName"] = pSt_PeerInfo->tszUserName;

	st_JsonBuilder["emitUTF8"] = true;
	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_P2PConnect
函数功能：请求连接打包函数
 参数.一：pSt_ProtocolHdr
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的协议头
 参数.二：pSt_IOProtocol
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入连接信息
 参数.三：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出封装好的缓冲区
 参数.四：pInt_MsgLen
  In/Out：In/Out
  类型：整数型指针
  可空：N
  意思：输入你的缓冲区大小,输出缓冲区真实大小
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_P2PConnect(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPIO_PROTOCOL* pSt_IOProtocol)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = false;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;

	st_JsonRoot["tszSourceUser"] = pSt_IOProtocol->tszSourceUser;
	st_JsonRoot["tszDestUser"] = pSt_IOProtocol->tszDestUser;
	st_JsonRoot["tszConnectAddr"] = pSt_IOProtocol->tszConnectAddr;
	st_JsonRoot["nDestPort"] = pSt_IOProtocol->nDestPort;
	st_JsonRoot["bIsTcp"] = pSt_IOProtocol->bIsTcp;

	*pInt_MsgLen = st_JsonRoot.toStyledString().length();
	memcpy(ptszMsgBuffer, st_JsonRoot.toStyledString().c_str(), *pInt_MsgLen);
	return true;
}