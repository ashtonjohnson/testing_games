//
//  UpgradeScene.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 29/10/13.
//
//

#ifndef __FlyGuy__UpgradeScene__
#define __FlyGuy__UpgradeScene__

#include <iostream>
#include "cocos2d.h"
#include "FGScrollView.h"
using namespace cocos2d;

class UpgradeScene: public CCScene {
public:
    virtual bool init(ObjectiveStatus pObjectiveStatus);
    static UpgradeScene* create(ObjectiveStatus pObjectiveStatus);
    
    CCSize winSize;
};

#endif /* defined(__FlyGuy__UpgradeScene__) */
