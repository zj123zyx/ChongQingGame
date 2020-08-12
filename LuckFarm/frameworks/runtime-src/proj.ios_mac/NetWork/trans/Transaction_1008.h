#ifndef _TRANSACTION_1008_H_
#define _TRANSACTION_1008_H_

#include "AbstractTransaction.h"

/*
 **用户注销
 */

class Transaction1008 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _password, Password);// 密码
    WRITEONLY_PASS_BY_REF(string, _idNumber, IdNumber);// 身份证号码
    WRITEONLY_PASS_BY_REF(string, _phone, Phone);// 手机号码
    WRITEONLY_PASS_BY_REF(string, _name, Name);// 名字
    
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif