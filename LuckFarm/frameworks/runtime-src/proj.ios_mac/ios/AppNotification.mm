//
//  AppNotification.cpp
//  SlotFun
//
//  Created by xuzhiqiang on 12-12-19.
//  Copyright (c) 2012年 RenRenGame. All rights reserved.
//

#include "AppNotification.h"
#include <string>
#include <sstream>
#include <vector>


template <class T>
std::string toString(T val) {
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

template <class T>
T toNumber(const char* val){
    if(!val)
    {
        return 0;
    }
    std::istringstream b(val);
    T num;
    b >> num;
    return num;
}

//字符串分割函数
void splitToSVector(std::string str, std::vector<std::string>& dest, const char* pttn)
{
    if(str.size() == 0) return;
    
    std::string pattern = pttn;
    
    std::string::size_type pos;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size();
    
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            dest.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
}

// singleton instance pointer
AppNotification* AppNotification::s_sharedAppNotification = NULL;

AppNotification* AppNotification::sharedAppNotification(void)
{
    if (!s_sharedAppNotification)
    {
        s_sharedAppNotification = new AppNotification();
    }
    return s_sharedAppNotification;
}


/*************************************************************************
 Constructor
 *************************************************************************/
AppNotification::AppNotification(void):
    mDeviceToken("")
{
}
/*************************************************************************
 Destructor
 *************************************************************************/
AppNotification::~AppNotification(void)
{
}

const char* AppNotification::GetDeviceToken()
{
    return mDeviceToken;
}

double AppNotification::GetTimeByString(const char *timeStr)
{
    NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
    [dateFormat setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSString* dateStr = [[NSString alloc] initWithCString:timeStr encoding:NSUTF8StringEncoding];
    NSDate* toDate = [dateFormat dateFromString:dateStr];
    
    NSTimeInterval toDateTotalSecond = [toDate timeIntervalSince1970] * 1;
    return toDateTotalSecond;
}

void AppNotification::cancelAllLocalNotifications()
{
    [[UIApplication sharedApplication] cancelAllLocalNotifications];
}

void AppNotification::canceLoacalNotification(const char *type)
{    
    NSArray* notificationArray = [[UIApplication sharedApplication] scheduledLocalNotifications];
    
    for (id notification in notificationArray) {
        
        NSDictionary* userinfo =  [notification userInfo];
        
        NSString *val = [userinfo objectForKey:[NSString stringWithUTF8String:"noticeType"]];
        
        if (val) {
            std::string strval = [val UTF8String];
            if(strcmp(type, strval.c_str()) == 0){
                [[UIApplication sharedApplication] cancelLocalNotification:notification];
            }
        }
    }
    
}

void AppNotification::RegisterLocalNotification(const char* time, const char* notice)
{
    UILocalNotification* notification = [[UILocalNotification alloc] init];
    
    std::vector<std::string> timeArray;
    splitToSVector(time, timeArray, ":");
   
    NSDate* nowDate = [NSDate date];
    double seconds = toNumber<double>( timeArray[0].c_str() );
    int type = toNumber<int>( timeArray[1].c_str() );

    switch (type) {
        case 1:
            notification.repeatInterval = kCFCalendarUnitEra;
            break;
        case 2:
            notification.repeatInterval = kCFCalendarUnitDay;
            break;
        case 3:
            notification.repeatInterval = kCFCalendarUnitWeek;
            break;
        case 4:
            notification.repeatInterval = kCFCalendarUnitYear;
            break;
    }
   
    notification.timeZone = [NSTimeZone defaultTimeZone];
    notification.applicationIconBadgeNumber = notification.applicationIconBadgeNumber+1;
    notification.alertAction = NSLocalizedString(@"Display", nil);
    notification.fireDate = [nowDate initWithTimeIntervalSince1970: seconds];
    
    notification.alertBody = [NSString stringWithUTF8String:notice];
    
    NSString *keyval = [NSString stringWithCString:timeArray[3].c_str() encoding:[NSString defaultCStringEncoding]];

    
    NSDictionary* userinfo = [NSDictionary dictionaryWithObjectsAndKeys: keyval, @"noticeType",nil];
    
    [notification setUserInfo:userinfo];
    
    [[UIApplication sharedApplication] scheduleLocalNotification: notification];

}

bool AppNotification::RegisterForRemoteNotificationTypes()
{
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:
     (UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert ) ];
    
    return YES;
}

void AppNotification::DidRegisterForRemoteNotificationWithDeviceToken( const char* token)
{
    if (!token) mDeviceToken = "";
    
    mDeviceToken = token;
}

void AppNotification::DidFailToRegisterForRemoteNotificationWithError( int error )
{
}

void AppNotification::DidReceiveLocalNotification( const char* token )
{
   // UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"本地通知" message:[NSString stringWithUTF8String:token] delegate:nil cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
    
   // [alert show];
    //[UIApplication sharedApplication].applicationIconBadgeNumber=0;
}