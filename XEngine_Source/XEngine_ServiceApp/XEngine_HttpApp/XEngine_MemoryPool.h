#pragma once
/********************************************************************
//    Created:     2025/06/24  16:49:26
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp\XEngine_MemoryPool.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp
//    File Base:   XEngine_MemoryPool
//    File Ext:    h
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     内存池封装
//    History:
*********************************************************************/
class CXEngine_MemoryPoolEx
{
public:
	CXEngine_MemoryPoolEx(size_t nSize)
	{
		lPtr = ManagePool_Memory_Alloc(xhMemPool, nSize);
		if (NULL == lPtr)
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ALERT, _X("内存池分配失败，系统面临崩溃!"));
		}
	}
	~CXEngine_MemoryPoolEx()
	{
		if (NULL != lPtr)
		{
			ManagePool_Memory_Free(xhMemPool, lPtr);
		}
	}
public:
	// 支持类型转换
	template<typename T>
	T* as() {
		return static_cast<T*>(lPtr);
	}
	XCHAR* get()
	{
		return static_cast<XCHAR*>(lPtr);
	}
	LPCXSTR tostr()
	{
		return static_cast<LPCXSTR>(lPtr);
	}
private:
	XPVOID lPtr = NULL;
};