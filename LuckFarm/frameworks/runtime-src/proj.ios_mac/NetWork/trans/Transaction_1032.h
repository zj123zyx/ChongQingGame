#ifndef _TRANSACTION_1032_H_
#define _TRANSACTION_1032_H_

#include "AbstractTransaction.h"

/*
 **意见反馈查询
 */

class Transaction1032 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _id, Id);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _type, Type);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _memo, Memo);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _createTime, CreateTime);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _reply, Reply);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _replyTime, ReplyTime);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();
    string tableMeg = "";
protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif