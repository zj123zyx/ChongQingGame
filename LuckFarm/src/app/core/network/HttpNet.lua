local HttpNet = {}

HttpNet.connectErrCode = "9999"

-- local serverurl = "http://httpbin.org/post"

-- local serverurl = "http://202.105.127.10:20200/"
local serverurl = "http://192.168.0.188:20200/"

-- local serverurlRewardHistory = "10.36.0.84:8080/ids/transaction/" -- 正式的
local serverurlRewardHistory = "http://xq7yer.natappfree.cc/ids/transaction"
-- local resget = "https://183.62.200.201:17788/download/getResourceInfo"
--[[
jsonTable:json lua table
iCallbackFunction:回调函数
]]



function HttpNet.sendCommonMessage(jsonTable, iCallbackFunction)

    local ipAddress = cc.UserDefault:getInstance():getStringForKey("socket_addr")

    local url = serverurl

    if ipAddress and  string.len(ipAddress) < 16 and  string.len(ipAddress) >= 7 then
        url = "http://"..ipAddress..":20200/"
    end
    
    local jsonPacket = json.encode(jsonTable)

    HttpNet.sendJsonDataAsync(url,jsonPacket, iCallbackFunction)
end


-- function HttpNet.sendCommonMessage(jsonTable, iCallbackFunction)

--     local ipAddress = cc.UserDefault:getInstance():getStringForKey("socket_addr")

--     local url = resget
    
--     local jsonPacket = json.encode(jsonTable)

--     HttpNet.sendJsonDataAsync(url,jsonPacket, iCallbackFunction)
-- end

-- 获取历史走势接口  因为跟渠道不是公用一个ip sort，所以单独列出一个接口
function HttpNet.sendCommonMessageToGetRHistory(jsonTable, iCallbackFunction)

    local ipAddress = cc.UserDefault:getInstance():getStringForKey("socket_addr_rHis")

    local url = serverurlRewardHistory

    if ipAddress and  string.len(ipAddress) < 16 and  string.len(ipAddress) >= 7 then
        url = "http://"..ipAddress..":8080/ids/transaction"
    end
    
    -- 测试服务器 正式的时候需要注掉
    url = serverurlRewardHistory

    local jsonPacket = json.encode(jsonTable)

    HttpNet.sendJsonDataAsync(url,jsonPacket, iCallbackFunction)
end


--发送json到服务器
function HttpNet.sendJsonDataAsync(url, jsonPacket, iCallbackFunction)

    local xhr = cc.XMLHttpRequest:new()

    xhr.responseType = cc.XMLHTTPREQUEST_RESPONSE_JSON
    xhr:setRequestHeader("Content-Type", "application/json")

    xhr:open("POST", url)

    xhr.timeout = 5

    local function onHttpCallback()
        if xhr.readyState == 4 and (xhr.status >= 200 and xhr.status < 207) then
            
            local response   = xhr.response

            -- print( "----------------start--------------------")
            -- print(response)
            -- print( "-----------------end-------------------")


            local output = json.decode(response,1)
            
            -- table.foreach(output,function(i, v) print (i, v) end)
            -- print("headers are")
            -- table.foreach(output.headers,print)

            -- dump(output, " ++++ +++ ++++")
            iCallbackFunction(output)
        else
            -- http连接失败，模仿服务器返回错误码
            iCallbackFunction({
                content = {},
                code = HttpNet.connectErrCode,
                msg = "网络错误信息,请重新尝试连接",
            })
        end
    end

    print("jsonPacket :",jsonPacket)

    xhr:registerScriptHandler(onHttpCallback)
    xhr:send(jsonPacket)
end


return HttpNet
