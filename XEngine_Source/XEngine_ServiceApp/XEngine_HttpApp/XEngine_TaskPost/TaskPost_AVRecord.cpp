#include "../XEngine_Hdr.h"

static bool bRecord = false;
static XHANDLE xhVideo = NULL;
static XHANDLE xhAudio = NULL;
static XHANDLE xhSound = NULL;
static XHANDLE xhScreen = NULL;
static XHANDLE xhPacket = NULL;
static XHANDLE xhFilter = NULL;
static XHANDLE xhScale = NULL;

void XCALLBACK HTTPTask_TaskPost_CBVideo(XHANDLE*** pppSt_AVBuffer, XPVOID lParam)
{
	XHANDLE** ppSt_AVFrame;
	if (VideoCodec_Help_ScaleConvert(xhScale, (*pppSt_AVBuffer)[0], &ppSt_AVFrame))
	{
		int nListCount = 0;
		XHANDLE** ppSt_AVPacket;
		VideoCodec_Stream_EnCodec(xhVideo, ppSt_AVFrame[0], &ppSt_AVPacket, &nListCount);
		for (int j = 0; j < nListCount; j++)
		{
			AVFormat_Packet_StreamWrite(xhPacket, 0, ppSt_AVPacket[j]);
		}
		AVHelp_Memory_FreeAVList(&ppSt_AVPacket, nListCount);
	}
	AVHelp_Memory_FreeAVList(&ppSt_AVFrame, 1, false);
}
void XCALLBACK HTTPTask_TaskPost_CBAudio(XHANDLE*** pppSt_AVBuffer, XPVOID lParam)
{
	int nListCount = 0;
	XHANDLE** ppSt_MSGBuffer;
	AVFilter_Audio_Cvt(xhFilter, pppSt_AVBuffer, &ppSt_MSGBuffer, &nListCount);
	for (int i = 0; i < nListCount; i++)
	{
		int nAudioCount = 0;
		XHANDLE** ppSt_AVPacket;
		AudioCodec_Stream_EnCodec(xhAudio, ppSt_MSGBuffer[i], &ppSt_AVPacket, &nAudioCount);
		for (int j = 0; j < nAudioCount; j++)
		{
			AVFormat_Packet_StreamWrite(xhPacket, 1, ppSt_AVPacket[j]);
		}
		AVHelp_Memory_FreeAVList(&ppSt_AVPacket, nAudioCount);
	}
	AVHelp_Memory_FreeAVList(&ppSt_MSGBuffer, nListCount, false);
}

