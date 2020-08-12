GameManager    = require("app.manager.GameManager")
-----------------------------------------------------------
-- MainScene 
-----------------------------------------------------------
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

MainScene.cellHeight=24.5
-----------------------------------------------------------
-- @Construct:
-- initData
-----------------------------------------------------------
function MainScene:ctor()
    self.ccbView = CCBuilderReaderLoad("ccb/MainScene.ccbi", self)
    self:addChild(self.ccbView)

    self:registerUIEvent()

    GameManager.loadQiDetailTable()

    self:setScene()

    -- print("ccbAniEnd()")
    -- ToolUtils.NewTimeKey()
    -- local tempTable = {}
    -- for i=1,20 do
    --     table.insert(tempTable,i)
    -- end
    -- local paraTb = {
    --     num1=0,
    --     num2=0,
    --     num3=0,
    --     num4=0,
    --     num5=0,
    --     num6=0,
    --     num7=0,
    --     num8=0,
    -- }
    -- for i=1,8 do
    --     local idx = ToolUtils.randRange(1, #tempTable)
    --     paraTb["num"..tostring(i)]=tempTable[idx]
    --     table.remove(tempTable, idx);
    -- end
    -- dump(paraTb)
end

function MainScene:setScene()
    self.m_upQiTxt:setString(tostring(GameManager.curQi))
    self:setQiTime()
    self:InitQiListScrollView()
    self:setDownInfo()
    self:setMissCntInfo()
    self:setLastRwdInfo()
    self:setHistory10Info()
    self:setIllustrationInfo()
    if GameManager.curQiTime<=0 then
        GameManager.curQiTime=600
    end
    if GameManager.curQiTime>30 then
        self:showViewByIdx(2)
    else
        self:showViewByIdx(1)
    end
end

function MainScene:registerUIEvent()
    ------------------------------------------------------------------------------------
    ----------------------------------------test----------------------------------------
    ------------------------------------------------------------------------------------
    core.displayEX.newButton(self.m_NetBtn):onButtonClicked(function() 
        release_print("self.m_NetBtn")
        self:showViewByIdx(1)
        ScnMgr.replaceScene("KaiJiangScene",{num1=17,num2=18,num3=19,num4=20,num5=1,num6=2,num7=3,num8=4})
        -- ScnMgr.popView("FruitShowView",{fruitNum=1})
        -- local cellNode = require("app.views.FruitShowView").new({fruitNum=1})
        -- self:addChild(cellNode)
    end)
    core.displayEX.newButton(self.m_IOSBtn):onButtonClicked(function() 
        release_print("self.m_IOSBtn")
        self:showViewByIdx(2)
    end)
    core.displayEX.newButton(self.m_AndroidBtn):onButtonClicked(function() 
        release_print("self.m_AndroidBtn")
        self:PlayVideo1("name","/storage/emulated/0/EnterGame.mp4")
    end)
    ------------------------------------------------------------------------------------
    ----------------------------------------test----------------------------------------
    ------------------------------------------------------------------------------------

end

function MainScene:showViewByIdx(_idx)
    self.m_videoNode:setVisible(false)
    self.m_missCntNode:setVisible(false)
    self.m_lastRwdNode:setVisible(false)
    self.m_history10Node:setVisible(false)
    self.m_illustrationNode:setVisible(false)
    release_print("MainScene:showViewByIdx(_idx)",_idx)
    if _idx then
        self.idx=_idx
    end
    if self.idx==1 then
        self.m_upScrollNode:setPositionY(600)
        local cellCount = self.betListContainer:getChildrenCount()
        local lastY = 0-self.betListContainer:getChildByTag(cellCount):getPositionY()
        print("lastY:" .. lastY)
        if lastY>0 then
            self.betListContainer:pos(0, lastY)
        end
    else
        if self.idx==2 then
            self.m_videoNode:setVisible(true)
            self:PlayVideo1("name","video/EnterGame.mp4")
        else
            if self.idx==3 then
                self.m_missCntNode:setVisible(true)
            elseif self.idx==4 then
                self.m_lastRwdNode:setVisible(true)
            elseif self.idx==5 then
                self.m_history10Node:setVisible(true)
            elseif self.idx==6 then
                self.idx=0
                self.m_illustrationNode:setVisible(true)
            end
            scheduler.performWithDelayGlobal(function()
                print("show next:" .. tostring(self.idx+1))
                self:showViewByIdx(self.idx+1)
            end, 5.0)
        end
        self.m_upScrollNode:setPositionY(202.0)
        local cellCount = self.betListContainer:getChildrenCount()
        local lastY = 0-(self.betListContainer:getChildByTag(cellCount):getPositionY()-(834-440))
        if lastY>0 then
            self.betListContainer:pos(0, lastY)
        end
    end
        
end

function MainScene:PlayVideo1(_type,path)
    local videoPath = path
    local videoPlayer = nil
    if _type=="name" then
        if device.platform == "android" then 
            videoPath="/storage/emulated/0/EnterGame.mp4"
            if io.exists(videoPath) then
                release_print(videoPath.." android video exists:yes!!!")
            else
                release_print(videoPath.." android video exists:no!!")
                -- self.m_videoNode:setVisible(false)
                self:showViewByIdx(3)
                return
            end
        -- elseif io.exists(videoPath) then
        --     release_print(videoPath.." video exists:yes!!!")
        -- else
        --     release_print(videoPath.." video exists:no!!!") 
        end
        --调用视频接口
        videoPlayer = ccexp.VideoPlayer:create()
        --载入视频文件
        videoPlayer:setFileName(videoPath)
    elseif _type=="url" then
        --调用视频接口
        videoPlayer = ccexp.VideoPlayer:create()
        --载入视频文件
        videoPlayer:setURL(videoPath)
    end
    --播放视频时是否始终保持款高比
    videoPlayer:setKeepAspectRatioEnabled(true)
    --是否全屏
    videoPlayer:setFullScreenEnabled(false)
    videoPlayer:setContentSize(cc.size(640 ,360))
    --开始播放
    videoPlayer:play()
    self.m_videoNode:addChild(videoPlayer, 9999)
    --回调监听
    videoPlayer:addEventListener(function(videoPlayer, eventType) 
        if eventType == ccexp.VideoPlayerEvent.PLAYING then
            release_print("PlayVideo1() PLAYING")
        elseif eventType == ccexp.VideoPlayerEvent.PAUSED then
            release_print("PlayVideo1() PAUSED")
        elseif eventType == ccexp.VideoPlayerEvent.STOPPED then
            release_print("PlayVideo1() STOPPED")
        elseif eventType == ccexp.VideoPlayerEvent.COMPLETED then
        --播放完成时处理回调
            release_print("PlayVideo1() COMPLETED")
            --先停止播放再延迟一段时间销毁视频。
            --若直接销毁会出现冲突问题。
            -- videoPlayer:stop()
            self:runAction(cc.Sequence:create(
                cc.DelayTime:create(0.01),
                cc.CallFunc:create(function() 
                    -- self:removeChild(videoPlayer)
                    videoPlayer:removeFromParent(true)
                    -- self.m_videoNode:setVisible(false)
                    self:showViewByIdx(3)
                end)
            ))      
        end
    end)
end

function MainScene:runAnimationByName(target, name)
    if target == nil then
        return false
    end
    if target.animationManager:getRunningSequenceName() == name then
        return false
    end
    target.animationManager:runAnimationsForSequenceNamed(name)

    return true
end

function MainScene:InitQiListScrollView()
    if self.qiListScroll~=nil then
        self.qiListScroll:removeFromParent(true)
        self.qiListScroll=nil
    end
    local rect = self.m_scrollContainer:getBoundingBox()
    self.betListContainer = cc.Node:create()
    self.betListContainer:setContentSize(cc.size(rect.width,rect.height))

    self.qiListScroll = cc.ui.UIScrollView.new({
        -- bgColor = cc.c4b(200, 200, 200, 120),
        viewRect = cc.rect(0,0,rect.width,rect.height)
    })-- 窗口的大小
    self.qiListScroll:addScrollNode(self.betListContainer)--设置显示内容
    self.qiListScroll:setDirection(cc.ui.UIScrollView.DIRECTION_VERTICAL) -- 设置滚动方向
    self.qiListScroll:onScroll(function ( event )
      -- event.name -- 滚动的状态  began moved ended 
      -- event.x
      -- event.y -- 
    end)
    self.qiListScroll:addTo(self.m_scrollContainer)

    self:addScrollList(self.betListContainer,MainScene.cellHeight)
end

function MainScene:addScrollList(_container,_cellHeight)
    print("BingoScene:addBetList")
    local cellCount = _container:getChildrenCount()
    release_print("child count:" .. cellCount)
    for i=1,cellCount do
        _container:getChildByTag(i):removeFromParent(true)
    end
    local cellPosY = _container:getBoundingBox().height-_cellHeight
    -- local cellCnt = ToolUtils.randRange(5, 20)

    for i=1,#GameManager.qiListTable do
        local cellNode = require("app.scenes.MainSceneCell").new({idx=i})
        cellNode:pos(0, cellPosY)
        _container:addChild(cellNode)
        cellNode:setTag(i)
        cellPosY=cellPosY-_cellHeight
    end
    local ContainerPosY = 0-cellPosY-_cellHeight
    if ContainerPosY>0 then
        _container:pos(0, ContainerPosY)
    end
end

function MainScene:setDownInfo()
    local maxRwdCnt = 0
    for i=1,#GameManager.qiSumTable do
        if GameManager.qiSumTable[i].rwdCnt>maxRwdCnt then
            maxRwdCnt = GameManager.qiSumTable[i].rwdCnt
        end
    end
    for i=1,#GameManager.qiSumTable do
        self["m_rwdCnt"..tostring(GameManager.qiSumTable[i].pos)]:setString(tostring(GameManager.qiSumTable[i].rwdCnt))
        self["m_missCnt"..tostring(GameManager.qiSumTable[i].pos)]:setString(tostring(GameManager.qiSumTable[i].maxMissCnt))
        self["m_rwdSpr"..tostring(GameManager.qiSumTable[i].pos)]:setScaleY(GameManager.qiSumTable[i].rwdCnt/maxRwdCnt)
    end
end

function MainScene:setMissCntInfo()
    for i=1,#GameManager.qiSumTable do
        self.m_missCntNode:getChildByTag(GameManager.qiSumTable[i].pos):setString(tostring(GameManager.qiSumTable[i].maxMissCnt))
    end
end

function MainScene:setLastRwdInfo()
    self.m_lastRwdQiTxt:setString(tostring(GameManager.lastRwdTable.qi))
    self.m_lastRwdTotalTxt:setString(tostring(GameManager.lastRwdTable.total).."元")
    for i=1,8 do
        local icon = dict_FruitTable[tostring(GameManager.lastRwdTable["num"..tostring(i)])].big_icon
        self["m_lastRwdNumSpr"..tostring(i)]:setSpriteFrame(display.newSpriteFrame(icon))
    end
    for i=1,5 do
        self["m_lastRwdTypeTxt"..tostring(i)]:setString(tostring(GameManager.lastRwdTable["rwdType"..tostring(i)]._type).."注")
        self["m_lastRwdValueTxt"..tostring(i)]:setString(tostring(GameManager.lastRwdTable["rwdType"..tostring(i)]._value).."元")
    end
end

function MainScene:setHistory10Info()
    for i=1,10 do
        local qiIdx = #GameManager.qiListTable-10+i
        local qiInfo = GameManager.qiListTable[qiIdx]
        self["m_historyCell"..tostring(i)]:getChildByTag(10):setString(tostring(qiInfo.qi))
        for j=1,8 do
            local icon = dict_FruitTable[tostring(qiInfo["num"..tostring(j)])].icon
            self["m_historyCell"..tostring(i)]:getChildByTag(j):setSpriteFrame(display.newSpriteFrame(icon))
        end
    end
end

function MainScene:setIllustrationInfo()

end

-- function MainScene:onBet(event) 
--     if event and event.game then
--         print("MainScene:onBet-->game:",event.game)
--     end
-- end

function MainScene:setQiTime()
    local timeStr = ""
    local min = math.floor(GameManager.curQiTime/60)
    if min<10 then
        timeStr = "0"..tostring(min)..":"
    else
        timeStr = tostring(min)..":"
    end
    local sec = GameManager.curQiTime%60
    if sec<10 then
        timeStr = timeStr.."0"..tostring(sec)
    else
        timeStr = timeStr..tostring(sec)
    end
    self.m_upTimeTxt:setString(timeStr)
end

function MainScene:updateTime(_dt)
    -- print("MainScene:updateTime")
    if GameManager.curQiTime>0 then
        GameManager.curQiTime=GameManager.curQiTime-1
        self:setQiTime()
    else
        -- print("MainScene:endTime")
        ScnMgr.replaceScene("WaitScene")
    end
    

end

function MainScene:onKaiJiangBack(event) 
    self:setScene()
end
-----------------------------------------------------------
-- onEnter
-----------------------------------------------------------
function MainScene:onEnter()
    print("MainScene:onEnter")
    -- audio.playMusic("audio/lobby.mp3")
    -- audio.setMusicVolume(0.3)
    EventMgr:addEventListener("onKaiJiangBack", handler(self, self.onKaiJiangBack))

    self.scheduleObj = scheduler.scheduleGlobal(function(dt)
        self:updateTime(dt)
    end, 1)
    self:updateTime(0)
end

-----------------------------------------------------------
-- onExit
-----------------------------------------------------------
function MainScene:onExit()
    print("MainScene:onExit")
    -- audio.stopMusic()
    EventMgr:removeEventListenersByEvent("onKaiJiangBack")

    scheduler.unscheduleGlobal(self.scheduleObj)
end

return MainScene

