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
	BOOL ModuleHelp_QRCode_QREncodecFile(LPCTSTR lpszFileName, LPCTSTR lpszMsgBuffer);
	BOOL ModuleHelp_QRCode_QREncodecMemory(LPCTSTR lpszMsgBuffer, TCHAR* ptszMsgBuffer, int* pInt_MsgLen);
	BOOL ModuleHelp_QRCode_QRDecodecFile(LPCTSTR lpszFileName, TCHAR* ptszMsgBuffer, LPCTSTR lpszDetectProto, LPCTSTR lpszDetectModel, LPCTSTR lpszSrProto, LPCTSTR lpszSrModel);
	BOOL ModuleHelp_QRCode_QRDecodecMemory(LPCSTR lpszMsgBuffer, int nMsgLen, TCHAR* ptszMsgBuffer, LPCTSTR lpszDetectProto, LPCTSTR lpszDetectModel, LPCTSTR lpszSrProto, LPCTSTR lpszSrModel);
protected:
private:
};