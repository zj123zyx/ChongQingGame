//
//  AppNotification.cpp
//  SlotFun
//
//  Created by yi.meng on 12-12-19.
//  Copyright (c) 2012年 RenRenGame. All rights reserved.
//

#include "AppNotification.h"
#include "cocos2d.h"
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#define JavaJni_AppNotification_ClassName "com/hongbogufen/hongboyicai/notification/NotificationManagerJNI"

using namespace cocos2d;
using namespace std;

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
    return 0;
}

void AppNotification::canceLoacalNotification(const char *type)
{    

}

void AppNotification::RegisterLocalNotification(const char* timeStr, const char* notice)
{
    std::vector<std::string> timeArray;
    splitToSVector(timeStr, timeArray, ":");
    time_t startTime = toNumber<time_t>( timeArray[0].c_str() );
    int type = toNumber<int>( timeArray[1].c_str() );
    
    int notificationId = 999; // Just support only one notificaion
   	
    time_t nowTime = time(NULL);

    time_t interval = 0;
   	time_t subSeconds = 0;

    subSeconds = startTime - nowTime;
    
    switch (type) {
        case 1:
            break;
        case 2:
            interval = 24*60*60;
            break;
        case 3:
            interval = 7 * 24*60*60;
            break;
        case 4:
            interval = 365 * 24*60*60;
            break;
    }

    if (type == 1){
        RegisterForLocalNotificationByJNI(notificationId, "Slots Secret", notice, subSeconds);
    }else{
        if (subSeconds<0)
        {
            subSeconds += interval;
        }
        RegisterRepeatingNotificationByJNI( notificationId, "Slots Secret", notice, subSeconds , interval );
    }


}

bool AppNotification::RegisterForRemoteNotificationTypes()
{
    return true;
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

}

void AppNotification::canceLoacalNotification(int androidNotificationType)
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,
                                       JavaJni_AppNotification_ClassName,
                                       "canceLoacalNotification",
                                       "(I)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID , androidNotificationType);
        t.env->DeleteLocalRef(t.classID);
    }
}

void AppNotification::cancelAllLocalNotifications()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,
                                       JavaJni_AppNotification_ClassName,
                                       "cancelAllLocalNotifications",
                                       "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void AppNotification::RegisterForLocalNotificationByJNI(int notificationId, const char * title, const char * msg ,long triggerAfterTime)
{
	JniMethodInfo t;
	// com.renren.game.lyz.notification
    if (JniHelper::getStaticMethodInfo(t,
                                       JavaJni_AppNotification_ClassName,
                                       "RegisterForLocalNotification",
                                       "(ILjava/lang/String;Ljava/lang/String;J)V")) {
        
        jstring stringArg2 = t.env->NewStringUTF(title);
        jstring stringArg3 = t.env->NewStringUTF(msg);
        jlong longArg4 = (jlong) triggerAfterTime;
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, notificationId, stringArg2, stringArg3 ,longArg4);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(stringArg3);
        t.env->DeleteLocalRef(t.classID);
    }
}

void AppNotification::RegisterRepeatingNotificationByJNI(int notificationId, const char * title, const char * msg ,long triggerAfterTime , long interval)
{
	JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,
                                       JavaJni_AppNotification_ClassName,
                                       "RegisterRepeatingNotification",
                                       "(ILjava/lang/String;Ljava/lang/String;JJ)V")) {
        
        jstring stringArg2 = t.env->NewStringUTF(title);
        jstring stringArg3 = t.env->NewStringUTF(msg);
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, notificationId, stringArg2, stringArg3 , (jlong)triggerAfterTime , (jlong)interval);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(stringArg3);
        t.env->DeleteLocalRef(t.classID);
    }
}