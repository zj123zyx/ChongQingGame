local CommonView = class("CommonView", function()
    return core.displayEX.newSwallowEnabledNode()
end)

function CommonView:ctor(msg)
    self.viewNode  = CCBuilderReaderLoad("view/CommonView.ccbi", self)
    self:addChild(self.viewNode)

    self:addNodeEventListener(cc.NODE_TOUCH_EVENT,handler(self, self.onTouch_))

    self.title:enableOutline(cc.c4b(64, 64, 64, 255), 3);
    self.content:enableOutline(cc.c4b(64, 64, 64, 255), 2);

    if msg then

        if msg.onlyContent then
            self.contentOnly:setVisible(true)
            self.commonBg:setVisible(false)
            if msg.content then
                self.contentOnly:setString(msg.content)
            end

            self:performWithDelay(function() 
                --scn.ScnMgr.removeView(self)
                self:removeFromParent(true)
            end,2.2)
        else
            --self.contentOnly:setVisible(false)
            if msg.title then
                self.title:setString(msg.title)
            end

            if msg.content then
                self.content:setString(msg.content)
            end
        end

        self.callback = msg.callback
        self.delayPopCall = msg.delayPopCall
    end

end


function CommonView:onTouch_(event)

    if event.name == "ended" then
        
        if self.callback ~= nil then
            self.callback()
        end

        if self.delayPopCall ~= nil then
            self:delayPopCall()
        end

        --scn.ScnMgr.removeView(self)
        self:removeFromParent(true)

    end

    return true
end

return CommonView
