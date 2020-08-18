local ccnet = require("framework.cc.net.init")

local SocketNet = class("SocketNet")

function SocketNet:ctor()
    --self:init()
end

--初始化方法，程序启动时初始化一次
function SocketNet:init()

    local time = ccnet.SocketTCP.getTime()
   -- print("socket time:" .. time)

    local socket = ccnet.SocketTCP.new()
    socket:setName("SocketTcp")
    socket:setTickTime(0.1)
    socket:setReconnTime(6)
    socket:setConnFailTime(4)

    socket:addEventListener(ccnet.SocketTCP.EVENT_DATA, handler(self, self.tcpData))
    socket:addEventListener(ccnet.SocketTCP.EVENT_CLOSE, handler(self, self.tcpClose))
    socket:addEventListener(ccnet.SocketTCP.EVENT_CLOSED, handler(self, self.tcpClosed))
    socket:addEventListener(ccnet.SocketTCP.EVENT_CONNECTED, handler(self, self.tcpConnected))
    socket:addEventListener(ccnet.SocketTCP.EVENT_CONNECT_FAILURE, handler(self, self.tcpConnectedFail))

    self.socket_ = socket
    
    self:ConnectServer()

    self.requests = {}

    self.netErrorViewOpen = false

    self.netReceiveData = nil

    self.connectCnt = 0

end

function SocketNet:ConnectServer()
    
    -- core.Waiting.show()

    local socket_addr = cc.UserDefault:getInstance():getStringForKey("socket_addr")
    -- local socket_port = cc.UserDefault:getInstance():getStringForKey("socket_port")


    -- socket_addr = "10.37.0.209"
    socket_port = "21001"
    -- socket_port = "21001"
    --10.8.0.104:21001
    --10.37.0.209:21001

    if socket_addr and  string.len(socket_addr) < 16 and  string.len(socket_addr) >= 7 then
        print("socket_addr is right!!!")
    else
        socket_addr = "10.37.0.209"
        -- socket_addr = "192.168.0.188"
    end


    print("socket_addr", socket_addr, socket_port,string.len(socket_addr))

    --self.socket_:connect(socket_addr, socket_port, false) --122.0.71.122   8081
    -- self.socket_:connect("newvegas.acejoy.cn", "8081", false)
    --self.socket_:connect("10.36.0.67", "20009", false)

    self.socket_:connect(socket_addr, socket_port, false) --122.0.71.122   8081

end

function SocketNet:enterGame()

end

function SocketNet:isConnected()
    return self.socket_.isConnected
end

function SocketNet:isNeedWaiting()
    for k,v in pairs(self.requests) do
        if k ~= nil and v ~= nil then
            if v.needwait == true and v.count > 0 then
                return true
            end
        end
    end
    return false
end


function SocketNet:resetRequests()
    for k,v in pairs(self.requests) do
        if k ~= nil and v ~= nil then
            if v.global == false then
                v.count = 0
            end
        end
    end

    self.requestting = false
    -- app.logining = false
    -- core.Waiting.forceHide()
end

function SocketNet:removeReq(itype,rtype)

    for k,v in pairs(self.requests) do
        if k ~= nil and v ~= nil and k == itype then

            if v.global == true then
                if v.count > 0 then v.count = v.count - 1 end
            else
                if v.rType == rtype and v.count > 0 then

                    if v.needwait==true then
                        core.Waiting.hide()
                    end

                    v.count = v.count - 1
                    -- print("收到数据", rtype, v.needwait, v.count)

                    return
                end
            end

        end
    end
end

function SocketNet:handleRequestType(rtype)

    for k,v in pairs(self.requests) do

        if k ~= nil and v ~= nil then
            
            if v.rType == rtype and v.count > 0 then

                if v.global == false then
                    self.requestting = false
                    self:removeReq(k, rtype)
                end

                return v.callback

            end
        end
    end

    return nil

end

function SocketNet:tcpData(event)
    -- print("-----tcpData--1",string.char(event.data[1]))
    -- print("-----tcpData--1",string.char(event.data[2]))

    event.data = core.DataBuilder.removeChar(event.data)

    if self.netReceiveData then
        event.data = self.netReceiveData..event.data
    end
    print("-----tcpData--",event.data)
    -- print("-----tcpData--2",string.char(event.data[2]))

    local itype, body, datanext = core.DataBuilder.getPacketBody(event.data)

    -- print("data sub:", datanext)

    local reNum = 0

    while itype and body do

        reNum = reNum + 1

        local callbackFun = self:handleRequestType(itype)

        if nil ~= callbackFun then

            callbackFun(string.split(body, ';'))

        else

            if itype == 999999 then
                
                local dataarray = string.split(event.data, ';')

                local callbackFun = self:handleRequestType(tonumber(dataarray[6]))

                -- print("error back:",dataarray[6],callbackFun)

                if nil ~= callbackFun then
                    callbackFun(string.split(event.data, ';'))
                end
            else
                print("not found callbackFun by type:"..itype)
            end
            -- self:sendBackMessage(tostring(itype),"999999","")
        end

        itype, body, datanext = core.DataBuilder.getPacketBody(datanext)

    end

    self.netReceiveData = datanext

