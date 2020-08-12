#ifndef __JNITESTHELPER_H__
#define __JNITESTHELPER_H__

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

extern "C"
{

    //extern void Java_com_hongbogufen_hongboyicai_JniTestHelper_setShowShakePhone(JNIEnv*  env, jobject thiz,jint flag);

    extern void Java_com_hongbogufen_hongboyicai_JniTestHelper_setShowEncryptWithRsa(JNIEnv*  env, jobject thiz,jstring xmlContent);

    extern void Java_com_hongbogufen_hongboyicai_JniTestHelper_setDestoryActivity(JNIEnv*  env, jobject thiz);

    extern void Java_com_hongbogufen_hongboyicai_JniTestHelper_returnToLuaWithOpenIDAndAccessToken(JNIEnv*  env, jobject thiz,jstring openId,jstring accessToken);

    extern void Java_com_hongbogufen_hongboyicai_JniTestHelper_getTokenFromLuaRequestWithCode(JNIEnv*  env, jobject thiz,jstring code);

    extern void Java_com_hongbogufen_hongboyicai_JniTestHelper_returnToLuaWithNotificationInfo(JNIEnv*  env, jobject thiz,jstring userInfo,jstring clientType);

    extern void Java_com_hongbogufen_hongboyicai_JniTestHelper_sendLLpayResultToServer(JNIEnv*  env, jobject thiz,jstring retCode,jstring retMsg,jstring resultPay,jstring oidPaybill,jstring moneyOrder,jstring noOrder);

    extern void Java_com_hongbogufen_hongboyicai_JniTestHelper_weiXinLoginCancel(JNIEnv*  env, jobject thiz,jstring code);
}

#endif