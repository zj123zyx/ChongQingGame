//
//  ImagePicker.cpp
//  baobing
//
//  Created by 李战平 on 5/26/15.
//
//
#include "ImagePicker.h"
#include "JniInterface.h"
#include "cocos2d.h"
#include "CCLuaEngine.h"

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

ImagePicker* ImagePicker::s_storeKit = NULL;

ImagePicker::~ImagePicker()
{
    
}

ImagePicker* ImagePicker::sharedImagePicker()
{
    if (!s_storeKit)
    {
        s_storeKit = new ImagePicker();
    }
    return s_storeKit;
}

void ImagePicker::setImgPickerListenerLua(cocos2d::LUA_FUNCTION listener)//注册执行callback
{
    if (mListener)
    {
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(mListener);
    }

    mListener = listener;
}

void ImagePicker::startImagePicker()
{
    gotoActivityJNI();
}

void ImagePicker::startImageCamera()
{
    gotoActivityJNICamera();
}

void ImagePicker::updateUserImg(const char* url) //执行callback
{
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    stack->pushString("");
    stack->executeFunctionByHandler(mListener, 1);
}


