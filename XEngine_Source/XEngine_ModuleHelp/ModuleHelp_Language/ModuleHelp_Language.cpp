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
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ZH == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("zh"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_EN == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("en"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_YUE == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("yue"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_WYW == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("wyw"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_JP == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("jp"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_KOR == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("kor"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_FRA == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("fra"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_SPA == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("spa"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_TH == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("th"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_DE == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("de"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_IT == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("it"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_EL == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("el"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_NL == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("nl"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_PL == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("pl"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_BUL == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("bul"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_EST == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("est"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_DAN == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("dan"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_FIN == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("fin"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_CS == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("cs"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_ROM == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("rom"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_SLO == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("slo"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_SWE == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("swe"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_HU == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("hu"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_CHT == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("cht"));
	}
	else if (ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE_VIE == enTranslationType)
	{
		_tcsxcpy(ptszTranslationType, _X("vie"));
	}
	else
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LANGUAGE_NOTSUPPORT;
		return false;
	}
	return true;
}