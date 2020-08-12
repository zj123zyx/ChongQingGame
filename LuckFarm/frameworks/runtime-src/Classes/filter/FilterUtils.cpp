//
//  FilterUtils.cpp
//  CasinoGameNew
//
//  Created by wanghongqi on 16-6-12.
//
//

#include "FilterUtils.h"

FilterUtils * FilterUtils::m_instance = NULL;
FilterUtils::FilterUtils():m_oneWordLength(1){

}
FilterUtils::~FilterUtils(){

}
void FilterUtils::init(){
    string str = "策";
    m_oneWordLength = (int)str.length();
    printf("FilterUtils::init==>m_oneWordLength=%d",m_oneWordLength);
}
FilterUtils * FilterUtils::getInstance(){
    if(m_instance == NULL){
        m_instance = new FilterUtils();
        m_instance->init();
    }
    return m_instance;
}
string FilterUtils::getOneWord(string & str,int position){
    string strchar("");
    int len = (int)str.size();
    if(position>=len){
        printf("FilterUtils::getOneWord==>分隔出错");
        return "";
    }
    int countNum = 0;
    for(int i=position;i<len;i++){
        if(str[i]&0x80){
            countNum = countNum+1;
            strchar+=str.substr(i,1);
            if(countNum == m_oneWordLength){
                break;
            }
        }else{
            if(countNum == 0){
                strchar+=str.substr(i,1);
            }
            break;
        }
    }
    return strchar;
}
