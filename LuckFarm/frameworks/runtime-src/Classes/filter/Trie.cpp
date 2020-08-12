//
//  Trie.cpp
//  CasinoGameNew
//
//  Created by wanghongqi on 16-6-6.
//
//

#include "Trie.h"


Trie::Trie(TrieNode::Encoding encoding) : __emptyRoot(TrieNode(encoding)), __size(0),count(0),bitCount(0){
    switch (encoding) {
        case TrieNode::UTF8:
            __pace = 1;
            break;
        case TrieNode::UTF16:
            __pace = 2;
            break;
        default:
            printf("Trie::Trie==>no this type");
            break;
    }
}
TrieNode* Trie::insert(std::string& keyword) {
    return insert(&__emptyRoot, keyword,(int)keyword.length());
}
TrieNode* Trie::insert(const char* keyword) {
    std::string ___keyword(keyword);
    return insert(___keyword);
}
TrieNode* Trie::insert(TrieNode* parent, std::string& keyword,int len) {
    if (keyword.size() == 0) {
        parent->setTrieLen(len);
        return NULL;
    }
    
    //TODO wangxuebin add 截取一个字符或汉字
    std::string ___firstCharacter = FilterUtils::getInstance()->getOneWord(keyword,0);
    TrieNode* ___firstNode = parent->findChild(___firstCharacter);
    if (___firstNode == NULL) {
        return insertBranch(parent, keyword,len);
    }
    std::string ___restString = keyword.substr(___firstCharacter.length(), keyword.size());
    return insert(___firstNode, ___restString,len);
}
TrieNode* Trie::insertBranch(TrieNode* parent, std::string& keyword,int len) {
    std::string ___firstCharacter = FilterUtils::getInstance()->getOneWord(keyword,0);
    TrieNode* ___firstNode = parent->insertChild(___firstCharacter);
    
    if (___firstNode != NULL) {
        std::string ___restString = keyword.substr(___firstCharacter.size(), keyword.size());
        if (!___restString.empty())
            return insertBranch(___firstNode, ___restString,len);
    }
    ___firstNode->setTrieLen(len);
    return NULL;
}
TrieNode* Trie::find(std::string& keyword) {
    return find(&__emptyRoot, keyword);
}
TrieNode* Trie::find(TrieNode* parent, std::string& keyword) {
    std::string ___firstChild = FilterUtils::getInstance()->getOneWord(keyword,0);
    TrieNode* ___firstNode = parent->findChild(___firstChild);
    if (___firstNode == NULL) {
        count=0;
        bitCount = 0;
        return NULL;
    }
    count++;
    bitCount = bitCount+(int)___firstChild.length();
    
    // More than one character
    std::string ___restString = keyword.substr(___firstChild.size(), keyword.size());
    if (___firstNode->__map.empty()) {
        return ___firstNode;
    }
    
    //TODO 最后一个词的情况下 判断__firstNode 的map里有没有这个长度的 没有返回NULL 解决TMD 和 TMD靠 这种问题
    std::string tempStr = FilterUtils::getInstance()->getOneWord(keyword,0);
    int keyWordLen = (int)keyword.length();
    int tempStrLen = (int)tempStr.length();
    
    if(keyWordLen == tempStrLen){
        if(___firstNode->isHasThisLen(bitCount)){
            return ___firstNode;
        }
        count=0;
        bitCount = 0;
        return NULL;
    }
    
    return find(___firstNode, ___restString);
}
std::string Trie::toString() {
    std::string ___result("[");
    bool ___isFirstChild = true;
    for (TrieNode::_TrieMapIterator ___it = __emptyRoot.__map.begin();
         ___it != __emptyRoot.__map.end(); ++___it) {
        if (___isFirstChild) {
            ___result.append(toString(const_cast<TrieNode*>(&(___it->second))));
            ___isFirstChild = false;
        } else {
            ___result.append(",");
            ___result.append(toString(const_cast<TrieNode*>(&(___it->second))));
        }
    }
    ___result.append("]");
    return ___result;
}
std::string Trie::toString(TrieNode* parent) {
    std::string ___result("[");
    ___result += parent->getCharacter() + ":";
    bool ___isFirstChild = true;
    for (TrieNode::_TrieMapIterator ___it = parent->__map.begin();
         ___it != parent->__map.end(); ++___it) {
        if (___isFirstChild) {
            ___result.append(toString(const_cast<TrieNode*>(&(___it->second))));
            ___isFirstChild = false;
        } else {
            ___result.append(",");
            ___result.append(toString(const_cast<TrieNode*>(&(___it->second))));
        }
    }
    ___result.append("]");
    return ___result;
}
std::string Trie::getKeywords() {
    std::string ___result;
    for (TrieNode::_TrieMapIterator ___it = __emptyRoot.__map.begin();
         ___it != __emptyRoot.__map.end(); ++___it) {
        ___result.append(getKeywords(___it->first, &(___it->second)));
    }
    return ___result;
}
std::string Trie::getKeywords(const std::string& character, const TrieNode* parent) {
    std::string ___result;
    for (TrieNode::_TrieMapIterator ___it = parent->__map.begin();
         ___it != parent->__map.end(); ++___it) {
        //___result.append(Logger::toHex(character, true));
        ___result.append(getKeywords(___it->first, &(___it->second)));
    }
    // Last character
    if (parent->__map.size() == 0) {
        __size++;
        //___result.append(Logger::toHex(character, true));
        ___result.append("\n");
    }
    return ___result;
}