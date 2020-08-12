//
//  FilterUtils.h
//  CasinoGameNew
//
//  Created by wanghongqi on 16-6-12.
//
//

#ifndef __CasinoGameNew__FilterUtils__
#define __CasinoGameNew__FilterUtils__

#include <stdio.h>
#include <string>

using namespace std;

class FilterUtils{
public:
    ~FilterUtils();
    
    static FilterUtils * getInstance();
    string getOneWord(string & str,int position=0);
private:
    FilterUtils();
    static FilterUtils * m_instance;
    int m_oneWordLength;
    void init();
};

#endif /* defined(__CasinoGameNew__FilterUtils__) */
