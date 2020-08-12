
#import "AppLuaApi.h"
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "CCScriptSupport.h"
#include "CCLuaEngine.h"
#import "SvUDIDTools.h"
#import "CryptorTools.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "AppController.h"
#import "OC-Lua-Bridge.h"
#import "ImageCrop.hpp"

using namespace cocos2d;

AppLuaApi* AppLuaApi::s_AppLuaApiInstance = NULL;

AppLuaApi* AppLuaApi::getInstance(void)
{
    if (!s_AppLuaApiInstance)
    {
        s_AppLuaApiInstance = new AppLuaApi();
    }
    return s_AppLuaApiInstance;
}

AppLuaApi::~AppLuaApi(void)
{
}

void AppLuaApi::showIndicator(void)
{
    
}

void AppLuaApi::hideIndicator(void)
{
    
}

void AppLuaApi::openLLPayForPayWith(const char *orderinfo)
{
    OCBridge::openLLPayForPayWith(orderinfo);
}

void AppLuaApi::gotoQQLogin()
{
    OCBridge::gotoQQLogin();
}

void AppLuaApi::gotoWeiXinLogin()
{
    OCBridge::gotoWeiXinLogin();
}

void AppLuaApi::shareWeChatFriend()
{
    OCBridge::shareWeChatFriend();
}

void AppLuaApi::shareWeChatFriendQuan()
{
    OCBridge::shareWeChatFriendQuan();
}

void AppLuaApi::shareQQFriend()
{
    OCBridge::shareQQFriend();
}

const char* AppLuaApi::stringToUtf8(const char *str)
{
    NSString * string = [NSString stringWithCString:str encoding:NSUTF8StringEncoding];
    string = [string stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    const char *resultStr = [string cStringUsingEncoding:NSUTF8StringEncoding];
    return resultStr;
}

const char* AppLuaApi::utf8ToString(const char *str)
{
    NSString * string = [NSString stringWithCString:str encoding:NSUTF8StringEncoding];
    string = [string stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    const char *resultStr = [string UTF8String];
    return resultStr;
}

const char* AppLuaApi::UDID()
{
    NSString *udid = [SvUDIDTools UDID];
    NSLog(@"udid in keychain %@", udid);
    NSLog(@"current identityForVendor %@", [UIDevice currentDevice].identifierForVendor);
    
    return [udid UTF8String];
}

const char* AppLuaApi::AppVersion()
{
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    // app版本
    NSString *app_Version = [infoDictionary objectForKey:@"CFBundleShortVersionString"];
    
    return [app_Version UTF8String];
}
const char* AppLuaApi::AppVersionCode()
{
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    // app版本
    NSString *app_Version = [infoDictionary objectForKey:@"CFBundleVersion"];
    
    return [app_Version UTF8String];
}
const char* AppLuaApi::ResVersion()
{
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    
    NSString *res_Version = [infoDictionary objectForKey:@"ResVersion"];
    
    return [res_Version UTF8String];
}

const char* AppLuaApi::SystemVersion()
{
    NSString *ver = [[UIDevice currentDevice] systemVersion];
    return [ver UTF8String];
}

#if CC_LUA_ENGINE_ENABLED > 0
void AppLuaApi::postFBListenerLua(cocos2d::LUA_FUNCTION listener)
{
    if (mListener)
    {
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(mListener);
    }
    mListener = listener;
}
#endif

void AppLuaApi::postPhoto(const char* profileID, const char* name,const char* path, int errorcode)
{
#if CC_LUA_ENGINE_ENABLED > 0
    
    if (mListener == -1) {
        return;
    }
    
    if (errorcode == -1){
        
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        LuaValueDict event;
        event["photo"] = LuaValue::stringValue("-1");
        
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(mListener, 1);
        
    }else{
        LuaValueDict postData;
        
        postData["id"]   = LuaValue::stringValue(profileID);
        postData["name"] = LuaValue::stringValue(name);
        postData["path"] = LuaValue::stringValue(path);
        
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        
        LuaValueDict event;
        event["photo"] = LuaValue::dictValue(postData);
        
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(mListener, 1);
    }
#endif
}
void AppLuaApi::downloadPhoto(const char *fbID)
{
    
    std::string fileName = StringUtils::format("%s_square.png",fbID);
    
    // Save file for resue.
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    writablePath = writablePath + fileName;
    if(FileUtils::getInstance()->isFileExist(writablePath.c_str())){
        postPhoto(fbID, fileName.c_str(), writablePath.c_str(),1);
        return;
    }
    
    std::string downloadURL = StringUtils::format("http://graph.facebook.com/%s/picture?type=square",fbID);
    
    HttpRequest* pRequest = new HttpRequest();
    pRequest->setUrl((downloadURL.c_str()));
    pRequest->setRequestType(HttpRequest::Type::GET);
    //pRequest->setResponseCallback(this, httpresponse_selector(CCAccountManager::onHttpRequestCompleted));
    pRequest->setResponseCallback(CC_CALLBACK_2(AppLuaApi::onHttpRequestCompleted, this));
    pRequest->setTag(fbID);
    
    HttpClient::getInstance()->send(pRequest);
    pRequest->release();
    
    
}

void AppLuaApi::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    
    if (!response)
    {
        CCLOG("No Response");
    }
    
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        //CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    if (!response->isSucceed())
    {
        postPhoto("", "", "", -1);
        return;
    }
    
    // Dump the data
    std::vector<char> *buffer = response->getResponseData();
    std::string _data;
    _data.assign(buffer->begin(), buffer->end());
    
    cocos2d::Image * img=new cocos2d::Image();
    img->initWithImageData((const unsigned char*)_data.c_str(), buffer->size());
    
    // Save file for resue.
    std::string writablePath = cocos2d::FileUtils::getInstance()->getWritablePath();
    std::string fbid = response->getHttpRequest()->getTag();
    std::string fname = fbid;
    fname.append("_square.png");
    
    writablePath.append(fname);
    img->saveToFile(writablePath.c_str());
    
    postPhoto(fbid.c_str(), fname.c_str(), writablePath.c_str(), 1);
    
}

void AppLuaApi::purgeInstance(void)
{
    if (s_AppLuaApiInstance)
    {
        delete s_AppLuaApiInstance;
        s_AppLuaApiInstance = NULL;
    }
}

void AppLuaApi::downloadNewApp(const char *mainVersion)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if ( CCApplication::getInstance()->getTargetPlatform() == Application::Platform::OS_IPHONE){
        NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:"https://itunes.apple.com/us/app/hong-bo-jie-ji/id1095627048?l=zh&ls=1&mt=8" encoding:NSUTF8StringEncoding]];
        [[UIApplication sharedApplication] openURL:nsurl];
    }
    else if(CCApplication::getInstance()->getTargetPlatform() == Application::Platform::OS_IPAD){
        NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:"https://itunes.apple.com/us/app/hong-bo-jie-ji/id1095627048?l=zh&ls=1&mt=8" encoding:NSUTF8StringEncoding]];
        [[UIApplication sharedApplication] openURL:nsurl];
    }
