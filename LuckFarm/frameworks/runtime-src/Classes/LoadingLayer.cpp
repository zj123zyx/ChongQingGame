//
//  LoadingLayer.cpp
//  GameWorld
//
//  Created by Zhiqiang Xu on 12-8-10.
//  Copyright (c) 2012年 RenRenGame. All rights reserved.
//

#include <iostream>
#include "LoadingLayer.h"
#include "VersionsManager.h"

LoadingLayer::LoadingLayer():
mProgressSprite(NULL),mProgressLabel(NULL),mProgressTimer(NULL),mRoorNode(NULL),mRetryLayer(NULL),mRetrySprite(NULL),mProgressNode(NULL)
{
}

LoadingLayer::~LoadingLayer()
{
}

void LoadingLayer::onEnter(){   
    Layer::onEnter();
}

void LoadingLayer::onExit(){
    Layer::onExit();
}

void LoadingLayer::onError(AssetsManager::ErrorCode errorCode)
{
    CCLOG("LoadingLayer::onError");
    if (errorCode == AssetsManager::ErrorCode::NO_NEW_VERSION)
    {
        CCLOG("LoadingLayer::NO_NEW_VERSION");
        //mProgressLabel->setString("no new version");
        
        mRoorNode->setVisible(false);
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("APP_UPDATE_FINISHBACK_EVENT");
    }
    
    if (errorCode == AssetsManager::ErrorCode::NETWORK)
    {
        CCLOG("LoadingLayer::NETWORK");
        mRetryLayer->setVisible(true);
    }
}

void LoadingLayer::onProgress(int percent)
{
    char progress[20];
    snprintf(progress, 20, "更新已下载 %d%%", percent);
    
    if (percent > 0) {
        mProgressLabel->setString(progress);
        mProgressTimer->setPercentage(percent);
    }

}

void LoadingLayer::onSuccess()
{
    UserDefault::getInstance()->setStringForKey(mIT->first.c_str(),mIT->second.c_str());
    
    ++mIT;
    
    if (mIT != mFileList.end()) {
        std::string key     = mIT->first;
        std::string value   = mIT->second;
        std::string baseurl = UserDefault::getInstance()->getStringForKey(KEY_BASEURL);
        baseurl += key;
        
        mAssetsMgr->deleteVersion();
        UserDefault::getInstance()->flush();

        mAssetsMgr->setPackageUrl(baseurl.c_str());
        mAssetsMgr->update();
        
    }
    else{
        mRoorNode->setVisible(false);
        mProgressLabel->setString("下载完成");
        mProgressNode->setVisible(false);

        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("APP_UPDATE_FINISHBACK_EVENT");
    }
}

void LoadingLayer::setProgressFromTo(int from, int to)
{
    ActionInterval* layerAction = (ActionInterval*)Sequence::create(
                                                                    ProgressFromTo::create(1, from, to),
                                                                    nullptr);
    mProgressTimer->runAction(layerAction);
}

void LoadingLayer::onNodeLoaded(Node *pNode, NodeLoader *pNodeLoader)
{
    mRoorNode->setScale(0.56);

    mProgressNode->setVisible(false);

    Point pt = mProgressSprite->getPosition();
    Node* parent = mProgressSprite->getParent();
    
    mProgressSprite->removeFromParentAndCleanup(false);
    mProgressTimer = CCProgressTimer::create(mProgressSprite);
    mProgressTimer->setType(ProgressTimer::Type::BAR);
    mProgressTimer->setMidpoint(Vec2(0, 0));
    mProgressTimer->setBarChangeRate(Vec2(1, 0));
    mProgressTimer->setPosition(pt);
    
    parent->addChild(mProgressTimer);
    
    Point retryPt = mRetrySprite->getPosition();
    Node* retryParent = mRetrySprite->getParent();
    mRetrySprite->removeFromParentAndCleanup(false);
    
    Button *m_pUpBtn = Button::create();
    m_pUpBtn->setTouchEnabled(true);
    m_pUpBtn->loadTextures( "eshare_btn_chongshi.png", "eshare_btn_chongshi.png", "eshare_btn_chongshi.png", cocos2d::ui::Button::TextureResType::PLIST);
    m_pUpBtn->setPosition(retryPt);
    m_pUpBtn->addTouchEventListener(this,  toucheventselector( LoadingLayer::touchButton ) );
    retryParent->addChild(m_pUpBtn);
    
    mRetryLayer->setVisible(false);
    
}

void LoadingLayer::initWithAssetsManager(cocos2d::extension::AssetsManager* assetsMgr,KVMAP &filesmap)
{
    mAssetsMgr = assetsMgr;
    mFileList = filesmap;
    
    mIT = mFileList.begin();
    
    if (mIT != mFileList.end()) {
        std::string key     = mIT->first;
        std::string value   = mIT->second;
        std::string baseurl = UserDefault::getInstance()->getStringForKey(KEY_BASEURL);
        baseurl += key;
        
        mAssetsMgr->setPackageUrl(baseurl.c_str());
        mAssetsMgr->setDelegate(this);
        mAssetsMgr->update();
        mProgressNode->setVisible(true);
    }
}

SEL_MenuHandler LoadingLayer::onResolveCCBCCMenuItemSelector(Ref * pTarget, const char* pSelectorName) {
    return NULL;    
}

Control::Handler LoadingLayer::onResolveCCBCCControlSelector(Ref * pTarget, const char* pSelectorName) {
    return NULL;
}

bool LoadingLayer::onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode) {
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "rootView", Node*, mRoorNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "progressLabel", Label*, mProgressLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "progressSprite", Sprite*, mProgressSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "progressNode", Node*, mProgressNode);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "retryLayer", Node*, mRetryLayer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "retrySprite", Sprite*, mRetrySprite);

    return false;
}

void LoadingLayer::touchButton(Object* object,TouchEventType type)
{
    switch (type)
    {
        case TouchEventType::TOUCH_EVENT_BEGAN:
            break;
        case TouchEventType::TOUCH_EVENT_MOVED:
            break;
        case TouchEventType::TOUCH_EVENT_ENDED:
        {
            mRetryLayer->setVisible(false);
            this->schedule(CC_SCHEDULE_SELECTOR(LoadingLayer::resumeRetry), 1.0f);
        }
            break;
        case TouchEventType::TOUCH_EVENT_CANCELED:
            break;
        default:
            break;
    }
}

void LoadingLayer::resumeRetry(float time)
{
    //CCLOG("LoadingLayer::resumeRetry ");
    this->unschedule(CC_SCHEDULE_SELECTOR(LoadingLayer::resumeRetry));
    
    this->removeFromParent();
    VersionsManager::sharedVersionsManager()->postUpdateAgain();
}