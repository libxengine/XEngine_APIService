#include "pch.h"
#include "ModuleHelp_ImageGet.h"
/********************************************************************
//    Created:     2023/08/11  15:16:20
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Image\ModuleHelp_ImageGet.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Image
//    File Base:   ModuleHelp_ImageGet
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     图像信息获取处理库
//    History:
*********************************************************************/
CModuleHelp_ImageGet::CModuleHelp_ImageGet()
{
}
CModuleHelp_ImageGet::~CModuleHelp_ImageGet()
{
}
//////////////////////////////////////////////////////////////////////////
//                        公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleHelp_ImageGet_Attr
函数功能：获取图像属性
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入图像内存
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入图像大小
 参数.三：pSt_BaseInfo
  In/Out：Out
  类型：数据结构指针
  可空：Y
  意思：输出图像基本信息
 参数.四：pSt_ExtAttr
  In/Out：Out
  类型：数据结构指针
  可空：Y
  意思：输出图像扩展信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_ImageGet::ModuleHelp_ImageGet_Attr(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_IMGBASEATTR* pSt_BaseInfo /* = NULL */, XENGINE_IMGEXTATTR* pSt_ExtAttr /* = NULL */)
{
	ModuleHelp_IsErrorOccur = false;

	if (NULL == lpszMsgBuffer)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_PARAMRT;
		return false;
	}
	//读取到内存
	cv::_InputArray m_InputArray(lpszMsgBuffer, nMsgLen);
	cv::Mat m_Frame = cv::imdecode(m_InputArray, cv::IMREAD_UNCHANGED);

	if (m_Frame.empty())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_OPEN;
		return false;
	}
	//获取信息
	if (NULL != pSt_BaseInfo)
	{
		pSt_BaseInfo->nWidth = m_Frame.rows;
		pSt_BaseInfo->nHeigth = m_Frame.cols;
		pSt_BaseInfo->nChannel = m_Frame.channels();
	}
	//获取其他信息
	if (NULL != pSt_ExtAttr)
	{
		pSt_ExtAttr->nItem = m_Frame.elemSize();
		pSt_ExtAttr->nDepth = m_Frame.depth();
		pSt_ExtAttr->nType = m_Frame.type();
	}
	return true;
}