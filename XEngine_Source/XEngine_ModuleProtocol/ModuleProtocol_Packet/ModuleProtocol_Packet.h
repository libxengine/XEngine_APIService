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
	XCHAR tszUsername[MAX_PATH];
	XCHAR tszClientAddr[128];
}P2XPPROTOCOL_LANPACKET;

class CModuleProtocol_Packet
{
public:
	CModuleProtocol_Packet();
	~CModuleProtocol_Packet();
public:
	XBOOL ModuleProtocol_Packet_Common(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	XBOOL ModuleProtocol_Packet_IDQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO* pSt_IDInfo, XENGINE_IDREGION* pSt_IDRegion, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	XBOOL ModuleProtocol_Packet_BankQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_BANKINFO* pSt_BankInfo, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	XBOOL ModuleProtocol_Packet_LanguageQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	XBOOL ModuleProtocol_Packet_Locker(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	XBOOL ModuleProtocol_Packet_ZIPCode(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_ZIPINFO* pSt_ZIPInfo, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	XBOOL ModuleProtocol_Packet_Log(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_XLOGINFO*** pppSt_XLogList, int nListCount);
	XBOOL ModuleProtocol_Packet_TestReport(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, LPCXSTR lpszIPAddr, int nIPPort, __int64x nNumber, __int64x nFailed, __int64x nSuccess, int nStatus);
	XBOOL ModuleProtocol_Packet_TestReply(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken);
	XBOOL ModuleProtocol_Packet_ShortLink(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_SHORTLINK* pSt_ShortLink);
public:
	XBOOL ModuleProtocol_Packet_P2PLan(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL*** pppSt_ListClients, int nListCount);
	XBOOL ModuleProtocol_Packet_P2PWLan(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, list<XENGINE_P2XPPEER_PROTOCOL>* pStl_ListClients);
	XBOOL ModuleProtocol_Packet_P2PUser(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL* pSt_PeerInfo);
	XBOOL ModuleProtocol_Packet_P2PConnect(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPIO_PROTOCOL* pSt_IOProtocol);
private:
};