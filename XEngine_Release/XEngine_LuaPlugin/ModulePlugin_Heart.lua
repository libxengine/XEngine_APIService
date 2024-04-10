function PluginCore_Init()
    return true
end

function PluginCore_UnInit()
end

function PluginCore_Call(lpszStrUrl, nListCount, lpszMsgBuffer, nMsgLen)

    if 0 == nListCount then
        PInt_HTTPCode = 200
        PInt_MsgLen = 0
    elseif nListCount > 0 then
        PInt_HTTPCode = 200
        PtszMsgBuffer = "{\"code\":0,\"msg\":\"success\"}"
        PInt_MsgLen = #PtszMsgBuffer
    else
        PInt_HTTPCode = 200
        PtszMsgBuffer = "{\"code\":1002,\"msg\":\"type does not support\"}"
        PInt_MsgLen = #PtszMsgBuffer
    end

    return true
end