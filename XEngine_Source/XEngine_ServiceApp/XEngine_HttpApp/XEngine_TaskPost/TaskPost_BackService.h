#pragma once
void XCALLBACK HTTPTask_TaskPost_CBVideo(XENGINE_MSGBUFFER* pSt_MSGBuffer, AVCODEC_TIMESTAMP* pSt_TimeInfo, int nNBSample, int nSampleFmt, XPVOID lParam);
void XCALLBACK HTTPTask_TaskPost_CBAudio(XENGINE_MSGBUFFER* pSt_MSGBuffer, AVCODEC_TIMESTAMP* pSt_TimeInfo, int nNBSample, int nSampleFmt, XPVOID lParam);

bool HTTPTask_TaskPost_BackService(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType);