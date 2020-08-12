
#include "CCAccountManager.h"
#include <sstream>
#include "cocos2d.h"
//#include "Config.h"
#include "CCLuaEngine.h"
#include "platform/android/jni/JniHelper.h"

#include <android/log.h>
#include <string.h>
#include <jni.h>


#define JavaJni_AccountManager_ClassName "com/hongbogufen/hongboyicai/AccountManager"


using namespace cocos2d;

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

// #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
void CCAccountManager::preloadFinish()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                       JavaJni_AccountManager_ClassName,
                                       "preloadFinish",
                                       "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}
// #endif

void CCAccountManager::downloadNewApp(const char* url)
{
    // openURLJNI(STORE_URL_ANDROID);
    JniMethodInfo t;
    
    CCLOG("downloadNewApp:%s",url);
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AccountManager_ClassName, "downloadNewApp", "(Ljava/lang/String;)V")) {
        if (url)
        {
            jstring stringArg1;
            stringArg1 = t.env->NewStringUTF(url);
            t.env->CallStaticVoidMethod(t.classID,t.methodID,stringArg1);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg1);
        }
    }
}

void CCAccountManager::showIndicator()
{
    // showProgressDialogJNI();

    // cocos2d::JniMethodInfo t;
    // if (cocos2d::JniHelper::getStaticMethodInfo(t,JavaJni_AccountManager_ClassName,"showIndicator","()V")) 
    // {
    //     t.env->CallStaticVoidMethod(t.classID, t.methodID);
    //     t.env->DeleteLocalRef(t.classID);
    // }

    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, JavaJni_AccountManager_ClassName, "showIndicator", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }


}

void CCAccountManager::hideIndicator()
{
    // hideProgressDialogJNI();
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,JavaJni_AccountManager_ClassName,"hideIndicator","()V")) 
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }

}

CCAccountManager::~CCAccountManager(void)
{
}

bool CCAccountManager::init(const char* nettype)
{
    m_fromNetwork = nettype;
    return true;
}

