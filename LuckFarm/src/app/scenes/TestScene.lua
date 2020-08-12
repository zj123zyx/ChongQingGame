-----------------------------------------------------------
-- TestScene 
-----------------------------------------------------------
local TestScene = class("TestScene", function()
    return display.newScene("TestScene")
end)

-----------------------------------------------------------
-- @Construct:
-- initData
-----------------------------------------------------------
function TestScene:ctor()
    self.ccbView = CCBuilderReaderLoad("ccb_new/TestScene.ccbi", self)
    self:addChild(self.ccbView)

    self:registerUIEvent()

    
end

function TestScene:registerUIEvent()
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
function TestScene:onEnter()
    print("TestScene:onEnter")
end

-----------------------------------------------------------
-- onExit
-----------------------------------------------------------
function TestScene:onExit()
    print("TestScene:onExit")
end

return TestScene

