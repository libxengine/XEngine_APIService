#include "../XEngine_Hdr.h"

// 处理图片相关HTTP任务请求。
// 参数说明：
// 1) lpszClientAddr: 客户端地址，用于回复与日志。
// 2) lpszMsgBuffer/nMsgLen: 图片二进制数据及长度（用于设置类操作）。
// 3) ppptszList/nListCount: HTTP附加参数列表，至少包含操作码及相关参数。
// 流程说明：
// - 根据编译开关检查是否支持OpenCV能力；
// - 解析操作码并分发到不同图片处理分支（获取/设置/扩展操作）；
// - 对参数数量与格式进行校验；
// - 调用底层ModuleHelp_ImageSet_*接口处理；
// - 无论成功或失败，均封包并发送HTTP响应，同时记录日志。
bool HTTPTask_TaskPost_Image(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, XCHAR*** ppptszList, int nListCount)
{
	int nSDLen = 0;
	XCHAR tszHTTPKey[64] = {};
	XCHAR tszHTTPVlu[64] = {};
	CXEngine_MemoryPoolEx m_MemorySend(XENGINE_MEMORY_SIZE_LARGE);

#if (0 == _XENGINE_BUILD_SWITCH_OPENCV)
	// 编译时未启用OpenCV能力：直接返回“不支持”错误。
	ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_NOTSUPPORT,_X("not support"));
	XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求图片操作失败,服务器没有启用此功能"), lpszClientAddr);
	return false;
#else

	// 从参数列表中提取操作码（示例：opcode=0/1/...）。
	BaseLib_String_GetKeyValue((*ppptszList)[1], "=", tszHTTPKey, tszHTTPVlu);
	int nOPCode = _ttxoi(tszHTTPVlu);
	// 0获取,1设置,其它值进入扩展图像处理分支
	if (0 == nOPCode)
	{
		// 获取配置/状态类请求前，先检查服务开关。
		if (!st_ServiceConfig.st_XImageText.bEnable)
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_DISABLE, _X("function is disable"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求图片转文本操作失败,服务器没有启用此功能"), lpszClientAddr);
			return false;
		}
		XCHAR** pptszListStr;
		int nListCount = 0;
		if (ModuleHelp_ImageGet_TextGet(lpszMsgBuffer, nMsgLen, &pptszListStr, &nListCount))
		{
			ModuleProtocol_Packet_ImageText(m_MemorySend.get(), &nSDLen, &pptszListStr, nListCount);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			BaseLib_Memory_Free((XPPPMEM)&pptszListStr, nListCount);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求获取识别图片文字成功,获取个数:%d"), lpszClientAddr, nListCount);
		}
		else
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("image operator failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求获取识别图片文字失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
		}
	}
	else if (1 == nOPCode)
	{
		XENGINE_IMGBASEATTR st_BaseInfo;
		XENGINE_IMGEXTATTR st_ExtAttr;

		if (ModuleHelp_ImageGet_Attr(lpszMsgBuffer, nMsgLen, &st_BaseInfo, &st_ExtAttr))
		{
			ModuleProtocol_Packet_ImageAttr(m_MemorySend.get(), &nSDLen, &st_BaseInfo, &st_ExtAttr);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求获取图像信息成功,宽:%d,高:%d,通道:%d"), lpszClientAddr, st_BaseInfo.nWidth, st_BaseInfo.nHeigth, st_BaseInfo.nChannel);
		}
		else
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("image operator failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求获取图片属性失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
		}
	}
	else
	{
		// 扩展图片处理分支：要求至少包含操作参数与文件后缀等关键字段。
		if (nListCount < 4)
		{
			ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("image operator failure"));
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求设置图像数据失败,因为附加参数不正确,参数个数:%d"), lpszClientAddr, nListCount);
			return false;
		}
		// 解析并缓存图片后缀名，供后续压缩/变换接口选择编码器使用。
		XCHAR tszFileExt[XPATH_MAX];
		memset(tszFileExt, '\0', sizeof(tszFileExt));

		memset(tszHTTPVlu, '\0', sizeof(tszHTTPVlu));

		BaseLib_String_GetKeyValue((*ppptszList)[2], "=", tszHTTPKey, tszHTTPVlu);
		_xstprintf(tszFileExt, _X(".%s"), tszHTTPVlu);

		BaseLib_String_GetKeyValue((*ppptszList)[3], "=", tszHTTPKey, tszHTTPVlu);
		int nWidth = _ttxoi(tszHTTPVlu);
		if (2 == nOPCode)
		{
			BaseLib_String_GetKeyValue((*ppptszList)[4], "=", tszHTTPKey, tszHTTPVlu);
			int nHeight = _ttxoi(tszHTTPVlu);
			if (ModuleHelp_ImageSet_Resolution(lpszMsgBuffer, nMsgLen, tszFileExt, m_MemorySend.get(), &nSDLen, nWidth, nHeight))
			{
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求设置图像分辨率成功,宽:%d,高:%d"), lpszClientAddr, nWidth, nHeight);
			}
			else
			{
				ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("image operator failure"));
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求设置图像分辨率失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
			}

		}
		else if (3 == nOPCode)
		{
			if (ModuleHelp_ImageSet_ColorCvt(lpszMsgBuffer, nMsgLen, tszFileExt, m_MemorySend.get(), &nSDLen, (ENUM_XENGINE_IMAGE_COLOR_INFO)nWidth))
			{
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求设置图像颜色空间转换成功,转换的值:%d"), lpszClientAddr, nWidth);
			}
			else
			{
				ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("image operator failure"));
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求设置图像颜色空间转换失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
			}
		}
		else if (4 == nOPCode)
		{
			if (ModuleHelp_ImageSet_Flip(lpszMsgBuffer, nMsgLen, tszFileExt, m_MemorySend.get(), &nSDLen, nWidth))
			{
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求设置图像翻转成功,翻转的值:%d"), lpszClientAddr, nWidth);
			}
			else
			{
				ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("image operator failure"));
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求设置图像翻转失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
			}
		}
		else if (5 == nOPCode)
		{
			if (ModuleHelp_ImageSet_Ligth(lpszMsgBuffer, nMsgLen, tszFileExt, m_MemorySend.get(), &nSDLen, nWidth))
			{
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求设置图像亮度,亮度的值:%d"), lpszClientAddr, nWidth);
			}
			else
			{
				ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("image operator failure"));
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求设置图像亮度失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
			}
		}
		else if (6 == nOPCode)
		{
			if (ModuleHelp_ImageSet_Level(lpszMsgBuffer, nMsgLen, tszFileExt, m_MemorySend.get(), &nSDLen, nWidth))
			{
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,请求设置图像质量压缩值:%d"), lpszClientAddr, nWidth);
			}
			else
			{
				ModuleProtocol_Packet_Common(m_MemorySend.get(), &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_FAILURE, _X("image operator failure"));
				XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求设置图像质量压缩失败,错误:%lX"), lpszClientAddr, ModuleHelp_GetLastError());
			}
		}
	}
#endif
	return true;
}