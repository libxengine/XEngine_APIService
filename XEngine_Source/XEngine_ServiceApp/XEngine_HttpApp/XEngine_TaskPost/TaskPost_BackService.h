#pragma once
void XCALLBACK HTTPTask_TaskPost_CBVideo(uint8_t* punStringY, int nYLen, uint8_t* punStringU, int nULen, uint8_t* punStringV, int nVLen, AVCOLLECT_TIMEINFO* pSt_TimeInfo, XPVOID lParam);
void XCALLBACK HTTPTask_TaskPost_CBAudio(uint8_t* punStringAudio, int nVLen, AVCOLLECT_TIMEINFO* pSt_TimeInfo, XPVOID lParam);

bool HTTPTask_TaskPost_BackService(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType);