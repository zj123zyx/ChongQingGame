scheduler = require(cc.PACKAGE_NAME .. ".scheduler")

-- data = require("app.data.init")
-- scn = require("app.scenes.lobby.init") 
ScnMgr = require("app.core.SceneManager")
EventMgr = require("app.event.EventManager").instance()
core = require("app.core.init") 
AppBase = require("framework.cc.mvc.AppBase")
-- require("app.login.AnySdkUserInfo")
require("app.dict.dictTable")

-- --公用方法
-- ErrorTipViewShow = function(scene,Msg)
--     if Msg or Msg == "" then
--         if scene:getChildByTag(999) then
--             scene:removeChildByTag(999)
--         end
--         local TipView = require("app.views.TipView").new(Msg)
--         TipView:setTag(999)
--         scene:addChild(TipView,998)
--     end
-- end

-- ShowLoadingLayer = function(scene)
--     if scene:getChildByTag(888) then
--         scene:removeChildByTag(888)
--     end
--     local NetLoadView = require("app.views.NetLoadView").new()
--     NetLoadView:setTag(888)
--     scene:addChild(NetLoadView,888)
-- end

-- HideLoadingLayer = function(scene)
--     if scene:getChildByTag(888) then
--         scene:removeChildByTag(888)
--     end
-- end


-- JudgeAllMusic = function()
-- 	local model = app:getUserModel()
--     local cls = model.class
--     local properties = model:getProperties({cls.noticeSign})
--     return  tonumber(properties[cls.noticeSign])
-- end

  
-- --公用变量
-- ADS_COUNT = 5 --广告数量
-- COUSTOMER_CALL = "020-87304860" --客服电话
-- TONGGAO_URL = "http://58.22.103.139:8066/msg/msg"
-- DEFINE_HEIGHT = 1136
-- DEFINE_WIDTH = 640
-- SHOW_ANIMATION = true


-- 初始化anysdk
-- if device.platform == "android" then
--     LoginManager = require("app.login.LoginAndroid").new()
-- else
-- 	LoginManager = require("app.login.LoginIos").new()
-- end
-- require("app.anysdkConst")
require("app.res")

