#include "Transaction_1003.h"

string Transaction1003::buildXmlBody(string sb)
{	
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction1003::getType()
{
	return "1003";
}

void Transaction1003::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_balance = node->value();
    node = node->next_sibling();
    this->_bigMoney = node->value();
    node = node->next_sibling();
    this->_freezeMoney = node->value();
    node = node->next_sibling();
    this->_totalPrizeMoney = node->value();
    node = node->next_sibling();
    this->_bigMoney = node->value();
    node = node->next_sibling();
    this->_giftBalance = node->value();
    node = node->next_sibling();
    this->_giftLotteryPoint = node->value();
    node = node->next_sibling();
    this->_totalSale = node->value();
    node = node->next_sibling();
    this->_totalPrize = node->value();

    

}

void Transaction1003::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}
