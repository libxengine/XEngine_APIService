#pragma once

void CALLBACK XEngine_HTTPTask_P2PCallback(XENGINE_P2XPPEER_PROTOCOL* pSt_P2PProtocol, XPVOID lParam);
XBOOL XEngine_HTTPTask_P2PClient(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int unOperatorCode);