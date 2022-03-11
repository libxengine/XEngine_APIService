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