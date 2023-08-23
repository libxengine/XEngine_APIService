#pragma once
/********************************************************************
//    Created:     2023/08/11  15:18:20
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Image\ModuleHelp_ImageSet.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Image
//    File Base:   ModuleHelp_ImageSet
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     图像修改处理库
//    History:
*********************************************************************/

class CModuleHelp_ImageSet
{
public:
	CModuleHelp_ImageSet();
	~CModuleHelp_ImageSet();
public:
	bool ModuleHelp_ImageSet_Resolution(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nWidth, int nHeight);
	bool ModuleHelp_ImageSet_Flip(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nOPMethod);
	bool ModuleHelp_ImageSet_ColorCvt(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, ENUM_XENGINE_IMAGE_COLOR_INFO enColorInfo);
	bool ModuleHelp_ImageSet_Ligth(LPCXSTR lpszSrcBuffer, int nSLen, LPCXSTR lpszExtFile, XCHAR* ptszDstBuffer, int* pInt_DLen, int nGamma);
protected:
private:
};