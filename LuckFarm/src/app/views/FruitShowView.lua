-----------------------------------------------------------
-- FruitShowView 
-----------------------------------------------------------
local FruitShowView = class("FruitShowView", function()
    return display.newNode()
end)
FruitShowView.obj=nil
-----------------------------------------------------------
-- @Construct:
-- initData
-----------------------------------------------------------
function FruitShowView:ctor(_param)
    print("FruitShowView:ctor()")
    -- dump(_param,"_param")
    FruitShowView.obj=self
    self.fruitNum=_param.fruitNum
    self.posNum=_param.posNum

    self.ccbView = CCBuilderReaderLoad("ccb/FruitShowView.ccbi", self)
    self:addChild(self.ccbView)
    self.aniState=1

    local icon = "fruit_name_"..tostring(self.fruitNum)..".png"
    self.m_nameSpr:setSpriteFrame(display.newSpriteFrame(icon))

    local icon = "fruit_"..tostring(self.fruitNum).."_"..tostring(self.aniState)..".png"
    self.m_fruitSpr:setSpriteFrame(display.newSpriteFrame(icon))

    --EventMgr
    -- EventMgr:addEventListener("KaiJiangEvent", handler(self, self.KaiJiangEvent))
    
    self:runAnimationByName(self.ccbView,"pos"..tostring(self.posNum))
end

function FruitShowView:showAniEnd()
    EventMgr:dispatchEvent({
                name  = "onCCBFun",
                funType = "FruitShowView",
            })
end

function FruitShowView:runAnimationByName(target, name)
    if target == nil then
        print("runAnimationByName target == nil")
        return false
    end
    if target.animationManager:getRunningSequenceName() == name then
        print("runAnimationByName target.animationManager:getRunningSequenceName() == ",target.animationManager:getRunningSequenceName())
        -- return false
    end
    target.animationManager:runAnimationsForSequenceNamed(name)

    return true
end



-- function FruitShowView:KaiJiangEvent(event)
--     print("FruitShowView:KaiJiangEvent()")
--     self:closeView()
-- end
function FruitShowView:ccbFruitChange()
    print("FruitShowView:ccbFruitChange()")
    FruitShowView.obj.aniState=FruitShowView.obj.aniState+1
    local icon = "fruit_"..tostring(FruitShowView.obj.fruitNum).."_"..tostring(FruitShowView.obj.aniState)..".png"
    -- local icon = "fruit_1/fruit_1_1.png"--"/PicRes/fruits/fruit_1/fruit_1_1.png"
    FruitShowView.obj.m_fruitSpr:setSpriteFrame(display.newSpriteFrame(icon))
end

-----------------------------------------------------------
-- onEnter
-----------------------------------------------------------
function FruitShowView:onEnter()
    print("FruitShowView:onEnter")
    -- audio.playMusic("fish/audio/bg_01.mp3")
    
end

-----------------------------------------------------------
-- onExit
-----------------------------------------------------------
function FruitShowView:onExit()
    print("FruitShowView:onExit")
    -- audio.stopMusic()
end

return FruitShowView

