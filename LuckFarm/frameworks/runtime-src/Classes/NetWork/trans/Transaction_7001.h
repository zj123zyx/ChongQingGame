//
//  Transaction7001.hpp
//  HongBoECai
//
//  Created by Administrator on 16/10/14.
//
//

#ifndef Transaction7001_hpp
#define Transaction7001_hpp

#include "AbstractTransaction.h"

/**
 * 连连支付发起（密匙信息获取）（7001）
 */

class Transaction7001 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _amount, Amount);                                 //充值金额
    WRITEONLY_PASS_BY_REF(string, _bankAccount, BankAccount);                       //银行卡号
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _orderId, OrderId);                  //订单Id 1
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _createTime, CreateTime);            //订单时间1
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _userAccountId, UserAccountId);      //用户账号1
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _oid_partner, Oid_partner);          //商户编号1
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _sign_type, Sign_type);              //签名方式1
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _buis_partner, Buis_partner);        //商户业务类型1
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _notify_url, Notify_url);            //异步通知url1
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _rsa_private_key, Rsa_private_key);  //商家私钥
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _rsa_public_key, Rsa_public_key);    //商家公钥
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _registerTime, RegisterTime);        //注册时间
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _phoneNumber, PhoneNumber);          //手机号码
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
public:
    string getType();
    
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* Transaction7001_hpp */
