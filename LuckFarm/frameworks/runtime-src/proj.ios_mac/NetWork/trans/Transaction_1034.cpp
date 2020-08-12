//
//  Transaction_1034.cpp
//  HongBoECai
//
//  Created by Administrator on 16/10/18.
//
//

#include "Transaction_1034.h"

string Transaction1034::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<page>");
    sb.append("<pageCount>"+this->_pageCount+"</pageCount>");
    sb.append("<pageSize>"+this->_pageSize+"</pageSize>");
    sb.append("</page>");
    
    sb.append("<userType>A</userType>");
    
    return sb;
}

string Transaction1034::getType()
{
    return "1034";
}

void Transaction1034::handleData(xml_node<>* resultData)
{
    auto nodeEmails = resultData->first_node();//Emails<>
    if(nodeEmails == NULL){
        return;
    }
    auto nodeItem  = nodeEmails->first_node();//item<>
    if(nodeItem == NULL){
        return;
    }
    
    for (int i=0; nodeItem != NULL;i++) {
        auto nodeEmailId = nodeItem->first_node();//emailId
        this->_emailId = nodeEmailId->value();
        tableMeg = tableMeg + "emailId=====" + this->_emailId + "&&&&&";
        
        auto nodeContent = nodeEmailId->next_sibling();//_content
        this->_content = nodeContent->value();
        tableMeg = tableMeg + "content=====" + this->_content+ "&&&&&";
        
        auto nodeCreateTime = nodeContent->next_sibling();//_createTime
        this->_createTime = nodeCreateTime->value();
        tableMeg = tableMeg + "createTime=====" + this->_createTime+ "&&&&&";
        
        auto nodeContentType = nodeCreateTime->next_sibling();//contentType
        this->_contentType = nodeContentType->value();
        tableMeg = tableMeg + "contentType=====" + this->_contentType+ "&&&&&";
        
        auto nodeImg = nodeContentType->next_sibling();//img
        this->_img = nodeImg->value();
        tableMeg = tableMeg + "img=====" + this->_img+ "&&&&&";
        
        auto nodeStatus = nodeImg->next_sibling();//status
        this->_status = nodeStatus->value();
        tableMeg = tableMeg + "status=====" + this->_status+ "&&&&&";
        
        auto nodeSalesType = nodeStatus->next_sibling();//salesType
        this->_salesType = nodeSalesType->value();
        tableMeg = tableMeg + "salesType=====" + this->_salesType+ "&&&&&";
        
        auto nodeTitle = nodeSalesType->next_sibling();//_title
        this->_title = nodeTitle->value();
        tableMeg = tableMeg + "title=====" + this->_title+ "&&&&&";
        
        tableMeg = tableMeg + ";;;;;";
        
        nodeItem = nodeItem->next_sibling();
    }
    this->_emailsInfo = tableMeg;
}

void Transaction1034::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
}
