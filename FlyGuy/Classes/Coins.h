//
//  Coins.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 02/10/13.
//
//

#ifndef __FlyGuy__Coins__
#define __FlyGuy__Coins__


#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"
#include "Constant.h"
class UserData;

using namespace cocos2d;

class Coins : public CCObject {
public:
    GameLayer *gameLayer;
    UserData *spriteUserData;
//    CCSprite *sprite;
    CCSize winSize;
    bool isActive;
    float reachTime;
    CCAnimate *animateAction;
    void onExit();
    void runAnimation(const char* frameName);
    void createSprite(GameLayer *gameLayer, CCString *spriteName, CCPoint position, CoinsType pCoinsType);
    void removeObstacle();
    void resetCoins();
//    void applyForce(b2Body *otherBody ,float delta, CCSprite  *charSprite);
    b2Body *body;
    void updateBodyPos();
    void setDeletionForCoin();
    void runFinalAnimation(const char *frameName);
    void ApplyMagnetPower();
    int getMaxMoveDistance();
    bool shouldApplyMagnet;
};

#endif /* defined(__FlyGuy__Coins__) */
