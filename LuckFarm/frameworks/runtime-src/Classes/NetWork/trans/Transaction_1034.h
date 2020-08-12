//
//  Transaction_1034.hpp
//  HongBoECai
//
//  Created by Administrator on 16/10/18.
//
//

#ifndef Transaction_1034_hpp
#define Transaction_1034_hpp

#include "AbstractTransaction.h"

/*
 * 个人信件查询
 */

class Transaction1034 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    WRITEONLY_PASS_BY_REF(string, _pageCount, PageCount);
    WRITEONLY_PASS_BY_REF(string, _pageSize, PageSize);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _emailId, EmailId);           //编号
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _content, Content);           //内容
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _createTime, CreateTime);     //创建时间
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _contentType, ContentType);   //信息类型
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _img, Img);                   //图片
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _status, Status);            //领取类,状态,1-未领取,2-已领取,3-失效
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _salesType, SalesType);      //领取类,活动标识
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _title, Title);               //标题
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _emailsInfo, EmailsInfo);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
public:
    string getType();
    string tableMeg = "";
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* Transaction_1034_hpp */
