//
//  ObjectiveScene.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 23/10/13.
//
//

#include "ObjectiveScene.h"
#include "ObjectiveLayer.h"

ObjectiveScene* ObjectiveScene::create() {
    ObjectiveScene *pRet = new ObjectiveScene;
    if (pRet && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ObjectiveScene::init() {
    if (!CCScene::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *bgSprite = CCSprite::create("bg.png");
    bgSprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    addChild(bgSprite);
    
    ObjectiveLayer *objectiveLayer = new ObjectiveLayer;
    objectiveLayer->init();
    this->addChild(objectiveLayer,1);
    CC_SAFE_RELEASE(objectiveLayer);
    
    return true;
}
