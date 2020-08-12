#ifndef _TRANSACTION_1013_H_
#define _TRANSACTION_1013_H_

#include "AbstractTransaction.h"

/*
 **用户支付宝WAP支付充值
 */

class Transaction1013 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    WRITEONLY_PASS_BY_REF(string, _amount, Amount);//充值金额
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _uri, Uri);//授权后请求URI
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif