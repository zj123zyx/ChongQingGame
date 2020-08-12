
--------------------------------
-- @module AppNotification
-- @parent_module 

--------------------------------
-- 
-- @function [parent=#AppNotification] RegisterForRemoteNotificationTypes 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#AppNotification] cancelAllLocalNotifications 
-- @param self
-- @return AppNotification#AppNotification self (return value: AppNotification)
        
--------------------------------
-- 
-- @function [parent=#AppNotification] DidReceiveLocalNotification 
-- @param self
-- @param #char token
-- @return AppNotification#AppNotification self (return value: AppNotification)
        
--------------------------------
-- 
-- @function [parent=#AppNotification] RegisterLocalNotification 
-- @param self
-- @param #char time
-- @param #char notice
-- @return AppNotification#AppNotification self (return value: AppNotification)
        
--------------------------------
-- 
-- @function [parent=#AppNotification] GetTimeByString 
-- @param self
-- @param #char timeStr
-- @return double#double ret (return value: double)
        
--------------------------------
-- 
-- @function [parent=#AppNotification] DidRegisterForRemoteNotificationWithDeviceToken 
-- @param self
-- @param #char token
-- @return AppNotification#AppNotification self (return value: AppNotification)
        
--------------------------------
-- 
-- @function [parent=#AppNotification] DidFailToRegisterForRemoteNotificationWithError 
-- @param self
-- @param #int error
-- @return AppNotification#AppNotification self (return value: AppNotification)
        
--------------------------------
-- 
-- @function [parent=#AppNotification] canceLoacalNotification 
-- @param self
-- @param #char type
-- @return AppNotification#AppNotification self (return value: AppNotification)
        
--------------------------------
-- 
-- @function [parent=#AppNotification] GetDeviceToken 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#AppNotification] sharedAppNotification 
-- @param self
-- @return AppNotification#AppNotification ret (return value: AppNotification)
        
return nil
