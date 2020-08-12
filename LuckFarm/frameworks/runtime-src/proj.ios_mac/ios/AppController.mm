/****************************************************************************
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

//#import <UIKit/UIKit.h>
//#import "cocos2d.h"
//
//#import "AppController.h"
//#import "AppDelegate.h"
//#import "RootViewController.h"
//#import "platform/ios/CCEAGLView-ios.h"
//#import "AppNotification.h"
////#import <FacebookSDK/FacebookSDK.h>
//#import "Config.h"
////#import "AppsFlyerTracker.h"
//
//
//@implementation AppController
//
//#pragma mark -
//#pragma mark Application lifecycle
//
//// cocos2d application instance
//static AppDelegate s_sharedApplication;
//
//- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
//{
//    if ([UIApplication instancesRespondToSelector:@selector(registerUserNotificationSettings:)])
//    {
//        [application registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert|UIUserNotificationTypeBadge|UIUserNotificationTypeSound categories:nil]];
//    }
//
//    cocos2d::Application *app = cocos2d::Application::getInstance();
//    app->initGLContextAttrs();
//    cocos2d::GLViewImpl::convertAttrs();
//
//    // Override point for customization after application launch.
//
//    // Add the view controller's view to the window and display.
//    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
//    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
//                                     pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
//                                     depthFormat: cocos2d::GLViewImpl::_depthFormat
//                              preserveBackbuffer: NO
//                                      sharegroup: nil
//                                   multiSampling: NO
//                                 numberOfSamples: 0 ];
//
//    [eaglView setMultipleTouchEnabled:YES];
//
//    // Use RootViewController manage CCEAGLView
//    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
//    viewController.wantsFullScreenLayout = YES;
//    viewController.view = eaglView;
//
//    // Set RootViewController to window
//    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
//    {
//        // warning: addSubView doesn't work on iOS6
//        [window addSubview: viewController.view];
//    }
//    else
//    {
//        // use this method on ios6
//        [window setRootViewController:viewController];
//    }
//
//    [window makeKeyAndVisible];
//
//    [[UIApplication sharedApplication] setStatusBarHidden: YES];
//
//    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
//    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
//    cocos2d::Director::getInstance()->setOpenGLView(glview);
//
//
//    //add AppsFlyer
////    [AppsFlyerTracker sharedTracker].appsFlyerDevKey = @"rwCvzTQcJSfAKtVrVuUgYk";
////    [AppsFlyerTracker sharedTracker].appleAppID = @APP_STORE_ID_IPHONE;
//
//    app->run();
//    return YES;
//}
//
//
//- (void)applicationWillResignActive:(UIApplication *)application {
//    /*
//     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
//     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
//     */
//    cocos2d::Director::getInstance()->pause();
//}
//
//- (void)applicationDidBecomeActive:(UIApplication *)application {
//    /*
//     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
//     */
//
////    [FBAppCall handleDidBecomeActive];
////    [FBAppEvents activateApp];
//    //[[AppsFlyerTracker sharedTracker] trackAppLaunch];
//
//    cocos2d::Director::getInstance()->resume();
//}
//
//- (void)applicationDidEnterBackground:(UIApplication *)application {
//    /*
//     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
//     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
//     */
//    cocos2d::Application::getInstance()->applicationDidEnterBackground();
//}
//
//- (void)applicationWillEnterForeground:(UIApplication *)application {
//    /*
//     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
//     */
//    cocos2d::Application::getInstance()->applicationWillEnterForeground();
//}
//
//- (void)applicationWillTerminate:(UIApplication *)application {
//    /*
//     Called when the application is about to terminate.
//     See also applicationDidEnterBackground:.
//     */
//}
//
//#pragma mark -
//#pragma mark Memory management
//
//- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
//    /*
//     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
//     */
//    cocos2d::Director::getInstance()->purgeCachedData();
//}
//
//
//- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken{
//
//    //AppNotification::sharedAppNotification()->DidRegisterForRemoteNotificationWithDeviceToken((const char*)[deviceToken bytes]);
//}
//
//- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error{
//    //AppNotification::sharedAppNotification()->DidFailToRegisterForRemoteNotificationWithError((int)[error code]);
//}
//
//- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo{
//
//}
//
//- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification{
//    NSString* alertBody = [notification alertBody] ;
//    AppNotification::sharedAppNotification()->DidReceiveLocalNotification([alertBody UTF8String]);
//}
//
//
//
//
////根据选择的平台去重写 handleOpenURL && openURL
//-(BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
//{
//    //return [FBSession.activeSession handleOpenURL:url];
//    return true;
//}
//
//- (void)dealloc {
//    [super dealloc];
//}
//
//
//@end
#import <UIKit/UIKit.h>
#import "cocos2d.h"

