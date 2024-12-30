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
	bool ModuleProtocol_Packet_Common(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	bool ModuleProtocol_Packet_IDQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO* pSt_IDInfo, XENGINE_IDREGION* pSt_IDRegion, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	bool ModuleProtocol_Packet_IDRegion(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDREGION* pSt_IDRegion, int nIDRegion);
	bool ModuleProtocol_Packet_BankQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_BANKINFO* pSt_BankInfo, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	bool ModuleProtocol_Packet_LanguageQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	bool ModuleProtocol_Packet_Locker(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	bool ModuleProtocol_Packet_ZIPCode(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_ZIPINFO* pSt_ZIPInfo, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
	bool ModuleProtocol_Packet_Log(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_XLOGINFO*** pppSt_XLogList, int nListCount);
	bool ModuleProtocol_Packet_LogShow(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** ppptszList, int nListCount);
	bool ModuleProtocol_Packet_TestReport(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, LPCXSTR lpszIPAddr, int nIPPort, __int64x nNumber, __int64x nFailed, __int64x nSuccess, int nStatus);
	bool ModuleProtocol_Packet_TestReply(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken);
	bool ModuleProtocol_Packet_Weather(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_WEATHERINFO* pSt_WeatherInfo);
	bool ModuleProtocol_Packet_ShortLink(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_SHORTLINK* pSt_ShortLink);
	bool ModuleProtocol_Packet_ShortLinkList(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_SHORTLINK*** pppSt_ShortLink, int nListCount);
	bool ModuleProtocol_Packet_WordFilter(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_WORDFILTER* pSt_WordFilter);
	bool ModuleProtocol_Packet_WordFilterList(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_WORDFILTER*** pppSt_WordFilter, int nListCount);
	bool ModuleProtocol_Packet_ImageAttr(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IMGBASEATTR* pSt_BaseInfo, XENGINE_IMGEXTATTR* pSt_ExtAttr);
	bool ModuleProtocol_Packet_ImageText(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** pppListStr, int nListCount);
	bool ModuleProtocol_Packet_EnumDevice(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, AVHELP_DEVICEINFO*** pppSt_AudioList, AVHELP_DEVICEINFO*** pppSt_VideoList, int nACount, int nVCount);
	bool ModuleProtocol_Packet_ListFile(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** pppszFileList, int nListCount);
	bool ModuleProtocol_Packet_HardWare(XCHAR* ptszHWInfo, int* pInt_Len);
	bool ModuleProtocol_Packet_SoftWare(XCHAR* ptszSWInfo, int* pInt_Len);
	bool ModuleProtocol_Packet_Machine(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_MACHINEINFO*** pppSt_MachineList, int nListCount);
	bool ModuleProtocol_Packet_OilInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_OILINFO* pSt_OilInfo);
	bool ModuleProtocol_Packet_PhoneInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_PHONEINFO* pSt_PhoneInfo);
	bool ModuleProtocol_Packet_IPAddr(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_IPADDRINFO* pSt_IPAddrInfo);
	bool ModuleProtocol_Packet_MacInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_MACADDRINFO* pSt_MacInfo);
public:
	bool ModuleProtocol_Packet_P2PLan(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL*** pppSt_ListClients, int nListCount);
	bool ModuleProtocol_Packet_P2PWLan(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, list<XENGINE_P2XPPEER_PROTOCOL>* pStl_ListClients);
	bool ModuleProtocol_Packet_P2PWList(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** ppptszListAddr, int nListCount);
private:
};