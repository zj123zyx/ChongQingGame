//
//  LogoScene.cpp
//  CasinoGameNew
//
//  Created by lizhanping on 16-6-24.
//
//

#include "LogoScene.h"
LogoScene::LogoScene(){

}
LogoScene::~LogoScene(){

}

bool LogoScene::init(){
    if ( !Scene::init() )
    {
        return false;
    }
    
    float winWidth = Director::getInstance()->getWinSize().width;
    float winHeight = Director::getInstance()->getWinSize().height;
    
    m_logo = Sprite::create("res/logo/Default.png");
    
    float logoWidth = m_logo->getContentSize().width;
    float logoHeigh =m_logo->getContentSize().height;
    
    m_logo->setPosition(Vec2(winWidth/2,winHeight/2));
    
    if(winWidth/logoWidth < winHeight/logoHeigh){
        m_logo->setScale(winHeight/logoHeigh);
    }else{
        m_logo->setScale(winWidth/logoWidth);
    }
    
    this->addChild(m_logo);
    
    return true;
}
void LogoScene::setDelegate(AppDelegate * delegate){
    m_delegate = delegate;
}
void LogoScene::onEnter(){
    Scene::onEnter();
    this->scheduleOnce(schedule_selector(LogoScene::hideLogo), 3.0f);
}
void LogoScene::hideLogo(float dt){
    if(m_delegate){
        m_delegate->showGameScene();
    }
}