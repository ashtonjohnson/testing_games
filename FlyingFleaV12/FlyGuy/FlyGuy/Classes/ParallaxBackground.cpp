//
//  ParallaxBackground.cpp
//  NobWars
//
//  Created by Hadron Solutions on 23/07/13.
//
//

#include "ParallaxBackground.h"
#include "Utility.h"

#define Z_ORDER_BG            0

CCSpriteBatchNode* ParallaxBackground:: addBatchNodes(CCString *spriteName) {
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCSpriteBatchNode *spriteBatchNode = CCSpriteBatchNode::create("parallax_bg.png", 3);
    spriteBatchNode->setPosition(CCPointZero);
    this->addChild(spriteBatchNode, Z_ORDER_BG);
    
	int positionX[3] = {0, winSize.width - 1, -(winSize.width - 1)};
	
	for (int i = 0; i < 3; i++){
		CCSprite* sprite = CCSprite::createWithSpriteFrameName(spriteName->getCString());
		sprite->setAnchorPoint(CCPointMake(0,0.5));
		sprite->setPosition(CCPointMake(positionX[i],winSize.height/2));
		if (i != 0) {
			sprite->setFlipX(true);
		}
        spriteBatchNode->addChild(sprite, i);
	}
    return spriteBatchNode;
}

void ParallaxBackground:: addBackgroundBatchNodes(GameLayer* gLayer) {
    gameLayer = gLayer;
    backgroundSpriteBatch = this->addBatchNodes(CCString::create("game_bg_0.png"));
//    backgroundSpriteBatch->setPosition(ccp(winSize.width * 0, -winSize.height * 0.5));
    borderDownSpriteBatch = this->addBatchNodes(CCString::create("grassDown_3.png"));
    borderDownSpriteBatch->setPosition(ccp(winSize.width * 0, -winSize.height * 0.25));
    borderUpSpriteBatch = this->addBatchNodes(CCString::create("grassUp_3.png"));
    borderUpSpriteBatch->setPosition(ccp(winSize.width * 0, winSize.height * 0.25));
}

void ParallaxBackground:: checkAndMoveBatchNode(CCSpriteBatchNode *batchNode, float velocity) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *sprite = NULL;
    CCObject *obj = NULL;
    
    CCARRAY_FOREACH(batchNode->getChildren(), obj) {
        sprite = (CCSprite*)obj;
        float pos = sprite->getPositionX();
        pos +=  velocity;
        if (pos < -winSize.width) {
            pos += (winSize.width * 2) - 2;
//            if (batchNode == backgroundSpriteBatch) {
//                sprite->removeAllChildrenWithCleanup(true);
//                int y = Utility::randomIntBetween(winSize.height * 0.2, winSize.height * 0.85);
//                CCSprite *obj = CCSprite::createWithSpriteFrameName("justCheck.png");
//                obj->setPosition(ccp(y,y));
//                sprite->addChild(obj);
//                CCLog("objXPos y %d", y);
//            }
        } else if (pos > winSize.width - 1) {
            pos -= (winSize.width * 2) - 2;
        }
        sprite->setPositionX(pos);
    }
}

void ParallaxBackground:: updateBatchNodes() {
    this->checkAndMoveBatchNode(backgroundSpriteBatch, -3.0);
    this->checkAndMoveBatchNode(borderUpSpriteBatch, -3.0);
   this->checkAndMoveBatchNode(borderDownSpriteBatch, -3.0);
}

void ParallaxBackground:: onExit() {
    CCNode::onExit();
}

