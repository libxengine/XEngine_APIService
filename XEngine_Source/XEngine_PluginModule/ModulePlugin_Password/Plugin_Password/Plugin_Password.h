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
	bool PluginCore_Init(XPVOID lParam);
	void PluginCore_UnInit();
	bool PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen);
protected:
	bool Plugin_Password_Creator(LPCXSTR lpszPassType, LPCXSTR lpszLength, XCHAR* ptszPassStr);
private:
};
