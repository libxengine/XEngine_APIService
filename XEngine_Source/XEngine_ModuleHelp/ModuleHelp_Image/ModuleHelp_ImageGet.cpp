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
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
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
		pSt_BaseInfo->nWidth = m_Frame.cols;
		pSt_BaseInfo->nHeigth = m_Frame.rows;
		pSt_BaseInfo->nChannel = m_Frame.channels();
	}
	//获取其他信息
	if (NULL != pSt_ExtAttr)
	{
		pSt_ExtAttr->nItem = m_Frame.elemSize();
		pSt_ExtAttr->nDepth = m_Frame.depth();
		pSt_ExtAttr->nType = m_Frame.type();
	}
#else
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_NOTSUPPORT;
	return false;
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_ImageGet_TextInit
函数功能：初始化图像文字转换
 参数.一：lpszPath
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入文本语言数据路径
 参数.二：lpszLanguage
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入加载的语言数据.通过+连接
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_ImageGet::ModuleHelp_ImageGet_TextInit(LPCXSTR lpszPath, LPCXSTR lpszLanguage)
{
	ModuleHelp_IsErrorOccur = false;

	if ((NULL == lpszPath) || (NULL == lpszLanguage))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_PARAMRT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	// 初始化 Tesseract API
	pSt_APITesseract = TessBaseAPICreate();
	if (NULL == pSt_APITesseract)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_CRAETE;
		return false;
	}
	if (0 != TessBaseAPIInit3(pSt_APITesseract, lpszPath, lpszLanguage))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_INIT;
		TessBaseAPIDelete(pSt_APITesseract);
		return false;
	}
#else
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_NOTSUPPORT;
	return false;
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_ImageGet_TextGet
函数功能：获取图像文本内容
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
 参数.三：ppptszListStr
  In/Out：Out
  类型：三级指针
  可空：N
  意思：输出获取到的内容列表
 参数.四：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出列表个数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_ImageGet::ModuleHelp_ImageGet_TextGet(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR*** ppptszListStr, int* pInt_ListCount)
{
	ModuleHelp_IsErrorOccur = false;

	if (NULL == lpszMsgBuffer)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_PARAMRT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	// 加载图片
	Pix* pSt_PIXImage = pixReadMem((const l_uint8*)lpszMsgBuffer, nMsgLen);
	if (NULL == pSt_PIXImage)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_READ;
		return false;
	}
	// 设置图像到 Tesseract
	TessBaseAPISetImage2(pSt_APITesseract, pSt_PIXImage);

	list<xstring> stl_ListStr;
	// 执行 OCR
	char* ptszOStr = TessBaseAPIGetUTF8Text(pSt_APITesseract);
	if (NULL == ptszOStr) 
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_GET;
		return false;
	}
	XCHAR tszUTFBuffer[8192] = {};
	_tcsxcpy(tszUTFBuffer, ptszOStr);
	TessDeleteText(ptszOStr);

	XCHAR* ptszTmpStr = NULL;
	XCHAR* ptszTokStr = _tcsxtok_s(tszUTFBuffer, _X("\n"), &ptszTmpStr);
	while (NULL != ptszTokStr)
	{
		stl_ListStr.push_back(ptszTokStr);
		ptszTokStr = _tcsxtok_s(NULL, _X("\n"), &ptszTmpStr);
	}

	*pInt_ListCount = stl_ListStr.size();
	BaseLib_Memory_Malloc((XPPPMEM)ppptszListStr, *pInt_ListCount, XPATH_MAX);

	auto stl_ListIterator = stl_ListStr.begin();
	for (int i = 0; stl_ListIterator != stl_ListStr.end(); i++, stl_ListIterator++)
	{
#ifdef _MSC_BUILD
		XCHAR tszGBKBuffer[2048] = {};
		_tcsxcpy((*ppptszListStr)[i], BaseLib_Charset_UTFToAnsi(stl_ListIterator->c_str(), tszGBKBuffer));
#else
		_tcsxcpy((*ppptszListStr)[i], stl_ListIterator->c_str());
#endif
	}
	// 释放资源
	pixDestroy(&pSt_PIXImage);
#else
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_NOTSUPPORT;
	return false;
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_ImageGet_TextDestory
函数功能：销毁文本提取功能
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_ImageGet::ModuleHelp_ImageGet_TextDestory()
{
	ModuleHelp_IsErrorOccur = false;

#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	TessBaseAPIDelete(pSt_APITesseract);
#else
ModuleHelp_IsErrorOccur = true;
ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_NOTSUPPORT;
return false;
#endif
	return true;
}