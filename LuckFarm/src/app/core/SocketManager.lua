
local SocketManager = class("SocketManager")

local sktMgr = SocketManager

GAME_HEART_EVENT = 300100
GAME_SERVERTIME_EVENT = 300101
GAME_INFO_EVENT = 300111
GAME_DRAWNUM_EVENT = 300151


local startIdx = 6

local error_code = {
    { errkey = -1,    errmsg = "系统错误"},
    { errkey = -1014, errmsg = "无效的游戏期号"},
    { errkey = -1015, errmsg = "无效的游戏ID"},
    { errkey = -1140, errmsg = "游戏期不在销售状态"},
    { errkey = -1141, errmsg = "游戏未到开始销售时间"},
    { errkey = -1142, errmsg = "游戏超出销售结束时间"},
    { errkey = -1302, errmsg = "取中奖信息错，请稍后重试"},
    { errkey = -1305, errmsg = "当前时间没有在销售时间内，不做新期初始化"},
    { errkey = -1311, errmsg = "还没到开奖时间"},
    { errkey = -1312, errmsg = "开奖还没有结束，禁止查询"},
    { errkey = -1313, errmsg = "投注站号不属于指定渠道"},
    { errkey = -1318, errmsg = "通讯停止"},
}

function sktMgr.init()
    core.SocketNet:init()
end

function sktMgr.isError(key)

    for k,v in pairs(error_code) do
        if v.errkey == tonumber(key) then
            print(v.errkey,v.errmsg)
            return true, v.errmsg
        end
    end

    return false, ""

end


function sktMgr.totime(val)

    if true then return val end

    print(val)
    --20190513095000
    local yearVal = tonumber(string.sub(val,1,4))
    local monthVal = tonumber(string.sub(val,5,6))
    local dayVal = tonumber(string.sub(val,7,8))
    local hourVal = tonumber(string.sub(val,9,10))
    local minuteVal = tonumber(string.sub(val,11,12))
    local secondVal = tonumber(string.sub(val,13,14))

    print(yearVal,monthVal,dayVal,hourVal,minuteVal,secondVal)

    local tVal = os.time({day=dayVal, month=monthVal, year=yearVal, hour=hourVal, min=minuteVal, sec=secondVal})

    print(tVal,os.time({day=dayVal, month=monthVal, year=yearVal, hour=hourVal, min=minuteVal, sec=secondVal}))

    return tVal

end

function sktMgr.getGameInfo(gameID, callfunction)
    print("sktMgr.getGameInfo()")
    local function callBack(rdata)
        --101448;0;0;0;18112300011024;8;181123096;1;20181123165500;20181123170000;20181123170005;
        print("sktMgr.getGameInfo callBack rdata:")
        dump(rdata)
        local state,msg = sktMgr.isError(rdata[7])

        local gameInfo = {}
        gameInfo.state = state
        gameInfo.msg = msg

        if gameInfo.state == false then

            gameInfo.startSaleTime = sktMgr.totime(rdata[startIdx])
            gameInfo.endSaleTime = sktMgr.totime(rdata[startIdx+1])
            gameInfo.drawTime = sktMgr.totime(rdata[startIdx+2])
            gameInfo.issue = rdata[startIdx+3]
            gameInfo.lastIssue = rdata[startIdx+5]
 
            gameInfo.serverCurTime = rdata[startIdx+6]

        end

        callfunction(gameInfo)

    end

    -- 86&300111

    local req = "0;0;0;0;0;"..tostring(gameID)..";-1;;"

    core.SocketNet:sendMessage(GAME_INFO_EVENT, GAME_INFO_EVENT, req, callBack, false)

end

function sktMgr.getDrawNum(gameID, issue, callfunction)
    
    local function callBack(rdata)
        --101454;0;0;0;18112300011026;8;181123095;20;1;1;01;1;2;02;1;3;03;1;4;04;1;5;05;1;6;06;1;7;07;1;8;08;1;9;09;1;10;10;1;11;41;1;12;42;1;13;43;1;14;44;1;15;45;1;16;46;1;17;47;1;18;48;1;19;49;1;20;50;

        local state,msg = sktMgr.isError(rdata[7])

        local drawInfo = {}
        drawInfo.state = state
        drawInfo.msg = msg

        if drawInfo.state == false then

            drawInfo.gameID = rdata[startIdx+1]
            drawInfo.issue = rdata[startIdx+2]
            drawInfo.winNumCount = rdata[startIdx+3]
            drawInfo.winNumVal = {}

            for i=1,drawInfo.winNumCount do
                drawInfo.winNumVal[tostring(rdata[startIdx+3+3*(i-1)+2])] = tonumber(rdata[startIdx+3+3*(i-1)+3])
            end
            
        end

        callfunction(drawInfo)

    end

    local req = "0;0;0;0;0;"..tostring(gameID)..";"..tostring(issue)..";"


    core.SocketNet:sendMessage(GAME_DRAWNUM_EVENT, GAME_DRAWNUM_EVENT, req, callBack, false)

end

function sktMgr.getServerTime(gameID, callfunction)
    print("sktMgr.getServerTime()")
    local function callBack(rdata)
        -- 101448;0;0;0;18112300011024;8;181123096;1;20181123165500;20181123170000;20181123170005;
        -- print("sktMgr.getServerTime callBack rdata:")
        -- dump(rdata)

        local state,msg = sktMgr.isError(rdata[7])

        local timeTal = {}
        timeTal.state = state
        timeTal.msg = msg

        if timeTal.state == false then

            timeTal.server_time = rdata[startIdx+1]
            timeTal.serverTime = sktMgr.totime(rdata[startIdx+1])

        end

        callfunction(timeTal)
    end
    local req = "0;0;0;0;0;"--..tostring(gameID)..";-1;;"

    core.SocketNet:sendMessage(GAME_SERVERTIME_EVENT, GAME_SERVERTIME_EVENT, req, callBack, false)

end


function sktMgr.heartMsg()
    print("sktMgr.heartMsg()")
    local function callBack(rdata)
    end
    local req = "0;0;0;0;0;"

    core.SocketNet:sendMessage(GAME_HEART_EVENT, GAME_HEART_EVENT, req, callBack, false)

end

return SocketManager