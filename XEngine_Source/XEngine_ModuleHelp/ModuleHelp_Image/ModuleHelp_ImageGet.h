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
	bool ModuleHelp_ImageGet_Attr(LPCXSTR lpszMsgBuffer, int nMsgLen, IMAGEINFO_BASEATTR* pSt_BaseInfo = NULL, IMAGEINFO_EXTENDATTR* pSt_ExtAttr = NULL);
protected:
private:
};