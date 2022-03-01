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
	
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	if (0 == nCode)
	{
		st_JsonObject["tszIPAddr"] = pSt_IPAddrInfo->st_IPAddrInfo.tszIPAddr;
		st_JsonObject["tszIPStart"] = pSt_IPAddrInfo->tszIPStart;
		st_JsonObject["tszIPEnd"] = pSt_IPAddrInfo->tszIPEnd;
		st_JsonObject["tszIPCountry"] = pSt_IPAddrInfo->st_IPAddrInfo.tszIPCountry;
		st_JsonObject["tszIPProvince"] = pSt_IPAddrInfo->st_IPAddrInfo.tszIPProvince;
		st_JsonObject["tszIPCity"] = pSt_IPAddrInfo->st_IPAddrInfo.tszIPCity;
		st_JsonObject["tszIPCounty"] = pSt_IPAddrInfo->st_IPAddrInfo.tszIPCounty;
		st_JsonObject["tszIPAddress"] = pSt_IPAddrInfo->st_IPAddrInfo.tszIPAddress;
		st_JsonObject["tszIPISP"] = pSt_IPAddrInfo->st_IPAddrInfo.tszIPISP;
		st_JsonObject["tszIPTime"] = pSt_IPAddrInfo->st_IPAddrInfo.tszIPTime;
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