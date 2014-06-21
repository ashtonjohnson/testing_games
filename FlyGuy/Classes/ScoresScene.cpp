//
//  ScoresScene.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/11/13.
//
//

#include "ScoresScene.h"
#include "ScoresLayer.h"
#include "Utility.h"
#include "NDKHelper.h"

using namespace cocos2d;

ScoresScene* ScoresScene::create() {
    ScoresScene *pRet = new ScoresScene;
    if (pRet && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ScoresScene::init() {
    if (!CCScene::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *bgSprite = CCSprite::create("bg.png");
    bgSprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    addChild(bgSprite);
    ScoresLayer *scoreLayer = ScoresLayer::create();
    addChild(scoreLayer);
    
    return true;
}