end

function SocketNet:ReConnectInit()
    self:resetRequests()
end

function SocketNet:tcpClose()
    print("SocketTCP close")

    -- if self.connectCnt < 10 then

    --     scheduler.performWithDelayGlobal(function()
    --         core.SocketNet:ConnectServer()
    --         self.connectCnt = self.connectCnt + 1
    --     end,5)

    --     return
    -- end

    self:resetRequests()
    -- core.Waiting.forceHide()

    EventMgr:dispatchEvent({name = EventMgr.SOCKET_CONNECT_ERROR})

    if self.netErrorViewOpen == false then

        local netview = ScnMgr.addView("NetErrorView",
        {
            callback = function()
                self.netErrorViewOpen = false
                core.SocketNet:ConnectServer()
            end
        })

        self.netErrorViewOpen = true

        self.connectCnt = 0

    end 
end

function SocketNet:tcpClosed()
    print("SocketTCP closed",EventMgr.SOCKET_CONNECT_ERROR)
    EventMgr:dispatchEvent({name = EventMgr.SOCKET_CONNECT_ERROR})
end

function SocketNet:tcpConnected()
    print("SocketTCP connect success",EventMgr.SOCKET_CONNECT_EVENT)
    -- core.Waiting.hide()
    
    EventMgr:dispatchEvent({ name  = EventMgr.SOCKET_CONNECT_EVENT  })

end

function SocketNet:tcpConnectedFail()
    print("SocketTCP connect fail")
    --core.Waiting.hide()
    -- core.Waiting.forceHide()
    -- if self.connectCnt < 10 then

    --     scheduler.performWithDelayGlobal(function()
    --         core.SocketNet:ConnectServer()
    --         self.connectCnt = self.connectCnt + 1
    --     end,1)

    -- end
    if self.netErrorViewOpen == false then

        local netview = ScnMgr.addView("NetErrorView",
        {
            callback = function()
                self.netErrorViewOpen = false
                core.SocketNet:ConnectServer()
            end
        })

        self.netErrorViewOpen = true

        self.connectCnt = 0

    end 
end

--停止发送和接收数据
function SocketNet:stop()
    self.socket_:close()
end

function SocketNet:registEvent(iType, callback)

    if self.requests[tostring(iType)] == nil then
        self.requests[tostring(iType)] = {}
    end

    self.requests[tostring(iType)].count=1
    self.requests[tostring(iType)].global=true
    self.requests[tostring(iType)].callback=callback
    self.requests[tostring(iType)].needwait=false
    self.requests[tostring(iType)].rType=iType

end

function SocketNet:unregistEvent(iType)
    self:removeReq(iType)
end

-- add request to queue
function SocketNet:sendMessage(iType, rType, bodyData, callback, needwait, forceMove)

    --print("发送数据  ", iType, rType)

    if self:isConnected() then

        if callback then

            if self.requests[tostring(iType)] == nil then
                self.requests[tostring(iType)] = {}
                self.requests[tostring(iType)].global=false
                self.requests[tostring(iType)].count=0
            end

            --self.requests[tostring(iType)].protoObj=protoObj
            self.requests[tostring(iType)].rType=rType
            --self.requests[tostring(iType)].passportId=passportId
            self.requests[tostring(iType)].callback=callback
            self.requests[tostring(iType)].needwait=needwait
            self.requests[tostring(iType)].global=false
            
            local count = self:requestBackHandleCount(iType)

            if self.requests[tostring(iType)].count ~= count then

                self.requests[tostring(iType)].count = count

                if needwait == true then
                    core.Waiting.show()
                end
            end

        end

        self:sendCommonMessage(iType,bodyData)
        
    end

end

function SocketNet:requestBackHandleCount(iType)

    local requetObj = {}

    for k,v in pairs(self.requests) do
        if k ~= nil and v ~= nil then
            if v.rType and tonumber(iType) == tonumber(k) then
                requetObj[v.rType] = iType
            elseif v.rType == nil and tonumber(iType) == tonumber(k) then
                requetObj["nil"] = iType
            end
        end
    end
    
    return table.nums(requetObj)
end

function SocketNet:sendBackMessage(iType,iBody,str)

    if self:isConnected() then
        local packet=core.DataBuilder.buildPacket(iType,iBody,str)

        if packet and string.len(packet) > 0 then
            self.socket_:send(packet)
        end
        
    end
    
end

function SocketNet:heartMsg()

    if self:isConnected() then
        local packet=core.DataBuilder.buildStream(GAME_HEART_EVENT,"")
        -- print("packet",packet)
        self.socket_:send(packet)
    end
    
end

function SocketNet:sendCommonMessage(iType, iBody)
    local packet=core.DataBuilder.buildStream(iType,iBody)
    -- print("packet:",packet)
    self.socket_:send(packet)
end
 
return SocketNet
