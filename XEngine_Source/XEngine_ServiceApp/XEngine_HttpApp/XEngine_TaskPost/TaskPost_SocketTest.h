﻿#pragma once

void XCALLBACK HTTPTask_TastPost_CBSocketTest(XNETHANDLE xhToken, LPCXSTR lpszAddr, int nPort, __int64x nNumber, __int64x nFailed, __int64x nSuccess, int nStatus, XPVOID lParam);
bool HTTPTask_TastPost_SocketTest(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType);