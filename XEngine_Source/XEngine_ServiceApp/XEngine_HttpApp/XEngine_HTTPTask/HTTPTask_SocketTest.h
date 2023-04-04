#pragma once

void CALLBACK XEngine_HTTPTask_CBSocketTest(XNETHANDLE xhToken, LPCSTR lpszAddr, int nPort, __int64x nNumber, __int64x nFailed, __int64x nSuccess, int nStatus, XPVOID lParam);
XBOOL XEngine_HTTPTask_SocketTest(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType);