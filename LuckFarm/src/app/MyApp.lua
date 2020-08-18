--[[
Descripttion: nothing
version: V1.0.0
Author: chenfang
Date: 2020-08-14 09:26:39
LastEditors: chenfang
LastEditTime: 2020-08-17 14:59:15
--]]
require("config")
require("cocos.init")
require("framework.init")
require("app.init")

-- Notification = require "app.core.Notification"

-- require('app.core.util.LuaXml')

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
    MyApp.super.ctor(self)
    core.sktMgr.init()
    -- self:init()
end

-- function MyApp:init() --初始化


-- end

function MyApp:run()
    cc.FileUtils:getInstance():addSearchPath("res/")
    -- --创建图片缓存
    -- if cc.SpriteFrameCache:getInstance():getSpriteFrame("fruit_1_1.png")==nil then
    --     print("load:Common_3")
    --     display.addSpriteFrames("PicRes/Common_3.plist","PicRes/Common_3.pvr.ccz")
    -- end
    -- if cc.SpriteFrameCache:getInstance():getSpriteFrame("fruit_20_1.png")==nil then
    --     print("load:Common_4")
    --     display.addSpriteFrames("PicRes/Common_4.plist","PicRes/Common_4.pvr.ccz")
    -- end
    self:preStart()
    -- ScnMgr.replaceScene("MainScene")
    ScnMgr.replaceScene("NetTestScene")--NetTestScene

end

function MyApp:preStart()
    local onTick = function(dt)

        if  self.slotCycle then
            self.slotCycle.sTime = self.slotCycle.sTime + dt
        end
        
        ScnMgr.show()
        
    end
    
    self.schedulerEntry = cc.Director:getInstance():getScheduler():scheduleScriptFunc(onTick, 0, false)
    -- Notification.registNotification()

    -- location notice
    -- AppNotification:sharedAppNotification():cancelAllLocalNotifications()
    -- AppNotification:sharedAppNotification():RegisterLocalNotification("10:46:00","slot location notification")
end


return MyApp
