﻿#pragma once
/********************************************************************
//    Created:     2022/04/21  11:13:32
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp\XEngine_PluginTask.h
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_ServiceApp\XEngine_HttpApp
//    File Base:   XEngine_PluginTask
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     插件处理框架代码
//    History:
*********************************************************************/
//插件处理函数
bool XEngine_PluginTask_Handle(LPCXSTR lpszMethodName, LPCXSTR lpszClientAddr, LPCXSTR lpszRVBuffer, int nRVLen, XCHAR*** ppptszList, int nListCount, int nPluginType);