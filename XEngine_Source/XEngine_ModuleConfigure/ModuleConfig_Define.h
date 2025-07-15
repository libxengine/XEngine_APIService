#pragma once
/********************************************************************
//    Created:     2021/12/02  16:09:03
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure\ModuleConfig_Define.h
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure
//    File Base:   ModuleConfig_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     配置模块导出定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                        导出的数据结构
//////////////////////////////////////////////////////////////////////////
typedef struct 
{
	XCHAR tszIPAddr[128];                     //本机IP地址,根据需要配置
	bool bDeamon;                             //是否以守护进程启动,LINUX有效
	bool bShowWnd;                            //是否显示窗口启动
	int nHttpPort;                            //HTTP服务端口
	int nRFCPort;                             //RFC标准服务端口
	int nNTPPort;  						      //NTP服务端口
	int nDNSPort;							  //DNS服务端口
	struct
	{
		int nMaxClient;                       //最大客户端个数
		int nMaxQueue;                        //最大队列个数
		int nIOThread;                        //网络IO线程数
		int nHTTPThread;                      //HTTP任务处理线程数
	}st_XMax;
	struct
	{
		int nTimeCheck;                       //检测次数
		int nHTTPTimeOut;                     //HTTP超时时间
		int nP2PTimeOut;                      //P2P客户端超时时间
	}st_XTime;                                //次数*时间=超时
	struct
	{
		XCHAR tszAPIFile[XPATH_MAX];           //日志文件地址
		XCHAR tszServiceFile[XPATH_MAX];
		int nMaxSize;                         //最大日志大小
		int nMaxCount;                        //最大日志个数
		int nLogLeave;                        //日志等级
		int nLogType;                         //日志类型
	}st_XLog;
	struct
	{
		XCHAR tszSQLAddr[128];                //MYSQL数据库地址
		XCHAR tszSQLUser[128];                //数据库用户名
		XCHAR tszSQLPass[128];                //数据库密码
		XCHAR tszDBName[128];                 //数据库表明
		int nSQLPort;                         //端口
		bool bEnable;                         //数据库支持开关
	}st_XSql;
	struct  
	{
		XCHAR tszWeatherUrl[XPATH_MAX];        //天气接口
		XCHAR tszBankUrl[XPATH_MAX];           //银行卡验证地址
		XCHAR tszOilUrl[XPATH_MAX];            //油价接口
		//翻译接口
		struct  
		{
			XCHAR tszAPPUrl[XPATH_MAX];    
			XCHAR tszAPPID[XPATH_MAX];
			XCHAR tszAPPKey[XPATH_MAX];
		}st_TranslationInfo;
	}st_XApi;
	struct  
	{
		bool bEnable;                           //是否启用
		XCHAR tszLibPlugin[XPATH_MAX];
		XCHAR tszLuaPlugin[XPATH_MAX];           
	}st_XPlugin;
	struct
	{   
		//二维码模型库
		struct
		{
			XCHAR tszModelDetect[XPATH_MAX];
			XCHAR tszModelSr[XPATH_MAX];
			XCHAR tszProtoDetect[XPATH_MAX];
			XCHAR tszProtoSr[XPATH_MAX];
		}st_ConfigQRCodec;
		XCHAR tszConfigDeamon[XPATH_MAX];      //守护进程配置文件
		XCHAR tszConfigHTTPMime[XPATH_MAX];    //HTTPMINE配置文件
		XCHAR tszConfigHTTPCode[XPATH_MAX];    //HTTP状态配置文件
	}st_XConfig;
	struct  
	{
		XCHAR tszHostUrl[XPATH_MAX];           //主机地址
		int nHTTPCode;                        //转发模式,301 永久,302 临时
	}st_XShortLink;
	struct
	{
		bool bEnable;                         //是否启用
		XCHAR tszImagePath[XPATH_MAX];         //图片文字识别配置
		XCHAR tszImageLanguage[XPATH_MAX];     //语言支持
	}st_XImageText;
	struct  
	{
		bool bReload;                         //配置重载
		XBYTE byCode;                         //1基本配置,2插件,3全部     
	}st_XReload;
	struct  
	{
		XCHAR tszUserName[XPATH_MAX];
		XCHAR tszUserPass[XPATH_MAX];
		struct  
		{
			bool bBackService;
			bool bDeamon;
		}st_VerSwitch;
	}st_XVerifcation;
	struct
	{
		bool bEnable;
		XCHAR tszDBPhone[XPATH_MAX];
		XCHAR tszDBMac[XPATH_MAX];
		XCHAR tszDBIPAddr[XPATH_MAX];
		XCHAR tszDBISPAddr[XPATH_MAX];
	}st_XAPIModule;
	struct
	{
		bool bEnable;
		XCHAR tszAPIUrl[XPATH_MAX];
		XCHAR tszServiceName[128];
	}st_XReport;
	struct  
	{
		list<string>* pStl_ListVer;
	}st_XVer;
}XENGINE_SERVICECONFIG;
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	bool bEnable;
	XCHAR tszOPMethod[XPATH_MAX];
	XCHAR tszOPNote[XPATH_MAX];
	XCHAR tszOPExample[XPATH_MAX];
}XENGINE_OPTIONINFO;
typedef struct
{
	list<XENGINE_OPTIONINFO> stl_ListBase;
}XENGINE_OPTIONLIST;
//////////////////////////////////////////////////////////////////////////
//用户进程列表
typedef struct
{
	bool bEnable;                      //是否启用
	XCHAR tszAPPName[XPATH_MAX];        //应用程序名称
	XCHAR tszAPPPath[XPATH_MAX];        //应用程序路径
	int nReTime;                       //是否自动重启
	int nReNumber;
	//自定义
	int nErrorTime;
	__int64x nStartTime;
}XENGINE_DEAMONAPPINFO;
typedef struct
{
	list<XENGINE_DEAMONAPPINFO> stl_ListDeamonApp;
}XENGINE_DEAMONAPPLIST;
//////////////////////////////////////////////////////////////////////////
//DNS
typedef struct  
{
	XCHAR tszDNSName[256];                       //域名名称
	XCHAR tszDNSAddr[256];                       //域名地址
	int nType;                                   //DNS地址类型,域名,IP
	int nTTL;                                    //服务器的TTL
}XENGINE_DNSADDRINFO;
typedef struct  
{
	bool bEnable;
	XCHAR tszDNSName[256];
	list<XENGINE_DNSADDRINFO> stl_ListDNSAddr;
}XENGINE_DNSDOMAIN;
typedef struct  
{
	list<xstring> stl_ListDNSServer;
	list<XENGINE_DNSDOMAIN> stl_ListDNSList;
}XENGINE_DNSINFO;
//////////////////////////////////////////////////////////////////////////
//                        导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleConfigure_GetLastError(int* pInt_ErrorCode = NULL);
/************************************************************************/
/*                        文件配置读取                                  */
/************************************************************************/
/********************************************************************
函数名称：ModuleConfigure_Json_File
函数功能：读取JSON配置文件
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要读取的配置文件
 参数.二：pSt_ServerConfig
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出服务配置信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleConfigure_Json_File(LPCXSTR lpszConfigFile, XENGINE_SERVICECONFIG* pSt_ServerConfig);
/********************************************************************
函数名称：ModuleConfigure_Json_VersionFile
函数功能：读取版本配置文件
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要读取的配置文件
 参数.二：pSt_ServerConfig
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出服务配置信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleConfigure_Json_VersionFile(LPCXSTR lpszConfigFile, XENGINE_SERVICECONFIG* pSt_ServerConfig);
/********************************************************************
函数名称：ModuleConfigure_Json_DeamonList
函数功能：读取JSON配置文件
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要读取的配置文件
 参数.二：pSt_AppConfig
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出守护进程列表
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleConfigure_Json_DeamonList(LPCXSTR lpszConfigFile, XENGINE_DEAMONAPPLIST* pSt_AppConfig);
/********************************************************************
函数名称：ModuleConfigure_Json_DNSFile
函数功能：读取JSON配置文件
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要读取的配置文件
 参数.二：pSt_DNSList
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出DNS服务器列表
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleConfigure_Json_DNSFile(LPCXSTR lpszConfigFile, XENGINE_DNSINFO* pSt_DNSList);