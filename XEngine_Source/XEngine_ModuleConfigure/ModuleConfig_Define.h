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
	XBOOL bDeamon;                             //是否以守护进程启动,LINUX有效
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
	}st_XTime;                                //次数*时间=超时
	struct
	{
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
	}st_XSql;
	struct  
	{
		XCHAR tszBankUrl[MAX_PATH];           //银行卡验证地址
		XCHAR tszTranslationUrl[MAX_PATH];    //翻译接口
	}st_XApi;
	struct  
	{
		XBOOL bEnable;                         //是否启用
		XCHAR tszPluginLib[MAX_PATH];         //配置文件地址
		XCHAR tszPluginLua[MAX_PATH];         //配置文件地址
	}st_XPlugin;
	struct
	{   
		XCHAR tszConfigOPencc[MAX_PATH];      //OPENCC配置地址
		XCHAR tszConfigQRCode[MAX_PATH];      //二维码配置地址
	}st_XConfig;
	struct  
	{
		list<string>* pStl_ListVer;
	}st_XVer;
}XENGINE_SERVICECONFIG;
//OPENCC语言转换配置文件
typedef struct 
{
	XCHAR tszFiles2t[MAX_PATH];
	XCHAR tszFilet2s[MAX_PATH];
	XCHAR tszFiles2tw[MAX_PATH];
	XCHAR tszFiletw2s[MAX_PATH];
	XCHAR tszFiles2hk[MAX_PATH];
	XCHAR tszFilehk2s[MAX_PATH];
	XCHAR tszFiles2twp[MAX_PATH];
	XCHAR tszFiletw2sp[MAX_PATH];
	XCHAR tszFilet2tw[MAX_PATH];
	XCHAR tszFilehk2t[MAX_PATH];
	XCHAR tszFilet2hk[MAX_PATH];
	XCHAR tszFilet2jp[MAX_PATH];
	XCHAR tszFilejp2t[MAX_PATH];
	XCHAR tszFiletw2t[MAX_PATH];
}XENGINE_OPENCCCONFIG;
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
	XBOOL bEnable;
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
	XBOOL bEnable;
	XCHAR tszOPMethod[MAX_PATH];
	XCHAR tszOPNote[MAX_PATH];
	XCHAR tszOPExample[MAX_PATH];
}XENGINE_OPTIONINFO;
typedef struct
{
	list<XENGINE_OPTIONINFO> stl_ListBase;
}XENGINE_OPTIONLIST;
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
extern "C" XBOOL ModuleConfigure_Json_File(LPCXSTR lpszConfigFile, XENGINE_SERVICECONFIG* pSt_ServerConfig);
/********************************************************************
函数名称：ModuleConfigure_Json_OPenccFile
函数功能：读取JSON配置文件
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要读取的配置文件
 参数.二：pSt_OPenccConfig
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出OPENCC配置信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" XBOOL ModuleConfigure_Json_OPenccFile(LPCXSTR lpszConfigFile, XENGINE_OPENCCCONFIG* pSt_OPenccConfig);
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
extern "C" XBOOL ModuleConfigure_Json_QRCodeFile(LPCXSTR lpszConfigFile, XENGINE_QRCODECONFIG* pSt_QRCodeConfig);
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
extern "C" XBOOL ModuleConfigure_Json_PluginFile(LPCXSTR lpszConfigFile, XENGINE_PLUGINCONFIG* pSt_PluginConfig);