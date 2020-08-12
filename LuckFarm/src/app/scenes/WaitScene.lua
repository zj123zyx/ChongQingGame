-----------------------------------------------------------
-- WaitScene 
-----------------------------------------------------------
local WaitScene = class("WaitScene", function()
    return display.newScene("WaitScene")
end)

-----------------------------------------------------------
-- @Construct:
-- initData
-----------------------------------------------------------
function WaitScene:ctor()
    self.ccbView = CCBuilderReaderLoad("ccb/WaitScene.ccbi", self)
    self:addChild(self.ccbView)

end
function WaitScene:ccbAniEnd()
    print("ccbAniEnd()")
    local tempTable = {}
    for i=1,20 do
        table.insert(tempTable,i)
    end
    local paraTb = {
        num1=0,
        num2=0,
        num3=0,
        num4=0,
        num5=0,
        num6=0,
        num7=0,
        num8=0,
    }
    for i=1,8 do
        local idx = ToolUtils.randRange(1, #tempTable)
        paraTb["num"..tostring(i)]=tempTable[idx]
        table.remove(tempTable, idx);
    end
    dump(paraTb)
    ScnMgr.replaceScene("KaiJiangScene",paraTb)--{num1=9,num2=10,num3=11,num4=12,num5=13,num6=14,num7=15,num8=16}
end

function WaitScene:runAnimationByName(target, name)
    if target == nil then
        return false
    end
    if target.animationManager:getRunningSequenceName() == name then
        return false
    end
    target.animationManager:runAnimationsForSequenceNamed(name)

    return true
end

-----------------------------------------------------------
-- onEnter
-----------------------------------------------------------
function WaitScene:onEnter()
    print("WaitScene:onEnter")
end

-----------------------------------------------------------
-- onExit
-----------------------------------------------------------
function WaitScene:onExit()
    print("WaitScene:onExit")
end

return WaitScene

