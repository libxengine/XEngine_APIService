#pragma once
/********************************************************************
//    Created:     2022/02/28  10:16:15
//    File Name:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleDatabase\ModuleDB_Define.h
//    File Path:   D:\XEngine_IPInfo\XEngine_Source\XEngine_ModuleDatabase
//    File Base:   ModuleDB_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     数据库操作导出
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
///                        导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleDB_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                         导出的身份证地址操作函数                     */
/************************************************************************/
/********************************************************************
函数名称：ModuleDatabase_IDCard_Init
函数功能：初始化SQLITE文件系统
 参数.一：pSt_DBConnector
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的数据库
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_IDCard_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector);
/********************************************************************
函数名称：ModuleDatabase_IDCard_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_IDCard_Destory();
/********************************************************************
函数名称：ModuleDatabase_IDCard_QueryRegion
函数功能：查询身份证位置信息
 参数.一：pSt_IDRegion
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出查询到的位置信息
 参数.二：pSt_IDInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要查询的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_IDCard_QueryRegion(XENGINE_IDREGION * pSt_IDRegion, XENGINE_IDCARDINFO * pSt_IDInfo);
/********************************************************************
函数名称：ModuleDatabase_IDCard_QueryByAddr
函数功能：查询地址对应的区域ID
 参数.一：pSt_IDRegion
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出查询到的位置信息
 参数.二：pInt_IDNumber
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出对应ID
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_IDCard_QueryByAddr(XENGINE_IDREGION* pSt_IDRegion, int* pInt_IDNumber);
/************************************************************************/
/*                         导出的银行卡信息函数                         */
/************************************************************************/
/********************************************************************
函数名称：ModuleDatabase_Bank_Init
函数功能：初始化SQLITE文件系统
 参数.一：pSt_DBConnector
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的数据库
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_Bank_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector);
/********************************************************************
函数名称：ModuleDatabase_Bank_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_Bank_Destory();
/********************************************************************
函数名称：ModuleDatabase_Bank_Query
函数功能：通过银行缩写获得银行名称
 参数.一：pSt_BankInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的名称,输出银行名称
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_Bank_Query(XENGINE_BANKINFO * pSt_BankInfo);
/************************************************************************/
/*                         导出的邮编行政信息函数                       */
/************************************************************************/
/********************************************************************
函数名称：ModuleDatabase_ZIPCode_Init
函数功能：初始化数据库
 参数.一：pSt_DBConnector
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的数据库
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_ZIPCode_Init(DATABASE_MYSQL_CONNECTINFO * pSt_DBConnector);
/********************************************************************
函数名称：ModuleDatabase_ZIPCode_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_ZIPCode_Destory();
/********************************************************************
函数名称：ModuleDatabase_ZIPCode_QueryZIPCode
函数功能：通过邮编查询行政地址信息
 参数.一：pSt_ZIPInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的邮编,输出查询到的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_ZIPCode_QueryZIPCode(XENGINE_ZIPINFO* pSt_ZIPInfo);
/********************************************************************
函数名称：ModuleDatabase_ZIPCode_QueryName
函数功能：通过行政名称查询内容
 参数.一：pSt_ZIPInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的信息,输出查询到的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_ZIPCode_QueryName(XENGINE_ZIPINFO* pSt_ZIPInfo);
/************************************************************************/
/*                         导出的日志服务数据库函数                     */
/************************************************************************/
/********************************************************************
函数名称：ModuleDatabase_XLog_Init
函数功能：初始化SQLITE文件系统
 参数.一：pSt_DBConnector
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的数据库
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_XLog_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector);
/********************************************************************
函数名称：ModuleDatabase_XLog_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_XLog_Destory();
/********************************************************************
函数名称：ModuleDatabase_XLog_Create
函数功能：创建一个日志服务表
 参数.一：lpszTableName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：创建的名称
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_XLog_Create(LPCXSTR lpszTableName);
/********************************************************************
函数名称：ModuleDatabase_XLog_Insert
函数功能：查询身份证位置信息
 参数.一：pSt_IDRegion
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要插入的日志信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_XLog_Insert(XENGINE_XLOGINFO* pSt_XLogInfo);
/********************************************************************
函数名称：ModuleDatabase_XLog_Query
函数功能：日志信息查询
 参数.一：pppSt_XLogInfo
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出查询到的数据
 参数.二：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出数据个数
 参数.三：lpszTableName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入表名称
 参数.四：lpszTimeStart
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入开始时间
 参数.五：lpszTimeEnd
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入结束时间
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_XLog_Query(XENGINE_XLOGINFO*** pppSt_XLogInfo, int* pInt_ListCount, LPCXSTR lpszTableName, LPCXSTR lpszTimeStart, LPCXSTR lpszTimeEnd);
/********************************************************************
函数名称：ModuleDatabase_XLog_Delete
函数功能：删除日志表
 参数.一：lpszTableName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：删除的名称
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_XLog_Delete(LPCXSTR lpszTableName);
/********************************************************************
函数名称：ModuleDatabase_XLog_Show
函数功能：日志表列举
 参数.一：ppptszList
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出日志数据库里面的表列
 参数.二：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出列个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_XLog_Show(XCHAR*** ppptszList, int* pInt_ListCount);
/************************************************************************/
/*                         导出的短连接数据库函数                       */
/************************************************************************/
/********************************************************************
函数名称：ModuleDatabase_ShortLink_Init
函数功能：初始化SQLITE文件系统
 参数.一：pSt_DBConnector
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：数据数据库信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_ShortLink_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector);
/********************************************************************
函数名称：ModuleDatabase_ShortLink_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_ShortLink_Destory();
/********************************************************************
函数名称：ModuleDatabase_ShortLink_Insert
函数功能：插入一个短连接到数据库中
 参数.一：pSt_SLinkInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要插入的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_ShortLink_Insert(XENGINE_SHORTLINK* pSt_SLinkInfo);
/********************************************************************
函数名称：ModuleDatabase_ShortLink_Query
函数功能：查询短连接
 参数.一：pSt_SLinkInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入查询的短连接,输出完整的连接
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_ShortLink_Query(XENGINE_SHORTLINK* pSt_SLinkInfo);
/********************************************************************
函数名称：ModuleDatabase_ShortLink_Delete
函数功能：删除短连接
 参数.一：pSt_SLinkInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要删除的短连接
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_ShortLink_Delete(XENGINE_SHORTLINK* pSt_SLinkInfo);
/************************************************************************/
/*                         导出的敏感词过滤数据库函数                   */
/************************************************************************/
/********************************************************************
函数名称：ModuleDatabase_WordFilter_Init
函数功能：初始化SQLITE文件系统
 参数.一：pSt_DBConnector
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的数据库
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_WordFilter_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector);
/********************************************************************
函数名称：ModuleDatabase_WordFilter_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_WordFilter_Destory();
/********************************************************************
函数名称：ModuleDatabase_WordFilter_Query
函数功能：获取敏感词系统
 参数.一：pSt_WordFilter
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要查询的词,输出查询到的敏感词
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_WordFilter_Query(XENGINE_WORDFILTER* pSt_WordFilter);
/********************************************************************
函数名称：ModuleDatabase_WordFilter_Insert
函数功能：查询一条敏感词
 参数.一：pSt_WordFilter
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入要操作的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_WordFilter_Insert(XENGINE_WORDFILTER* pSt_WordFilter);
/********************************************************************
函数名称：ModuleDatabase_WordFilter_Delete
函数功能：删除一条敏感词
 参数.一：pSt_WordFilter
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要操作的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" bool ModuleDatabase_WordFilter_Delete(XENGINE_WORDFILTER* pSt_WordFilter);