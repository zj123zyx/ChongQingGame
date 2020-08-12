-- K3Manager    = require("app.scenes.K3Manager")
-----------------------------------------------------------
-- MainSceneCell 
-----------------------------------------------------------
local MainSceneCell = class("MainSceneCell", function()
    return display.newNode()
end)


-----------------------------------------------------------
-- @Construct:
-- initData
-----------------------------------------------------------
function MainSceneCell:ctor(para)
    self.ccbView = CCBuilderReaderLoad("ccb/MainSceneCell.ccbi", self)
    self:addChild(self.ccbView)
    -- release_print("MainSceneCell",para.idx)
    self.idx=tonumber(para.idx)
    self.info = GameManager.qiListTable[self.idx]
    -- dump(self.info)
    self.m_qiTxt:setString(tostring(self.info.qi))

    for i=1,8 do
        local oneNum = self.info["num"..tostring(i)]
        local coinSpr1 = display.newSprite("#"..dict_FruitTable[tostring(oneNum)].icon)
        coinSpr1:setScale(0.45)
        coinSpr1:setPosition(13*(i-1),0)
        self.m_kjNode:addChild(coinSpr1)

        local coinSpr2 = display.newSprite("#"..dict_FruitTable[tostring(oneNum)].icon)
        coinSpr2:setScale(0.7)
        self.m_zsNode:getChildByTag(dict_FruitTable[tostring(oneNum)].pos):addChild(coinSpr2)
    end
        
    self:registerUIEvent()
end

function MainSceneCell:registerUIEvent()
    ------------------------------------------------------------------------------------
    ----------------------------------------test----------------------------------------
    ------------------------------------------------------------------------------------
    -- core.displayEX.newButton(self.m_NetBtn):onButtonClicked(function() 
    --     release_print("self.m_NetBtn")
    --     --self:httpGet()
    -- end)
    -- core.displayEX.newButton(self.m_IOSBtn):onButtonClicked(function() 
    --     release_print("self.m_IOSBtn")
    --     self:PlayVideo1("name","video/EnterGame.mp4")
    -- end)
    -- core.displayEX.newButton(self.m_AndroidBtn):onButtonClicked(function() 
    --     release_print("self.m_AndroidBtn")
    --     self:PlayVideo1("name","/storage/emulated/0/EnterGame.mp4")
    -- end)
    ------------------------------------------------------------------------------------
    ----------------------------------------test----------------------------------------
    ------------------------------------------------------------------------------------

end

return MainSceneCell