#import "AppController.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "SNSManager.h"
#import "NetDataManager.h"
#import "ImageCrop.hpp"

#import "JPUSHService.h"
#import <AdSupport/AdSupport.h>
#ifdef NSFoundationVersionNumber_iOS_9_x_Max
#import <UserNotifications/UserNotifications.h>
#endif

@interface AppController()<JPUSHRegisterDelegate>

@end

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    
    cocos2d::Application *app = cocos2d::Application::getInstance();
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();
    
    // Override point for customization after application launch.
    NSString *advertisingId = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
    
    if ([[UIDevice currentDevice].systemVersion floatValue] >= 10.0) {
#ifdef NSFoundationVersionNumber_iOS_9_x_Max
        JPUSHRegisterEntity * entity = [[JPUSHRegisterEntity alloc] init];
        entity.types = UNAuthorizationOptionAlert|UNAuthorizationOptionBadge|UNAuthorizationOptionSound;
        [JPUSHService registerForRemoteNotificationConfig:entity delegate:self];
#endif
    } else if ([[UIDevice currentDevice].systemVersion floatValue] >= 8.0) {
        //可以添加自定义categories
        [JPUSHService registerForRemoteNotificationTypes:(UIUserNotificationTypeBadge |
                                                          UIUserNotificationTypeSound |
                                                          UIUserNotificationTypeAlert)
                                              categories:nil];
    } else {
        //categories 必须为nil
        [JPUSHService registerForRemoteNotificationTypes:(UIRemoteNotificationTypeBadge |
                                                          UIRemoteNotificationTypeSound |
                                                          UIRemoteNotificationTypeAlert)
                                              categories:nil];
    }
    
    //如不需要使用IDFA，advertisingIdentifier 可为nil
    [JPUSHService setupWithOption:launchOptions appKey:appKey
                          channel:channel
                 apsForProduction:isProduction
            advertisingIdentifier:advertisingId];
    
    //2.1.9版本新增获取registration id block接口。
    [JPUSHService registrationIDCompletionHandler:^(int resCode, NSString *registrationID) {
        if(resCode == 0){
            NSLog(@"registrationID获取成功：%@",registrationID);
            
        }
        else{
            NSLog(@"registrationID获取失败，code：%d",resCode);
        }
    }];
    
    NSNotificationCenter *defaultCenter = [NSNotificationCenter defaultCenter];
    [defaultCenter addObserver:self selector:@selector(networkDidReceiveMessage:) name:kJPFNetworkDidReceiveMessageNotification object:nil];
    
    // apn 内容获取：
//    NSDictionary *remoteNotification = [launchOptions objectForKey:UIApplicationLaunchOptionsRemoteNotificationKey];
//    if (remoteNotification.allKeys > 0) {
//        NSLog(@"apn内容为：%@",[remoteNotification description]);
//    }else{
//        NSLog(@"没有推送内容");
//    }
    
    //清空角标
    [[UIApplication sharedApplication] setApplicationIconBadgeNumber:0];
    [JPUSHService resetBadge];
    
    
    NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
    [accountDefaults setBool:NO forKey:@"StatusBarVisible"];
    
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                         pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    [eaglView setMultipleTouchEnabled:YES];
    
    // Use RootViewController manage CCEAGLView
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;
    
    //    _navigationController = [[UINavigationController alloc]initWithRootViewController:viewController];
    
    ImageCrop::getInstance()->setViewController(_viewController);
    
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden: NO];
    
    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);
    
    app->run();
    return YES;
}

