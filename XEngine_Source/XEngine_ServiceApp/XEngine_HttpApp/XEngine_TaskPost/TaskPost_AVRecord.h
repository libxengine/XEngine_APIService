#pragma once
void XCALLBACK HTTPTask_TaskPost_CBVideo(XHANDLE*** pppSt_AVBuffer, XPVOID lParam);
void XCALLBACK HTTPTask_TaskPost_CBAudio(XHANDLE*** pppSt_AVBuffer, XPVOID lParam);

bool HTTPTask_TaskPost_AVRecordStart(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType);
bool HTTPTask_TaskPost_AVRecordStop(LPCXSTR lpszClientAddr);