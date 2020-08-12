#include "AbstractTransaction.h"

AbstractTransaction::AbstractTransaction():_responseCode(""), _responseMsg("")
{
	
}

AbstractTransaction::~AbstractTransaction()
{
	log("AbstractTransaction::~AbstractTransaction()");
}

string AbstractTransaction::getSendContent()
{
	string sb;
	string str = buildXmlBody(sb);
	return buildPackage(getType(), str);
}

// 不可char* str = "";传，char*似乎后面缺"\0"
void AbstractTransaction::handleXml(char * resultXml)
{
	xml_document<> doc;
	doc.parse<0>(resultXml);//将数据写入xml_document

	xml_node<>* rootNode = doc.first_node();//获取根节点

	xml_node<>* headNode = rootNode->first_node();//获取head节点

	xml_node<>* typeNode = headNode->first_node();//获取type节点

	xml_node<>* bodyNode = headNode->next_sibling();//获取body节点
	
	xml_node<>* responseNode = bodyNode->first_node();//获取response节点
	
	xml_node<>* responseCodeNode = responseNode->first_node();//获取responseCode节点
	
	this->_responseCode = responseCodeNode->value();

	auto responseMsgNode = responseCodeNode->next_sibling();
	this->_responseMsg = responseMsgNode->value();		
	log("responseCode=%s", this->_responseCode.c_str());	
	
	auto responseDataNode = responseNode->next_sibling();
    if (_responseCode == "000000"){
        this->handleData(responseDataNode);
    }else if (_responseCode == "100302"){
        this->handleVersionData(responseDataNode);
    }else if (_responseCode == "700008"){
        if (strcmp(this->getType().c_str(), "7004") == 0) {
            this->handleData(responseDataNode);
        }
    }
}

string AbstractTransaction::buildPackage(string type, string xmlData) 
{	
	string sb;
	char out[50] = {0};	
	CppMd5::EncryptMD5str(out, (unsigned char*)xmlData.c_str(), xmlData.size());
	//log("AbstractTransaction::md5 = %s", out);
	string md5Str(&out[0], &out[strlen(out)]);  

    string hallVersion ="";// UserDefault::getInstance()->getStringForKey("hallVersion");
    string clientType ="";// UserDefault::getInstance()->getStringForKey("clientType");
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        clientType = "ios";
        hallVersion = "1.0.0";
    #endif
        
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        clientType = "android";
        hallVersion = "2.2.5";
    #endif
    
    // log("AbstractTransaction::hallVersion = %s", hallVersion.c_str());
    // log("AbstractTransaction::clientType = %s", clientType.c_str());
    
    sb.append("<?xml version= '1.0' encoding='utf-8'?>");
    sb.append("<message>");
    sb.append("<head>");
    sb.append("<type>" + type + "</type>");
    sb.append("<messageId>1</messageId>");
    sb.append("<clientType>" + clientType + "</clientType>");
    sb.append("<agentId>A000000000000082</agentId>");
    sb.append("<digest>" + md5Str + "</digest>");
    sb.append("<version>" + hallVersion + "</version>");
    sb.append("</head>");
    sb.append("<body>");
    sb.append(xmlData);
    sb.append("</body>");
    sb.append("</message>");
    return sb;
}

