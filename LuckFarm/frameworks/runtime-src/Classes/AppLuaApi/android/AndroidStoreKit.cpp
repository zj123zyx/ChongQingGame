//
//  AndroidStoreKit.cpp
//  SlotFun
//
//  Created by 李战平 on 14-8-4.
//
//

#include "AndroidStoreKit.h"
#include "JniInterface.h"
#include "cocos2d.h"
#include "CCLuaEngine.h"

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

AndroidStoreKit* AndroidStoreKit::s_storeKit = NULL;

AndroidStoreKit::~AndroidStoreKit()
{
    
}

AndroidStoreKit* AndroidStoreKit::sharedStoreKit()
{
    if (!s_storeKit)
    {
        s_storeKit = new AndroidStoreKit();
    }
    return s_storeKit;
}

//设置购买成功以后的lua回调函数
void AndroidStoreKit::setTransactionCompletedListener(LUA_FUNCTION listener)
{
    if (m_listener)
    {
        cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
    }
    m_listener = listener;
}

//设置购买失败的lua回调函数
void AndroidStoreKit::setTransactionErrorListener(LUA_FUNCTION listener)
{
    if (err_listener)
    {
        cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(err_listener);
    }
    err_listener = listener;
}

void AndroidStoreKit::purchaseProductWithID(const char *theProductID,const char* payload)
{
    purchaseProductJNI(theProductID,payload);
}

//iOS上没有这一步 Android上在商品purchased成功后，进入这里验证
void AndroidStoreKit::purchaseProductCompleted(float dt)
{
    
    
}

void AndroidStoreKit::transactionCompleted(CCString *ret,CCString *signature)
{
    //theTransactionReceiptString 在这里实际上是一个jsonResult
    cocos2d::CCLog("transactionCompleted!");
    
    cocos2d::CCLog("jsonResult = %s,signature=%s",ret->getCString(),signature->getCString());
    
    CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
    stack->clean();
    stack->pushString(ret->getCString(), ret->length());
    stack->pushString(signature->getCString(), signature->length());
    stack->executeFunctionByHandler(this->m_listener, 2);
}

void AndroidStoreKit::transactionError(int code,CCString *ret)
{
    //theTransactionReceiptString 在这里实际上是一个jsonResult
    cocos2d::CCLog("transactionError,code=%d,msg=%s",code,ret->getCString());
    
    CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
    stack->clean();
    stack->pushInt(code),
    stack->pushString(ret->getCString(), ret->length());
    stack->executeFunctionByHandler(this->err_listener, 2);
}

bool AndroidStoreKit::isPurchaseEnabled()
{
    return false;
}

bool  AndroidStoreKit::getIsProcessDialogShow()
{
    return getIsProcessDialogShowJni();
}

void AndroidStoreKit::showProgressDialog(){
    showProgressDialogJNI();
}

void AndroidStoreKit::hideProgressDialog(){
    hideProgressDialogJNI();
}

void AndroidStoreKit::userReportCallBack(){
    userReportCallBackJNI();
}

void AndroidStoreKit::trackingWithEvent(const char* eventName,const char* value)
{
    trackingWithEventJNI(eventName,value);
}
