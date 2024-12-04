#include "pch.h"
#include "ModuleHelp_SocketTest.h"
/********************************************************************
//    Created:     2023/02/06  11:26:27
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_SocketTest\ModuleHelp_SocketTest.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_SocketTest
//    File Base:   ModuleHelp_SocketTest
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     套接字测试
//    History:
*********************************************************************/
CModuleHelp_SocketTest::CModuleHelp_SocketTest()
{
}
CModuleHelp_SocketTest::~CModuleHelp_SocketTest()
{
}
//////////////////////////////////////////////////////////////////////////
//                    公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleHelp_SocketTest_StartConnect
函数功能：测试连接
 参数.一：pxhToken
  In/Out：Out
  类型：句柄
  可空：N
  意思：导出句柄
 参数.二：pSt_ReConnect
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：要测试的属性
 参数.三：fpCall_ReConnect
  In/Out：In/Out
  类型：回调函数
  可空：N
  意思：测试回调信息
 参数.四：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：回调函数自定义参数
返回值
  类型：句柄型
  意思：成功返回连接的句柄,失败返回NULL
备注：链接测试函数，链接一次后就关闭
*********************************************************************/
bool CModuleHelp_SocketTest::ModuleHelp_SocketTest_StartConnect(XNETHANDLE* pxhToken, MODULEHELP_SOCKETTEST_RECONNECT* pSt_ReConnect, CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST fpCall_ReConnect, XPVOID lParam /* = NULL */)
{
    ModuleHelp_IsErrorOccur = false;

    if ((NULL == pSt_ReConnect) || (NULL == fpCall_ReConnect))
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_PARAMRT;
        return false;
    }
    MODULEHELP_SOCKETTEST_CONNINFO* pSt_ConnSocket = new MODULEHELP_SOCKETTEST_CONNINFO;
    if (NULL == pSt_ConnSocket)
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_MALLOC;
        return false;
    }
    memset(pSt_ConnSocket, '\0', sizeof(MODULEHELP_SOCKETTEST_CONNINFO));
    //结构体赋值
    pSt_ConnSocket->bIsRun = true;
    pSt_ConnSocket->lParam = lParam;
    pSt_ConnSocket->lpCall_ReConnect = fpCall_ReConnect;
    BaseLib_Handle_Create(&pSt_ConnSocket->xhToken);
    memcpy(&pSt_ConnSocket->st_SocketConn, pSt_ReConnect, sizeof(MODULEHELP_SOCKETTEST_RECONNECT));
    //创建线程
    pSt_ConnSocket->pSTDThread = make_shared<std::thread>(ModuleHelp_SocketTest_ThreadConn, pSt_ConnSocket);
    if (NULL == pSt_ConnSocket->pSTDThread)
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_THREAD;
        return false;
    }
	*pxhToken = pSt_ConnSocket->xhToken;
    st_LockConn.lock();
    stl_MapConnTest.insert(make_pair(pSt_ConnSocket->xhToken, pSt_ConnSocket));
    st_LockConn.unlock();
    return true;
}
/********************************************************************
函数名称：ModuleHelp_SocketTest_GetConnect
函数功能：获取是否在处理中
 参数.一：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入操作的句柄
 参数.二：pbRun
  In/Out：Out
  类型：逻辑型指针
  可空：N
  意思：输出是否在运行
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_SocketTest::ModuleHelp_SocketTest_GetConnect(XNETHANDLE xhToken, bool* pbRun)
{
	ModuleHelp_IsErrorOccur = false;

    st_LockConn.lock_shared();
    unordered_map<XNETHANDLE, MODULEHELP_SOCKETTEST_CONNINFO*>::iterator stl_MapIterator = stl_MapConnTest.find(xhToken);
    if (stl_MapIterator == stl_MapConnTest.end())
    {
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_NOTFOUND;
        st_LockConn.unlock_shared();
		return false;
    }
    *pbRun = stl_MapIterator->second->bIsRun;
    st_LockConn.unlock_shared();
	return true;
}
/********************************************************************
函数名称：ModuleHelp_SocketTest_StopConnect
函数功能：停止短连接测试
 参数.一：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入测试的句柄
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_SocketTest::ModuleHelp_SocketTest_StopConnect(XNETHANDLE xhToken)
{
    ModuleHelp_IsErrorOccur = false;

    st_LockConn.lock();
	unordered_map<XNETHANDLE, MODULEHELP_SOCKETTEST_CONNINFO*>::iterator stl_MapIterator = stl_MapConnTest.find(xhToken);
	if (stl_MapIterator != stl_MapConnTest.end())
	{
		stl_MapIterator->second->bIsRun = false;
		stl_MapIterator->second->pSTDThread->join();
		
		if (NULL != stl_MapIterator->second->lParam)
		{
			delete (XCHAR*)stl_MapIterator->second->lParam;
			stl_MapIterator->second->lParam = NULL;
		}
		
		delete stl_MapIterator->second;
		stl_MapIterator->second = NULL;

		stl_MapConnTest.erase(stl_MapIterator);
	}
    st_LockConn.unlock();
    return true;
}
/********************************************************************
函数名称：ModuleHelp_SocketTest_StartDatas
函数功能：数据包测试函数
 参数.一：pxhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输出创建的句柄
 参数.二：pSt_SocketDatas
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：要测试的属性
 参数.三：fpCall_DataTest
  In/Out：In/Out
  类型：回调函数
  可空：N
  意思：测试回调信息
 参数.四：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：回调函数自定义参数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_SocketTest::ModuleHelp_SocketTest_StartDatas(XNETHANDLE* pxhToken, MODULEHELP_SOCKETTEST_DATAS* pSt_SocketDatas, CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST fpCall_DataTest, bool bTCP /* = true */, XPVOID lParam /* = NULL */)
{
    ModuleHelp_IsErrorOccur = false;

    if ((NULL == pSt_SocketDatas) || (NULL == fpCall_DataTest))
    {
        ModuleHelp_IsErrorOccur = true;
        ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_PARAMRT;
        return false;
    }
    MODULEHELP_SOCKETTEST_DATAINFO *pSt_DataSocket = new MODULEHELP_SOCKETTEST_DATAINFO;
    if (NULL == pSt_DataSocket)
    {
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_MALLOC;
		return false;
    }
	pSt_DataSocket->bIsRun = true;
	pSt_DataSocket->bIsTCP = bTCP;
	pSt_DataSocket->lParam = lParam;
	pSt_DataSocket->lpCall_TestDatas = fpCall_DataTest;
    BaseLib_Handle_Create(&pSt_DataSocket->xhToken);
	memcpy(&pSt_DataSocket->st_SocketData, pSt_SocketDatas, sizeof(MODULEHELP_SOCKETTEST_DATAS));
	//创建客户端
	if (pSt_DataSocket->bIsTCP)
	{
		if (!XClient_TCPSelect_Create(&pSt_DataSocket->hSocket, pSt_SocketDatas->st_REConnect.tszAddr, pSt_SocketDatas->st_REConnect.nPort))
		{
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = XClient_GetLastError();
			return false;
		}
	}
	else
	{
		if (!XClient_UDPSelect_Create(&pSt_DataSocket->hSocket))
		{
			ModuleHelp_IsErrorOccur = true;
			ModuleHelp_dwErrorCode = XClient_GetLastError();
			return false;
		}
	}
	//创建线程
	pSt_DataSocket->pSTDThread = make_shared<std::thread>(ModuleHelp_SocketTest_ThreadData, pSt_DataSocket);
	if (!pSt_DataSocket->pSTDThread->joinable())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_THREAD;
		return false;
	}
	*pxhToken = pSt_DataSocket->xhToken;
    st_LockData.lock();
    stl_MapDataTest.insert(make_pair(pSt_DataSocket->xhToken, pSt_DataSocket));
    st_LockData.unlock();
    return true;
}
/********************************************************************
函数名称：ModuleHelp_SocketTest_GetDatas
函数功能：获取是否在处理中
 参数.一：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入操作的句柄
 参数.二：pbRun
  In/Out：Out
  类型：逻辑型指针
  可空：N
  意思：输出是否在运行
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_SocketTest::ModuleHelp_SocketTest_GetDatas(XNETHANDLE xhToken, bool* pbRun)
{
	ModuleHelp_IsErrorOccur = false;

    st_LockData.lock_shared();
    unordered_map<XNETHANDLE, MODULEHELP_SOCKETTEST_DATAINFO*>::iterator stl_MapIterator = stl_MapDataTest.find(xhToken);
    if (stl_MapIterator == stl_MapDataTest.end())
    {
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_SOCKETTEST_NOTFOUND;
        st_LockData.unlock_shared();
		return false;
    }
	*pbRun = stl_MapIterator->second->bIsRun;
    st_LockData.unlock_shared();
	return true;
}
/************************************************************************
函数名称：ModuleHelp_SocketTest_DatasStop
函数功能：停止大数据包测试
  参数.一：xhToken
   In/Out：In
   类型：句柄
   可空：N
   意思：输入测试的句柄
返回值
  类型：逻辑型
  意思：是否成功
备注：
************************************************************************/
bool CModuleHelp_SocketTest::ModuleHelp_SocketTest_StopDatas(XNETHANDLE xhToken)
{
    ModuleHelp_IsErrorOccur = false;

    st_LockData.unlock();
	unordered_map<XNETHANDLE, MODULEHELP_SOCKETTEST_DATAINFO*>::iterator stl_MapIterator = stl_MapDataTest.find(xhToken);
	if (stl_MapIterator != stl_MapDataTest.end())
	{
		//关闭客户端
        stl_MapIterator->second->bIsRun = false;
        stl_MapIterator->second->pSTDThread->join();
		XClient_TCPSelect_Close(stl_MapIterator->second->hSocket);

		if (NULL != stl_MapIterator->second->lParam)
		{
			delete (XCHAR*)stl_MapIterator->second->lParam;
			stl_MapIterator->second->lParam = NULL;
		}

		delete stl_MapIterator->second;
        stl_MapIterator->second = NULL;

        stl_MapDataTest.erase(stl_MapIterator);
	}
    st_LockData.unlock();
    return true;
}
//////////////////////////////////////////////////////////////////////////
//                    线程函数
//////////////////////////////////////////////////////////////////////////
XHTHREAD CModuleHelp_SocketTest::ModuleHelp_SocketTest_ThreadConn(XPVOID lParam)
{
    MODULEHELP_SOCKETTEST_CONNINFO* pSt_ReConnect = (MODULEHELP_SOCKETTEST_CONNINFO*)lParam;
    __int64x nFailed = 0;
    __int64x nSucess = 0;
	__int64x nNumber = 0;

    while (true)
    {
		if ((nNumber >= pSt_ReConnect->st_SocketConn.nConnectTest) && (-1 != pSt_ReConnect->st_SocketConn.nConnectTest))
		{
			break;
		}
		if (!pSt_ReConnect->bIsRun)
		{
			break;
		}
		//设置TCP
		XSOCKET hSocket = INVALID_SOCKET;
		if (XClient_TCPSelect_Create(&hSocket, pSt_ReConnect->st_SocketConn.tszAddr, pSt_ReConnect->st_SocketConn.nPort, 100))
		{
			pSt_ReConnect->lpCall_ReConnect(pSt_ReConnect->xhToken, pSt_ReConnect->st_SocketConn.tszAddr, pSt_ReConnect->st_SocketConn.nPort, ++nNumber, nFailed, ++nSucess, 0, pSt_ReConnect->lParam);
		}
		else
		{
			pSt_ReConnect->lpCall_ReConnect(pSt_ReConnect->xhToken, pSt_ReConnect->st_SocketConn.tszAddr, pSt_ReConnect->st_SocketConn.nPort, ++nNumber, ++nFailed, nSucess, 1, pSt_ReConnect->lParam);
		}
		//等待指定时间关闭客户端
		std::this_thread::sleep_for(std::chrono::milliseconds(pSt_ReConnect->st_SocketConn.nContWaitTime));
		XClient_TCPSelect_Close(hSocket);
		//等待指定时链接
		std::this_thread::sleep_for(std::chrono::milliseconds(pSt_ReConnect->st_SocketConn.nCloseWaitContTime));
    }
	pSt_ReConnect->lpCall_ReConnect(pSt_ReConnect->xhToken, pSt_ReConnect->st_SocketConn.tszAddr, pSt_ReConnect->st_SocketConn.nPort, nNumber, nFailed, nSucess, 2, pSt_ReConnect->lParam);
    pSt_ReConnect->bIsRun = false;
    return 0;
}
XHTHREAD CModuleHelp_SocketTest::ModuleHelp_SocketTest_ThreadData(XPVOID lParam)
{
    MODULEHELP_SOCKETTEST_DATAINFO* pSt_DataSocket = (MODULEHELP_SOCKETTEST_DATAINFO*)lParam;
	__int64x nFailed = 0;
	__int64x nSucess = 0;
	__int64x nNumber = 0;

	while (true)
	{
		if ((nNumber >= pSt_DataSocket->st_SocketData.st_REConnect.nConnectTest) && (-1 != pSt_DataSocket->st_SocketData.st_REConnect.nConnectTest))
		{
			break;
		}
		if (!pSt_DataSocket->bIsRun)
		{
			break;
		}
		//发送数据
		bool bRet = false;
		if (pSt_DataSocket->bIsTCP)
		{
			bRet = XClient_TCPSelect_SendMsg(pSt_DataSocket->hSocket, pSt_DataSocket->st_SocketData.tszSDBuffer, pSt_DataSocket->st_SocketData.nSDLen);
		}
		else
		{
			bRet = XClient_UDPSelect_SendMsg(pSt_DataSocket->hSocket, pSt_DataSocket->st_SocketData.tszSDBuffer, pSt_DataSocket->st_SocketData.nSDLen, pSt_DataSocket->st_SocketData.st_REConnect.tszAddr, pSt_DataSocket->st_SocketData.st_REConnect.nPort);
		}
		if (bRet)
		{
			//是否需要接受数据
			if (pSt_DataSocket->st_SocketData.nRVLen > 0)
			{
				//是否需要可读判断
				if (XClient_OPTSocket_IOSelect(pSt_DataSocket->hSocket, true, pSt_DataSocket->st_SocketData.st_REConnect.nContWaitTime))
				{
					//接受数据
					int nMsgLen = pSt_DataSocket->st_SocketData.nRVLen;
					XCHAR tszMsgBuffer[4096];
					memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));

					if (pSt_DataSocket->bIsTCP)
					{
						XClient_TCPSelect_RecvMsg(pSt_DataSocket->hSocket, tszMsgBuffer, &nMsgLen);
					}
					else
					{
						XClient_UDPSelect_RecvMsg(pSt_DataSocket->hSocket, tszMsgBuffer, &nMsgLen);
					}
					//需要验证数据
					if (0 == memcmp(pSt_DataSocket->st_SocketData.tszRVBuffer, tszMsgBuffer, pSt_DataSocket->st_SocketData.nRVLen))
					{
						pSt_DataSocket->lpCall_TestDatas(pSt_DataSocket->xhToken, pSt_DataSocket->st_SocketData.st_REConnect.tszAddr, pSt_DataSocket->st_SocketData.st_REConnect.nPort, ++nNumber, nFailed, ++nSucess, 0, pSt_DataSocket->lParam);
					}
					else
					{
						pSt_DataSocket->lpCall_TestDatas(pSt_DataSocket->xhToken, pSt_DataSocket->st_SocketData.st_REConnect.tszAddr, pSt_DataSocket->st_SocketData.st_REConnect.nPort, ++nNumber, ++nFailed, nSucess, 1, pSt_DataSocket->lParam);
					}
				}
				else
				{
					pSt_DataSocket->lpCall_TestDatas(pSt_DataSocket->xhToken, pSt_DataSocket->st_SocketData.st_REConnect.tszAddr, pSt_DataSocket->st_SocketData.st_REConnect.nPort, ++nNumber, ++nFailed, nSucess, 1, pSt_DataSocket->lParam);
				}
			}
		}
		else
		{
			pSt_DataSocket->lpCall_TestDatas(pSt_DataSocket->xhToken, pSt_DataSocket->st_SocketData.st_REConnect.tszAddr, pSt_DataSocket->st_SocketData.st_REConnect.nPort, ++nNumber, ++nFailed, nSucess, 1, pSt_DataSocket->lParam);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(pSt_DataSocket->st_SocketData.st_REConnect.nCloseWaitContTime));
	}
	pSt_DataSocket->lpCall_TestDatas(pSt_DataSocket->xhToken, pSt_DataSocket->st_SocketData.st_REConnect.tszAddr, pSt_DataSocket->st_SocketData.st_REConnect.nPort, nNumber, nFailed, nSucess, 2, pSt_DataSocket->lParam);
    pSt_DataSocket->bIsRun = false;
    return 0;
}
