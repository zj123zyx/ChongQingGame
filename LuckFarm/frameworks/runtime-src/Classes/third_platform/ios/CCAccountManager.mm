
#import "CCAccountManager.h"
#include <sstream>
#include "cocos2d/LuaScriptHandlerMgr.h"
#include "CCScriptSupport.h"
#include "CCLuaEngine.h"

using namespace cocos2d;
using namespace network;

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

CCAccountManager* CCAccountManager::s_sharedAccountManager = NULL;

CCAccountManager* CCAccountManager::sharedAccountManager(void)
{
    if (!s_sharedAccountManager)
    {
        s_sharedAccountManager = new CCAccountManager();
    }
    return s_sharedAccountManager;
}

void CCAccountManager::downloadNewApp(const char* url)
{
    CCLOG("CCAccountManager:: downloadNewApp is %s", url);
    #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]];
        [[UIApplication sharedApplication] openURL:nsurl];
    #endif
}

void CCAccountManager::showIndicator(void)
{

}

void CCAccountManager::hideIndicator(void)
{
}

CCAccountManager::~CCAccountManager(void)
{
}

#if CC_LUA_ENGINE_ENABLED > 0
void CCAccountManager::postFBListenerLua(cocos2d::LUA_FUNCTION listener)
{
    if (mListener)
    {
       cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(mListener);
    }
    mListener = listener;
}
#endif

bool CCAccountManager::init(const char* nettype)
{
    m_fromNetwork = nettype;
    return true;
}

const char* CCAccountManager::AppVersion()
{
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    // app版本
    NSString *app_Version = [infoDictionary objectForKey:@"CFBundleVersion"];
    
    return [app_Version UTF8String];
}
const char* CCAccountManager::ResVersion()
{
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    
    NSString *res_Version = [infoDictionary objectForKey:@"ResVersion"];
    
    return [res_Version UTF8String];
}
const char* CCAccountManager::SystemVersion()
{
    NSString *ver = [[UIDevice currentDevice] systemVersion];
    NSLog(@"system version %@", ver);
    
    // TODO: call back lua function
    int handler = cocos2d::ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, (cocos2d::ScriptHandlerMgr::HandlerType)500 );
    
    if (0 != handler)
    {
        CCLOG("come in handler, handler is %d", handler);
        cocos2d::CommonScriptData data(handler,"");
        cocos2d::ScriptEvent event(cocos2d::ScriptEventType::kCommonEvent,(void*)&data);
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
    
    
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    
    cocos2d::LuaValueDict event;
    event["post"] = cocos2d::LuaValue::stringValue("Test POST");
    
    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(mListener, 1);
    
    return [ver UTF8String];
}

void CCAccountManager::logIn()
{

}

void CCAccountManager::logOut()
{
}

bool CCAccountManager::isLogged()
{
    return false;
}

void CCAccountManager::applicationDidFinishLaunchingWithOptions()
{
}

void CCAccountManager::applicationDidBecomeActive()
{
}

bool CCAccountManager::application(const char* url, const char* sourceApplication)
{
    return false;
}
void CCAccountManager::postMe(DictUserInfo& info, int errorcode)
{
#if CC_LUA_ENGINE_ENABLED > 0
    if(errorcode == -1){
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        
        LuaValueDict event;
        event["user"] = LuaValue::stringValue("-1");
        
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(mListener, 1);
        return;
    }
    
    
    LuaValueDict postData;
    
    DictUserInfo::iterator it = info.begin();
    
    for (; it != info.end(); ++it) {
        postData[it->first] = LuaValue::stringValue(it->second);
    }
    
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    
    LuaValueDict event;
    event["user"] = LuaValue::dictValue(postData);
    
    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(mListener, 1);
#endif
}

