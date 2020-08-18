-- require "app.core.util.TableUtil"

-- require("app.core.ext.number")
-- require("app.core.ext.putsTable")

-- init core
local core = {}

-- core.Assets = import(".Assets")
core.displayEX = import(".displayEX")

-- if device.platform == "ios" then
-- 	core.Purchase = require("app.core.store.Purchase").new()
-- elseif device.platform == "android" then
-- 	core.Purchase = require("app.core.store.PurchaseGooglePlay").new()
-- end

-- core.HttpNet = import(".network.HttpNetModule")
-- core.NetPacket = import(".network.PacketModule")
-- core.SocketNet = require("app.core.network.SocketNetModule").new()
-- core.Sqlite = require("app.core.Sqlite")
core.Waiting = require("app.core.Waiting")
ToolUtils = require("app.core.ToolUtils")
core.SocketNet = require("app.core.network.SocketNet").new()
core.sktMgr = require("app.core.SocketManager")

--core.FBPlatform = require("app.core.FBPlatform")


-- ToJson = require('json')
-- import(".util.PrintTable")

-- import(".util.AnimationUtil")

return core

