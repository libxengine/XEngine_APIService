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
	pSt_ServerConfig->bAutoStart = st_JsonRoot["bAutoStart"].asBool();
	pSt_ServerConfig->bHideWnd = st_JsonRoot["bHideWnd"].asBool();
	pSt_ServerConfig->nHttpPort = st_JsonRoot["nHttpPort"].asInt();

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

	if (st_JsonRoot["XTime"].empty() || (4 != st_JsonRoot["XTime"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XTIME;
		return false;
	}
	Json::Value st_JsonXTime = st_JsonRoot["XTime"];
	pSt_ServerConfig->st_XTime.nTimeCheck = st_JsonXTime["nTimeCheck"].asInt();
	pSt_ServerConfig->st_XTime.nHTTPTimeOut = st_JsonXTime["nHttpTimeOut"].asInt();
	pSt_ServerConfig->st_XTime.nP2PTimeOut = st_JsonXTime["nP2PTimeOut"].asInt();
	pSt_ServerConfig->st_XTime.nDeamonTime = st_JsonXTime["nDeamonTime"].asInt();

	if (st_JsonRoot["XLog"].empty() || (3 != st_JsonRoot["XLog"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XLOG;
		return false;
	}
	Json::Value st_JsonXLog = st_JsonRoot["XLog"];
	pSt_ServerConfig->st_XLog.nMaxSize = st_JsonXLog["MaxSize"].asInt();
	pSt_ServerConfig->st_XLog.nMaxCount = st_JsonXLog["MaxCount"].asInt();
	pSt_ServerConfig->st_XLog.nLogLeave = st_JsonXLog["LogLeave"].asInt();

	if (st_JsonRoot["XApi"].empty() || (2 != st_JsonRoot["XApi"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XAPI;
		return false;
	}
	Json::Value st_JsonXApi = st_JsonRoot["XApi"];
	_tcsxcpy(pSt_ServerConfig->st_XApi.tszBankUrl, st_JsonXApi["tszBankUrl"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XApi.tszTranslationUrl, st_JsonXApi["tszTranslationUrl"].asCString());

	if (st_JsonRoot["XSql"].empty() || (4 != st_JsonRoot["XSql"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XDB;
		return false;
	}
	Json::Value st_JsonXSql = st_JsonRoot["XSql"];
	pSt_ServerConfig->st_XSql.nSQLPort = st_JsonXSql["SQLPort"].asInt();
	_tcsxcpy(pSt_ServerConfig->st_XSql.tszSQLAddr, st_JsonXSql["SQLAddr"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XSql.tszSQLUser, st_JsonXSql["SQLUser"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XSql.tszSQLPass, st_JsonXSql["SQLPass"].asCString());

	if (st_JsonRoot["XPlugin"].empty() || (3 != st_JsonRoot["XPlugin"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XPLUGIN;
		return false;
	}
	Json::Value st_JsonXPlugin = st_JsonRoot["XPlugin"];
	pSt_ServerConfig->st_XPlugin.bEnable = st_JsonXPlugin["bEnable"].asBool();
	_tcsxcpy(pSt_ServerConfig->st_XPlugin.tszPluginLib, st_JsonXPlugin["tszPluginLib"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XPlugin.tszPluginLua, st_JsonXPlugin["tszPluginLua"].asCString());

	if (st_JsonRoot["XConfig"].empty() || (2 != st_JsonRoot["XConfig"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XCONFIG;
		return false;
	}
	Json::Value st_JsonXConfig = st_JsonRoot["XConfig"];
	_tcsxcpy(pSt_ServerConfig->st_XConfig.tszConfigOPencc, st_JsonXConfig["tszConfigOPencc"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XConfig.tszConfigQRCode, st_JsonXConfig["tszConfigQRCode"].asCString());

	if (st_JsonRoot["XShortLink"].empty() || (2 != st_JsonRoot["XShortLink"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XSLINK;
		return false;
	}
	Json::Value st_JsonXShort = st_JsonRoot["XShortLink"];
	_tcsxcpy(pSt_ServerConfig->st_XShortLink.tszHostUrl, st_JsonXShort["tszHostUrl"].asCString());
	pSt_ServerConfig->st_XShortLink.nHTTPCode = st_JsonXShort["nHTTPCode"].asInt();

	if (st_JsonRoot["XVerification"].empty() || (4 != st_JsonRoot["XVerification"].size()))
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XVERICATION;
		return false;
	}
	Json::Value st_JsonXVerifcation = st_JsonRoot["XVerification"];
	_tcsxcpy(pSt_ServerConfig->st_XVerifcation.tszUserName, st_JsonXVerifcation["tszUserName"].asCString());
	_tcsxcpy(pSt_ServerConfig->st_XVerifcation.tszUserPass, st_JsonXVerifcation["tszUserPass"].asCString());
	pSt_ServerConfig->st_XVerifcation.bBackService = st_JsonXVerifcation["bBackService"].asBool();
	pSt_ServerConfig->st_XVerifcation.bDeamon = st_JsonXVerifcation["bDeamon"].asBool();

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
bool CModuleConfigure_Json::ModuleConfigure_Json_OPenccFile(LPCXSTR lpszConfigFile, XENGINE_OPENCCCONFIG* pSt_OPenccConfig)
{
	Config_IsErrorOccur = false;

	if ((NULL == lpszConfigFile) || (NULL == pSt_OPenccConfig))
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
	_tcsxcpy(pSt_OPenccConfig->tszFiles2t, st_JsonRoot["tszFiles2t"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFilet2s, st_JsonRoot["tszFilet2s"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFiles2tw, st_JsonRoot["tszFiles2tw"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFiletw2s, st_JsonRoot["tszFiletw2s"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFiles2hk, st_JsonRoot["tszFiles2hk"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFilehk2s, st_JsonRoot["tszFilehk2s"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFiles2twp, st_JsonRoot["tszFiles2twp"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFiletw2sp, st_JsonRoot["tszFiletw2sp"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFilet2tw, st_JsonRoot["tszFilet2tw"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFilehk2t, st_JsonRoot["tszFilehk2t"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFilet2hk, st_JsonRoot["tszFilet2hk"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFilet2jp, st_JsonRoot["tszFilet2jp"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFilejp2t, st_JsonRoot["tszFilejp2t"].asCString());
	_tcsxcpy(pSt_OPenccConfig->tszFiletw2t, st_JsonRoot["tszFiletw2t"].asCString());
	return true;
}
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
bool CModuleConfigure_Json::ModuleConfigure_Json_QRCodeFile(LPCXSTR lpszConfigFile, XENGINE_QRCODECONFIG* pSt_QRCodeConfig)
{
	Config_IsErrorOccur = false;

	if ((NULL == lpszConfigFile) || (NULL == pSt_QRCodeConfig))
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
	_tcsxcpy(pSt_QRCodeConfig->tszModelDetect, st_JsonRoot["tszModelDetect"].asCString());
	_tcsxcpy(pSt_QRCodeConfig->tszModelSr, st_JsonRoot["tszModelSr"].asCString());
	_tcsxcpy(pSt_QRCodeConfig->tszProtoDetect, st_JsonRoot["tszProtoDetect"].asCString());
	_tcsxcpy(pSt_QRCodeConfig->tszProtoSr, st_JsonRoot["tszProtoSr"].asCString());
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
	pSt_PluginConfig->pStl_ListPlugin = new list<XENGINE_PLUGININFO>;
	if (NULL == pSt_PluginConfig->pStl_ListPlugin)
	{
		Config_IsErrorOccur = true;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_MALLOC;
		return false;
	}
	//解析列表
	Json::Value st_JsonArray = st_JsonRoot["PluginArray"];
	for (unsigned int i = 0; i < st_JsonArray.size(); i++)
	{
		XENGINE_PLUGININFO st_PluginInfo;
		memset(&st_PluginInfo, '\0', sizeof(XENGINE_PLUGININFO));

		st_PluginInfo.bEnable = st_JsonArray[i]["PluginEnable"].asBool();
		_tcsxcpy(st_PluginInfo.tszPluginFile, st_JsonArray[i]["PluginFile"].asCString());

		if (NULL == _tcsxstr(st_PluginInfo.tszPluginFile + 3,_X(".")))
		{
#ifdef _MSC_BUILD
			_tcsxcat(st_PluginInfo.tszPluginFile, ".dll");
#elif __linux__
			_tcsxcat(st_PluginInfo.tszPluginFile, ".so");
#else
			_tcsxcat(st_PluginInfo.tszPluginFile, ".dylib");
#endif
		}

		_tcsxcpy(st_PluginInfo.tszPluginMethod, st_JsonArray[i]["PluginMethod"].asCString());
		pSt_PluginConfig->pStl_ListPlugin->push_back(st_PluginInfo);
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

		pSt_AppConfig->stl_ListDeamonApp.push_back(st_APPInfo);
	}
	return true;
}