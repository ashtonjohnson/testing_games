//
//  RandomParallaxBg.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 21/09/13.
//
//

#ifndef __FlyGuy__RandomParallaxBg__
#define __FlyGuy__RandomParallaxBg__

#include <iostream>
#include "cocos2d.h"
#include "Constant.h"
#include "Box2D.h"
#include "UserData.h"

using namespace cocos2d;
class GameLayer;
class RandomParallaxBg : public CCNode {
public:
//    UserData *spriteUserData;
    UserData *spriteUserData;
//    CCSprite *sprite;
    GameLayer *gameLayer;
    CCSize winSize;
    CCArray *bgArray;
    CCSpriteBatchNode *backgroundSpriteBatch;
    bool isActive;
    b2Body *body;
    void createSprite(CCString *spriteName, GameLayer *gLayer, CCPoint position, CaveType caveType);
    void createOneTimeBg(GameLayer *gLayer, CCString *spriteName);
    void moveBg();
    CCSpriteBatchNode* addBatchNodes(CCString *spriteName);
    void checkAndMoveBatchNode(CCSpriteBatchNode *batchNode, float velocity);
    void updateBodyPos();
};
#endif /* defined(__FlyGuy__RandomParallaxBg__) */
