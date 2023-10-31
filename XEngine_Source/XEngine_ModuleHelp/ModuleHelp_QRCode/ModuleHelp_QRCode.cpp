#include "pch.h"
#include "ModuleHelp_QRCode.h"
/********************************************************************
//    Created:     2023/01/31  09:38:48
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_QRCode\ModuleHelp_QRCode.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_QRCode
//    File Base:   ModuleHelp_QRCode
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     二维码处理代码
//    History:
*********************************************************************/
CModuleHelp_QRCode::CModuleHelp_QRCode()
{
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
#endif
}
CModuleHelp_QRCode::~CModuleHelp_QRCode()
{
}
//////////////////////////////////////////////////////////////////////////
//                        公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：ModuleHelp_QRCode_QREncodecFile
函数功能：二维码生成器
 参数.一：lpszFileName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要生成的图片位置
 参数.二：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要编码的数据
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_QRCode::ModuleHelp_QRCode_QREncodecFile(LPCXSTR lpszFileName, LPCXSTR lpszMsgBuffer)
{
	ModuleHelp_IsErrorOccur = false;

	if ((NULL == lpszFileName) || (NULL == lpszMsgBuffer))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_PARAMENT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	//使用qrencode进行字符串编码
	QRcode* pSt_QRCodec = QRcode_encodeString(lpszMsgBuffer, 0, QR_ECLEVEL_H, QR_MODE_8, 1);
	if (NULL == pSt_QRCodec)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_FAILED;
		return false;
	}
	cv::Mat m_SrcFrame;
	//转换数据
	m_SrcFrame = cv::Mat(pSt_QRCodec->width, pSt_QRCodec->width, CV_8U);
	for (int i = 0; i < pSt_QRCodec->width; ++i)
	{
		for (int j = 0; j < pSt_QRCodec->width; ++j)
		{
			m_SrcFrame.at<uchar>(i, j) = (pSt_QRCodec->data[i * pSt_QRCodec->width + j] & 0x01) == 0x01 ? 0 : 255;
		}
	}
	//调整大小
	cv::resize(m_SrcFrame, m_SrcFrame, cv::Size(m_SrcFrame.rows * 10, m_SrcFrame.cols * 10), 0, 0, cv::INTER_NEAREST);
	//转换成彩色
	cv::cvtColor(m_SrcFrame, m_SrcFrame, cv::COLOR_GRAY2BGR);
	if (!cv::imwrite(lpszFileName, m_SrcFrame))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_WRITE;
		return false;
	}
#else 
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_NOTSUPPORT;
	return false;
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_QRCode_QREncodecMemory
函数功能：编码数据为二维码格式PNG图片
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要编码的数据
 参数.二：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出编码的数据
 参数.三：pInt_MsgLen
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出数据大小
 参数.四：lpszFmt
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入文件格式.png
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_QRCode::ModuleHelp_QRCode_QREncodecMemory(LPCXSTR lpszMsgBuffer, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszFmt)
{
	ModuleHelp_IsErrorOccur = false;

	if ((NULL == lpszMsgBuffer) || (NULL == ptszMsgBuffer))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_PARAMENT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	//使用qrencode进行字符串编码
	QRcode* pSt_QRCodec = QRcode_encodeString(lpszMsgBuffer, 0, QR_ECLEVEL_H, QR_MODE_8, 1);
	if (NULL == pSt_QRCodec)
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_FAILED;
		return false;
	}
	cv::Mat m_SrcFrame;
	vector<uchar> stl_VecImg;
	//转换数据
	m_SrcFrame = cv::Mat(pSt_QRCodec->width, pSt_QRCodec->width, CV_8U);
	for (int i = 0; i < pSt_QRCodec->width; ++i)
	{
		for (int j = 0; j < pSt_QRCodec->width; ++j)
		{
			m_SrcFrame.at<uchar>(i, j) = (pSt_QRCodec->data[i * pSt_QRCodec->width + j] & 0x01) == 0x01 ? 0 : 255;
		}
	}
	//调整大小
	cv::resize(m_SrcFrame, m_SrcFrame, cv::Size(m_SrcFrame.rows * 10, m_SrcFrame.cols * 10), 0, 0, cv::INTER_NEAREST);
	//转换成彩色
	cv::cvtColor(m_SrcFrame, m_SrcFrame, cv::COLOR_GRAY2BGR);
	//是否成功
	if (!cv::imencode(lpszFmt, m_SrcFrame, stl_VecImg))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_FAILED;
		return false;
	}
	*pInt_MsgLen = stl_VecImg.size();
	for (int i = 0; i < (*pInt_MsgLen); i++)
	{
		ptszMsgBuffer[i] = stl_VecImg[i];
	}
