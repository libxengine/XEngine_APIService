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


function PluginCore_Call(lpszStrUrl, nListCount, lpszMsgBuffer, nMsgLen)
    if nListCount < 3 then
        PInt_HTTPCode = 200
        PtszMsgBuffer = "{\"code\":1001,\"msg\":\"request parament is incorrent\"}"
        PInt_MsgLen = #PtszMsgBuffer
        return true
    end

    local nValue = 0
    local HDRArray = PluginCore_URLSqlit(lpszStrUrl,'&')
    local HDRObjectValue1 = PluginCore_URLSqlit(HDRArray[1],'=')
    local HDRObjectValue2 = PluginCore_URLSqlit(HDRArray[2],'=')
    local HDRObjectType = PluginCore_URLSqlit(HDRArray[3],'=')

    if '0' == HDRObjectType[2] then
        nValue = HDRObjectValue1[2] + HDRObjectValue2[2]
    elseif '1' == HDRObjectType[2] then
        nValue = HDRObjectValue1[2] - HDRObjectValue2[2]
    elseif '2' == HDRObjectType[2] then
        nValue = HDRObjectValue1[2] * HDRObjectValue2[2]
    elseif '3' == HDRObjectType[2] then
        nValue = HDRObjectValue1[2] / HDRObjectValue2[2]
    else
        PInt_HTTPCode = 200
        PtszMsgBuffer = "{\"code\":1002,\"msg\":\"type does not support\"}"
        PInt_MsgLen = #PtszMsgBuffer
        return true
    end

    PInt_HTTPCode = 200
    PtszMsgBuffer = "{\"code\":0,\"msg\":\"success\",\"data\":{\"nType\":" .. HDRObjectType[2] .. ",\"nValue1\":" .. HDRObjectValue1[2] .. ",\"nValue2\":" .. HDRObjectValue2[2] .. ",\"nCal\":" .. nValue .. "}}"
    PInt_MsgLen = #PtszMsgBuffer

    return true
end

function PluginCore_GetInfo()

    ptszPluginName = "cal"
    ptszPluginVersion = "1.0.0.1001"
    ptszPluginAuthor = "xengine"
    ptszPluginDesc = "math cal for XEngine API Service"

    return ptszPluginName, ptszPluginVersion, ptszPluginAuthor, ptszPluginDesc
end

-- PluginCore_Call("param1=1&param2=2&param3=0",3,"hello",5)