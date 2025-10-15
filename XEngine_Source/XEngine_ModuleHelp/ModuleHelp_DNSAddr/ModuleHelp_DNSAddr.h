#pragma once
/********************************************************************
//    Created:     2025/07/14  15:46:17
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_DNSAddr\ModuleHelp_DNSAddr.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_DNSAddr
//    File Base:   ModuleHelp_DNSAddr
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     DNS解析处理帮助函数
//    History:
*********************************************************************/

class CModuleHelp_DNSAddr
{
public:
	CModuleHelp_DNSAddr();
	~CModuleHelp_DNSAddr();
public:
	bool ModuleHelp_DNSAddr_Init(XENGINE_DNSINFO* pSt_DNSInfo);
	bool ModuleHelp_DNSAddr_Destroy();
	bool ModuleHelp_DNSAddr_FindA(LPCXSTR lpszDNSAddr, XENGINE_DNSADDRINFO*** pppSt_DNSList, int* pInt_ListCount);
	bool ModuleHelp_DNSAddr_FindPtr(LPCXSTR lpszDNSAddr, XENGINE_DNSADDRINFO* pSt_DNSAddr);
	bool ModuleHelp_DNSAddr_Select(XCHAR* ptszDNSServer);
protected:
private:
	std::list<xstring> stl_ListDNSServer;
	std::unordered_map<xstring, list<XENGINE_DNSADDRINFO> > stl_MapDNSAddr;
};