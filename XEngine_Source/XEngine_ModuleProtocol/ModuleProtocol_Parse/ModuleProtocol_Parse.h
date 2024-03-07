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
	bool ModuleProtocol_Parse_IDCard(LPCXSTR lpszMsgBuffer, XENGINE_IDCARDINFO* pSt_IDInfo);
	bool ModuleProtocol_Parse_Bank(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_BANKINFO* pSt_BankInfo);
	bool ModuleProtocol_Parse_Translation(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo);
	bool ModuleProtocol_Parse_P2PClient(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_P2XPPEER_PROTOCOL* pSt_P2XPPeer);
	bool ModuleProtocol_Parse_ZIPCode(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_ZIPINFO* pSt_ZIPInfo);
	bool ModuleProtocol_Parse_XLog(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_XLOGINFO* pSt_XLogInfo);
	bool ModuleProtocol_Parse_QRCode(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_QRCODE* pSt_QRCode);
	bool ModuleProtocol_Parse_SocketTest(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_SOCKETTEST* pSt_SocketTest);
	bool ModuleProtocol_Parse_ShortLink(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_SHORTLINK* pSt_ShortLink);
	bool ModuleProtocol_Parse_WordFilter(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_WORDFILTER* pSt_WordFilter);
	bool ModuleProtocol_Parse_BackService(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR* ptszSrcBuffer = NULL, XCHAR* ptszDstBuffer = NULL, int* pInt_BSType = NULL);
	bool ModuleProtocol_Parse_Verifcation(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR* ptszUserName, XCHAR* ptszUserPass);
	bool ModuleProtocol_Parse_Deamon(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR* ptszAPPName, XCHAR* ptszAPPPath, int* pInt_Retime, bool* pbEnable);
	bool ModuleProtocol_Parse_Weather(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_WEATHERINFO* pSt_WeatherInfo);
private:
};