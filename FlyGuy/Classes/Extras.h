//
//  Extras.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 17/10/13.
//
//

#ifndef __FlyGuy__Extras__
#define __FlyGuy__Extras__

#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"

using namespace cocos2d;

class Extras:public CCNode {
public:
    void initWithExtras(GameLayer *gLayer, ExtrasType extraType);
    class GameLayer *gameLayer;
    void performedMysteryBox();
    void performedRocketspecial();
    void performedExtraLifeSpecial();
    void performedBrokenWallSpecial();
    void performedWideLaneSpecial(float delay);
    
    void resetBrokenWallSpecial();
    void addRocketPower();
    void removeRocketPower();
    void resetExtraLifeSpecial();
    
    void setLabel(const char *labelString);

    const char *labelString;
    CCLabelTTF *label;
};
#endif /* defined(__FlyGuy__Extras__) */
