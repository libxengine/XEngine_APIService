#pragma once
/********************************************************************
//    Created:     2022/03/04  13:37:09
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Define.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp
//    File Base:   ModuleHelp_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出帮助模块定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                       导出回调函数
//////////////////////////////////////////////////////////////////////////
typedef void(CALLBACK* CALLBACK_APISERVICE_MODULE_HELP_P2PCLIENT)(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol, LPVOID lParam);
//////////////////////////////////////////////////////////////////////////
//                       导出数据结构
//////////////////////////////////////////////////////////////////////////
//计时器
typedef struct 
{
	__int64x dwUserTime;                                                  //用户存在时间
	__int64x dwPacketTime;                                                //包时间,拿到包后的存活时间
	__int64x dwKeepAlive;                                                 //保活计时器时间,经过网络时间
	unsigned short int usTTL : 1;                                         //路由数
}P2XP_TIMER_INFOMATION, * LPP2XP_TIMER_INFOMATION;
//一个节点信息
typedef struct 
{
	XENGINE_P2XPPEER_PROTOCOL st_PeerAddr;                                //P2P通信的时候使用的地址（客户方使用）
	P2XP_TIMER_INFOMATION st_PeerTimer;                                   //节点时间信息
	XENGINE_IPADDRINFO st_IPAddrInfo;                                     //IP地址信息
	BOOL bIsLogin;
}XENGINE_P2XP_PEERINFO, * LPNETENGINE_P2XP_PEERINFO;
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD ModuleHelp_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                         导出的身份证帮助函数                         */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_IDCard_CheckBirth
函数功能：检查身份证号生日
 参数.一：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要检查的身份结构
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleHelp_IDCard_CheckBirth(XENGINE_IDCARDINFO* pSt_IDInfo);
/********************************************************************
函数名称：ModuleHelp_IDCard_CheckBirth
函数功能：检查身份证的校验码是否正确
 参数.一：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要检查的身份结构
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleHelp_IDCard_CheckSum(XENGINE_IDCARDINFO* pSt_IDInfo);
/************************************************************************/
/*                         导出的语言转换帮助函数                       */
/************************************************************************/
/********************************************************************
函数名称：ModuleHelp_Language_ConvertZh
函数功能：中文语言转换函数
 参数.一：lpszJsonFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的配置文件
 参数.一：lpszSourceStr
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要转换的字符串
 参数.一：ptszDestStr
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的字符串
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleHelp_Language_ConvertZh(LPCTSTR lpszJsonFile, LPCTSTR lpszSourceStr, TCHAR* ptszDestStr);
/********************************************************************
函数名称：ModuleHelp_Translation_Convert
函数功能：翻译类型转换
 参数.一：enTranslationType
  In/Out：In
  类型：枚举型
  可空：N
  意思：输入要转换的类型
 参数.二：ptszTranslationType
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的类型
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleHelp_Translation_Convert(ENUM_XENGINE_APISERVICE_TRANSLATION_TYPE enTranslationType, TCHAR* ptszTranslationType);
/************************************************************************/
/*                       节点管理器导出函数                             */
/************************************************************************/
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
extern "C" BOOL ModuleHelp_P2PClient_Init(int nTimeout, CALLBACK_APISERVICE_MODULE_HELP_P2PCLIENT fpCall_P2PClient, LPVOID lParam = NULL);
/********************************************************************
函数名称：ModuleHelp_P2PClient_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleHelp_P2PClient_Destory();
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
extern "C" BOOL ModuleHelp_P2PClient_Add(XENGINE_P2XP_PEERINFO * pSt_PeerInfo);
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
extern "C" BOOL ModuleHelp_P2PClient_Get(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol, XENGINE_P2XP_PEERINFO * pSt_PeerInfo = NULL);
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
extern "C" BOOL ModuleHelp_P2PClient_GetLan(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol, XENGINE_P2XPPEER_PROTOCOL * **pppSt_P2XPClient, int* pInt_ListCount);
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
extern "C" BOOL ModuleHelp_P2PClient_GetLList(LPCSTR lpszPubAddr, CHAR * **pppszP2XPClient, int* pInt_ListCount);
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
extern "C" BOOL ModuleHelp_P2PClient_GetWList(CHAR * **pppszP2XPClient, int* pInt_ListCount);
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
extern "C" BOOL ModuleHelp_P2PClient_Delete(XENGINE_P2XPPEER_PROTOCOL * pSt_P2PProtocol);
/********************************************************************
函数名称：ModuleHelp_P2PClient_DelAll
函数功能：清空节点列表数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL ModuleHelp_P2PClient_DelAll();
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
extern "C" BOOL ModuleHelp_P2PClient_Heart(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol);