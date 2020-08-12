//
//  SocketClient.cpp
//  IMDiors
//
//  Created by 李 战平 on 13-8-21.
//
//

#include "SocketClient.h"
#include <errno.h>
#include <signal.h>
#include "Message.h"

NS_CC_EXT_BEGIN

SocketClient::SocketClient(string host, int port):
m_iState(SocketClient_WAIT_CONNECT),
m_cbRecvBuf(1024*60),m_cbSendBuf(1024*60)
{	
    pthread_mutex_init (&m_sendqueue_mutex,NULL);
	pthread_mutex_init(&m_thread_cond_mutex,NULL);
	pthread_cond_init(&m_threadCond, NULL);
	
	m_hSocket = -1;
	
	this->m_host = host;
	this->m_iport = port;
	
	m_bThreadRecvCreated = false;
	m_bThreadSendCreated = false;
}


void SocketClient::start(){
	if(!m_bThreadSendCreated){
		pthread_create( &pthread_t_send, NULL,ThreadSendMessage, this);
		m_bThreadSendCreated = true;
	}
}

bool SocketClient::isWaitConnect(){
	return m_iState == SocketClient_WAIT_CONNECT;
}

SocketClient::~SocketClient()
{
	m_iState = SocketClient_DESTROY;
	if( m_hSocket!=-1)
		close(m_hSocket);
	
	pthread_mutex_destroy(&m_sendqueue_mutex);
	pthread_mutex_destroy(&m_thread_cond_mutex);
	pthread_cond_destroy(&m_threadCond);
    
    while (!m_receivedMessageQueue.empty()) {
		Message* m = m_receivedMessageQueue.front();
		m_receivedMessageQueue.pop();
		SAFE_DELETE_ELEMENT(m);
	}
	
	while (!m_sendMessageQueue.empty()) {
		Message* m = m_sendMessageQueue.front();
		m_sendMessageQueue.pop();
		SAFE_DELETE_ELEMENT(m);
	}
    
}

void SocketClient::stop(boolean b){
	m_iState = SocketClient_DESTROY;
	
	{
		MyLock lock(&m_thread_cond_mutex);
		pthread_cond_signal(&m_threadCond);
	}
	if(m_bThreadRecvCreated){
        pthread_join(pthread_t_receive, NULL);
    }
	pthread_join(pthread_t_send, NULL);
}

bool SocketClient::connectServer()
{
    
	if( m_host.length() < 1 || m_iport == 0) return false;
    //	if( DEBUG){
    CCLOG("[SocketClient::Connect()] [ host:%s,port:%d ] \n",m_host.c_str(),m_iport);
    //	}
	int dwServerIP = inet_addr(m_host.c_str());
	unsigned short wPort = m_iport;
    
	if( m_hSocket != -1){
		close(m_hSocket);
	}
    
	m_hSocket = socket(AF_INET,SOCK_STREAM,0);
	if (m_hSocket == -1)
	{
        CCLOG("socket connect error! errno=%d\n", errno);
		return false;
	}
    
	
	sockaddr_in SocketAddr;
	memset(&SocketAddr,0,sizeof(SocketAddr));
    
	SocketAddr.sin_family=AF_INET;
	SocketAddr.sin_port=htons(wPort);
    
	SocketAddr.sin_addr.s_addr=dwServerIP;
    
    memset(&(SocketAddr.sin_zero),0,sizeof(SocketAddr.sin_zero));
    
	int iErrorCode=0;
    
    
	iErrorCode= connect(m_hSocket,(sockaddr*)&SocketAddr,sizeof(SocketAddr));
	if (iErrorCode==-1)
	{
		CCLOG("socket connect error:%d\n",errno);
		return false;
	}
    
	
	if( !m_bThreadRecvCreated ){
        
		if(pthread_create( &pthread_t_receive, NULL,ThreadReceiveMessage, this)!=0)
        {
            
            CCLOG("pthread_create error!\n");
			return false;
		}
        m_bThreadRecvCreated = true;
	}
    
	m_iState = SocketClient_OK;
	
	
	
    CCLOG("socket connected success[ %s,%d],%p ,%d,%d \n",m_host.c_str(),m_iport, this,m_iState,SocketClient_OK);
	
	return true;
}


