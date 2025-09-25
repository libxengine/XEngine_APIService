#pragma once
void XCALLBACK HTTPTask_TaskPost_CBVideo(uint8_t* ptszAVBuffer, int nAVLen, AVCODEC_TIMESTAMP* pSt_TimeInfo, XPVOID lParam);
void XCALLBACK HTTPTask_TaskPost_CBAudio(AVCODEC_AUDIO_MSGBUFFER* pSt_MSGBuffer, XPVOID lParam);

bool HTTPTask_TaskPost_BackService(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType);