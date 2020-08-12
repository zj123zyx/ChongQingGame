//
//  GameHttpClient.h
//  IMDiors
//
//  Created by 李 战平 on 13-8-17.
//
//

#ifndef IMDiors_GameHttpClient_h
#define IMDiors_GameHttpClient_h
#include "CCLuaEngine.h"
#include "HttpClientEX.h"

USING_NS_CC;
USING_NS_CC_EXT;


class GameHttpClient:public cocos2d::Ref
{
public:
    static GameHttpClient* httpClient();
    
    void onHttpRequestCompleted(CCHttpClientEX *sender, CCHttpResponseEX *response);
    
    void onPostBinary(const char* url,const char* data,unsigned int len,LUA_FUNCTION listener);

    virtual void executeFunction(int responseCode, const char* resp,unsigned int len);
    
private:
    GameHttpClient()
    {
    }
    
    ~GameHttpClient();
    
    int m_nHandler;
    
};



#endif