//往发送队列中放入一个包
void SocketClient::sendMessage_(Message* msg)
{
	if(m_iState == SocketClient_DESTROY){
		delete msg;
		return;
	}
    
    MyLock lock(&m_sendqueue_mutex);
    m_sendMessageQueue.push(msg);
    
	if( m_iState == SocketClient_OK)
	{
		MyLock lock(&m_thread_cond_mutex);
		pthread_cond_signal(&m_threadCond);
	}
	
}

//这个方法现在改成回调
void SocketClient::dispatchReceivedMessage(Message* msg){
    //执行回调
    Ref *pTarget = this->getTarget();
    SEL_SocketResponse pSelector = this->getSelector();
    if (pTarget && pSelector)
    {
        (pTarget->*pSelector)(msg);
    }else{
        CCLOG("[SocketClient::dispatchReceivedMessage()][error:%s] \n","pTarget && pSelector is null");
    }
}

//构建通讯层的异常消息
Message* constructErrorMessage(int errCode,string error){
	
        Message* msg = new Message();
    
    	ByteBuffer* buf = new ByteBuffer(1024);
        buf->putInt(0);//长度
        buf->putShort(502);//异常标志,网关错误
        buf->putLong(502);//占用个passportId
    	buf->putInt(errCode);//错误编号
    	//buf->putUTF(error.c_str());//错误信息
         printf("%s] \n",error.c_str());
        msg->datalength=buf->position;
    	msg->data = buf->toByteArray();
    
    	delete buf;	
	return msg;
}

void* SocketClient::ThreadSendMessage(void *p){
    
	SocketClient* This = static_cast<SocketClient*>(p) ;
    
	//连接server不成功时
	while(This->m_iState == SocketClient_WAIT_CONNECT && !This->connectServer()){
			This->m_iState = SocketClient_DESTROY;
			string error("连网失败,请检查网络设置");
            char tmp[64];
            sprintf(tmp, "%d",This->m_iport);
            error.append(This->m_host).append(":").append(tmp);
			{
				MyLock lock(&This->m_sendqueue_mutex);
                
				//This->dispatchReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CONNECT_FAIL,error));
                This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CONNECT_FAIL,error));
			}
            CCLOG("[SocketClient::start()][connect failed][error:%s] \n",error.c_str());
			return ((void *)0);
	}
	
	ByteBuffer& sendBuff = This->m_cbSendBuf;
	int socket = This->m_hSocket;
	
	while (This->m_iState != SocketClient_DESTROY) {
		if( This->m_iState == SocketClient_OK){
            
            //发送缓冲器有遗留的数据要发送
            if(sendBuff.getPosition() > 0){
                sendBuff.flip();
                int ret = send(socket,(char *)sendBuff.getBuffer(),sendBuff.getLimit(),0);
                if(ret == -1){
                    This->m_iState = SocketClient_DESTROY ;
                    string err("发送数据，网络异常！");
                    char* errStr = strerror(errno);
                    if( errStr!=NULL ) err.append(errStr);
                    
                    MyLock lock(&This->m_sendqueue_mutex);
                    //This->dispatchReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CANNOT_SEND_MESSAGE,err));
                    This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CANNOT_SEND_MESSAGE,err));
                    return ((void *)0);
                }else{
                    CCLOG("SocketClient::ThreadSendMessage(), send message to server, size = %d\n",ret);
                }
                sendBuff.setPosition(sendBuff.getPosition()+ret);
                sendBuff.compact();
            }
            
            Message* msg = NULL;
            while( This->m_iState != SocketClient_DESTROY && This->m_sendMessageQueue.size()> 0){
                {
                    MyLock lock(&This->m_sendqueue_mutex);
                    msg = This->m_sendMessageQueue.front();
                    This->m_sendMessageQueue.pop();
                }
                
                CCLOG(" sendData length: %d  %ld \n" ,  msg->datalength, sizeof(char));
                
                //超过上限
                if(msg->datalength + sendBuff.getPosition() > sendBuff.getLimit()){
                    This->m_iState = SocketClient_DESTROY;
                    printf("send buffer is full, send thread stop!");
                    MyLock lock(&This->m_sendqueue_mutex);
                    //This->dispatchReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CANNOT_SEND_MESSAGE,"发送缓冲器已满，您的网络环境好像出现了问题！"));
                     This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CANNOT_SEND_MESSAGE,"发送缓冲器已满，您的网络环境好像出现了问题！"));
                    return ((void *)0);
                }
                //printf("send message %0x \n",msg->type);
                sendBuff.put(msg->data,0,msg->datalength);
                sendBuff.flip();
                int ret = send(socket,(char *)sendBuff.getBuffer(),sendBuff.getLimit(),0);
                if(ret == -1){
                    This->m_iState = SocketClient_DESTROY;
                    string err("发送数据，网络异常！");
                    MyLock lock(&This->m_sendqueue_mutex);
                    //This->dispatchReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CANNOT_SEND_MESSAGE,err));
                     This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CANNOT_SEND_MESSAGE,err));
                    return ((void *)0);
                }else{
                    CCLOG("SocketClient::ThreadSendMessage(), send message to server, size = %d\n",ret);
                }
                sendBuff.setPosition(sendBuff.getPosition()+ret);
                sendBuff.compact();
                msg=NULL;
            }
		}
		
        //空的情况下就等待
		if(This->m_iState != SocketClient_DESTROY && This->m_sendMessageQueue.size() == 0){
			//sleep
			struct timeval tv;
			struct timespec ts;
			gettimeofday(&tv, NULL);
			ts.tv_sec = tv.tv_sec + 5;
			ts.tv_nsec = 0;
			
			MyLock lock(&(This->m_thread_cond_mutex));
			if(This->m_iState != SocketClient_DESTROY && This->m_sendMessageQueue.size() == 0){
				pthread_cond_timedwait(&(This->m_threadCond),&(This->m_thread_cond_mutex),&ts);
			}
			
		}
		
	}
	//if(DEBUG) printf("SocketClient::ThreadSendMessage(), send thread stop!\n");
	return (void*)0;
}

