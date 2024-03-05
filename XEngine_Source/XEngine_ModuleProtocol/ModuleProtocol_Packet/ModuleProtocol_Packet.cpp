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

	st_JsonRoot["code"] = nCode;
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
		st_JsonObject["tszProvincer"] = pSt_IDRegion->tszProvincer;
		st_JsonObject["tszCity"] = pSt_IDRegion->tszCity;
		st_JsonObject["tszCounty"] = pSt_IDRegion->tszCounty;
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
		st_JsonObject["tszBankName"] = pSt_BankInfo->tszBankName;
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
		st_JsonObject["tszFromStr"] = pSt_LanguageInfo->tszFromStr;
		st_JsonObject["tszToStr"] = pSt_LanguageInfo->tszToStr;
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
函数名称：ModuleProtocol_Packet_WordFilter
函数功能：敏感词生成协议打包函数
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
 参数.三：pSt_WordFilter
  In/Out：In
  类型：数据结构
  可空：N
  意思：输入要打包的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_WordFilter(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_WORDFILTER* pSt_WordFilter)
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

	st_JsonObject["tszWordsFrom"] = pSt_WordFilter->tszWordsFrom;
	st_JsonObject["tszWordsTo"] = pSt_WordFilter->tszWordsTo;
	st_JsonObject["nLevel"] = pSt_WordFilter->nLevel;

	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_ImageAttr
函数功能：图片属性打包
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
 参数.三：pSt_BaseInfo
  In/Out：In
  类型：数据结构
  可空：N
  意思：输入要打包的信息
 参数.四：pSt_ExtAttr
  In/Out：In
  类型：数据结构
  可空：N
  意思：输入要打包的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_ImageAttr(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IMGBASEATTR* pSt_BaseInfo, XENGINE_IMGEXTATTR* pSt_ExtAttr)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonBase;
	Json::Value st_JsonExt;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonBase["nWidth"] = pSt_BaseInfo->nWidth;
	st_JsonBase["nHeigth"] = pSt_BaseInfo->nHeigth;
	st_JsonBase["nChannel"] = pSt_BaseInfo->nChannel;

	st_JsonExt["nDepth"] = pSt_ExtAttr->nDepth;
	st_JsonExt["nItem"] = pSt_ExtAttr->nItem;
	st_JsonExt["nSize"] = pSt_ExtAttr->nSize;
	st_JsonExt["nType"] = pSt_ExtAttr->nType;

	st_JsonRoot["st_BaseInfo"] = st_JsonBase;
	st_JsonRoot["st_ExtInfo"] = st_JsonExt;

	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_EnumDevice
函数功能：打包枚举的设备信息
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
 参数.三：pppSt_AudioList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的音频设备信息
 参数.四：pppSt_VideoList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的视频设备信息
 参数.五：nACount
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入音频设备个数
 参数.六：nVCount
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入视频设备个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_EnumDevice(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, AVHELP_DEVICEINFO*** pppSt_AudioList, AVHELP_DEVICEINFO*** pppSt_VideoList, int nACount, int nVCount)
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
	Json::Value st_JsonVideo;
	Json::Value st_JsonAudio;
	Json::StreamWriterBuilder st_JsonBuilder;

	for (int i = 0; i < nACount; i++)
	{
		Json::Value st_JsonObject;
		st_JsonObject["nDeviceInout"] = (*pppSt_AudioList)[i]->nDeviceInout;
		st_JsonObject["nDeviceType"] = (*pppSt_AudioList)[i]->nDeviceType;
		st_JsonObject["tszName"] = (*pppSt_AudioList)[i]->st_MetaInfo.tszKey;
		st_JsonAudio.append(st_JsonObject);
	}
	for (int i = 0; i < nVCount; i++)
	{
		Json::Value st_JsonObject;
		st_JsonObject["nDeviceInout"] = (*pppSt_VideoList)[i]->nDeviceInout;
		st_JsonObject["nDeviceType"] = (*pppSt_VideoList)[i]->nDeviceType;
		st_JsonObject["tszName"] = (*pppSt_VideoList)[i]->st_MetaInfo.tszKey;
		st_JsonVideo.append(st_JsonObject);
	}
	st_JsonArray["AArray"] = st_JsonAudio;
	st_JsonArray["VArray"] = st_JsonVideo;
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonArray;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_ListFile
函数功能：打包文件列表信息
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
 参数.三：pppszFileList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的文件列表
 参数.四：nListCount
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_ListFile(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** pppszFileList, int nListCount)
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
		st_JsonObject["FileName"] = (*pppszFileList)[i];
		st_JsonArray.append(st_JsonObject);
	}
	st_JsonRoot["Count"] = nListCount;
	st_JsonRoot["data"] = st_JsonArray;
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);

	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_HardWare
