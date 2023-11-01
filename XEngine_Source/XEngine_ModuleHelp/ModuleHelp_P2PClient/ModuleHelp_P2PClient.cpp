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
函数名称：ModuleHelp_P2PClient_Init
函数功能：初始化P2P客户端
 参数.一：nTimeout
  In/Out：In
  类型：整数型
  可空：N
  意思：输入超时时间,秒
 参数.二：fpCall_P2PClient
  In/Out：In/Out
  类型：回调函数
  可空：N
  意思：P2P客户端导出信息
 参数.三：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：回调函数自定义参数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_P2PClient::ModuleHelp_P2PClient_Init(int nTimeout, CALLBACK_APISERVICE_MODULE_HELP_P2PCLIENT fpCall_P2PClient, XPVOID lParam /* = NULL */)
{
    ModuleHelp_IsErrorOccur = false;

    m_bIsRun = true;
    m_nTimeout = nTimeout;
    m_lParam = lParam;
    lpCall_P2PClient = fpCall_P2PClient;

    pSTDThread = make_shared<std::thread>(ModuleHelp_P2PClient_Thread, this);
    if (NULL == pSTDThread)
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_THREAD;
        return false;
    }
    return true;
}
/********************************************************************
函数名称：ModuleHelp_P2PClient_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_P2PClient::ModuleHelp_P2PClient_Destory()
{
	ModuleHelp_IsErrorOccur = false;

    if (m_bIsRun)
    {
        m_bIsRun = false;
        if (pSTDThread->joinable())
        {
            pSTDThread->join();
        }
    }
	return true;
}
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
bool CModuleHelp_P2PClient::ModuleHelp_P2PClient_Add(XENGINE_P2XP_PEERINFO* pSt_PeerInfo)
{
    ModuleHelp_IsErrorOccur = false;

    st_Locker.lock();
	unordered_map<string, unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> > >::iterator stl_MapIteratorAddr = stl_MapClients.find(pSt_PeerInfo->st_PeerAddr.tszPublicAddr);
	if (stl_MapIteratorAddr == stl_MapClients.end())
	{
		//没有找到,一个一个加入,首先加入私有同步网络
        unordered_map<string, XENGINE_P2XP_PEERINFO> stl_MapPrivate;
        stl_MapPrivate.insert(make_pair(pSt_PeerInfo->st_PeerAddr.tszPrivateAddr, *pSt_PeerInfo));
		//获取私有网络的路由地址
		XENGINE_LIBADDR st_LibAddr;
		XCHAR tszPrivateAddr[64];

		memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
		memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
		if (!BaseLib_OperatorIPAddr_IsIPV4Addr(pSt_PeerInfo->st_PeerAddr.tszPrivateAddr, &st_LibAddr))
		{
			//没有内网地址不加入.
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = BaseLib_GetLastError();
			return false;
		}
		_xstprintf(tszPrivateAddr, _X("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);
		//然后加入到私网地址
		unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> > stl_MapPriAddr;
        stl_MapPriAddr.insert(make_pair(tszPrivateAddr, stl_MapPrivate));
        //加入公网
		stl_MapClients.insert(make_pair(pSt_PeerInfo->st_PeerAddr.tszPublicAddr, stl_MapPriAddr));
	}
	else
	{
		//找到了这个公网的地址
		XENGINE_LIBADDR st_LibAddr;
		XCHAR tszPrivateAddr[64];

		memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
		memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
		//获取私有网络的路由地址
		if (!BaseLib_OperatorIPAddr_IsIPV4Addr(pSt_PeerInfo->st_PeerAddr.tszPrivateAddr, &st_LibAddr))
		{
			//没有内网地址不加入.
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = BaseLib_GetLastError();
			return false;
		}
		//内网地址192.168.1.2  内网出口192.168.1.1 链接地址10.0.1.0:13444
		_xstprintf(tszPrivateAddr, _X("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);
		unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> >::iterator stl_MapPriIteartor = stl_MapIteratorAddr->second.find(tszPrivateAddr);
		if (stl_MapPriIteartor == stl_MapIteratorAddr->second.end())
		{
            //没有私网地址
			unordered_map<string, XENGINE_P2XP_PEERINFO> stl_MapPrivate;
			stl_MapPrivate.insert(make_pair(pSt_PeerInfo->st_PeerAddr.tszPrivateAddr, *pSt_PeerInfo));

			stl_MapIteratorAddr->second.insert(make_pair(tszPrivateAddr, stl_MapPrivate));
		}
		else
		{
            //查找链接地址是否存在.存在表示已经加入过了,那么就什么都不做
            unordered_map<string, XENGINE_P2XP_PEERINFO>::iterator stl_MapConnIterator = stl_MapPriIteartor->second.find(pSt_PeerInfo->st_PeerAddr.tszPrivateAddr);
            if (stl_MapConnIterator == stl_MapPriIteartor->second.find(pSt_PeerInfo->st_PeerAddr.tszPrivateAddr))
			{
                //没有找到就加入
                stl_MapPriIteartor->second.insert(make_pair(pSt_PeerInfo->st_PeerAddr.tszPrivateAddr, *pSt_PeerInfo));
			}
		}
	}
    st_Locker.unlock();
    return true;
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
bool CModuleHelp_P2PClient::ModuleHelp_P2PClient_GetLan(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol, XENGINE_P2XPPEER_PROTOCOL*** pppSt_P2XPClient, int* pInt_ListCount)
{
    ModuleHelp_IsErrorOccur = false;

    if ((NULL == pSt_P2PProtocol) || (NULL == pppSt_P2XPClient) || (NULL == pInt_ListCount))
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_PARAMENT;
        return false;
    }
    //查找公网IP地址
    st_Locker.lock_shared();
    unordered_map<string, unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> > >::const_iterator stl_MapPubIterator = stl_MapClients.find(pSt_P2PProtocol->tszPublicAddr);
    if (stl_MapPubIterator == stl_MapClients.end())
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTPUBADDRR;
        st_Locker.unlock_shared();
        return false;
    }
    XENGINE_LIBADDR st_LibAddr;
    XCHAR tszPrivateAddr[64];

    memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
    memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
    //如果输入的是192.168.1.1 IP,就我们自己分割,否则认为输入的是 192.168.1
    if (BaseLib_OperatorIPAddr_IsIPV4Addr(pSt_P2PProtocol->tszPrivateAddr, &st_LibAddr))
    {
        _xstprintf(tszPrivateAddr, _X("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);
        unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> >::const_iterator stl_MapPriIterator = stl_MapPubIterator->second.find(tszPrivateAddr);
        if (stl_MapPriIterator == stl_MapPubIterator->second.end())
        {
            ModuleHelp_IsErrorOccur = true;
            ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTPRIADDR;
            st_Locker.unlock_shared();
            return false;
        }
        if (stl_MapPriIterator->second.empty())
        {
            ModuleHelp_IsErrorOccur = true;
            ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOLIST;
            st_Locker.unlock_shared();
            return false;
        }
        BaseLib_OperatorMemory_Malloc((XPPPMEM)pppSt_P2XPClient, stl_MapPriIterator->second.size(), sizeof(XENGINE_P2XPPEER_PROTOCOL));
        unordered_map<string, XENGINE_P2XP_PEERINFO>::const_iterator stl_MapConnIterator = stl_MapPriIterator->second.begin();
        for (int i = 0; stl_MapConnIterator != stl_MapPriIterator->second.end(); stl_MapConnIterator++, i++)
        {
            *(*pppSt_P2XPClient)[i] = stl_MapConnIterator->second.st_PeerAddr;
        }
        *pInt_ListCount = (int)stl_MapPriIterator->second.size();
    }
    else
    {
        unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> >::const_iterator stl_MapPriIterator = stl_MapPubIterator->second.find(pSt_P2PProtocol->tszPrivateAddr);
        if (stl_MapPriIterator == stl_MapPubIterator->second.end())
        {
            ModuleHelp_IsErrorOccur = true;
            ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTPRIADDR;
            st_Locker.unlock_shared();
            return false;
        }
        if (stl_MapPriIterator->second.empty())
        {
            ModuleHelp_IsErrorOccur = true;
            ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOLIST;
            st_Locker.unlock_shared();
            return false;
        }
        BaseLib_OperatorMemory_Malloc((XPPPMEM)pppSt_P2XPClient, stl_MapPriIterator->second.size(), sizeof(XENGINE_P2XPPEER_PROTOCOL));
        unordered_map<string, XENGINE_P2XP_PEERINFO>::const_iterator stl_MapConnIterator = stl_MapPriIterator->second.begin();
        for (int i = 0; stl_MapConnIterator != stl_MapPriIterator->second.end(); stl_MapConnIterator++, i++)
        {
            *(*pppSt_P2XPClient)[i] = stl_MapConnIterator->second.st_PeerAddr;
        }
        *pInt_ListCount = (int)stl_MapPriIterator->second.size();
    }
    st_Locker.unlock_shared();
    return true;
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
bool CModuleHelp_P2PClient::ModuleHelp_P2PClient_GetLList(LPCXSTR lpszPubAddr, XCHAR*** pppszP2XPClient, int* pInt_ListCount)
{
    ModuleHelp_IsErrorOccur = false;

    if ((NULL == lpszPubAddr) || (NULL == pppszP2XPClient) || (NULL == pInt_ListCount))
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_PARAMENT;
        return false;
    }
    st_Locker.lock_shared();
    unordered_map<string, unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> > >::const_iterator stl_MapPubIterator = stl_MapClients.find(lpszPubAddr);
    if (stl_MapPubIterator == stl_MapClients.end())
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND;
        st_Locker.unlock_shared();
        return false;
    }
    BaseLib_OperatorMemory_Malloc((XPPPMEM)pppszP2XPClient, stl_MapPubIterator->second.size(), 128);
    unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> >::const_iterator stl_MapPriIterator = stl_MapPubIterator->second.begin();
    for (int i = 0; stl_MapPriIterator != stl_MapPubIterator->second.end(); stl_MapPriIterator++, i++)
    {
        _tcsxcpy((*pppszP2XPClient)[i], stl_MapPriIterator->first.c_str());
    }
    *pInt_ListCount = (int)stl_MapPubIterator->second.size();
    st_Locker.unlock_shared();
    return true;
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
bool CModuleHelp_P2PClient::ModuleHelp_P2PClient_GetWList(XCHAR*** pppszP2XPClient, int* pInt_ListCount)
{
    ModuleHelp_IsErrorOccur = false;

    if ((NULL == pppszP2XPClient) || (NULL == pInt_ListCount))
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_PARAMENT;
        return false;
    }
    if (stl_MapClients.size() <= 0)
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND;
        return false;
    }
    BaseLib_OperatorMemory_Malloc((XPPPMEM)pppszP2XPClient, stl_MapClients.size(), 128);

    st_Locker.lock_shared();
    unordered_map<string, unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> > >::const_iterator stl_MapIterator = stl_MapClients.begin();
    for (int i = 0; stl_MapIterator != stl_MapClients.end(); stl_MapIterator++, i++)
    {
        _tcsxcpy((*pppszP2XPClient)[i], stl_MapIterator->first.c_str());
    }
    *pInt_ListCount = (int)stl_MapClients.size();
    st_Locker.unlock_shared();
    return true;
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
bool CModuleHelp_P2PClient::ModuleHelp_P2PClient_Delete(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol)
{
	ModuleHelp_IsErrorOccur = false;
	//查找公网地址
	unordered_map<string, unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> > >::iterator stl_MapPubIteartor = stl_MapClients.find(pSt_P2PProtocol->tszPublicAddr);
	if (stl_MapPubIteartor != stl_MapClients.end())
	{
		XENGINE_LIBADDR st_LibAddr;
		XCHAR tszPrivateAddr[64];

		memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
		memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
		if (BaseLib_OperatorIPAddr_IsIPV4Addr(pSt_P2PProtocol->tszPrivateAddr, &st_LibAddr))
		{
			_xstprintf(tszPrivateAddr, _X("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);
			//查找私有路由地址
			unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> >::iterator stl_MapPriIterator = stl_MapPubIteartor->second.find(tszPrivateAddr);
			if (stl_MapPriIterator != stl_MapPubIteartor->second.end())
			{
				//查找局域网自身的IP地址是否存在
                unordered_map<string, XENGINE_P2XP_PEERINFO>::iterator stl_MapConnIterator = stl_MapPriIterator->second.find(pSt_P2PProtocol->tszPrivateAddr);
				if (stl_MapConnIterator != stl_MapPriIterator->second.end())
				{
					//找到了删除
					stl_MapPriIterator->second.erase(stl_MapConnIterator);
				}
				if (stl_MapPriIterator->second.empty())
				{
					//如果这个私有网络列表为空,那么就清楚他
					stl_MapPubIteartor->second.erase(stl_MapPriIterator);
				}
			}
		}
		if (stl_MapPubIteartor->second.empty())
		{
			stl_MapClients.erase(stl_MapPubIteartor);        //如果这个公有网络IP地址列表为空,那么就删除他.
		}
	}
	return true;
}
/********************************************************************
函数名称：ModuleHelp_P2PClient_DelAll
函数功能：清空节点列表数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_P2PClient::ModuleHelp_P2PClient_DelAll()
{
    ModuleHelp_IsErrorOccur = false;

    st_Locker.lock();
    stl_MapClients.clear();
    st_Locker.unlock();

    return true;
}
/********************************************************************
函数名称：ModuleHelp_P2PClient_Heart
函数功能：触发一次心跳
 参数.一：pSt_P2PProtocol
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：要操作的节点地址
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_P2PClient::ModuleHelp_P2PClient_Heart(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol)
{
	ModuleHelp_IsErrorOccur = false;

	if (NULL == pSt_P2PProtocol)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_PARAMENT;
		return false;
	}
	//查找元素
	st_Locker.lock_shared();
	unordered_map<string, unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> > >::iterator stl_MapPubIterator = stl_MapClients.find(pSt_P2PProtocol->tszPublicAddr);
	if (stl_MapPubIterator == stl_MapClients.end())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND;
		st_Locker.unlock_shared();
		return false;
	}
	//转换地址
	XENGINE_LIBADDR st_LibAddr;
	XCHAR tszPrivateAddr[64];

	memset(tszPrivateAddr, '\0', sizeof(tszPrivateAddr));
	memset(&st_LibAddr, '\0', sizeof(XENGINE_LIBADDR));
	//获取私有网络的路由地址
	BaseLib_OperatorIPAddr_IsIPV4Addr(pSt_P2PProtocol->tszPrivateAddr, &st_LibAddr);
	_xstprintf(tszPrivateAddr, _X("%d.%d.%d"), st_LibAddr.nIPAddr1, st_LibAddr.nIPAddr2, st_LibAddr.nIPAddr3);

	unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> >::iterator stl_MapPriIterator = stl_MapPubIterator->second.find(tszPrivateAddr);
	if (stl_MapPriIterator == stl_MapPubIterator->second.end())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND;
		st_Locker.unlock_shared();
		return false;
	}
	unordered_map<string, XENGINE_P2XP_PEERINFO>::iterator stl_MapConnIterator = stl_MapPriIterator->second.find(pSt_P2PProtocol->tszPrivateAddr);
	if (stl_MapConnIterator == stl_MapPriIterator->second.end())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_P2P_NOTFOUND;
		st_Locker.unlock_shared();
		return false;
	}
    stl_MapConnIterator->second.st_PeerTimer.dwUserTime = time(NULL);
	st_Locker.unlock_shared();
	return true;
}
//////////////////////////////////////////////////////////////////////////
//                          保护函数
//////////////////////////////////////////////////////////////////////////
XHTHREAD CALLBACK CModuleHelp_P2PClient::ModuleHelp_P2PClient_Thread(XPVOID lParam)
{
    CModuleHelp_P2PClient* pClass_This = (CModuleHelp_P2PClient*)lParam;
    list<XENGINE_P2XP_PEERINFO> stl_ListRemove;

    while (pClass_This->m_bIsRun)
    {
        pClass_This->st_Locker.lock_shared();
        //公网轮训
        for (unordered_map<string, unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> > >::iterator stl_MapPubIterator = pClass_This->stl_MapClients.begin(); stl_MapPubIterator != pClass_This->stl_MapClients.end(); stl_MapPubIterator++)
        {
            //内网轮训
            for (unordered_map<string, unordered_map<string, XENGINE_P2XP_PEERINFO> >::iterator stl_MapPriIterator = stl_MapPubIterator->second.begin(); stl_MapPriIterator != stl_MapPubIterator->second.end(); stl_MapPriIterator++)
            {
                //连接地址
                for (unordered_map<string, XENGINE_P2XP_PEERINFO>::iterator stl_MapConnIterator = stl_MapPriIterator->second.begin(); stl_MapConnIterator != stl_MapPriIterator->second.end(); stl_MapConnIterator++)
                {
                    //是否超时
                    time_t nTimeEnd = time(NULL);
                    if ((nTimeEnd - stl_MapConnIterator->second.st_PeerTimer.dwUserTime) > pClass_This->m_nTimeout)
                    {
                        stl_ListRemove.push_back(stl_MapConnIterator->second);
                    }
                }
            }
        }
        pClass_This->st_Locker.unlock_shared();

        for (auto stl_ListIterator = stl_ListRemove.begin(); stl_ListIterator != stl_ListRemove.end(); stl_ListIterator++)
        {
            pClass_This->lpCall_P2PClient((XENGINE_P2XPPEER_PROTOCOL*)&stl_ListIterator->st_PeerAddr, pClass_This->m_lParam);
            pClass_This->ModuleHelp_P2PClient_Delete((XENGINE_P2XPPEER_PROTOCOL*) &stl_ListIterator->st_PeerAddr);
        }
        stl_ListRemove.clear();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}