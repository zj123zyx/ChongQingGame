#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "HelloWorldScene.h"
#include "FacebookInterface.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "cocos2d.h"

const char* FBJavaFriendClassName = "com/zuanyan/slotssecret/FacebookPickFriendPlugin";
const char* FBJavaLoginClassName = "com/zuanyan/slotssecret/FacebookConnectPlugin";
const char* FBJavaPostClassName = "com/zuanyan/slotssecret/FacebookPostPlugin";
const char* FBJavaSendRequestsClassName = "com/zuanyan/slotssecret/FacebookSendRequestsPlugin";
const char* FBJavaClassName = "com/zuanyan/slotssecret/FacebookConnectPlugin";

extern "C"
{
    void Java_com_zuanyan_slotssecret_FacebookConnectPlugin_nativeCallback(JNIEnv*  env, jobject thiz, jint cbIndex,jstring params)
    {
        
        if (params != NULL)
		{
            
			const char* str;
        	str = env->GetStringUTFChars(params, 0);
            
            cocos2d::CCLog("loginback%s",str);
            
        	std::string tstr(str);
			//HelloWorld::CallFunctionName(cbIndex,tstr);
		}
		else
		{
			std::string tstr = "";
			//HelloWorld::CallFunctionName(cbIndex,tstr);
		}
    }
    
    //登录成功以后的回调
    void Java_com_zuanyan_slotssecret_FacebookConnectPlugin_nativeLoginCallback(JNIEnv*  env, jobject thiz, jstring id, jstring name, jstring link, jstring token, jstring expireDate)
    {
        DictUserInfo userinfo;
        
        //const char* KEY_USER_ID                = "id";
        //const char* KEY_USER_NAME              = "name";
        //const char* KEY_USER_LINK              = "link";
        //const char* KEY_USER_TOKEN             = "token";
        //const char* KEY_USER_TOKENEXPIREDATE   = "tokenexpiredate";
        //userinfo[KEY_USER_NAME]            = [[user name] UTF8String];
        //userinfo[KEY_USER_LINK]            = [[user link] UTF8String];
        //userinfo[KEY_USER_TOKEN]           = [[[FBSession.activeSession accessTokenData ] accessToken] UTF8String];
        if (id != NULL)
		{
			const char* str;
        	str = env->GetStringUTFChars(id, 0);
            userinfo["id"]= str;
		}
        if (name != NULL)
		{
			const char* str;
        	str = env->GetStringUTFChars(name, 0);
            userinfo["name"]= str;
		}
        if (link != NULL)
		{
			const char* str;
        	str = env->GetStringUTFChars(link, 0);
            userinfo["link"]= str;
		}
        if (token != NULL)
		{
			const char* str;
        	str = env->GetStringUTFChars(token, 0);
            userinfo["token"]= str;
		}
        if (expireDate != NULL)
		{
			const char* str;
        	str = env->GetStringUTFChars(expireDate, 0);
            userinfo["tokenexpiredate"]= str;
		}
        
        cocos2d::CCLog("nativeLoginCallback=%s %s %s %s %s",userinfo["id"],userinfo["name"],userinfo["link"],userinfo["token"],userinfo["tokenexpiredate"]);
        
       // CCAccountManager::sharedAccountManager()->postMe(userinfo,1);
    }
    
    //登录失败的回调
    void Java_com_zuanyan_slotssecret_FacebookConnectPlugin_nativeLoginErrorCallback(JNIEnv*  env, jobject thiz, jint cbIndex)
    {
        cocos2d::CCLog("nativeLoginErrorCallback");
        DictUserInfo userinfo;
        
       // CCAccountManager::sharedAccountManager()->postMe(userinfo,-1);
    }
    

};
void FacebookInterface::login(int cbIndex,const char* scope){
    cocos2d::CCLog("FacebookInterface::login");
    
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , FBJavaLoginClassName
                                                , "login"
                                                , "(ILjava/lang/String;)V"))
	{
		if (scope)
		{
			jstring jeventId = t.env->NewStringUTF(scope);
			t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex,jeventId);
			t.env->DeleteLocalRef(jeventId);
		}
		else
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex,NULL);
		}
		t.env->DeleteLocalRef(t.classID);
	}
}

void FacebookInterface::logout(int cbIndex){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , FBJavaClassName
                                                , "logout"
                                                , "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex);
		t.env->DeleteLocalRef(t.classID);
	}
}

const char* FacebookInterface::getStatus(int cbIndex){
	
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
                                                , FBJavaClassName
                                                , "getStatus"
                                                , "(I)Ljava/lang/String;"))
	{
		jstring ret = (jstring)(t.env->CallStaticObjectMethod(t.classID, t.methodID,cbIndex));
        t.env->DeleteLocalRef(t.classID);
        const char* aStr = " ";
        aStr = t.env->GetStringUTFChars(ret, false);
        return aStr;
	}  
}

void FacebookInterface::pickFriend(int cbIndex){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
		, FBJavaFriendClassName
		, "pickFriend"
        , "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex);
		t.env->DeleteLocalRef(t.classID);
	}
}

void FacebookInterface::postStatus(int cbIndex,const char* name,const char* caption,const char* description,const char* link,const char* picture){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
		, FBJavaPostClassName
		, "postStatus"
		, "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
	{
		CCLOG("ajhsdkjahdkjahkjsdhakjsdhajksd");
		if (name && caption && description && link && picture)
		{
			jstring nameId = t.env->NewStringUTF(name);
			jstring captionId = t.env->NewStringUTF(caption);
			jstring descriptionId = t.env->NewStringUTF(description);
			jstring linkId = t.env->NewStringUTF(link);
			jstring pictureId = t.env->NewStringUTF(picture);

			t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex,nameId,captionId,descriptionId,linkId,pictureId);
			t.env->DeleteLocalRef(nameId);
			t.env->DeleteLocalRef(captionId);
			t.env->DeleteLocalRef(descriptionId);
			t.env->DeleteLocalRef(linkId);
			t.env->DeleteLocalRef(pictureId);
		}
		else
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex,NULL);
		}
		
		t.env->DeleteLocalRef(t.classID);
	}   
}

void FacebookInterface::sendRequests(int cbIndex){
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
		, FBJavaSendRequestsClassName
		, "sendRequests"
		, "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex);
		t.env->DeleteLocalRef(t.classID);
	}   
}
#endif
