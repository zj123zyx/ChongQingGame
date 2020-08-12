//
//  AppNotification.h
//  SLOTFUN
//
//  Created by xuzhiqiang on 12-12-19.
//  Copyright (c) 2012年 RenRenGame. All rights reserved.
//

#ifndef SlotFun_AppNotification_h
#define SlotFun_AppNotification_h

class AppNotification
{
public:
    /*************************************************************************
     Construction and Destruction
     *************************************************************************/
	   
	/*!
     \brief
     Destructor for AppNotification
     */
	~AppNotification(void);
    
    
    static AppNotification* sharedAppNotification(void);

    const char* GetDeviceToken();
    
    void cancelAllLocalNotifications();
    void canceLoacalNotification(const char* type);
    
    void RegisterLocalNotification(const char* time, const char* notice);
    
    double GetTimeByString(const char* timeStr);
    
public:
    bool RegisterForRemoteNotificationTypes();
    void DidRegisterForRemoteNotificationWithDeviceToken( const char* token );
    void DidFailToRegisterForRemoteNotificationWithError( int error );
    
    void DidReceiveLocalNotification( const char* token );
    
protected:
    
    /*!
     \brief
     Constructs a new AppNotification.
     */
	AppNotification(void);

    const char* mDeviceToken;
    
    static AppNotification*  s_sharedAppNotification;

};

#endif
