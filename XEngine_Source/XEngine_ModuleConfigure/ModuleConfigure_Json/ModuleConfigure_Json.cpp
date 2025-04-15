#include "pch.h"
#include "ModuleConfigure_Json.h"
/********************************************************************
//    Created:     2021/12/02  16:14:11
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure\ModuleConfigure_Json\ModuleConfigure_Json.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ModuleConfigure\ModuleConfigure_Json
//    File Base:   ModuleConfigure_Json
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     JSON配置读写实现
//    History:
*********************************************************************/
CModuleConfigure_Json::CModuleConfigure_Json()
{

}
CModuleConfigure_Json::~CModuleConfigure_Json()
{

}
//////////////////////////////////////////////////////////////////////////
//                        公用函数
//////////////////////////////////////////////////////////////////////////
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
bool CModuleConfigure_Json::ModuleConfigure_Json_File(LPCXSTR lpszConfigFile, XENGINE_SERVICECONFIG* pSt_ServerConfig)
{
	Config_IsErrorOccur = false;

	if ((NULL == lpszConfigFile) || (NULL == pSt_ServerConfig))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//读取配置文件所有内容到缓冲区
	FILE* pSt_File = _xtfopen(lpszConfigFile, _X("rb"));
	if (NULL == pSt_File)
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_OPENFILE;
		return false;
	}
	size_t nCount = 0;
	XCHAR tszMsgBuffer[4096];
	while (1)
	{
		size_t nRet = fread(tszMsgBuffer + nCount, 1, 2048, pSt_File);
		if (nRet <= 0)
		{
			break;
		}
		nCount += nRet;
	}
	fclose(pSt_File);
	//开始解析配置文件
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonBuilder.newCharReader());
	if (!pSt_JsonReader->parse(tszMsgBuffer, tszMsgBuffer + nCount, &st_JsonRoot, &st_JsonError))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARSE;
		return false;
	}
	_tcsxcpy(pSt_ServerConfig->tszIPAddr, st_JsonRoot["tszIPAddr"].asCString());
	pSt_ServerConfig->bDeamon = st_JsonRoot["bDeamon"].asBool();
	pSt_ServerConfig->bHideWnd = st_JsonRoot["bHideWnd"].asBool();
	pSt_ServerConfig->nHttpPort = st_JsonRoot["nHttpPort"].asInt();
	pSt_ServerConfig->nRFCPort = st_JsonRoot["nRFCPort"].asInt();

	if (st_JsonRoot["XMax"].empty() || (4 != st_JsonRoot["XMax"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XMAX;
		return false;
	}
	Json::Value st_JsonXMax = st_JsonRoot["XMax"];
	pSt_ServerConfig->st_XMax.nMaxClient = st_JsonXMax["nMaxClient"].asInt();
	pSt_ServerConfig->st_XMax.nMaxQueue = st_JsonXMax["nMaxQueue"].asInt();
	pSt_ServerConfig->st_XMax.nIOThread = st_JsonXMax["nIOThread"].asInt();
	pSt_ServerConfig->st_XMax.nHTTPThread = st_JsonXMax["nHttpThread"].asInt();

	if (st_JsonRoot["XTime"].empty() || (3 != st_JsonRoot["XTime"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XTIME;
		return false;
	}
	Json::Value st_JsonXTime = st_JsonRoot["XTime"];
	pSt_ServerConfig->st_XTime.nTimeCheck = st_JsonXTime["nTimeCheck"].asInt();
	pSt_ServerConfig->st_XTime.nHTTPTimeOut = st_JsonXTime["nHttpTimeOut"].asInt();
	pSt_ServerConfig->st_XTime.nP2PTimeOut = st_JsonXTime["nP2PTimeOut"].asInt();

	if (st_JsonRoot["XLog"].empty() || (6 != st_JsonRoot["XLog"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XLOG;
		return false;
	}
	Json::Value st_JsonXLog = st_JsonRoot["XLog"];
	pSt_ServerConfig->st_XLog.nMaxSize = st_JsonXLog["MaxSize"].asInt();
	pSt_ServerConfig->st_XLog.nMaxCount = st_JsonXLog["MaxCount"].asInt();
	pSt_ServerConfig->st_XLog.nLogLeave = st_JsonXLog["LogLeave"].asInt();
	pSt_ServerConfig->st_XLog.nLogType = st_JsonXLog["LogType"].asInt();
	_tcsxcpy(pSt_ServerConfig->st_XLog.tszAPIFile, st_JsonXLog["tszAPIFile"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XLog.tszServiceFile, st_JsonXLog["tszServiceFile"].asCString());

	if (st_JsonRoot["XApi"].empty() || (5 != st_JsonRoot["XApi"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XAPI;
		return false;
	}
	Json::Value st_JsonXApi = st_JsonRoot["XApi"];

	_tcsxcpy(pSt_ServerConfig->st_XApi.tszWeatherUrl, st_JsonXApi["tszWeatherUrl"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XApi.tszBankUrl, st_JsonXApi["tszBankUrl"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XApi.tszOilUrl, st_JsonXApi["tszOilUrl"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XApi.tszTranslationUrl, st_JsonXApi["tszTranslationUrl"].asCString());
	Json::Value st_JsonTranslationInfo = st_JsonXApi["st_TranslationInfo"];
	_tcsxcpy(pSt_ServerConfig->st_XApi.st_TranslationInfo.tszAPPID, st_JsonTranslationInfo["appid"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XApi.st_TranslationInfo.tszAPPKey, st_JsonTranslationInfo["key"].asCString());

	if (st_JsonRoot["XSql"].empty() || (5 != st_JsonRoot["XSql"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XDB;
		return false;
	}
	Json::Value st_JsonXSql = st_JsonRoot["XSql"];

	pSt_ServerConfig->st_XSql.bEnable = st_JsonXSql["bEnable"].asBool();
	pSt_ServerConfig->st_XSql.nSQLPort = st_JsonXSql["SQLPort"].asInt();
	_tcsxcpy(pSt_ServerConfig->st_XSql.tszSQLAddr, st_JsonXSql["SQLAddr"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XSql.tszSQLUser, st_JsonXSql["SQLUser"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XSql.tszSQLPass, st_JsonXSql["SQLPass"].asCString());

	if (st_JsonRoot["XPlugin"].empty() || (2 != st_JsonRoot["XPlugin"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XPLUGIN;
		return false;
	}
	Json::Value st_JsonXPlugin = st_JsonRoot["XPlugin"];
	pSt_ServerConfig->st_XPlugin.bEnable = st_JsonXPlugin["bEnable"].asBool();
	_tcsxcpy(pSt_ServerConfig->st_XPlugin.tszPlugin, st_JsonXPlugin["tszPlugin"].asCString());

	if (st_JsonRoot["XConfig"].empty() || (4 != st_JsonRoot["XConfig"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XCONFIG;
		return false;
	}
	Json::Value st_JsonXConfig = st_JsonRoot["XConfig"];

	_tcsxcpy(pSt_ServerConfig->st_XConfig.st_ConfigQRCodec.tszModelDetect, st_JsonXConfig["st_ConfigQRCode"]["tszModelDetect"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XConfig.st_ConfigQRCodec.tszModelSr, st_JsonXConfig["st_ConfigQRCode"]["tszModelSr"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XConfig.st_ConfigQRCodec.tszProtoDetect, st_JsonXConfig["st_ConfigQRCode"]["tszProtoDetect"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XConfig.st_ConfigQRCodec.tszProtoSr, st_JsonXConfig["st_ConfigQRCode"]["tszProtoSr"].asCString());

	_tcsxcpy(pSt_ServerConfig->st_XConfig.tszConfigDeamon, st_JsonXConfig["tszConfigDeamon"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XConfig.tszConfigHTTPMime, st_JsonXConfig["tszConfigHTTPMime"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XConfig.tszConfigHTTPCode, st_JsonXConfig["tszConfigHTTPCode"].asCString());

	if (st_JsonRoot["XShortLink"].empty() || (2 != st_JsonRoot["XShortLink"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XSLINK;
		return false;
	}
	Json::Value st_JsonXShort = st_JsonRoot["XShortLink"];
	_tcsxcpy(pSt_ServerConfig->st_XShortLink.tszHostUrl, st_JsonXShort["tszHostUrl"].asCString());
	pSt_ServerConfig->st_XShortLink.nHTTPCode = st_JsonXShort["nHTTPCode"].asInt();

	if (st_JsonRoot["XImageText"].empty() || (3 != st_JsonRoot["XImageText"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XIMAGETEXT;
		return false;
	}
	Json::Value st_JsonXImageText = st_JsonRoot["XImageText"];
	pSt_ServerConfig->st_XImageText.bEnable = st_JsonXImageText["bEnable"].asBool();
	_tcsxcpy(pSt_ServerConfig->st_XImageText.tszImagePath, st_JsonXImageText["tszImagePath"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XImageText.tszImageLanguage, st_JsonXImageText["tszImageLanguage"].asCString());

	if (st_JsonRoot["XVerification"].empty() || (3 != st_JsonRoot["XVerification"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XVERICATION;
		return false;
	}
	Json::Value st_JsonXVerifcation = st_JsonRoot["XVerification"];
	_tcsxcpy(pSt_ServerConfig->st_XVerifcation.tszUserName, st_JsonXVerifcation["tszUserName"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XVerifcation.tszUserPass, st_JsonXVerifcation["tszUserPass"].asCString());
	
	Json::Value st_JsonVerSwitch = st_JsonXVerifcation["st_VerSwitch"];
	pSt_ServerConfig->st_XVerifcation.st_VerSwitch.bBackService = st_JsonVerSwitch["bBackService"].asBool();
	pSt_ServerConfig->st_XVerifcation.st_VerSwitch.bDeamon = st_JsonVerSwitch["bDeamon"].asBool();

	if (st_JsonRoot["XAPIModule"].empty() || (5 != st_JsonRoot["XAPIModule"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XREPORT;
		return false;
	}
	Json::Value st_JsonXAPIModule = st_JsonRoot["XAPIModule"];
	pSt_ServerConfig->st_XAPIModule.bEnable = st_JsonXAPIModule["bEnable"].asBool();
	_tcsxcpy(pSt_ServerConfig->st_XAPIModule.tszDBIPAddr, st_JsonXAPIModule["tszDBIPAddr"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XAPIModule.tszDBISPAddr, st_JsonXAPIModule["tszDBISPAddr"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XAPIModule.tszDBMac, st_JsonXAPIModule["tszDBMac"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XAPIModule.tszDBPhone, st_JsonXAPIModule["tszDBPhone"].asCString());

	if (st_JsonRoot["XReport"].empty() || (3 != st_JsonRoot["XReport"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XREPORT;
		return false;
	}
	Json::Value st_JsonXReport = st_JsonRoot["XReport"];

	pSt_ServerConfig->st_XReport.bEnable = st_JsonXReport["bEnable"].asBool();
	_tcsxcpy(pSt_ServerConfig->st_XReport.tszAPIUrl, st_JsonXReport["tszAPIUrl"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XReport.tszServiceName, st_JsonXReport["tszServiceName"].asCString());
	return true;
}
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
bool CModuleConfigure_Json::ModuleConfigure_Json_VersionFile(LPCXSTR lpszConfigFile, XENGINE_SERVICECONFIG* pSt_ServerConfig)
{
	Config_IsErrorOccur = false;

	if ((NULL == lpszConfigFile) || (NULL == pSt_ServerConfig))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//读取配置文件所有内容到缓冲区
	FILE* pSt_File = _xtfopen(lpszConfigFile, _X("rb"));
	if (NULL == pSt_File)
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_OPENFILE;
		return false;
	}
	size_t nCount = 0;
	XCHAR tszMsgBuffer[4096];
	while (1)
	{
		size_t nRet = fread(tszMsgBuffer + nCount, 1, 2048, pSt_File);
		if (nRet <= 0)
		{
			break;
		}
		nCount += nRet;
	}
	fclose(pSt_File);
	//开始解析配置文件
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonBuilder.newCharReader());
	if (!pSt_JsonReader->parse(tszMsgBuffer, tszMsgBuffer + nCount, &st_JsonRoot, &st_JsonError))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARSE;
		return false;
	}
	
	if (st_JsonRoot["XVer"].empty())
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XVER;
		return false;
	}
	pSt_ServerConfig->st_XVer.pStl_ListVer = new list<string>;
	if (NULL == pSt_ServerConfig->st_XVer.pStl_ListVer)
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_MALLOC;
		return false;
	}
	Json::Value st_JsonXVer = st_JsonRoot["XVer"];
	for (unsigned int i = 0; i < st_JsonXVer.size(); i++)
	{
		pSt_ServerConfig->st_XVer.pStl_ListVer->push_back(st_JsonXVer[i].asCString());
	}
	return true;
}
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
bool CModuleConfigure_Json::ModuleConfigure_Json_PluginFile(LPCXSTR lpszConfigFile, XENGINE_PLUGINCONFIG* pSt_PluginConfig)
{
	Config_IsErrorOccur = false;

	if ((NULL == lpszConfigFile) || (NULL == pSt_PluginConfig))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARAMENT;
		return false;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//读取配置文件所有内容到缓冲区
	FILE* pSt_File = _xtfopen(lpszConfigFile, _X("rb"));
	if (NULL == pSt_File)
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_OPENFILE;
		return false;
	}
	size_t nCount = 0;
	XCHAR tszMsgBuffer[4096];
	while (1)
	{
		size_t nRet = fread(tszMsgBuffer + nCount, 1, 2048, pSt_File);
		if (nRet <= 0)
		{
			break;
		}
		nCount += nRet;
	}
	fclose(pSt_File);
	//开始解析配置文件
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonBuilder.newCharReader());
	if (!pSt_JsonReader->parse(tszMsgBuffer, tszMsgBuffer + nCount, &st_JsonRoot, &st_JsonError))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARSE;
		return false;
	}
	//申请内存
	pSt_PluginConfig->pStl_ListPluginLua = new list<XENGINE_PLUGININFO>;
	pSt_PluginConfig->pStl_ListPluginModule = new list<XENGINE_PLUGININFO>;
	if (NULL == pSt_PluginConfig->pStl_ListPluginLua || NULL == pSt_PluginConfig->pStl_ListPluginModule)
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_MALLOC;
		return false;
	}
	//解析module列表
	Json::Value st_JsonModuleArray = st_JsonRoot["PluginModule"];
	for (unsigned int i = 0; i < st_JsonModuleArray.size(); i++)
	{
		XENGINE_PLUGININFO st_PluginInfo;
		memset(&st_PluginInfo, '\0', sizeof(XENGINE_PLUGININFO));

		st_PluginInfo.bEnable = st_JsonModuleArray[i]["PluginEnable"].asBool();
		_tcsxcpy(st_PluginInfo.tszPluginFile, st_JsonModuleArray[i]["PluginFile"].asCString());
#ifdef _MSC_BUILD
		_tcsxcat(st_PluginInfo.tszPluginFile, ".dll");
#elif __linux__
		_tcsxcat(st_PluginInfo.tszPluginFile, ".so");
#else
		_tcsxcat(st_PluginInfo.tszPluginFile, ".dylib");
#endif
		_tcsxcpy(st_PluginInfo.tszPluginMethod, st_JsonModuleArray[i]["PluginMethod"].asCString());

		pSt_PluginConfig->pStl_ListPluginModule->push_back(st_PluginInfo);
	}
	//解析lua列表
	Json::Value st_JsonLuaArray = st_JsonRoot["PluginLua"];
	for (unsigned int i = 0; i < st_JsonLuaArray.size(); i++)
	{
		XENGINE_PLUGININFO st_PluginInfo;
		memset(&st_PluginInfo, '\0', sizeof(XENGINE_PLUGININFO));

		st_PluginInfo.bEnable = st_JsonLuaArray[i]["PluginEnable"].asBool();
		_tcsxcpy(st_PluginInfo.tszPluginFile, st_JsonLuaArray[i]["PluginFile"].asCString());
		_tcsxcpy(st_PluginInfo.tszPluginMethod, st_JsonLuaArray[i]["PluginMethod"].asCString());

		pSt_PluginConfig->pStl_ListPluginLua->push_back(st_PluginInfo);
	}
	return true;
}
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
bool CModuleConfigure_Json::ModuleConfigure_Json_DeamonList(LPCXSTR lpszConfigFile, XENGINE_DEAMONAPPLIST* pSt_AppConfig)
{
	Config_IsErrorOccur = false;

	if ((NULL == lpszConfigFile) || (NULL == pSt_AppConfig))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARAMENT;
		return false;
	}
	JSONCPP_STRING st_JsonError;
	Json::Value st_JsonRoot;
	Json::CharReaderBuilder st_JsonBuilder;

	FILE* pSt_File = fopen(lpszConfigFile, "rb");
	if (NULL == pSt_File)
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_OPENFILE;
		return false;
	}
	int nCount = 0;
	XCHAR tszMsgBuffer[4096];
	while (1)
	{
		int nRet = fread(tszMsgBuffer + nCount, 1, 2048, pSt_File);
		if (nRet <= 0)
		{
			break;
		}
		nCount += nRet;
	}
	fclose(pSt_File);

	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonBuilder.newCharReader());
	if (!pSt_JsonReader->parse(tszMsgBuffer, tszMsgBuffer + nCount, &st_JsonRoot, &st_JsonError))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARSE;
		return false;
	}

	Json::Value st_JsonArray = st_JsonRoot["ListArray"];
	for (unsigned int i = 0; i < st_JsonRoot["ListArray"].size(); i++)
	{
		XENGINE_DEAMONAPPINFO st_APPInfo;
		memset(&st_APPInfo, '\0', sizeof(XENGINE_DEAMONAPPINFO));

		strcpy(st_APPInfo.tszAPPName, st_JsonArray[i]["tszAPPName"].asCString());
		strcpy(st_APPInfo.tszAPPPath, st_JsonArray[i]["tszAPPPath"].asCString());
		st_APPInfo.bEnable = st_JsonArray[i]["bEnable"].asBool();
		st_APPInfo.nReTime = st_JsonArray[i]["nAPPReTime"].asInt();
		st_APPInfo.nReNumber = st_JsonArray[i]["nAPPReNumber"].asInt();

		pSt_AppConfig->stl_ListDeamonApp.push_back(st_APPInfo);
	}
	return true;
}