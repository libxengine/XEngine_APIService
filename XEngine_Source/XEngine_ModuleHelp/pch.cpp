#include "pch.h"
#include "ModuleHelp_IDCard/ModuleHelp_IDCard.h"
#include "ModuleHelp_Language/ModuleHelp_Language.h"
/********************************************************************
//    Created:     2022/03/04  13:37:38
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\pch.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出函数实现
//    History:
*********************************************************************/
BOOL ModuleHelp_IsErrorOccur = FALSE;
DWORD ModuleHelp_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleHelp_IDCard m_IDCard;
CModuleHelp_Language m_Language;
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModuleHelp_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return ModuleHelp_dwErrorCode;
}
/************************************************************************/
/*                         导出的身份证帮助函数                         */
/************************************************************************/
extern "C" BOOL ModuleHelp_IDCard_CheckBirth(XENGINE_IDCARDINFO * pSt_IDInfo)
{
	return m_IDCard.ModuleHelp_IDCard_CheckBirth(pSt_IDInfo);
}
extern "C" BOOL ModuleHelp_IDCard_CheckSum(XENGINE_IDCARDINFO * pSt_IDInfo)
{
	return m_IDCard.ModuleHelp_IDCard_CheckSum(pSt_IDInfo);
}
/************************************************************************/
/*                         导出的语言转换帮助函数                       */
/************************************************************************/
extern "C" BOOL ModuleHelp_Language_ConvertZh(LPCTSTR lpszJsonFile, LPCTSTR lpszSourceStr, TCHAR * ptszDestStr)
{
	return m_Language.ModuleHelp_Language_ConvertZh(lpszJsonFile, lpszSourceStr, ptszDestStr);
}