#else 
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_NOTSUPPORT;
	return false;
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_QRCode_QRDecodecFile
函数功能：从文件解码二维码
 参数.一：lpszFileName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的图片地址
 参数.二：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出识别到的内容
 参数.三：lpszDetectProto
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.四：lpszDetectModel
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.五：lpszSrProto
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.六：lpszSrModel
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_QRCode::ModuleHelp_QRCode_QRDecodecFile(LPCXSTR lpszFileName, XCHAR* ptszMsgBuffer, LPCXSTR lpszDetectProto, LPCXSTR lpszDetectModel, LPCXSTR lpszSrProto, LPCXSTR lpszSrModel)
{
	ModuleHelp_IsErrorOccur = false;

	if ((NULL == lpszFileName) || (NULL == ptszMsgBuffer))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_PARAMENT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	cv::Mat m_Frame;
	vector<cv::Mat> m_MatPoint;
	cv::Ptr<cv::wechat_qrcode::WeChatQRCode> m_QRDetector;
	m_Frame = cv::imread(lpszFileName);
	//是否成功
	if (m_Frame.empty())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_EMPTY;
		return false;
	}
	m_QRDetector = cv::makePtr<cv::wechat_qrcode::WeChatQRCode>(lpszDetectProto, lpszDetectModel, lpszSrProto, lpszSrModel);
	vector<string> stl_VectorQRList = m_QRDetector->detectAndDecode(m_Frame, m_MatPoint);

	if (stl_VectorQRList.empty())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_NOTQR;
		return false;
	}
	strcpy(ptszMsgBuffer, stl_VectorQRList[0].c_str());
#else 
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_NOTSUPPORT;
	return false;
#endif
	return true;
}
/********************************************************************
函数名称：ModuleHelp_QRCode_QRDecodecMemory
函数功能：从内存解析二维码
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的图片缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：ptszMsgBuffer
  In/Out：Out
  类型：字符指针
  可空：N
  意思：输出识别到的内容
 参数.四：lpszDetectProto
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.五：lpszDetectModel
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.六：lpszSrProto
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
 参数.七：lpszSrModel
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：学习模型地址,参考示例
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModuleHelp_QRCode::ModuleHelp_QRCode_QRDecodecMemory(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR* ptszMsgBuffer, LPCXSTR lpszDetectProto, LPCXSTR lpszDetectModel, LPCXSTR lpszSrProto, LPCXSTR lpszSrModel)
{
	ModuleHelp_IsErrorOccur = false;

	if ((NULL == lpszMsgBuffer) || (NULL == ptszMsgBuffer))
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_PARAMENT;
		return false;
	}
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	cv::Mat m_Frame;
	vector<cv::Mat> m_MatPoint;
	cv::Ptr<cv::wechat_qrcode::WeChatQRCode> m_QRDetector;

	cv::_InputArray m_InputArray(lpszMsgBuffer, nMsgLen);
	m_Frame = cv::imdecode(m_InputArray, cv::IMREAD_UNCHANGED);
	//是否成功
	if (m_Frame.empty())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_EMPTY;
		return false;
	}
	m_QRDetector = cv::makePtr<cv::wechat_qrcode::WeChatQRCode>(lpszDetectProto, lpszDetectModel, lpszSrProto, lpszSrModel);
	vector<string> stl_VectorQRList = m_QRDetector->detectAndDecode(m_Frame, m_MatPoint);

	if (stl_VectorQRList.empty())
	{
		ModuleHelp_IsErrorOccur = true;
		ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_NOTQR;
		return false;
	}
	strcpy(ptszMsgBuffer, stl_VectorQRList[0].c_str());
#else 
	ModuleHelp_IsErrorOccur = true;
	ModuleHelp_dwErrorCode = ERROR_XENGINE_APISERVICE_MODULE_HELP_QRCODE_NOTSUPPORT;
	return false;
#endif
	return true;
}