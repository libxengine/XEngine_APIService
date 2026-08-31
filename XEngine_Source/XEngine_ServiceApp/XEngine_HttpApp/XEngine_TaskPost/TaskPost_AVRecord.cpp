#include "../XEngine_Hdr.h"

static bool bRecord = false;
static XHANDLE xhENVideocodec = NULL;
static XHANDLE xhENAudiocodec = NULL;
static XHANDLE xhDEVideocodec = NULL;
static XHANDLE xhDEAudiocodec = NULL;

static XHANDLE xhSound = NULL;
static XHANDLE xhScreen = NULL;
static XHANDLE xhPacket = NULL;
static XHANDLE xhFilter = NULL;
static XHANDLE xhScale = NULL;
static int nVideoIndex = -1;
static int nAudioIndex = -1;

void XCALLBACK HTTPTask_TaskPost_CBVideo()
{
	while (bRecord)
	{
		int nAVIndex = 0;
		XHANDLE** ppSt_AVBuffer;
		if (!AVFormat_UNPack_Read(xhScreen, &nAVIndex, &ppSt_AVBuffer))
		{
			break;
		}

		int nDeCount = 0;
		XHANDLE** ppSt_AVBufferDecodec;
		VideoCodec_Stream_DeCodec(xhDEVideocodec, ppSt_AVBuffer[0], &ppSt_AVBufferDecodec, &nDeCount);
		for (int i = 0; i < nDeCount; i++)
		{
			if (VideoCodec_Help_ScaleConvert(xhScale, ppSt_AVBufferDecodec[i]))
			{
				int nEnCount = 0;
				XHANDLE** ppSt_AVBufferEncodec;
				VideoCodec_Stream_EnCodec(xhENVideocodec, ppSt_AVBufferDecodec[i], &ppSt_AVBufferEncodec, &nEnCount);
				for (int j = 0; j < nEnCount; j++)
				{
					AVFormat_Packet_StreamWrite(xhPacket, nVideoIndex, ppSt_AVBufferEncodec[j]);
				}
				AVHelp_Memory_FreeAVList(&ppSt_AVBufferEncodec, nEnCount);
			}
		}
		AVHelp_Memory_FreeAVList(&ppSt_AVBufferDecodec, nDeCount, false);
		AVHelp_Memory_FreeAVList(&ppSt_AVBuffer, 1, true);
	}
}
void XCALLBACK HTTPTask_TaskPost_CBAudio()
{
	while (bRecord)
	{
		int nAVIndex = 0;
		XHANDLE** ppSt_AVBuffer;
		if (!AVFormat_UNPack_Read(xhSound, &nAVIndex, &ppSt_AVBuffer))
		{
			break;
		}
		int nDeCount = 0;
		XHANDLE** ppSt_AVBufferDecodec;
		AudioCodec_Stream_DeCodec(xhDEAudiocodec, ppSt_AVBuffer[0], &ppSt_AVBufferDecodec, &nDeCount);
		for (int i = 0; i < nDeCount; i++)
		{
			int nFilterCount = 0;
			XHANDLE** ppSt_AVBufferFilter;
			AVFilter_Audio_Cvt(xhFilter, ppSt_AVBufferDecodec[i], &ppSt_AVBufferFilter, &nFilterCount);
			for (int j = 0; j < nFilterCount; j++)
			{
				int nEnCount = 0;
				XHANDLE** ppSt_AVBufferEncodec;
				AudioCodec_Stream_EnCodec(xhENAudiocodec, ppSt_AVBufferFilter[j], &ppSt_AVBufferEncodec, &nEnCount);
				for (int k = 0; k < nEnCount; k++)
				{
					AVFormat_Packet_StreamWrite(xhPacket, nAudioIndex, ppSt_AVBufferEncodec[k]);
				}
				AVHelp_Memory_FreeAVList(&ppSt_AVBufferEncodec, nEnCount, true);
			}
			AVHelp_Memory_FreeAVList(&ppSt_AVBufferFilter, nFilterCount, false);
		}
		AVHelp_Memory_FreeAVList(&ppSt_AVBufferDecodec, nDeCount, false);
		AVHelp_Memory_FreeAVList(&ppSt_AVBuffer, 1, true);
	}
}

