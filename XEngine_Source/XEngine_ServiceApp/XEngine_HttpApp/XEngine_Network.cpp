#include "XEngine_Hdr.h"
/********************************************************************
//    Created:     2022/01/20  14:44:40
//    File Name:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp\XEngine_Network.cpp
//    File Path:   D:\XEngine_ServiceApp\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp
//    File Base:   XEngine_Network
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     网络IO相关代码
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////下面是HTTP网络IO相关代码处理函数
BOOL __stdcall Network_Callback_HTTPLogin(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam)
{
	SocketOpt_HeartBeat_InsertAddrEx(xhHTTPHeart, lpszClientAddr);
	RfcComponents_HttpServer_CreateClientEx(xhHTTPPacket, lpszClientAddr, 0);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,连接到服务器"), lpszClientAddr);
	return TRUE;
}
void __stdcall Network_Callback_HTTPRecv(LPCTSTR lpszClientAddr, SOCKET hSocket, LPCTSTR lpszRecvMsg, int nMsgLen, LPVOID lParam)
{
	if (!RfcComponents_HttpServer_InserQueueEx(xhHTTPPacket, lpszClientAddr, lpszRecvMsg, nMsgLen))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,投递HTTP数据包到消息队列失败，错误:%lX"), lpszClientAddr, HttpServer_GetLastError());
		return;
	}
	SocketOpt_HeartBeat_ActiveAddrEx(xhHTTPHeart, lpszClientAddr);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_DEBUG, _T("HTTP客户端:%s,投递数据包到组包队列成功,大小:%d"), lpszClientAddr, nMsgLen);
}
void __stdcall Network_Callback_HTTPLeave(LPCTSTR lpszClientAddr, SOCKET hSocket, LPVOID lParam)
{
	XEngine_Network_Close(lpszClientAddr, FALSE);
}
void __stdcall Network_Callback_HTTPHeart(LPCTSTR lpszClientAddr, SOCKET hSocket, int nStatus, LPVOID lParam)
{
	XEngine_Network_Close(lpszClientAddr, TRUE);
}
//////////////////////////////////////////////////////////////////////////网络IO关闭操作
void XEngine_Network_Close(LPCTSTR lpszClientAddr, BOOL bHeart)
{
	if (bHeart)
	{
		NetCore_TCPXCore_CloseForClientEx(xhHTTPSocket, lpszClientAddr);
	}
	else
	{
		SocketOpt_HeartBeat_DeleteAddrEx(xhHTTPHeart, lpszClientAddr);
	}
	RfcComponents_HttpServer_CloseClinetEx(xhHTTPPacket, lpszClientAddr);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("HTTP客户端:%s,离开服务器"), lpszClientAddr);
}
//////////////////////////////////////////////////////////////////////////
BOOL XEngine_Network_Send(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen)
{
	//发送数据给指定客户端
	if (!NetCore_TCPXCore_SendEx(xhHTTPSocket, lpszClientAddr, lpszMsgBuffer, nMsgLen))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("HTTP客户端:%s,发送数据失败，错误:%lX"), lpszClientAddr, NetCore_GetLastError());
		return FALSE;
	}
	//发送成功激活一次心跳
	SocketOpt_HeartBeat_ActiveAddrEx(xhHTTPHeart, lpszClientAddr);
	return TRUE;
}