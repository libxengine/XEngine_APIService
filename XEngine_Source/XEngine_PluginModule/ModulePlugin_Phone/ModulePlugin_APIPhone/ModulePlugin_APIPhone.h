#pragma once
/********************************************************************
//    Created:     2023/01/09  17:13:28
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\ModulePlugin_APIPhone\ModulePlugin_APIPhone.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\ModulePlugin_APIPhone
//    File Base:   ModulePlugin_APIPhone
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     电话接口类
//    History:
*********************************************************************/

class CModulePlugin_APIPhone
{
public:
	CModulePlugin_APIPhone();
	~CModulePlugin_APIPhone();
public:
	BOOL PluginCore_Init(LPVOID lParam);
	void PluginCore_UnInit();
	BOOL PluginCore_Call(TCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, TCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCTSTR lpszMsgBuffer, int nMsgLen);
protected:
private:
	CModulePlugin_DBPhone m_DBPhone;
};
