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
	XSOCKET hSocket;
	XBOOL bIsTCP;
	XBOOL bIsRun;                                                      //是否运行

	shared_ptr<std::thread> pSTDThread;
	XPVOID lParam;
	CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST lpCall_TestDatas;
}MODULEHELP_SOCKETTEST_DATAINFO;
typedef struct
{
	MODULEHELP_SOCKETTEST_RECONNECT st_SocketConn;
	XNETHANDLE xhToken;                                               //句柄
	XBOOL bIsRun;                                                      //是否运行

	shared_ptr<std::thread> pSTDThread;                               //线程句柄
	XPVOID lParam;
	CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST lpCall_ReConnect;
}MODULEHELP_SOCKETTEST_CONNINFO;


class CModuleHelp_SocketTest
{
public:
	CModuleHelp_SocketTest();
    ~CModuleHelp_SocketTest();
public:
	//链接测试
	XBOOL ModuleHelp_SocketTest_StartConnect(XNETHANDLE* pxhToken, MODULEHELP_SOCKETTEST_RECONNECT* pSt_ReConnect, CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST fpCall_ReConnect, XPVOID lParam = NULL);
	XBOOL ModuleHelp_SocketTest_GetConnect(XNETHANDLE xhToken, XBOOL* pbRun);
	XBOOL ModuleHelp_SocketTest_StopConnect(XNETHANDLE xhToken);
	//数据包压力测试
	XBOOL ModuleHelp_SocketTest_StartDatas(XNETHANDLE* pxhToken, MODULEHELP_SOCKETTEST_DATAS* pSt_SocketDatas, CALLBACK_APISERVICE_MODULE_HELP_SOCKETTEST fpCall_DataTest, XBOOL bTCP = TRUE, XPVOID lParam = NULL);
	XBOOL ModuleHelp_SocketTest_GetDatas(XNETHANDLE xhToken, XBOOL* pbRun);
	XBOOL ModuleHelp_SocketTest_StopDatas(XNETHANDLE xhToken);
protected:
    static XHTHREAD ModuleHelp_SocketTest_ThreadConn(XPVOID lParam);          //反复连接测试线程
    static XHTHREAD ModuleHelp_SocketTest_ThreadData(XPVOID lParam);                  //大数据包长连接测试
private:
	shared_mutex st_LockConn;
	shared_mutex st_LockData;
private:
	unordered_map<XNETHANDLE, MODULEHELP_SOCKETTEST_CONNINFO*> stl_MapConnTest;
	unordered_map<XNETHANDLE, MODULEHELP_SOCKETTEST_DATAINFO*> stl_MapDataTest;
};
