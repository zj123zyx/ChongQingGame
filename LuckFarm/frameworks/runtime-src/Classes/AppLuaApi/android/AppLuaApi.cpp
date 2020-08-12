
#include "AppLuaApi.h"
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "CCScriptSupport.h"
#include "Config.h"
#include "CCLuaEngine.h"
#include "platform/android/jni/JniHelper.h"

// #include "JniHelper.h"
#include <android/log.h>
#include <string.h>
#include <jni.h>

// #include "JniInterface.h"

#define JavaJni_AppLuaApi_ClassName "com/hongbogufen/hongboyicai/AppLuaApi"

#define STORE_URL_ANDROID       "http://123.57.172.138/static/app/casino_cn/app_casino_cn_"

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

void AppLuaApi::downloadNewApp(const char *mainVersion)
{
    // openURLJNI(STORE_URL_ANDROID);
    JniMethodInfo t;
    
    //CCLOG("openURLJNI:%s",STORE_URL_ANDROID);
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "downloadNewApp", "(Ljava/lang/String;)V")) {
        if (STORE_URL_ANDROID)
        {
            jstring stringArg1;
            std::string downloadurl = STORE_URL_ANDROID + std::string(mainVersion) + ".apk";
            stringArg1 = t.env->NewStringUTF(downloadurl.c_str());
            t.env->CallStaticVoidMethod(t.classID,t.methodID,stringArg1);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(stringArg1);
        }
    }
}

AppLuaApi::~AppLuaApi(void)
{
}

void AppLuaApi::showIndicator()
{
    CCLOG("AppLuaApi::showIndicator");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "showIndicator", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    
    
}

void AppLuaApi::hideIndicator()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,JavaJni_AppLuaApi_ClassName,"hideIndicator","()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void AppLuaApi::setIsNeedShowWait(bool isNeed){
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,JavaJni_AppLuaApi_ClassName,"setIsNeedShowWait","(Z)V"))
    {
        jboolean jisNeed =isNeed;
        t.env->CallStaticVoidMethod(t.classID, t.methodID,jisNeed);
        t.env->DeleteLocalRef(t.classID);
    }
}
#endif

const char* AppLuaApi::UDID()
{
    CCLOG("AppLuaApi::UDID");
    cocos2d::JniMethodInfo t;
    std::string ret("");
    
    if (cocos2d::JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "getUUID", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = cocos2d::JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    
    CCString *pRet = CCString::create(ret);
    
    return pRet->getCString();
}

const char* AppLuaApi::AppVersion()
{  
    JniMethodInfo t;
    std::string ret("1.0");
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "getAppVersion", "()Ljava/lang/String;")) {
    // if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lua/test", "showIndicator", "()V")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = cocos2d::JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }

    
    CCString *pRet = CCString::create(ret);
    
    return pRet->getCString();
}
const char* AppLuaApi::AppVersionCode()
{  
    JniMethodInfo t;
    std::string ret("1");
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "getAppVersionCode", "()Ljava/lang/String;")) {
    // if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lua/test", "showIndicator", "()V")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = cocos2d::JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }

    
    CCString *pRet = CCString::create(ret);
    
    return pRet->getCString();
}
const char* AppLuaApi::ResVersion()
{
    cocos2d::JniMethodInfo t;
    std::string ret("");
    
    if (cocos2d::JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "getResVersion", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = cocos2d::JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    
    CCString *pRet = CCString::create(ret);
    
    return pRet->getCString();
}

const char* AppLuaApi::SystemVersion()
{
    cocos2d::JniMethodInfo t;
    std::string ret("");
    
    if (cocos2d::JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "getSystemVersion", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = cocos2d::JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    
    CCString *pRet = CCString::create(ret);
    
    return pRet->getCString();
}

void AppLuaApi::postPhoto(const char* profileID, const char* name,const char* path, int errorcode)
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

void AppLuaApi::purgeInstance(void)
{
    if (s_AppLuaApiInstance)
    {
        delete s_AppLuaApiInstance;
        s_AppLuaApiInstance = NULL;
    }
}

void AppLuaApi::downloadPhoto(const char *fbID)
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
    pRequest->setResponseCallback(CC_CALLBACK_2(AppLuaApi::onHttpRequestCompleted, this));
    pRequest->setTag(fbID);
    
    HttpClient::getInstance()->send(pRequest);
    pRequest->release();
    
    
}

void AppLuaApi::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
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
        pRequest->setResponseCallback(CC_CALLBACK_2(AppLuaApi::onHttpRequestCompleted, this));
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

void AppLuaApi::postFBListenerLua(cocos2d::LUA_FUNCTION listener)
{
    if (mListener)
    {
       cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(mListener);
    }
    mListener = listener;
}

void AppLuaApi::encryptWithRsa(const char* xmlContent)
{
    // openURLJNI(STORE_URL_ANDROID);
    JniMethodInfo t;
    
    if (!JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "doEncryptWithRsa", "(Ljava/lang/String;)V")) 
    {
       CCLog("sendToMMAppId failed in JniInterface");
       return; 
    }
    jstring stringArg1 = t.env->NewStringUTF(xmlContent);
    t.env->CallStaticVoidMethod(t.classID,t.methodID,stringArg1);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(stringArg1);
}

