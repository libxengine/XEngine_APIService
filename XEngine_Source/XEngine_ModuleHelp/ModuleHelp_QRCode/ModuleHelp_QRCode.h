#pragma once
/********************************************************************
//    Created:     2023/01/31  09:38:32
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_QRCode\ModuleHelp_QRCode.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_QRCode
//    File Base:   ModuleHelp_QRCode
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     二维码处理代码
//    History:
*********************************************************************/

class CModuleHelp_QRCode
{
public:
	CModuleHelp_QRCode();
	~CModuleHelp_QRCode();
public:
	XBOOL ModuleHelp_QRCode_QREncodecFile(LPCXSTR lpszFileName, LPCXSTR lpszMsgBuffer);
	XBOOL ModuleHelp_QRCode_QREncodecMemory(LPCXSTR lpszMsgBuffer, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszFmt);
	XBOOL ModuleHelp_QRCode_QRDecodecFile(LPCXSTR lpszFileName, XCHAR* ptszMsgBuffer, LPCXSTR lpszDetectProto, LPCXSTR lpszDetectModel, LPCXSTR lpszSrProto, LPCXSTR lpszSrModel);
	XBOOL ModuleHelp_QRCode_QRDecodecMemory(LPCSTR lpszMsgBuffer, int nMsgLen, XCHAR* ptszMsgBuffer, LPCXSTR lpszDetectProto, LPCXSTR lpszDetectModel, LPCXSTR lpszSrProto, LPCXSTR lpszSrModel);
protected:
private:
};