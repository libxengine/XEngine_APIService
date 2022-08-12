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
	BOOL ModuleProtocol_Parse_IDCard(LPCTSTR lpszMsgBuffer, XENGINE_IDCARDINFO* pSt_IDInfo);
	BOOL ModuleProtocol_Parse_Bank(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_BANKINFO* pSt_BankInfo);
	BOOL ModuleProtocol_Parse_Translation(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo);
	BOOL ModuleProtocol_Parse_P2PClient(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_P2XPPEER_PROTOCOL* pSt_P2XPPeer);
	BOOL ModuleProtocol_Parse_CDKey(LPCTSTR lpszMsgBuffer, int nMsgLen, XENGINE_AUTHORIZE_LOCAL* pSt_Authorize);
private:
};