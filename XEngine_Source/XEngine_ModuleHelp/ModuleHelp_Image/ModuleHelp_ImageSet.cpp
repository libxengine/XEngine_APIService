#include "pch.h"
#include "ModuleHelp_ImageSet.h"
/********************************************************************
//    Created:     2023/08/11  15:18:25
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Image\ModuleHelp_ImageSet.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Image
//    File Base:   ModuleHelp_ImageSet
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     图像修改处理库
//    History:
*********************************************************************/
CModuleHelp_ImageSet::CModuleHelp_ImageSet()
{
}
CModuleHelp_ImageSet::~CModuleHelp_ImageSet()
{
}
//////////////////////////////////////////////////////////////////////////
//                        公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleHelp_ImageSet_Resolution
函数功能：分辨率调整
 参数.一：lpszSrcFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始缓冲区数据
 参数.二：nSLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入原始缓冲区大小
 参数.三：lpszExtFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的图像格式.jpg .png .bmp
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的缓冲区
 参数.五：pInt_DLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出转换后的大小
 参数.六：nWidth
  In/Out：In
  类型：整数型
  可空：N
  意思：输入调整后的宽
 参数.七：nHeight
  In/Out：In
  类型：整数型
  可空：N
  意思：输入调整后的高
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_ImageSet::ModuleHelp_ImageSet_Resolution(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nWidth, int nHeight)
{
	ModuleHelp_IsErrorOccur = false;

	if (NULL == lpszSrcBuffer)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_PARAMRT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	//读取到内存
	cv::_InputArray m_InputArray(lpszSrcBuffer, nSLen);
	cv::Mat m_SrcFrame = cv::imdecode(m_InputArray, cv::IMREAD_UNCHANGED);
	cv::Mat m_DstFrame;

	if (m_SrcFrame.empty())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_OPEN;
		return false;
	}
	//调整分辨率
	cv::resize(m_SrcFrame, m_DstFrame, cv::Size(nWidth, nHeight));

	vector<unsigned char> stl_VectorImage;
	cv::imencode(lpszExtFile, m_DstFrame, stl_VectorImage);

	*pInt_DLen = stl_VectorImage.size();
	memcpy(ptszDstBuffer, stl_VectorImage.data(), stl_VectorImage.size());
#else
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_NOTSUPPORT;
	return false;
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_ImageSet_Flip
函数功能：图像翻转
 参数.一：lpszSrcFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始缓冲区数据
 参数.二：nSLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入原始缓冲区大小
 参数.三：lpszExtFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的图像格式.jpg .png .bmp
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的缓冲区
 参数.五：pInt_DLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出转换后的大小
 参数.六：nOPMethod
  In/Out：In
  类型：整数型
  可空：N
  意思：输入图像翻转方式,0:上下,1:左右,-1:上下左右同时
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_ImageSet::ModuleHelp_ImageSet_Flip(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nOPMethod)
{
	ModuleHelp_IsErrorOccur = false;

	if (NULL == lpszSrcBuffer)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_PARAMRT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	cv::_InputArray m_InputArray(lpszSrcBuffer, nSLen);
	cv::Mat m_SrcFrame = cv::imdecode(m_InputArray, cv::IMREAD_UNCHANGED);
	cv::Mat m_DstFrame;

	if (m_SrcFrame.empty())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_OPEN;
		return false;
	}
	//调整分辨率
	cv::flip(m_SrcFrame, m_DstFrame, nOPMethod);

	vector<unsigned char> stl_VectorImage;
	if (!cv::imencode(lpszExtFile, m_DstFrame, stl_VectorImage))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_WRITE;
		return false;
	}

	*pInt_DLen = stl_VectorImage.size();
	memcpy(ptszDstBuffer, stl_VectorImage.data(), stl_VectorImage.size());
#else
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_NOTSUPPORT;
	return false;
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_ImageSet_ColorCvt
函数功能：色彩空间转换
 参数.一：lpszSrcFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始缓冲区数据
 参数.二：nSLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入原始缓冲区大小
 参数.三：lpszExtFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的图像格式.jpg .png .bmp
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的缓冲区
 参数.五：pInt_DLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出转换后的大小
 参数.六：enColorInfo
  In/Out：In
  类型：整数型
  可空：N
  意思：输入要转换的类型
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_ImageSet::ModuleHelp_ImageSet_ColorCvt(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, ENUM_XENGINE_IMAGE_COLOR_INFO enColorInfo)
{
	ModuleHelp_IsErrorOccur = false;

	if (NULL == lpszSrcBuffer)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_PARAMRT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	cv::_InputArray m_InputArray(lpszSrcBuffer, nSLen);
	cv::Mat m_SrcFrame = cv::imdecode(m_InputArray, cv::IMREAD_UNCHANGED);
	cv::Mat m_DstFrame;

	if (m_SrcFrame.empty())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_OPEN;
		return false;
	}
	cv::cvtColor(m_SrcFrame, m_DstFrame, enColorInfo);
	//写到文件
	vector<unsigned char> stl_VectorImage;
	if (!cv::imencode(lpszExtFile, m_DstFrame, stl_VectorImage))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_WRITE;
		return false;
	}

	*pInt_DLen = stl_VectorImage.size();
	memcpy(ptszDstBuffer, stl_VectorImage.data(), stl_VectorImage.size());
