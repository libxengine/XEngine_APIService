#pragma once

XBOOL HTTPTask_TaskPost_SLProxy(LPCXSTR lpszClientAddr, LPCXSTR lpszUriStr, XCHAR*** ppptszHDRList, int nHDRCount);
XBOOL HTTPTask_TaskPost_ShortLink(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType);