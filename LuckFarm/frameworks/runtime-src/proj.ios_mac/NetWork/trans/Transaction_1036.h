//
//  Transaction_1036.hpp
//  HongBoECai
//
//  Created by Administrator on 16/10/19.
//
//

#ifndef Transaction_1036_hpp
#define Transaction_1036_hpp

#include "AbstractTransaction.h"

/*
 * 领取类信件领取奖励
 */

class Transaction1036 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    WRITEONLY_PASS_BY_REF(string, _emailId, EmailId);    //编号
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _giftAmount, GiftAmount);     //获赠红包金额
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _balance, Balance);           //账号金额
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _giftBalance, GiftBalance);   //账号红包金额
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
public:
    string getType();
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* Transaction_1036_hpp */
