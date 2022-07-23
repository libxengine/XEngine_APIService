#pragma once
/********************************************************************
//    Created:     2022/04/21  15:52:08
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Password\Plugin_Password\Plugin_Password.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Password\Plugin_Password
//    File Base:   Plugin_Password
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     密码生成类
//    History:
*********************************************************************/

class CPlugin_Password
{
public:
	CPlugin_Password();
	~CPlugin_Password();
public:
	BOOL PluginCore_Init(LPVOID lParam);
	BOOL PluginCore_UnInit();
	BOOL PluginCore_Call(TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBuffer, int nMsgLen);
protected:
	BOOL Plugin_Password_Creator(LPCTSTR lpszPassType, LPCTSTR lpszLength, TCHAR* ptszPassStr);
private:
};
