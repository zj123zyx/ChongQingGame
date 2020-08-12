#ifndef _TRANSACTION_1020_H_
#define _TRANSACTION_1020_H_

#include "AbstractTransaction.h"

/*
 **用户反馈（1020）
 */

class Transaction1020 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    WRITEONLY_PASS_BY_REF(string, _memo, Memo);//反馈内容
    WRITEONLY_PASS_BY_REF(string, _adviceType, AdviceType);//反馈类型
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif
