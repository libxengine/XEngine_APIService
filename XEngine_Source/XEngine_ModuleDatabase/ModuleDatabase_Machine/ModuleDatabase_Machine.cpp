#include "pch.h"
#include "ModuleDatabase_Machine.h"
/********************************************************************
//    Created:     2024/04/07  10:37:48
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Machine\ModuleDatabase_Machine.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleDatabase\ModuleDatabase_Machine
//    File Base:   ModuleDatabase_Machine
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     机器信息收集数据库
//    History:
*********************************************************************/
CModuleDatabase_Machine::CModuleDatabase_Machine()
{
}
CModuleDatabase_Machine::~CModuleDatabase_Machine()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleDatabase_Machine_Init
函数功能：初始化数据库
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
bool CModuleDatabase_Machine::ModuleDatabase_Machine_Init(DATABASE_MYSQL_CONNECTINFO* pSt_DBConnector)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_DBConnector)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	//连接数据库
	_tcsxcpy(pSt_DBConnector->tszDBName, _X("XEngine_APIMachine"));
	if (!DataBase_MySQL_Connect(&xhDBSQL, pSt_DBConnector))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_Machine_Destory
函数功能：销毁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_Machine::ModuleDatabase_Machine_Destory()
{
	DBModule_IsErrorOccur = false;

	DataBase_MySQL_Close(xhDBSQL);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_Machine_Insert
函数功能：插入一条信息到数据库中
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
bool CModuleDatabase_Machine::ModuleDatabase_Machine_Insert(XENGINE_MACHINEINFO* pSt_MachineInfo)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_MachineInfo)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[4096];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("INSERT INTO `XEngine_MachineList` (tszMachineName,tszMachineCode,tszMachineSystem,tszMachineText,nTimeNumber,tszCreateTime) VALUES('%s','%s','%s','%s',%lld,now())"), pSt_MachineInfo->tszMachineName, pSt_MachineInfo->tszMachineCode, pSt_MachineInfo->tszMachineSystem, pSt_MachineInfo->tszMachineText, pSt_MachineInfo->nTimeNumber);
#ifdef _MSC_BUILD
	XCHAR tszUTFStr[4096] = {};
	int nSLen = _tcsxlen(tszSQLStatement);
	BaseLib_OperatorCharset_AnsiToUTF(tszSQLStatement, tszUTFStr, &nSLen);
	if (!DataBase_MySQL_Execute(xhDBSQL, tszUTFStr))
#else
	if (!DataBase_MySQL_Execute(xhDBSQL, tszSQLStatement))
#endif
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_Machine_Query
函数功能：查询数据
 参数.一：pSt_SLinkInfo
  In/Out：In/Out
  类型：数据结构指针
  可空：N
  意思：输入查询的信息,输出完整的信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_Machine::ModuleDatabase_Machine_Query(XENGINE_MACHINEINFO* pSt_MachineInfo)
{
	DBModule_IsErrorOccur = false;

	if ((NULL == pSt_MachineInfo))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	//查询
	XNETHANDLE xhTable = 0;
	__int64u nllLine = 0;
	__int64u nllRow = 0;

	XCHAR tszSQLStatement[1024];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("SELECT * FROM `XEngine_MachineList` WHERE tszMachineCode = '%s'"), pSt_MachineInfo->tszMachineCode);
	if (!DataBase_MySQL_ExecuteQuery(xhDBSQL, &xhTable, tszSQLStatement, &nllLine, &nllRow))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	if (nllLine <= 0)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_NOTFOUND;
		return false;
	}
	for (__int64u i = 0; i < nllLine; i++)
	{
		XCHAR** pptszResult = DataBase_MySQL_GetResult(xhDBSQL, xhTable);

		if (NULL != pptszResult[0])
		{
			pSt_MachineInfo->nID = _ttxoi(pptszResult[0]);
		}
		if (NULL != pptszResult[1])
		{
			_tcsxcpy(pSt_MachineInfo->tszMachineName, pptszResult[1]);
		}
		if (NULL != pptszResult[2])
		{
			_tcsxcpy(pSt_MachineInfo->tszMachineCode, pptszResult[2]);
		}
		if (NULL != pptszResult[3])
		{
			_tcsxcpy(pSt_MachineInfo->tszMachineSystem, pptszResult[3]);
		}
		if (NULL != pptszResult[4])
		{
			_tcsxcpy(pSt_MachineInfo->tszMachineText, pptszResult[4]);
		}
		if (NULL != pptszResult[5])
		{
			pSt_MachineInfo->nTimeNumber = _ttxoll(pptszResult[5]);
		}
		if (NULL != pptszResult[6])
		{
			_tcsxcpy(pSt_MachineInfo->tszCreateTime, pptszResult[6]);
		}
	}
	DataBase_MySQL_FreeResult(xhDBSQL, xhTable);
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_Machine_Delete
函数功能：删除数据
 参数.一：pSt_SLinkInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要删除的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_Machine::ModuleDatabase_Machine_Delete(XENGINE_MACHINEINFO* pSt_MachineInfo)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_MachineInfo)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[1024];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	if (_tcsxlen(pSt_MachineInfo->tszMachineCode) > 0)
	{
		_xstprintf(tszSQLStatement, _X("DELETE FROM `XEngine_MachineList` WHERE tszMachineCode = '%s'"), pSt_MachineInfo->tszMachineCode);
	}
	else
	{
		_xstprintf(tszSQLStatement, _X("DELETE FROM `XEngine_MachineList` WHERE tszMachineName = '%s'"), pSt_MachineInfo->tszMachineName);
	}
	
	if (!DataBase_MySQL_Execute(xhDBSQL, tszSQLStatement))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}
/********************************************************************
函数名称：ModuleDatabase_Machine_UPDate
函数功能：更新数据
 参数.一：pSt_SLinkInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：输入要更新的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleDatabase_Machine::ModuleDatabase_Machine_UPDate(XENGINE_MACHINEINFO* pSt_MachineInfo)
{
	DBModule_IsErrorOccur = false;

	if (NULL == pSt_MachineInfo)
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = ERROR_APISERVICE_MODULE_DATABASE_PARAMENT;
		return false;
	}
	XCHAR tszSQLStatement[1024];
	memset(tszSQLStatement, '\0', sizeof(tszSQLStatement));

	_xstprintf(tszSQLStatement, _X("UPDATE `XEngine_MachineList` SET nTimeNumber = %lld WHERE tszMachineCode = '%s'"), pSt_MachineInfo->nTimeNumber, pSt_MachineInfo->tszMachineCode);

	if (!DataBase_MySQL_Execute(xhDBSQL, tszSQLStatement))
	{
		DBModule_IsErrorOccur = true;
		DBModule_dwErrorCode = DataBase_GetLastError();
		return false;
	}
	return true;
}