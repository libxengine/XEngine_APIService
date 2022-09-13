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
typedef struct
{
	TCHAR tszUsername[MAX_PATH];
	TCHAR tszClientAddr[128];
}P2XPPROTOCOL_LANPACKET;

class CModuleProtocol_Packet
{
public:
	CModuleProtocol_Packet();
	~CModuleProtocol_Packet();
public:
	BOOL ModuleProtocol_Packet_Common(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, int nCode = 0, LPCTSTR lpszMsgBuffer = NULL);
	BOOL ModuleProtocol_Packet_IPQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IPADDRINFO* pSt_IPAddrInfo, int nCode = 0, LPCTSTR lpszMsgBuffer = NULL);
	BOOL ModuleProtocol_Packet_IPQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IPADDRINFO* pSt_IPAddrInfo, int nCode = 0);
	BOOL ModuleProtocol_Packet_IDQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO* pSt_IDInfo, XENGINE_IDREGION* pSt_IDRegion, int nCode = 0, LPCTSTR lpszMsgBuffer = NULL);
	BOOL ModuleProtocol_Packet_IDQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO* pSt_IDInfo, XENGINE_IDREGION* pSt_IDRegion, int nCode = 0);
	BOOL ModuleProtocol_Packet_PhoneQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_PHONEINFO* pSt_PhoneInfo, int nCode = 0, LPCTSTR lpszMsgBuffer = NULL);
	BOOL ModuleProtocol_Packet_PhoneQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_PHONEINFO* pSt_PhoneInfo, int nCode = 0);
	BOOL ModuleProtocol_Packet_BankQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_BANKINFO* pSt_BankInfo, int nCode = 0, LPCTSTR lpszMsgBuffer = NULL);
	BOOL ModuleProtocol_Packet_BankQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_BANKINFO* pSt_BankInfo, int nCode = 0);
	BOOL ModuleProtocol_Packet_LanguageQuery(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo, int nCode = 0, LPCTSTR lpszMsgBuffer = NULL);
	BOOL ModuleProtocol_Packet_LanguageQuery2(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo, int nCode = 0);
	BOOL ModuleProtocol_Packet_Locker(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, int nCode = 0, LPCTSTR lpszMsgBuffer = NULL);
public:
	BOOL ModuleProtocol_Packet_P2PLan(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL*** pppSt_ListClients, int nListCount);
	BOOL ModuleProtocol_Packet_P2PWLan(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, list<XENGINE_P2XPPEER_PROTOCOL>* pStl_ListClients);
	BOOL ModuleProtocol_Packet_P2PUser(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL* pSt_PeerInfo, XENGINE_IPADDRINFO* pSt_AddrInfo);
	BOOL ModuleProtocol_Packet_P2PConnect(TCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPIO_PROTOCOL* pSt_IOProtocol);
private:
};