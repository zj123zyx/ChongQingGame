#include "TransactionA.h"

string Transaction1001::buildXmlBody(string sb) 
{	
	sb.append("<name>" + this->_userName + "</name>");   
	sb.append("<userPwd>" + this->_userPwd + "</userPwd>");
	sb.append("<verifyNumber>" + this->_verifyNumber + "</verifyNumber>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1001::getType()
{
	return "1001";
}

void Transaction1001::handleData(xml_node<>* resultData)
{
	auto node = resultData->first_node();
	this->_bigMoney = node->value();
    
    node = node->next_sibling();
    this->_isConsummate = node->value();
	
    node = node->next_sibling();
	this->_userId = node->value();

	node = node->next_sibling();
	this->_balance = node->value();
    
    node = node->next_sibling();
    this->_freeze = node->value();
	
	node = node->next_sibling();
	this->_accountId = node->value();
    
    node = node->next_sibling();
    this->_scale = node->value();

	node = node->next_sibling();
	this->_lotteryPoint = node->value();
    
    node = node->next_sibling();
    this->_giftBalance = node->value();
    
    node = node->next_sibling();
    this->_giftLotteryPoint = node->value();
    
    node = node->next_sibling();
    this->_totalSale = node->value();
    
    node = node->next_sibling();
    this->_totalPrize = node->value();

	node = node->next_sibling();
	this->_sessionId = node->value();
}

void Transaction1001::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
}