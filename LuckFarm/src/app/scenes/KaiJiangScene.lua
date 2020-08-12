-----------------------------------------------------------
-- KaiJiangScene 
-----------------------------------------------------------
local KaiJiangScene = class("KaiJiangScene", function()
    return display.newScene("KaiJiangScene")
end)
KaiJiangScene.aniState=1
KaiJiangScene.numState=1
-----------------------------------------------------------
-- @Construct:
-- initData
-----------------------------------------------------------
function KaiJiangScene:ctor(_para)
    self.para=_para
    -- dump(self.para)
    self.ccbView = CCBuilderReaderLoad("ccb/KaiJiangScene.ccbi", self)
    self:addChild(self.ccbView)

    self:registerUIEvent()

    KaiJiangScene.aniState=1
    KaiJiangScene.numState=1
end

function KaiJiangScene:registerUIEvent()
    ------------------------------------------------------------------------------------
    ----------------------------------------test----------------------------------------
    ------------------------------------------------------------------------------------
    core.displayEX.newButton(self.m_NetBtn):onButtonClicked(function() 
        release_print("self.m_NetBtn")
        ScnMgr.replaceScene("MainScene")
        -- self:runAnimationByName(self.ccbView,"run")
        -- local coinSpr1 = display.newSprite("#fruit_t8.png")
        --     coinSpr1:setAnchorPoint(cc.p(0.5,0.5))
        --     coinSpr1:setScale(0.5)
        --     self["m_fruitNode1"]:addChild(coinSpr1)
    end)
    ------------------------------------------------------------------------------------
    ----------------------------------------test----------------------------------------
    ------------------------------------------------------------------------------------

end

function KaiJiangScene:runAnimationByName(target, name)
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

function KaiJiangScene:ccbChangeFruitSpr()
    print("ccbChangeFruitSpr()")
    EventMgr:dispatchEvent({
                name  = "onCCBFun",
                funType = "ccbChangeFruitSpr",
            })
end

function KaiJiangScene:ccbShowNum()
    print("ccbShowNum()")
    EventMgr:dispatchEvent({
                name  = "onCCBFun",
                funType = "ccbShowNum",
            })
end

function KaiJiangScene:ccbAniEnd()
    print("ccbAniEnd()")
    EventMgr:dispatchEvent({
                name  = "onCCBFun",
                funType = "ccbAniEnd",
            })
end

