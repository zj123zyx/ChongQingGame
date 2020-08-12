#ifndef _TRANSACTION_1030_H_
#define _TRANSACTION_1030_H_

#include "AbstractTransaction.h"

/*
 **用户更新手机资料
 */

class Transaction1030 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    WRITEONLY_PASS_BY_REF(string, _phone, Phone);//手机号码
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif