
local AppBase = class("AppBase")

AppBase.APP_ENTER_BACKGROUND_EVENT = "APP_ENTER_BACKGROUND_EVENT"
AppBase.APP_ENTER_FOREGROUND_EVENT = "APP_ENTER_FOREGROUND_EVENT"

function AppBase:ctor(appName, packageRoot)
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()

    self.name = appName
    self.packageRoot = packageRoot or "app"

    local eventDispatcher = cc.Director:getInstance():getEventDispatcher()
    local customListenerBg = cc.EventListenerCustom:create(AppBase.APP_ENTER_BACKGROUND_EVENT,
                                handler(self, self.onEnterBackground))
    eventDispatcher:addEventListenerWithFixedPriority(customListenerBg, 1)
    local customListenerFg = cc.EventListenerCustom:create(AppBase.APP_ENTER_FOREGROUND_EVENT,
                                handler(self, self.onEnterForeground))
    eventDispatcher:addEventListenerWithFixedPriority(customListenerFg, 1)

    self.snapshots_ = {}

    -- set global app
    app = self
end

function AppBase:run()
end

function AppBase:exit()
    cc.Director:getInstance():endToLua()
    if device.platform == "windows" or device.platform == "mac" then
        os.exit()
    end
end

function AppBase:enterScene(scenePath, args, transitionType, time, more)

    local scenePackageName = ""

    if type(scenePath) == "table" then
        scenePackageName = scenePath.path
        print("scenePath:",type(scenePath),scenePackageName,scenePath.path)

    else
        scenePackageName = self.packageRoot .. ".scenes." .. scenePath
    end
    print("scenePath:",type(scenePath),scenePackageName)

    --local scenePackageName = self.packageRoot .. ".scenes." .. sceneName
    local sceneClass = require(scenePackageName)
    local scene = sceneClass.new(args)--unpack(checktable(args))
    display.replaceScene(scene, transitionType, time, more)

    return scene
end

function AppBase:createView(viewName, ...)
    local viewPackageName = self.packageRoot .. ".views." .. viewName
    local viewClass = require(viewPackageName)
    return viewClass.new(...)
end

-- view`s is SwallowEnabled = true
function AppBase:createSView(viewName, ...)
    local viewPackageName = self.packageRoot .. ".views." .. viewName
    local viewClass = require(viewPackageName)
    return viewClass.new(...)
end

-- view`s is the v of "mvc"
function AppBase:createMView(viewName, ...)
    local viewPackageName = self.packageRoot .. ".scenes.views." .. viewName
    local viewClass = require(viewPackageName)
    return viewClass.new(...)
end

function AppBase:onEnterBackground()
    self:dispatchEvent({name = AppBase.APP_ENTER_BACKGROUND_EVENT})
end

function AppBase:onEnterForeground()
    self:dispatchEvent({name = AppBase.APP_ENTER_FOREGROUND_EVENT})
end

return AppBase
