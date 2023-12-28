#include "pch.h"
#include "ModuleHelp_Language.h"
/********************************************************************
//    Created:     2022/03/24  10:27:34
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Language\ModuleHelp_Language.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Language
//    File Base:   ModuleHelp_Language
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     语言转换
//    History:
*********************************************************************/
CModuleHelp_Language::CModuleHelp_Language()
{
}
CModuleHelp_Language::~CModuleHelp_Language()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleHelp_Language_ConvertZh
函数功能：中文语言转换
 参数.一：lpszJsonFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的配置文件
 参数.一：lpszSourceStr
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要转换的字符串
 参数.一：ptszDestStr
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的字符串
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_Language::ModuleHelp_Language_ConvertZh(LPCXSTR lpszJsonFile, LPCXSTR lpszSourceStr, XCHAR* ptszDestStr)
{
	ModuleHelp_IsErrorOccur = false;

	if ((NULL == lpszJsonFile) || (NULL == lpszSourceStr) || (NULL == ptszDestStr))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LANGUAGE_PARAMENT;
		return false;
	}
#if (1 == _XENGINE_BUILD_SWITCH_OPENCC)
	opencc_t m_OPencc = opencc_open(lpszJsonFile);
	if ((opencc_t)-1 == m_OPencc)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LANGUAGE_FAILED;
		return false;
	}
	if ((size_t)-1 == opencc_convert_utf8_to_buffer(m_OPencc, lpszSourceStr, strlen(lpszSourceStr), ptszDestStr))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LANGUAGE_NOTSUPPORT;
		return false;
	}
	opencc_close(m_OPencc);
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_Translation_Convert
函数功能：翻译类型转换
 参数.一：enTranslationType
  In/Out：In
  类型：枚举型
  可空：N
  意思：输入要转换的类型
 参数.二：ptszTranslationType
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的类型
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_Language::ModuleHelp_Translation_Convert(ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE enTranslationType, XCHAR* ptszTranslationType)
{
	ModuleHelp_IsErrorOccur = false;

	if (NULL == ptszTranslationType)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LANGUAGE_PARAMENT;
		return false;
	}
	//转换为服务需要的类型
	if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_AUTO == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("auto"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2EN == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("ZH_CN2EN"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2JA == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("ZH_CN2JA"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2KR == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("ZH_CN2KR"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2FR == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("ZH_CN2FR"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2RU == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("ZH_CN2RU"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH_CN2SP == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("ZH_CN2SP"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_EN2ZH_CN == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("EN2ZH_CN"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_JA2ZH_CN == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("JA2ZH_CN"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_KR2ZH_CN == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("KR2ZH_CN"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_FR2ZH_CN == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("FR2ZH_CN"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_RU2ZH_CN == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("RU2ZH_CN"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_SP2ZH_CN == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("SP2ZH_CN"));
	}
	else
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LANGUAGE_NOTSUPPORT;
		return false;
	}
	return true;
}