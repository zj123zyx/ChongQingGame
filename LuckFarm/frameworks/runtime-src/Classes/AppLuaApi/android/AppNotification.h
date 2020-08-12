//
//  AppNotification.h
//  SLOTFUN
//
//  Created by mey on 12-12-19.
//  Copyright (c) 2012年 . All rights reserved.
//

#ifndef SlotFun_AppNotification_h
#define SlotFun_AppNotification_h
#include "cocos2d.h"

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
    
//  for android
public:
    void canceLoacalNotification(int androidNotificationType);
    void RegisterForLocalNotificationByJNI(int notificationId, const char * title, const char * msg ,long triggerAfterTime);
    void RegisterRepeatingNotificationByJNI(int notificationId, const char * title, const char * msg ,long triggerAfterTime , long interval);
    
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
