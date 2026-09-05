#pragma once
void XCALLBACK HTTPTask_TaskPost_CBVideo();
void XCALLBACK HTTPTask_TaskPost_CBAudio();

bool HTTPTask_TaskPost_AVRecordStart(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen);
bool HTTPTask_TaskPost_AVRecordStop(LPCXSTR lpszClientAddr);