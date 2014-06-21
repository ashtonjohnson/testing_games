//
//  RandomParallaxBg.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 21/09/13.
//
//

#include "RandomParallaxBg.h"
#include "Utility.h"
#include "GameLayer.h"

using namespace cocos2d;

static int spriteTag = 100;

void RandomParallaxBg::createSprite(CCString *spriteName, GameLayer *gLayer, CCPoint position, CaveType caveType) {
    winSize = gLayer->winSize;
    spriteUserData = new UserData;
    spriteUserData->initWithFrameName(spriteName->getCString());
    spriteUserData->setReadyForDeletion(false);
    spriteUserData->setCollision(false);
    spriteUserData->sprite->setTag(spriteTag);
    spriteUserData->setTag(spriteTag);
    spriteUserData->userDataType = caveType;
    
    spriteUserData->sprite->setPosition(position);
    if (caveType == kCaveType_UpperWithGrass || caveType == kCaveType_UpperWithoutGrass) {
         spriteUserData->sprite->setAnchorPoint(ccp(0,1));
    } else if (caveType == kCaveType_LowerWithGrass || caveType == kCaveType_LowerWithoutGrass) {
         spriteUserData->sprite->setAnchorPoint(ccp(0,0));
    }   
    spriteTag++;
    gameLayer = gLayer;
    spriteUserData->sprite->setPosition(ccp(-winSize.width, 0));
    gLayer->addChild(spriteUserData->sprite);
    
    isActive = false;
    
    //adding bodies
    b2BodyDef obsBodyDef;
    obsBodyDef.userData = spriteUserData;
    obsBodyDef.type = b2_staticBody;
    body = gameLayer->world->CreateBody(&obsBodyDef);
    body->SetTransform(b2Vec2(-winSize.width/PTM_RATIO, -winSize.width/PTM_RATIO), 0);
    gameLayer->gb2ShapeCache->addFixturesToBody(body, spriteName->getCString());
    spriteUserData->sprite->setAnchorPoint(gameLayer->gb2ShapeCache->anchorPointForShape(spriteName->getCString()));
}

CCSpriteBatchNode* RandomParallaxBg::addBatchNodes(CCString *spriteName) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSpriteBatchNode *spriteBatchNode = CCSpriteBatchNode::create("bgTexture.png", 3);
    spriteBatchNode->setPosition(CCPointZero);
    this->addChild(spriteBatchNode, 0);
    
	int positionX[3] = {0, winSize.width - 1, -(winSize.width - 1)};
	
	for (int i = 0; i < 3; i++){
		CCSprite* sprite = CCSprite::createWithSpriteFrameName(spriteName->getCString());
		sprite->setAnchorPoint(CCPointMake(0,0.5f));
		sprite->setPosition(CCPointMake(positionX[i],winSize.height/2));
		if (i != 0) {
			sprite->setFlipX(true);
		}
        spriteBatchNode->addChild(sprite, i);
	}
    return spriteBatchNode;
}


void RandomParallaxBg::createOneTimeBg(GameLayer *gLayer, CCString *spriteName) {
     backgroundSpriteBatch = this->addBatchNodes(CCString::create(spriteName->getCString()));
}

void RandomParallaxBg::moveBg() {
    int speed = Utility::isIPad()? kInitGameSpeediPad : kInitGameSpeediPhone;
    checkAndMoveBatchNode(backgroundSpriteBatch, -speed);
}

void RandomParallaxBg:: checkAndMoveBatchNode(CCSpriteBatchNode *batchNode, float velocity) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *sprite = NULL;
    CCObject *obj = NULL;
    
    CCARRAY_FOREACH(batchNode->getChildren(), obj) {
        sprite = (CCSprite*)obj;
        float pos = sprite->getPositionX();
        pos +=  velocity;
        if (pos < -winSize.width) {
            pos += (winSize.width * 2) - 2;
        } else if (pos > winSize.width - 1) {
            pos -= (winSize.width * 2) - 2;
        }
        sprite->setPositionX(pos);
    }
}

void RandomParallaxBg::updateBodyPos() {
    b2Vec2 vect = b2Vec2(Utility::toMeters(CCPoint(spriteUserData->getSprite()->getPositionX(),spriteUserData->getSprite()->getPositionY())));
    body->SetTransform(vect, CC_DEGREES_TO_RADIANS(-spriteUserData->getSprite()->getRotation()));
}

