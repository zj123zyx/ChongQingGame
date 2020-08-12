//
//  TrieNode.cpp
//  CasinoGameNew
//
//  Created by wanghongqi on 16-6-6.
//
//

#include "TrieNode.h"

TrieNode::TrieNode(std::string character, int dataSize) {
    if (character.size() == 2)
        __character.assign(character);
    else
        __character.assign(character);
        //printf("TrieNode::TrieNode==>error，%d",(int)character.size());
    
    __map.clear();
    m_TrieLenVector.clear();
}
TrieNode* TrieNode::findChild(std::string& nextCharacter) const {
    _TrieMapIterator ___trieMapIt = __map.find(nextCharacter);
    return (___trieMapIt == __map.end()) ? NULL : const_cast<TrieNode*>(&(___trieMapIt->second));
}
TrieNode* TrieNode::insertChild(std::string& nextCharacter) {
    if (!findChild(nextCharacter)) {
        TrieNode tempTrieNode =TrieNode(nextCharacter, __dataSize);
        __map.insert(std::pair<std::string, TrieNode>(nextCharacter, tempTrieNode));
        return &(__map.find(nextCharacter)->second);
    }
    return NULL;
}
void TrieNode::setTrieLen(int len){
    if(len<0){
        return;
    }
    vector<int>::iterator it;
    for(it=m_TrieLenVector.begin();it!=m_TrieLenVector.end();it++){
        if(len == (*it)){
            return;
        }
    }
    m_TrieLenVector.push_back(len);
}
bool TrieNode::isHasThisLen(int len){
    vector<int>::iterator it;
    for(it=m_TrieLenVector.begin();it!=m_TrieLenVector.end();it++){
        if(len == (*it)){
            return true;
        }
    }
    return false;
}


