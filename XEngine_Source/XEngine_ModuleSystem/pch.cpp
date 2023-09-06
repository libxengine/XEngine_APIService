#include "pch.h"
#include "ModuleSystem_API/ModuleSystem_API.h"
/********************************************************************
//    Created:     2023/09/06  13:54:52
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem\pch.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
bool ModuleSystem_IsErrorOccur = false;
XLONG ModuleSystem_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CModuleSystem_API m_ModuleSystem;
//////////////////////////////////////////////////////////////////////////
//                        导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" XLONG ModuleSystem_GetLastError(int* pInt_ErrorCode)
{
	if (NULL != pInt_ErrorCode)
	{
		*pInt_ErrorCode = errno;
	}
	return ModuleSystem_dwErrorCode;
}
/************************************************************************/
/*                        系统函数库                                    */
/************************************************************************/
extern "C" bool ModuleSystem_API_AutoStart(bool bIsAuto /* = true */)
{
	return m_ModuleSystem.ModuleSystem_API_AutoStart(bIsAuto);
}