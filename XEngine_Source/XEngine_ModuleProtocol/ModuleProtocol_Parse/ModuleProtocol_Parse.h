#pragma once
/********************************************************************
//    Created:     2022/03/03  11:09:16
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Parse\ModuleProtocol_Parse.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Parse
//    File Base:   ModuleProtocol_Parse
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     协议解析类
//    History:
*********************************************************************/


class CModuleProtocol_Parse
{
public:
	CModuleProtocol_Parse();
	~CModuleProtocol_Parse();
public:
	XBOOL ModuleProtocol_Parse_IDCard(LPCXSTR lpszMsgBuffer, XENGINE_IDCARDINFO* pSt_IDInfo);
	XBOOL ModuleProtocol_Parse_Bank(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_BANKINFO* pSt_BankInfo);
	XBOOL ModuleProtocol_Parse_Translation(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo);
	XBOOL ModuleProtocol_Parse_P2PClient(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_P2XPPEER_PROTOCOL* pSt_P2XPPeer);
	XBOOL ModuleProtocol_Parse_ZIPCode(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_ZIPINFO* pSt_ZIPInfo);
	XBOOL ModuleProtocol_Parse_XLog(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_XLOGINFO* pSt_XLogInfo);
	XBOOL ModuleProtocol_Parse_QRCode(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_QRCODE* pSt_QRCode);
	XBOOL ModuleProtocol_Parse_SocketTest(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_SOCKETTEST* pSt_SocketTest);
	XBOOL ModuleProtocol_Parse_ShortLink(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_SHORTLINK* pSt_ShortLink);
private:
};