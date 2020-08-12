#ifndef _ABSTRACTTRANSACTIONA_H_
#define _ABSTRACTTRANSACTIONA_H_

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    #include "rapidxml.hpp"
    #include "rapidxml_iterators.hpp"
    #include "rapidxml_print.hpp"
    #include "rapidxml_utils.hpp"
    #include "md5.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "./util/xml/rapidxml.hpp"
    #include "./util/xml/rapidxml_iterators.hpp"
    #include "./util/xml/rapidxml_print.hpp"
    #include "./util/xml/rapidxml_utils.hpp"
    #include "./util/md5.h"
#endif

USING_NS_CC;
using namespace std;
using namespace rapidxml;

#define WRITEONLY_PASS_BY_REF(varType, varName, funName)\
private: varType varName;\
public: virtual void set##funName(const varType& var){ varName = var; }

class AbstractTransaction
{
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _responseCode, ResponseCode); 

	CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _responseMsg, ResponseMsg); 

public:
	AbstractTransaction();

	virtual ~AbstractTransaction();

	virtual string getType() = 0;

protected:
	virtual string buildXmlBody(string sb) = 0;

	virtual void handleData(xml_node<>* resultData) = 0;
    
    virtual void handleVersionData(xml_node<>* resultData) = 0;

public:		
	string getSendContent();
	//// 必须要传入联系到string或file的char*, 不可纯char*,否则会报错
	void handleXml(char * resultXml);

private:
	string buildPackage(string type, string xmlData);

};

#endif