bool HTTPTask_TaskPost_AVRecordStart(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen)
{
	int nSDLen = 0;
	XCHAR tszSDBuffer[XPATH_2MAX] = {};
	if (bRecord)
	{
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_STARTED, _X("record is started"));
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,因为已经在录制中了"), lpszClientAddr);
		return false;
	}
	XENGINE_AVRECORD st_AVRecord = {};
	XENGINE_PROTOCOL_AVINFO st_AVInfo = {};

	if (!ModuleProtocol_Parse_AVRecord(lpszMsgBuffer, nMsgLen, &st_AVRecord))
	{
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_JSON, _X("json is incorrect"));
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,解析协议失败,错误码:%lX"), lpszClientAddr, ModuleProtocol_GetLastError());
		return false;
	}
	xhPacket = AVFormat_Packet_Init();
	if (!AVFormat_Packet_Output(xhPacket, st_AVRecord.tszFilePath))
	{
		ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_OPEN, _X("open stream server is failed"));
		XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,推流服务端:%s 连接失败,错误码:%lX"), lpszClientAddr, st_AVRecord.tszFilePath, AVFormat_GetLastError());
		return false;
	}
	//屏幕采集
	if (_tcsxlen(st_AVRecord.tszVideoDevice) > 0)
	{
		int nListCount = 2;
		XENGINE_KEYVALUE** ppSt_KEYValue;
		BaseLib_Memory_Malloc((XPPPMEM)&ppSt_KEYValue, nListCount, sizeof(XENGINE_KEYVALUE));

		_xstprintf(ppSt_KEYValue[0]->tszStrKey, _X("framerate"));
		_xstprintf(ppSt_KEYValue[0]->tszStrVlu, _X("25"));

		_xstprintf(ppSt_KEYValue[1]->tszStrKey, _X("video_size"));
		_xstprintf(ppSt_KEYValue[1]->tszStrVlu, _X("%s"), st_AVRecord.tszRsolution);
		 
		bool bRet = false;
		xhScreen = AVFormat_UNPack_Init();
#ifdef _MSC_BUILD
		bRet = AVFormat_UNPack_Input(xhScreen, st_AVRecord.tszVideoDevice, "gdigrab", false, &ppSt_KEYValue, nListCount);
#elif __linux__
		bRet = AVFormat_UNPack_Input(xhScreen, st_AVRecord.tszVideoDevice, "x11grab", &ppSt_KEYValue, nListCount);
#else
		bRet = AVFormat_UNPack_Input(xhScreen, st_AVRecord.tszVideoDevice, "avfoundation", &ppSt_KEYValue, nListCount);
#endif
		BaseLib_Memory_Free((XPPPMEM)&ppSt_KEYValue, nListCount);
		if (!bRet)
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_DEVICE, _X("open video device is failed"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,屏幕采集器请求失败,错误码:%lX"), lpszClientAddr, AVFormat_GetLastError());
			return false;
		}
		XHANDLE xhVideoCodec = NULL;
		//初始化屏幕编码器
		AVFormat_UNPack_GetAVInfo(xhScreen, 0, &st_AVInfo);
		xhDEVideocodec = VideoCodec_Stream_DeInit((ENUM_AVCODEC_VIDEOTYPE)st_AVInfo.st_VideoInfo.enAVCodec);
		if (NULL == xhDEVideocodec)
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_INIT, _X("init video codec is failed"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,打开视频解码器失败,错误码:%lX"), lpszClientAddr, VideoCodec_GetLastError());
			return false;
		}
		xhScale = VideoCodec_Help_ScaleInit(st_AVInfo.st_VideoInfo.nWidth, st_AVInfo.st_VideoInfo.nHeight, st_AVInfo.st_VideoInfo.nFormat, st_AVInfo.st_VideoInfo.nWidth, st_AVInfo.st_VideoInfo.nHeight, ENUM_AVCODEC_VIDEO_SAMPLEFMT_YUV420P);

		st_AVInfo.st_VideoInfo.nFormat = 0;
		st_AVInfo.st_VideoInfo.nFrameBase = 1;
		st_AVInfo.st_VideoInfo.nFrameRate = 30;
		st_AVInfo.st_VideoInfo.enAVCodec = ENUM_XENGINE_AVCODEC_VIDEO_TYPE_H264;
		xhENVideocodec = VideoCodec_Stream_EnInit(&st_AVInfo.st_VideoInfo);
		if (NULL == xhENVideocodec)
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_INIT, _X("init video codec is failed"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,请求屏幕录制失败,打开视频编码器失败,错误码:%lX"), lpszClientAddr, VideoCodec_GetLastError());
			return false;
		}
		VideoCodec_Stream_GetAVCodec(xhENVideocodec, &xhVideoCodec);
		AVFormat_Packet_StreamCreate(xhPacket, xhVideoCodec, &nVideoIndex);
		AVHelp_Memory_FreeAVParameter(xhVideoCodec);
	}
	//启用音频
	if (_tcsxlen(st_AVRecord.tszAudioDevice) > 0)
	{
		bool bRet = false;
		xhSound = AVFormat_UNPack_Init();
#ifdef _MSC_BUILD
		bRet = AVFormat_UNPack_Input(xhSound, st_AVRecord.tszAudioDevice, "dshow");
#elif __linux__
		bRet = AVFormat_UNPack_Input(xhSound, st_AVRecord.tszAudioDevice, "alsa");
#else
		bRet = AVFormat_UNPack_Input(xhSound, st_AVRecord.tszAudioDevice, "avfoundation");
#endif
		if (!bRet)
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_INIT, _X("init audio collect is failed"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频采集器请求失败,错误码:%lX"), lpszClientAddr, AVFormat_GetLastError());
			return false;
		}
		AVFormat_UNPack_GetAVInfo(xhSound, 0, &st_AVInfo);
		AVFILTER_AUDIO_INFO st_AudioFilter = {};
		st_AudioFilter.nIndex = 0;
		st_AudioFilter.st_AudioInfo = st_AVInfo.st_AudioInfo;
		AVFormat_UNPack_GetTime(xhSound, 0, NULL, &st_AudioFilter.st_AudioTime);
		xhFilter = AVFilter_Audio_Init(_X("aresample=44100,aformat=sample_fmts=fltp:channel_layouts=stereo,asetnsamples=n=1024:p=1"), &st_AudioFilter);
		if (NULL == xhFilter)
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_INIT, _X("init audio filter is failed"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频滤镜失败,错误码:%lX"), lpszClientAddr, AVFilter_GetLastError());
			return false;
		}
		XHANDLE xhAudioParameter = NULL;
		AVFormat_UNPack_GetAVCodec(xhSound, 0, &xhAudioParameter);
		xhDEAudiocodec = AudioCodec_Stream_DeInit((ENUM_AVCODEC_AUDIOTYPE)st_AVInfo.st_AudioInfo.enAVCodec, xhAudioParameter);
		if (NULL == xhDEAudiocodec)
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_INIT, _X("init audio codec is failed"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频解码器请求失败,错误码:%lX"), lpszClientAddr, AudioCodec_GetLastError());
			return false;
		}

		st_AVInfo.st_AudioInfo.nSampleRate = 44100;
		st_AVInfo.st_AudioInfo.nSampleFmt = ENUM_AVCODEC_AUDIO_SAMPLEFMT_FLTP;
		st_AVInfo.st_AudioInfo.enAVCodec = ENUM_XENGINE_AVCODEC_AUDIO_TYPE_AAC;
		xhENAudiocodec = AudioCodec_Stream_EnInit(&st_AVInfo.st_AudioInfo);
		if (NULL == xhENAudiocodec)
		{
			ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen, ERROR_XENGINE_PROTOCL_HTTP_INIT, _X("init audio codec is failed"));
			XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _X("HTTP客户端:%s,初始化音频编码器请求失败,错误码:%lX"), lpszClientAddr, AudioCodec_GetLastError());
			return false;
		}
		XHANDLE xhAudioCodec = NULL;
		AudioCodec_Stream_GetAVCodec(xhENAudiocodec, &xhAudioCodec);
		AVFormat_Packet_StreamCreate(xhPacket, xhAudioCodec, &nAudioIndex);
		//使用了滤镜,需要单独设置
		AVCODEC_TIMEBASE st_TimeBase = {};
		st_TimeBase.nDen = 44100;
		st_TimeBase.nNum = 1;
		AVFormat_Packet_TimeBase(xhPacket, 1, &st_TimeBase);
		AVHelp_Memory_FreeAVParameter(xhAudioCodec);
		AVHelp_Memory_FreeAVParameter(xhAudioParameter);
	}
	bRecord = true;
	AVFormat_Packet_Start(xhPacket);

	std::thread st_ThreadVideo(HTTPTask_TaskPost_CBVideo);
	std::thread st_ThreadAudio(HTTPTask_TaskPost_CBAudio);
	st_ThreadVideo.detach();
	st_ThreadAudio.detach();
	ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen);
	XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,开始屏幕录制,音频:%s,视频:%s 推流:%s 请求成功"), lpszClientAddr, st_AVRecord.tszAudioDevice, st_AVRecord.tszVideoDevice, st_AVRecord.tszFilePath);
	return true;
}
bool HTTPTask_TaskPost_AVRecordStop(LPCXSTR lpszClientAddr)
{
	bRecord = false;

	AVFormat_UNPack_Stop(xhScreen);
	AVFormat_UNPack_Stop(xhSound);

	VideoCodec_Stream_Destroy(xhENVideocodec);
	VideoCodec_Stream_Destroy(xhDEVideocodec);
	AudioCodec_Stream_Destroy(xhENAudiocodec);
	AudioCodec_Stream_Destroy(xhDEAudiocodec);

	AVFilter_Audio_Destroy(xhFilter);

	AVFormat_Packet_Stop(xhPacket);
	VideoCodec_Help_ScaleUninit(xhScale);
	xhScreen = NULL;
	xhSound = NULL;
	xhENVideocodec = NULL;
	xhDEVideocodec = NULL;
	xhENAudiocodec = NULL;
	xhDEAudiocodec = NULL;
	xhFilter = NULL;
	xhPacket = NULL;
	xhScale = NULL;

	int nSDLen = 0;
	XCHAR tszSDBuffer[XPATH_MAX] = {};
	ModuleProtocol_Packet_Common(tszSDBuffer, &nSDLen);
	XEngine_Network_Send(lpszClientAddr, tszSDBuffer, nSDLen);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _X("HTTP客户端:%s,停止屏幕录制推流请求成功"), lpszClientAddr);

	return true;
}