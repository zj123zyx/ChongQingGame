
if cc.bPlugin_ then
	--luaoc = require("cocos.cocos2d.luaoc")
	luaoc = require("luaoc")
else
	luaoc = require(cc.PACKAGE_NAME .. ".luaoc")
end

function device.showAlertIOS(title, message, buttonLabels, listener)
end