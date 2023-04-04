#include "pch.h"
#include "ModuleHelp_Locker.h"
/********************************************************************
//    Created:     2022/08/15  16:11:12
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Locker\ModuleHelp_Locker.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Locker
//    File Base:   ModuleHelp_Locker
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     分布式锁
//    History:
*********************************************************************/
CModuleHelp_Locker::CModuleHelp_Locker()
{
}
CModuleHelp_Locker::~CModuleHelp_Locker()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleHelp_Locker_Create
函数功能：创建锁
 参数.一：pxhToken
  In/Out：Out
  类型：句柄
  可空：N
  意思：输出创建的锁句柄,并且会打开这个锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleHelp_Locker::ModuleHelp_Locker_Create(XNETHANDLE* pxhToken)
{
	ModuleHelp_IsErrorOccur = FALSE;

	if (NULL == pxhToken)
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_PARAMENT;
		return FALSE;
	}
	MODULEHELP_LOCKINFO *pSt_LockInfo = new MODULEHELP_LOCKINFO;
	if (NULL == pSt_LockInfo)
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_MALLOC;
		return FALSE;
	}
	pSt_LockInfo->enLockStatus = ENUM_MODULEHELP_LOCKSTATUS_NOTUSED;

	BaseLib_OperatorHandle_Create(pxhToken);

	st_Locker.lock();
	stl_MapLocker.insert(make_pair(*pxhToken, pSt_LockInfo));
	st_Locker.unlock();
	return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_Locker_OPen
函数功能：打开一个锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleHelp_Locker::ModuleHelp_Locker_OPen(XNETHANDLE xhToken)
{
	ModuleHelp_IsErrorOccur = FALSE;

	//看看存在不存在
	st_Locker.lock_shared();
	auto stl_MapIterator = stl_MapLocker.find(xhToken);
	if (stl_MapIterator != stl_MapLocker.end())
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_EXIST;
		st_Locker.unlock_shared();
		return FALSE;
	}
	st_Locker.unlock_shared();
	//不存在插入
	MODULEHELP_LOCKINFO* pSt_LockInfo = new MODULEHELP_LOCKINFO;
	if (NULL == pSt_LockInfo)
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_MALLOC;
		return FALSE;
	}
	pSt_LockInfo->enLockStatus = ENUM_MODULEHELP_LOCKSTATUS_NOTUSED;

	st_Locker.lock();
	stl_MapLocker.insert(make_pair(xhToken, pSt_LockInfo));
	st_Locker.unlock();
	return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_Locker_ReadLock
函数功能：读加锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleHelp_Locker::ModuleHelp_Locker_ReadLock(XNETHANDLE xhToken)
{
	ModuleHelp_IsErrorOccur = FALSE;

	//看看存在不存在
	st_Locker.lock_shared();
	auto stl_MapIterator = stl_MapLocker.find(xhToken);
	if (stl_MapIterator == stl_MapLocker.end())
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_NOTFOUND;
		st_Locker.unlock_shared();
		return FALSE;
	}
	//判断锁状态,如果是写,返回错误
	if (ENUM_MODULEHELP_LOCKSTATUS_WRITE == stl_MapIterator->second->enLockStatus)
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_LOCKED;
		st_Locker.unlock_shared();
		return FALSE;
	}
	//没有加锁,开始加锁
	stl_MapIterator->second->enLockStatus = ENUM_MODULEHELP_LOCKSTATUS_READ;

	st_Locker.unlock_shared();
	return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_Locker_ReadUNLock
函数功能：读解锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleHelp_Locker::ModuleHelp_Locker_ReadUNLock(XNETHANDLE xhToken)
{
	ModuleHelp_IsErrorOccur = FALSE;

	//看看存在不存在
	st_Locker.lock_shared();
	auto stl_MapIterator = stl_MapLocker.find(xhToken);
	if (stl_MapIterator == stl_MapLocker.end())
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_NOTFOUND;
		st_Locker.unlock_shared();
		return FALSE;
	}
	//是不是READ锁定,不是返回错误
	if (ENUM_MODULEHELP_LOCKSTATUS_READ != stl_MapIterator->second->enLockStatus)
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_STATUS;
		st_Locker.unlock_shared();
		return FALSE;
	}
	stl_MapIterator->second->enLockStatus = ENUM_MODULEHELP_LOCKSTATUS_NOTUSED;

	st_Locker.unlock_shared();
	return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_Locker_WriteLock
函数功能：写加锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleHelp_Locker::ModuleHelp_Locker_WriteLock(XNETHANDLE xhToken)
{
	ModuleHelp_IsErrorOccur = FALSE;

	//看看存在不存在
	st_Locker.lock_shared();
	auto stl_MapIterator = stl_MapLocker.find(xhToken);
	if (stl_MapIterator == stl_MapLocker.end())
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_NOTFOUND;
		st_Locker.unlock_shared();
		return FALSE;
	}
	//有没有锁定状态
	if ((ENUM_MODULEHELP_LOCKSTATUS_READ == stl_MapIterator->second->enLockStatus) || (ENUM_MODULEHELP_LOCKSTATUS_WRITE == stl_MapIterator->second->enLockStatus))
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_LOCKED;
		st_Locker.unlock_shared();
		return FALSE;
	}
	stl_MapIterator->second->enLockStatus = ENUM_MODULEHELP_LOCKSTATUS_WRITE;

	st_Locker.unlock_shared();
	return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_Locker_WriteUNLock
函数功能：写解锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleHelp_Locker::ModuleHelp_Locker_WriteUNLock(XNETHANDLE xhToken)
{
	ModuleHelp_IsErrorOccur = FALSE;

	//看看存在不存在
	st_Locker.lock_shared();
	auto stl_MapIterator = stl_MapLocker.find(xhToken);
	if (stl_MapIterator == stl_MapLocker.end())
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_NOTFOUND;
		st_Locker.unlock_shared();
		return FALSE;
	}
	//有没有锁定状态
	if (ENUM_MODULEHELP_LOCKSTATUS_WRITE == stl_MapIterator->second->enLockStatus)
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_LOCK_STATUS;
		st_Locker.unlock_shared();
		return FALSE;
	}
	stl_MapIterator->second->enLockStatus = ENUM_MODULEHELP_LOCKSTATUS_NOTUSED;

	st_Locker.unlock_shared();
	return TRUE;
}
/********************************************************************
函数名称：ModuleHelp_Locker_Close
函数功能：关闭锁
 参数.一：xhToken
  In/Out：In
  类型：锁句柄
  可空：N
  意思：输入要操作的锁
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
XBOOL CModuleHelp_Locker::ModuleHelp_Locker_Close(XNETHANDLE xhToken)
{
	ModuleHelp_IsErrorOccur = FALSE;

	//看看存在不存在
	st_Locker.lock();
	unordered_map<XNETHANDLE, MODULEHELP_LOCKINFO*>::iterator stl_MapIterator = stl_MapLocker.find(xhToken);
	if (stl_MapIterator != stl_MapLocker.end())
	{
		delete stl_MapIterator->second;
		stl_MapIterator->second = NULL;
		stl_MapLocker.erase(stl_MapIterator);
	}
	st_Locker.unlock();
	return TRUE;
}