#include "pch.h"
#include "ModuleHelp_Charset.h"
/********************************************************************
//    Created:     2022/03/23  13:57:16
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Charset\ModuleHelp_Charset.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Charset
//    File Base:   ModuleHelp_Charset
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     字符集转换
//    History:
*********************************************************************/
CModuleHelp_Charset::CModuleHelp_Charset()
{
}
CModuleHelp_Charset::~CModuleHelp_Charset()
{

}
//////////////////////////////////////////////////////////////////////////
//                             公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleHelp_Charset_Convert
函数功能：字体转换
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
BOOL CModuleHelp_Charset::ModuleHelp_Charset_Convert(LPCTSTR lpszJsonFile, LPCTSTR lpszSourceStr, TCHAR* ptszDestStr)
{
	ModuleHelp_IsErrorOccur = FALSE;

	if ((NULL == lpszJsonFile) || (NULL == lpszSourceStr) || (NULL == ptszDestStr))
	{
		ModuleHelp_IsErrorOccur = TRUE;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_CHARSET_PARAMENT;
		return FALSE;
	}
	opencc::SimpleConverter m_Converter(lpszJsonFile);
	m_Converter.Convert(lpszSourceStr, ptszDestStr);

	return TRUE;
}