#ifndef _TRANSACTION_1006_H_
#define _TRANSACTION_1006_H_

#include "AbstractTransaction.h"

/*
 **用户提款
 */

class Transaction1006 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    WRITEONLY_PASS_BY_REF(string, _bankAccount, BankAccount);//银行账户
    WRITEONLY_PASS_BY_REF(string, _amount, Amount);//提款金额
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif