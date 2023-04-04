#pragma once
/********************************************************************
//    Created:     2022/08/15  16:04:28
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Locker\ModuleHelp_Locker.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Locker
//    File Base:   ModuleHelp_Locker
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     分布式锁
//    History:
*********************************************************************/
//锁状态
typedef enum
{
	ENUM_MODULEHELP_LOCKSTATUS_NOTUSED = 0,
	ENUM_MODULEHELP_LOCKSTATUS_READ = 1,
	ENUM_MODULEHELP_LOCKSTATUS_WRITE = 1,
}MODULEHELP_LOCKSTATUS;
//锁属性
typedef struct  
{
	atomic<MODULEHELP_LOCKSTATUS> enLockStatus;
}MODULEHELP_LOCKINFO;

class CModuleHelp_Locker
{
public:
	CModuleHelp_Locker();
	~CModuleHelp_Locker();
public:
	XBOOL ModuleHelp_Locker_Create(XNETHANDLE* pxhToken);
	XBOOL ModuleHelp_Locker_OPen(XNETHANDLE xhToken);
	XBOOL ModuleHelp_Locker_ReadLock(XNETHANDLE xhToken);
	XBOOL ModuleHelp_Locker_ReadUNLock(XNETHANDLE xhToken);
	XBOOL ModuleHelp_Locker_WriteLock(XNETHANDLE xhToken);
	XBOOL ModuleHelp_Locker_WriteUNLock(XNETHANDLE xhToken);
	XBOOL ModuleHelp_Locker_Close(XNETHANDLE xhToken);
private:
	shared_mutex st_Locker;
private:
	unordered_map<XNETHANDLE, MODULEHELP_LOCKINFO*> stl_MapLocker;
};