function KaiJiangScene:onCCBFun(event) 
    if event then
        if event.funType=="ccbAniEnd" then
            print("ccbAniEnd-->KaiJiangScene.aniState:",KaiJiangScene.aniState)
            if KaiJiangScene.aniState<=1 then
                self:runAnimationByName(self.ccbView,"run")
            elseif KaiJiangScene.aniState==2 then
                self:runAnimationByName(self.ccbView,"fruit_"..tostring(self.para["num1"]))
            elseif KaiJiangScene.aniState<=3 then
                self:runAnimationByName(self.ccbView,"run")
            elseif KaiJiangScene.aniState==4 then
                self:runAnimationByName(self.ccbView,"fruit_"..tostring(self.para["num2"]))
            elseif KaiJiangScene.aniState<=5 then
                self:runAnimationByName(self.ccbView,"run")
            elseif KaiJiangScene.aniState==6 then
                self:runAnimationByName(self.ccbView,"fruit_"..tostring(self.para["num3"]))
            elseif KaiJiangScene.aniState<=7 then
                self:runAnimationByName(self.ccbView,"run")
            elseif KaiJiangScene.aniState==8 then
                self:runAnimationByName(self.ccbView,"fruit_"..tostring(self.para["num4"]))
            elseif KaiJiangScene.aniState<=9 then
                self:runAnimationByName(self.ccbView,"run")
            elseif KaiJiangScene.aniState==10 then
                self:runAnimationByName(self.ccbView,"fruit_"..tostring(self.para["num5"]))
            elseif KaiJiangScene.aniState<=11 then
                self:runAnimationByName(self.ccbView,"run")
            elseif KaiJiangScene.aniState==12 then
                self:runAnimationByName(self.ccbView,"fruit_"..tostring(self.para["num6"]))
            elseif KaiJiangScene.aniState<=13 then
                self:runAnimationByName(self.ccbView,"run")
            elseif KaiJiangScene.aniState==14 then
                self:runAnimationByName(self.ccbView,"fruit_"..tostring(self.para["num7"]))
            elseif KaiJiangScene.aniState<=15 then
                self:runAnimationByName(self.ccbView,"run")
            elseif KaiJiangScene.aniState==16 then
                self:runAnimationByName(self.ccbView,"fruit_"..tostring(self.para["num8"]))
            end
            KaiJiangScene.aniState=KaiJiangScene.aniState+1
        elseif event.funType=="ccbShowNum" then
            print("ccbShowNum-->KaiJiangScene.numState:",KaiJiangScene.numState)
            -- if KaiJiangScene.numState==1 then
                -- ScnMgr.popView("FruitShowView",{fruitNum=1})--,{fruitNum=1}
                local curNum = self.para["num"..tostring(KaiJiangScene.numState)]
                local cellNode = require("app.views.FruitShowView").new({fruitNum=curNum,posNum=KaiJiangScene.numState})
                cellNode:setTag(10)
                self:addChild(cellNode)
            -- end
        elseif event.funType=="ccbChangeFruitSpr" then
            local curNum = self.para["num"..tostring(KaiJiangScene.numState)]
            local icon = "fruit_s_t"..tostring(curNum)..".png"
            self["fruit_t"..tostring(curNum)]:setSpriteFrame(display.newSpriteFrame(icon))
        elseif event.funType=="FruitShowView" then
            if self:getChildByTag(10) then
                self:getChildByTag(10):removeFromParent(true)
            end
            -- if KaiJiangScene.numState==1 then
                local curNum = self.para["num"..tostring(KaiJiangScene.numState)]
                local fruitSpr = display.newSprite("#fruit_t"..tostring(curNum)..".png")
                fruitSpr:setScale(0.8)
                self["m_fruitNode"..tostring(KaiJiangScene.numState)]:addChild(fruitSpr)
                local nameSpr = display.newSprite("#fruit_name_"..tostring(curNum)..".png")
                nameSpr:setScale(0.25)
                nameSpr:pos(0,-62)
                self["m_fruitNode"..tostring(KaiJiangScene.numState)]:addChild(nameSpr)
            -- end
            if KaiJiangScene.numState<8 then
                KaiJiangScene.numState=KaiJiangScene.numState+1
            else
                self:runAnimationByName(self.ccbView,"end")
                scheduler.performWithDelayGlobal(function()
                    ScnMgr.replaceScene("MainScene")
                end, 8.0)
            end
        end
    end
            
end

-- function KaiJiangScene:updateTime(_dt)
--     print("KaiJiangScene:updateTime")
-- end
-----------------------------------------------------------
-- onEnter
-----------------------------------------------------------
function KaiJiangScene:onEnter()
    print("KaiJiangScene:onEnter")
    -- audio.playMusic("audio/lobby.mp3")
    -- audio.setMusicVolume(0.3)
    EventMgr:addEventListener("onCCBFun", handler(self, self.onCCBFun))

    -- self.scheduleObj = scheduler.scheduleGlobal(function(dt)
    --     self:updateTime(dt)
    -- end, 1)
    -- self:updateTime(0)
end

-----------------------------------------------------------
-- onExit
-----------------------------------------------------------
function KaiJiangScene:onExit()
    print("KaiJiangScene:onExit")
    -- audio.stopMusic()
    EventMgr:removeEventListenersByEvent("onCCBFun")
    KaiJiangScene.aniState=1
    KaiJiangScene.numState=1
    EventMgr:dispatchEvent({ name  = "onKaiJiangBack" })
    -- scheduler.unscheduleGlobal(self.scheduleObj)
end

return KaiJiangScene

