#include "pch.h"
#include "ModuleDatabase_Phone.h"
/********************************************************************
//    Created:     2022/03/09  10:31:44
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Phone\ModuleDatabase_Phone.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Phone
//    File Base:   ModuleDatabase_Phone
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     移动电话查询
//    History:
*********************************************************************/
CModuleDatabase_Phone::CModuleDatabase_Phone()
{
}
CModuleDatabase_Phone::~CModuleDatabase_Phone()
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
BOOL CModuleDatabase_Phone::ModuleDatabase_Phone_Init(LPCTSTR lpszSQLFile)
{
	DBModule_IsErrorOccur = FALSE;

	if (NULL == lpszSQLFile)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_PHONE_PARAMENT;
		return FALSE;
	}
	//打开数据库
	FILE* pSt_File = _tfopen(lpszSQLFile, _T("rb"));
	//申请内存
	ptszMsgBuffer = (TCHAR*)malloc(XENGINE_APISERVICE_DATABASE_PHONE_BUFFER_SIZE);
	if (NULL == ptszMsgBuffer)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_PHONE_MALLOC;
		return FALSE;
	}
	memset(ptszMsgBuffer, '\0', XENGINE_APISERVICE_DATABASE_PHONE_BUFFER_SIZE);
	//读取内容
	while (TRUE)
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
	return TRUE;
}
/********************************************************************
函数名称：ModuleDatabase_Phone_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleDatabase_Phone::ModuleDatabase_Phone_Destory()
{
	DBModule_IsErrorOccur = FALSE;

	free(ptszMsgBuffer);
	ptszMsgBuffer = NULL;
	return TRUE;
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
BOOL CModuleDatabase_Phone::ModuleDatabase_Phone_Query(LPCTSTR lpszPhoneNumber, XENGINE_PHONEINFO* pSt_PhoneInfo)
{
	DBModule_IsErrorOccur = FALSE;

	if ((NULL == lpszPhoneNumber) || (NULL == pSt_PhoneInfo))
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_PHONE_PARAMENT;
		return FALSE;
	}
	size_t nPLen = _tcslen(lpszPhoneNumber);
	size_t nPhone = 0;
	//不能超过7
	if (nPLen > 7)
	{
		TCHAR tszPhone[64];
		memset(tszPhone, '\0', sizeof(tszPhone));

		memcpy(tszPhone, lpszPhoneNumber, 7);
		nPhone = _ttoi(tszPhone);
	}
	else
	{
		nPhone = _ttoi(lpszPhoneNumber);
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
			while (TRUE)
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
				return FALSE;
			}
			break;
		}
	}	
	return TRUE;
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
BOOL CModuleDatabase_Phone::ModuleDatabase_Phone_Convert(LPCTSTR lpszPhoneInfo, int nMsgLen, XENGINE_PHONEINFO* pSt_PhoneInfo)
{
	DBModule_IsErrorOccur = FALSE;

	TCHAR tszMsgBuffer[128];
	memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
	memcpy(tszMsgBuffer, lpszPhoneInfo, nMsgLen);
	//省
	TCHAR* ptszTokStr = _tcstok(tszMsgBuffer, _T("|"));
	if (NULL == ptszTokStr)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_PHONE_NOTFOUND;
		return FALSE;
	}
	_tcscpy(pSt_PhoneInfo->tszProvincer, ptszTokStr);
	//市区
	ptszTokStr = _tcstok(NULL, _T("|"));
	if (NULL == ptszTokStr)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_PHONE_NOTFOUND;
		return FALSE;
	}
	_tcscpy(pSt_PhoneInfo->tszCity, ptszTokStr);
	//邮编
	ptszTokStr = _tcstok(NULL, _T("|"));
	if (NULL == ptszTokStr)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_PHONE_NOTFOUND;
		return FALSE;
	}
	pSt_PhoneInfo->nZipCode = _ttoi(ptszTokStr);
	//区号
	ptszTokStr = _tcstok(NULL, _T("|"));
	if (NULL == ptszTokStr)
	{
		DBModule_IsErrorOccur = TRUE;
		DBModule_dwErrorCode = ERROR_XENGINE_IPADDR_MODULE_DATABASE_PHONE_NOTFOUND;
		return FALSE;
	}
	pSt_PhoneInfo->nAreaCode = _ttoi(ptszTokStr);

	return TRUE;
}