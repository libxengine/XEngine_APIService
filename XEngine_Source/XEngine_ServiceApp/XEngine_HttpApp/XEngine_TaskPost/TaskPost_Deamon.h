﻿#pragma once

void XCALLBACK HTTPTask_TaskPost_Thread();
bool HTTPTask_TaskPost_Deamon(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen);