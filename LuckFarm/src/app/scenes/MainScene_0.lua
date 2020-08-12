-- K3Manager    = require("app.scenes.K3Manager")
-----------------------------------------------------------
-- MainScene_0 
-----------------------------------------------------------
local MainScene_0 = class("MainScene_0", function()
    return display.newScene("MainScene_0")
end)


-----------------------------------------------------------
-- @Construct:
-- initData
-----------------------------------------------------------
function MainScene_0:ctor()
    self.ccbView = CCBuilderReaderLoad("ccb/MainScene_0.ccbi", self)
    self:addChild(self.ccbView)

    self:registerUIEvent()
    -- self:setVideoPlayer()
end

function MainScene_0:registerUIEvent()
    ------------------------------------------------------------------------------------
    ----------------------------------------test----------------------------------------
    ------------------------------------------------------------------------------------
    core.displayEX.newButton(self.m_NetBtn):onButtonClicked(function() 
        release_print("self.m_NetBtn")
        --self:httpGet()
    end)
    core.displayEX.newButton(self.m_IOSBtn):onButtonClicked(function() 
        release_print("self.m_IOSBtn")
        self:PlayVideo1("name","video/EnterGame.mp4")
    end)
    core.displayEX.newButton(self.m_AndroidBtn):onButtonClicked(function() 
        release_print("self.m_AndroidBtn")
        self:PlayVideo1("name","/storage/emulated/0/EnterGame.mp4")
    end)
    ------------------------------------------------------------------------------------
    ----------------------------------------test----------------------------------------
    ------------------------------------------------------------------------------------

end

function MainScene_0:httpGet()
    local url = "http://172.21.32.97:8888/NetTest/test.php"
    local request = network.createHTTPRequest(function(event)
        self:onResponseGet(event)
    end, url, "GET")
    request:setTimeout(30)
    request:start()
end

function MainScene_0:onResponseGet(event)
    -- dump(event)
    local request = event.request
    if event.name ~= "completed" then -- 當為completed表示正常結束此事件
        release_print("request:getErrorCode(), request:getErrorMessage() ", request:getErrorCode(), request:getErrorMessage())
        return 
    end
     
    local code = request:getResponseStatusCode()
    if code ~= 200 then -- 成功
        release_print("code ", code)
        return 
    end
     
    local strResponse = string.trim(request:getResponseString())
    self:playVideo(strResponse)
    -- EventMgr:dispatchEvent({
    --             name  = "playVideo",
    --             para = strResponse,
    --         })
end

function MainScene_0:playVideo(event)
    -- dump(event)
    local paraStr = event--event.para
    local index = string.find(paraStr, "-", 0)
    local para1 = string.sub(paraStr, 0, index-1)
    local para2 = string.sub(paraStr, index+1, string.len(paraStr))
    release_print("para1:"..para1..",para2:"..para2)
    if para1=="1" then
        self:PlayVideo1("name",para2)
    elseif para1=="2" then
        self:PlayVideo1("url",para2)
    end
end

function MainScene_0:PlayVideo1(_type,path)
    local videoPlayer = nil
    if _type=="name" then
        if io.exists(path) then
            release_print(path.." exists:yes!!!")
        elseif device.platform == "android" then 
            release_print(path.." exists:no!!")
            return
        end
        --调用视频接口
        videoPlayer = ccexp.VideoPlayer:create()
        --载入视频文件
        videoPlayer:setFileName(path)
    elseif _type=="url" then
        --调用视频接口
        videoPlayer = ccexp.VideoPlayer:create()
        --载入视频文件
        videoPlayer:setURL(path)
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
                    -- self:doComplete()
                end)
            ))      
        end
    end)
end

function MainScene_0:runAnimationByName(target, name)
    if target == nil then
        return false
    end
    if target.animationManager:getRunningSequenceName() == name then
        return false
    end
    target.animationManager:runAnimationsForSequenceNamed(name)

    return true
end

-- function MainScene_0:onBet(event) 
--     if event and event.game then
--         print("MainScene_0:onBet-->game:",event.game)
--     end
-- end

-- function MainScene_0:updateTime(_dt)
--     print("MainScene_0:updateTime")
-- end
-----------------------------------------------------------
-- onEnter
-----------------------------------------------------------
function MainScene_0:onEnter()
    print("MainScene_0:onEnter")
    -- audio.playMusic("audio/lobby.mp3")
    -- audio.setMusicVolume(0.3)
    EventMgr:addEventListener("playVideo", handler(self, self.playVideo))

    -- self.scheduleObj = scheduler.scheduleGlobal(function(dt)
    --     self:updateTime(dt)
    -- end, 1)
    -- self:updateTime(0)
end

-----------------------------------------------------------
-- onExit
-----------------------------------------------------------
function MainScene_0:onExit()
    print("MainScene_0:onExit")
    -- audio.stopMusic()
    EventMgr:removeEventListenersByEvent("playVideo")

    -- scheduler.unscheduleGlobal(self.scheduleObj)
end

return MainScene_0

