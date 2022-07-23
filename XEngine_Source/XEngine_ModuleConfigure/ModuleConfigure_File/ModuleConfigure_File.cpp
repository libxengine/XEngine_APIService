#include "pch.h"
#include "ModuleConfigure_File.h"
/********************************************************************
//    Created:     2022/07/21  17:07:28
//    File Name:   H:\XEngine_APIService\XEngine_Source\XEngine_ModuleConfigure\ModuleConfigure_File\ModuleConfigure_File.cpp
//    File Path:   H:\XEngine_APIService\XEngine_Source\XEngine_ModuleConfigure\ModuleConfigure_File
//    File Base:   ModuleConfigure_File
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     文件信息读写
//    History:
*********************************************************************/
CModuleConfigure_File::CModuleConfigure_File()
{

}
CModuleConfigure_File::~CModuleConfigure_File()
{

}
//////////////////////////////////////////////////////////////////////////
//                        公用函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleConfigure_File_OPtion
函数功能：服务器可用方法查询配置文件
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要读取的配置文件
 参数.二：pSt_OPtionList
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出信息列表
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleConfigure_File::ModuleConfigure_File_OPtion(LPCTSTR lpszConfigFile, XENGINE_OPTIONLIST* pSt_OPtionList)
{
	Config_IsErrorOccur = FALSE;

	if ((NULL == lpszConfigFile) || (NULL == pSt_OPtionList))
	{
		Config_IsErrorOccur = TRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_FILE_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//读取配置文件所有内容到缓冲区
	FILE* pSt_File = _tfopen(lpszConfigFile, _T("rb"));
	if (NULL == pSt_File)
	{
		Config_IsErrorOccur = TRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_FILE_OPENFILE;
		return FALSE;
	}
	size_t nCount = 0;
	TCHAR tszMsgBuffer[4096];
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
		Config_IsErrorOccur = TRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_FILE_PARSE;
		return FALSE;
	}

	if (st_JsonRoot["OPTionBase"].empty())
	{
		Config_IsErrorOccur = TRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_FILE_BASE;
		return FALSE;
	}
	if (st_JsonRoot["OPTionPlugin"].empty())
	{
		Config_IsErrorOccur = TRUE;
		Config_dwErrorCode = ERROR_MODULE_CONFIGURE_JSON_PLUGIN;
		return FALSE;
	}
	Json::Value st_JsonBase = st_JsonRoot["OPTionBase"];
	for (unsigned int i = 0; i < st_JsonBase.size(); i++)
	{
		XENGINE_OPTIONINFO st_OPTionInfo;
		memset(&st_OPTionInfo, '\0', sizeof(XENGINE_OPTIONINFO));

		st_OPTionInfo.bEnable = st_JsonBase[i]["OPTionEnable"].asBool();
		_tcscpy(st_OPTionInfo.tszOPMethod, st_JsonBase[i]["OPTionMethod"].asCString());
		_tcscpy(st_OPTionInfo.tszOPNote, st_JsonBase[i]["OPTionNote"].asCString());
		_tcscpy(st_OPTionInfo.tszOPExample, st_JsonBase[i]["OPTionExample"].asCString());

		pSt_OPtionList->stl_ListBase.push_back(st_OPTionInfo);
	}
	Json::Value st_JsonPlug = st_JsonRoot["OPTionPlugin"];
	for (unsigned int i = 0; i < st_JsonPlug.size(); i++)
	{
		XENGINE_OPTIONINFO st_OPTionInfo;
		memset(&st_OPTionInfo, '\0', sizeof(XENGINE_OPTIONINFO));

		st_OPTionInfo.bEnable = st_JsonPlug[i]["OPTionEnable"].asBool();
		_tcscpy(st_OPTionInfo.tszOPMethod, st_JsonPlug[i]["OPTionMethod"].asCString());
		_tcscpy(st_OPTionInfo.tszOPNote, st_JsonPlug[i]["OPTionNote"].asCString());
		_tcscpy(st_OPTionInfo.tszOPExample, st_JsonPlug[i]["OPTionExample"].asCString());

		pSt_OPtionList->stl_ListPlug.push_back(st_OPTionInfo);
	}
	return TRUE;
}