#ifndef _TRANSACTION_1011_H_
#define _TRANSACTION_1011_H_

#include "AbstractTransaction.h"

/*
 **用户信息查询
 */

class Transaction1011 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _userName, UserName);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _userId, UserId);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _idNumber, IdNumber);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _phoneNumber, PhoneNumber);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _cardNumber, CardNumber);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _bank, Bank);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif