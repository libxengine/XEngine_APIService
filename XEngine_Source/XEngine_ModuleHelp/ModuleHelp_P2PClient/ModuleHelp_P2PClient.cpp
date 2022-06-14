#include "pch.h"
#include "ModuleHelp_P2PClient.h"
/********************************************************************
//    Created:     2022/06/13  16:56:32
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_P2PClient\ModuleHelp_P2PClient.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_P2PClient
//    File Base:   ModuleHelp_P2PClient
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     P2P客户端管理器
//    History:
*********************************************************************/
CModuleHelp_P2PClient::CModuleHelp_P2PClient()
{
}
CModuleHelp_P2PClient::~CModuleHelp_P2PClient()
{
}
//////////////////////////////////////////////////////////////////////////
//                          公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleHelp_P2PClient_Add
函数功能：添加一个客户到一个节点信息
 参数.一：pSt_PeerInfo
  In/Out：In
  类型：结构体指针
  可空：N
  意思：要添加的节点信息
返回值
  类型：逻辑型
  意思：是否添加成功
备注：
*********************************************************************/
BOOL CModuleHelp_P2PClient::ModuleHelp_P2PClient_Add(XENGINE_P2XP_PEERINFO* pSt_PeerInfo)
{
    ModuleHelp_IsErrorOccur = FALSE;

    st_Locker.lock();
	unordered_map<string, unordered_map<string, list<XENGINE_P2XP_PEERINFO> > >::iterator stl_MapIteratorAddr = stl_MapClients.find(pSt_PeerInfo->st_PeerAddr.tszPublicAddr);
	if (stl_MapIteratorAddr == stl_MapClients.end())
	{
		//没有找到,一个一个加入,首先加入私有同步网络
		list<XENGINE_P2XP_PEERINFO> stl_ListSecond;
		stl_ListSecond.push_back(*pSt_PeerInfo);
		//获取私有网络的路由地址
		XENGINE_LIBADDR st_LibAddr;
		TCHAR tszPrivateAddr[64];

		memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
		memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
		if (!BaseLib_OperatorIPAddr_IsIPV4Addr(pSt_PeerInfo->st_PeerAddr.tszPrivateAddr, &st_LibAddr))
		{
			//没有内网地址不加入.
			ModuleHelp_IsErrorOccur = TRUE;
			ModuleHelp_dwErrorCode = BaseLib_GetLastError();
			return FALSE;
		}
		_stprintf_s(tszPrivateAddr, _T("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);
		//然后加入到
		unordered_map<string, list<XENGINE_P2XP_PEERINFO> > stl_MapSecond;
		stl_MapSecond.insert(make_pair(tszPrivateAddr, stl_ListSecond));
		stl_MapClients.insert(make_pair(pSt_PeerInfo->st_PeerAddr.tszPublicAddr, stl_MapSecond));
	}
	else
	{
		//找到了这个公网的地址
		XENGINE_LIBADDR st_LibAddr;
		TCHAR tszPrivateAddr[64];

		memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
		memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
		//获取私有网络的路由地址
		if (!BaseLib_OperatorIPAddr_IsIPV4Addr(pSt_PeerInfo->st_PeerAddr.tszPrivateAddr, &st_LibAddr))
		{
			//没有内网地址不加入.
			ModuleHelp_IsErrorOccur = TRUE;
			ModuleHelp_dwErrorCode = BaseLib_GetLastError();
			return FALSE;
		}
		//内网地址192.168.1.2  内网出口192.168.1.1 链接地址10.0.1.0:13444
		_stprintf_s(tszPrivateAddr, _T("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);
		unordered_map<string, list<XENGINE_P2XP_PEERINFO> >::iterator stl_MapIteartorPrivate = stl_MapIteratorAddr->second.find(tszPrivateAddr);
		if (stl_MapIteartorPrivate == stl_MapIteratorAddr->second.end())
		{
			list<XENGINE_P2XP_PEERINFO> stl_ListClient;
			stl_ListClient.push_back(*pSt_PeerInfo);
			stl_MapIteratorAddr->second.insert(make_pair(tszPrivateAddr, stl_ListClient));
		}
		else
		{
			BOOL bIsFound = FALSE;
			//查找链接地址是否存在.存在表示已经加入过了,那么就什么都不做
			list<XENGINE_P2XP_PEERINFO>::iterator stl_ListIterator = stl_MapIteartorPrivate->second.begin();
			for (; stl_ListIterator != stl_MapIteartorPrivate->second.end(); stl_ListIterator++)
			{
				if (0 == _tcscmp(stl_ListIterator->st_PeerAddr.tszConnectAddr, pSt_PeerInfo->st_PeerAddr.tszConnectAddr))
				{
					bIsFound = TRUE;
					break;
				}
			}
			//没有找到就加入
			if (!bIsFound)
			{
				stl_MapIteartorPrivate->second.push_back(*pSt_PeerInfo);
			}
		}
	}
    st_Locker.unlock();
    return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_P2PClient_Get
函数功能：获取P2P节点对应信息
 参数.一：pSt_P2PProtocol
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：要查询的地址
 参数.二：pSt_PeerInfo
  In/Out：Out
  类型：数据结构指针
  可空：Y
  意思：如果为空将不导出对应的数据
返回值
  类型：逻辑型
  意思：是否查找成功
备注：
*********************************************************************/
BOOL CModuleHelp_P2PClient::ModuleHelp_P2PClient_Get(XENGINE_P2XPPEER_PROTOCOL *pSt_P2PProtocol, XENGINE_P2XP_PEERINFO* pSt_PeerInfo /* = NULL */)
{
    ModuleHelp_IsErrorOccur = FALSE;

    if (NULL == pSt_P2PProtocol)
    {
        ModuleHelp_IsErrorOccur = TRUE;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_PARAMENT;
        return FALSE;
    }
    //查找元素
    st_Locker.lock_shared();
    unordered_map<string, unordered_map<string, list<XENGINE_P2XP_PEERINFO> > >::const_iterator stl_MapPubIterator = stl_MapClients.find(pSt_P2PProtocol->tszPublicAddr);
    if (stl_MapPubIterator == stl_MapClients.end())
    {
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND;
		st_Locker.unlock_shared();
		return FALSE;
    }
    //转换地址
	XENGINE_LIBADDR st_LibAddr;
	TCHAR tszPrivateAddr[64];

	memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
	memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
	//获取私有网络的路由地址
    BaseLib_OperatorIPAddr_IsIPV4Addr(pSt_P2PProtocol->tszPrivateAddr, &st_LibAddr);
	_stprintf_s(tszPrivateAddr, _T("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);

    unordered_map<string, list<XENGINE_P2XP_PEERINFO> >::const_iterator stl_MapPriIterator = stl_MapPubIterator->second.find(tszPrivateAddr);
    if (stl_MapPriIterator == stl_MapPubIterator->second.end())
    {
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND;
		st_Locker.unlock_shared();
		return FALSE;
    }
    BOOL bFound = FALSE;
    list<XENGINE_P2XP_PEERINFO>::const_iterator stl_ListIterator = stl_MapPriIterator->second.begin();
    for (; stl_ListIterator != stl_MapPriIterator->second.end(); stl_ListIterator++)
    {
        if (0 == _tcsncmp(pSt_P2PProtocol->tszConnectAddr, stl_ListIterator->st_PeerAddr.tszConnectAddr, _tcslen(pSt_P2PProtocol->tszConnectAddr)))
        {
            bFound = TRUE;
            break;
        }
    }
    if (!bFound)
    {
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND;
		st_Locker.unlock_shared();
		return FALSE;
    }
    //判断是否导出节点信息
    if (NULL != pSt_PeerInfo)
    {
        *pSt_PeerInfo = *stl_ListIterator;
    }
    st_Locker.unlock_shared();
    return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_P2PClient_GetLan
函数功能：获取局域网IP地址列表
 参数.一：pSt_P2PProtocol
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：要查找地址信息
 参数.二：pppSt_P2XPClient
  In/Out：Out
  类型：三级指针
  可空：N
  意思：导出局域网IP地址列表
 参数.三：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出地址列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：参数二需要调用基础库的BaseLib_OperatorMemory_Free函数进行内存释放
*********************************************************************/
BOOL CModuleHelp_P2PClient::ModuleHelp_P2PClient_GetLan(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol, XENGINE_P2XPPEER_PROTOCOL*** pppSt_P2XPClient, int* pInt_ListCount)
{
    ModuleHelp_IsErrorOccur = FALSE;

    if ((NULL == pSt_P2PProtocol) || (NULL == pppSt_P2XPClient) || (NULL == pInt_ListCount))
    {
        ModuleHelp_IsErrorOccur = TRUE;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_PARAMENT;
        return FALSE;
    }
    //查找公网IP地址
    st_Locker.lock_shared();
    unordered_map<string, unordered_map<string, list<XENGINE_P2XP_PEERINFO> > >::const_iterator stl_MapIterator = stl_MapClients.find(pSt_P2PProtocol->tszPublicAddr);
    if (stl_MapIterator == stl_MapClients.end())
    {
        ModuleHelp_IsErrorOccur = TRUE;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTPUBADDRR;
        st_Locker.unlock_shared();
        return FALSE;
    }
    XENGINE_LIBADDR st_LibAddr;
    TCHAR tszPrivateAddr[64];

    memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
    memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
    //如果输入的是192.168.1.1 IP,就我们自己分割,否则认为输入的是 192.168.1
    if (BaseLib_OperatorIPAddr_IsIPV4Addr(pSt_P2PProtocol->tszPrivateAddr, &st_LibAddr))
    {
        _stprintf_s(tszPrivateAddr, _T("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);
        unordered_map<string, list<XENGINE_P2XP_PEERINFO> >::const_iterator stl_MapSubIterator = stl_MapIterator->second.find(tszPrivateAddr);
        if (stl_MapSubIterator == stl_MapIterator->second.end())
        {
            ModuleHelp_IsErrorOccur = TRUE;
            ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTPRIADDR;
            st_Locker.unlock_shared();
            return FALSE;
        }
        if (stl_MapSubIterator->second.empty())
        {
            ModuleHelp_IsErrorOccur = TRUE;
            ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOLIST;
            st_Locker.unlock_shared();
            return FALSE;
        }
        BaseLib_OperatorMemory_Malloc((XPPPMEM)pppSt_P2XPClient, stl_MapSubIterator->second.size(), sizeof(XENGINE_P2XPPEER_PROTOCOL));
        list<XENGINE_P2XP_PEERINFO>::const_iterator stl_ListIterator = stl_MapSubIterator->second.begin();
        for (int i = 0; stl_ListIterator != stl_MapSubIterator->second.end(); stl_ListIterator++, i++)
        {
            *(*pppSt_P2XPClient)[i] = stl_ListIterator->st_PeerAddr;
        }
        *pInt_ListCount = stl_MapSubIterator->second.size();
    }
    else
    {
        unordered_map < string, list<XENGINE_P2XP_PEERINFO> >::const_iterator stl_MapSubIterator = stl_MapIterator->second.find(pSt_P2PProtocol->tszPrivateAddr);
        if (stl_MapSubIterator == stl_MapIterator->second.end())
        {
            ModuleHelp_IsErrorOccur = TRUE;
            ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTPRIADDR;
            st_Locker.unlock_shared();
            return FALSE;
        }
        if (stl_MapSubIterator->second.empty())
        {
            ModuleHelp_IsErrorOccur = TRUE;
            ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOLIST;
            st_Locker.unlock_shared();
            return FALSE;
        }
        BaseLib_OperatorMemory_Malloc((XPPPMEM)pppSt_P2XPClient, stl_MapSubIterator->second.size(), sizeof(XENGINE_P2XPPEER_PROTOCOL));
        list<XENGINE_P2XP_PEERINFO>::const_iterator stl_ListIterator = stl_MapSubIterator->second.begin();
        for (int i = 0; stl_ListIterator != stl_MapSubIterator->second.end(); stl_ListIterator++, i++)
        {
            *(*pppSt_P2XPClient)[i] = stl_ListIterator->st_PeerAddr;
        }
        *pInt_ListCount = stl_MapSubIterator->second.size();
    }
    st_Locker.unlock_shared();
    return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_P2PClient_GetLList
函数功能：获取同一公网下所有局域网主IP列表
 参数.一：lpszPubAddr
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要获取的IP地址
 参数.二：pppszP2XPClient
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出内网主IP地址列表
 参数.三：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：参数二需要调用基础库的BaseLib_OperatorMemory_Free函数进行内存释放
*********************************************************************/
BOOL CModuleHelp_P2PClient::ModuleHelp_P2PClient_GetLList(LPCTSTR lpszPubAddr, TCHAR*** pppszP2XPClient, int* pInt_ListCount)
{
    ModuleHelp_IsErrorOccur = FALSE;

    if ((NULL == lpszPubAddr) || (NULL == pppszP2XPClient) || (NULL == pInt_ListCount))
    {
        ModuleHelp_IsErrorOccur = TRUE;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_PARAMENT;
        return FALSE;
    }
    st_Locker.lock_shared();
    unordered_map<string, unordered_map<string, list<XENGINE_P2XP_PEERINFO> > >::const_iterator stl_MapIterator = stl_MapClients.find(lpszPubAddr);
    if (stl_MapIterator == stl_MapClients.end())
    {
        ModuleHelp_IsErrorOccur = TRUE;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND;
        st_Locker.unlock_shared();
        return FALSE;
    }
    BaseLib_OperatorMemory_Malloc((XPPPMEM)pppszP2XPClient, stl_MapIterator->second.size(), 128);
    unordered_map<string, list<XENGINE_P2XP_PEERINFO> >::const_iterator stl_MapListIterator = stl_MapIterator->second.begin();
    for (int i = 0; stl_MapListIterator != stl_MapIterator->second.end(); stl_MapListIterator++, i++)
    {
        _tcscpy((*pppszP2XPClient)[i], stl_MapListIterator->first.c_str());
    }
    *pInt_ListCount = stl_MapIterator->second.size();
    st_Locker.unlock_shared();
    return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_P2PClient_GetWList
函数功能：获取所有连接到的公网地址列表
 参数.一：pppszP2XPClient
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出地址列表
 参数.二：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleHelp_P2PClient::ModuleHelp_P2PClient_GetWList(TCHAR*** pppszP2XPClient, int* pInt_ListCount)
{
    ModuleHelp_IsErrorOccur = FALSE;

    if ((NULL == pppszP2XPClient) || (NULL == pInt_ListCount))
    {
        ModuleHelp_IsErrorOccur = TRUE;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_PARAMENT;
        return FALSE;
    }
    if (stl_MapClients.size() <= 0)
    {
        ModuleHelp_IsErrorOccur = TRUE;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND;
        return FALSE;
    }
    BaseLib_OperatorMemory_Malloc((XPPPMEM)pppszP2XPClient, stl_MapClients.size(), 128);

    st_Locker.lock_shared();
    unordered_map<string, unordered_map<string, list<XENGINE_P2XP_PEERINFO> > >::const_iterator stl_MapIterator = stl_MapClients.begin();
    for (int i = 0; stl_MapIterator != stl_MapClients.end(); stl_MapIterator++, i++)
    {
        _tcscpy((*pppszP2XPClient)[i], stl_MapIterator->first.c_str());
    }
    *pInt_ListCount = stl_MapClients.size();
    st_Locker.unlock_shared();
    return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_P2PClient_Delete
函数功能：删除一个指定的节点
 参数.一：pSt_P2PProtocol
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：要删除的节点地址
返回值
  类型：逻辑型
  意思：是否成功删除
备注：
*********************************************************************/
BOOL CModuleHelp_P2PClient::ModuleHelp_P2PClient_Delete(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol)
{
	ModuleHelp_IsErrorOccur = FALSE;
	//查找公网地址
	unordered_map<string, unordered_map<string, list<XENGINE_P2XP_PEERINFO> > >::iterator stl_MapPubIteartor = stl_MapClients.find(pSt_P2PProtocol->tszPublicAddr);
	if (stl_MapPubIteartor != stl_MapClients.end())
	{
		XENGINE_LIBADDR st_LibAddr;
		TCHAR tszPrivateAddr[64];

		memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
		memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
		if (BaseLib_OperatorIPAddr_IsIPV4Addr(pSt_P2PProtocol->tszPrivateAddr, &st_LibAddr))
		{
			_stprintf_s(tszPrivateAddr, _T("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);
			//查找私有路由地址
			unordered_map<string, list<XENGINE_P2XP_PEERINFO> >::iterator stl_MapSubIterator = stl_MapPubIteartor->second.find(tszPrivateAddr);
			if (stl_MapSubIterator != stl_MapPubIteartor->second.end())
			{
				//查找局域网自身的IP地址是否存在
				list<XENGINE_P2XP_PEERINFO>::iterator stl_ListIterator = stl_MapSubIterator->second.begin();
				for (; stl_ListIterator != stl_MapSubIterator->second.end(); stl_ListIterator++)
				{
					if (0 == _tcscmp(stl_ListIterator->st_PeerAddr.tszConnectAddr, pSt_P2PProtocol->tszConnectAddr))
					{
						//找到了删除
						stl_MapSubIterator->second.erase(stl_ListIterator);
						break;
					}
				}
				if (stl_MapSubIterator->second.empty())
				{
					//如果这个私有网络列表为空,那么就清楚他
					stl_MapPubIteartor->second.erase(stl_MapSubIterator);
				}
			}
		}
		if (stl_MapPubIteartor->second.empty())
		{
			stl_MapClients.erase(stl_MapPubIteartor);        //如果这个公有网络IP地址列表为空,那么就删除他.
		}
	}
	return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_P2PClient_DelAll
函数功能：清空节点列表数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CModuleHelp_P2PClient::ModuleHelp_P2PClient_DelAll()
{
    ModuleHelp_IsErrorOccur = FALSE;

    st_Locker.lock();
    stl_MapClients.clear();
    st_Locker.unlock();

    return TRUE;
}