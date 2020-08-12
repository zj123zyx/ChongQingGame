//
//  Transaction_7002.hpp
//  HongBoECai
//
//  Created by Administrator on 16/9/5.
//
//

#ifndef Transaction_7002_hpp
#define Transaction_7002_hpp

#include "AbstractTransaction.h"

/**
 * 连连支付确认
 */

class Transaction7002 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _ret_code, Ret_code);           //交易结果代码
    WRITEONLY_PASS_BY_REF(string, _ret_msg, Ret_msg);             //交易结果描述
    WRITEONLY_PASS_BY_REF(string, _result_pay, Result_pay);        //支付结果
    WRITEONLY_PASS_BY_REF(string, _oid_paybill, Oid_paybill);      //连连支付订单号
    WRITEONLY_PASS_BY_REF(string, _money_order, Money_order);      //交易金额
    WRITEONLY_PASS_BY_REF(string, _no_order, No_order);            //商户唯一订单号
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
public:
    string getType();
    
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* Transaction_7002_hpp */
