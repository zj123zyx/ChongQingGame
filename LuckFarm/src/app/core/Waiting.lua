local Waiting = {}

Waiting.hasshow = false
Waiting.count = 0
Waiting.indicator = nil
Waiting.countScheduler = nil 

function Waiting.show()

    print("Waiting.show:",Waiting.count,Waiting.hasshow )

    Waiting.count = Waiting.count + 1
    if Waiting.hasshow == true then 
        return 
    end
    Waiting.hasshow = true

    if device.platform == "ios" then
        Waiting.showIos()
    elseif device.platform == "android" then
        Waiting.showAndroid()
    end
end

function Waiting.hide()
    print("Waiting.hide:",Waiting.count,Waiting.hasshow)

    Waiting.count = Waiting.count - 1

    if Waiting.count < 0 then Waiting.count = 0 end
    if Waiting.hasshow == false then return end
    if Waiting.count > 0 then return end

    if device.platform == "ios" then
        Waiting.hideIos()
    elseif device.platform == "android" then
        Waiting.hideAndroid()
    end

    Waiting.hasshow = false
end
function Waiting.hideAll()
    print("Waiting.hideAll:",Waiting.count,Waiting.hasshow)

    Waiting.count = 0

    if device.platform == "ios" then
        Waiting.hideIos()
    elseif device.platform == "android" then
        Waiting.hideAndroid()
    end

    Waiting.hasshow = false
end

function Waiting.forceHide()

    Waiting.count = 0
    Waiting.hasshow = false 

    if device.platform == "ios" then
        Waiting.hideIos()
    elseif device.platform == "android" then
        Waiting.hideAndroid()
    end
end

function Waiting.showIos()
    device.showActivityIndicator()

    Waiting.indicator = scn.ScnMgr.addView("CoverView")
    
    if Waiting.indicator then
        Waiting.indicator:setLocalZOrder(80000)
    end


    
    if  Waiting.countScheduler == nil then
        print("============加载定时器")
        Waiting.countScheduler = scheduler.performWithDelayGlobal(Waiting.waitTimeOut, 300)
    end
end

function Waiting.hideIos()
    device.hideActivityIndicator()
    if Waiting.indicator then
        scn.ScnMgr.removeView(Waiting.indicator)
        Waiting.indicator = nil
    end

    if Waiting.countScheduler ~= nil then 
        print("============卸载定时器")
        cc.Director:getInstance():getScheduler():unscheduleScriptEntry(Waiting.countScheduler)
        Waiting.countScheduler = nil
    end
end

function Waiting.showAndroid()
    -- if Waiting.hasshow == true then return end
    -- Waiting.hasshow = true
    AppLuaApi:showIndicator()
    if  Waiting.countScheduler == nil then
        print("============加载定时器")
        Waiting.countScheduler = scheduler.performWithDelayGlobal(Waiting.waitTimeOut, 20)
    end
end

function Waiting.hideAndroid()
    -- if Waiting.hasshow == false then return end
    --  Waiting.hasshow = false
    AppLuaApi:hideIndicator()
    if Waiting.countScheduler ~= nil then 
        print("============卸载定时器")
        cc.Director:getInstance():getScheduler():unscheduleScriptEntry(Waiting.countScheduler)
        Waiting.countScheduler = nil
    end
end

function Waiting.waitTimeOut()
    -- body
    Waiting.hideAll()
    scn.ScnMgr.addView("LabelCommonTipView","数据异常!")
end


return Waiting