函数功能：获取硬件信息
 参数.一：ptszHWInfo
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出获取到的数据,这个数据是JSON格式
 参数.二：pInt_Len
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：导出数据的长度
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_HardWare(XCHAR* ptszHWInfo, int* pInt_Len)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszHWInfo) || (NULL == pInt_Len))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return false;
	}
	int nDiskNumber = 0;
	XCHAR** pptszRootName;
	XCHAR tszOSName[MAX_PATH];
	XCHAR tszOSVersion[MAX_PATH];
	XCHAR tszOSBuild[MAX_PATH];
	XLONG nOSPro = 0;
	XCHAR tszOSInfo[2048];
	SYSTEMAPI_DISK_INFOMATION st_DiskInfo;
	SYSTEMAPI_CPU_INFOMATION st_CPUInfo;
	SYSTEMAPI_MEMORY_INFOMATION st_MemoryInfo;
	SYSTEMAPI_SERIAL_INFOMATION st_SDKSerial;

	memset(tszOSName, '\0', sizeof(tszOSName));
	memset(tszOSVersion, '\0', sizeof(tszOSVersion));
	memset(tszOSBuild, '\0', sizeof(tszOSBuild));
	memset(tszOSInfo, '\0', sizeof(tszOSInfo));
	memset(&st_MemoryInfo, '\0', sizeof(SYSTEMAPI_MEMORY_INFOMATION));
	memset(&st_CPUInfo, '\0', sizeof(SYSTEMAPI_CPU_INFOMATION));
	memset(&st_DiskInfo, '\0', sizeof(SYSTEMAPI_DISK_INFOMATION));
	memset(&st_SDKSerial, '\0', sizeof(SYSTEMAPI_SERIAL_INFOMATION));

	if (!SystemApi_HardWare_GetDiskNumber(&pptszRootName, &nDiskNumber))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = SystemApi_GetLastError();
		return false;
	}
	BaseLib_OperatorMemory_Free((XPPPMEM)&pptszRootName, nDiskNumber);

	XCHAR tszDriveStr[MAX_PATH];
	memset(tszDriveStr, '\0', MAX_PATH);

#ifdef _MSC_BUILD
	GetLogicalDriveStringsA(MAX_PATH, tszDriveStr);
#else
	LPCXSTR lpszDir = _X("/");
	strcpy(tszDriveStr, lpszDir);
