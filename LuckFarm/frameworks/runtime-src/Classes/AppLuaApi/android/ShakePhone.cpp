//
//  ShakePhone.cpp
//  baobing
//
//  Created by jian.feng on 15/5/26.
//
//

#include "ShakePhone.h"
#include "JniTestHelper.h"
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

ShakePhone* ShakePhone::s_storeKit = NULL;

ShakePhone::~ShakePhone()
{
    
}

ShakePhone* ShakePhone::sharedShakePhone()
{
    if (!s_storeKit)
    {
        s_storeKit = new ShakePhone();
    }
    return s_storeKit;
}

void ShakePhone::setShakePhoneListenerLua(cocos2d::LUA_FUNCTION listener)
{
    if (mListener)
    {
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(mListener);
    }
    mListener = listener;
}

void ShakePhone::showShakePhone(int flag)
{
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    
    stack->pushInt(flag);
    stack->executeFunctionByHandler(mListener, 1);
}
