#pragma once

void CALLBACK XEngine_HTTPTask_P2PCallback(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol, LPVOID lParam);
BOOL XEngine_HTTPTask_P2PClient(LPCTSTR lpszClientAddr, LPCTSTR lpszMsgBuffer, int nMsgLen, int unOperatorCode);