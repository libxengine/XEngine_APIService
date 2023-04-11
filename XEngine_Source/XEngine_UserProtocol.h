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
//分布式锁状态
typedef enum
{
	ENUM_XENGINE_APISERVICE_LOCKER_TYPE_CREATE = 0,         //创建
	ENUM_XENGINE_APISERVICE_LOCKER_TYPE_OPEN = 1,           //打开
	ENUM_XENGINE_APISERVICE_LOCKER_TYPE_CLOSE = 2,          //关闭,打开和创建后必须调用
	ENUM_XENGINE_APISERVICE_LOCKER_TYPE_READ = 3,           //读加锁
	ENUM_XENGINE_APISERVICE_LOCKER_TYPE_UNREAD = 4,         //读解锁
	ENUM_XENGINE_APISERVICE_LOCKER_TYPE_WRITE = 5,          //写加锁
	ENUM_XENGINE_APISERVICE_LOCKER_TYPE_UNWRITE= 6          //写解锁
}ENUM_XENGINE_APISERVICE_LOCKER_TYPE;
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
//身份证校验
typedef struct  
{
	XCHAR tszIDNumber[20];
	XSHOT nIDProvince;           //省/自治区/直辖市
	XSHOT nIDCity;               //市/区
	XSHOT nIDCounty;             //县
	XSHOT nBirthYear;            //出生年
	XSHOT nBirthMonth;           //出生月
	XSHOT nBirthDay;             //出生日
	XSHOT nPoliceID;             //派出所编码
	XSHOT nSex;                  //性别
	XSHOT nCheck;                //校验码
}XENGINE_IDCARDINFO;
//行政区域
typedef struct
{
	XCHAR tszProvincer[64];     //省/自治区/直辖市
	XCHAR tszCity[64];          //市/区     
	XCHAR tszCounty[64];        //县
}XENGINE_IDREGION;
//银行卡
typedef struct
{
	XCHAR tszBankNumber[MAX_PATH];       //银行卡号
	XCHAR tszBankName[MAX_PATH];         //银行卡名称
	XCHAR tszBankAbridge[MAX_PATH];      //银行卡缩写
	ENUM_XENGINE_APISERVICE_BANK_TYPE enBankType;
}XENGINE_BANKINFO;
//语言转换
typedef struct
{
	XCHAR tszSourceStr[1024];                                //原始字符串
	XCHAR tszDestStr[1024];                                  //转换字符串
	int enType;                                              //简繁为ENUM_XENGINE_APISERVICE_LANGUAGE_TYPE 翻译为ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE
}XENGINE_LANGUAGEINFO;
//连接信息
typedef struct
{
	XCHAR tszUserName[64];                                                 //用户信息
	XCHAR tszPrivateAddr[32];                                              //私有本地地址，内网地址
	XCHAR tszPublicAddr[32];                                               //外网地址
	XCHAR tszConnectAddr[32];                                              //链接地址
	XSHOT dwConnectType;                                                   //连接类型
	XSHOT dwPeerType;                                                      //节点类型
}XENGINE_P2XPPEER_PROTOCOL, * LPXENGINE_P2XPPEER_PROTOCOL;
//P2XP通道连接命令
typedef struct tag_XEngine_P2XPIO_Protocol
{
	XCHAR tszSourceUser[32];                                               //请求连接的用户
	XCHAR tszDestUser[32];                                                 //要连接的用户
	XCHAR tszConnectAddr[32];                                              //连接的IP地址
	int nDestPort;                                                        //要连接的端口
	XBOOL bIsTcp;                                                          //连接类型TCP,否则为UDP
}XENGINE_P2XPIO_PROTOCOL, * LPXENGINE_P2XPIO_PROTOCOL;
//邮编信息
typedef struct
{
	XCHAR tszProvincer[64];     //省/自治区/直辖市
	XCHAR tszCity[64];          //市/区     
	XCHAR tszCounty[64];        //县
	XCHAR tszPinYin[64];        //拼音
	double dlLng;               //经度
	double dlLat;               //纬度
	int nZipCode;               //邮编
	int nAreaCode;              //区号
	int nLevel;                 //行政级别
}XENGINE_ZIPINFO;
//日志服务
typedef struct  
{
	XENGINE_PROTOCOL_XLOG st_ProtocolLog;
	XCHAR tszLogBuffer[10240];
	XCHAR tszTableName[128];
	XCHAR tszTimeStart[128];
	XCHAR tszTimeEnd[128];
	int nLogSize;
}XENGINE_XLOGINFO;
//二维码
typedef struct
{
	XCHAR tszMsgBuffer[4096];
	XCHAR tszFmtBuffer[8];
}XENGINE_QRCODE;
//网络测试
typedef struct
{
	XCHAR tszAddr[64];                                                     //要测试的IP地址
	int nPort;                                                            //端口号码
	//单位毫秒
	int nConnectCount;                                                    //要测试的客户端个数
	int nConnectTest;                                                     //每个客户端测试的次数,-1表示不限制
	int nContWaitTime;                                                    //连接后等待多长时间关闭/处理一次休息时间，毫秒
	int nCloseWaitContTime;                                               //关闭后等待多长时间连接/套接字操作超时时间
}MODULEHELP_SOCKETTEST_RECONNECT, * LPMODULEHELP_SOCKETTEST_RECONNECT;
//数据包压力测试
typedef struct
{
	MODULEHELP_SOCKETTEST_RECONNECT st_REConnect;
	int nSDLen;                                                           //发送数据包大小，如果ptszSDBuffer的值为NULL，那么这个值表示测试端允许发送的大小，否则表示缓冲区大小
	int nRVLen;                                                           //接收端大小,表示ptszRVBuffer缓冲区大小,ptszRVBuffer的值匹配接受数据才表示成功,如果ptszRVBuffer为NULL,不做数据验证只接受.
	XCHAR tszSDBuffer[4096];                                               //如果你的服务器有特殊数据测试，请填写这个参数，否则测试端将自定义数据发送,内存需要由用户管理
	XCHAR tszRVBuffer[4096];
}MODULEHELP_SOCKETTEST_DATAS, * LPMODULEHELP_SOCKETTEST_DATAS;
typedef struct
{
	MODULEHELP_SOCKETTEST_RECONNECT st_SocketConn;
	MODULEHELP_SOCKETTEST_DATAS st_SocketData;
	XCHAR tszAPIUrl[MAX_PATH];
	XNETHANDLE xhToken;
	int nType;                                                  //0,全部报告,其他结束统计报告
	bool bTCP;
	bool bConn;
}XENGINE_SOCKETTEST;
//短连接
typedef struct
{
	XCHAR tszFullUrl[MAX_PATH];
	XCHAR tszShotUrl[MAX_PATH];
	XCHAR tszKeyUrl[MAX_PATH];
	XCHAR tszMapUrl[MAX_PATH];
	XCHAR tszCvtUrl[MAX_PATH];
	XCHAR tszCreateTime[64];
	int nLength;
	int nID;
}XENGINE_SHORTLINK;
#pragma pack(pop)