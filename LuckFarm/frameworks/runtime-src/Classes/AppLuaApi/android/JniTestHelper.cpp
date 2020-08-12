#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "JniTestHelper.h"
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCLuaEngine.h"
#include "AppLuaApi.h"
#import "NetDataManager.h"
#include "ImagePicker.h"

using namespace cocos2d;

extern "C"
{

    
    // void Java_com_hongbogufen_hongboyicai_JniTestHelper_setShowShakePhone(JNIEnv*  env, jobject thiz,jint flag)
    // {
    //     CCLog(">>>JNI<<< Java_com_hongbogufen_hongboyicai_JniTestHelper_setShowShakePhone!");
    //     CCLOG("%d", flag);
        
        
    //     ShakePhone::sharedShakePhone() -> showShakePhone(flag);
    // }

    void Java_com_hongbogufen_hongboyicai_JniTestHelper_setShowEncryptWithRsa(JNIEnv*  env, jobject thiz,jstring xmlContent)
    {
        CCLog(">>>JNI<<< Java_com_hongbogufen_hongboyicai_JniTestHelper_setShowEncryptWithRsa!");
        CCLOG("%s", xmlContent);
        
        CCString *ret = NULL;
        
        if (xmlContent != NULL)
        {
            ret = new CCString(JniHelper::jstring2string(xmlContent).c_str());
            ret->autorelease();
        }

        AppLuaApi::getInstance() -> showEncryptWithRsa(ret->getCString());
    }

    void Java_com_hongbogufen_hongboyicai_JniTestHelper_setDestoryActivity(JNIEnv*  env, jobject thiz)
    {
        CCLog(">>>JNI<<< Java_com_hongbogufen_hongboyicai_JniTestHelper_setDestoryActivity!");

        NetDataManager::sharedNetDataManager()->postQuit();

    }

    void Java_com_hongbogufen_hongboyicai_JniTestHelper_returnToLuaWithOpenIDAndAccessToken(JNIEnv*  env, jobject thiz,jstring openId,jstring accessToken)
    {
        CCLog(">>>JNI<<< Java_com_hongbogufen_hongboyicai_JniTestHelper_returnToLuaWithOpenIDAndAccessToken!");
        CCLOG("openId = %s", openId);
        CCLOG("accessToken = %s", accessToken);
        
        CCString *openIdRet = NULL;
        CCString *accessTokenRet = NULL;
        
        if (openId != NULL)
        {
            openIdRet = new CCString(JniHelper::jstring2string(openId).c_str());
            openIdRet->autorelease();
        }

        if (accessToken != NULL)
        {
            accessTokenRet = new CCString(JniHelper::jstring2string(accessToken).c_str());
            accessTokenRet->autorelease();
        }

        NetDataManager::sharedNetDataManager() -> returnToLuaWithOpenIDAndAccessToken(openIdRet->getCString(),accessTokenRet->getCString());
    }

    void Java_com_hongbogufen_hongboyicai_JniTestHelper_getTokenFromLuaRequestWithCode(JNIEnv*  env, jobject thiz,jstring code)
    {
        CCLog(">>>JNI<<< Java_com_hongbogufen_hongboyicai_JniTestHelper_getTokenFromLuaRequestWithCode!");
        CCLOG("%s", code);
        
        CCString *ret = NULL;
        
        if (code != NULL)
        {
            ret = new CCString(JniHelper::jstring2string(code).c_str());
            ret->autorelease();
        }

        NetDataManager::sharedNetDataManager() -> getOpenTokenAndOpenIdFromWeiXinWithUrl(ret->getCString());
    }

    void Java_com_hongbogufen_hongboyicai_JniTestHelper_weiXinLoginCancel(JNIEnv*  env, jobject thiz,jstring code)
    {
        CCLog(">>>JNI<<< Java_com_hongbogufen_hongboyicai_JniTestHelper_weiXinLoginCancel!");
        CCLOG("微信取消登陆");
        
        CCString *ret = NULL;
        
        if (code != NULL)
        {
            ret = new CCString(JniHelper::jstring2string(code).c_str());
            ret->autorelease();
        }

        ImagePicker::sharedImagePicker() -> updateUserImg(""); //执行微信取消的回调
    

    }

  
    void Java_com_hongbogufen_hongboyicai_JniTestHelper_returnToLuaWithNotificationInfo(JNIEnv*  env, jobject thiz,jstring userInfo,jstring clientType)
    {
        CCLog(">>>JNI<<< Java_com_hongbogufen_hongboyicai_JniTestHelper_returnToLuaWithNotificationInfo!");
        
        CCString *userInfoRet = NULL;
        CCString *clientTypeRet = NULL;
        
        if (userInfo != NULL)
        {
            userInfoRet = new CCString(JniHelper::jstring2string(userInfo).c_str());
            userInfoRet->autorelease();
        }

        if (clientType != NULL)
        {
            clientTypeRet = new CCString(JniHelper::jstring2string(clientType).c_str());
            clientTypeRet->autorelease();
        }

        NetDataManager::sharedNetDataManager() -> returnToLuaWithAndroidNotificationInfo(userInfoRet->getCString(),clientTypeRet->getCString());
    }

    void Java_com_hongbogufen_hongboyicai_JniTestHelper_sendLLpayResultToServer(JNIEnv*  env, jobject thiz,jstring retCode,jstring retMsg,jstring resultPay,jstring oidPaybill,jstring moneyOrder,jstring noOrder)
    {
        CCLog(">>>JNI<<< Java_com_hongbogufen_hongboyicai_JniTestHelper_sendLLpayResultToServer!");
        
        CCString *retCodeRet = NULL;
        CCString *retMsgRet = NULL;
        CCString *resultPayRet = NULL;
        CCString *oidPaybillRet = NULL;
        CCString *moneyOrderRet = NULL;
        CCString *noOrderRet = NULL;
        

        if (retCode != NULL)
        {
            retCodeRet = new CCString(JniHelper::jstring2string(retCode).c_str());
            retCodeRet->autorelease();
        }

        if (retMsg != NULL)
        {
            retMsgRet = new CCString(JniHelper::jstring2string(retMsg).c_str());
            retMsgRet->autorelease();
        }

        if (resultPay != NULL)
        {
            resultPayRet = new CCString(JniHelper::jstring2string(resultPay).c_str());
            resultPayRet->autorelease();
        }

        if (oidPaybill != NULL)
        {
            oidPaybillRet = new CCString(JniHelper::jstring2string(oidPaybill).c_str());
            oidPaybillRet->autorelease();
        }

        if (moneyOrder != NULL)
        {
            moneyOrderRet = new CCString(JniHelper::jstring2string(moneyOrder).c_str());
            moneyOrderRet->autorelease();
        }

        if (noOrder != NULL)
        {
            noOrderRet = new CCString(JniHelper::jstring2string(noOrder).c_str());
            noOrderRet->autorelease();
        }

        NetDataManager::sharedNetDataManager() -> sendLLpayResultToServerForAndroid(retCodeRet->getCString(),retMsgRet->getCString(),
            resultPayRet->getCString(),oidPaybillRet->getCString(),moneyOrderRet->getCString(),noOrderRet->getCString());
    }
}

#endif