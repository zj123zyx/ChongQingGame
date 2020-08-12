#ifndef _TRANSACTION_1012_H_
#define _TRANSACTION_1012_H_

#include "AbstractTransaction.h"

/*
 **用户密码修改
 */

class Transaction1012 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _userPwd, UserPwd);
    WRITEONLY_PASS_BY_REF(string, _newUserPwd, NewUserPwd);
    
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif