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
函数名称：ModuleProtocol_Packet_IDRegion
函数功能：ID区域转换
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
 参数.三：pSt_IDRegion
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
 参数.四：nIDRegion
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入要打包的ID
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_IDRegion(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDREGION* pSt_IDRegion, int nIDRegion)
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

	st_JsonObject["tszProvincer"] = pSt_IDRegion->tszProvincer;
	st_JsonObject["tszCity"] = pSt_IDRegion->tszCity;
	st_JsonObject["tszCounty"] = pSt_IDRegion->tszCounty;
	st_JsonObject["nIDRegion"] = nIDRegion;

	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
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

	* pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
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
函数名称：ModuleProtocol_Packet_LogShow
函数功能：日志表名打包
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
 参数.三：ppptszList
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
bool CModuleProtocol_Packet::ModuleProtocol_Packet_LogShow(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** ppptszList, int nListCount)
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

		st_JsonObject["tszTableName"] = (*ppptszList)[i];
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
函数名称：ModuleProtocol_Packet_Weather
函数功能：天气信息协议打包函数
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
 参数.三：pSt_WeatherInfo
  In/Out：In
  类型：数据结构
  可空：N
  意思：输入要打包的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_Weather(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_WEATHERINFO* pSt_WeatherInfo)
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

	st_JsonObject["nHumidity"] = pSt_WeatherInfo->nHumidity;
	st_JsonObject["nTemperature"] = pSt_WeatherInfo->nTemperature;
	st_JsonObject["tszCity"] = pSt_WeatherInfo->tszCity;
	st_JsonObject["tszProvince"] = pSt_WeatherInfo->tszProvince;
	st_JsonObject["tszUPTime"] = pSt_WeatherInfo->tszUPTime;
	st_JsonObject["tszWeatherStr"] = pSt_WeatherInfo->tszWeatherStr;
	st_JsonObject["tszWinddiRection"] = pSt_WeatherInfo->tszWinddiRection;
	st_JsonObject["tszWindPowerStr"] = pSt_WeatherInfo->tszWindPowerStr;

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
函数名称：ModuleProtocol_Packet_ShortLinkList
函数功能：短链接列表打包函数
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
 参数.三：pppSt_MachineList
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
bool CModuleProtocol_Packet::ModuleProtocol_Packet_ShortLinkList(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_SHORTLINK*** pppSt_ShortLink, int nListCount)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
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

		st_JsonObject["tszFullUrl"] = (*pppSt_ShortLink)[i]->tszFullUrl;
		st_JsonObject["tszShotUrl"] = (*pppSt_ShortLink)[i]->tszShotUrl;
		st_JsonObject["tszKeyUrl"] = (*pppSt_ShortLink)[i]->tszKeyUrl;
		st_JsonObject["tszMapUrl"] = (*pppSt_ShortLink)[i]->tszMapUrl;
		st_JsonObject["tszCvtUrl"] = (*pppSt_ShortLink)[i]->tszCvtUrl;
		st_JsonObject["tszCreateTime"] = (*pppSt_ShortLink)[i]->tszCreateTime;
		st_JsonObject["nLength"] = (*pppSt_ShortLink)[i]->nLength;
		st_JsonObject["nID"] = (*pppSt_ShortLink)[i]->nID;
		st_JsonArray.append(st_JsonObject);
	}
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonArray;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MSGLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);
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
函数名称：ModuleProtocol_Packet_WordFilterList
函数功能：敏感词列表打包函数
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
 参数.三：pppSt_MachineList
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
bool CModuleProtocol_Packet::ModuleProtocol_Packet_WordFilterList(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_WORDFILTER*** pppSt_WordFilter, int nListCount)
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

		st_JsonObject["tszWordsFrom"] = (*pppSt_WordFilter)[i]->tszWordsFrom;
		st_JsonObject["tszWordsTo"] = (*pppSt_WordFilter)[i]->tszWordsTo;
		st_JsonObject["nLevel"] = (*pppSt_WordFilter)[i]->nLevel;
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
函数名称：ModuleProtocol_Packet_ImageText
函数功能：图片文本识别打包
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
 参数.三：pppListStr
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的文本列表
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
bool CModuleProtocol_Packet::ModuleProtocol_Packet_ImageText(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** pppListStr, int nListCount)
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
		st_JsonObject["TextStr"] = (*pppListStr)[i];
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
		st_JsonObject["tszName"] = (*pppSt_AudioList)[i]->st_MetaInfo.tszStrKey;
		st_JsonAudio.append(st_JsonObject);
	}
	for (int i = 0; i < nVCount; i++)
	{
		Json::Value st_JsonObject;
		st_JsonObject["nDeviceInout"] = (*pppSt_VideoList)[i]->nDeviceInout;
		st_JsonObject["nDeviceType"] = (*pppSt_VideoList)[i]->nDeviceType;
		st_JsonObject["tszName"] = (*pppSt_VideoList)[i]->st_MetaInfo.tszStrKey;
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
函数名称：ModuleProtocol_Packet_Machine
函数功能：机器信息列表打包函数
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
 参数.三：pppSt_MachineList
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
bool CModuleProtocol_Packet::ModuleProtocol_Packet_Machine(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_MACHINEINFO*** pppSt_MachineList, int nListCount)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
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

		st_JsonObject["tszMachineSoftware"] = (*pppSt_MachineList)[i]->tszMachineSoftware;
		st_JsonObject["tszMachineHardware"] = (*pppSt_MachineList)[i]->tszMachineHardware;
		st_JsonObject["tszMachineName"] = (*pppSt_MachineList)[i]->tszMachineName;
		st_JsonObject["tszMachineUser"] = (*pppSt_MachineList)[i]->tszMachineUser;
		st_JsonObject["tszMachineCode"] = (*pppSt_MachineList)[i]->tszMachineCode;
		st_JsonObject["tszMachineSystem"] = (*pppSt_MachineList)[i]->tszMachineSystem;
		st_JsonObject["tszCreateTime"] = (*pppSt_MachineList)[i]->tszCreateTime;
		st_JsonObject["nTimeNumber"] = (Json::Value::UInt64)(*pppSt_MachineList)[i]->nTimeNumber;
		st_JsonObject["nID"] = (*pppSt_MachineList)[i]->nID;
		st_JsonArray.append(st_JsonObject);
	}
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonArray;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MSGLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_OilInfo
函数功能：油价信息打包函数
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
 参数.三：pSt_OilInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_OilInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_OILINFO* pSt_OilInfo)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonObject["tszCityStr"] = pSt_OilInfo->tszCityStr;
	st_JsonObject["dlValue0"] = pSt_OilInfo->dlValue0;
	st_JsonObject["dlValue10"] = pSt_OilInfo->dlValue10;
	st_JsonObject["dlValue20"] = pSt_OilInfo->dlValue20;
	st_JsonObject["dlValue35"] = pSt_OilInfo->dlValue35;
	st_JsonObject["dlValue92"] = pSt_OilInfo->dlValue92;
	st_JsonObject["dlValue95"] = pSt_OilInfo->dlValue95;
	st_JsonObject["dlValue98"] = pSt_OilInfo->dlValue98;
	st_JsonObject["tszUPTime"] = pSt_OilInfo->tszUPTime;

	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MSGLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_PhoneInfo
