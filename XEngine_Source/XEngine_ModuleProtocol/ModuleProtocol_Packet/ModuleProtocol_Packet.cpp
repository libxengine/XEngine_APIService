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
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_Common(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, int nCode /* = 0 */, LPCTSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;

	st_JsonRoot["code"] = 0;
	if (NULL != lpszMsgBuffer)
	{
		st_JsonRoot["msg"] = lpszMsgBuffer;
	}
	*pInt_MsgLen = st_JsonRoot.toStyledString().length();
	memcpy(ptszMsgBuffer, st_JsonRoot.toStyledString().c_str(), *pInt_MsgLen);
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_IPQuery
函数功能：IP地址查询打包协议
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
 参数.三：pSt_IPAddrInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的IP地址信息
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
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_IPQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IPADDRINFO* pSt_IPAddrInfo, int nCode /* = 0 */, LPCTSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen) || (NULL == pSt_IPAddrInfo))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	if (0 == nCode)
	{
		st_JsonObject["tszIPAddr"] = pSt_IPAddrInfo->tszIPAddr;
		st_JsonObject["tszIPStart"] = pSt_IPAddrInfo->tszIPStart;
		st_JsonObject["tszIPEnd"] = pSt_IPAddrInfo->tszIPEnd;
		st_JsonObject["tszIPCountry"] = pSt_IPAddrInfo->tszIPCountry;
		st_JsonObject["tszIPProvince"] = pSt_IPAddrInfo->tszIPProvince;
		st_JsonObject["tszIPCity"] = pSt_IPAddrInfo->tszIPCity;
		st_JsonObject["tszIPCounty"] = pSt_IPAddrInfo->tszIPCounty;
		st_JsonObject["tszIPAddress"] = pSt_IPAddrInfo->tszIPAddress;
		st_JsonObject["tszIPISP"] = pSt_IPAddrInfo->tszIPISP;
		st_JsonObject["tszIPTime"] = pSt_IPAddrInfo->tszIPTime;
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
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_IPQuery2
函数功能：IP查询打包函数另一种方式
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
 参数.三：pSt_IPAddrInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的IP地址信息
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_IPQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IPADDRINFO* pSt_IPAddrInfo, int nCode /* = 0 */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen) || (NULL == pSt_IPAddrInfo))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	*pInt_MsgLen = _stprintf(ptszMsgBuffer, "%d\r\n"
		"%s\r\n"
		"%s\r\n"
		"%s\r\n"
		"%s\r\n"
		"%s\r\n"
		"%s\r\n"
		"%s\r\n"
		"%s\r\n"
		"%s\r\n"
		"%s", nCode, pSt_IPAddrInfo->tszIPAddr, pSt_IPAddrInfo->tszIPStart, pSt_IPAddrInfo->tszIPEnd, pSt_IPAddrInfo->tszIPCountry, pSt_IPAddrInfo->tszIPProvince, pSt_IPAddrInfo->tszIPCity, pSt_IPAddrInfo->tszIPCounty, pSt_IPAddrInfo->tszIPAddress, pSt_IPAddrInfo->tszIPISP, pSt_IPAddrInfo->tszIPTime);
	return TRUE;
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
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_IDQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO* pSt_IDInfo, XENGINE_IDREGION* pSt_IDRegion, int nCode /* = 0 */, LPCTSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
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
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_IDQuery2
函数功能：ID查询打包为字符串流函数
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
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_IDQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO* pSt_IDInfo, XENGINE_IDREGION* pSt_IDRegion, int nCode /* = 0 */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	*pInt_MsgLen = _stprintf(ptszMsgBuffer, "%d\r\n"
		"%s\r\n"
		"%d\r\n"
		"%d\r\n"
		"%d\r\n"
		"%d\r\n"
		"%d\r\n"
		"%s\r\n"
		"%s\r\n"
		"%s", nCode, pSt_IDInfo->tszIDNumber, pSt_IDInfo->nBirthYear, pSt_IDInfo->nBirthMonth, pSt_IDInfo->nBirthDay, pSt_IDInfo->nPoliceID, pSt_IDInfo->nSex / 2 == 0 ? 0 : 1, pSt_IDRegion->tszProvincer, pSt_IDRegion->tszCity, pSt_IDRegion->tszCounty);
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_PhoneQuery
函数功能：电话信息查询打包为JSON的封包函数
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
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的信息
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
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_PhoneQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_PHONEINFO* pSt_PhoneInfo, int nCode /* = 0 */, LPCTSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	if (0 == nCode)
	{
		st_JsonObject["nPhoneNumber"] = (Json::Value::Int64)pSt_PhoneInfo->nPhoneNumber;
		st_JsonObject["tszProvincer"] = pSt_PhoneInfo->tszProvincer;
		st_JsonObject["tszCity"] = pSt_PhoneInfo->tszCity;
		st_JsonObject["nZipCode"] = pSt_PhoneInfo->nZipCode;
		st_JsonObject["nAreaCode"] = pSt_PhoneInfo->nAreaCode;
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
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_PhoneQuery2
函数功能：电话查询打包为字符串流函数
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
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的信息
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_PhoneQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_PHONEINFO* pSt_PhoneInfo, int nCode /* = 0 */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	*pInt_MsgLen = _stprintf(ptszMsgBuffer, "%d\r\n"
		"%lld\r\n"
		"%s\r\n"
		"%s\r\n"
		"%d\r\n"
		"%d", nCode, pSt_PhoneInfo->nPhoneNumber, pSt_PhoneInfo->tszProvincer, pSt_PhoneInfo->tszCity, pSt_PhoneInfo->nZipCode, pSt_PhoneInfo->nAreaCode);
	return TRUE;
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
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_BankQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_BANKINFO* pSt_BankInfo, int nCode /* = 0 */, LPCTSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	if (0 == nCode)
	{
		st_JsonObject["tszBankNumber"] = pSt_BankInfo->tszBankNumber;
		st_JsonObject["tszBankName"] = pSt_BankInfo->tszBankName;
		st_JsonObject["tszBankAbridge"] = pSt_BankInfo->tszBankAbridge;
		st_JsonObject["enBankType"] = pSt_BankInfo->enBankType;
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
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_BankQuery2
函数功能：银行卡信息查询打包为字节流
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
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的信息
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_BankQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_BANKINFO* pSt_BankInfo, int nCode /* = 0 */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	*pInt_MsgLen = _stprintf(ptszMsgBuffer, "%d\r\n"
		"%s\r\n"
		"%s\r\n"
		"%s\r\n"
		"%d", nCode, pSt_BankInfo->tszBankNumber, pSt_BankInfo->tszBankName, pSt_BankInfo->tszBankAbridge, pSt_BankInfo->enBankType);
	return TRUE;
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
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_LanguageQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo, int nCode /* = 0 */, LPCTSTR lpszMsgBuffer /* = NULL */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
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
	return TRUE;
}
/********************************************************************
函数名称：ModuleProtocol_Packet_LanguageQuery2
函数功能：语言打包为字节流
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
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的信息
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_LanguageQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo, int nCode /* = 0 */)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = TRUE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	*pInt_MsgLen = _stprintf(ptszMsgBuffer, "%d\r\n"
		"%s\r\n"
		"%s\r\n"
		"%d", nCode, pSt_LanguageInfo->tszSourceStr, pSt_LanguageInfo->tszDestStr, pSt_LanguageInfo->enType);
	return TRUE;
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
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_P2PLan(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL*** pppSt_ListClients, int nListCount)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == pppSt_ListClients) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = FALSE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
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
	return TRUE;
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
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_P2PWLan(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, list<XENGINE_P2XPPEER_PROTOCOL>* pStl_ListClients)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == pStl_ListClients) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = FALSE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	unordered_map<string, list<P2XPPROTOCOL_LANPACKET>> stl_MapClient;
	//首先处理公网下的局域网网段列表
	for (auto stl_ListIterator = pStl_ListClients->begin(); stl_ListIterator != pStl_ListClients->end(); stl_ListIterator++)
	{
		TCHAR tszClientAddr[128];
		XENGINE_LIBADDR st_LibAddr;
		P2XPPROTOCOL_LANPACKET st_LANPacket;

		memset(tszClientAddr, '\0', sizeof(tszClientAddr));
		memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
		memset(&st_LANPacket, '\0', sizeof(P2XPPROTOCOL_LANPACKET));
		//分割
		BaseLib_OperatorIPAddr_IsIPV4Addr(stl_ListIterator->tszPrivateAddr, &st_LibAddr);
		_stprintf(tszClientAddr, _T("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);
		//赋值
		_tcscpy(st_LANPacket.tszUsername, stl_ListIterator->tszUserName);
		_tcscpy(st_LANPacket.tszClientAddr, stl_ListIterator->tszPrivateAddr);
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
	return TRUE;
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
 参数.四：pSt_AddrInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：IP地址信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_P2PUser(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL* pSt_PeerInfo, XENGINE_IPADDRINFO* pSt_AddrInfo)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == pSt_PeerInfo) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = FALSE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
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

	st_JsonAddr["tszIPCountry"] = pSt_AddrInfo->tszIPCountry;
	st_JsonAddr["tszIPProvince"] = pSt_AddrInfo->tszIPProvince;
	st_JsonAddr["tszIPCity"] = pSt_AddrInfo->tszIPCity;
	st_JsonAddr["tszIPCounty"] = pSt_AddrInfo->tszIPCounty;
	st_JsonAddr["tszIPISP"] = pSt_AddrInfo->tszIPISP;

	st_JsonRoot["st_AddrInfo"] = st_JsonAddr;

	st_JsonBuilder["emitUTF8"] = true;
	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	return TRUE;
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
BOOL CModuleProtocol_Packet::ModuleProtocol_Packet_P2PConnect(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPIO_PROTOCOL* pSt_IOProtocol)
{
	ModuleProtocol_IsErrorOccur = FALSE;

	if ((NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		ModuleProtocol_IsErrorOccur = FALSE;
		ModuleProtocol_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_PROTOCOL_PACKET_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;

	st_JsonRoot["tszSourceUser"] = pSt_IOProtocol->tszSourceUser;
	st_JsonRoot["tszDestUser"] = pSt_IOProtocol->tszDestUser;
	st_JsonRoot["tszConnectAddr"] = pSt_IOProtocol->tszConnectAddr;
	st_JsonRoot["nDestPort"] = pSt_IOProtocol->nDestPort;
	st_JsonRoot["bIsTcp"] = pSt_IOProtocol->bIsTcp;

	*pInt_MsgLen = st_JsonRoot.toStyledString().length();
	memcpy(ptszMsgBuffer, st_JsonRoot.toStyledString().c_str(), *pInt_MsgLen);
	return TRUE;
}