#include "pch.h"
#include "ModuleHelp_IDCard/ModuleHelp_IDCard.h"
#include "ModuleHelp_Language/ModuleHelp_Language.h"
#include "ModuleHelp_P2PClient/ModuleHelp_P2PClient.h"
#include "ModuleHelp_Locker/ModuleHelp_Locker.h"
#include "ModuleHelp_QRCode/ModuleHelp_QRCode.h"
#include "ModuleHelp_SocketTest/ModuleHelp_SocketTest.h"
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
XBOOL ModuleHelp_IsErrorOccur = FALSE;
DWORD ModuleHelp_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleHelp_IDCard m_IDCard;
CModuleHelp_Language m_Language;
CModuleHelp_P2PClient m_P2PClient;
CModuleHelp_Locker m_Locker;
CModuleHelp_QRCode m_QRCode;
CModuleHelp_SocketTest m_SocketTest;
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
extern "C" XBOOL ModuleHelp_IDCard_CheckBirth(XENGINE_IDCARDINFO * pSt_IDInfo)
{
	return m_IDCard.ModuleHelp_IDCard_CheckBirth(pSt_IDInfo);
}
extern "C" XBOOL ModuleHelp_IDCard_CheckSum(XENGINE_IDCARDINFO * pSt_IDInfo)
{
	return m_IDCard.ModuleHelp_IDCard_CheckSum(pSt_IDInfo);
}
/************************************************************************/
/*                         导出的语言转换帮助函数                       */
/************************************************************************/
extern "C" XBOOL ModuleHelp_Language_ConvertZh(LPCXSTR lpszJsonFile, LPCXSTR lpszSourceStr, XCHAR * ptszDestStr)
{
	return m_Language.ModuleHelp_Language_ConvertZh(lpszJsonFile, lpszSourceStr, ptszDestStr);
}
extern "C" XBOOL ModuleHelp_Translation_Convert(ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE enTranslationType, XCHAR * ptszTranslationType)
{
	return m_Language.ModuleHelp_Translation_Convert(enTranslationType, ptszTranslationType);
}
/************************************************************************/
/*                         导出的P2P客户端帮助函数                      */
/************************************************************************/
extern "C" XBOOL ModuleHelp_P2PClient_Init(int nTimeout, CALLBACK_APISERVICE_MODULE_HELP_P2PCLIENT fpCall_P2PClient, XPVOID lParam)
{
	return m_P2PClient.ModuleHelp_P2PClient_Init(nTimeout, fpCall_P2PClient, lParam);
}
extern "C" XBOOL ModuleHelp_P2PClient_Destory()
{
	return m_P2PClient.ModuleHelp_P2PClient_Destory();
}
extern "C" XBOOL ModuleHelp_P2PClient_Add(XENGINE_P2XP_PEERINFO * pSt_PeerInfo)
{
	return m_P2PClient.ModuleHelp_P2PClient_Add(pSt_PeerInfo);
}
extern "C" XBOOL ModuleHelp_P2PClient_Get(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol, XENGINE_P2XP_PEERINFO * pSt_PeerInfo /* = NULL */)
{
	return m_P2PClient.ModuleHelp_P2PClient_Get(pSt_P2PProtocol, pSt_PeerInfo);
}
extern "C" XBOOL ModuleHelp_P2PClient_GetLan(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol, XENGINE_P2XPPEER_PROTOCOL * **pppSt_P2XPClient, int* pInt_ListCount)
{
	return m_P2PClient.ModuleHelp_P2PClient_GetLan(pSt_P2PProtocol, pppSt_P2XPClient, pInt_ListCount);
}
extern "C" XBOOL ModuleHelp_P2PClient_GetLList(LPCXSTR lpszPubAddr, XCHAR * **pppszP2XPClient, int* pInt_ListCount)
{
	return m_P2PClient.ModuleHelp_P2PClient_GetLList(lpszPubAddr, pppszP2XPClient, pInt_ListCount);
}
extern "C" XBOOL ModuleHelp_P2PClient_GetWList(XCHAR * **pppszP2XPClient, int* pInt_ListCount)
{
	return m_P2PClient.ModuleHelp_P2PClient_GetWList(pppszP2XPClient, pInt_ListCount);
}
extern "C" XBOOL ModuleHelp_P2PClient_Delete(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol)
{
	return m_P2PClient.ModuleHelp_P2PClient_Delete(pSt_P2PProtocol);
}
extern "C" XBOOL ModuleHelp_P2PClient_DelAll()
{
	return m_P2PClient.ModuleHelp_P2PClient_DelAll();
}
extern "C" XBOOL ModuleHelp_P2PClient_Heart(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol)
{
	return m_P2PClient.ModuleHelp_P2PClient_Heart(pSt_P2PProtocol);
}
/************************************************************************/
/*                       分布式锁导出函数                               */
/************************************************************************/
extern "C" XBOOL ModuleHelp_Locker_Create(XNETHANDLE * pxhToken)
{
	return m_Locker.ModuleHelp_Locker_Create(pxhToken);
}
extern "C" XBOOL ModuleHelp_Locker_OPen(XNETHANDLE xhToken)
{
	return m_Locker.ModuleHelp_Locker_OPen(xhToken);
}
extern "C" XBOOL ModuleHelp_Locker_ReadLock(XNETHANDLE xhToken)
{
	return m_Locker.ModuleHelp_Locker_ReadLock(xhToken);
}
extern "C" XBOOL ModuleHelp_Locker_ReadUNLock(XNETHANDLE xhToken)
{
	return m_Locker.ModuleHelp_Locker_ReadUNLock(xhToken);
}
extern "C" XBOOL ModuleHelp_Locker_WriteLock(XNETHANDLE xhToken)
{
	return m_Locker.ModuleHelp_Locker_WriteLock(xhToken);
}
extern "C" XBOOL ModuleHelp_Locker_WriteUNLock(XNETHANDLE xhToken)
{
	return m_Locker.ModuleHelp_Locker_WriteUNLock(xhToken);
}
extern "C" XBOOL ModuleHelp_Locker_Close(XNETHANDLE xhToken)
{
	return m_Locker.ModuleHelp_Locker_Close(xhToken);
}
/************************************************************************/
/*                       二维码导出函数                                 */
/************************************************************************/
extern "C" XBOOL ModuleHelp_QRCode_QREncodecFile(LPCXSTR lpszFileName, LPCXSTR lpszMsgBuffer)
{
	return m_QRCode.ModuleHelp_QRCode_QREncodecFile(lpszFileName, lpszMsgBuffer);
}
extern "C" XBOOL ModuleHelp_QRCode_QREncodecMemory(LPCXSTR lpszMsgBuffer, XCHAR * ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszFmt)
{
	return m_QRCode.ModuleHelp_QRCode_QREncodecMemory(lpszMsgBuffer, ptszMsgBuffer, pInt_MsgLen, lpszFmt);
}
extern "C" XBOOL ModuleHelp_QRCode_QRDecodecFile(LPCXSTR lpszFileName, XCHAR * ptszMsgBuffer, LPCXSTR lpszDetectProto, LPCXSTR lpszDetectModel, LPCXSTR lpszSrProto, LPCXSTR lpszSrModel)
{
	return m_QRCode.ModuleHelp_QRCode_QRDecodecFile(lpszFileName, ptszMsgBuffer, lpszDetectProto, lpszDetectModel, lpszSrProto, lpszSrModel);
}
extern "C" XBOOL ModuleHelp_QRCode_QRDecodecMemory(LPCSTR lpszMsgBuffer, int nMsgLen, XCHAR * ptszMsgBuffer, LPCXSTR lpszDetectProto, LPCXSTR lpszDetectModel, LPCXSTR lpszSrProto, LPCXSTR lpszSrModel)
{
	return m_QRCode.ModuleHelp_QRCode_QRDecodecMemory(lpszMsgBuffer, nMsgLen, ptszMsgBuffer, lpszDetectProto, lpszDetectModel, lpszSrProto, lpszSrModel);
}
/************************************************************************/
/*                       网络测试导出函数                               */
/************************************************************************/
extern "C" XBOOL ModuleHelp_SocketTest_StartConnect(XNETHANDLE * pxhToken, MODULEHELP_SOCKETTEST_RECONNECT * pSt_ReConnect, CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST fpCall_ReConnect, XPVOID lParam)
{
	return m_SocketTest.ModuleHelp_SocketTest_StartConnect(pxhToken, pSt_ReConnect, fpCall_ReConnect, lParam);
}
extern "C" XBOOL ModuleHelp_SocketTest_GetConnect(XNETHANDLE xhToken, XBOOL * pbRun)
{
	return m_SocketTest.ModuleHelp_SocketTest_GetConnect(xhToken, pbRun);
}
extern "C" XBOOL ModuleHelp_SocketTest_StopConnect(XNETHANDLE xhToken)
{
	return m_SocketTest.ModuleHelp_SocketTest_StopConnect(xhToken);
}
extern "C" XBOOL ModuleHelp_SocketTest_StartDatas(XNETHANDLE * pxhToken, MODULEHELP_SOCKETTEST_DATAS * pSt_SocketDatas, CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST fpCall_DataTest, XBOOL bTCP, XPVOID lParam)
{
	return m_SocketTest.ModuleHelp_SocketTest_StartDatas(pxhToken, pSt_SocketDatas, fpCall_DataTest, bTCP, lParam);
}
extern "C" XBOOL ModuleHelp_SocketTest_GetDatas(XNETHANDLE xhToken, XBOOL * pbRun)
{
	return m_SocketTest.ModuleHelp_SocketTest_GetDatas(xhToken, pbRun);
}
extern "C" XBOOL ModuleHelp_SocketTest_StopDatas(XNETHANDLE xhToken)
{
	return m_SocketTest.ModuleHelp_SocketTest_StopDatas(xhToken);
}