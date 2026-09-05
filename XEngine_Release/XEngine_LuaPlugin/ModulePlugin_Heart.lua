function PluginCore_Init(pSt_PluginParameter)
    -- print("API Ver:", pSt_PluginParameter.APIVersion)
    -- print("XEngine Ver:", pSt_PluginParameter.XEngineVer)
    return true
end

function PluginCore_UnInit()
end

function PluginCore_Call(lpszStrUrl, nListCount, lpszMsgBuffer, nMsgLen)
    local OutputTable = {}

    if 0 == nListCount then
        PtszMsgBuffer = ""
    elseif nListCount > 0 then
        PtszMsgBuffer = "{\"code\":0,\"msg\":\"success\"}"
    else
        PtszMsgBuffer = "{\"code\":1002,\"msg\":\"type does not support\"}"
    end

    return OutputTable, PtszMsgBuffer, #PtszMsgBuffer, true
end

function PluginCore_GetInfo()

    ptszPluginName = "heart"
    ptszPluginVersion = "1.0.0.1001"
    ptszPluginAuthor = "xengine"
    ptszPluginDesc = "heartbeat handle for XEngine API Service"

    return ptszPluginName, ptszPluginVersion, ptszPluginAuthor, ptszPluginDesc
end