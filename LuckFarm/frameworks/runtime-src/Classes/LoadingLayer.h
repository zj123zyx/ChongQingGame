//
//  LoadingLayer.h
//
//  Created by Zhiqiang Xu on 12-8-10.
//  Copyright (c) 2012年 RenRenGame. All rights reserved.
//

#ifndef GameWorld_LoadingLayer_h
#define GameWorld_LoadingLayer_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocosbuilder/CocosBuilder.h"

using namespace cocos2d;
using namespace extension;
using namespace cocosbuilder;

using namespace cocos2d::ui;

#define KEY_RES                 "res"
#define KEY_BASEURL             "base_url"
#define KEY_MAINVERSION         "main_version"
#define KEY_VERSION             "version"
#define KEY_CURRENT_VERSION     "current-version-code"
#define KEY_DOWNLOADURL         "download_link"
#define KEY_SERVERURL           "server_url"
#define KEY_VERSIONURL          "version_url"
#define KEY_SOCKET_ADDR         "socket_addr"
#define KEY_SOCKET_PORT         "socket_port"

typedef std::map<std::string, std::string> KVMAP;

class LoadingLayer
: public Layer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public NodeLoaderListener
, public AssetsManagerDelegateProtocol
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LoadingLayer, create);

    LoadingLayer();
    virtual ~LoadingLayer();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onError(cocos2d::extension::AssetsManager::ErrorCode errorCode);
    virtual void onProgress(int percent);
    virtual void onSuccess();
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Ref * pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Ref * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(Ref* pTarget, const char* pMemberVariableName, Node* pNode);
    virtual void onNodeLoaded(Node * pNode, NodeLoader * pNodeLoader);
    
    void touchButton(Object* object,TouchEventType type);
    void resumeRetry(float time);
    
    void initWithAssetsManager(cocos2d::extension::AssetsManager* assetsMgr, KVMAP &filesmap);
    
    void setProgressFromTo(int from, int to);
    
protected:
    KVMAP mFileList;
    KVMAP::iterator mIT;
    Node * mRoorNode;
    Label * mProgressLabel;
    Sprite * mProgressSprite;
    Node * mProgressNode;
    ProgressTimer* mProgressTimer;
    AssetsManager* mAssetsMgr;
    
    Node* mRetryLayer;
    Sprite* mRetrySprite;
};


class LoadingLayerLoader : public LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LoadingLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LoadingLayer);
};

#endif
