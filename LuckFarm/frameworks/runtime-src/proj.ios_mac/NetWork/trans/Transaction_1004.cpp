#include "Transaction_1004.h"

string Transaction1004::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    
    sb.append("<userName>"+ this->_realName + "</userName>");
    sb.append("<bankId>"+ this->_bankId +"</bankId>");
    sb.append("<areaId>"+ this->_areaId +"</areaId>");
    sb.append("<idNumber>"+ this->_idNumber +"</idNumber>");
    sb.append("<loginPhone>"+ this->_loginPhone +"</loginPhone>");
    
    sb.append("<accountChange>");
//    sb.append("<phone>"+ this->_phone + "</phone>");
    sb.append("<cardNumber>"+ this->_cardNumber + "</cardNumber>");
    sb.append("</accountChange>");
    
//    sb.append("<address>"+this->_address+"</address>");
//    sb.append("<postCode>"+this->_postCode+"</postCode>");
//    sb.append("<email>"+this->_email+"</email>");
//    sb.append("<tel>"+this->_tel+"</tel>");
//    sb.append("<faxNo>"+this->_faxNo+"</faxNo>");
    
//    sb.append("<areaId>"+ this->_areaId +"</areaId>");
//    sb.append("<bankId>"+ this->_bankId +"</bankId>");
//    sb.append("<loginPhone>"+ this->_loginPhone +"</loginPhone>");
//    
//    sb.append("<accountChange>");
//    sb.append("<phone>"+ this->_phone + "</phone>");
//    sb.append("<cardNumber>"+ this->_cardNumber + "</cardNumber>");
//    sb.append("</accountChange>");
//    
//    sb.append("<idNumber>"+ this->_idNumber + "</idNumber>");
    
    
    sb.append("<userType>A</userType>");
    
    return sb;
}

string Transaction1004::getType()
{
	return "1004";
}

void Transaction1004::handleData(xml_node<>* resultData)
{
    
}

void Transaction1004::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}