//
//  LogoScene.h
//  CasinoGameNew
//
//  Created by lizhanping on 16-6-24.
//
//

#ifndef __CasinoGameNew__LogoScene__
#define __CasinoGameNew__LogoScene__

#include <stdio.h>

#include "cocos2d.h"
#include "AppDelegate.h"

using namespace cocos2d;

class LogoScene:public Scene{
public:
    LogoScene();
    virtual ~LogoScene();
    CREATE_FUNC(LogoScene);
    bool init();
    void setDelegate(AppDelegate * delegate);
    void onEnter();
    
private:
    cocos2d::Sprite * m_logo;
    AppDelegate * m_delegate;
    void hideLogo(float dt);
};

#endif /* defined(__CasinoGameNew__LogoScene__) */
