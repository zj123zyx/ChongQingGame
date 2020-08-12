touchLayer = require("app.scenes.TouchLayer")

local sm = class("SceneManager")

sm.showPools = {}
sm.showingView = nil
sm.viewNode = nil
sm.greyLayer = nil

--------------------------------------
-- replaceScene showType 1=直接切换
--------------------------------------
function sm.replaceScene(sceneName, args, showType)
    -- local nextScene = require("app." .. sceneName).new(args and args[1] or {})
    -- if showType == 1 or showType == nil or showType == true then
    --     cc.Director:getInstance():replaceScene(nextScene)
    -- else
    --     local transition = nil
    --     if showType == 2 then --创建一个从右边推入覆盖的过渡动画
    --         transition = cc.TransitionMoveInR:create(0.3,nextScene)
    --     elseif showType == 3 then -- 创建一个从左边推入覆盖的过渡动画
    --         transition = cc.TransitionMoveInL:create(0.3,nextScene)
    --     elseif showType == 4 then -- 创建一个从顶部推入覆盖的过渡动画
    --         transition = cc.TransitionMoveInT:create(0.3,nextScene)
    --     elseif showType == 5 then -- 创建一个从底部推入覆盖的过渡动画
    --         transition = cc.TransitionMoveInB:create(0.3,nextScene)
    --     elseif showType == 6 then -- 本场景从左到右消失同时另一场景出现
    --         transition = cc.TransitionProgressHorizontal:create(0.3,nextScene)
    --     end
    --     cc.Director:getInstance():replaceScene(transition)
    -- end
    
    if showloading ~= nil and showloading == true then
        sm.showPools[#sm.showPools + 1] = {name="lobby.LoadingPage", type="scene",value= {sceneName,args}}
    else
        sm.showPools[#sm.showPools + 1] = {name=sceneName, type="scene", value= args }
    end
end

--------------------------------------
-- addView
--------------------------------------
function sm.addTopView(View,scene,args)--view 弹出框 scene父节点  args参数
    local topview = require("app.views." .. View).new(args)
    scene:addChild(topview,888)


end

-- function sm.addTopView( className, oldview, ... )
    
--     local view = nil

--     if sm.viewNode ~= nil then

--         view = app:createSView(className, ... )
--         view.pop = false
--         view.top = true
--         sm.viewNode:addChild( view )

--         if oldview then view.showingAddView = oldview end

--         if view.showingAddView then

--             local posX, posY = view:getPosition()
--             view:setPositionX(posX + display.width)

--             transition.moveBy(view, {x = -display.width, time = 0.35})
--             transition.moveBy(view.showingAddView, {x = -display.width, time = 0.35})
--         end

--     end
--     return view
-- end
--------------------------------------
-- addView
--------------------------------------
function sm.removeTopView( topview )

    if topview.showingAddView then

        local showingAddView = topview.showingAddView

        transition.moveBy(topview, {x = display.width, time = 0.35, onComplete = function()
                topview:removeSelf()
            end})
        transition.moveBy(showingAddView, {x = display.width, time = 0.35})
    else
        topview:removeSelf()
    end

end

--------------------------------------
-- addView
--------------------------------------
function sm.addView( className, ... )
    local view = nil
    if sm.viewNode ~= nil then
        view = app:createSView(className, ... )
        view.pop = false
        sm.viewNode:addChild( view )
    end
    return view
end

--------------------------------------
-- addView
--------------------------------------
function sm.addViewEx( className, ... )
    local view = nil
    if sm.viewNode ~= nil then
        view = app:createSView(className, ... )
        view.pop = false
        sm.viewNode:addChild( view )
    end
    return view
end

--------------------------------------
-- addView
--------------------------------------
function sm.removeView( view )
    
    if view.top and view.top == true then
        sm.removeTopView( view )
        return
    end

    if view.pop == nil then
        sm.shownext(view.nextshow)
    end
    view:removeSelf()
end

--------------------------------------
-- PopView
--------------------------------------
function sm.popView( className, args )
    -- print("sm.popView ",className)
    if sm.showingView ~= nil then
        local nextview = sm.showingView.nextshow
        local newshow = {name=className, type="view", value= args }
        newshow.nextshow = nextview

        local tempview = newshow
        local tempshows = {}
        
        while tempview ~= nil do
            tempshows[#tempshows + 1] = tempview
            tempview = tempview.nextshow
        end

        local sortFunc = function(a, b)
            return tonumber(sm.getPriority(a)) > tonumber(sm.getPriority(b))
        end

        table.sort(tempshows, sortFunc)
        
        for i=2,#tempshows do
            local show = tempshows[i-1]
            local nextshow = tempshows[i]
            nextshow.nextshow = nil
            show.nextshow = nextshow
        end
        
        local showingnext = tempshows[1]

        sm.showingView.obj.nextshow = showingnext
        sm.showingView.nextshow = showingnext

    else
        sm.showPools[#sm.showPools + 1] = {name=className, type="view", value= args }
    end
end

function sm.shownext(nextshow)

    print("sm.shownext", nextshow)
    sm.showingView = nil

    if nextshow ~= nil then
        if nextshow.type == "view" then
            print("View: ",nextshow.name)
            local view = app:createSView(nextshow.name, nextshow.value )
            view.nextshow = nextshow.nextshow

            if nextshow.value ~= nil and nextshow.value.event ~= nil then
                local event = nextshow.value.event
                view:addEventListener(event.name,    event.func,    event.target)
            end

            -- local scn = display.getRunningScene()
            if sm.viewNode ~= nil then
                sm.viewNode:addChild(view)
                nextshow.obj = view
                sm.showingView = nextshow
            end

        elseif nextshow.type == "scene" then
            print("Scene: ",nextshow.name)
            sm.preEnter()

            local scn = app:enterScene(nextshow.name, nextshow.value)
            -- dump(nextshow.value,"nextshow.value")
            sm.viewNode = touchLayer.new()
            scn:addChild(sm.viewNode, 10000)

            sm.postEnter()
        end
    end
end

function sm.preEnter()

    if sm.viewNode ~= nil then
        sm.viewNode:removeFromParent(true)
        sm.viewNode = nil
        sm.greyLayer = nil
    end
    
    display.removeUnusedSpriteFrames()
    collectgarbage("collect")
end

function sm.postEnter()
    if core.Waiting.hasshow == true then
        if device.platform == "ios" then
            core.Waiting.indicator = sm.addView('CoverView')
            core.Waiting.indicator:setLocalZOrder(80000)
        end
    end
end

function sm.show()
    -- print("sm.show")
    if sm.viewNode ~= nil then
        if table.getn(sm.viewNode:getChildren()) > 0 and sm.greyLayer == nil then
            sm.greyLayer = display.newColorLayer(cc.c4b(0, 0, 0, 180))
            sm.viewNode:addChild(sm.greyLayer,-10)

            --sm.greyLayer:setOpacity(0)
            --transition.fadeTo(sm.greyLayer, {time = 2, opacity=128, easing = "BACKOUT"})

        elseif table.getn(sm.viewNode:getChildren()) == 1 and sm.greyLayer ~= nil then

           sm.greyLayer:removeFromParent(true)
            sm.greyLayer = nil

            -- transition.fadeTo(sm.greyLayer, {time = 0.1,opacity=0,easing = "BACKIN",
            --     onComplete = function()
         
            --     end}
            -- )

        end
    end

    if #sm.showPools < 1 then return end

    local sortFunc = function(a, b)
        return tonumber(sm.getPriority(a)) > tonumber(sm.getPriority(b))
    end

    table.sort(sm.showPools, sortFunc)

    for i=2,#sm.showPools do
        local show = sm.showPools[i-1]
        local nextshow = sm.showPools[i]
        show.nextshow = nextshow
    end
    
    local showview = sm.showPools[1]
    sm.showPools = nil 
    sm.showPools = {}

    sm.shownext(showview)

end

function sm.getPriority(show)
    
    local priority = 0

    if show.type == "scene" then
        priority = -100
    else
        priority = 0
    end
    
    return priority

end

return sm
