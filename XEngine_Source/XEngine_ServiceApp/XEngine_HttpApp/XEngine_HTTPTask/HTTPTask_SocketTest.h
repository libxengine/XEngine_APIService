#pragma once

void CALLBACK XEngine_HTTPTask_CBSocketTest(XNETHANDLE xhToken, LPCSTR lpszAddr, int nPort, __int64x nNumber, __int64x nFailed, __int64x nSuccess, int nStatus, LPVOID lParam);
BOOL XEngine_HTTPTask_SocketTest(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, int nType);