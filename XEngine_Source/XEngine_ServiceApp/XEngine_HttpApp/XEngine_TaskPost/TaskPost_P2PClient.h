#pragma once

void XCALLBACK HTTPTask_TastPost_P2PCallback(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol, XPVOID lParam);
bool HTTPTask_TastPost_P2PClient(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int unOperatorCode);