//
//  IntergrateAppsFlyer.h
//  SlotMachine
//
//  Created by Forrest HAN on 5/2/13.
//
//

#ifndef SlotFun_IntergrateAppsFlyer_h
#define SlotFun_IntergrateAppsFlyer_h

class IntergrateAppsFlyer
{
public:
    
    static IntergrateAppsFlyer* instance();
    
    void integrateAppsFlyer();
    
    void appsFlyerTrackEvent(const char* iName, const char* iValue);
    
    const char* getIDFA();
    
private:
    
    IntergrateAppsFlyer(){}
    
    ~IntergrateAppsFlyer();
    
};

#endif
