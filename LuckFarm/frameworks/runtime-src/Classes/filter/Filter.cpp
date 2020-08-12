//
//  Filter.cpp
//  CasinoGameNew
//
//  Created by wanghongqi on 16-6-6.
//
//

#include "Filter.h"
#include <iostream>
#include <fstream>
#include "cocos2d.h"
using namespace cocos2d;



bool Filter::__LEGAL = true;
bool Filter::__ILLEGAL = false;
bool Filter::__initialized = false;
Trie Filter::__trie(TrieNode::UTF8);
void Filter::init(Level level,std::string loadFile) {
    if (level == Filter::NORMAL) {
        load(loadFile.c_str(),0);
    } else if (level == Filter::HIGH) {
        load(loadFile.c_str(),0);
    } else{
    }
    __initialized = true;
}

void Filter::load(const char* filePath, int startPos) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    unsigned char* pBuffer = NULL;
    ssize_t bufferSize = 0;
    pBuffer = FileUtils::getInstance()->getFileData(filePath, "rb", &bufferSize);
    
    
    //在需要按行拆分的时候就使用下边的代码
    std::string s = (char*)pBuffer;
    std::string inFile = s.substr(0,bufferSize);
    
    size_t size=inFile.size();
    std::string::size_type pos;
    for(size_t i=0; i<size; i++)
    {
        pos=inFile.find("\n",i);
        if(pos<size)
        {
            std::string word=inFile.substr(i,pos-i);
            /*此处s即获取到的单行信息*/
            //CCLOG("word:%s==%d",word.c_str(),word.length());
            __trie.insert(word);
            i=pos;
        }
    }
    
    if(bufferSize >0 && pBuffer){
        delete[] pBuffer;
        pBuffer = nullptr;
    }
    
    
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::ifstream keywordsFile(filePath, std::ios::in);
    CCLOG("filePath:%s",filePath);
    CCLOG("filePath:%d",keywordsFile.is_open());
    if (keywordsFile.is_open()) {
        keywordsFile.seekg(0, std::ios::beg);
        char buffer[256];
        
        while( keywordsFile.getline(buffer,256) )
        {
            string word;
            word.assign(buffer);
            //CCLOG("word:%s==%d",word.c_str(),word.length());
            __trie.insert(word);
        }
    }
    keywordsFile.close();
#endif
}

bool Filter::censor(std::string& source) {
    if (!__initialized) {
        CCLOG("Filter::censor==>屏蔽字库未初始化！");
        return __ILLEGAL;
    } else {
        unsigned long length = source.size();
        
        for(int i=0;i<length;i++){
            string m = FilterUtils::getInstance()->getOneWord(source,i);
            
            string substring = source.substr(i, length-i);
            if (__trie.find(substring) != NULL) {
                __trie.count = 0;
                __trie.bitCount = 0;
                return __ILLEGAL;
            }
            
            int tempLen = (int)m.length();
            if(tempLen>1){
                i = i+tempLen-1;
            }
            
        }
        return __LEGAL;
    }
}
string Filter::censorEx(string source){
    if (!__initialized) {
        CCLOG("Filter::censorEx==>屏蔽字库未初始化！");
        return "";
    } else {
        unsigned long  length = source.size();
        
        for(int i=0;i<length;i++){
            string m = FilterUtils::getInstance()->getOneWord(source,i);
            
            string substring = source.substr(i, length-i);
            if (__trie.find(substring) != NULL) {
                source.replace(i,(__trie.bitCount)*TrieNode::UTF8,"**");
                length = source.size();
                __trie.count = 0;
                __trie.bitCount = 0;
            }
            
            
            int tempLen = m.length();
            if(tempLen>1){
                i = i+tempLen-1;
            }
        }
        
        return source;
    }

}