#endif
}




void AppLuaApi::setStatusBar(const char* flag)
{
    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    UIViewController * rootViewController = [window rootViewController];
    
    int value = [[NSString stringWithUTF8String:flag] intValue];
    NSLog(@"value =  %d", value);
    if (value == 1){
        //[[UIApplication sharedApplication] setStatusBarHidden: NO];
        NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
        [accountDefaults setBool:NO forKey:@"StatusBarVisible"];
        
        [UIView animateWithDuration:0.5 animations:^{
            [rootViewController setNeedsStatusBarAppearanceUpdate];
        }];
    }else if (value == 2){
        //[[UIApplication sharedApplication] setStatusBarHidden: YES];
        
        NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
        [accountDefaults setBool:YES forKey:@"StatusBarVisible"];
        
        [UIView animateWithDuration:0.5 animations:^{
            [rootViewController setNeedsStatusBarAppearanceUpdate];
        }];
    }
}

void AppLuaApi::setGameOrientation(const char* flag)
{
    NSLog(@"setGameOrientation");
    int value = [[NSString stringWithUTF8String:flag] intValue];
    NSLog(@"value =  %d", value);
    if (value == 1){
        [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight];
        UIWindow *window = [UIApplication sharedApplication].keyWindow;
        UIViewController * rootViewController = [window rootViewController];
        rootViewController.view.transform = CGAffineTransformMakeRotation(M_PI_2);
        
        CGRect frame = [UIScreen mainScreen].applicationFrame;
        rootViewController.view.bounds = CGRectMake(0, 0, frame.size.height, frame.size.width);
    }else if (value == 2){
        [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationPortraitUpsideDown];
        UIWindow *window = [UIApplication sharedApplication].keyWindow;
        UIViewController * rootViewController = [window rootViewController];
        rootViewController.view.transform = CGAffineTransformMakeRotation(0);
        CGRect frame = [UIScreen mainScreen].applicationFrame;
        rootViewController.view.bounds = CGRectMake(0, 0, frame.size.width, frame.size.height);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 返回进过RSA加密处理的xml
 */
const char* AppLuaApi::cryptorToolsToRSA(const char* xmlContent)
{
    //NSLog(@"----------cryptorToolsToRSA----------  ");
    NSString * content = [NSString stringWithUTF8String:xmlContent];
    //NSLog(@"xmlContent =  %@", content);
    
    //创建CryptorTools对象
    CryptorTools *tool = [[CryptorTools alloc] init];
    NSString *pubPath = [[NSBundle mainBundle] pathForResource:@"res/hongbo/hongbo.cer" ofType:nil];
    //NSLog(@"pubPath =  %@", pubPath);
    [tool loadPublicKeyWithFilePath:pubPath];
    
    //RSA加密
    NSString *result = [tool RSAEncryptString:content];
    
    [tool release];
    
    return [result UTF8String];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AppLuaApi::encryptWithRsa(const char* xmlContent)
{

}

void AppLuaApi::showEncryptWithRsa(const char* xmlContent)
{

}


void AppLuaApi::app_to_call(const char *num)
{
    
    NSMutableString * str=[[NSMutableString alloc] initWithFormat:@"telprompt://%s",num];
    NSLog(@"str======%@",str);
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:str]];
}

void AppLuaApi::openPhotoAlbum()
{

    ImageCrop::getInstance()->openPhoto([=](std::string path)
    {
        CCLOG("=========openPhoto path:%s",path.c_str());
        bool isFileExist = FileUtils::getInstance()->isFileExist(path);
        if (isFileExist) {
            CCLOG("~~~~图片文件存在！");
        }else{
            CCLOG("~~~~~图片文件不存在！");
        }
        //   _img -> removeFromParent();

//        _img->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        
    });

}

void AppLuaApi::openCamera()
{
    ImageCrop::getInstance()->openCamera([=](std::string path)
     {
         CCLOG("====openCamera path:%s",path.c_str());
         bool isFileExist = FileUtils::getInstance()->isFileExist(path);
         if (isFileExist) {
             CCLOG("~~~~图片文件存在！");
         }else{
             CCLOG("~~~~~图片文件不存在！");
         }

         
     });
}

void AppLuaApi::openURL(const char * url)
{
    printf("===url==%s",url);
    NSString *str = [NSString stringWithUTF8String:url];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:str]];

}

void AppLuaApi::setJPushTag(const char * userName)
{


}
