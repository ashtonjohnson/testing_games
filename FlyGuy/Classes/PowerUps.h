//
//  PowerUps.h
//  FlyGuy
//
//  Created by bakshish on 04/10/13.
//
//

#ifndef __FlyGuy__PowerUps__
#define __FlyGuy__PowerUps__

#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"
#include "Constant.h"
class UserData;

using namespace cocos2d;

class PowerUps : public CCNode {
public:
    PowerUps();
    void initPowerUp(GameLayer *gLayer, const char *frameName, int type, CCPoint position);
    GameLayer *gameLayer;
    CCSize winSize;
    UserData *spriteUserData;
//    CCSprite *sprite;
    CCArray powerUpArray;
    b2Body *body;
    void actionPerformed(UserData* userData, float delayPowerUp);
    
    void actionPerformedBubbleShield(float delayPowerUp);
    void actionPerformedSpeedBurst(float delayPowerUp);
    void actionPerformedSuperRocket(float delayPowerUp);
    void actionPerformedTinyMode(float delayPowerUp);
    void actionPerformedByStar();
    void blinkSpriteDuringPowerEnd();
    
    void removeBubbleSprite();
    void resetCharSize();
    void addRocketPower();
    void removeRocketPower();
    void onExit();
};
#endif /* defined(__FlyGuy__PowerUps__) */
