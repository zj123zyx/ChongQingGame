#ifndef _TRANSACTION_1031_H_
#define _TRANSACTION_1031_H_

#include "AbstractTransaction.h"

/*
 **用户忘记密码
 */

class Transaction1031 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _phone, Phone);// 手机号
    WRITEONLY_PASS_BY_REF(string, _userName, UserName);// 真实姓名
    WRITEONLY_PASS_BY_REF(string, _idNumber, IdNumber);// 身份证号
    WRITEONLY_PASS_BY_REF(string, _userPwd, UserPwd);// 账户密码
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif