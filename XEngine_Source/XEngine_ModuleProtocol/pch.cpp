#include "pch.h"
#include "ModuleProtocol_Packet/ModuleProtocol_Packet.h"
/********************************************************************
//    Created:     2022/02/28  14:23:53
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol\pch.cpp
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出协议模块实现
//    History:
*********************************************************************/
BOOL ModuleProtocol_IsErrorOccur = FALSE;
DWORD ModuleProtocol_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleProtocol_Packet m_ProtocolPacket;
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModuleProtocol_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return ModuleProtocol_dwErrorCode;
}
/************************************************************************/
/*                         导出的打包协议函数                           */
/************************************************************************/
extern "C" BOOL ModuleProtocol_Packet_IPQuery(TCHAR * ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IPADDRINFO * pSt_IPAddrInfo, int nCode, LPCTSTR lpszMsgBuffer)
{
	return m_ProtocolPacket.ModuleProtocol_Packet_IPQuery(ptszMsgBuffer, pInt_MsgLen, pSt_IPAddrInfo, nCode, lpszMsgBuffer);
}