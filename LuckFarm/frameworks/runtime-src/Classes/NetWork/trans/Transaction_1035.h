//
//  Transaction_1035.hpp
//  HongBoECai
//
//  Created by Administrator on 16/10/19.
//
//

#ifndef Transaction_1035_hpp
#define Transaction_1035_hpp

#include "AbstractTransaction.h"

/*
 * 个人信件删除
 */

class Transaction1035 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    WRITEONLY_PASS_BY_REF(string, _emailId, EmailId);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
public:
    string getType();
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* Transaction_1035_hpp */
