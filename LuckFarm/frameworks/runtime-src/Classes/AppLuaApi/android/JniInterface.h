#ifndef __JNIINTERFACE_H__
#define __JNIINTERFACE_H__

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

extern "C"
{	
	extern void	jniCpp2Java(const char* id);
	
	extern void fetchAllProductsJNI(const char* jsonProductIDs);

	extern void purchaseProductJNI(const char* productID,const char* payload);

	extern void Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativeFetchAllProductsCompleted(JNIEnv*  env, jobject thiz,jstring jsonProducts);

	extern void Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativePurchaseProductCompleted(JNIEnv* env,jobject thiz,jstring jsonResult);

	extern void Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativeConsumeProductCompleted(JNIEnv* env,jobject thiz,jstring jsonResult,jstring signature);
    
    extern void Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativeConsumeProductError(JNIEnv* env,jobject thiz,jint code,jstring jsonResult);
    
    extern void Java_com_zuanyan_slotssecret_googleplay_JavaJniLibs_nativeUserReport(JNIEnv* env,jobject thiz);
    
    extern void userReportCallBackJNI();

    extern const char* getAppFValueJNI();
    
    extern bool  getIsProcessDialogShowJni();
    
    extern bool getBooleanValueInSharePreferencesForKeyJNI(const char* key);
    
	extern void setBooleanValueInSharedPreferencesJNI(bool value,const char *key);
    
	extern void removeValueInSharedPreferencesForKeyJNI(const char* key);
    
	extern void showProgressDialogJNI();
    
	extern void hideProgressDialogJNI();
    
    extern void openURLJNI(const char* url);
    
    extern void trackingWithEventJNI(const char* eventName,const char* value);

}

#endif