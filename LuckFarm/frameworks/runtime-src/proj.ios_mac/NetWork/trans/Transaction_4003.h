#ifndef _TRANSACTION_4003_H_
#define _TRANSACTION_4003_H_

#include "AbstractTransaction.h"

/*
 **用户注册接口
 */

class Transaction4003 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 账户名
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 账户密码
    WRITEONLY_PASS_BY_REF(string, _salesType, SalesType);// 活动标识
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _message , Message );

    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif
