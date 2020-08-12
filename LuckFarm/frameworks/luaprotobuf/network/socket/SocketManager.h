//
//  SocketManager.h
//  IMDiors
//
//  Created by 李 战平 on 13-8-21.
//
//

#ifndef IMDiors_SocketManager_h
#define IMDiors_SocketManager_h


#include "cocos2d.h"
#include "Message.h"
#include "SocketClient.h"
#include "CCLuaEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;


class SocketManager:public Ref{
public:
    static SocketManager* getInstance();
    
    void startSocket(string host, int port,LUA_FUNCTION listener);
    
    void sendMessage(const char* data,unsigned int len);
    
    void onSocketResponse(Message* msg);
    
    void stop();
    
    void setLuaHandler(LUA_FUNCTION listener);
    
    char* popReceivedData();
private:
    SocketManager()
    {
    }
    
    ~SocketManager();
    
    SocketClient* _socket;
    
    int m_nHandler;
};


#endif