const char* CCAccountManager::UDID()
{
    cocos2d::JniMethodInfo t;
    std::string ret("");
    
    if (cocos2d::JniHelper::getStaticMethodInfo(t, JavaJni_AccountManager_ClassName, "getUUID", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = cocos2d::JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    
    CCString *pRet = CCString::create(ret);
    
    return pRet->getCString();
}

const char* CCAccountManager::AppVersion()
{  
    JniMethodInfo t;
    std::string ret("1.22");
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AccountManager_ClassName, "getAppVersion", "()Ljava/lang/String;")) {
    // if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lua/test", "showIndicator", "()V")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = cocos2d::JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }

    
    CCString *pRet = CCString::create(ret);
    
    return pRet->getCString();
}

const char* CCAccountManager::ResVersion()
{
    cocos2d::JniMethodInfo t;
    std::string ret("");
    
    if (cocos2d::JniHelper::getStaticMethodInfo(t, JavaJni_AccountManager_ClassName, "getResVersion", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = cocos2d::JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    
    CCString *pRet = CCString::create(ret);
    
    return pRet->getCString();
}

const char* CCAccountManager::SystemVersion()
{
    cocos2d::JniMethodInfo t;
    std::string ret("");
    
    if (cocos2d::JniHelper::getStaticMethodInfo(t, JavaJni_AccountManager_ClassName, "getSystemVersion", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = cocos2d::JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    
    CCString *pRet = CCString::create(ret);
    
    return pRet->getCString();
}

// use os.time() instead in lua
// const char* CCAccountManager::SystemTime()
// {
//     return "2015-10-20 10:30:20";
// }

// use os.time() instead in lua
// const char* CCAccountManager::getDayTime(const char* millSecond)
// {
//     return "todo";
// }

void CCAccountManager::logIn()
{
    if ( strcmp(m_fromNetwork.c_str(), "facebook") == 0)
    {
        //todo
        CCLOG("androidfb loginIn");
        // FacebookInterface::login(0, "login");
    }
}

void CCAccountManager::logOut()
{
    if ( strcmp(m_fromNetwork.c_str(), "facebook") == 0)
    {
        // FacebookInterface::logout(1);
    }
}

bool CCAccountManager::isLogged()
{
    if ( strcmp(m_fromNetwork.c_str(), "facebook") == 0)
    {
        return true;
    }
    return false;
}

void CCAccountManager::requestFriends()
{
    if ( strcmp(m_fromNetwork.c_str(), "facebook") == 0)
    {
        // todo
    }
}

void CCAccountManager::postMe(DictUserInfo& info, int errorcode)
{
// #if CC_LUA_ENGINE_ENABLED > 0
//     if(errorcode == -1){
//         CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        
//         CCLuaValueDict event;
//         event["user"] = CCLuaValue::stringValue("-1");
        
//         stack->pushCCLuaValueDict(event);
//         stack->executeFunctionByHandler(m_listener, 1);
//         return;
//     }
    
    
//     CCLuaValueDict postData;
    
//     DictUserInfo::iterator it = info.begin();

//     for (; it != info.end(); ++it) {
//         postData[it->first] = CCLuaValue::stringValue(it->second);
//     }
    
//     CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
    
//     CCLuaValueDict event;
//     event["user"] = CCLuaValue::dictValue(postData);
    
//     stack->pushCCLuaValueDict(event);
//     stack->executeFunctionByHandler(m_listener, 1);
// #endif
}

void CCAccountManager::postFriends(UsersVector& info, int errorcode)
{
// #if CC_LUA_ENGINE_ENABLED > 0
    
//     if(errorcode == -1){
//         CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        
//         CCLuaValueDict event;
//         event["friends"] = CCLuaValue::stringValue("-1");
        
//         stack->pushCCLuaValueDict(event);
//         stack->executeFunctionByHandler(m_listener, 1);
//         return;
//     }
    
//     int count = info.size();
//     CCLuaValueDict usersdict;

//     for (int i=0; i < count; ++i) {
        
//         DictUserInfo user = info[i];
//         DictUserInfo::iterator it = user.begin();
        
//         CCLuaValueDict userdict;

//         for (; it != user.end(); ++it) {
//             userdict[it->first] = CCLuaValue::stringValue(it->second);
//         }
        
//         std::string key = "user1111";
        
//         usersdict[key.c_str()] = CCLuaValue::dictValue(userdict);
//     }
    
//     CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
    
//     CCLuaValueDict event;
//     event["friends"] = CCLuaValue::dictValue(usersdict);
    
//     stack->pushCCLuaValueDict(event);
//     stack->executeFunctionByHandler(m_listener, 1);
// #endif
}

void CCAccountManager::postInviteFriends(int errorcode)
{
// #if CC_LUA_ENGINE_ENABLED > 0
    
//     if (errorcode == -1){
        
//         CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
//         CCLuaValueDict event;
//         event["inviteFriends"] = CCLuaValue::stringValue("-1");
        
//         stack->pushCCLuaValueDict(event);
//         stack->executeFunctionByHandler(m_listener, 1);
        
//     }else{
        
//         CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
//         CCLuaValueDict event;
//         event["inviteFriends"] = CCLuaValue::stringValue("1");
        
//         stack->pushCCLuaValueDict(event);
//         stack->executeFunctionByHandler(m_listener, 1);
//     }
// #endif
}

void CCAccountManager::postShare(int errorcode)
{
// #if CC_LUA_ENGINE_ENABLED > 0
//     if (errorcode == -1){
        
//         CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
//         CCLuaValueDict event;
//         event["share"] = CCLuaValue::stringValue("-1");
        
//         stack->pushCCLuaValueDict(event);
//         stack->executeFunctionByHandler(m_listener, 1);
        
//     }else{
        
//         CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
//         CCLuaValueDict event;
//         event["share"] = CCLuaValue::stringValue("1");
        
//         stack->pushCCLuaValueDict(event);
//         stack->executeFunctionByHandler(m_listener, 1);
//     }
// #endif
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

void CCAccountManager::applicationDidFinishLaunchingWithOptions()
{
    if ( strcmp(m_fromNetwork.c_str(), "facebook") == 0)
    {
        // [[CCFaceBookIOS sharedFaceBook] applicationDidFinishLaunchingWithOptions];
        // todo
    }
}

void CCAccountManager::applicationDidBecomeActive()
{
    if ( strcmp(m_fromNetwork.c_str(), "facebook") == 0)
    {
        // [[CCFaceBookIOS sharedFaceBook] applicationDidBecomeActive];
        // todo
    }
}

bool CCAccountManager::application(const char* url, const char* sourceApplication)
{
    if ( strcmp(m_fromNetwork.c_str(), "facebook") == 0)
    {
        // NSString* urlString = [[NSString alloc] initWithCString:url encoding:NSUTF8StringEncoding];
        // NSURL* urlObj = [[NSURL alloc] initWithString:urlString];
        // NSString* srcString = nil;
        // if (sourceApplication != nil)
        //     srcString = [[NSString alloc] initWithCString:sourceApplication encoding:NSUTF8StringEncoding];

        // return [[CCFaceBookIOS sharedFaceBook] application:urlObj sourceApplication:srcString];
        return false;
    }
    if ( strcmp(m_fromNetwork.c_str(), "google") == 0)
    {
        return false;
    }
    return false;
}

void CCAccountManager::shareText(const char* text)
{
    // NSString* textString = [[NSString alloc] initWithCString:text encoding:NSUTF8StringEncoding];
    // [[CCFaceBookIOS sharedFaceBook] shareText:textString];
    // todo

}

void CCAccountManager::share(const char* theName,const char* theCaption,const char* theDesc,const char* thePictureURL,const char* theLink)
{
    // todo
}
void CCAccountManager::purgeSharedAccountManager(void)
{
    if (s_sharedAccountManager)
    {
        delete s_sharedAccountManager;
        s_sharedAccountManager = NULL;
    }
}

void CCAccountManager::inviteFriends()
{
    // [[CCFaceBookIOS sharedFaceBook] inviteFriends];
    // FacebookInterface::sendRequests(1);
}
// void CCAccountManager::pickPlace()
// {
//     // [[CCFaceBookIOS sharedFaceBook] pickPlace];
// }
// void CCAccountManager::pickPhoto(int pickType)
// {
//     // [[CCFaceBookIOS sharedFaceBook] pickPhoto:pickType];
// }

void CCAccountManager::downloadPhoto(const char *fbID)
{

    std::string fileName = StringUtils::format("%s_square.png",fbID);
    
    // Save file for resue.
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    writablePath = writablePath + fileName;
    // if(FileUtils::getInstance()->isFileExist(writablePath.c_str())){
    //     postPhoto(fbID, fileName.c_str(), writablePath.c_str(),1);
    //     return;
    // }

    if(FileUtils::getInstance()->isFileExist(writablePath.c_str())){
        unsigned char* pBuffer = NULL;
        ssize_t bufferSize = 0;
        pBuffer = FileUtils::getInstance()->getFileData(writablePath.c_str(), "r", &bufferSize);
        if(bufferSize>0)
        {
            postPhoto(fbID, fileName.c_str(), writablePath.c_str(),1);
            return;
        }
    }
    
    std::string downloadURL = StringUtils::format("http://graph.facebook.com/%s/picture?type=square",fbID);

    HttpRequest* pRequest = new HttpRequest();
    pRequest->setUrl((downloadURL.c_str()));

    // pRequest->setUrl("http://graph.facebook.com/795555483874735/picture?type=square");
    pRequest->setRequestType(HttpRequest::Type::GET);
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

    int responseCode = response->getResponseCode();

    CCLOG("response code: %d ", responseCode);
    
    if (responseCode > 300 && responseCode < 400){

        std::vector<char> *header = response->getResponseHeader();

        std::string str(header->begin(), header->end());

        // CCLOG("response header: %s ", str.c_str());

        std::string::size_type pos1, pos2;

        std::string reg = "\n";
        std::string reg2 = "Location:";

        pos1 = 0;
        pos2 = str.find(reg);
        
        std::string subStr;
        std::string location;
          
        while(std::string::npos != pos2)
        {

            subStr = str.substr(pos1, pos2-pos1);

            if (subStr.find(reg2) != std::string::npos)
            {
                location = subStr.substr(reg2.size());
                break;
            }
         
            pos1 = pos2 + reg.size();
            pos2 = str.find(reg, pos1);

        }

        CCLOG("response header Location: %s ", location.c_str());

        HttpRequest* pRequest = new HttpRequest();
        pRequest->setUrl(location.c_str());
        pRequest->setRequestType(HttpRequest::Type::GET);
        pRequest->setResponseCallback(CC_CALLBACK_2(CCAccountManager::onHttpRequestCompleted, this));
        pRequest->setTag(response->getHttpRequest()->getTag());
        
        HttpClient::getInstance()->send(pRequest);
        pRequest->release();

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

void CCAccountManager::postFBListenerLua(cocos2d::LUA_FUNCTION listener)
{
    if (mListener)
    {
       cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(mListener);
    }
    mListener = listener;
}
void CCAccountManager::applicationDidFinishLaunchingReport()
{
    
}

void CCAccountManager::applicationDidFinishLaunchingReportCompleted(HttpClient *sender, HttpResponse *response)
{
    
}

const char* CCAccountManager::getIdfa()
{
    return "null";
}

const char* CCAccountManager::getIdfv()
{
    return "null";
}