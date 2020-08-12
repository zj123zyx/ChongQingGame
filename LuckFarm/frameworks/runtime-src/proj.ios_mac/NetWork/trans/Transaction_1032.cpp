#include "Transaction_1032.h"

string Transaction1032::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1032::getType()
{
	return "1032";
}

void Transaction1032::handleData(xml_node<>* resultData)
{
    
    auto node = resultData->first_node();//feedBackOeder
    auto nodeItem = node->first_node();//item<>
    if(nodeItem == NULL){
        return;
    }
    for (int i=0; nodeItem != NULL;i++) {
     
        auto nodeId = nodeItem->first_node();//id
        this->_id = nodeId->value();
        tableMeg = tableMeg + this->_id+ ",";
        
        auto nodeType = nodeId->next_sibling();//type
        this->_type = nodeType->value();
        tableMeg = tableMeg + this->_type+ ",";
        
        auto nodeMeno = nodeType->next_sibling();//memo
        this->_memo = nodeMeno->value();
        tableMeg = tableMeg + this->_memo+ ",";
        
        auto nodeTime = nodeMeno->next_sibling();//createTime
        this->_createTime = nodeTime->value();
        tableMeg = tableMeg + this->_createTime+ ",";
        
        auto nodeReply = nodeTime->next_sibling();//replyTime
        this->_reply = nodeReply->value();
        tableMeg = tableMeg + this->_reply+ ",";
        
        auto nodeReplyTime = nodeTime->next_sibling();//replyTime
        this->_replyTime = nodeReplyTime->value();
        tableMeg = tableMeg + this->_replyTime+ ",";

        nodeItem = nodeItem->next_sibling();
        
    }
    this->_replyTime = tableMeg;
    printf("======%s", tableMeg.c_str());
    
}


void Transaction1032::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}