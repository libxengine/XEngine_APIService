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
	bool PluginCore_Init(XPVOID lParam);
	void PluginCore_UnInit();
	bool PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen);
protected:
	bool PluginCore_Phone_Init(LPCXSTR lpszMSGBuffer);
	std::string PluginCore_Phone_7Digits(LPCXSTR lpszMSGBuffer);
private:
	size_t nPos = 0;
	size_t nFSize = 0;
	XCHAR* ptszMSGBuffer = NULL;
	XCHAR* ptszPhoneIndex = NULL;

	XENGINE_PROTOCOLHDR st_ProtocolHdr = {};
	XENGINE_PROTOCOLHDR st_ProtocolMap = {};
	XENGINE_PROTOCOLHDR st_ProtocolRecord = {};
	XENGINE_PROTOCOLHDR st_ProtocolIndex = {};
private:
	std::unordered_map<int, std::string> stl_MapISPName;
};
