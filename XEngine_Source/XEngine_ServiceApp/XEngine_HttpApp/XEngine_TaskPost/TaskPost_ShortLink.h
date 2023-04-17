#pragma once

bool HTTPTask_TaskPost_SLProxy(LPCXSTR lpszClientAddr, LPCXSTR lpszUriStr, XCHAR*** ppptszHDRList, int nHDRCount);
bool HTTPTask_TaskPost_ShortLink(LPCXSTR lpszClientAddr, LPCXSTR lpszMsgBuffer, int nMsgLen, int nType);