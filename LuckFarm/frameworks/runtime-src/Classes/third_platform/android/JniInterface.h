#ifndef __JNIINTERFACE_H__
#define __JNIINTERFACE_H__

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

extern "C"
{

	extern void gotoActivityJNI();

	extern void gotoActivityJNICamera();

    
    extern void Java_com_hongbogufen_hongboyicai_UserImageUtil_nativeSetHeadImg(JNIEnv*  env, jobject thiz,jstring key);

}

#endif