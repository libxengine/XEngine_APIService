#pragma once
/********************************************************************
//    Created:     2023/08/11  15:16:00
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Image\ModuleHelp_ImageGet.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ModuleHelp\ModuleHelp_Image
//    File Base:   ModuleHelp_ImageGet
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     图像信息获取处理库
//    History:
*********************************************************************/

class CModuleHelp_ImageGet
{
public:
	CModuleHelp_ImageGet();
	~CModuleHelp_ImageGet();
public:
	bool ModuleHelp_ImageGet_Attr(LPCXSTR lpszMsgBuffer, int nMsgLen, XENGINE_IMGBASEATTR* pSt_BaseInfo = NULL, XENGINE_IMGEXTATTR* pSt_ExtAttr = NULL);
public:
	bool ModuleHelp_ImageGet_TextInit(LPCXSTR lpszPath, LPCXSTR lpszLanguage);
	bool ModuleHelp_ImageGet_TextGet(LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR*** ppptszListStr, int* pInt_ListCount);
	bool ModuleHelp_ImageGet_TextDestory();
protected:
private:
#if _XENGINE_BUILD_SWITCH_OPENCV == 1
	TessBaseAPI* pSt_APITesseract = NULL;
#endif
};