--[[
Descripttion: nothing
version: V1.0.0
Author: chenfang
Date: 2020-08-14 09:26:39
LastEditors: chenfang
LastEditTime: 2020-08-17 15:30:07
--]]
-----------------------------------------------------------
-- NetTestScene 
-----------------------------------------------------------

require("app.init")

local NetTestScene = class("NetTestScene", function()
    return display.newScene("NetTestScene")
end)

-----------------------------------------------------------
-- @Construct:
-- initData
-----------------------------------------------------------
function NetTestScene:ctor()
    self.ccbView = CCBuilderReaderLoad("ccb_new/NetTestScene.ccbi", self)
    self:addChild(self.ccbView)

    self:registerNetEvent();

    self:registerUIEvent()

    --连接网络
    core.sktMgr:ConnectServer();

end

--注册网络监听相关的事件
function NetTestScene:registerNetEvent()
    

end

function NetTestScene:registerUIEvent()
    ------------------------------------------------------------------------------------
    ----------------------------------------test----------------------------------------
    ------------------------------------------------------------------------------------
    core.displayEX.newButton(self.m_testBtn1):onButtonClicked(function() 
        release_print("self.m_testBtn1")
    end)


    core.displayEX.newButton(self.m_testBtn2):onButtonClicked(function() 
        release_print("self.m_testBtn2")
    end)

    core.displayEX.newButton(self.m_testBtn3):onButtonClicked(function() 
        release_print("self.m_testBtn3")
    end)

    core.displayEX.newButton(self.m_testBtn4):onButtonClicked(function() 
        release_print("self.m_testBtn4")
    end)
    
    core.displayEX.newButton(self.m_testBtn5):onButtonClicked(function() 
        release_print("self.m_testBtn5")
    end)

    ------------------------------------------------------------------------------------
    ----------------------------------------test----------------------------------------
    ------------------------------------------------------------------------------------

end

-----------------------------------------------------------
-- onEnter
-----------------------------------------------------------
function NetTestScene:onEnter()
    print("NetTestScene:onEnter")
end

-----------------------------------------------------------
-- onExit
-----------------------------------------------------------
function NetTestScene:onExit()
    print("NetTestScene:onExit")
end

return NetTestScene