- (void)networkDidReceiveMessage:(NSNotification *)notification {
    //清空角标
    [[UIApplication sharedApplication] setApplicationIconBadgeNumber:0];
    [JPUSHService resetBadge];
    
    NSMutableDictionary * userInfo = [[NSMutableDictionary alloc]initWithDictionary:[notification userInfo]];
    NSString *content = [userInfo valueForKey:@"content"];
    NSDictionary *extras = [[NSDictionary alloc]initWithDictionary:[userInfo valueForKey:@"extras"]];
    [userInfo setObject:extras forKey:@"extras"];
    //    NSString *customizeField1 = [extras valueForKey:@"customizeField1"]; //服务端传递的Extras附加字段，key是自己定义的
    NSMutableString *mulStr = [[NSMutableString alloc]init];
    for (NSString *key in userInfo) {
        if ([key isEqualToString:@"extras"]) {
            continue;
        }
        if (![mulStr isEqualToString:@""]) {
            [mulStr appendString:@"&&"];
        }
        [mulStr appendString:[NSString stringWithFormat:@"%@==%@",key,userInfo[key]]];
    }
    
    for (NSString *key in extras) {
        if (![mulStr isEqualToString:@""]) {
            [mulStr appendString:@"&&"];
        }
        [mulStr appendString:[NSString stringWithFormat:@"%@==%@",key,extras[key]]];
    }
    const char *infoStr = [mulStr cStringUsingEncoding:NSUTF8StringEncoding];
    NetDataManager::sharedNetDataManager()->returnToLuaWithNotificationInfo(infoStr);
    UserDefault::getInstance()->setBoolForKey("ReceivePushMessage", true);
    NSLog(@"%@",[userInfo description]);
}

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::Director::getInstance()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::Director::getInstance()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
    //调用退出登录接口
    NSLog(@"applicationWillTerminate");
    NetDataManager::sharedNetDataManager()->postQuit();
}

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    NSLog(@"%@", [NSString stringWithFormat:@"Device Token: %@", deviceToken]);
    [JPUSHService registerDeviceToken:deviceToken];
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    NSLog(@"did Fail To Register For Remote Notifications With Error: %@", error);
}

