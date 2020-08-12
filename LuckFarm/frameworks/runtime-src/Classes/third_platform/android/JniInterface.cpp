#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "JniInterface.h"
#include <android/log.h>
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ImagePicker.h"
#include "CCLuaEngine.h"

#define JavaJni_ClassName "com/hongbogufen/hongboyicai/UserImageUtil"


using namespace cocos2d;

extern "C"
{

    //调用打开相册的函数
	void gotoActivityJNI()
	{
        CCLog(">>>JNI<<< gotoActivityJNI!");

        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t
                                           , JavaJni_ClassName
                                           , "gotoActivity"
                                           , "()Ljava/lang/Object;"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
	}

    //调用打开照相机的函数
    void gotoActivityJNICamera()
    {

        CCLog(">>>JNI<<< gotoActivityJNICamera!");

        JniMethodInfo t;
        
        if (JniHelper::getStaticMethodInfo(t
                                           , JavaJni_ClassName
                                           , "gotoActivityCamera"
                                           , "()Ljava/lang/Object;"))
        {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }


	void Java_com_hongbogufen_hongboyicai_UserImageUtil_nativeSetHeadImg(JNIEnv*  env, jobject thiz,jstring jsonProducts)
    {
		CCLog(">>>JNI<<< Java_com_hongbogufen_hongboyicai_UserImageUtil_nativeSetHeadImg!");
        
		CCString *ret = NULL;
		
		if (jsonProducts != NULL)
		{
			ret = new CCString(JniHelper::jstring2string(jsonProducts).c_str());
        	ret->autorelease();
		}
        
        const char *str= ret->getCString();
		
        ImagePicker::sharedImagePicker() -> updateUserImg(str);
    }


}

#endif