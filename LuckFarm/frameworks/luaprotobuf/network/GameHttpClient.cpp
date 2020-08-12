//
//  GameHttpClient.cpp
//  IMDiors
//
//  Created by 李 战平 on 13-8-17.
//
//
#include "cocos2d.h"
#include "GameHttpClient.h"
#include "HttpClient.h"
#include "CCLuaEngine.h"
//#include "LuaEngineShell.h"

USING_NS_CC;
USING_NS_CC_EXT;


GameHttpClient::~GameHttpClient()
{
}

GameHttpClient* GameHttpClient::httpClient()
{
    
    GameHttpClient* client = new GameHttpClient();
    return client;
}


void GameHttpClient::onPostBinary(const char* url,const char* data,unsigned int len,LUA_FUNCTION listener)
{
    m_nHandler=listener;
    
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(url);
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, httpresponse_selector(GameHttpClient::onHttpRequestCompleted));
      
    request->setRequestData(data, len);
    
    request->setTag("POST Binary test");
    CCHttpClientEX::getInstance()->send(request);
    request->release();

}

void GameHttpClient::executeFunction(int responseCode, const char* data,unsigned int len)
{  
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    stack->clean();
    stack->pushInt(responseCode);
    stack->pushString(data, len);
    // lua_pushinteger(tolua_s, responseCode);
    // lua_pushstring(tolua_s,data);
    stack->executeFunctionByHandler(this->m_nHandler, 2);
}


void GameHttpClient::onHttpRequestCompleted(CCHttpClientEX *sender, CCHttpResponseEX *response)
{
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLOG("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    
    CCLOG("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLOG("response failed");
        CCLOG("error buffer: %s", response->getErrorBuffer());
        this->executeFunction(statusCode, response->getErrorBuffer(),1);
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    printf("Http Test, dump data: ");
    char data[buffer->size()];
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        data[i]=(*buffer)[i];
        printf("%c", (*buffer)[i]);
    }
    //data[buffer->size()]='\0';
    printf("\n");
    
    this->executeFunction(statusCode, data,buffer->size());
}


/**void GameHttpClient::onHttpRequestCompleted(CCHttpClientEX *sender, CCHttpResponseEX *response)
{
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    printf("Http Test, dump data:");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        printf("%c", (*buffer)[i]);
    }
    printf("\n");
}
 
 */
