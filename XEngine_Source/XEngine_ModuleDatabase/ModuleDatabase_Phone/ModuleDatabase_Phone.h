#pragma once
/********************************************************************
//    Created:     2022/03/09  10:30:46
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Phone\ModuleDatabase_Phone.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Phone
//    File Base:   ModuleDatabase_Phone
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     电话信息查询
//    History:
*********************************************************************/
#define XENGINE_APISERVICE_DATABASE_PHONE_BUFFER_SIZE 1024 * 1024 * 10
#define XENGINE_APISERVICE_DATABASE_PHONE_INDEX_LEN 9

typedef struct 
{
	BYTE byVersion[4];
	unsigned int nOffset;
}XENGINE_DBPHONEHDR;

typedef struct
{
	unsigned int nPhone;
	unsigned int nOffset;
	BYTE byType;
}XENGINE_DBPHONERECORD;

class CModuleDatabase_Phone
{
public:
	CModuleDatabase_Phone();
	~CModuleDatabase_Phone();
public:
	BOOL ModuleDatabase_Phone_Init(LPCTSTR lpszSQLFile);
	BOOL ModuleDatabase_Phone_Destory();
	BOOL ModuleDatabase_Phone_Query(LPCTSTR lpszPhoneNumber, XENGINE_PHONEINFO* pSt_PhoneInfo);
protected:
	BOOL ModuleDatabase_Phone_Convert(LPCTSTR lpszPhoneInfo, int nMsgLen, XENGINE_PHONEINFO* pSt_PhoneInfo);
private:
	XENGINE_DBPHONEHDR st_PhoneHdr;
private:
	size_t nFLen = 0;
	size_t nCount = 0;
	TCHAR* ptszMsgBuffer;
};