//
//  UpgradeScene.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 29/10/13.
//
//

#include "UpgradeScene.h"
#include "UpgradeLayer.h"
#include "Utility.h"

UpgradeScene* UpgradeScene::create(ObjectiveStatus pObjectiveStatus) {
    UpgradeScene *pRet = new UpgradeScene;
    if (pRet && pRet->init(pObjectiveStatus)) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool UpgradeScene::init(ObjectiveStatus pObjectiveStatus) {
    if (!CCScene::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *bgSprite = CCSprite::create("bg.png");
    bgSprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    addChild(bgSprite);
    
    UpgradeLayer *upgradeLayer = new UpgradeLayer;
    upgradeLayer->init(pObjectiveStatus);
    this->addChild(upgradeLayer,1);
    CC_SAFE_RELEASE(upgradeLayer);
    
    return true;
}
