#pragma once
/********************************************************************
//    Created:     2021/12/03  14:16:27
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_UserProtocol.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source
//    File Base:   XEngine_UserProtocol
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     用户自定义协议头
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                          主协议定义;unOperatorType
//////////////////////////////////////////////////////////////////////////
typedef enum 
{
	//用户消息
	ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_MSG = ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_USER + 1
}ENUM_XENGINE_COMMUNICATION_PROTOCOL_TYPE_CUSTOM;
//电话号码类型
typedef enum
{
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_UNKNOWN = 0,	    // 未知，查找失败
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CMCC,			// 中国移动
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CUCC,			// 中国联通
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CTCC,			// 中国电信
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CTCC_V,			// 电信虚拟运营商
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CUCC_V,			// 联通虚拟运营商
	ENUM_XENGINE_APISERVICE_PHONE_TYPE_CMCC_V			// 移动虚拟运营商
}ENUM_XENGINE_APISERVICE_PHONE_TYPE;
//银行卡类型
typedef enum
{
	ENUM_XENGINE_APISERVICE_BANK_TYPE_UNKNOWN = 0,	    // 未知，查找失败
	ENUM_XENGINE_APISERVICE_BANK_TYPE_BC,               // 银行卡
	ENUM_XENGINE_APISERVICE_BANK_TYPE_DC,			    // 存蓄卡
	ENUM_XENGINE_APISERVICE_BANK_TYPE_CC			    // 信用卡
}ENUM_XENGINE_APISERVICE_BANK_TYPE;
//语言转换类型
typedef enum
{
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_UNKNOWN = 0,	    // 未知
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_S2T,              // 简体到繁体
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_T2S,			    // 繁体到简体
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_S2TW,			    // 简体到台繁
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_TW2S,			    // 台繁到简体
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_S2HK,			    // 简体到港繁
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_HK2S,			    // 港繁到简体
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_S2TWP,			// 简体（简到台正体标准）
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_TW2SP,			// 繁体（台到简标准）
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_T2TW,			    // 繁体（OpenCC 标准）台正体
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_HK2T,			    // 港繁到繁体（OpenCC）
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_T2HK,			    // 繁体（OpenCC）到港繁
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_T2JP,			    // 繁体（OpenCC 标准，旧字体）到日文新字体
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_JP2T,			    // 日文新字体到繁体（OpenCC 标准，旧字体）
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE_TW2T			    // 台繁到繁体（OpenCC 标准）
}ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE;
//////////////////////////////////////////////////////////////////////////
//                          子协议定义:unOperatorCode
//////////////////////////////////////////////////////////////////////////
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_MSG_TEXTREQ 0x0001   //发送消息
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_MSG_TEXTREP 0x0002   //回复消息
///////////////////////////////////////////////////////////////////////////
//                          导出的数据结构
///////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)
//IP地址信息
typedef struct  
{
	TCHAR tszIPStart[128];
	TCHAR tszIPEnd[128];
	TCHAR tszIPAddr[128];       //IP地址
	TCHAR tszIPCountry[128];    //国家/地区
	TCHAR tszIPProvince[128];   //省/自治区
	TCHAR tszIPCity[128];       //市
	TCHAR tszIPCounty[128];     //县
	TCHAR tszIPAddress[128];    //详细地址
	TCHAR tszIPISP[128];        //运营商
	TCHAR tszIPTime[128];       //数据库日期
}XENGINE_IPADDRINFO;
//身份证校验
typedef struct  
{
	TCHAR tszIDNumber[20];
	WORD nIDProvince;           //省/自治区/直辖市
	WORD nIDCity;               //市/区
	WORD nIDCounty;             //县
	WORD nBirthYear;            //出生年
	WORD nBirthMonth;           //出生月
	WORD nBirthDay;             //出生日
	WORD nPoliceID;             //派出所编码
	WORD nSex;                  //性别
	WORD nCheck;                //校验码
}XENGINE_IDCARDINFO;
//行政区域
typedef struct
{
	TCHAR tszProvincer[64];     //省/自治区/直辖市
	TCHAR tszCity[64];          //市/区     
	TCHAR tszCounty[64];        //县
}XENGINE_IDREGION;
//行政区域
typedef struct
{
	TCHAR tszProvincer[64];     //省/自治区/直辖市
	TCHAR tszCity[64];          //市/区     
	__int64x nPhoneNumber;      //电话号码
	int nZipCode;               //邮编
	int nAreaCode;              //区号
	ENUM_XENGINE_APISERVICE_PHONE_TYPE enPhoneType;  //电话号码类型
}XENGINE_PHONEINFO;
//银行卡
typedef struct
{
	TCHAR tszBankNumber[MAX_PATH];       //银行卡号
	TCHAR tszBankName[MAX_PATH];         //银行卡名称
	TCHAR tszBankAbridge[MAX_PATH];      //银行卡缩写
	ENUM_XENGINE_APISERVICE_BANK_TYPE enBankType;
}XENGINE_BANKINFO;
//语言转换
typedef struct
{
	TCHAR tszSourceStr[1024];                                //原始字符串
	TCHAR tszDestStr[1024];                                  //转换字符串
	ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE enLanguageType;    //语言转换类型
}XENGINE_LANGUAGEINFO;
#pragma pack(pop)