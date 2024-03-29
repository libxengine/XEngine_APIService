﻿#include "pch.h"
#include "ModulePlugin_DBPhone.h"
/********************************************************************
//    Created:     2023/01/09  17:06:56
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\ModulePlugin_DBPhone\ModulePlugin_DBPhone.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\ModulePlugin_DBPhone
//    File Base:   ModulePlugin_DBPhone
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     电话信息查询
//    History:
*********************************************************************/
CModulePlugin_DBPhone::CModulePlugin_DBPhone()
{
}
CModulePlugin_DBPhone::~CModulePlugin_DBPhone()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_Phone_Init
函数功能：初始化电话信息查询数据库
 参数.一：lpszSQLFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要操作的SQL文件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_DBPhone::ModuleDatabase_Phone_Init(LPCXSTR lpszSQLFile)
{
	Phone_IsErrorOccur = false;

	if (NULL == lpszSQLFile)
	{
		Phone_IsErrorOccur = true;
		Phone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PHONE_PARAMENT;
		return false;
	}
	//打开数据库
	FILE* pSt_File = _xtfopen(lpszSQLFile, _X("rb"));
	if (NULL == pSt_File)
	{
		Phone_IsErrorOccur = true;
		Phone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PHONE_NOTFOUND;
		return false;
	}
	//申请内存
	ptszMsgBuffer = (XCHAR*)malloc(XENGINE_APISERVICE_DATABASE_PHONE_BUFFER_SIZE);
	if (NULL == ptszMsgBuffer)
	{
		Phone_IsErrorOccur = true;
		Phone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PHONE_MALLOC;
		return false;
	}
	memset(ptszMsgBuffer, '\0', XENGINE_APISERVICE_DATABASE_PHONE_BUFFER_SIZE);
	//读取内容
	while (true)
	{
		int nRet = fread(ptszMsgBuffer + nFLen, 1, 2048, pSt_File);
		if (nRet <= 0)
		{
			break;
		}
		nFLen += nRet;
	}
	fclose(pSt_File);
	memcpy(&st_PhoneHdr, ptszMsgBuffer, sizeof(XENGINE_DBPHONEHDR));
	nCount = (nFLen - st_PhoneHdr.nOffset) / XENGINE_APISERVICE_DATABASE_PHONE_INDEX_LEN;
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_Phone_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_DBPhone::ModuleDatabase_Phone_Destory()
{
	Phone_IsErrorOccur = false;

	free(ptszMsgBuffer);
	ptszMsgBuffer = NULL;
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_Phone_Query
函数功能：查询电话号码信息
 参数.一：lpszPhoneNumber
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要查询的电话号码
 参数.二：pSt_PhoneInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出电话信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_DBPhone::ModuleDatabase_Phone_Query(LPCXSTR lpszPhoneNumber, XENGINE_PHONEINFO* pSt_PhoneInfo)
{
	Phone_IsErrorOccur = false;

	if ((NULL == lpszPhoneNumber) || (NULL == pSt_PhoneInfo))
	{
		Phone_IsErrorOccur = true;
		Phone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PHONE_PARAMENT;
		return false;
	}
	size_t nPLen = _tcsxlen(lpszPhoneNumber);
	size_t nPhone = 0;
	//不能超过7
	if (nPLen > 7)
	{
		XCHAR tszPhone[64];
		memset(tszPhone, '\0', sizeof(tszPhone));

		memcpy(tszPhone, lpszPhoneNumber, 7);
		nPhone = _ttxoi(tszPhone);
	}
	else
	{
		nPhone = _ttxoi(lpszPhoneNumber);
	}
	
	size_t nLeft = 0;
	size_t nRight = nCount;
	while (nLeft <= nRight)
	{
		//二分查找
		size_t nMiddle = (nLeft + nRight) / 2;
		size_t nCurrentPos = st_PhoneHdr.nOffset + nMiddle * XENGINE_APISERVICE_DATABASE_PHONE_INDEX_LEN;
		if (nCurrentPos >= nFLen)
		{
			break;
		}
		XENGINE_DBPHONERECORD st_DBRecord;
		memset(&st_DBRecord, '\0', sizeof(XENGINE_DBPHONERECORD));

		memcpy(&st_DBRecord, ptszMsgBuffer + nCurrentPos, XENGINE_APISERVICE_DATABASE_PHONE_INDEX_LEN);
		if (st_DBRecord.nPhone > nPhone)
		{
			nRight = nMiddle - 1;
		}
		else if (st_DBRecord.nPhone < nPhone)
		{
			nLeft = nMiddle + 1;
		}
		else
		{
			int i = 0;
			while (true)
			{
				if (ptszMsgBuffer[i + st_DBRecord.nOffset] == '\0')
				{
					break;
				}
				i++;
			}
			pSt_PhoneInfo->enPhoneType = (ENUM_XENGINE_APISERVICE_PHONE_TYPE)st_DBRecord.byType;
			//转换数据
			if (!ModuleDatabase_Phone_Convert(ptszMsgBuffer + st_DBRecord.nOffset, i, pSt_PhoneInfo))
			{
				return false;
			}
			break;
		}
	}	
	return true;
}
//////////////////////////////////////////////////////////////////////////
//                             保护函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_Phone_Convert
函数功能：转换数据格式到指定数据结构
 参数.一：lpszPhoneInfo
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要转换的信息
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入查找大小
 参数.三：pSt_PhoneInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输出转换后的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_DBPhone::ModuleDatabase_Phone_Convert(LPCXSTR lpszPhoneInfo, int nMsgLen, XENGINE_PHONEINFO* pSt_PhoneInfo)
{
	Phone_IsErrorOccur = false;

	XCHAR tszMsgBuffer[128];
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memcpy(tszMsgBuffer, lpszPhoneInfo, nMsgLen);
	//省
	XCHAR* ptszTokStr = _tcsxtok(tszMsgBuffer, _X("|"));
	if (NULL == ptszTokStr)
	{
		Phone_IsErrorOccur = true;
		Phone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PHONE_NOTFOUND;
		return false;
	}
	_tcsxcpy(pSt_PhoneInfo->tszProvincer, ptszTokStr);
	//市区
	ptszTokStr = _tcsxtok(NULL, _X("|"));
	if (NULL == ptszTokStr)
	{
		Phone_IsErrorOccur = true;
		Phone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PHONE_NOTFOUND;
		return false;
	}
	_tcsxcpy(pSt_PhoneInfo->tszCity, ptszTokStr);
	//邮编
	ptszTokStr = _tcsxtok(NULL, _X("|"));
	if (NULL == ptszTokStr)
	{
		Phone_IsErrorOccur = true;
		Phone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PHONE_NOTFOUND;
		return false;
	}
	pSt_PhoneInfo->nZipCode = _ttxoi(ptszTokStr);
	//区号
	ptszTokStr = _tcsxtok(NULL, _X("|"));
	if (NULL == ptszTokStr)
	{
		Phone_IsErrorOccur = true;
		Phone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PHONE_NOTFOUND;
		return false;
	}
	pSt_PhoneInfo->nAreaCode = _ttxoi(ptszTokStr);

	return true;
}