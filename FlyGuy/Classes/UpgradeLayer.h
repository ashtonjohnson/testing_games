//
//  UpgradeLayer.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 29/10/13.
//
//

#ifndef __FlyGuy__UpgradeLayer__
#define __FlyGuy__UpgradeLayer__

#include <iostream>
#include "cocos2d.h"
#include "FGScrollView.h"
using namespace cocos2d;

class UpgradeLayer: public CCLayer {
public:
    virtual bool init(ObjectiveStatus pObjectiveStatus);
    static UpgradeLayer* create(ObjectiveStatus pObjectiveStatus);
    void addMenuItems(const char *frameName, int tag);
    void loadObjectiveAchieved();
    void updateObjAchievedLayer();
    void createLabel(const char *labelName, CCPoint position);
    void goToUpgradeScreenWithCoinsStars(CCNode *sender, void *data);
    void onEnter();
    void onExit();
    
    CCSize winSize;
    CCArray *charMenuIemList;
    void menuCallBack(CCObject *menuItem);
    CCProgressTimer *objAchieved;
    CCLabelBMFont *perLabel, *coinLabel, *headLabel, *label, *starLabel;
    FGScrollView *fgScrollView;
    void removeAdsListener(CCNode *sender, void *data);
    void replaceSceneAfterUnlock(CCNode *sender, void *data);
    void restorePurchases() ;
    
};

#endif /* defined(__FlyGuy__UpgradeLayer__) */
