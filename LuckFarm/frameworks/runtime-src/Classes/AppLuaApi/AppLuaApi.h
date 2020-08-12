
#ifndef  __CC_THIRDPLATFORM_AppLuaApi_H_
#define  __CC_THIRDPLATFORM_AppLuaApi_H_

#include "network/HttpClient.h"
#include "CCLuaValue.h"

using namespace cocos2d::network;

class AppLuaApi
{
public:
    static AppLuaApi* getInstance(void);
    static void purgeInstance(void);

    static void showIndicator(void);
    static void hideIndicator(void);
    
    static void openLLPayForPayWith(const char *orderinfo);
    static void gotoQQLogin(void);
    static void gotoWeiXinLogin(void);
    static void shareWeChatFriend(void);
    static void shareWeChatFriendQuan(void);
    static void shareQQFriend(void);
    static const char* stringToUtf8(const char *str);
    static const char* utf8ToString(const char *str);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static void setIsNeedShowWait(bool isNeed);
    
#endif
    const char* AppVersionCode();
    
    ~AppLuaApi(void);
    
    const char* UDID();
    const char* AppVersion();
    const char* ResVersion();
    const char* SystemVersion();
    
    static void downloadNewApp(const char *mainVersion);
    
    void postFBListenerLua(cocos2d::LUA_FUNCTION listener);

    void downloadPhoto(const char *fbID);
    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    void postPhoto(const char* profileID, const char* name,const char* path, int errorcode);
    
    //设置屏幕旋转
    void setGameOrientation(const char* flag);
    //设置屏幕状态栏
    void setStatusBar(const char* flag);
    
    //CryptorTools工具加密xml数据
    const char* cryptorToolsToRSA(const char* xmlContent);
    
    //ios 发送xml数据到java做RSA加密
    void encryptWithRsa(const char* xmlContent);
    void showEncryptWithRsa(const char* xmlContent);
    //ios 调用打电话
    void app_to_call(const char * num);
    //调用相册 和相机
    void openPhotoAlbum();//相册
    void openCamera();//相机
    
    void openURL(const char * url);//打开指定网址

    void setJPushTag(const char* userName);
private:
    AppLuaApi(void)
    {
        mListener = -1;
    }
    cocos2d::LUA_FUNCTION mListener;

    static AppLuaApi*  s_AppLuaApiInstance;
};

#endif // __CC_THIRDPLATFORM_AppLuaApi_H_
