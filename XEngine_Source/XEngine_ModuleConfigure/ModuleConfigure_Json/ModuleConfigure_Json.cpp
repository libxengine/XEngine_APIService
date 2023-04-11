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
XBOOL CModuleConfigure_Json::ModuleConfigure_Json_File(LPCXSTR lpszConfigFile, XENGINE_SERVICECONFIG* pSt_ServerConfig)
{
	Config_IsErrorOccur = XFALSE;

	if ((NULL == lpszConfigFile) || (NULL == pSt_ServerConfig))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARAMENT;
		return XFALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//读取配置文件所有内容到缓冲区
	FILE* pSt_File = _tfopen(lpszConfigFile, _T("rb"));
	if (NULL == pSt_File)
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_OPENFILE;
		return XFALSE;
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
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARSE;
		return XFALSE;
	}
	_tcscpy(pSt_ServerConfig->tszIPAddr, st_JsonRoot["tszIPAddr"].asCString());
	pSt_ServerConfig->bDeamon = st_JsonRoot["bDeamon"].asInt();
	pSt_ServerConfig->nHttpPort = st_JsonRoot["nHttpPort"].asInt();

	if (st_JsonRoot["XMax"].empty() || (4 != st_JsonRoot["XMax"].size()))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XMAX;
		return XFALSE;
	}
	Json::Value st_JsonXMax = st_JsonRoot["XMax"];
	pSt_ServerConfig->st_XMax.nMaxClient = st_JsonXMax["nMaxClient"].asInt();
	pSt_ServerConfig->st_XMax.nMaxQueue = st_JsonXMax["nMaxQueue"].asInt();
	pSt_ServerConfig->st_XMax.nIOThread = st_JsonXMax["nIOThread"].asInt();
	pSt_ServerConfig->st_XMax.nHTTPThread = st_JsonXMax["nHttpThread"].asInt();

	if (st_JsonRoot["XTime"].empty() || (3 != st_JsonRoot["XTime"].size()))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XTIME;
		return XFALSE;
	}
	Json::Value st_JsonXTime = st_JsonRoot["XTime"];
	pSt_ServerConfig->st_XTime.nTimeCheck = st_JsonXTime["nTimeCheck"].asInt();
	pSt_ServerConfig->st_XTime.nHTTPTimeOut = st_JsonXTime["nHttpTimeOut"].asInt();
	pSt_ServerConfig->st_XTime.nP2PTimeOut = st_JsonXTime["nP2PTimeOut"].asInt();

	if (st_JsonRoot["XLog"].empty() || (3 != st_JsonRoot["XLog"].size()))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XLOG;
		return XFALSE;
	}
	Json::Value st_JsonXLog = st_JsonRoot["XLog"];
	pSt_ServerConfig->st_XLog.nMaxSize = st_JsonXLog["MaxSize"].asInt();
	pSt_ServerConfig->st_XLog.nMaxCount = st_JsonXLog["MaxCount"].asInt();
	pSt_ServerConfig->st_XLog.nLogLeave = st_JsonXLog["LogLeave"].asInt();

	if (st_JsonRoot["XApi"].empty() || (2 != st_JsonRoot["XApi"].size()))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XAPI;
		return XFALSE;
	}
	Json::Value st_JsonXApi = st_JsonRoot["XApi"];
	_tcscpy(pSt_ServerConfig->st_XApi.tszBankUrl, st_JsonXApi["tszBankUrl"].asCString());
	_tcscpy(pSt_ServerConfig->st_XApi.tszTranslationUrl, st_JsonXApi["tszTranslationUrl"].asCString());

	if (st_JsonRoot["XSql"].empty() || (4 != st_JsonRoot["XSql"].size()))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XDB;
		return XFALSE;
	}
	Json::Value st_JsonXSql = st_JsonRoot["XSql"];
	pSt_ServerConfig->st_XSql.nSQLPort = st_JsonXSql["SQLPort"].asInt();
	_tcscpy(pSt_ServerConfig->st_XSql.tszSQLAddr, st_JsonXSql["SQLAddr"].asCString());
	_tcscpy(pSt_ServerConfig->st_XSql.tszSQLUser, st_JsonXSql["SQLUser"].asCString());
	_tcscpy(pSt_ServerConfig->st_XSql.tszSQLPass, st_JsonXSql["SQLPass"].asCString());

	if (st_JsonRoot["XPlugin"].empty() || (3 != st_JsonRoot["XPlugin"].size()))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XPLUGIN;
		return XFALSE;
	}
	Json::Value st_JsonXPlugin = st_JsonRoot["XPlugin"];
	pSt_ServerConfig->st_XPlugin.bEnable = st_JsonXPlugin["bEnable"].asBool();
	_tcscpy(pSt_ServerConfig->st_XPlugin.tszPluginLib, st_JsonXPlugin["tszPluginLib"].asCString());
	_tcscpy(pSt_ServerConfig->st_XPlugin.tszPluginLua, st_JsonXPlugin["tszPluginLua"].asCString());

	if (st_JsonRoot["XConfig"].empty() || (2 != st_JsonRoot["XConfig"].size()))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XCONFIG;
		return XFALSE;
	}
	Json::Value st_JsonXConfig = st_JsonRoot["XConfig"];
	_tcscpy(pSt_ServerConfig->st_XConfig.tszConfigOPencc, st_JsonXConfig["tszConfigOPencc"].asCString());
	_tcscpy(pSt_ServerConfig->st_XConfig.tszConfigQRCode, st_JsonXConfig["tszConfigQRCode"].asCString());

	if (st_JsonRoot["XVer"].empty())
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_XVER;
		return XFALSE;
	}
	pSt_ServerConfig->st_XVer.pStl_ListVer = new list<string>;
	if (NULL == pSt_ServerConfig->st_XVer.pStl_ListVer)
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_MALLOC;
		return XFALSE;
	}
	Json::Value st_JsonXVer = st_JsonRoot["XVer"];
	for (unsigned int i = 0; i < st_JsonXVer.size(); i++)
	{
		pSt_ServerConfig->st_XVer.pStl_ListVer->push_back(st_JsonXVer[i].asCString());
	}
	return XTRUE;
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
XBOOL CModuleConfigure_Json::ModuleConfigure_Json_OPenccFile(LPCXSTR lpszConfigFile, XENGINE_OPENCCCONFIG* pSt_OPenccConfig)
{
	Config_IsErrorOccur = XFALSE;

	if ((NULL == lpszConfigFile) || (NULL == pSt_OPenccConfig))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARAMENT;
		return XFALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//读取配置文件所有内容到缓冲区
	FILE* pSt_File = _tfopen(lpszConfigFile, _T("rb"));
	if (NULL == pSt_File)
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_OPENFILE;
		return XFALSE;
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
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARSE;
		return XFALSE;
	}
	_tcscpy(pSt_OPenccConfig->tszFiles2t, st_JsonRoot["tszFiles2t"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFilet2s, st_JsonRoot["tszFilet2s"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFiles2tw, st_JsonRoot["tszFiles2tw"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFiletw2s, st_JsonRoot["tszFiletw2s"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFiles2hk, st_JsonRoot["tszFiles2hk"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFilehk2s, st_JsonRoot["tszFilehk2s"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFiles2twp, st_JsonRoot["tszFiles2twp"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFiletw2sp, st_JsonRoot["tszFiletw2sp"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFilet2tw, st_JsonRoot["tszFilet2tw"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFilehk2t, st_JsonRoot["tszFilehk2t"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFilet2hk, st_JsonRoot["tszFilet2hk"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFilet2jp, st_JsonRoot["tszFilet2jp"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFilejp2t, st_JsonRoot["tszFilejp2t"].asCString());
	_tcscpy(pSt_OPenccConfig->tszFiletw2t, st_JsonRoot["tszFiletw2t"].asCString());
	return XTRUE;
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
XBOOL CModuleConfigure_Json::ModuleConfigure_Json_QRCodeFile(LPCXSTR lpszConfigFile, XENGINE_QRCODECONFIG* pSt_QRCodeConfig)
{
	Config_IsErrorOccur = XFALSE;

	if ((NULL == lpszConfigFile) || (NULL == pSt_QRCodeConfig))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARAMENT;
		return XFALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//读取配置文件所有内容到缓冲区
	FILE* pSt_File = _tfopen(lpszConfigFile, _T("rb"));
	if (NULL == pSt_File)
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_OPENFILE;
		return XFALSE;
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
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARSE;
		return XFALSE;
	}
	_tcscpy(pSt_QRCodeConfig->tszModelDetect, st_JsonRoot["tszModelDetect"].asCString());
	_tcscpy(pSt_QRCodeConfig->tszModelSr, st_JsonRoot["tszModelSr"].asCString());
	_tcscpy(pSt_QRCodeConfig->tszProtoDetect, st_JsonRoot["tszProtoDetect"].asCString());
	_tcscpy(pSt_QRCodeConfig->tszProtoSr, st_JsonRoot["tszProtoSr"].asCString());
	return XTRUE;
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
XBOOL CModuleConfigure_Json::ModuleConfigure_Json_PluginFile(LPCXSTR lpszConfigFile, XENGINE_PLUGINCONFIG* pSt_PluginConfig)
{
	Config_IsErrorOccur = XFALSE;

	if ((NULL == lpszConfigFile) || (NULL == pSt_PluginConfig))
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARAMENT;
		return XFALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//读取配置文件所有内容到缓冲区
	FILE* pSt_File = _tfopen(lpszConfigFile, _T("rb"));
	if (NULL == pSt_File)
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_OPENFILE;
		return XFALSE;
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
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PARSE;
		return XFALSE;
	}
	//申请内存
	pSt_PluginConfig->pStl_ListPlugin = new list<XENGINE_PLUGININFO>;
	if (NULL == pSt_PluginConfig->pStl_ListPlugin)
	{
		Config_IsErrorOccur = XTRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_MALLOC;
		return XFALSE;
	}
	//解析列表
	Json::Value st_JsonArray = st_JsonRoot["PluginArray"];
	for (unsigned int i = 0; i < st_JsonArray.size(); i++)
	{
		XENGINE_PLUGININFO st_PluginInfo;
		memset(&st_PluginInfo, '\0', sizeof(XENGINE_PLUGININFO));

		st_PluginInfo.bEnable = st_JsonArray[i]["PluginEnable"].asBool();
		_tcscpy(st_PluginInfo.tszPluginFile, st_JsonArray[i]["PluginFile"].asCString());

		if (NULL == _tcsstr(st_PluginInfo.tszPluginFile + 3,_T(".")))
		{
#ifdef _MSC_BUILD
			_tcscat(st_PluginInfo.tszPluginFile, ".dll");
#elif __linux__
			_tcscat(st_PluginInfo.tszPluginFile, ".so");
#else
			_tcscat(st_PluginInfo.tszPluginFile, ".dylib");
#endif
		}

		_tcscpy(st_PluginInfo.tszPluginMethod, st_JsonArray[i]["PluginMethod"].asCString());
		pSt_PluginConfig->pStl_ListPlugin->push_back(st_PluginInfo);
	}
	return XTRUE;
}