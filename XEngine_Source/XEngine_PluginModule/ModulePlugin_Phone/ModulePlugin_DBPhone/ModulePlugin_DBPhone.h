#pragma once
/********************************************************************
//    Created:     2023/01/09  17:06:35
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\ModulePlugin_DBPhone\ModulePlugin_DBPhone.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\ModulePlugin_DBPhone
//    File Base:   ModulePlugin_DBPhone
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     电话信息查询
//    History:
*********************************************************************/
#define XENGINE_APISERVICE_DATABASE_PHONE_BUFFER_SIZE 1024 * 1024 * 10
#define XENGINE_APISERVICE_DATABASE_PHONE_INDEX_LEN 9

typedef struct 
{
	XBYTE byVersion[4];
	unsigned int nOffset;
}XENGINE_DBPHONEHDR;

typedef struct
{
	unsigned int nPhone;
	unsigned int nOffset;
	XBYTE byType;
}XENGINE_DBPHONERECORD;

class CModulePlugin_DBPhone
{
public:
	CModulePlugin_DBPhone();
	~CModulePlugin_DBPhone();
public:
	bool ModuleDatabase_Phone_Init(LPCXSTR lpszSQLFile);
	bool ModuleDatabase_Phone_Destory();
	bool ModuleDatabase_Phone_Query(LPCXSTR lpszPhoneNumber, XENGINE_PHONEINFO* pSt_PhoneInfo);
protected:
	bool ModuleDatabase_Phone_Convert(LPCXSTR lpszPhoneInfo, int nMsgLen, XENGINE_PHONEINFO* pSt_PhoneInfo);
private:
	XENGINE_DBPHONEHDR st_PhoneHdr;
private:
	size_t nFLen = 0;
	size_t nCount = 0;
	XCHAR* ptszMsgBuffer;
};