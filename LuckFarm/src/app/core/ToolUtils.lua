
local ToolUtils = {}
ToolUtils.socket = require "socket"

function ToolUtils.rtd(r)
	return r * 180 / math.pi
end

function ToolUtils.dta(d)
	return d * math.pi / 180
end

function ToolUtils.NewTimeKey()
    local time_helper = require("app.core.time_helper")--require "time_helper"
    local a = time_helper.current_time_millis()
    print("NewTimeKey:"..tostring(a))
end

ToolUtils.lastRandTime=0
function ToolUtils.randRange(min, max)
    -- math.randomseed(tostring(os.time()*10000):reverse():sub(1, 6))  
    
    for i=1,10000 do
        local x = i
    end
    local cur_time = ToolUtils.socket.gettime()
    local use_time = ((cur_time - ToolUtils.lastRandTime )*1000)%1
    print("use_time:"..use_time)
    ToolUtils.lastRandTime=cur_time

    -- local randRangeTime = cur_time*10000
    -- print("randRange:"..use_time(randRangeTime))
    -- math.randomseed(tostring(randRangeTime):reverse():sub(1, 6))  

    local randRangeTime = math.ceil(use_time*1000000)
    print("randRangeTime:"..randRangeTime)
    math.randomseed(tostring(randRangeTime))  

    math.random()
    math.random()
    math.random()

    if min == nil and max == nil then
        return math.random()
    end
    
    return math.floor(math.random() * (max - min + 1)) + min
end

function ToolUtils.getRotationByPoint(p1, p2, length)

    local angle = math.atan2(p2.y-p1.y, p2.x-p1.x)
    local ox = math.sin(angle)*length
    local oy = math.cos(angle)*length

    return {x=ox, y=oy}
end

function ToolUtils.getRotation(x1, y1, x2, y2)

    local angle = math.atan2(y2-y1, x2-x1)
    local degree = ToolUtils.rtd(angle)

    return degree
end

--二点距离，未开方 
function ToolUtils.dist(x1, y1, x2, y2)
    return (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1)
end

--二点距离，开方 
function ToolUtils.dist2(p1, p2)
    local dist = ToolUtils.dist(p1.x,p1.y,p2.x,p2.y)
    return math.sqrt(dist)
end

function ToolUtils.getTenThousandPer( num )
    -- body
    return num / 10000
end


function ToolUtils.formatLongTextNumber(val)

    local numTxt = tostring(val)

    local subnum1 =  val / 1000 
    local subnum2 = math.floor( val / 1000000 ) 

    local subStr = function( subnum )
        -- body
        local str = tostring(subnum)
        local len = string.len(str)

        if len >= 4 and idx2 ~= 4 then
            str = string.sub(str,1,4)
        end

        len = string.len(str)
        
        if string.sub(str,len) == '.' then
            str = string.sub(str,1,len-1)
        end

        return str
    end

    if math.floor(subnum1) > 1 and math.floor(subnum2) <= 1 then
        numTxt = subStr(subnum1).."K"
    elseif math.floor(subnum2) > 1 then
        numTxt = subStr(subnum2).."M"
    end

    return numTxt
    
end

function ToolUtils.formatTimer(isecs)

    local minsec = isecs - math.ceil(isecs)
    isecs = math.ceil(isecs)

    local function formatSTR(num)
        if num < 10 then
            num = '0'..num
        end
        return num
    end

    local hor = math.modf(isecs/(60 * 60))
    local min = math.modf((isecs - hor * 60 * 60)/60)
    local sec = isecs - hor * 60 * 60 - min * 60
    local subsec = math.abs(math.ceil(minsec*100))

    local horStr = formatSTR(hor)
    local minStr = formatSTR(min)
    local secStr = formatSTR(sec)
    local subsecStr = formatSTR(subsec)

    local timeStr = "00:00:00"

    if hor > 24 then
        local day = math.modf(hor/24)
        local hours = hor - day * 24

        if day > 1 then 
            timeStr = day..' days '
        else
            timeStr = day..' day '
        end

        if hours > 1 then 
            timeStr = timeStr..hours..' hours '
        else
            timeStr = timeStr..hours..' hour '
        end

    elseif hor < 24 and hor >= 1 then
        timeStr = horStr..':'..minStr..':'..secStr
    elseif hor < 1 and (sec > 0 or min > 0)then
        timeStr = minStr..':'..secStr..':'..subsecStr
    end

    return timeStr
end

function ToolUtils.shortContent(str, cnt)
    local shortContent = str
    if string.len(shortContent) > 80 then
        shortContent = string.sub(shortContent, 1, 80).."......"
    end

    return shortContent

end

function ToolUtils.flipPoker(pokerFront, pokerBack, time,  backcall)

    local orbitTime = 1

    if time then
        orbitTime = time
    end

    pokerFront:setVisible(false)

    pokerFront:setScaleX(0)
    local orbitFront = cc.ScaleTo:create(orbitTime, 1.0, 1.0)--cc.OrbitCamera:create(orbitTime, 1, 0, 270, 90, 0, 0)
    local sequenceFront = cc.Sequence:create(cc.Show:create(), orbitFront)
    local targetFront = cc.TargetedAction:create(pokerFront, sequenceFront)
    pokerBack:setScaleX(1)
    local orbitBack = cc.ScaleTo:create(orbitTime, 0, 1.0)--cc.OrbitCamera:create(orbitTime, 1, 0, 0, 90, 0, 0)
    
    pokerBack:runAction(cc.Sequence:create(orbitBack, cc.Hide:create(), targetFront, 
        cc.CallFunc:create(function()
            -- body
            if backcall then backcall() end
            end)
        ));  

end

-- 输出表格式的日志 jjf
function ToolUtils.printTable(prefix, table, maxlevel, level, key)

    level = level or 1

    local indent = prefix
    for i = 1, level do
        indent = indent.."\t"
    end

    if key ~= nil then
        print(indent..key.." ".."=")
    end

    print(indent.."{")

    for k, v in pairs(table) do
        if type(k) == "table" then
            k = tostring(k)
        end

        if type(v) == "table" then
            if maxlevel ~= nil and maxlevel >= level + 1 then
                ToolUtils.printTable(prefix, v, maxlevel, level + 1, k)
            else
                print(string.format("%s%s = {...}", indent.."\t", tostring(k)))
            end
        else
            print(string.format("%s%s = %s", indent.."\t", tostring(k), tostring(v)))
        end
    end
    
    print(indent.."}")
end

function ToolUtils.callJavaFun(string)  --调用android的方法实现
    if device.platform == "android" then
        local str = tostring(string)
        --release_print(str)
        
        --包名/类名  这个可以在对应的android工程的manifest中得到 
        local className="org/cocos2dx/lua/AppActivity" --"org/cocos2dx/lua/LuaJavaHelper" 
        local args = { str }  
        local sigs = "(Ljava/lang/String;)V" --传入string参数，无返回值  
        local ret1,ret2 = luaj.callStaticMethod(className,"luaCallJavaFun",args) 
    else
        release_print("device.platform != android")
        release_print("function ToolUtils.callJavaFun(string) ==============> return!!!")
    end
         
    
end

function callFromCppWithRet(_funName,_param)
    local funName = tostring(_funName)
    local _param = tostring(_param)
    release_print("callFromCppWithRet:"..funName..",_param:".._param)
    return _param
end

function callFromCpp(_funName,_result)
    local funName = tostring(_funName)
    local result = tostring(_result)
    release_print("【callFromCpp】funName:"..funName..",result:"..result)
    EventMgr:dispatchEvent({ name  = "onEvent", game = result, })
end

return ToolUtils