void AppLuaApi::showEncryptWithRsa(const char* xmlContent)
{
   cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
   LuaValueDict event;
   event["xmlContent"] = LuaValue::stringValue(xmlContent);
   
   stack->pushLuaValueDict(event);
   stack->executeFunctionByHandler(mListener, 1);
}

//汉字转utf-8
const char* AppLuaApi::stringToUtf8(const char *str)
{  
    //log("AppLuaApi::stringToUtf8 = %s", str);
    JniMethodInfo t;
    std::string ret("");
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "convertStringToUTF8", "(Ljava/lang/String;)Ljava/lang/String;")) 
    {
        //CCLog("convertStringToUTF8 succeed in JniInterface");
        jstring stringArg1 = t.env->NewStringUTF(str);
        jstring utfStr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
        ret = cocos2d::JniHelper::jstring2string(utfStr);
        t.env->DeleteLocalRef(utfStr);
    }

    CCString *pRet = CCString::create(ret);

    //log("end stringToUtf8 = %s", pRet->getCString());
    
    return pRet->getCString();

}

//utf-8转汉字
const char* AppLuaApi::utf8ToString(const char *str)
{  
    //log("AppLuaApi::utf8ToString = %s", str);
    JniMethodInfo t;
    std::string ret("");
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "convertUTF8ToString", "(Ljava/lang/String;)Ljava/lang/String;")) 
    {
        //CCLog("convertUTF8ToString succeed in JniInterface");
        jstring stringArg1 = t.env->NewStringUTF(str);
        jstring utfStr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
        ret = cocos2d::JniHelper::jstring2string(utfStr);
        t.env->DeleteLocalRef(utfStr);
    }

    CCString *pRet = CCString::create(ret);

    //log("end utf8ToString = %s", pRet->getCString());
    
    return pRet->getCString();

}

void AppLuaApi::gotoQQLogin(void)
{
    CCLOG("AppLuaApi::gotoQQLogin");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "gotoQQLogin", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

void AppLuaApi::shareQQFriend(void)
{
    CCLOG("AppLuaApi::shareQQFriend");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "shareQQFriend", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

void AppLuaApi::gotoWeiXinLogin(void)
{
    CCLOG("AppLuaApi::gotoWeiXinLogin");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "gotoWeiXinLogin", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }    
}

void AppLuaApi::shareWeChatFriend(void)
{
    CCLOG("AppLuaApi::shareWeChatFriend");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "shareWeChatFriend", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

void AppLuaApi::shareWeChatFriendQuan(void)
{
    CCLOG("AppLuaApi::shareWeChatFriendQuan");
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "shareWeChatFriendQuan", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

void AppLuaApi::app_to_call(const char *num)
{
    // openURLJNI(STORE_URL_ANDROID);
    JniMethodInfo t;
    
    if (!JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "callPhone", "(Ljava/lang/String;)V")) 
    {
       CCLog("app_to_call sendToMMAppId failed in JniInterface");
       return; 
    }
    jstring stringArg1 = t.env->NewStringUTF(num);
    t.env->CallStaticVoidMethod(t.classID,t.methodID,stringArg1);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(stringArg1);
}

void AppLuaApi::setStatusBar(const char *flag)
{
    // openURLJNI(STORE_URL_ANDROID);
    JniMethodInfo t;
    CCLog("====setStatusBar========%s",flag);
    if (!JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "setStatusBar", "(Ljava/lang/String;)V")) 
    {
       CCLog("setStatusBar sendToMMAppId failed in JniInterface");
       return; 
    }
    jstring stringArg1 = t.env->NewStringUTF(flag);
    t.env->CallStaticVoidMethod(t.classID,t.methodID,stringArg1);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(stringArg1);
}

void AppLuaApi::setJPushTag(const char * userName)
{
    JniMethodInfo t;
    CCLog("=========setJPushTag===================");
    if (!JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "setJPushTag", "(Ljava/lang/String;)V")) 
    {
       CCLog("setJPushTag sendToMMAppId failed in JniInterface");
       return; 
    }
    jstring stringArg1 = t.env->NewStringUTF(userName);
    t.env->CallStaticVoidMethod(t.classID,t.methodID,stringArg1);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(stringArg1);

}

//调用相册
void AppLuaApi::openPhotoAlbum()
{
    
    
}

//调用机
void AppLuaApi::openCamera()
{
    
    
}

//调用支付
void AppLuaApi::openLLPayForPayWith(const char *orderinfo)
{
    JniMethodInfo t;
    
    if (!JniHelper::getStaticMethodInfo(t, JavaJni_AppLuaApi_ClassName, "onClickPay", "(Ljava/lang/String;)V")) 
    {
       CCLog("onClickPay sendToMMAppId failed in JniInterface");
       return; 
    }
    jstring stringArg1 = t.env->NewStringUTF(orderinfo);
    t.env->CallStaticVoidMethod(t.classID,t.methodID,stringArg1);
    t.env->DeleteLocalRef(t.classID);
    t.env->DeleteLocalRef(stringArg1);
}
