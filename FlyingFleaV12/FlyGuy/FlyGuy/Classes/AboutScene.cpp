//
//  AboutScene.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 25/10/13.
//
//

#include "AboutScene.h"
#include "AboutLayer.h"
#include "Utility.h"
#include "NDKHelper.h"

using namespace cocos2d;

AboutScene* AboutScene::create() {
    AboutScene *pRet = new AboutScene;
    if (pRet && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool AboutScene::init() {
    if (!CCScene::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *bgSprite = CCSprite::create("bg.png");
    bgSprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    addChild(bgSprite);
    AboutLayer *aboutLayer = AboutLayer::create();
    addChild(aboutLayer);
    return true;
}