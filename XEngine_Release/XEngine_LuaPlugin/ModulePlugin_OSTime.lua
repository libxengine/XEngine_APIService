function PluginCore_Init(pSt_PluginParameter)
    -- print("API Ver:", pSt_PluginParameter.APIVersion)
    -- print("XEngine Ver:", pSt_PluginParameter.XEngineVer)
    return true
end

function PluginCore_UnInit()
end

function PluginCore_URLSqlit(str,reps)
    local resultStrList = {}
    string.gsub(str,'[^'..reps..']+',function (w)
        table.insert(resultStrList,w)
    end)
    return resultStrList
end

function PluginCore_Call(ParamsTable, nListCount, lpszMsgBuffer, nMsgLen)
    local OutputTable = {}

    if nListCount < 1 then
        local PInt_HTTPCode = 200
        local PtszMsgBuffer = "{\"code\":1001,\"msg\":\"request parament is incorrent\"}"
        return OutputTable, PtszMsgBuffer, #PtszMsgBuffer, true
    end

    local tszValue = 0
    local HDRObjectType = PluginCore_URLSqlit(ParamsTable[1], '=')

    if '0' == HDRObjectType[2] then
        tszValue = os.date("%Y-%m-%d %H:%M:%S")
    elseif '1' == HDRObjectType[2] then
        tszValue = os.clock()
    elseif '2' == HDRObjectType[2] then
        tszValue = os.time()
    else
        PInt_HTTPCode = 200
        PtszMsgBuffer = "{\"code\":1002,\"msg\":\"type does not support\"}"
        return OutputTable, PtszMsgBuffer, #PtszMsgBuffe, true
    end

    local PInt_HTTPCode = 200
    local PtszMsgBuffer = "{\"code\":0,\"msg\":\"success\",\"data\":{\"Time\":\"" .. tszValue .. "\"}}"

    return OutputTable, PtszMsgBuffer, #PtszMsgBuffer, true
end

function PluginCore_GetInfo()

    ptszPluginName = "time"
    ptszPluginVersion = "1.0.0.1001"
    ptszPluginAuthor = "xengine"
    ptszPluginDesc = "get time info for XEngine API Service"

    return ptszPluginName, ptszPluginVersion, ptszPluginAuthor, ptszPluginDesc
end
-- PluginCore_Call("",0,"",0)