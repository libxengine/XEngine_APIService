#include "pch.h"
#include "ModuleHelp_DNSAddr.h"
/********************************************************************
//    Created:     2025/07/14  15:47:28
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_DNSAddr\ModuleHelp_DNSAddr.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_DNSAddr
//    File Base:   ModuleHelp_DNSAddr
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     DNS解析处理帮助函数
//    History:
*********************************************************************/
CModuleHelp_DNSAddr::CModuleHelp_DNSAddr()
{
}
CModuleHelp_DNSAddr::~CModuleHelp_DNSAddr()
{
}
//////////////////////////////////////////////////////////////////////////
//                        公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleHelp_DNSAddr_Init
函数功能：初始化DNS数据表
 参数.一：pSt_DNSInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要转换的列表
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_DNSAddr::ModuleHelp_DNSAddr_Init(XENGINE_DNSINFO* pSt_DNSInfo)
{
	ModuleHelp_IsErrorOccur = false;

	if (NULL == pSt_DNSInfo)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_DNS_PARAMRT;
		return false;
	}

	for (auto stl_ListIterator = pSt_DNSInfo->stl_ListDNSServer.begin(); stl_ListIterator != pSt_DNSInfo->stl_ListDNSServer.end(); stl_ListIterator++)
	{
		stl_ListDNSServer.push_back(stl_ListIterator->c_str());
	}
	for (auto stl_ListIterator = pSt_DNSInfo->stl_ListDNSList.begin(); stl_ListIterator != pSt_DNSInfo->stl_ListDNSList.end(); stl_ListIterator++)
	{
		if (stl_ListIterator->bEnable)
		{
			stl_MapDNSAddr.insert(make_pair(stl_ListIterator->tszDNSName, stl_ListIterator->stl_ListDNSAddr));
		}
	}
	return true;
}
/********************************************************************
函数名称：ModuleHelp_DNSAddr_Destroy
函数功能：销毁DNS帮助函数库
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_DNSAddr::ModuleHelp_DNSAddr_Destroy()
{
	ModuleHelp_IsErrorOccur = false;
	
	stl_ListDNSServer.clear();
	stl_MapDNSAddr.clear();
	return true;
}
/********************************************************************
函数名称：ModuleHelp_DNSAddr_FindA
函数功能：A记录查找
 参数.一：lpszDNSAddr
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要查找的DNS地址
 参数.二：pppSt_DNSList
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出查找到的列表
 参数.三：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_DNSAddr::ModuleHelp_DNSAddr_FindA(LPCXSTR lpszDNSAddr, XENGINE_DNSADDRINFO*** pppSt_DNSList, int* pInt_ListCount)
{
	ModuleHelp_IsErrorOccur = false;

	auto stl_MapIterator = stl_MapDNSAddr.find(lpszDNSAddr);
	if (stl_MapIterator == stl_MapDNSAddr.end())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_DNS_NOTFOUND;
		return false;
	}
	
	*pInt_ListCount = stl_MapIterator->second.size();
	BaseLib_Memory_Malloc((XPPPMEM)pppSt_DNSList, *pInt_ListCount, sizeof(XENGINE_DNSADDRINFO));

	auto stl_ListIterator = stl_MapIterator->second.begin();
	for (int i = 0; stl_ListIterator != stl_MapIterator->second.end(); stl_ListIterator++, i++)
	{
		*(*pppSt_DNSList)[i] = *stl_ListIterator;
	}

	return true;
}
/********************************************************************
函数名称：ModuleHelp_DNSAddr_FindPtr
函数功能：输出IP对应的域名
 参数.一：lpszDNSAddr
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要查找的IP地址
 参数.二：pSt_DNSAddr
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出查找到的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_DNSAddr::ModuleHelp_DNSAddr_FindPtr(LPCXSTR lpszDNSAddr, XENGINE_DNSADDRINFO* pSt_DNSAddr)
{
	ModuleHelp_IsErrorOccur = false;

	auto stl_MapIterator = stl_MapDNSAddr.begin();
	//查找地址
	bool bIsFound = false;
	for (auto stl_ListIterator = stl_MapIterator->second.begin(); stl_ListIterator != stl_MapIterator->second.end(); stl_ListIterator++)
	{
		if (0 == _tcsxnicmp(stl_ListIterator->tszDNSAddr, lpszDNSAddr, _tcsxlen(stl_ListIterator->tszDNSAddr)))
		{
			*pSt_DNSAddr = *stl_ListIterator;
			bIsFound = true;
			break;
		}
	}

	if (!bIsFound)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_DNS_NOTFOUND;
		return false;
	}

	return true;
}
/********************************************************************
函数名称：ModuleHelp_DNSAddr_Select
函数功能：备选地址
 参数.一：ptszDNSServer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出选择的DNS服务器
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_DNSAddr::ModuleHelp_DNSAddr_Select(XCHAR* ptszDNSServer)
{
	ModuleHelp_IsErrorOccur = false;

	if (stl_ListDNSServer.size() > 1)
	{
		_tcsxcpy(ptszDNSServer, stl_ListDNSServer.front().c_str());
	}
	else
	{
		_tcsxcpy(ptszDNSServer, stl_ListDNSServer.front().c_str());
	}

	return true;
}