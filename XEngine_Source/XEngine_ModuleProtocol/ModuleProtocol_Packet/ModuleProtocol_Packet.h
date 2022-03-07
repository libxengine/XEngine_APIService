#pragma once
/********************************************************************
//    Created:     2022/02/28  14:10:28
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Packet\ModuleProtocol_Packet.h
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Packet
//    File Base:   ModuleProtocol_Packet
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     协议打包类
//    History:
*********************************************************************/


class CModuleProtocol_Packet
{
public:
	CModuleProtocol_Packet();
	~CModuleProtocol_Packet();
public:
	BOOL ModuleProtocol_Packet_IPQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IPADDRINFO* pSt_IPAddrInfo, int nCode = 0, LPCTSTR lpszMsgBuffer = NULL);
	BOOL ModuleProtocol_Packet_IPQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IPADDRINFO* pSt_IPAddrInfo, int nCode = 0);
	BOOL ModuleProtocol_Packet_IDQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO* pSt_IDInfo, XENGINE_IDREGION* pSt_IDRegion, int nCode = 0, LPCTSTR lpszMsgBuffer = NULL);
	BOOL ModuleProtocol_Packet_IDQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO* pSt_IDInfo, XENGINE_IDREGION* pSt_IDRegion, int nCode = 0);
private:
};