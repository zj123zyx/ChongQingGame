#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "JniInterface.h"
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "cocos2d.h"
#include "AndroidStoreKit.h"
#include "support/CCNotificationCenter.h"

#define JavaJni_ClassName "com/zuanyan/slotssecret/googleplay/JavaJniLibs"


using namespace cocos2d;

extern "C"
{

	void jniCpp2Java(const char* id)
	{
		JniMethodInfo methodInfo;

		CCLog("jniCpp2Java jni c++");
														 
		if (!JniHelper::getStaticMethodInfo(methodInfo, JavaJni_ClassName, "jniCpp2Java", "(Ljava/lang/String;)V"))
		{
			CCLog("sendToMMAppId failed in JniInterface");
			return;
		}
		jstring l_stringUrl = methodInfo.env->NewStringUTF(id);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, l_stringUrl);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);		
		methodInfo.env->DeleteLocalRef(l_stringUrl);	
	}


	void fetchAllProductsJNI(const char* jsonProductIDs)
	{
		CCLog(">>>JNI<<< fetchAllProductsJNI!");

        JniMethodInfo methodInfo;
									 
		if (!JniHelper::getStaticMethodInfo(methodInfo, JavaJni_ClassName, "fetchAllProducts", "(Ljava/lang/String;)V"))
		{
			CCLog("fetchAllProductsJNI failed in JniInterface");
			return;
		}
		jstring l_stringUrl = methodInfo.env->NewStringUTF(jsonProductIDs);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, l_stringUrl);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);		
		methodInfo.env->DeleteLocalRef(l_stringUrl);	
	}

    //调用购买的函数
	void purchaseProductJNI(const char* productID,const char* payload)
	{

        CCLog(">>>JNI<<< purchaseProductJNI!");

        JniMethodInfo methodInfo;
									 
		if (!JniHelper::getStaticMethodInfo(methodInfo, JavaJni_ClassName, "purchaseProduct", "(Ljava/lang/String;Ljava/lang/String;)V"))
		{
			CCLog("purchaseProductJNI failed in JniInterface");
			return;
		}
		jstring l_stringUrl1 = methodInfo.env->NewStringUTF(productID);
		jstring l_stringUrl2 = methodInfo.env->NewStringUTF(payload);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, l_stringUrl1,l_stringUrl2);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);		
		methodInfo.env->DeleteLocalRef(l_stringUrl1);
		methodInfo.env->DeleteLocalRef(l_stringUrl2);
	}


	void Java_com_zuanyan_slotssecret_googleplay_nativeFetchAllProductsCompleted(JNIEnv*  env, jobject thiz,jstring jsonProducts)
    {
		CCLog(">>>JNI<<< Java_com_zuanyan_slotssecret_googleplay_nativeFetchAllProductsCompleted!");

		CCString *ret = NULL;
		
		if (jsonProducts != NULL)
		{
			ret = new CCString(JniHelper::jstring2string(jsonProducts).c_str());
        	ret->autorelease();
		}
		
		CCNotificationCenter::sharedNotificationCenter()->postNotification("NotificationFetchProductsDataCompleted",
				ret);
		// CasinoStoreKit::sharedStoreKit() -> fetchProductsDataCompleted(ret);
    }

	void Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativePurchaseProductCompleted(JNIEnv* env,jobject thiz,jstring jsonResult)
	{
		CCLog(">>>JNI<<< Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativePurchaseProductCompleted!");

		CCString *ret = NULL;
		
		if (jsonResult != NULL)
		{
			ret = new CCString(JniHelper::jstring2string(jsonResult).c_str());
        	ret->autorelease();
		}

		CCNotificationCenter::sharedNotificationCenter()->postNotification("NotificationPurchaseProductCompleted",
				ret);
		// CasinoStoreKit::sharedStoreKit() -> purchaseProductCompleted(ret);
	}

    //目前android调用的是这个函数
	void Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativeConsumeProductCompleted(JNIEnv* env,jobject thiz,jstring jsonResult,jstring signature)
	{
		
		CCLog(">>>JNI<<< Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativeConsumeProductCompleted!");

		CCString *ret = NULL;
		
		if (jsonResult != NULL)
		{
			ret = new CCString(JniHelper::jstring2string(jsonResult).c_str());
        	ret->autorelease();
		}
        
        CCString *sig = NULL;
        
        if (signature != NULL)
		{
			sig = new CCString(JniHelper::jstring2string(signature).c_str());
        	sig->autorelease();
		}

		//CCNotificationCenter::sharedNotificationCenter()->postNotification("NotificationTransactionCompleted",ret);
		// CasinoStoreKit::sharedStoreKit() -> transactionCompleted(ret);
        AndroidStoreKit::sharedStoreKit() -> transactionCompleted(ret,sig);
	}
    
    void Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativeConsumeProductError(JNIEnv* env,jobject thiz,jint code,jstring message)
	{
		
		CCLog(">>>JNI<<< Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativeConsumeProductError!");
        
		CCString *ret = NULL;
		
		if (message != NULL)
		{
			ret = new CCString(JniHelper::jstring2string(message).c_str());
        	ret->autorelease();
		}
        
		//CCNotificationCenter::sharedNotificationCenter()->postNotification("NotificationTransactionCompleted",ret);
		// CasinoStoreKit::sharedStoreKit() -> transactionCompleted(ret);
        AndroidStoreKit::sharedStoreKit() -> transactionError(code,ret);
	}
    
    void Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativeUserReport(JNIEnv* env,jobject thiz)
    {
        CCLog(">>>JNI<<< Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativeUserReport!");
        //userReportCallBackJNI();
        CCLog("APP_ANDROID_QUIT_EVENT start");
        CCNotificationCenter::sharedNotificationCenter()->postNotification("APP_ANDROID_QUIT_EVENT");
        CCLog("APP_ANDROID_QUIT_EVENT end");
    }
    
    void trackingWithEventJNI(const char* eventName,const char* value)
    {
        CCLog(">>>JNI<<< trackingWithEventJNI!");
        
        JniMethodInfo methodInfo;
        
		if (!JniHelper::getStaticMethodInfo(methodInfo, "com/zuanyan/slotssecret/util/AppsFlyeUtil", "trackingWithEvent", "(Ljava/lang/String;Ljava/lang/String;)V"))
		{
			CCLog("trackingWithEventJNI failed in JniInterface");
			return;
		}
		jstring l_stringUrl1 = methodInfo.env->NewStringUTF(eventName);
		jstring l_stringUrl2 = methodInfo.env->NewStringUTF(value);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, l_stringUrl1,l_stringUrl2);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(l_stringUrl1);
		methodInfo.env->DeleteLocalRef(l_stringUrl2);
    }


	bool  getIsProcessDialogShowJni()
	{
		JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t
            , JavaJni_ClassName
            , "isProcessDialogShow"
            , "()I"))
        {
            int code = t.env->CallStaticIntMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);

            return code != 0;
        }

        return true;

	}

	void showProgressDialogJNI()
	{
		JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t
            , JavaJni_ClassName
            , "showProgressDialog"
            , "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
        }

	}
	
	void hideProgressDialogJNI()
	{
		
		JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t
            , JavaJni_ClassName
            , "hideProgressDialog"
            , "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
        }

	}	

	void openURLJNI(const char *url)
	{
		JniMethodInfo t;

		CCLOG("openURLJNI:%s",url);

        if (JniHelper::getStaticMethodInfo(t
            , JavaJni_ClassName
            , "openURL"
            , "(Ljava/lang/String;)V"))
        {
            if (url)
            {
				jstring stringArg1;
                stringArg1 = t.env->NewStringUTF(url);

				//jclass cocos2dxActivityClass = t.env->FindClass(JavaJni_ClassName);
				//jobject cocos2dxActivityClassInstance = getInstance(t.env,cocos2dxActivityClass);

            	t.env->CallStaticVoidMethod(t.classID,t.methodID,stringArg1);
				t.env->DeleteLocalRef(t.classID);
				t.env->DeleteLocalRef(stringArg1);

            }
        }

	}
	
	bool getBooleanValueInSharePreferencesForKeyJNI(const char *key)
	{
		JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t
            , JavaJni_ClassName
            , "getBooleanValueInSharedPreferencesForKey"
            , "(Ljava/lang/String;)Z"))
        {
			if (key)
			{
				jstring stringArg1 = t.env->NewStringUTF(key);

            	bool ret = t.env->CallStaticBooleanMethod(t.classID,t.methodID,stringArg1);
				t.env->DeleteLocalRef(t.classID);
				t.env->DeleteLocalRef(stringArg1);

				return ret;
			}

        }

        return false;
	}
	
	void setBooleanValueInSharedPreferencesJNI(bool value,const char *key)
	{
		JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t
            , JavaJni_ClassName
            , "setBooleanValueInSharedPreferences"
            , "(ZLjava/lang/String;)V"))
        {
			if (key)
			{
				jstring stringArg1 = t.env->NewStringUTF(key);

            	t.env->CallStaticVoidMethod(t.classID,t.methodID,value,stringArg1);
				t.env->DeleteLocalRef(t.classID);
				t.env->DeleteLocalRef(stringArg1);

			}

        }
	
	}

	void removeValueInSharedPreferencesForKeyJNI(const char *key)
	{
	
		JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t
            , JavaJni_ClassName
            , "removeValueInSharedPreferencesForKey"
            , "(Ljava/lang/String;)V"))
        {
			if (key)
			{
				jstring stringArg1 = t.env->NewStringUTF(key);

            	t.env->CallStaticVoidMethod(t.classID,t.methodID,stringArg1);
				t.env->DeleteLocalRef(t.classID);
				t.env->DeleteLocalRef(stringArg1);

			}

        }

	}

	const char *getAppFValueJNI()
	{

		JniMethodInfo t;

        if (JniHelper::getStaticMethodInfo(t
            , JavaJni_ClassName
            , "getAppFValue"
            , "()Ljava/lang/String;"))
        {

            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID,t.methodID);
            t.env->DeleteLocalRef(t.classID);
			CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
            ret->autorelease();
            t.env->DeleteLocalRef(str);

			return ret -> getCString();

        }
	
		return 0;

	}
    
    void userReportCallBackJNI()
	{
		
		JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t
                                           , JavaJni_ClassName
                                           , "userReportCallBack"
                                           , "()V"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
        }
        
	}

}

#endif