//
//  Filter.h
//  CasinoGameNew
//
//  Created by wanghongqi on 16-6-6.
//
//

#ifndef __CasinoGameNew__Filter__
#define __CasinoGameNew__Filter__

#include <string>
#include "Trie.h"
class Filter {
private:
    static bool __initialized;
    static Trie __trie;
    static void load(const char* fileName, int startPos);
    //static bool censor(std::string& source);
public:
    static bool __LEGAL;
    static bool __ILLEGAL;
    enum Level{
        NORMAL = 1,
        HIGH = 2
    };
    static void init(Level level,std::string loadFile = "");
    static bool isInitialized();
    //判断是否出现了屏蔽字
    //static bool censor(const char* source);
    static bool censor(std::string& source);
    //将屏蔽字用*代替
    static string censorEx(string source);
};
inline bool Filter::isInitialized() {
    return __initialized;
}
#endif /* defined(__CasinoGameNew__Filter__) */