bool g_bcheckReceivedMessage = true;//是否检查返回包
//处理返回消息的方法
void* SocketClient::ThreadReceiveMessage(void *p)
{

	fd_set fdRead;
	
	struct timeval	aTime;
	aTime.tv_sec = 1;
	aTime.tv_usec = 0;
    
	//最大多少秒，连接上收不到数据就提示用户，重新登录
	int maxIdleTimeInSeconds = 60*5;
	
	//最大多少秒，连接上收不到数据就提示用户，选择重连
	int hint2TimeInSeconds = 60*3;
	
	
	//多长时间没有收到任何数据，提示用户
	int hintTimeInSeconds = 60;
	
	struct timeval lastHintUserTime;
	struct timeval lastReceiveDataTime;
	struct timeval now;
	
	gettimeofday(&lastReceiveDataTime, NULL);
	lastHintUserTime = lastReceiveDataTime;
	
	SocketClient* This = static_cast<SocketClient*>(p) ;
	
	ByteBuffer* recvBuff = &This->m_cbRecvBuf;
    
	while (This->m_iState != SocketClient_DESTROY)
	{
        
        //CCLog("hahahahahahahhahahahahahahahha");
		if( This->m_iState != SocketClient_OK){
			usleep(1000);
			continue;
		}
		FD_ZERO(&fdRead);
        
		FD_SET(This->m_hSocket,&fdRead);
        
		aTime.tv_sec = 1;
		aTime.tv_usec = 0;
		
        //		int ret = select(This->m_hSocket+1,&fdRead,NULL,NULL,NULL);
        int ret = select(This->m_hSocket+1,&fdRead,NULL,NULL,&aTime);
        
		if (ret == -1 )
		{
			if(errno == EINTR){
				printf("======   收到中断信号，什么都不处理＝＝＝＝＝＝＝＝＝");
			}else{
				This->m_iState = SocketClient_DESTROY;
                printf("select error, receive thread stop! errno=%d, address=%p\n",errno,This);
				//MyLock lock(&This->m_sendqueue_mutex);
				This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CONNECT_TERMINATE,"连接异常中断"));
				return ((void *)0);
			}
		}else if(ret==0){
            //printf("selector timeout . continue select.... \n");
            //This->dispatchReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_RECONNECT_FORCE,"您的网络已经出问题了！"));
            gettimeofday(&now, NULL);
			if( g_bcheckReceivedMessage ){
                if(now.tv_sec - lastReceiveDataTime.tv_sec > maxIdleTimeInSeconds && now.tv_sec - lastHintUserTime.tv_sec > hintTimeInSeconds){
                    lastHintUserTime = now;
                    This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_RECONNECT_FORCE,"您的网络已经出问题了！"));
                    
                }else if(now.tv_sec - lastReceiveDataTime.tv_sec > hint2TimeInSeconds && now.tv_sec - lastHintUserTime.tv_sec > hintTimeInSeconds){
                    lastHintUserTime = now;
                    //MyLock lock(&This->m_sendqueue_mutex);
                    This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_RECONNECT_HINT,"您的网络好像出问题了！"));
                }else if(now.tv_sec - lastReceiveDataTime.tv_sec > hintTimeInSeconds && now.tv_sec - lastHintUserTime.tv_sec > hintTimeInSeconds){
                    lastHintUserTime = now;
                    //MyLock lock(&This->m_sendqueue_mutex);
                    This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_IDLE_TIMEOUT,"您的网络好像出问题了！"));
                }
            }else{
                lastHintUserTime = now;
                lastReceiveDataTime= now;
            }
		}else if (ret > 0){
			if (FD_ISSET(This->m_hSocket,&fdRead))
			{
				int iRetCode = 0;
                printf(" recv data remaining %d \n", recvBuff->remaining());
				if(recvBuff->remaining() > 0){
					iRetCode = recv(This->m_hSocket,recvBuff->getBuffer()+recvBuff->getPosition(), recvBuff->remaining(),0);
				}
                
                printf(" recv data later  remaining %d   iRetCode %d \n", recvBuff->remaining(), iRetCode);
				if (iRetCode == -1)
				{
					This->m_iState = SocketClient_DESTROY;
					//MyLock lock(&This->m_sendqueue_mutex);
					
					string tmp("网络连接中断！");
                    char* stre = strerror(errno);
                    if( stre!=NULL){
                        tmp.append(stre);
                    }
					This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CONNECT_TERMINATE,tmp));
					return ((void *)0);
				}else if(iRetCode == 0 && recvBuff->remaining() > 0){
					This->m_iState = SocketClient_DESTROY;
                    printf("server closed connection, receive thread stop %p!\n",This);
					//MyLock lock(&This->m_sendqueue_mutex);
					This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_SERVER_CLOSE_CONNECTION,"服务器主动关闭连接!"));
					
					return ((void *)0);
				}else{
					gettimeofday(&lastReceiveDataTime, NULL);
					
					recvBuff->setPosition(recvBuff->getPosition()+ iRetCode);
					recvBuff->flip();
					int tmpOffset = 6;//最小的包也应该有长度和类型
					while(recvBuff->remaining() > tmpOffset){
						int pos = recvBuff->position;
						int length= recvBuff->getLength(0);
						if(recvBuff->remaining() >= length){
                            //正常的消息处理===============================
							Message* message = new Message();
                            message->datalength=length;
                            
							printf("message length: %d \n", message->datalength);
                            
							char* tmp = new char[length];
							recvBuff->get(tmp,0,length);
                            message->data = tmp;
                            //MyLock lock(&This->m_sendqueue_mutex);
                            This->pushReceivedMessage(message);
						}else if(length>recvBuff->getCapacity()){
							This->m_iState = SocketClient_DESTROY;
							//MyLock lock(&This->m_sendqueue_mutex);
							This->pushReceivedMessage(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CONNECT_TERMINATE,"数据包太大，连接中断！"));
							return ((void *)0);
						}else {
							//printf("----------------------------\n");
							recvBuff->position = pos;
							break;
						}
					}
					recvBuff->compact();
				}
				
			}//end read
		}
        
	}
	//if(DEBUG) printf("SocketClient::ThreadSendMessage(), receive thread stop!\n");
	return (void*)0;
}

//获取服务器包
Message* SocketClient::pickReceivedMessage(){
	Message* msg = NULL;
	MyLock lock(&m_sendqueue_mutex);
	if( m_receivedMessageQueue.size()>0){
		
		msg = m_receivedMessageQueue.front();
        
	}
	
	return msg;
}
Message* SocketClient::popReceivedMessage(){
	Message* msg = NULL;
	MyLock lock(&m_sendqueue_mutex);
    //printf("SocketClient::popReceivedMessage m_receivedMessageQueue.size()=%d \n",(int)m_receivedMessageQueue.size());
	if( m_receivedMessageQueue.size()>0){
		
		msg = m_receivedMessageQueue.front();
		m_receivedMessageQueue.pop();
        
	}
	return msg;
}

void SocketClient::pushReceivedMessage(Message* msg){
	MyLock lock(&m_sendqueue_mutex);
	m_receivedMessageQueue.push(msg);
    printf("SocketClient::pushReceivedMessage msg length=%d \n",msg->datalength);
}


NS_CC_EXT_END
