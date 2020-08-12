#ifndef  __CC_THIRDPLATFORM_NetDataManager_H_
#define  __CC_THIRDPLATFORM_NetDataManager_H_

#include <map>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "CCLuaValue.h"
#include "network/HttpClient.h"

#include "./trans/Transaction_7002.h"

using namespace std;
using namespace cocos2d::network;

#define DES_KEY "12345678"/*"H3b2e6C%"*/

class AbstractTransaction;

class NetDataManager
{
public:
    static NetDataManager* sharedNetDataManager(void);
    static void purgeSharedNetDataManager(void);
    
    ~NetDataManager(void);
    
    
#if CC_LUA_ENGINE_ENABLED > 0
    void postListenerLua(cocos2d::LUA_FUNCTION listener);
#endif
    /*
     发送正常接口请求
     */
    void post(char* xmlData) ;
    /*
     发送累积奖接口请求
     */
    void postJackpots(char* gameId) ;
    /*
     发送退出进程退出登录接口请求
     */
    void postQuit() ;
    
    ///////////////////////////////////
    //发送需要进行build的xml数据包
    void buildXMLData(char* xmlData) ;
    //发送需要进行RSA加密处理的xml数据包
    void postRSA(char* xmlData) ;
    ///////////////////////////////////
    
    /*
     //向服务器请求静态页面的用户中奖信息
     */
    void postUpdateNotice(char* serverAddress) ;
    
    void getOpenTokenAndOpenIdFromWeiXinWithUrl(const char* url);
    void onJackpotsHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    /**
     * QQ返回openId和accessToken
     */
    void returnToLuaWithOpenIDAndAccessToken(const char* openId, const char* accessToken);
    
    void returnToLuaWithNotificationInfo(const char* userInfo);

    void returnToLuaWithAndroidNotificationInfo(const char* userInfo, const char* clientType);
    
    /**
     * 支付成功，通知服务器
     */
    void sendLLpayResultToServer(Transaction7002 *tranc7002);

    /**
     * 支付成功，通知服务器----Android
     */
    void sendLLpayResultToServerForAndroid(const char* retCode, const char* retMsg, const char* resultPay, const char* oidPaybill, const char* moneyOrder, const char* noOrder);
    
    void returnToLuaWithLLpayResult(const char* result);
    
protected:
    void createTransaction(char* xmlData);
    
    //    const char* buildXML(char* type, char* xmlData) ;
    
    int gzipToEnBase64(char *data, unsigned long size, char** en);
    unsigned char* DeBase64ToGunzip(char *en, unsigned int size);
    
    void httpSendData(char * enData, unsigned int size);
    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    void userNeedLogin();
    /*
     //调用静态页面的返回的用户中奖信息
     */
    void onUpdateNoticeHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    /**
     * 微信获取验证
     */
    void onGetOpenTokenAndOpenIdHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    void onOK(AbstractTransaction* transaction);
    void onFail(AbstractTransaction* transaction);
    void onNetError(AbstractTransaction* transaction, HttpResponse *response);
    void onFinished(AbstractTransaction* transaction);
    
    ///////////////////////////////////
    //判断是否是需要进行RSA加密的接口
    bool doRsaEncrypt();
    ///////////////////////////////////
    /**
     *  判断是否是第三方登录的接口
     */
    bool isThirdLoginRequest();
    
private:
    NetDataManager(void)
    {
    }
    int contentSign;
    
    cocos2d::LUA_FUNCTION mListener;
    
    AbstractTransaction* _transaction;
    
    static NetDataManager*  s_sharedNetDataManager;
};

#endif // __CC_THIRDPLATFORM_NetDataManager_H_
