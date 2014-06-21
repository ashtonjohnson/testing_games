//
//  ParallaxBackground.h
//  NobWars
//
//  Created by Hadron Solutions on 23/07/13.
//
//

#ifndef __NobWars__ParallaxBackground__
#define __NobWars__ParallaxBackground__

#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"

using namespace cocos2d;

class ParallaxBackground : public CCNode {
public:
    GameLayer *gameLayer;
    CCSize winSize;
    CCSpriteBatchNode *backgroundSpriteBatch;
    CCSpriteBatchNode *borderUpSpriteBatch;
    CCSpriteBatchNode *borderDownSpriteBatch;
    
    CCSpriteBatchNode* addBatchNodes(CCString *spriteName);
    void addBackgroundBatchNodes(GameLayer* gLayer);
    virtual void onExit();
    void updateBatchNodes();
    void checkAndMoveBatchNode(CCSpriteBatchNode *batchNode, float velocity);
};


#endif /* defined(__NobWars__ParallaxBackground__) */
