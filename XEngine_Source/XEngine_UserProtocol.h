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
//翻译接口
typedef enum 
{
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_AUTO = 0,
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2EN,      //中文　»　英语
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2JA,      //中文　»　日语
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2KR,      //中文　»　韩语
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2FR,      //中文　»　法语
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2RU,      //中文　»　俄语
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2SP,      //中文　»　西语
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_EN2ZH_CN,      //英语　»　中文
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_JA2ZH_CN,      //日语　»　中文
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_KR2ZH_CN,      //韩语　»　中文
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_FR2ZH_CN,      //法语　»　中文
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_RU2ZH_CN,      //俄语　»　中文
	ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_SP2ZH_CN       //西语　»　中文
}ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE;
//////////////////////////////////////////////////////////////////////////
//                          子协议定义:unOperatorCode
//////////////////////////////////////////////////////////////////////////
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_MSG_TEXTREQ 0x0001   //发送消息
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_MSG_TEXTREP 0x0002   //回复消息
//P2XP协议
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQLOGIN 0x6001        //登录
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REPLOGIN 0x6002
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQLANLIST 0x6003      //同步列表协议,同步本地局域网IP中的客户端
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REPLANLIST 0x6004      //同步列表回复确认协议
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQCONNECT 0x6005      //请求用户连接到网络服务
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REPCONNECT 0x6006      //确认连接协议
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REQUSERQUERY 0x6007    //用户查询
#define XENGINE_COMMUNICATION_PROTOCOL_OPERATOR_CODE_P2XP_REPUSERQUERY 0x6008    //用户查询确认
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
	int enType;                                              //简繁为ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE 翻译为ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE
}XENGINE_LANGUAGEINFO;
//连接信息
typedef struct
{
	CHAR tszUserName[64];                                                 //用户信息
	CHAR tszPrivateAddr[32];                                              //私有本地地址，内网地址
	CHAR tszPublicAddr[32];                                               //外网地址
	CHAR tszConnectAddr[32];                                              //链接地址
	WORD dwConnectType;                                                   //连接类型
	WORD dwPeerType;                                                      //节点类型
}XENGINE_P2XPPEER_PROTOCOL, * LPXENGINE_P2XPPEER_PROTOCOL;
//P2XP通道连接命令
typedef struct tag_XEngine_P2XPIO_Protocol
{
	CHAR tszSourceUser[32];                                               //请求连接的用户
	CHAR tszDestUser[32];                                                 //要连接的用户
	CHAR tszConnectAddr[32];                                              //连接的IP地址
	int nDestPort;                                                        //要连接的端口
	BOOL bIsTcp;                                                          //连接类型TCP,否则为UDP
}XENGINE_P2XPIO_PROTOCOL, * LPXENGINE_P2XPIO_PROTOCOL;
#pragma pack(pop)