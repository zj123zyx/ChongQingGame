#ifndef _TRANSACTION_1004_H_
#define _TRANSACTION_1004_H_

#include "AbstractTransaction.h"

/*
 **完善用户资料或账户变更
 */

class Transaction1004 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    WRITEONLY_PASS_BY_REF(string, _realName, RealName);// 真实名字
    WRITEONLY_PASS_BY_REF(string, _bankId, BankId);// 银行编号
    WRITEONLY_PASS_BY_REF(string, _areaId, AreaId);// 区域代码
    WRITEONLY_PASS_BY_REF(string, _idNumber, IdNumber);// 区域代码
    WRITEONLY_PASS_BY_REF(string, _loginPhone, LoginPhone);// 是否容许手机登陆 0-否，1-是
    WRITEONLY_PASS_BY_REF(string, _cardNumber, CardNumber);// 借记卡号码
//    WRITEONLY_PASS_BY_REF(string, _phone, Phone);// 手机
//    WRITEONLY_PASS_BY_REF(string, _address, Address);
//    WRITEONLY_PASS_BY_REF(string, _postCode, PostCode);
//    WRITEONLY_PASS_BY_REF(string, _email, Email);
//    WRITEONLY_PASS_BY_REF(string, _tel, Tel);
//    WRITEONLY_PASS_BY_REF(string, _faxNo, FaxNo);
//    WRITEONLY_PASS_BY_REF(string, _idNumber, IdNumber);// 身份证号码
    
    
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif