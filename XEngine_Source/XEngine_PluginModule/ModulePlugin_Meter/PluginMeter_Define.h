#pragma once
/********************************************************************
//    Created:     2022/11/01  13:56:53
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Meter\PluginMeter_Define.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Meter
//    File Base:   PluginMeter_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     计量转换插件
//    History:
*********************************************************************/
//长度计量
typedef enum
{
	//美国标准
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_KILOMETRE = 0,                     //公里
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_METRE = 1,                         //米
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_DECIMETER = 2,                     //分米
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_CENTIMEER = 3,                     //厘米
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_MILLMETER = 4,                     //毫米
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_MICROMETER = 5,                    //微米
	//中国标准
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_LI = 10,                           //里
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_ZHANG = 11,                        //丈
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_CHI = 12,                          //尺
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_CUN = 13,                          //寸
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_FEN = 14,                          //分
	//英国标准
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_NAUTICALMILE = 20,                 //海里
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_MILE = 21,                         //英里
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_YARD = 22,                         //码
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_INCH = 23,                         //英寸
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_FUR = 24,                          //弗隆
	ENUM_APISERVICE_PLUGIN_METER_LENGTH_FOOT = 25                          //英尺
}ENUM_APISERVICE_PLUGIN_METER_LENGTH;
//温度计量
typedef enum 
{
	ENUM_APISERVICE_PLUGIN_METER_TEMPERATURE_C = 0,                        //摄氏度
	ENUM_APISERVICE_PLUGIN_METER_TEMPERATURE_F = 1,                        //华氏度
	ENUM_APISERVICE_PLUGIN_METER_TEMPERATURE_K = 2,                        //开氏度
	ENUM_APISERVICE_PLUGIN_METER_TEMPERATURE_RA = 3,                       //兰氏度
	ENUM_APISERVICE_PLUGIN_METER_TEMPERATURE_RE = 4                        //列氏度
}ENUM_APISERVICE_PLUGIN_METER_TEMPERATURE;
//功率
typedef enum
{
	ENUM_APISERVICE_PLUGIN_METER_POWER_W = 0,                              //瓦
	ENUM_APISERVICE_PLUGIN_METER_POWER_KW = 1,                             //千瓦
	ENUM_APISERVICE_PLUGIN_METER_POWER_HP = 2,                             //英制马力
	ENUM_APISERVICE_PLUGIN_METER_POWER_PS = 3,                             //米制马力
}ENUM_APISERVICE_PLUGIN_METER_POWER;
//速度
typedef enum
{
	ENUM_APISERVICE_PLUGIN_METER_SPEED_KNOT = 0,                           //节
	ENUM_APISERVICE_PLUGIN_METER_POWER_MILE = 1,                           //里
	ENUM_APISERVICE_PLUGIN_METER_POWER_KILOMETER = 2,                      //公里
}ENUM_APISERVICE_PLUGIN_METER_SPEED;
//重量
//面积
//体积
//压力
//进制
//////////////////////////////////////////////////////////////////////////
//                       导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG PluginCore_GetLastError();
/*********************************************************************************
*                                导出函数定义                                    *
*********************************************************************************/
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
extern "C" bool PluginCore_Init(XPVOID lParam = NULL);
/********************************************************************
函数名称：PluginCore_UnInit
函数功能：卸载插件
返回值
  类型：无
  意思：
备注：
*********************************************************************/
extern "C" void PluginCore_UnInit();
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool PluginCore_Call(XCHAR * **pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer = NULL, int nMsgLen = 0);