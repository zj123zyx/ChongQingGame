//
//  SocketClient.h
//  IMDiors
//
//  Created by 李 战平 on 13-8-21.
//
//

#ifndef IMDiors_SocketClient_h
#define IMDiors_SocketClient_h


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "ByteBuffer.h"

NS_CC_EXT_BEGIN

const int	SocketClient_WAIT_CONNECT = 0;
const int	SocketClient_OK = 1;
const int	SocketClient_DESTROY = 2;

class Message;
typedef void (CCObject::*SEL_SocketResponse)(Message* msg);
#define socketresponse_selector(_SELECTOR) (SEL_SocketResponse)(&_SELECTOR)

class SocketClient: public Ref{
public:
	int m_hSocket;
    
	string m_host;
	int m_iport;
	
	//发送和接收缓冲区，发送缓冲区满的时候，会断开连接，并提示信号不好
	ByteBuffer m_cbRecvBuf;
	ByteBuffer m_cbSendBuf;
	
	//需要发送到服务端的消息
	queue<Message*> m_sendMessageQueue;
    
    //收到服务端消息
	queue<Message*> m_receivedMessageQueue;
	
	int m_iState;
	
	//接收线程
	bool m_bThreadRecvCreated;
	pthread_t pthread_t_receive;
	
	//发送线程
	bool m_bThreadSendCreated;
	pthread_t pthread_t_send;
	pthread_mutex_t m_thread_cond_mutex;//pthread_mutex_t 互斥锁
	pthread_cond_t m_threadCond;
	
    //pthread_cond_t m_threadCond;
	//发送队列同步锁
	pthread_mutex_t m_sendqueue_mutex;
    
    SEL_SocketResponse   _pSelector; //回调函数
    
    CCObject*          _pTarget;
private:
	//连接服务器
	bool  connectServer();
	
	static void* ThreadReceiveMessage(void *p);
    
	static void* ThreadSendMessage(void *p);
    
   
	
public:
    
    SocketClient(string host, int port);
	
	~SocketClient();

    
	void start();
    
	void stop(boolean b);
	
	bool isWaitConnect();
	//发送数据
	void sendMessage_(Message* msg);
	
	void dispatchReceivedMessage(Message* msg);
    
    Message* popReceivedMessage();
    
	Message* pickReceivedMessage();
	
	void pushReceivedMessage(Message* msg);
    
    CC_DEPRECATED_ATTRIBUTE inline void setResponseCallback(CCObject* pTarget, SEL_CallFuncND pSelector)
    {
        setResponseCallback(pTarget, (SEL_SocketResponse) pSelector);
    }
    
    inline void setResponseCallback(CCObject* pTarget, SEL_SocketResponse pSelector)
    {
        _pTarget = pTarget;
        _pSelector = pSelector;
        
        if (_pTarget)
        {
            //_pTarget->retain();
        }
         
    }
    /** Get the target of callback selector funtion, mainly used by CCHttpClientEX */
    inline Ref* getTarget()
    {
        return _pTarget;
    }
    
    /* This sub class is just for migration SEL_CallFuncND to SEL_HttpResponse,
     someday this way will be removed */
    class _prxy
    {
    public:
        _prxy( SEL_SocketResponse cb ) :_cb(cb) {}
        ~_prxy(){};
        operator SEL_SocketResponse() const { return _cb; }
        CC_DEPRECATED_ATTRIBUTE operator SEL_CallFuncND()   const { return (SEL_CallFuncND) _cb; }
    protected:
        SEL_SocketResponse _cb;
    };
    
    /** Get the selector function pointer, mainly used by CCHttpClientEX */
    inline _prxy getSelector()
    {
        return _prxy(_pSelector);
    }
};

NS_CC_EXT_END

#endif
