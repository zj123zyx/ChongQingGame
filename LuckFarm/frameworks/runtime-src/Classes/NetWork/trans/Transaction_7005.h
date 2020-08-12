//
//  Transaction7005.hpp
//  HongBoECai
//
//  Created by Administrator on 16/9/5.
//
//

#ifndef Transaction7005_hpp
#define Transaction7005_hpp

#include "AbstractTransaction.h"

/**
 * QQ,微信用户发起绑定请求
 */
class Transaction7005 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    WRITEONLY_PASS_BY_REF(string, _openId, OpenId);
    WRITEONLY_PASS_BY_REF(string, _accessToken, AccessToken);
    WRITEONLY_PASS_BY_REF(string, _platformName, PlatformName);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
public:
    string getType();
    
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* Transaction7005_hpp */
