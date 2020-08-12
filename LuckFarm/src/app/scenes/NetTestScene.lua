-----------------------------------------------------------
-- NetTestScene 
-----------------------------------------------------------
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

    self:registerUIEvent()

    
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

