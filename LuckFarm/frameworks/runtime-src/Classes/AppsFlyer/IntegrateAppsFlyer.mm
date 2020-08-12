//
//  integrateAppsFlyer.cpp
//  SlotMachine
//
//  Created by Forrest HAN on 2/18/13.
//
//

#include "IntegrateAppsFlyer.h"
#import "AppsFlyerTracker.h"
#import "Config.h"
#include <string>
// Import these
#import <CommonCrypto/CommonDigest.h>
#import <AdSupport/AdSupport.h>

IntergrateAppsFlyer::~IntergrateAppsFlyer()
{
}

static IntergrateAppsFlyer*  _instance;

IntergrateAppsFlyer* IntergrateAppsFlyer::instance()
{
    if (!_instance)
    {
        _instance = new IntergrateAppsFlyer();
    }
    return _instance;
}



void IntergrateAppsFlyer::integrateAppsFlyer()
{
    
    NSDictionary *infoDict = [[NSBundle mainBundle] infoDictionary];
    NSString *nsBundleId = [infoDict objectForKey:@"CFBundleIdentifier"];
    
    std::string bundleID = [nsBundleId UTF8String];
    
    
    if (BUNDLE_ID_IPHONE == bundleID ) {
    //iphone
        [AppsFlyerTracker sharedTracker].appsFlyerDevKey = @"rwCvzTQcJSfAKtVrVuUgYk";
        [AppsFlyerTracker sharedTracker].appleAppID = @APP_STORE_ID_IPHONE;
    
    }else
    {
    //ipad
        [AppsFlyerTracker sharedTracker].appsFlyerDevKey = @"rwCvzTQcJSfAKtVrVuUgYk";
        [AppsFlyerTracker sharedTracker].appleAppID = @APP_STORE_ID_IPAD;
    }
    
    [[AppsFlyerTracker sharedTracker] trackAppLaunch];
}

void IntergrateAppsFlyer::appsFlyerTrackEvent(const char* iName, const char* iValue)
{
    NSString *eventName = [NSString stringWithUTF8String:iName];
    NSString *value = [NSString stringWithUTF8String:iValue];
    NSLog(@"AppsFlyerTrackEvent: %@, %@", eventName, value);

    [[AppsFlyerTracker sharedTracker] trackEvent:eventName withValue:value];
}

const char* IntergrateAppsFlyer::getIDFA()
{
    // Print IFA (Identifier for Advertising) in Output section. Add to applicationDidBecomeActive. iOS 6+ devices only.
    NSString* ifa = [[[NSClassFromString(@"ASIdentifierManager") sharedManager] advertisingIdentifier] UUIDString];
    ifa = [[ifa stringByReplacingOccurrencesOfString:@"-" withString:@""] lowercaseString];
    NSLog(@"IFA: %@",ifa);
    return [ifa UTF8String];
}