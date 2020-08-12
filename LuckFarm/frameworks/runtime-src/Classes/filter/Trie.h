//
//  Trie.h
//  CasinoGameNew
//
//  Created by wanghongqi on 16-6-6.
//
//

#ifndef __CasinoGameNew__Trie__
#define __CasinoGameNew__Trie__

#include <stdio.h>

#include <map>
#include <string>
#include "TrieNode.h"
#include "FilterUtils.h"
class Trie {
private:
    TrieNode __emptyRoot;
    int __pace;
   
    TrieNode* insert(TrieNode* parent, std::string& keyword,int len=-1);
    TrieNode* insertBranch(TrieNode* parent, std::string& keyword,int len=-1);
    TrieNode* find(TrieNode* parent, std::string& keyword);
    std::string toString(TrieNode* parent);
    std::string getKeywords(const std::string& character, const TrieNode* parent);
public:
    int __size;
    int count;    //当前查找的一个敏感词的字数
    int bitCount;

    Trie(TrieNode::Encoding encoding);
    ~Trie();
    TrieNode* insert(std::string& keyword);
    TrieNode* insert(const char* keyword);
    TrieNode* find(std::string& keyword);
    std::string toString();
    std::string getKeywords();
};
inline Trie::~Trie() {
}

#endif /* defined(__CasinoGameNew__Trie__) */
