#pragma once
/********************************************************************
//    Created:     2022/06/13  16:55:53
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_P2PClient\ModuleHelp_P2PClient.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_P2PClient
//    File Base:   ModuleHelp_P2PClient
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     P2P客户端管理器
//    History:
*********************************************************************/
class CModuleHelp_P2PClient
{
public:
	CModuleHelp_P2PClient();
	~CModuleHelp_P2PClient();
public:
	BOOL ModuleHelp_P2PClient_Init(int nTimeout, CALLBACK_APISERVICE_MODULE_HELP_P2PCLIENT fpCall_P2PClient, LPVOID lParam = NULL);
	BOOL ModuleHelp_P2PClient_Destory();
	BOOL ModuleHelp_P2PClient_Add(XENGINE_P2XP_PEERINFO* pSt_PeerInfo);
	BOOL ModuleHelp_P2PClient_Get(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol, XENGINE_P2XP_PEERINFO* pSt_PeerInfo = NULL);
	BOOL ModuleHelp_P2PClient_GetLan(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol, XENGINE_P2XPPEER_PROTOCOL*** pppSt_P2XPClient, int* pInt_ListCount);      
	BOOL ModuleHelp_P2PClient_GetLList(LPCTSTR lpszPubAddr, TCHAR*** pppszP2XPClient, int* pInt_ListCount);
	BOOL ModuleHelp_P2PClient_GetWList(TCHAR*** pppszP2XPClient, int* pInt_ListCount); 
	BOOL ModuleHelp_P2PClient_Delete(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol);
	BOOL ModuleHelp_P2PClient_DelAll();     
protected:
	static XHTHREAD CALLBACK ModuleHelp_P2PClient_Thread(LPVOID lParam);
private:
	BOOL m_bIsRun;
	int m_nTimeout;
	LPVOID m_lParam;
	CALLBACK_APISERVICE_MODULE_HELP_P2PCLIENT lpCall_P2PClient;
private:
	shared_mutex st_Locker;    
private:
	shared_ptr<std::thread> pSTDThread;
private:
	//接口:公网 内网 连接.
	unordered_map<string, unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> > > stl_MapClients;
};
