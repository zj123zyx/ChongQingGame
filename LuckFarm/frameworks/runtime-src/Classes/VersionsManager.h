//
//  VersionsManager.h
//  SlotFun
//
//  Created by xuzhiqiang on 14-4-21.
//
//

#ifndef __SlotFun__VersionsManager__
#define __SlotFun__VersionsManager__

#include <iostream>
#include "network/HttpClient.h"
#include "LoadingLayer.h"
#include <vector>


using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::network;
using namespace std;

class VersionsManager: public Ref
{
public:
    static VersionsManager* sharedVersionsManager(void);
    static void purgeSharedVersionsManager(void);
    
    ~VersionsManager(void);
    
    bool checkUpdate();
    
    void getUpdateFilesList();

    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
    
    void postUpdateAgain();
protected:
    bool addUserDownload(const char* flag,const char* name,const char* md5);
    void showLoading();
    void onLoadLayerLoaded();
    Node* openLoadingLayer();
    
private:
    VersionsManager(void);
    
    LoadingLayer* m_pLoadLayar;
    KVMAP mDownloadFiles;
    AssetsManager * m_pAssetsManager;
    static VersionsManager*  s_sharedVersionsManager;
    
    string m_serverUrl;
    string m_versionUrl;
};

#endif /* defined(__SlotFun__VersionsManager__) */
