//
//  ObjectiveLayer.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 23/10/13.
//
//

#ifndef __FlyGuy__ObjectiveLayer__
#define __FlyGuy__ObjectiveLayer__

#include <iostream>
#include "cocos2d.h"
#include "FGScrollView.h"

using namespace cocos2d;

class ObjectiveLayer: public CCLayer {
public:
    virtual bool init();
    static ObjectiveLayer* create();
    void addMenuItems(const char *frameName, int tag);
    void loadObjectiveAchieved();
    void updateObjAchievedLayer();
    
    CCSize winSize;
    CCArray *charMenuIemList;
    void menuCallBack(CCObject *menuItem);
    CCProgressTimer *objAchieved;
    CCLabelBMFont *perLabel, *label;;
    FGScrollView *fgScrollView;
    bool atLeastOneAchieved;
    CCSprite *colorLayerRight;
    CCLabelBMFont *notYetClearedLabel;
};

#endif /* defined(__FlyGuy__ObjectiveLayer__) */
