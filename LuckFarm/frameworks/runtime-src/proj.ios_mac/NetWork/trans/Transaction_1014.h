#ifndef _TRANSACTION_1014_H_
#define _TRANSACTION_1014_H_

#include "AbstractTransaction.h"

/*
 **短信验证
 */

class Transaction1014 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _oldPhone, OldPhone);
    WRITEONLY_PASS_BY_REF(string, _newPhone, NewPhone);
    WRITEONLY_PASS_BY_REF(string, _cardNumber, CardNumber);
    WRITEONLY_PASS_BY_REF(string, _type, Type);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _smsNum, SmsNum);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif