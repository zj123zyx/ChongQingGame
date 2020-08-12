//
//  ImagePicker.h
//  baobing
//
//  Created by 李战平 on 5/26/15.
//
//

#ifndef baobing_ImagePicker_h
#define baobing_ImagePicker_h

#include <map>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "CCLuaValue.h"
//#include "HttpClient.h"


class ImagePicker
{
    
public:
    ~ImagePicker();
    
    static ImagePicker* sharedImagePicker();
    
    void setImgPickerListenerLua(cocos2d::LUA_FUNCTION listener);
    
    void startImagePicker();

    void startImageCamera();
    
    void updateUserImg(const char* url);
    
private:
    
    static ImagePicker*  s_storeKit;
    
    cocos2d::LUA_FUNCTION mListener;
    
};

#endif
