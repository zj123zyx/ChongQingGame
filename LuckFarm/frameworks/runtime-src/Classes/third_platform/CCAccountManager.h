
#ifndef  __CC_THIRDPLATFORM_CCAccountManager_H_
#define  __CC_THIRDPLATFORM_CCAccountManager_H_

#include <map>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "CCLuaValue.h"
#include "network/HttpClient.h"

using namespace cocos2d::network;

typedef  std::map<const char*, const char*>  DictUserInfo;

typedef std::vector<DictUserInfo> UsersVector;

class CCAccountManager
{
public:
    static CCAccountManager* sharedAccountManager(void);
    static void purgeSharedAccountManager(void);
    static void downloadNewApp(const char* url);
    
    static void preloadFinish();
    static void showIndicator();
    static void hideIndicator();

    ~CCAccountManager(void);
    
    bool init(const char* nettype);
    
    const char* UDID();
    const char* AppVersion();
    const char* ResVersion();
    const char* SystemVersion();
    const char* getIdfa();
    const char* getIdfv();
    
    void logIn();
    void logOut();
    bool isLogged();
    
    void postFBListenerLua(cocos2d::LUA_FUNCTION listener);
    
    void postPhoto(const char* profileID, const char* name,const char* path, int errorcode);
    void postMe(DictUserInfo& info, int errorcode);
    void postShare(int errorcode);
    void postFriends(UsersVector& info, int errorcode);
    void postInviteFriends(int errorcode);
    
    void applicationDidFinishLaunchingWithOptions();
    void applicationDidBecomeActive();
    bool application(const char* url, const char* sourceApplication);
    
    void requestFriends();
    void inviteFriends();
    void shareText(const char* text);
    void share(const char* theName,const char* theCaption,const char* theDesc,const char* thePictureURL,const char* theLink);
    
    void downloadPhoto(const char *fbID);
    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    void applicationDidFinishLaunchingReport();
    void applicationDidFinishLaunchingReportCompleted(HttpClient *sender, HttpResponse *response);

private:
    CCAccountManager(void):m_fromNetwork("facebook")
    {
        
    }
    
    bool m_isSignUp;
    std::string m_fromNetwork;
    cocos2d::LUA_FUNCTION mListener;
    std::map<const char*, const char*> m_pProfile;
    std::map<const char*, cocos2d::LUA_FUNCTION> m_pListeners;

    static CCAccountManager*  s_sharedAccountManager;
};

#endif // __CC_THIRDPLATFORM_CCAccountManager_H_
