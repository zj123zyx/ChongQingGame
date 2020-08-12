//
//  Transaction_7006.hpp
//  HongBoECai
//
//  Created by Administrator on 16/9/5.
//
//

#ifndef Transaction_7006_hpp
#define Transaction_7006_hpp

#include "AbstractTransaction.h"

/**
 * 彩乐乐用户获取openId和accessToken
 */

class Transaction7006 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _account, Account);
    WRITEONLY_PASS_BY_REF(string, _password, Password);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _openId, OpenId);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _accessToken, AccessToken);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
public:
    string getType();
    
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* Transaction_7006_hpp */
