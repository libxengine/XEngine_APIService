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
BOOL ModuleProtocol_IsErrorOccur = FALSE;
DWORD ModuleProtocol_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleProtocol_Packet m_ProtocolPacket;
CModuleProtocol_Parse m_ProtocolParse;
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModuleProtocol_GetLastError(int* pInt_SysError)
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
extern "C" BOOL ModuleProtocol_Packet_Common(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, int nCode, LPCTSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_Common(ptszMsgBuffer, pInt_MsgLen, nCode, lpszMsgBuffer);
}
extern "C" BOOL ModuleProtocol_Packet_IDQuery(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO * pSt_IDInfo, XENGINE_IDREGION * pSt_IDRegion, int nCode, LPCTSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_IDQuery(ptszMsgBuffer, pInt_MsgLen, pSt_IDInfo, pSt_IDRegion, nCode, lpszMsgBuffer);
}
extern "C" BOOL ModuleProtocol_Packet_BankQuery(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_BANKINFO * pSt_BankInfo, int nCode, LPCTSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_BankQuery(ptszMsgBuffer, pInt_MsgLen, pSt_BankInfo, nCode, lpszMsgBuffer);
}
extern "C" BOOL ModuleProtocol_Packet_LanguageQuery(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_LANGUAGEINFO * pSt_LanguageInfo, int nCode, LPCTSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_LanguageQuery(ptszMsgBuffer, pInt_MsgLen, pSt_LanguageInfo, nCode, lpszMsgBuffer);
}
extern "C" BOOL ModuleProtocol_Packet_Locker(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, int nCode, LPCTSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_Locker(ptszMsgBuffer, pInt_MsgLen, xhToken, nCode, lpszMsgBuffer);
}
extern "C" BOOL ModuleProtocol_Packet_ZIPCode(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_ZIPINFO * pSt_ZIPInfo, int nCode, LPCTSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_ZIPCode(ptszMsgBuffer, pInt_MsgLen, pSt_ZIPInfo, nCode, lpszMsgBuffer);
}
extern "C" BOOL ModuleProtocol_Packet_Log(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_XLOGINFO * **pppSt_XLogList, int nListCount)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_Log(ptszMsgBuffer, pInt_MsgLen, pppSt_XLogList, nListCount);
}
extern "C" BOOL ModuleProtocol_Packet_P2PLan(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL * **pppSt_ListClients, int nListCount)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_P2PLan(ptszMsgBuffer, pInt_MsgLen, pppSt_ListClients, nListCount);
}
extern "C" BOOL ModuleProtocol_Packet_P2PWLan(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, list<XENGINE_P2XPPEER_PROTOCOL>*pStl_ListClients)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_P2PWLan(ptszMsgBuffer, pInt_MsgLen, pStl_ListClients);
}
extern "C" BOOL ModuleProtocol_Packet_P2PUser(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL * pSt_PeerInfo)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_P2PUser(ptszMsgBuffer, pInt_MsgLen, pSt_PeerInfo);
}
extern "C" BOOL ModuleProtocol_Packet_P2PConnect(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPIO_PROTOCOL * pSt_IOProtocol)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_P2PConnect(ptszMsgBuffer, pInt_MsgLen, pSt_IOProtocol);
}
/************************************************************************/
/*                         导出的协议解析函数                           */
/************************************************************************/
extern "C" BOOL ModuleProtocol_Parse_IDCard(LPCTSTR lpszMsgBuffer, XENGINE_IDCARDINFO * pSt_IDInfo)
{
	return m_ProtocolParse.ModuleProtocol_Parse_IDCard(lpszMsgBuffer, pSt_IDInfo);
}
extern "C" BOOL ModuleProtocol_Parse_Bank(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_BANKINFO * pSt_BankInfo)
{
	return m_ProtocolParse.ModuleProtocol_Parse_Bank(lpszMsgBuffer, nMsgLen, pSt_BankInfo);
}
extern "C" BOOL ModuleProtocol_Parse_Translation(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_LANGUAGEINFO * pSt_LanguageInfo)
{
	return m_ProtocolParse.ModuleProtocol_Parse_Translation(lpszMsgBuffer, nMsgLen, pSt_LanguageInfo);
}
extern "C" BOOL ModuleProtocol_Parse_P2PClient(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_P2XPPEER_PROTOCOL * pSt_P2XPPeer)
{
	return m_ProtocolParse.ModuleProtocol_Parse_P2PClient(lpszMsgBuffer, nMsgLen, pSt_P2XPPeer);
}
extern "C" BOOL ModuleProtocol_Parse_ZIPCode(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_ZIPINFO * pSt_ZIPInfo)
{
	return m_ProtocolParse.ModuleProtocol_Parse_ZIPCode(lpszMsgBuffer, nMsgLen, pSt_ZIPInfo);
}
extern "C" BOOL ModuleProtocol_Parse_XLog(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_XLOGINFO * pSt_XLogInfo)
{
	return m_ProtocolParse.ModuleProtocol_Parse_XLog(lpszMsgBuffer, nMsgLen, pSt_XLogInfo);
}
extern "C" BOOL ModuleProtocol_Parse_QRCode(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_QRCODE * pSt_QRCode)
{
	return m_ProtocolParse.ModuleProtocol_Parse_QRCode(lpszMsgBuffer, nMsgLen, pSt_QRCode);
}
extern "C" BOOL ModuleProtocol_Parse_SocketTest(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_SOCKETTEST * pSt_SocketTest)
{
	return m_ProtocolParse.ModuleProtocol_Parse_SocketTest(lpszMsgBuffer, nMsgLen, pSt_SocketTest);
}