#if __IPHONE_OS_VERSION_MAX_ALLOWED > __IPHONE_7_1
- (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings
{
    
}

// Called when your app has been activated by the user selecting an action from
// a local notification.
// A nil action identifier indicates the default action.
// You should call the completion handler as soon as you've finished handling
// the action.
- (void)application:(UIApplication *)application handleActionWithIdentifier:(NSString *)identifier forLocalNotification:(UILocalNotification *)notification completionHandler:(void (^)())completionHandler
{
    
}

// Called when your app has been activated by the user selecting an action from
// a remote notification.
// A nil action identifier indicates the default action.
// You should call the completion handler as soon as you've finished handling
// the action.
- (void)application:(UIApplication *)application handleActionWithIdentifier:(NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo completionHandler:(void (^)())completionHandler
{
    
}

#endif

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
    [JPUSHService handleRemoteNotification:userInfo];
    NSLog(@"iOS6及以下系统，收到通知:%@", [self logDic:userInfo]);
    //    [rootViewController addNotificationCount];
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler
{
    [JPUSHService handleRemoteNotification:userInfo];
    
    NSMutableDictionary *infoDic = [[NSMutableDictionary alloc]initWithDictionary:userInfo];
    NSDictionary *apsTemp = [infoDic objectForKey:@"aps"];
    NSDictionary *aps = [[NSDictionary alloc]initWithDictionary:apsTemp];
    [infoDic setObject:aps forKey:@"aps"];
    //    NSLog(@"iOS7及以上系统，收到通知:%@", [self logDic:userInfo]);
    
    if ([[UIDevice currentDevice].systemVersion floatValue]<10.0 || application.applicationState>0) {
        //        [rootViewController addNotificationCount];
        NSMutableString *mulStr = [[NSMutableString alloc]init];
        for (NSString *key in infoDic) {
            if ([key isEqualToString:@"aps"]) {
                continue;
            }
            if (![mulStr isEqualToString:@""]) {
                [mulStr appendString:@"&&"];
            }
            [mulStr appendString:[NSString stringWithFormat:@"%@==%@",key,userInfo[key]]];
        }
        
        for (NSString *key in aps) {
            if ([key isEqualToString:@"alert"]) {
                if (![mulStr isEqualToString:@""]) {
                    [mulStr appendString:@"&&"];
                }
                [mulStr appendString:[NSString stringWithFormat:@"%@==%@",key,aps[key]]];
            }
        }
        const char *infoStr = [mulStr cStringUsingEncoding:NSUTF8StringEncoding];
        NetDataManager::sharedNetDataManager()->returnToLuaWithNotificationInfo(infoStr);
    }
    
    completionHandler(UIBackgroundFetchResultNewData);
}

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
{
    [JPUSHService showLocalNotificationAtFront:notification identifierKey:nil];
}

#ifdef NSFoundationVersionNumber_iOS_9_x_Max
#pragma mark- JPUSHRegisterDelegate
- (void)jpushNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(NSInteger))completionHandler {
    NSDictionary * userInfo = notification.request.content.userInfo;
    
    UNNotificationRequest *request = notification.request; // 收到推送的请求
    UNNotificationContent *content = request.content; // 收到推送的消息内容
    
    NSNumber *badge = content.badge;  // 推送消息的角标
    NSString *body = content.body;    // 推送消息体
    UNNotificationSound *sound = content.sound;  // 推送消息的声音
    NSString *subtitle = content.subtitle;  // 推送消息的副标题
    NSString *title = content.title;  // 推送消息的标题
    
    if([notification.request.trigger isKindOfClass:[UNPushNotificationTrigger class]]) {
        [JPUSHService handleRemoteNotification:userInfo];
        NSLog(@"iOS10 前台收到远程通知:%@", [self logDic:userInfo]);
        NSMutableString *mulStr = [[NSMutableString alloc]init];
        for (NSString *key in userInfo) {
            if ([key isEqualToString:@"title"] || [key isEqualToString:@"desc"]) {
                if (![mulStr isEqualToString:@""]) {
                    [mulStr appendString:@"&&"];
                }
                [mulStr appendString:[NSString stringWithFormat:@"%@==%@",key,userInfo[key]]];
            }
        }
        
        //        [rootViewController addNotificationCount];
        
    }
    else {
        // 判断为本地通知
        NSLog(@"iOS10 前台收到本地通知:{\nbody:%@，\ntitle:%@,\nsubtitle:%@,\nbadge：%@，\nsound：%@，\nuserInfo：%@\n}",body,title,subtitle,badge,sound,userInfo);
    }
    completionHandler(UNNotificationPresentationOptionBadge|UNNotificationPresentationOptionSound|UNNotificationPresentationOptionAlert); // 需要执行这个方法，选择是否提醒用户，有Badge、Sound、Alert三种类型可以设置
}

- (void)jpushNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void (^)())completionHandler {
    
    NSDictionary * userInfo = response.notification.request.content.userInfo;
    UNNotificationRequest *request = response.notification.request; // 收到推送的请求
    UNNotificationContent *content = request.content; // 收到推送的消息内容
    
    NSNumber *badge = content.badge;  // 推送消息的角标
    NSString *body = content.body;    // 推送消息体
    UNNotificationSound *sound = content.sound;  // 推送消息的声音
    NSString *subtitle = content.subtitle;  // 推送消息的副标题
    NSString *title = content.title;  // 推送消息的标题
    
    if([response.notification.request.trigger isKindOfClass:[UNPushNotificationTrigger class]]) {
        [JPUSHService handleRemoteNotification:userInfo];
        NSLog(@"iOS10 收到远程通知:%@", [self logDic:userInfo]);
        NSMutableString *mulStr = [[NSMutableString alloc]init];
        for (NSString *key in userInfo) {
            [mulStr appendString:[NSString stringWithFormat:@"%@==%@",key,userInfo[key]]];
        }
        //        [rootViewController addNotificationCount];
        
    }
    else {
        // 判断为本地通知
        NSLog(@"iOS10 收到本地通知:{\nbody:%@，\ntitle:%@,\nsubtitle:%@,\nbadge：%@，\nsound：%@，\nuserInfo：%@\n}",body,title,subtitle,badge,sound,userInfo);
    }
    
    completionHandler();  // 系统要求执行这个方法
}
#endif

// log NSSet with UTF8
// if not ,log will be \Uxxx
- (NSString *)logDic:(NSDictionary *)dic {
    if (![dic count]) {
        return nil;
    }
    NSLog(@"description = %@",[dic description]);
    NSString *tempStr1 =
    [[dic description] stringByReplacingOccurrencesOfString:@"\\u"
                                                 withString:@"\\U"];
    NSString *tempStr2 =
    [tempStr1 stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""];
    NSString *tempStr3 =
    [[@"\"" stringByAppendingString:tempStr2] stringByAppendingString:@"\""];
    NSData *tempData = [tempStr3 dataUsingEncoding:NSUTF8StringEncoding];
    NSString *str =
    [NSPropertyListSerialization propertyListFromData:tempData
                                     mutabilityOption:NSPropertyListImmutable
                                               format:NULL
                                     errorDescription:NULL];
    
    return str;
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    NSInteger actionType = [SNSManager sharedManager].actionType;
    return [SNSManager handleOpenURL:url withType:actionType];
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
    NSInteger actionType = [SNSManager sharedManager].actionType;
    return [SNSManager handleOpenURL:url withType:actionType];
}

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
    cocos2d::Director::getInstance()->purgeCachedData();
}


- (void)dealloc {
    [super dealloc];
}


@end