函数功能：电话号码信息打包函数
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
 参数.三：pSt_PhoneInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_PhoneInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_PHONEINFO* pSt_PhoneInfo)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonObject["tszAreaCode"] = pSt_PhoneInfo->tszAreaCode;
	st_JsonObject["tszCity"] = pSt_PhoneInfo->tszCity;
	st_JsonObject["tszISPName"] = pSt_PhoneInfo->tszISPName;
	st_JsonObject["tszPhoneNumber"] = pSt_PhoneInfo->tszPhoneNumber;
	st_JsonObject["tszProvincer"] = pSt_PhoneInfo->tszProvincer;

	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MSGLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_IPAddr
函数功能：IP地址信息打包函数
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
 参数.三：pSt_PhoneInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_IPAddr(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_IPADDRINFO* pSt_IPAddrInfo)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonObject["tszIPAddr"] = pSt_IPAddrInfo->tszIPAddr;
	st_JsonObject["tszIPContinent"] = pSt_IPAddrInfo->tszIPContinent;
	st_JsonObject["tszIPCountry"] = pSt_IPAddrInfo->tszIPCountry;
	st_JsonObject["tszIPProvince"] = pSt_IPAddrInfo->tszIPProvince;
	st_JsonObject["tszIPCity"] = pSt_IPAddrInfo->tszIPCity;
	st_JsonObject["tszIPISP"] = pSt_IPAddrInfo->tszIPISP;
	st_JsonObject["tszTimezone"] = pSt_IPAddrInfo->tszTimezone;
	st_JsonObject["dlLatitude"] = pSt_IPAddrInfo->dlLatitude;
	st_JsonObject["dlLongitude"] = pSt_IPAddrInfo->dlLongitude;

	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MSGLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	BaseLib_Charset_AnsiToUTF(Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), ptszMSGBuffer, pInt_MSGLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_MacInfo
函数功能：MAC地址信息打包函数
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
 参数.三：pSt_PhoneInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_MacInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_MACADDRINFO* pSt_MacInfo)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonObject["bPrivate"] = pSt_MacInfo->bPrivate;
	st_JsonObject["tszBlockType"] = pSt_MacInfo->tszBlockType;
	st_JsonObject["tszMACPrefix"] = pSt_MacInfo->tszMACPrefix;
	st_JsonObject["tszUPTime"] = pSt_MacInfo->tszUPTime;
	st_JsonObject["tszVendorName"] = pSt_MacInfo->tszVendorName;

	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MSGLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);
	return true;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_BackNotify
函数功能：后台服务通知协议
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
  可空：N
  意思：输入返回的值
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleProtocol_Packet::ModuleProtocol_Packet_BackNotify(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, int nCode, int nOPerator, LPCXSTR lpszSourceStr, LPCXSTR lpszDestStr, LPCXSTR lpszAPIStr)
{
	ModuleProtocol_IsErrorOccur = false;

	if ((NULL == ptszMSGBuffer) || (NULL == pInt_MSGLen))
	{
		ModuleProtocol_IsErrorOccur = true;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonObject["nOPerator"] = nOPerator;
	st_JsonObject["lpszSourceStr"] = lpszSourceStr;
	st_JsonObject["lpszDestStr"] = lpszDestStr;
	st_JsonObject["lpszAPIStr"] = lpszAPIStr;

	st_JsonRoot["code"] = nCode;
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_MSGLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMSGBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MSGLen);

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
		APIADDR_IPADDR st_LibAddr;
		P2XPPROTOCOL_LANPACKET st_LANPacket;

		memset(tszClientAddr, '\0', sizeof(tszClientAddr));
		memset(&st_LibAddr, '\0', sizeof(APIADDR_IPADDR));
		memset(&st_LANPacket, '\0', sizeof(P2XPPROTOCOL_LANPACKET));
		//分割
		APIAddr_IPAddr_IsIPV4Addr(stl_ListIterator->tszPrivateAddr, &st_LibAddr);
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