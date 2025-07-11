﻿#pragma once
/********************************************************************
//    Created:     2022/02/28  14:21:45
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol\ModuleProtocol_Define.h
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleProtocol
//    File Base:   ModuleProtocol_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出协议模块定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleProtocol_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                         导出的协议打包函数                           */
/************************************************************************/
/********************************************************************
函数名称：ModuleProtocol_Packet_Common
函数功能：公用协议打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打好包的缓冲区
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出缓冲区大小
 参数.三：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.四：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入要打包的后续内容
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_Common(XCHAR * ptszMsgBuffer, int* pInt_MsgLen, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
/********************************************************************
函数名称：ModuleProtocol_Packet_IDQuery
函数功能：ID查询打包为JSON的封包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的ID信息
 参数.四：pSt_IDRegion
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入ID地址信息
 参数.五：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.六：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_IDQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDCARDINFO* pSt_IDInfo, XENGINE_IDREGION* pSt_IDRegion, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
/********************************************************************
函数名称：ModuleProtocol_Packet_IDRegion
函数功能：ID区域转换
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_IDRegion
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
 参数.四：nIDRegion
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入要打包的ID
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_IDRegion(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IDREGION* pSt_IDRegion, int nIDRegion);
/********************************************************************
函数名称：ModuleProtocol_Packet_BankQuery
函数功能：银行卡信息查询打包为JSON
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_BankInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.五：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_BankQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_BANKINFO* pSt_BankInfo, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
/********************************************************************
函数名称：ModuleProtocol_Packet_LanguageQuery
函数功能：语言打包为JSON
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_LanguageInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.五：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_LanguageQuery(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
/********************************************************************
函数名称：ModuleProtocol_Packet_Locker
函数功能：分布式锁协议打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入要打包的数据
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.五：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_Locker(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
/********************************************************************
函数名称：ModuleProtocol_Packet_ZIPCode
函数功能：打包行政邮编信息协议
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_ZIPInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
 参数.四：nCode
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入返回的值
 参数.五：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：输入操作结果
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_ZIPCode(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_ZIPINFO* pSt_ZIPInfo, int nCode = 0, LPCXSTR lpszMsgBuffer = NULL);
/********************************************************************
函数名称：ModuleProtocol_Packet_TestReport
函数功能：套接字测试信息打包
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入句柄
 参数.四：lpszIPAddr
  In/Out：In
  类型：常量字符指针
  可空：N
 参数.五：nIPPort
  In/Out：In
  类型：整数型
  可空：N
  意思：测试的端口
 参数.六：nNumber
  In/Out：In
  类型：整数型
  可空：N
  意思：测试的次数
 参数.七：nFailed
  In/Out：In
  类型：整数型
  可空：N
  意思：失败的次数
 参数.八：nSuccess
  In/Out：In
  类型：整数型
  可空：N
  意思：成功的次数
 参数.九：nStatus
  In/Out：In
  类型：整数型
  可空：N
  意思：运行状态
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_TestReport(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken, LPCXSTR lpszIPAddr, int nIPPort, __int64x nNumber, __int64x nFailed, __int64x nSuccess, int nStatus);
/********************************************************************
函数名称：ModuleProtocol_Packet_TestReply
函数功能：请求返回
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：xhToken
  In/Out：In
  类型：句柄
  可空：N
  意思：输入句柄
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_TestReply(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XNETHANDLE xhToken);
/********************************************************************
函数名称：ModuleProtocol_Packet_P2PLan
函数功能：响应同步局域网地址列表
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出封装好的缓冲区
 参数.二：pInt_MsgLen
  In/Out：In/Out
  类型：整数型指针
  可空：N
  意思：输入你的缓冲区大小,输出缓冲区真实大小
 参数.三：pppSt_ListClients
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入局域网地址信息列表
 参数.四：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：局域网地址列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_P2PLan(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_P2XPPEER_PROTOCOL*** pppSt_ListClients, int nListCount);
/********************************************************************
函数名称：ModuleProtocol_Packet_P2PWLan
函数功能：响应同步局域网所有地址列表
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出封装好的缓冲区
 参数.二：pInt_MsgLen
  In/Out：In/Out
  类型：整数型指针
  可空：N
  意思：输入你的缓冲区大小,输出缓冲区真实大小
 参数.三：pStl_ListClients
  In/Out：In
  类型：容器指针
  可空：N
  意思：客户端列表
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_P2PWLan(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, list<XENGINE_P2XPPEER_PROTOCOL>* pStl_ListClients);
/********************************************************************
函数名称：ModuleProtocol_Packet_P2PWList
函数功能：打包公有地址列表
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出封装好的缓冲区
 参数.二：pInt_MsgLen
  In/Out：In/Out
  类型：整数型指针
  可空：N
  意思：输入你的缓冲区大小,输出缓冲区真实大小
 参数.三：ppptszListAddr
  In/Out：In
  类型：三级指针
  可空：N
  意思：客户端列表
 参数.四：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_P2PWList(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** ppptszListAddr, int nListCount);
/********************************************************************
函数名称：ModuleProtocol_Packet_Log
函数功能：日志信息打包
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pppSt_XLogList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的数据
 参数.四：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：输入打包数据个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_Log(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_XLOGINFO*** pppSt_XLogList, int nListCount);
/********************************************************************
函数名称：ModuleProtocol_Packet_LogShow
函数功能：日志表名打包
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：ppptszList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的数据
 参数.四：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：输入打包数据个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_LogShow(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** ppptszList, int nListCount);
/********************************************************************
函数名称：ModuleProtocol_Packet_Weather
函数功能：天气信息协议打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_WeatherInfo
  In/Out：In
  类型：数据结构
  可空：N
  意思：输入要打包的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_Weather(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_WEATHERINFO* pSt_WeatherInfo);
/********************************************************************
函数名称：ModuleProtocol_Packet_ShortLink
函数功能：短连接生成协议打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_ShortLink
  In/Out：In
  类型：数据结构
  可空：N
  意思：输入要打包的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_ShortLink(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_SHORTLINK* pSt_ShortLink);
/********************************************************************
函数名称：ModuleProtocol_Packet_ShortLinkList
函数功能：短链接列表打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pppSt_MachineList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的数据
 参数.四：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：输入打包数据个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_ShortLinkList(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_SHORTLINK*** pppSt_ShortLink, int nListCount);
/********************************************************************
函数名称：ModuleProtocol_Packet_WordFilter
函数功能：敏感词生成协议打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_WordFilter
  In/Out：In
  类型：数据结构
  可空：N
  意思：输入要打包的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_WordFilter(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_WORDFILTER* pSt_WordFilter);
/********************************************************************
函数名称：ModuleProtocol_Packet_WordFilterList
函数功能：敏感词列表打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pppSt_MachineList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的数据
 参数.四：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：输入打包数据个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_WordFilterList(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_WORDFILTER*** pppSt_WordFilter, int nListCount);
/********************************************************************
函数名称：ModuleProtocol_Packet_ImageAttr
函数功能：图片属性打包
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_BaseInfo
  In/Out：In
  类型：数据结构
  可空：N
  意思：输入要打包的信息
 参数.四：pSt_ExtAttr
  In/Out：In
  类型：数据结构
  可空：N
  意思：输入要打包的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_ImageAttr(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XENGINE_IMGBASEATTR* pSt_BaseInfo, XENGINE_IMGEXTATTR* pSt_ExtAttr);
/********************************************************************
函数名称：ModuleProtocol_Packet_ImageText
函数功能：图片文本识别打包
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pppListStr
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的文本列表
 参数.四：nListCount
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_ImageText(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** pppListStr, int nListCount);
/********************************************************************
函数名称：ModuleProtocol_Packet_EnumDevice
函数功能：打包枚举的设备信息
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pppSt_AudioList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的音频设备信息
 参数.四：pppSt_VideoList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的视频设备信息
 参数.五：nACount
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入音频设备个数
 参数.六：nVCount
  In/Out：In
  类型：整数型
  可空：Y
  意思：输入视频设备个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_EnumDevice(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, AVHELP_DEVICEINFO*** pppSt_AudioList, AVHELP_DEVICEINFO*** pppSt_VideoList, int nACount, int nVCount);
/********************************************************************
函数名称：ModuleProtocol_Packet_ListFile
函数功能：打包文件列表信息
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pppszFileList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的文件列表
 参数.四：nListCount
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_ListFile(XCHAR* ptszMsgBuffer, int* pInt_MsgLen, XCHAR*** pppszFileList, int nListCount);
/********************************************************************
函数名称：ModuleProtocol_Packet_Machine
函数功能：机器信息列表打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pppSt_MachineList
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入要打包的数据
 参数.四：nListCount
  In/Out：In
  类型：整数型
  可空：N
  意思：输入打包数据个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_Machine(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_MACHINEINFO*** pppSt_MachineList, int nListCount);
/********************************************************************
函数名称：ModuleProtocol_Packet_OilInfo
函数功能：油价信息打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_OilInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_OilInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_OILINFO* pSt_OilInfo);
/********************************************************************
函数名称：ModuleProtocol_Packet_PhoneInfo
函数功能：电话号码信息打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_PhoneInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_PhoneInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_PHONEINFO* pSt_PhoneInfo);
/********************************************************************
函数名称：ModuleProtocol_Packet_IPAddr
函数功能：IP地址信息打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_PhoneInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_IPAddr(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_IPADDRINFO* pSt_IPAddrInfo);
/********************************************************************
函数名称：ModuleProtocol_Packet_MacInfo
函数功能：MAC地址信息打包函数
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打包的数据信息
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出打包大小
 参数.三：pSt_PhoneInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要打包的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_MacInfo(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, XENGINE_MACADDRINFO* pSt_MacInfo);
/********************************************************************
函数名称：ModuleProtocol_Packet_BackNotify
函数功能：后台服务通知协议
 参数.一：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出打好包的缓冲区
 参数.二：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出缓冲区大小
 参数.三：nCode
  In/Out：In
  类型：整数型
  可空：N
  意思：输入返回的值
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Packet_BackNotify(XCHAR* ptszMSGBuffer, int* pInt_MSGLen, int nCode, int nOPerator, LPCXSTR lpszSourceStr, LPCXSTR lpszDestStr, LPCXSTR lpszAPIStr);
/************************************************************************/
/*                         导出的协议解析函数                           */
/************************************************************************/
/********************************************************************
函数名称：ModuleProtocol_Parse_IDCard
函数功能：ID身份证号码解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的身份证
 参数.二：pSt_IDInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出ID身份证编码信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_IDCard(LPCXSTR lpszMsgBuffer, XENGINE_IDCARDINFO* pSt_IDInfo);
/********************************************************************
函数名称：ModuleProtocol_Parse_Bank
函数功能：银行卡解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的内容
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入解析大小
 参数.三：pSt_BankInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析好的内容
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_Bank(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_BANKINFO* pSt_BankInfo);
/********************************************************************
函数名称：ModuleProtocol_Parse_Translation
函数功能：翻译解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的内容
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入解析大小
 参数.三：pSt_LanguageInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析好的内容
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_Translation(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_LANGUAGEINFO* pSt_LanguageInfo);
/********************************************************************
函数名称：ModuleProtocol_Parse_P2PClient
函数功能：P2P客户端请求解析函数
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pSt_P2XPPeer
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析后的节点信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_P2PClient(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_P2XPPEER_PROTOCOL * pSt_P2XPPeer);
/********************************************************************
函数名称：ModuleProtocol_Parse_ZIPCode
函数功能：解析邮政地址信息
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pSt_ZIPInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析后的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_ZIPCode(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_ZIPINFO* pSt_ZIPInfo);
/********************************************************************
函数名称：ModuleProtocol_Parse_XLog
函数功能：解析日志信息
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入数据大小
 参数.三：pSt_XLogInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析的日志信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_XLog(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_XLOGINFO* pSt_XLogInfo);
/********************************************************************
函数名称：ModuleProtocol_Parse_QRCode
函数功能：二维码协议解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入数据大小
 参数.三：pSt_QRCode
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_QRCode(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_QRCODE* pSt_QRCode);
/********************************************************************
函数名称：ModuleProtocol_Parse_SocketTest
函数功能：套接字测试协议解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：pSt_SocketTest
 参数.三：pSt_QRCode
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_SocketTest(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_SOCKETTEST* pSt_SocketTest);
/********************************************************************
函数名称：ModuleProtocol_Parse_ShortLink
函数功能：短连接协议解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：pSt_SocketTest
 参数.三：pSt_ShortLink
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析好的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_ShortLink(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_SHORTLINK* pSt_ShortLink);
/********************************************************************
函数名称：ModuleProtocol_Parse_WordFilter
函数功能：敏感词协议解析
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：要解析的大小
 参数.三：pSt_ShortLink
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析好的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_WordFilter(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_WORDFILTER* pSt_WordFilter);
/********************************************************************
函数名称：ModuleProtocol_Parse_BackService
函数功能：后台控制协议
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：要解析的大小
 参数.三：ptszSrcBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出解析好的信息
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出解析好的信息
 参数.五：ptszAPIBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出反驳地址
 参数.六：pInt_BSType
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出解析好的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：输出的内容具体参考协议文档
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_BackService(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR* ptszSrcBuffer = NULL, XCHAR* ptszDstBuffer = NULL, XCHAR* ptszAPIBuffer = NULL, int* pInt_BSType = NULL);
/********************************************************************
函数名称：ModuleProtocol_Parse_Verifcation
函数功能：解析验证协议
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：要解析的大小
 参数.三：ptszUserName
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出解析好的信息
 参数.四：ptszUserPass
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出解析好的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_Verifcation(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR* ptszUserName, XCHAR* ptszUserPass);
/********************************************************************
函数名称：ModuleProtocol_Parse_Deamon
函数功能：守护进程协议
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的数据
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：要解析的大小
 参数.三：ptszAPPName
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出进程名称
 参数.四：ptszAPPPath
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出进程路径
 参数.五：pInt_Retime
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出重试次数
 参数.六：pInt_ReNumber
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出重启次数
 参数.七：pbEnable
  In/Out：Out
  类型：逻辑型指针
  可空：N
  意思：输出是否启用
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_Deamon(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR* ptszAPPName, XCHAR* ptszAPPPath, int* pInt_Retime, int* pInt_ReNumber, bool* pbEnable);
/********************************************************************
函数名称：ModuleProtocol_Parse_Weather
函数功能：解析天气信息
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pSt_WeatherInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析后的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_Weather(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_WEATHERINFO* pSt_WeatherInfo);
/********************************************************************
函数名称：ModuleProtocol_Parse_Machine
函数功能：解析机器信息收集协议
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pSt_MachineInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析后的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_Machine(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_MACHINEINFO* pSt_MachineInfo);
/********************************************************************
函数名称：ModuleProtocol_Parse_Oil
函数功能：解析油价协议
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pSt_OilInfo
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出解析后的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleProtocol_Parse_Oil(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_OILINFO* pSt_OilInfo);