bool HTTPTask_TaskPost_AVRecordStart(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	int nSDLen = 0;
	int nRVLen = 0;
	CXEngine_MemoryPoolEx m_MemorySend(XENGINE_MEMORY_SIZE_MAX);
	CXEngine_MemoryPoolEx m_MemoryRecv(XENGINE_MEMORY_SIZE_MAX);

	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};    //发送给客户端的参数

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭
	if (bRecord)
	{
		st_HDRParam.nHttpCode = 400;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,因为已经在录制中了"), lpszClientAddr);
		return false;
	}
	XENGINE_AVRECORD st_AVRecord = {};
	XENGINE_PROTOCOL_AVINFO st_AVInfo = {};

	if (!ModuleProtocol_Parse_AVRecord(lpszMsgBuffer, nMsgLen, &st_AVRecord))
	{
		st_HDRParam.nHttpCode = 400;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,解析协议失败,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
		return false;
	}
	xhPacket = AVFormat_Packet_Init();
	if (!AVFormat_Packet_Output(xhPacket, st_AVRecord.tszFilePath, _X("flv")))
	{
		st_HDRParam.nHttpCode = 400;
		HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
		XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,推流服务端:%s 连接失败,错误码:%lX"), lpszClientAddr, st_AVRecord.tszFilePath, AVFormat_GetLastError());
		return false;
	}
	//屏幕采集
	if (_tcsxlen(st_AVRecord.tszVideoDevice) > 0)
	{
		AVCOLLECT_SCREENINFO st_AVScreen = {};

		st_AVScreen.nFrameRate = 24;
		st_AVScreen.nPosX = 0;
		st_AVScreen.nPosY = 0;
		_xstprintf(st_AVScreen.tszVideoSize, _X("%s"), st_AVRecord.tszRsolution);
#ifdef _MSC_BUILD
		xhScreen = AVCollect_Video_Init("gdigrab", st_AVRecord.tszVideoDevice, &st_AVScreen, HTTPTask_TaskPost_CBVideo);
#elif __linux__
		xhScreen = AVCollect_Video_Init("x11grab", st_AVRecord.tszVideoDevice, &st_AVScreen, HTTPTask_TaskPost_CBVideo);
#else
		xhScreen = AVCollect_Video_Init("avfoundation", st_AVRecord.tszVideoDevice, &st_AVScreen, HTTPTask_TaskPost_CBVideo);
#endif
		if (NULL == xhScreen)
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,屏幕采集器请求失败,错误码:%lX"), lpszClientAddr, AVCollect_GetLastError());
			return false;
		}
		XHANDLE xhVideoCodec = NULL;
		//初始化屏幕编码器
		AVCollect_Video_GetInfo(xhScreen, &st_AVInfo);

		xhScale = VideoCodec_Help_ScaleInit(st_AVInfo.st_VideoInfo.nWidth, st_AVInfo.st_VideoInfo.nHeight, st_AVInfo.st_VideoInfo.nFormat, st_AVInfo.st_VideoInfo.nWidth, st_AVInfo.st_VideoInfo.nHeight, ENUM_AVCODEC_VIDEO_SAMPLEFMT_YUV420P);

		st_AVInfo.st_VideoInfo.nFormat = 0;
		st_AVInfo.st_VideoInfo.enAVCodec = ENUM_XENGINE_AVCODEC_VIDEO_TYPE_H264;
		xhVideo = VideoCodec_Stream_EnInit(&st_AVInfo.st_VideoInfo);
		if (NULL == xhVideo)
		{
			st_HDRParam.nHttpCode = 500;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,打开编码器视频编码器失败,错误码:%lX"), lpszClientAddr, VideoCodec_GetLastError());
			return false;
		}
		VideoCodec_Stream_GetAVCodec(xhVideo, &xhVideoCodec);
		AVFormat_Packet_StreamCreate(xhPacket, xhVideoCodec);
		BaseLib_Memory_FreeCStyle((XPPMEM)&xhVideoCodec);
	}
	//启用音频
	if (_tcsxlen(st_AVRecord.tszAudioDevice) > 0)
	{
#ifdef _MSC_BUILD
		xhSound = AVCollect_Audio_Init("dshow", st_AVRecord.tszAudioDevice, HTTPTask_TaskPost_CBAudio);
#elif __linux__
		xhSound = AVCollect_Audio_Init("alsa", st_AVRecord.tszAudioDevice, HTTPTask_TaskPost_CBAudio);
#else
		xhSound = AVCollect_Audio_Init("avfoundation", st_AVRecord.tszAudioDevice, HTTPTask_TaskPost_CBAudio);
#endif
		if (NULL == xhSound)
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频采集器请求失败,错误码:%lX"), lpszClientAddr, AVCollect_GetLastError());
			return false;
		}
		AVCollect_Audio_GetInfo(xhSound, &st_AVInfo);
		AVFILTER_AUDIO_INFO st_AudioFilter = {};
		st_AudioFilter.nIndex = 0;
		st_AudioFilter.st_AudioInfo = st_AVInfo.st_AudioInfo;
		AVCollect_Audio_GetTimeBase(xhSound, &st_AudioFilter.st_AudioTime);
		xhFilter = AVFilter_Audio_Init(_X("aresample=44100,aformat=sample_fmts=fltp:channel_layouts=stereo"), &st_AudioFilter);
		if (NULL == xhFilter)
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频滤镜失败,错误码:%lX"), lpszClientAddr, AVFilter_GetLastError());
			return false;
		}
		st_AVInfo.st_AudioInfo.nSampleRate = 44100;
		st_AVInfo.st_AudioInfo.nSampleFmt = ENUM_AVCODEC_AUDIO_SAMPLEFMT_FLTP;
		st_AVInfo.st_AudioInfo.enAVCodec = ENUM_XENGINE_AVCODEC_AUDIO_TYPE_AAC;
		xhAudio = AudioCodec_Stream_EnInit(&st_AVInfo.st_AudioInfo);
		if (NULL == xhAudio)
		{
			st_HDRParam.nHttpCode = 400;
			HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
			XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频采集器请求失败,错误码:%lX"), lpszClientAddr, AudioCodec_GetLastError());
			return false;
		}
		XHANDLE xhAudioCodec = NULL;
		AudioCodec_Stream_GetAVCodec(xhAudio, &xhAudioCodec);
		AVFormat_Packet_StreamCreate(xhPacket, xhAudioCodec);
		//使用了滤镜,需要单独设置
		AVCODEC_TIMEBASE st_TimeBase = {};
		st_TimeBase.nDen = 44100;
		st_TimeBase.nNum = 1;
		AVFormat_Packet_TimeBase(xhPacket, 1, &st_TimeBase);
		BaseLib_Memory_FreeCStyle((XPPMEM)&xhAudioCodec);
	}
	bRecord = true;
	AVFormat_Packet_Start(xhPacket);
	AVCollect_Audio_Start(xhSound);
	AVCollect_Video_Start(xhScreen);
	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, m_MemorySend.get(), &nSDLen, &st_HDRParam);
	XEngine_Network_Send(lpszClientAddr, m_MemorySend.get(), nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,开始屏幕录制,音频:%s,视频:%s 推流:%s 请求成功"), lpszClientAddr, st_AVRecord.tszAudioDevice, st_AVRecord.tszVideoDevice, st_AVRecord.tszFilePath);
	return true;
}
bool HTTPTask_TaskPost_AVRecordStop(LPCXSTR lpszClientAddr)
{
	bRecord = false;

	AVCollect_Video_Destory(xhScreen);
	AVCollect_Audio_Destory(xhSound);

	VideoCodec_Stream_Destroy(xhVideo);
	AudioCodec_Stream_Destroy(xhAudio);

	AVFilter_Audio_Destroy(xhFilter);

	AVFormat_Packet_Stop(xhPacket);
	VideoCodec_Help_ScaleUninit(xhScale);
	xhScreen = NULL;
	xhSound = NULL;
	xhVideo = NULL;
	xhAudio = NULL;
	xhPacket = NULL;

	int nMSGLen = 0;
	XCHAR tszMSGBuffer[XPATH_MAX] = {};
	RFCCOMPONENTS_HTTP_HDRPARAM st_HDRParam = {};    //发送给客户端的参数

	st_HDRParam.nHttpCode = 200; //HTTP CODE码
	st_HDRParam.bIsClose = true; //收到回复后就关闭

	HttpProtocol_Server_SendMsgEx(xhHTTPPacket, tszMSGBuffer, &nMSGLen, &st_HDRParam);
	XEngine_Network_Send(lpszClientAddr, tszMSGBuffer, nMSGLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,停止屏幕录制推流请求成功"), lpszClientAddr);

	return true;
}