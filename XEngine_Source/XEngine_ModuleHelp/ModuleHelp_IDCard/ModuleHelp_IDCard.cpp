#include "pch.h"
#include "ModuleHelp_IDCard.h"
/********************************************************************
//    Created:     2022/03/03  13:59:47
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_IDCard\ModuleHelp_IDCard.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_IDCard
//    File Base:   ModuleHelp_IDCard
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     身份证处理
//    History:
*********************************************************************/
CModuleHelp_IDCard::CModuleHelp_IDCard()
{
}
CModuleHelp_IDCard::~CModuleHelp_IDCard()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleHelp_IDCard_CheckBirth
函数功能：检查身份证号生日
 参数.一：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要检查的身份结构
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleHelp_IDCard::ModuleHelp_IDCard_CheckBirth(XENGINE_IDCARDINFO *pSt_IDInfo)
{
	ModuleHelp_IsErrorOccur = XFALSE;

	if (NULL == pSt_IDInfo)
	{
		ModuleHelp_IsErrorOccur = XTRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IDCARD_PARAMENT;
		return XFALSE;
	}
	if (pSt_IDInfo->nBirthYear < 1949 || pSt_IDInfo->nBirthYear > 2999)
	{
		ModuleHelp_IsErrorOccur = XTRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IDCARD_FMT;
		return XFALSE;
	}
	if (pSt_IDInfo->nBirthMonth < 1 || pSt_IDInfo->nBirthMonth > 12)
	{
		ModuleHelp_IsErrorOccur = XTRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IDCARD_FMT;
		return XFALSE;
	}
	if (pSt_IDInfo->nBirthDay < 1 || pSt_IDInfo->nBirthDay > 31)
	{
		ModuleHelp_IsErrorOccur = XTRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IDCARD_FMT;
		return XFALSE;
	}
	return XTRUE;
}
/********************************************************************
函数名称：ModuleHelp_IDCard_CheckBirth
函数功能：检查身份证的校验码是否正确
 参数.一：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要检查的身份结构
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleHelp_IDCard::ModuleHelp_IDCard_CheckSum(XENGINE_IDCARDINFO* pSt_IDInfo)
{
	ModuleHelp_IsErrorOccur = XFALSE;

	if (NULL == pSt_IDInfo)
	{
		ModuleHelp_IsErrorOccur = XTRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IDCARD_PARAMENT;
		return XFALSE;
	}
	int nCheck = 0;
	int nIDArray[18];
	const int nFactor[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };       //加权因子
	const int nTable[] = { 1, 0, 10, 9, 8, 7, 6, 5, 4, 3, 2 };                           //校验值对应表
	//转换字符为整数
	for (int i = 0; i < 18; i++)
	{
		nIDArray[i] = pSt_IDInfo->tszIDNumber[i] - 48;
	}
	//计算校验码
	for (int i = 0; i < 17; i++)
	{
		nCheck += nIDArray[i] * nFactor[i];
	}
	if ((nIDArray[17] != nTable[nCheck % 11]) && (pSt_IDInfo->nCheck != 'x' || nTable[nCheck % 11] != 2))
	{
		ModuleHelp_IsErrorOccur = XTRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IDCARD_SUM;
		return XFALSE;
	}
	return XTRUE;
}