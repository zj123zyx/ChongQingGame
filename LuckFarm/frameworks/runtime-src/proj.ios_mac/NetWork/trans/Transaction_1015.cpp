#include "Transaction_1015.h"

string Transaction1015::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<areaRank>"+this->_areaRank+"</areaRank>");
    sb.append("<areaParentId>"+this->_areaParentId+"</areaParentId>");
    sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1015::getType()
{
	return "1015";
}

void Transaction1015::handleData(xml_node<>* resultData)
{

    auto nodeItem = resultData->first_node();//item<>
    if(nodeItem == NULL){
        return;
    }
    for (int i=0; nodeItem != NULL;i++) {
        
        auto nodeAreaId = nodeItem->first_node();//areaId
        this->_areaId = nodeAreaId->value();
        tableMeg = tableMeg + this->_areaId+ ",";
        
        auto nodeAreaRank = nodeAreaId->next_sibling();//areaRank
        this->_curAreaRank = nodeAreaRank->value();
        tableMeg = tableMeg + this->_curAreaRank+ ",";
        
        auto nodeAreaName = nodeAreaRank->next_sibling();//areaName
        this->_areaName = nodeAreaName->value();
        tableMeg = tableMeg + this->_areaName+ ",";
        
//        auto nodeAreaCode = nodeAreaName->next_sibling();//areaCode
//        this->_areaCode = nodeAreaCode->value();
//        tableMeg = tableMeg + this->_areaCode+ ",";
        
        nodeItem = nodeItem->next_sibling();
        
    }
    this->_areaInfo = tableMeg;
}

void Transaction1015::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}