#pragma once
/********************************************************************
//    Created:     2023/02/06  11:26:18
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_SocketTest\ModuleHelp_SocketTest.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_SocketTest
//    File Base:   ModuleHelp_SocketTest
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     套接字测试
//    History:
*********************************************************************/
typedef struct
{
	MODULEHELP_SOCKETTEST_DATAS st_SocketData;
	XNETHANDLE xhToken;                                               //句柄
	SOCKET hSocket;
	BOOL bIsTCP;
	BOOL bIsRun;                                                      //是否运行

	shared_ptr<std::thread> pSTDThread;
	LPVOID lParam;
	CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST lpCall_TestDatas;
}MODULEHELP_SOCKETTEST_DATAINFO;
typedef struct
{
	MODULEHELP_SOCKETTEST_RECONNECT st_SocketConn;
	XNETHANDLE xhToken;                                               //句柄
	BOOL bIsRun;                                                      //是否运行

	shared_ptr<std::thread> pSTDThread;                               //线程句柄
	LPVOID lParam;
	CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST lpCall_ReConnect;
}MODULEHELP_SOCKETTEST_CONNINFO;


class CModuleHelp_SocketTest
{
public:
	CModuleHelp_SocketTest();
    ~CModuleHelp_SocketTest();
public:
	//链接测试
	BOOL ModuleHelp_SocketTest_StartConnect(XNETHANDLE* pxhToken, MODULEHELP_SOCKETTEST_RECONNECT* pSt_ReConnect, CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST fpCall_ReConnect, LPVOID lParam = NULL);
	BOOL ModuleHelp_SocketTest_GetConnect(XNETHANDLE xhToken, BOOL* pbRun);
	BOOL ModuleHelp_SocketTest_StopConnect(XNETHANDLE xhToken);
	//数据包压力测试
	BOOL ModuleHelp_SocketTest_StartDatas(XNETHANDLE* pxhToken, MODULEHELP_SOCKETTEST_DATAS* pSt_SocketDatas, CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST fpCall_DataTest, BOOL bTCP = TRUE, LPVOID lParam = NULL);
	BOOL ModuleHelp_SocketTest_GetDatas(XNETHANDLE xhToken, BOOL* pbRun);
	BOOL ModuleHelp_SocketTest_StopDatas(XNETHANDLE xhToken);
protected:
    static XHTHREAD ModuleHelp_SocketTest_ThreadConnect(LPVOID lParam);          //反复连接测试线程
    static XHTHREAD StressTest_Thread_DatasTest(LPVOID lParam);                  //大数据包长连接测试
private:
	shared_mutex st_LockConn;
	shared_mutex st_LockData;
private:
	unordered_map<XNETHANDLE, MODULEHELP_SOCKETTEST_CONNINFO*> stl_MapConnTest;
	unordered_map<XNETHANDLE, MODULEHELP_SOCKETTEST_DATAINFO*> stl_MapDataTest;
};
