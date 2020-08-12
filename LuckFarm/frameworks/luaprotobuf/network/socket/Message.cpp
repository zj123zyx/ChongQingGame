//
//  message.cpp
//  IMDiors
//
//  Created by 李 战平 on 13-8-21.
//
//

#include "Message.h"

NS_CC_EXT_BEGIN


Message::Message():data(NULL){
    
}

Message::~Message()
{
	if (data!=NULL) {
		delete[] data;
	}
}

NS_CC_EXT_END