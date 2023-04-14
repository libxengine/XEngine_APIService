#include "pch.h"
#include "Plugin_Timezone.h"
/********************************************************************
//    Created:     2022/07/20  09:56:34
//    File Name:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Timezone\Plugin_Timezone\Plugin_Timezone.cpp
//    File Path:   H:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Timezone\Plugin_Timezone
//    File Base:   Plugin_Timezone
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     时区工具库
//    History:
*********************************************************************/
CPlugin_Timezone::CPlugin_Timezone()
{
}
CPlugin_Timezone::~CPlugin_Timezone()
{
}
//////////////////////////////////////////////////////////////////////////
//                       公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：PluginCore_Init
函数功能：初始化插件模块
 参数.一：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：N
  意思：自定义参数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CPlugin_Timezone::PluginCore_Init(XPVOID lParam)
{
	Timezone_IsErrorOccur = FALSE;

	MODULEPLUGIN_TIMEZONE st_TimeZone;
	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));

	st_TimeZone.st_TimeZone.wHour = -12;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("国际日期变更线，西边"));
	stl_MapTimezone.insert(make_pair(_X("IDLE"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -11;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("阿拉斯加诺姆时间"));
	stl_MapTimezone.insert(make_pair(_X("NT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -10;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中阿拉斯加时间"));
	stl_MapTimezone.insert(make_pair(_X("CAT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -10;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("夏威夷标准时间"));
	stl_MapTimezone.insert(make_pair(_X("HST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -10;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("夏威夷-阿拉斯加标准时间"));
	stl_MapTimezone.insert(make_pair(_X("AHST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -9;
	st_TimeZone.st_TimeZone.wMinute = -30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("马克萨斯群岛时间"));
	stl_MapTimezone.insert(make_pair(_X("MART"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -9;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("夏威夷/阿拉斯加夏时制"));
	stl_MapTimezone.insert(make_pair(_X("HDT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -9;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("阿拉斯加标准时间"));
	stl_MapTimezone.insert(make_pair(_X("AKST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -8;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("育空地区标准时"));
	stl_MapTimezone.insert(make_pair(_X("YST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -8;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("太平洋标准时间"));
	stl_MapTimezone.insert(make_pair(_X("PST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -8;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("阿拉斯加白昼时间"));
	stl_MapTimezone.insert(make_pair(_X("AKDT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -7;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("太平洋夏时制"));
	stl_MapTimezone.insert(make_pair(_X("PDT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -7;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("山地标准时间"));
	stl_MapTimezone.insert(make_pair(_X("MST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -6;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("山地夏时制"));
	stl_MapTimezone.insert(make_pair(_X("MDT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -6;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中部标准时间"));
	stl_MapTimezone.insert(make_pair(_X("CST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -5;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("东部标准时间"));
	stl_MapTimezone.insert(make_pair(_X("EST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -5;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中部夏时制"));
	stl_MapTimezone.insert(make_pair(_X("CDT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -5;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("大西洋阿雷格里港 标准时间"));
	stl_MapTimezone.insert(make_pair(_X("ACT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -4;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("东部夏时制"));
	stl_MapTimezone.insert(make_pair(_X("EDT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -4;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("大西洋阿雷格里港夏令时"));
	stl_MapTimezone.insert(make_pair(_X("ACST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -4;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("大西洋标准时间（加拿大）"));
	stl_MapTimezone.insert(make_pair(_X("AST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -3;
	st_TimeZone.st_TimeZone.wMinute = -30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("纽芬兰（Newfoundland）标准时间"));
	stl_MapTimezone.insert(make_pair(_X("NST"), st_TimeZone));
	stl_MapTimezone.insert(make_pair(_X("NFT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -3;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("巴西利亚时间"));
	stl_MapTimezone.insert(make_pair(_X("BRT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -3;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("大西洋夏时制"));
	stl_MapTimezone.insert(make_pair(_X("ADT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -2;
	st_TimeZone.st_TimeZone.wMinute = -30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("纽芬兰夏时制"));
	stl_MapTimezone.insert(make_pair(_X("NDT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("巴西利亚夏令时"));
	stl_MapTimezone.insert(make_pair(_X("BRST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("巴西费尔南多·迪诺罗尼亚岛时间"));
	stl_MapTimezone.insert(make_pair(_X("FNT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -1;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("巴西费尔南多·迪诺罗尼亚岛 夏令时"));
	stl_MapTimezone.insert(make_pair(_X("FNST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = -1;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("西非时间"));
	stl_MapTimezone.insert(make_pair(_X("WAT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("西欧"));
	stl_MapTimezone.insert(make_pair(_X("WET"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("和 UTC 相同"));
	stl_MapTimezone.insert(make_pair(_X("ZULU"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("校准的全球时间"));
	stl_MapTimezone.insert(make_pair(_X("UTC"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("全球时间"));
	stl_MapTimezone.insert(make_pair(_X("UT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("格林尼治标准时间"));
	stl_MapTimezone.insert(make_pair(_X("GMT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 1;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("西欧光照利用时间"));
	stl_MapTimezone.insert(make_pair(_X("WETDST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 1;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("瑞典冬时制"));
	stl_MapTimezone.insert(make_pair(_X("SWT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 1;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("挪威标准时间"));
	stl_MapTimezone.insert(make_pair(_X("NOR"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 1;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中欧时间"));
	stl_MapTimezone.insert(make_pair(_X("MET"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 1;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("法国夏时制"));
	stl_MapTimezone.insert(make_pair(_X("FST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 1;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("丹麦正规时间"));
	stl_MapTimezone.insert(make_pair(_X("DNT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 1;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中欧时间"));
	stl_MapTimezone.insert(make_pair(_X("CET"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 1;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("英国夏时制"));
	stl_MapTimezone.insert(make_pair(_X("BST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("瑞典夏时制"));
	stl_MapTimezone.insert(make_pair(_X("SST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中欧白昼时间"));
	stl_MapTimezone.insert(make_pair(_X("METDST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中欧夏时制"));
	stl_MapTimezone.insert(make_pair(_X("MEST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("以色列标准时间"));
	stl_MapTimezone.insert(make_pair(_X("IST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("法国冬时制"));
	stl_MapTimezone.insert(make_pair(_X("FWT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("东欧"));
	stl_MapTimezone.insert(make_pair(_X("EET"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中欧夏时制"));
	stl_MapTimezone.insert(make_pair(_X("CETDST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中欧夏令时"));
	stl_MapTimezone.insert(make_pair(_X("CEST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 2;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("英国双重标准时间"));
	stl_MapTimezone.insert(make_pair(_X("BDST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 3;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("希腊地中海时间"));
	stl_MapTimezone.insert(make_pair(_X("HMT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 3;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("东欧夏时制"));
	stl_MapTimezone.insert(make_pair(_X("EETDST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 3;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("巴格达时间"));
	stl_MapTimezone.insert(make_pair(_X("BT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 3;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("科摩罗时间"));
	stl_MapTimezone.insert(make_pair(_X("EAT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 3;
	st_TimeZone.st_TimeZone.wMinute = 30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("伊朗时间"));
	stl_MapTimezone.insert(make_pair(_X("IRT"), st_TimeZone));
	stl_MapTimezone.insert(make_pair(_X("IT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 4;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("塞舌尔马埃岛时间"));
	stl_MapTimezone.insert(make_pair(_X("SCT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 4;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("法属留尼汪岛时间"));
	stl_MapTimezone.insert(make_pair(_X("RET"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 4;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("毛里求斯时间"));
	stl_MapTimezone.insert(make_pair(_X("MUT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 4;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("马达加斯加塔那那利佛时间"));
	stl_MapTimezone.insert(make_pair(_X("EAST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 4;
	st_TimeZone.st_TimeZone.wMinute = 30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("阿富汗时间"));
	stl_MapTimezone.insert(make_pair(_X("AFT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 5;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("法属凯尔盖朗岛时间"));
	stl_MapTimezone.insert(make_pair(_X("TFT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 5;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("马尔代夫时间"));
	stl_MapTimezone.insert(make_pair(_X("MVT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 5;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("英属印度洋领地时间"));
	stl_MapTimezone.insert(make_pair(_X("IOT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 6;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("哈萨克斯坦阿拉木图"));
	stl_MapTimezone.insert(make_pair(_X("ALMT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 6;
	st_TimeZone.st_TimeZone.wMinute = 30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("缅甸时间"));
	stl_MapTimezone.insert(make_pair(_X("MMT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 7;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("澳大利亚圣诞岛时间"));
	stl_MapTimezone.insert(make_pair(_X("CXT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 7;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("阿拉木图"));
	stl_MapTimezone.insert(make_pair(_X("ALMST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 7;
	st_TimeZone.st_TimeZone.wMinute = 30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("爪哇时间"));
	stl_MapTimezone.insert(make_pair(_X("JT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 8;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("西澳大利亚标准时间"));
	stl_MapTimezone.insert(make_pair(_X("WST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 8;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中国北京时间"));
	stl_MapTimezone.insert(make_pair(_X("CCT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 8;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("澳大利亚西部标准时间"));
	stl_MapTimezone.insert(make_pair(_X("AWST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 9;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("韩国朝鲜标准时间"));
	stl_MapTimezone.insert(make_pair(_X("KST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 9;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("日本标准时间"));
	stl_MapTimezone.insert(make_pair(_X("JST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 9;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("马绍尔群岛瓜加林岛时间"));
	stl_MapTimezone.insert(make_pair(_X("MHT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 9;
	st_TimeZone.st_TimeZone.wMinute = 30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中澳大利亚标准时间"));
	stl_MapTimezone.insert(make_pair(_X("CAST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 9;
	st_TimeZone.st_TimeZone.wMinute = 30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("南澳大利亚标准时间"));
	stl_MapTimezone.insert(make_pair(_X("SAST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 10;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("澳大利亚墨尔本"));
	stl_MapTimezone.insert(make_pair(_X("LIGT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 10;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("关岛标准时间"));
	stl_MapTimezone.insert(make_pair(_X("GST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 10;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("东澳大利亚标准时间"));
	stl_MapTimezone.insert(make_pair(_X("EAST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 10;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("澳大利亚东部标准时间"));
	stl_MapTimezone.insert(make_pair(_X("AEST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 10;
	st_TimeZone.st_TimeZone.wMinute = 30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("南澳大利亚夏时制"));
	stl_MapTimezone.insert(make_pair(_X("SADT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 10;
	st_TimeZone.st_TimeZone.wMinute = 30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中澳大利亚夏时制"));
	stl_MapTimezone.insert(make_pair(_X("CADT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 10;
	st_TimeZone.st_TimeZone.wMinute = 30;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("中澳大利亚标准夏时制"));
	stl_MapTimezone.insert(make_pair(_X("ACSST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 11;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("澳大利亚东部标准夏时制"));
	stl_MapTimezone.insert(make_pair(_X("AESST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 12;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("新西兰标准时间"));
	stl_MapTimezone.insert(make_pair(_X("NZST"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 12;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("新西兰时间"));
	stl_MapTimezone.insert(make_pair(_X("NZT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 12;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("国际日期变更线，东边"));
	stl_MapTimezone.insert(make_pair(_X("IDLW"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 13;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("新西兰夏时制"));
	stl_MapTimezone.insert(make_pair(_X("NZDT"), st_TimeZone));

	memset(&st_TimeZone, '\0', sizeof(MODULEPLUGIN_TIMEZONE));
	st_TimeZone.st_TimeZone.wHour = 14;
	_tcsxcpy(st_TimeZone.tszTimeCountry, _X("基里巴斯线岛时间"));
	stl_MapTimezone.insert(make_pair(_X("KLT"), st_TimeZone));
    return TRUE;
}
/********************************************************************
函数名称：PluginCore_UnInit
函数功能：卸载插件
返回值
  类型：无
  意思：
备注：
*********************************************************************/
void CPlugin_Timezone::PluginCore_UnInit()
{
	Timezone_IsErrorOccur = FALSE;

	stl_MapTimezone.clear();
}
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CPlugin_Timezone::PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	Timezone_IsErrorOccur = FALSE;

	if ((NULL == pInt_HTTPCode) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		Timezone_IsErrorOccur = TRUE;
		Timezone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_TIMEZONE_PARAMENT;
		return FALSE;
	}
	XCHAR tszKeyName[128];
	XCHAR tszParamType[128];
	XCHAR tszParamCvt[128];
	XCHAR tszParamTime[128];

	memset(tszKeyName, '\0', sizeof(tszKeyName));
	memset(tszParamType, '\0', sizeof(tszParamType));
	memset(tszParamCvt, '\0', sizeof(tszParamCvt));
	memset(tszParamTime, '\0', sizeof(tszParamTime));

	BaseLib_OperatorString_GetKeyValue((*pppHDRList)[1], "=", tszKeyName, tszParamType);
	if (0 == _ttxoi(tszParamType))
	{
		//如果是统计
		Plugin_Timezone_Count(ptszMsgBuffer, pInt_MsgLen);
	}
	else if (1 == _ttxoi(tszParamType))
	{
		//如果是列举
		BaseLib_OperatorString_GetKeyValue((*pppHDRList)[2], "=", tszKeyName, tszParamCvt);
		Plugin_Timezone_List(tszParamCvt, ptszMsgBuffer, pInt_MsgLen);
	}
	else if (2 == _ttxoi(tszParamType))
	{
		//如果是转换
		BaseLib_OperatorString_GetKeyValue((*pppHDRList)[2], "=", tszKeyName, tszParamCvt);
		BaseLib_OperatorString_GetKeyValue((*pppHDRList)[3], "=", tszKeyName, tszParamTime);
		if (!Plugin_Timezone_Convert(tszParamCvt, tszParamTime, ptszMsgBuffer, pInt_MsgLen))
		{
			*pInt_HTTPCode = 404;
			return FALSE;
		}
	}
	*pInt_HTTPCode = 200;
	
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////
XBOOL CPlugin_Timezone::Plugin_Timezone_Count(XCHAR* ptszMsgBufer, int* pInt_Len)
{
	Timezone_IsErrorOccur = FALSE;

	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	st_JsonObject["Count"] = (Json::Value::UInt)stl_MapTimezone.size();
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_Len = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBufer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_Len);
	return TRUE;
}
XBOOL CPlugin_Timezone::Plugin_Timezone_List(LPCXSTR lpszConvert, XCHAR* ptszMsgBufer, int* pInt_Len)
{
	Timezone_IsErrorOccur = FALSE;

	int nPosStart = 0;
	int nPosEnd = 0;
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	_stxscanf(lpszConvert, _X("%d-%d"), &nPosStart, &nPosEnd);

	unordered_map<string, MODULEPLUGIN_TIMEZONE>::const_iterator stl_MapIterator = stl_MapTimezone.cbegin();
	for (int i = 0; stl_MapIterator != stl_MapTimezone.cend(); stl_MapIterator++, i++)
	{
		if ((nPosEnd >= i) && (nPosStart <= i))
		{
			Json::Value st_JsonArray;
			st_JsonArray["tszTimeZone"] = stl_MapIterator->first.c_str();
			st_JsonArray["tszTimeCountry"] = stl_MapIterator->second.tszTimeCountry;
			st_JsonObject.append(st_JsonArray);
		}
	}
	st_JsonRoot["Array"] = st_JsonObject;
	st_JsonRoot["Count"] = nPosEnd - nPosStart;
	st_JsonRoot["nPosStat"] = nPosStart;
	st_JsonRoot["nPosEnd"] = nPosEnd;
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_Len = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBufer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_Len);
	return TRUE;
}
XBOOL CPlugin_Timezone::Plugin_Timezone_Convert(LPCXSTR lpszConvert, LPCXSTR lpszTimeStr, XCHAR* ptszMsgBufer, int* pInt_Len)
{
	Timezone_IsErrorOccur = FALSE;

	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;

	unordered_map<string, MODULEPLUGIN_TIMEZONE>::const_iterator stl_MapIterator = stl_MapTimezone.find(lpszConvert);
	if (stl_MapIterator == stl_MapTimezone.end())
	{
		return FALSE;
	}
	XCHAR tszTimeStr[64];
	XENGINE_LIBTIMER st_TimeStart;
	XENGINE_LIBTIMER st_TimeEnd;

	memset(tszTimeStr, '\0', sizeof(tszTimeStr));
	memset(&st_TimeStart, '\0', sizeof(XENGINE_LIBTIMER));
	memset(&st_TimeEnd, '\0', sizeof(XENGINE_LIBTIMER));

	st_TimeEnd = stl_MapIterator->second.st_TimeZone;

	_stxscanf(lpszTimeStr, _X("%04d-%02d-%02d_%02d:%02d:%02d"), &st_TimeStart.wYear, &st_TimeStart.wMonth, &st_TimeStart.wDay, &st_TimeStart.wHour, &st_TimeStart.wMinute, &st_TimeStart.wSecond);
	BaseLib_OperatorTimeSpan_CalForStu(&st_TimeStart, &st_TimeEnd);
	_xstprintf(tszTimeStr, _X("%04d-%02d-%02d %02d:%02d:%02d"), st_TimeEnd.wYear, st_TimeEnd.wMonth, st_TimeEnd.wDay, st_TimeEnd.wHour, st_TimeEnd.wMinute, st_TimeEnd.wSecond);

	st_JsonObject["tszTimeStr"] = tszTimeStr;
	st_JsonObject["tszTimeZone"] = stl_MapIterator->first.c_str();
	st_JsonObject["tszTimeCountry"] = stl_MapIterator->second.tszTimeCountry;
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_Len = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBufer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_Len);
	return TRUE;
}