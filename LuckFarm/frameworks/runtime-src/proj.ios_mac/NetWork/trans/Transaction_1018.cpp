#include "Transaction_1018.h"

string Transaction1018::buildXmlBody(string sb)
{	
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1018::getType()
{
	return "1018";
}

void Transaction1018::handleData(xml_node<>* resultData)
{
    
    auto nodeItem = resultData->first_node();//item<>
    if(nodeItem == NULL){
        return;
    }
    for (int i=0; nodeItem != NULL;i++) {
        
        auto nodeBankId = nodeItem->first_node();//bankId
        this->_bankId = nodeBankId->value();
        tableMeg = tableMeg + this->_bankId+ ",";
        
        auto nodeBankName = nodeBankId->next_sibling();//bankName
        this->_bankName = nodeBankName->value();
        tableMeg = tableMeg + this->_bankName+ ",";
        
        nodeItem = nodeItem->next_sibling();
        
    }
    this->_allBanks = tableMeg;
    
}

void Transaction1018::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}