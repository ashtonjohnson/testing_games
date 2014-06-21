//
//  
//  Speriminator
//
//  Created by Hadron Solutions on 23/07/13.
//
//

#ifndef __Speriminator__Abstacle__
#define __Speriminator__Abstacle__

#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"
class UserData;

using namespace cocos2d;

class Obstacle : public CCNode {
public:
    GameLayer *gLayer;
    UserData *spriteUserData;
//    CCSprite *sprite;
    CCSize winSize;
    bool isActive;
    float reachTime;
    void createSprite(GameLayer *gameLayer, ObstacleType obstacleType, CCString *spriteName, CCPoint position);
    void removeObstacle();
    void removeWeakWallAnimation();
    void onExit();
    bool isWallMoving;
    b2Body *body;
    void updateBodyPos();
};



#endif /* defined(__Speriminator__Abstacle.h__) */
