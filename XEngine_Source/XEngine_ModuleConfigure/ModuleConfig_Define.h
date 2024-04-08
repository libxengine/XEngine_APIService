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
	bool bAutoStart;                          //是否自动启动
	bool bHideWnd;                            //是否隐藏窗口启动
	int nHttpPort;                            //HTTP服务端口
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
		int nDeamonTime;                      //进程守护失败执行次数
	}st_XTime;                                //次数*时间=超时
	struct
	{
		XCHAR tszLogFile[MAX_PATH];           //日志文件地址
		int nMaxSize;                         //最大日志大小
		int nMaxCount;                        //最大日志个数
		int nLogLeave;                        //日志等级
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
		XCHAR tszWeatherUrl[MAX_PATH];        //天气接口
		XCHAR tszBankUrl[MAX_PATH];           //银行卡验证地址
		XCHAR tszTranslationUrl[MAX_PATH];    //翻译接口
		struct  
		{
			XCHAR tszAPPID[MAX_PATH];
			XCHAR tszAPPKey[MAX_PATH];
		}st_TranslationInfo;
	}st_XApi;
	struct  
	{
		bool bEnable;                         //是否启用
		XCHAR tszPluginLib[MAX_PATH];         //配置文件地址
		XCHAR tszPluginLua[MAX_PATH];         //配置文件地址
	}st_XPlugin;
	struct
	{   
		XCHAR tszConfigQRCode[MAX_PATH];      //二维码配置地址
		XCHAR tszConfigDeamon[MAX_PATH];      //守护进程配置文件
		XCHAR tszConfigHTTPMime[MAX_PATH];    //HTTPMINE配置文件
		XCHAR tszConfigHTTPCode[MAX_PATH];    //HTTP状态配置文件
	}st_XConfig;
	struct  
	{
		XCHAR tszHostUrl[MAX_PATH];           //主机地址
		int nHTTPCode;                        //转发模式,301 永久,302 临时
	}st_XShortLink;
	struct  
	{
		bool bReload;                         //配置重载
		XBYTE byCode;                         //1基本配置,2插件,3全部     
	}st_XReload;
	struct  
	{
		XCHAR tszUserName[MAX_PATH];
		XCHAR tszUserPass[MAX_PATH];
		struct  
		{
			bool bBackService;
			bool bDeamon;
		}st_VerSwitch;
	}st_XVerifcation;
	struct  
	{
		list<string>* pStl_ListVer;
	}st_XVer;
}XENGINE_SERVICECONFIG;
//二维码模型库
typedef struct
{
	XCHAR tszModelDetect[MAX_PATH];
	XCHAR tszModelSr[MAX_PATH];
	XCHAR tszProtoDetect[MAX_PATH];
	XCHAR tszProtoSr[MAX_PATH];
}XENGINE_QRCODECONFIG;
//插件
typedef struct
{
	bool bEnable;
	XCHAR tszPluginMethod[MAX_PATH];
	XCHAR tszPluginFile[MAX_PATH];
}XENGINE_PLUGININFO;
typedef struct
{
	list<XENGINE_PLUGININFO>* pStl_ListPlugin;
}XENGINE_PLUGINCONFIG;
//////////////////////////////////////////////////////////////////////////
typedef struct
{
	bool bEnable;
	XCHAR tszOPMethod[MAX_PATH];
	XCHAR tszOPNote[MAX_PATH];
	XCHAR tszOPExample[MAX_PATH];
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
	XCHAR tszAPPName[MAX_PATH];        //应用程序名称
	XCHAR tszAPPPath[MAX_PATH];        //应用程序路径
	int nReTime;                       //是否自动重启
	//自定义
	int nErrorTime;
	__int64x nStartTime;
}XENGINE_DEAMONAPPINFO;
typedef struct
{
	list<XENGINE_DEAMONAPPINFO> stl_ListDeamonApp;
}XENGINE_DEAMONAPPLIST;
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
函数名称：ModuleConfigure_Json_QRCodeFile
函数功能：读取JSON配置文件
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要读取的配置文件
 参数.二：pSt_QRCodeConfig
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出二维码配置信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleConfigure_Json_QRCodeFile(LPCXSTR lpszConfigFile, XENGINE_QRCODECONFIG* pSt_QRCodeConfig);
/********************************************************************
函数名称：ModuleConfigure_Json_PluginFile
函数功能：读取JSON配置文件
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要读取的配置文件
 参数.二：pSt_PluginConfig
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出插件配置信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleConfigure_Json_PluginFile(LPCXSTR lpszConfigFile, XENGINE_PLUGINCONFIG* pSt_PluginConfig);
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