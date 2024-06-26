#include "pch.h"
#include "ModulePlugin_APIPhone.h"
/********************************************************************
//    Created:     2023/01/09  17:13:39
//    File Name:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\ModulePlugin_APIPhone\ModulePlugin_APIPhone.cpp
//    File Path:   D:\XEngine_APIService\XEngine_Source\XEngine_PluginModule\ModulePlugin_Phone\ModulePlugin_APIPhone
//    File Base:   ModulePlugin_APIPhone
//    File Ext:    cpp
//    Project:     XEngine
//    Author:      qyt
//    Purpose:     电话接口类
//    History:
*********************************************************************/
CModulePlugin_APIPhone::CModulePlugin_APIPhone()
{
}
CModulePlugin_APIPhone::~CModulePlugin_APIPhone()
{
}
//////////////////////////////////////////////////////////////////////////
//                       公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：PluginCore_Init
函数功能：初始化插件模块
 参数.一：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：N
  意思：自定义参数
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_APIPhone::PluginCore_Init(XPVOID lParam)
{
	Phone_IsErrorOccur = false;

	LPCXSTR lpszFile = _X("./XEngine_DBFile/phone.dat");
	FILE* pSt_File = _xtfopen(lpszFile, _X("rb"));
	if (NULL == pSt_File)
	{
		return false;
	}
	ptszMSGBuffer = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_LARGE);
	if (NULL == ptszMSGBuffer)
	{
		return false;
	}
	memset(ptszMSGBuffer, '\0', XENGINE_MEMORY_SIZE_LARGE);
	nFSize = fread(ptszMSGBuffer, 1, XENGINE_MEMORY_SIZE_LARGE, pSt_File);
	fclose(pSt_File);

	if (!PluginCore_Phone_Init(ptszMSGBuffer))
	{
		return false;
	}
    return true;
}
/********************************************************************
函数名称：PluginCore_UnInit
函数功能：卸载插件
返回值
  类型：无
  意思：
备注：
*********************************************************************/
void CModulePlugin_APIPhone::PluginCore_UnInit()
{
	Phone_IsErrorOccur = false;

	if (NULL != ptszMSGBuffer)
	{
		free(ptszMSGBuffer);
		ptszMSGBuffer = NULL;
	}
	if (NULL != ptszPhoneIndex)
	{
		free(ptszPhoneIndex);
		ptszPhoneIndex = NULL;
	}
}
/********************************************************************
函数名称：PluginCore_Call
函数功能：调用插件
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
bool CModulePlugin_APIPhone::PluginCore_Call(XCHAR*** pppHDRList, int nListCount, int* pInt_HTTPCode, XCHAR* ptszMsgBuffer, int* pInt_MsgLen, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	Phone_IsErrorOccur = false;

	if ((NULL == pInt_HTTPCode) || (NULL == ptszMsgBuffer) || (NULL == pInt_MsgLen))
	{
		Phone_IsErrorOccur = true;
		Phone_dwErrorCode = ERROR_XENGINE_APISERVICE_PLUGIN_MODULE_PHONE_PARAMENT;
		return false;
	}
	XCHAR tszKeyName[128];
	XCHAR tszKeyValue[128];
	Json::Value st_JsonRoot;
	Json::Value st_JsonObject;
	Json::StreamWriterBuilder st_JsonBuilder;
	XENGINE_PHONEINFO st_PhoneInfo;

	memset(tszKeyName, '\0', sizeof(tszKeyName));
	memset(tszKeyValue, '\0', sizeof(tszKeyValue));
	memset(&st_PhoneInfo, '\0', sizeof(XENGINE_PHONEINFO));

	BaseLib_OperatorString_GetKeyValue((*pppHDRList)[1], "=", tszKeyName, tszKeyValue);
	//查找
	ptszPhoneIndex = (XCHAR*)malloc(XENGINE_MEMORY_SIZE_LARGE);
	if (NULL == ptszPhoneIndex)
	{
		return false;
	}
	memset(ptszPhoneIndex, '\0', XENGINE_MEMORY_SIZE_LARGE);
	memcpy(ptszPhoneIndex, ptszMSGBuffer + nPos, nFSize - nPos);

	XCHAR* ptszTokTmp = NULL;
	XCHAR* ptszTokStr = _tcsxtok_s(ptszPhoneIndex, _X("\n"), &ptszTokTmp);
	while (NULL != ptszTokStr)
	{
		typedef struct
		{
			XCHAR tszPhoneStr[64];
			XCHAR tszAreaStr[64];
			XCHAR tszPhoneType[64];
			XCHAR tszIndexStr[64];
			XCHAR tszTransferStr[64];
		}XENGINE_PHONEINDEX;

		XENGINE_PHONEINDEX st_PhoneIndex = {};
		int nRet = _stxscanf(ptszTokStr, _X("%[^-]-%[^-]-%[^-]-%[^-]-%s"), st_PhoneIndex.tszPhoneStr, st_PhoneIndex.tszAreaStr, st_PhoneIndex.tszPhoneType, st_PhoneIndex.tszIndexStr, st_PhoneIndex.tszTransferStr);
		if (nRet != 5)
		{
			break;
		}

		std::string m_StrPhone = PluginCore_Phone_7Digits(tszKeyValue);
		if (0 == _tcsxnicmp(m_StrPhone.c_str(), st_PhoneIndex.tszPhoneStr, m_StrPhone.length()))
		{
			XCHAR tszLocationStr[MAX_PATH] = {};
			memcpy(tszLocationStr, ptszMSGBuffer + _ttxoi(st_PhoneIndex.tszIndexStr), 64);

			XCHAR* ptszSubTmp = NULL;
			XCHAR* ptszSubStr = _tcsxtok_s(tszLocationStr, _X("\n"), &ptszSubTmp);

			int nRet = _stxscanf(ptszSubStr, _X("%[^-]-%[^-]-%s"), st_PhoneIndex.tszAreaStr, st_PhoneInfo.tszProvincer, st_PhoneInfo.tszCity);

			st_JsonObject["nPhoneNumber"] = (Json::Value::Int64)_ttxoll(tszKeyValue);
			st_JsonObject["tszProvincer"] = st_PhoneInfo.tszProvincer;
			st_JsonObject["tszCity"] = st_PhoneInfo.tszCity;
			st_JsonObject["nAreaCode"] = st_PhoneIndex.tszAreaStr;

			auto stl_MapIterator = stl_MapISPName.find(_ttxoi(st_PhoneIndex.tszPhoneType));
			if (stl_MapIterator != stl_MapISPName.end())
			{
				st_JsonObject["tszISPName"] = stl_MapIterator->second.c_str();
			}
			break;
		}
		ptszTokStr = _tcsxtok_s(NULL, _X("\n"), &ptszTokTmp);
	}
	st_JsonRoot["data"] = st_JsonObject;
	st_JsonRoot["code"] = 0;
	st_JsonRoot["msg"] = "success";
	st_JsonBuilder["emitUTF8"] = true;

	*pInt_HTTPCode = 200;
	*pInt_MsgLen = Json::writeString(st_JsonBuilder, st_JsonRoot).length();
	memcpy(ptszMsgBuffer, Json::writeString(st_JsonBuilder, st_JsonRoot).c_str(), *pInt_MsgLen);
	free(ptszPhoneIndex);
	ptszPhoneIndex = NULL;
	return true;
}
//////////////////////////////////////////////////////////////////////////
//                       保护函数
//////////////////////////////////////////////////////////////////////////
bool CModulePlugin_APIPhone::PluginCore_Phone_Init(LPCXSTR lpszMSGBuffer)
{
	Phone_IsErrorOccur = false;

	nPos = 0;
	XCHAR tszMSGBuffer[MAX_PATH] = {};
	//得到头分区数据
	memcpy(&st_ProtocolHdr, lpszMSGBuffer, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);
	if (XENGIEN_COMMUNICATION_PACKET_PROTOCOL_HEADER != st_ProtocolHdr.wHeader || XENGIEN_COMMUNICATION_PACKET_PROTOCOL_TAIL != st_ProtocolHdr.wTail || 200 != st_ProtocolHdr.unOperatorType)
	{
		return false;
	}
	memcpy(tszMSGBuffer, lpszMSGBuffer + nPos, st_ProtocolHdr.unPacketSize);
	nPos += st_ProtocolHdr.unPacketSize;
	//得到类型映射
	memcpy(&st_ProtocolMap, lpszMSGBuffer + nPos, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);

	memset(tszMSGBuffer, '\0', sizeof(tszMSGBuffer));
	memcpy(tszMSGBuffer, lpszMSGBuffer + nPos, st_ProtocolMap.unPacketSize);
	nPos += st_ProtocolMap.unPacketSize;

	XCHAR* ptszTokStr = _tcsxtok(tszMSGBuffer, _X(","));
	while (NULL != ptszTokStr)
	{
		XCHAR tszKEYStr[16] = {};
		XCHAR tszVLUStr[16] = {};
		int nRet = _stxscanf(ptszTokStr, _X("%[^-]-%s"), tszKEYStr, tszVLUStr);
		if (nRet != 2)
		{
			break;
		}
		stl_MapISPName.insert(std::make_pair(_ttxoi(tszKEYStr), tszVLUStr));
		ptszTokStr = _tcsxtok(NULL, _X(","));
	}
	//得到记录分区
	memcpy(&st_ProtocolRecord, ptszMSGBuffer + nPos, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);
	nPos += st_ProtocolRecord.unPacketSize;
	//得到索引分区
	memcpy(&st_ProtocolIndex, ptszMSGBuffer + nPos, sizeof(XENGINE_PROTOCOLHDR));
	nPos += sizeof(XENGINE_PROTOCOLHDR);
	return true;
}
std::string CModulePlugin_APIPhone::PluginCore_Phone_7Digits(LPCXSTR lpszMSGBuffer)
{
	Phone_IsErrorOccur = false;

	std::string str = lpszMSGBuffer;

	if (str.length() < 7) 
	{
		str.append(7 - str.length(), '0');
	}
	else if (str.length() > 7) 
	{
		str = str.substr(0, 7);
	}

	return str;
}