#endif

	if (!SystemApi_HardWare_GetDiskInfomation(tszDriveStr, &st_DiskInfo, XENGINE_SYSTEMSDK_API_SYSTEM_SIZE_MB))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = SystemApi_GetLastError();
		return false;
	}
	if (!SystemApi_HardWare_GetCpuInfomation(&st_CPUInfo))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = SystemApi_GetLastError();
		return false;
	}
	if (!SystemApi_System_GetMemoryUsage(&st_MemoryInfo, XENGINE_SYSTEMSDK_API_SYSTEM_SIZE_MB))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = SystemApi_GetLastError();
		return false;
	}
	if (!SystemApi_HardWare_GetSerial(&st_SDKSerial))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = SystemApi_GetLastError();
		return false;
	}
	if (!SystemApi_System_GetSystemVer(tszOSName, tszOSVersion, tszOSBuild, &nOSPro))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = SystemApi_GetLastError();
		return false;
	}

	Json::Value st_JsonRoot;
	Json::Value st_JsonDisk;
	Json::Value st_JsonCpu;
	Json::Value st_JsonSerial;
	Json::Value st_JsonMemory;
	Json::Value st_JsonNetCard;

	st_JsonDisk["DiskNumber"] = nDiskNumber;
	st_JsonDisk["DiskFree"] = (Json::UInt64)st_DiskInfo.dwDiskFree;
	st_JsonDisk["DiskTotal"] = (Json::UInt64)st_DiskInfo.dwDiskTotal;
	st_JsonDisk["DiskName"] = tszDriveStr;

	st_JsonCpu["CpuNumber"] = st_CPUInfo.nCpuNumber;
	st_JsonCpu["CpuSpeed"] = st_CPUInfo.nCpuSpeed;
	st_JsonCpu["CpuName"] = st_CPUInfo.tszCpuName;

	st_JsonMemory["MemoryFree"] = (Json::UInt64)st_MemoryInfo.dwMemory_Free;
	st_JsonMemory["MemoryTotal"] = (Json::UInt64)st_MemoryInfo.dwMemory_Total;

	st_JsonSerial["DiskSerial"] = st_SDKSerial.tszDiskSerial;
	st_JsonSerial["CpuSerial"] = st_SDKSerial.tszCpuSerial;
	st_JsonSerial["BoardSerial"] = st_SDKSerial.tszBoardSerial;
	st_JsonSerial["SystemSerail"] = st_SDKSerial.tszSystemSerail;

	int nListCount = 0;
	XSOCKET_CARDINFO** ppSt_ListIFInfo;
	XSocket_Api_GetCardInfo(&ppSt_ListIFInfo, &nListCount);
	for (int i = 0; i < nListCount; i++)
	{
		Json::Value st_JsonIPAddr;
		st_JsonIPAddr["tszIFName"] = ppSt_ListIFInfo[i]->tszIFName;
		st_JsonIPAddr["tszIPAddr"] = ppSt_ListIFInfo[i]->tszIPAddr;
		st_JsonIPAddr["tszBroadAddr"] = ppSt_ListIFInfo[i]->tszBroadAddr;
		st_JsonIPAddr["tszDnsAddr"] = ppSt_ListIFInfo[i]->tszDnsAddr;
		st_JsonIPAddr["tszMacAddr"] = ppSt_ListIFInfo[i]->tszMacAddr;
		st_JsonNetCard.append(st_JsonIPAddr);
	}
	BaseLib_OperatorMemory_Free((XPPPMEM)&ppSt_ListIFInfo, nListCount);

	st_JsonRoot["Disk"] = st_JsonDisk;
	st_JsonRoot["Cpu"] = st_JsonCpu;
	st_JsonRoot["Memory"] = st_JsonMemory;
	st_JsonRoot["Serial"] = st_JsonSerial;
	st_JsonRoot["NetCard"] = st_JsonNetCard;

	sprintf(tszOSInfo, "%s %s %s %lu", tszOSName, tszOSVersion, tszOSBuild, nOSPro);
	st_JsonRoot["Platfrom"] = tszOSInfo;

	*pInt_Len = st_JsonRoot.toStyledString().length();
	memcpy(ptszHWInfo, st_JsonRoot.toStyledString().c_str(), *pInt_Len);

	return true;
}
/********************************************************************
函数名称：XControl_Info_SoftWare
函数功能：获取软件系统信息
 参数.一：ptszSWInfo
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出系统信息JSON结构
 参数.二：pInt_Len
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：导出系统信息长度
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_SoftWare(XCHAR* ptszSWInfo, int* pInt_Len)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszSWInfo) || (NULL == pInt_Len))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_PARAMENT;
		return false;
	}
	int nProcessCount;
	XLONG nOSProcessor;
	XCHAR tszOSBuild[MAX_PATH];
	XCHAR tszOSVersion[MAX_PATH];
	XCHAR tszOSInfo[MAX_PATH];
	XCHAR tszUPTime[MAX_PATH];
	XCHAR tszOSUser[MAX_PATH];
	XCHAR tszServicePacket[MAX_PATH];
	XENGINE_LIBTIMER st_LibTimer;

	memset(tszOSBuild, '\0', MAX_PATH);
	memset(tszOSVersion, '\0', MAX_PATH);
	memset(tszOSInfo, '\0', MAX_PATH);
	memset(tszUPTime, '\0', MAX_PATH);
	memset(tszOSUser, '\0', MAX_PATH);
	memset(tszServicePacket, '\0', MAX_PATH);
	memset(&st_LibTimer, '\0', sizeof(XENGINE_LIBTIMER));

#ifdef _MSC_BUILD
	XLONG dwMaxSize = MAX_PATH;
	if (!GetComputerNameA(tszOSUser, &dwMaxSize))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_GETNAME;
		return false;
	}
#else
	struct passwd* pSt_Passwd = NULL;
	pSt_Passwd = getpwuid(getuid());
	if (NULL == pSt_Passwd)
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PARSE_GETNAME;
		return false;
	}
	strcpy(tszOSUser, pSt_Passwd->pw_name);
#endif
	if (!SystemApi_System_GetSystemVer(tszOSInfo, tszOSVersion, tszOSBuild, &nOSProcessor))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = SystemApi_GetLastError();
		return false;
	}
	if (!SystemApi_System_GetProcessCount(&nProcessCount))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = SystemApi_GetLastError();
		return false;
	}
	if (!SystemApi_System_GetUpTime(&st_LibTimer))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = SystemApi_GetLastError();
		return false;
	}
	sprintf(tszUPTime, "%04d-%02d-%02d %02d:%02d:%02d", st_LibTimer.wYear, st_LibTimer.wMonth, st_LibTimer.wDay, st_LibTimer.wHour, st_LibTimer.wMinute, st_LibTimer.wSecond);

	Json::Value st_JsonRoot;
	Json::Value st_JsonSystem;

	st_JsonSystem["OSUser"] = tszOSUser;
	st_JsonSystem["OSUPTime"] = tszUPTime;
	st_JsonSystem["OSVersion"] = tszOSInfo;
	st_JsonSystem["OSProcessCount"] = nProcessCount;
	st_JsonRoot["OSInfo"] = st_JsonSystem;

	*pInt_Len = st_JsonRoot.toStyledString().length();
	memcpy(ptszSWInfo, st_JsonRoot.toStyledString().c_str(), *pInt_Len);

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
函数名称：ModuleProtocol_Packet_P2PWList
函数功能：打包公有地址列表
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
 参数.三：ppptszListAddr
  In/Out：In
  类型：三级指针
  可空：N
  意思：客户端列表
 参数.四：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_P2PWList(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** ppptszListAddr, int nListCount)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = false;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	//打包成JSON数据
	int nCount = 0;
	Json::Value st_JsonRoot;
	Json::Value st_JsonArray;

	for (int i = 0; i < nListCount; i++)
	{
		Json::Value st_JsonObject;
		st_JsonObject["tszWAddr"] = (*ppptszListAddr)[i];
		st_JsonArray.append(st_JsonObject);
	}
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "sucess";
	st_JsonRoot["ClientArray"] = st_JsonArray;
	st_JsonRoot["ClientCount"] = nCount;

	*pInt_MsgLen = st_JsonRoot.toStyledString().length();
	memcpy(ptszMsgBuffer, st_JsonRoot.toStyledString().c_str(), *pInt_MsgLen);
	return true;
}