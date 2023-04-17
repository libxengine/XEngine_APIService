#include "pch.h"
#include "ModuleProtocol_Packet/ModuleProtocol_Packet.h"
#include "ModuleProtocol_Parse/ModuleProtocol_Parse.h"
/********************************************************************
//    Created:     2022/02/28  14:23:53
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol\pch.cpp
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出协议模块实现
//    History:
*********************************************************************/
bool ModuleProtocol_IsErrorOccur = false;
XLONG ModuleProtocol_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleProtocol_Packet m_ProtocolPacket;
CModuleProtocol_Parse m_ProtocolParse;
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleProtocol_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return ModuleProtocol_dwErrorCode;
}
/************************************************************************/
/*                         导出的协议打包函数                           */
/************************************************************************/
extern "C" bool ModuleProtocol_Packet_Common(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, int nCode, LPCXSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_Common(ptszMsgBuffer, pInt_MsgLen, nCode, lpszMsgBuffer);
}
extern "C" bool ModuleProtocol_Packet_IDQuery(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO * pSt_IDInfo, XENGINE_IDREGION * pSt_IDRegion, int nCode, LPCXSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_IDQuery(ptszMsgBuffer, pInt_MsgLen, pSt_IDInfo, pSt_IDRegion, nCode, lpszMsgBuffer);
}
extern "C" bool ModuleProtocol_Packet_BankQuery(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_BANKINFO * pSt_BankInfo, int nCode, LPCXSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_BankQuery(ptszMsgBuffer, pInt_MsgLen, pSt_BankInfo, nCode, lpszMsgBuffer);
}
extern "C" bool ModuleProtocol_Packet_LanguageQuery(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_LANGUAGEINFO * pSt_LanguageInfo, int nCode, LPCXSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_LanguageQuery(ptszMsgBuffer, pInt_MsgLen, pSt_LanguageInfo, nCode, lpszMsgBuffer);
}
extern "C" bool ModuleProtocol_Packet_Locker(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, int nCode, LPCXSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_Locker(ptszMsgBuffer, pInt_MsgLen, xhToken, nCode, lpszMsgBuffer);
}
extern "C" bool ModuleProtocol_Packet_ZIPCode(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_ZIPINFO * pSt_ZIPInfo, int nCode, LPCXSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_ZIPCode(ptszMsgBuffer, pInt_MsgLen, pSt_ZIPInfo, nCode, lpszMsgBuffer);
}
extern "C" bool ModuleProtocol_Packet_Log(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_XLOGINFO * **pppSt_XLogList, int nListCount)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_Log(ptszMsgBuffer, pInt_MsgLen, pppSt_XLogList, nListCount);
}
extern "C" bool ModuleProtocol_Packet_TestReport(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, LPCXSTR lpszIPAddr, int nIPPort, __int64x nNumber, __int64x nFailed, __int64x nSuccess, int nStatus)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_TestReport(ptszMsgBuffer, pInt_MsgLen, xhToken, lpszIPAddr, nIPPort, nNumber, nFailed, nSuccess, nStatus);
}
extern "C" bool ModuleProtocol_Packet_TestReply(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_TestReply(ptszMsgBuffer, pInt_MsgLen, xhToken);
}
extern "C" bool ModuleProtocol_Packet_ShortLink(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_SHORTLINK * pSt_ShortLink)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_ShortLink(ptszMsgBuffer, pInt_MsgLen, pSt_ShortLink);
}
extern "C" bool ModuleProtocol_Packet_P2PLan(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL * **pppSt_ListClients, int nListCount)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_P2PLan(ptszMsgBuffer, pInt_MsgLen, pppSt_ListClients, nListCount);
}
extern "C" bool ModuleProtocol_Packet_P2PWLan(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, list<XENGINE_P2XPPEER_PROTOCOL>*pStl_ListClients)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_P2PWLan(ptszMsgBuffer, pInt_MsgLen, pStl_ListClients);
}
extern "C" bool ModuleProtocol_Packet_P2PUser(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL * pSt_PeerInfo)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_P2PUser(ptszMsgBuffer, pInt_MsgLen, pSt_PeerInfo);
}
extern "C" bool ModuleProtocol_Packet_P2PConnect(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPIO_PROTOCOL * pSt_IOProtocol)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_P2PConnect(ptszMsgBuffer, pInt_MsgLen, pSt_IOProtocol);
}
/************************************************************************/
/*                         导出的协议解析函数                           */
/************************************************************************/
extern "C" bool ModuleProtocol_Parse_IDCard(LPCXSTR lpszMsgBuffer, XENGINE_IDCARDINFO * pSt_IDInfo)
{
	return m_ProtocolParse.ModuleProtocol_Parse_IDCard(lpszMsgBuffer, pSt_IDInfo);
}
extern "C" bool ModuleProtocol_Parse_Bank(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_BANKINFO * pSt_BankInfo)
{
	return m_ProtocolParse.ModuleProtocol_Parse_Bank(lpszMsgBuffer, nMsgLen, pSt_BankInfo);
}
extern "C" bool ModuleProtocol_Parse_Translation(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_LANGUAGEINFO * pSt_LanguageInfo)
{
	return m_ProtocolParse.ModuleProtocol_Parse_Translation(lpszMsgBuffer, nMsgLen, pSt_LanguageInfo);
}
extern "C" bool ModuleProtocol_Parse_P2PClient(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_P2XPPEER_PROTOCOL * pSt_P2XPPeer)
{
	return m_ProtocolParse.ModuleProtocol_Parse_P2PClient(lpszMsgBuffer, nMsgLen, pSt_P2XPPeer);
}
extern "C" bool ModuleProtocol_Parse_ZIPCode(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_ZIPINFO * pSt_ZIPInfo)
{
	return m_ProtocolParse.ModuleProtocol_Parse_ZIPCode(lpszMsgBuffer, nMsgLen, pSt_ZIPInfo);
}
extern "C" bool ModuleProtocol_Parse_XLog(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_XLOGINFO * pSt_XLogInfo)
{
	return m_ProtocolParse.ModuleProtocol_Parse_XLog(lpszMsgBuffer, nMsgLen, pSt_XLogInfo);
}
extern "C" bool ModuleProtocol_Parse_QRCode(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_QRCODE * pSt_QRCode)
{
	return m_ProtocolParse.ModuleProtocol_Parse_QRCode(lpszMsgBuffer, nMsgLen, pSt_QRCode);
}
extern "C" bool ModuleProtocol_Parse_SocketTest(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_SOCKETTEST * pSt_SocketTest)
{
	return m_ProtocolParse.ModuleProtocol_Parse_SocketTest(lpszMsgBuffer, nMsgLen, pSt_SocketTest);
}
extern "C" bool ModuleProtocol_Parse_ShortLink(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_SHORTLINK * pSt_ShortLink)
{
	return m_ProtocolParse.ModuleProtocol_Parse_ShortLink(lpszMsgBuffer, nMsgLen, pSt_ShortLink);
}