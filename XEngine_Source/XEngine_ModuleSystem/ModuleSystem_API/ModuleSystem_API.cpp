#include "pch.h"
#include "ModuleSystem_API.h"
/********************************************************************
//    Created:     2023/09/06  13:50:15
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem\ModuleSystem_API\ModuleSystem_API.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleSystem\ModuleSystem_API
//    File Base:   ModuleSystem_API
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     系统API函数库
//    History:
*********************************************************************/
CModuleSystem_API::CModuleSystem_API()
{

}
CModuleSystem_API::~CModuleSystem_API()
{

}
//////////////////////////////////////////////////////////////////////////
//                        公用函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleSystem_API_AutoStart
函数功能：注册自动启动与服务函数
 参数.一：bIsAuto
  In/Out：In
  类型：逻辑型
  可空：Y
  意思：是否让其自动启动，默认为真，自动启动
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleSystem_API::ModuleSystem_API_AutoStart(bool bIsAuto /* = true */)
{
	ModuleSystem_IsErrorOccur = false;

#ifdef _MSC_BUILD
	if (bIsAuto)
	{
		IShellLinkA* pSt_ILink = NULL;      //IShellLink对象指针
		IPersistFile* pSt_IFile = NULL;    //IPersisFil对象指针
		//创建IShellLink对象
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
		HRESULT hResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pSt_ILink);
		if (FAILED(hResult))
		{
			ModuleSystem_IsErrorOccur = true;
			ModuleSystem_dwErrorCode = ERROR_MODULE_SYSTEM_API_COINIT;
			return false;
		}
		//从IShellLink对象中获取IPersistFile接口
		hResult = pSt_ILink->QueryInterface(IID_IPersistFile, (void**)&pSt_IFile);
		if (FAILED(hResult))
		{
			ModuleSystem_IsErrorOccur = true;
			ModuleSystem_dwErrorCode = ERROR_MODULE_SYSTEM_API_QUERY;
			return false;
		}

		XCHAR tszFilePath[MAX_PATH];
		XCHAR tszFileName[MAX_PATH];

		memset(tszFilePath, '\0', MAX_PATH);
		memset(tszFileName, '\0', MAX_PATH);

		GetCurrentDirectoryA(MAX_PATH, tszFilePath);
		GetModuleFileNameA(NULL, tszFileName, MAX_PATH);
		//目标
		pSt_ILink->SetPath(tszFileName);
		//工作目录
		pSt_ILink->SetWorkingDirectory(tszFilePath);
		//备注
		pSt_ILink->SetDescription(_X("XDeamon systemd service"));
		//显示方式
		pSt_ILink->SetShowCmd(SW_SHOW);
		//保存快捷方式到指定目录下

		XCHAR tszAFile[MAX_PATH];
		WCHAR tszUFile[MAX_PATH];

		memset(tszAFile, '\0', sizeof(tszAFile));
		memset(tszUFile, '\0', sizeof(tszUFile));

		if (S_OK != SHGetFolderPathA(NULL, CSIDL_STARTUP, NULL, 0, tszAFile))
		{
			ModuleSystem_IsErrorOccur = true;
			ModuleSystem_dwErrorCode = ERROR_MODULE_SYSTEM_API_GETFILENAME;
			return false;
		}
		_tcsxcat(tszAFile, _X("\\XEngine_DeamonApp.lnk"));
		BaseLib_Charset_AnsiToUnicode(tszAFile, tszUFile);

		hResult = pSt_IFile->Save(tszUFile, TRUE);
		if (FAILED(hResult))
		{
			ModuleSystem_IsErrorOccur = true;
			ModuleSystem_dwErrorCode = ERROR_MODULE_SYSTEM_API_SYSENABLE;
			return false;
		}
		pSt_IFile->Release();
		pSt_ILink->Release();
		CoUninitialize();
	}
	else
	{
		XCHAR tszAFile[MAX_PATH];
		memset(tszAFile, '\0', sizeof(tszAFile));

		if (S_OK != SHGetFolderPathA(NULL, CSIDL_STARTUP, NULL, 0, tszAFile))
		{
			ModuleSystem_IsErrorOccur = true;
			ModuleSystem_dwErrorCode = ERROR_MODULE_SYSTEM_API_SYSDISABLE;
			return false;
		}
		_tcsxcat(tszAFile, _X("\\XEngine_DeamonApp.lnk"));
		_xtremove(tszAFile);
	}
#elif __linux__
	LPCXSTR lpszStartStr = _X("/usr/lib/systemd/system/xdeamon.service");
	if (bIsAuto)
	{
		if (0 != _xtaccess(lpszStartStr, F_OK))
		{
			XCHAR tszMsgBuffer[2048];
			XCHAR tszFileDir[MAX_PATH];

			memset(tszMsgBuffer, '\0', sizeof(tszMsgBuffer));
			memset(tszFileDir, '\0', sizeof(tszFileDir));

			SystemApi_Process_GetPath(tszFileDir);

			int nRet = _xstprintf(tszMsgBuffer, _X("# XDeamon systemd service file\n"
				"\n"
				"[Unit]\n"
				"Description=XEngine XDeamon Service\n"
				"Documentation=http://www.xyry.org\n"
				"After=network.target\n"
				"\n"
				"[Install]\n"
				"WantedBy=multi-user.target\n"
				"\n"
				"[Service]\n"
				"Type=forking\n"
				"PIDFile=xdeamon.pid\n"
				"ExecStart=%s\n"
				"ExecStop=kill -s QUIT $MAINPID\n"), tszFileDir);

			if (!SystemApi_File_SaveBuffToFile(lpszStartStr, tszMsgBuffer, nRet))
			{
				return false;
			}
		}
		XCHAR tszServiceStr[MAX_PATH];
		memset(tszServiceStr, '\0', MAX_PATH);

		_xstprintf(tszServiceStr, _X("sudo systemctl enable xdeamon"));
		if (-1 == system(tszServiceStr))
		{
			ModuleSystem_IsErrorOccur = true;
			ModuleSystem_dwErrorCode = ERROR_MODULE_SYSTEM_API_SYSENABLE;
			return false;
		}
	}
	else
	{
		XCHAR tszServiceStr[MAX_PATH];
		memset(tszServiceStr, '\0', MAX_PATH);

		_xstprintf(tszServiceStr, _X("systemctl disable xdeamon"));
		if (-1 == system(tszServiceStr))
		{
			ModuleSystem_IsErrorOccur = true;
			ModuleSystem_dwErrorCode = ERROR_MODULE_SYSTEM_API_SYSDISABLE;
			return false;
		}
		_xtremove(lpszStartStr);
	}
#endif
	return true;
}