void CCAccountManager::postShare(int errorcode)
{
#if CC_LUA_ENGINE_ENABLED > 0
    if (errorcode == -1){
        
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        LuaValueDict event;
        event["share"] = LuaValue::stringValue("-1");
        
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(mListener, 1);
        
    }else{
        
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        LuaValueDict event;
        event["share"] = LuaValue::stringValue("1");
        
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(mListener, 1);
    }
#endif
}

void CCAccountManager::postFriends(UsersVector& info, int errorcode)
{
#if CC_LUA_ENGINE_ENABLED > 0
    
    if(errorcode == -1){
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        
        LuaValueDict event;
        event["friends"] = LuaValue::stringValue("-1");
        
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(mListener, 1);
        return;
    }
    
    size_t count = info.size();
    LuaValueDict usersdict;
    
    for (int i=0; i < count; ++i) {
        
        DictUserInfo user = info[i];
        DictUserInfo::iterator it = user.begin();
        
        LuaValueDict userdict;
        
        for (; it != user.end(); ++it) {
            userdict[it->first] = LuaValue::stringValue(it->second);
        }
        
        std::string key = "user"+std::to_string(i+1);
        
        usersdict[key.c_str()] = LuaValue::dictValue(userdict);
    }
    
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    
    LuaValueDict event;
    event["friends"] = LuaValue::dictValue(usersdict);
    
    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(mListener, 1);
#endif
}

void CCAccountManager::postInviteFriends(int errorcode)
{
#if CC_LUA_ENGINE_ENABLED > 0
    
    if (errorcode == -1){
        
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        LuaValueDict event;
        event["inviteFriends"] = LuaValue::stringValue("-1");
        
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(mListener, 1);
        
    }else{
        
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        LuaValueDict event;
        event["inviteFriends"] = LuaValue::stringValue("1");
        
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(mListener, 1);
    }
#endif
}

void CCAccountManager::postPhoto(const char* profileID, const char* name,const char* path, int errorcode)
{
#if CC_LUA_ENGINE_ENABLED > 0
    
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

void CCAccountManager::requestFriends()
{
}

void CCAccountManager::inviteFriends()
{
}

void CCAccountManager::shareText(const char* text)
{

}

void CCAccountManager::share(const char* theName,const char* theCaption,const char* theDesc,const char* thePictureURL,const char* theLink)
{

}
void CCAccountManager::purgeSharedAccountManager(void)
{
    if (s_sharedAccountManager)
    {
        delete s_sharedAccountManager;
        s_sharedAccountManager = NULL;
    }
}

void CCAccountManager::downloadPhoto(const char *fbID)
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
    pRequest->setResponseCallback(CC_CALLBACK_2(CCAccountManager::onHttpRequestCompleted, this));
    pRequest->setTag(fbID);
    
    HttpClient::getInstance()->send(pRequest);
    pRequest->release();
    
    
}

void CCAccountManager::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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

const char* CCAccountManager::UDID()
{
    
    return "";
}

void CCAccountManager::preloadFinish()
{
}

void CCAccountManager::applicationDidFinishLaunchingReport()
{
    
    std::string udid = UDID();
    std::string idfa = getIdfa();
    std::string idfv = getIdfv();
    
    std::string downloadURL = StringUtils::format("http://104.200.30.18:8020/appstart?udid=%s&idfa=%s&idfv=%s", udid.c_str(), idfa.c_str(), idfv.c_str());
    
    HttpRequest* pRequest = new HttpRequest();
    pRequest->setUrl((downloadURL.c_str()));
    pRequest->setRequestType(HttpRequest::Type::GET);
    pRequest->setResponseCallback(CC_CALLBACK_2(CCAccountManager::applicationDidFinishLaunchingReportCompleted, this));
    
    HttpClient::getInstance()->send(pRequest);
    pRequest->release();
    
}

void CCAccountManager::applicationDidFinishLaunchingReportCompleted(HttpClient *sender, HttpResponse *response)
{
    
}

const char* CCAccountManager::getIdfa()
{
    return "";
}

const char* CCAccountManager::getIdfv()
{
    return "";
}