#else
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_NOTSUPPORT;
	return false;
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_ImageSet_Ligth
函数功能：亮度与对比度调整
 参数.一：lpszSrcFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始缓冲区数据
 参数.二：nSLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入原始缓冲区大小
 参数.三：lpszExtFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的图像格式.jpg .png .bmp
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的缓冲区
 参数.五：pInt_DLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出转换后的大小
 参数.六：nGamma
  In/Out：In
  类型：整数型
  可空：N
  意思：输入要调整的值
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_ImageSet::ModuleHelp_ImageSet_Ligth(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nGamma)
{
	ModuleHelp_IsErrorOccur = false;

	if (NULL == lpszSrcBuffer)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_PARAMRT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	cv::_InputArray m_InputArray(lpszSrcBuffer, nSLen);
	cv::Mat m_SrcFrame = cv::imdecode(m_InputArray, cv::IMREAD_UNCHANGED);
	cv::Mat m_DstFrame;

	if (m_SrcFrame.empty())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_OPEN;
		return false;
	}
	//配置
	cv::Mat m_MatScalar = cv::Mat::zeros(m_SrcFrame.size(), m_SrcFrame.type());
	cv::addWeighted(m_SrcFrame, 1.0, m_MatScalar, 0, nGamma, m_DstFrame);
	//写到文件
	vector<unsigned char> stl_VectorImage;
	if (!cv::imencode(lpszExtFile, m_DstFrame, stl_VectorImage))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_WRITE;
		return false;
	}

	*pInt_DLen = stl_VectorImage.size();
	memcpy(ptszDstBuffer, stl_VectorImage.data(), stl_VectorImage.size());
#else
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_NOTSUPPORT;
	return false;
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_ImageSet_Level
函数功能：图像压缩级别调整
 参数.一：lpszSrcFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入原始缓冲区数据
 参数.二：nSLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入原始缓冲区大小
 参数.三：lpszExtFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入转换的图像格式.jpg .png .jpeg .webp
 参数.四：ptszDstBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出转换后的缓冲区
 参数.五：pInt_DLen
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出转换后的大小
 参数.六：nLevel
  In/Out：In
  类型：整数型
  可空：N
  意思：输入压缩后者质量级别.根据类型不同,此值作用不同
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_ImageSet::ModuleHelp_ImageSet_Level(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nLevel)
{
	ModuleHelp_IsErrorOccur = false;

	if (NULL == lpszSrcBuffer)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_PARAMRT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	cv::_InputArray m_InputArray(lpszSrcBuffer, nSLen);
	cv::Mat m_SrcFrame = cv::imdecode(m_InputArray, cv::IMREAD_UNCHANGED);
	cv::Mat m_DstFrame;

	if (m_SrcFrame.empty())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_OPEN;
		return false;
	}
	std::vector<int> stl_ListCompress;

	if (0 == _tcsxnicmp(lpszExtFile, _X(".jpg"), 4) || 0 == _tcsxnicmp(lpszExtFile, _X(".jpeg"), 5))
	{
		stl_ListCompress.push_back(cv::IMWRITE_JPEG_QUALITY);
	}
	else if (0 == _tcsxnicmp(lpszExtFile, _X(".png"), 4))
	{
		stl_ListCompress.push_back(cv::IMWRITE_PNG_COMPRESSION);
	}
	else if (0 == _tcsxnicmp(lpszExtFile, _X(".exr"), 4))
	{
		stl_ListCompress.push_back(cv::IMWRITE_EXR_COMPRESSION);
	}
	else if (0 == _tcsxnicmp(lpszExtFile, _X(".webp"), 5))
	{
		stl_ListCompress.push_back(cv::IMWRITE_WEBP_QUALITY);
	}
	stl_ListCompress.push_back(nLevel);  // 调整压缩质量，范围0-100
	//写到文件
	vector<unsigned char> stl_VectorImage;
	if (!cv::imencode(lpszExtFile, m_DstFrame, stl_VectorImage, stl_ListCompress))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_WRITE;
		return false;
	}

	*pInt_DLen = stl_VectorImage.size();
	memcpy(ptszDstBuffer, stl_VectorImage.data(), stl_VectorImage.size());
#else
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_IAMGE_NOTSUPPORT;
	return false;
#endif
	return true;
}