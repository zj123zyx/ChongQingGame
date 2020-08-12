//
//  SocketManager.cpp
//  IMDiors
//
//  Created by 李 战平 on 13-8-21.
//
//

#include "SocketManager.h"


USING_NS_CC;
USING_NS_CC_EXT;


static SocketManager* instance = NULL;

SocketManager::~SocketManager()
{
}

SocketManager* SocketManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new SocketManager();
        
    }
    return instance;
}

void SocketManager::startSocket(string host, int port,LUA_FUNCTION listener)
{
    m_nHandler=listener;
    
    _socket = new SocketClient(host,port);
    _socket->setResponseCallback(this,socketresponse_selector(SocketManager::onSocketResponse));
    _socket->start();
}

void SocketManager::stop()
{
    _socket->stop(true);
}

void SocketManager::setLuaHandler(LUA_FUNCTION listener){
     m_nHandler=listener;
}

void SocketManager::sendMessage(const char* data,unsigned int len)
{
    Message* msg = new Message();
    msg->datalength=len;
    msg->data=(char*)data;
    _socket->sendMessage_(msg);
}

void SocketManager::onSocketResponse(Message* msg)
{
    //std::cout<<msg->datalength<<"\n";
    //把返回消息传给lua
    //LuaStack* stack =  LuaEngine::getInstance()->getLuaStack();
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    stack->clean();
    stack->pushString(msg->data, msg->datalength);
    stack->executeFunctionByHandler(this->m_nHandler, 1);
}

char* SocketManager::popReceivedData()
{
    Message* msg = _socket->popReceivedMessage();
    if(msg!=NULL){
        //printf("SocketManager::popReceivedData data length=%d \n",msg->datalength);
        //return  msg->data;
        onSocketResponse(msg);
    }
    return NULL;
}

