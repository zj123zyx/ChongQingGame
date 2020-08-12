//
//  TrieNode.h
//  CasinoGameNew
//
//  Created by wanghongqi on 16-6-6.
//
//

#ifndef __CasinoGameNew__TrieNode__
#define __CasinoGameNew__TrieNode__

#include <stdio.h>
#include<iostream>
#include<sstream>
#include<string>
#include <map>
#include<vector>
using namespace std;

class Trie;
class TrieNode {
    string a;
    friend class Trie;
    typedef std::map<std::string, TrieNode> _TrieMap;
    typedef std::map<std::string,TrieNode>::const_iterator _TrieMapIterator;
private:
    std::string __character;
    _TrieMap __map;
    TrieNode* __parent;
    int __dataSize;
    vector<int> m_TrieLenVector;
    void setTrieLen(int len);
public:
    enum Encoding {
        UTF8 = 1,
        UTF16 = 2
    };
    TrieNode(int dataSize);
    TrieNode(std::string character, int dataSize);
    ~TrieNode();
    std::string getCharacter() const;
    TrieNode* findChild(std::string& nextCharacter) const;
    TrieNode* insertChild(std::string& nextCharacter);
    
    bool isHasThisLen(int len);
};
inline TrieNode::TrieNode(int dataSize) {
    __dataSize = dataSize;
    __map.clear();
}
inline TrieNode::~TrieNode() {
}
inline std::string TrieNode::getCharacter() const {
    return __character;
}

#endif /* defined(__CasinoGameNew__TrieNode__) */
