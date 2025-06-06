function PluginCore_Init(pSt_PluginParameter)
    -- print("API Ver:", pSt_PluginParameter.APIVersion)
    -- print("XEngine Ver:", pSt_PluginParameter.XEngineVer)
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

function PluginCore_GetInfo()

    ptszPluginName = "heart"
    ptszPluginVersion = "1.0.0.1001"
    ptszPluginAuthor = "xengine"
    ptszPluginDesc = "heartbeat handle for XEngine API Service"

    return ptszPluginName, ptszPluginVersion, ptszPluginAuthor, ptszPluginDesc
end