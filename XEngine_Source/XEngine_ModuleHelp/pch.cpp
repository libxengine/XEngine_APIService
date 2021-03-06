#include "pch.h"
#include "ModuleHelp_IDCard/ModuleHelp_IDCard.h"
#include "ModuleHelp_Language/ModuleHelp_Language.h"
#include "ModuleHelp_P2PClient/ModuleHelp_P2PClient.h"
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
CModuleHelp_P2PClient m_P2PClient;
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
extern "C" BOOL ModuleHelp_Translation_Convert(ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE enTranslationType, TCHAR * ptszTranslationType)
{
	return m_Language.ModuleHelp_Translation_Convert(enTranslationType, ptszTranslationType);
}
/************************************************************************/
/*                         导出的P2P客户端帮助函数                      */
/************************************************************************/
extern "C" BOOL ModuleHelp_P2PClient_Init(int nTimeout, CALLBACK_APISERVICE_MODULE_HELP_P2PCLIENT fpCall_P2PClient, LPVOID lParam)
{
	return m_P2PClient.ModuleHelp_P2PClient_Init(nTimeout, fpCall_P2PClient, lParam);
}
extern "C" BOOL ModuleHelp_P2PClient_Destory()
{
	return m_P2PClient.ModuleHelp_P2PClient_Destory();
}
extern "C" BOOL ModuleHelp_P2PClient_Add(XENGINE_P2XP_PEERINFO * pSt_PeerInfo)
{
	return m_P2PClient.ModuleHelp_P2PClient_Add(pSt_PeerInfo);
}
extern "C" BOOL ModuleHelp_P2PClient_Get(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol, XENGINE_P2XP_PEERINFO * pSt_PeerInfo /* = NULL */)
{
	return m_P2PClient.ModuleHelp_P2PClient_Get(pSt_P2PProtocol, pSt_PeerInfo);
}
extern "C" BOOL ModuleHelp_P2PClient_GetLan(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol, XENGINE_P2XPPEER_PROTOCOL * **pppSt_P2XPClient, int* pInt_ListCount)
{
	return m_P2PClient.ModuleHelp_P2PClient_GetLan(pSt_P2PProtocol, pppSt_P2XPClient, pInt_ListCount);
}
extern "C" BOOL ModuleHelp_P2PClient_GetLList(LPCTSTR lpszPubAddr, TCHAR * **pppszP2XPClient, int* pInt_ListCount)
{
	return m_P2PClient.ModuleHelp_P2PClient_GetLList(lpszPubAddr, pppszP2XPClient, pInt_ListCount);
}
extern "C" BOOL ModuleHelp_P2PClient_GetWList(TCHAR * **pppszP2XPClient, int* pInt_ListCount)
{
	return m_P2PClient.ModuleHelp_P2PClient_GetWList(pppszP2XPClient, pInt_ListCount);
}
extern "C" BOOL ModuleHelp_P2PClient_Delete(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol)
{
	return m_P2PClient.ModuleHelp_P2PClient_Delete(pSt_P2PProtocol);
}
extern "C" BOOL ModuleHelp_P2PClient_DelAll()
{
	return m_P2PClient.ModuleHelp_P2PClient_DelAll();
}
extern "C" BOOL ModuleHelp_P2PClient_Heart(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol)
{
	return m_P2PClient.ModuleHelp_P2PClient_Heart(pSt_P2PProtocol);
}