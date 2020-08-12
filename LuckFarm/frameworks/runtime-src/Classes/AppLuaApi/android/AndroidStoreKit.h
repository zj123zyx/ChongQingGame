//
//  AndroidStoreKit.h
//  SlotFun
//
//  Created by 李战平 on 14-8-4.
//
//

#ifndef SlotFun_AndroidStoreKit_h
#define SlotFun_AndroidStoreKit_h
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
typedef int LUA_FUNCTION;

class AndroidStoreKit
{
    
public:
    ~AndroidStoreKit();
    
    static AndroidStoreKit* sharedStoreKit();
    
public:
    
    void purchaseProductWithID(const char* theProductID,const char* payload);
    
    bool isPurchaseEnabled();
    
    //iOS上没有这一步 Android上在商品purchased成功后，进入这里验证
    void purchaseProductCompleted(float dt);
    
    void transactionCompleted(CCString *ret,CCString *signature);
    
    void transactionError(int code,CCString *ret);
    
    void setTransactionCompletedListener(LUA_FUNCTION listener);
    
    void setTransactionErrorListener(LUA_FUNCTION listener);
    
    bool  getIsProcessDialogShow();
    
    void showProgressDialog();
    
    void hideProgressDialog();
    
    void userReportCallBack();
    
    void trackingWithEvent(const char* eventName,const char* value);
    
private:
    
    static AndroidStoreKit*  s_storeKit;
    
    LUA_FUNCTION m_listener;
    
    LUA_FUNCTION err_listener;
};


#endif
