//
//  LevelCompletionScene.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 01/10/13.
//
//

#include "MainMenuScene.h"
#include "MainMenuLayer.h"
#include "Utility.h"
#include "SoundConstant.h"
#include "NDKHelper.h"

using namespace cocos2d;

MainMenuScene* MainMenuScene::create() {
    MainMenuScene *pRet = new MainMenuScene;
    if (pRet && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool MainMenuScene::init() {
    if (!CCScene::init()) {
        return false;
    }       
    return true;
}

void MainMenuScene:: onEnter() {
    CCScene::onEnter();
    if (Utility::isAppStart) {
        runAction(CCSequence::createWithTwoActions(CCDelayTime::create(5), CCCallFunc::create(this, callfunc_selector(MainMenuScene::showChartBoost))));
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
    CCTextureCache::sharedTextureCache()->removeAllTextures();

    CCUserDefault::sharedUserDefault()->setBoolForKey(kBackgroundMusicKey, true);
    Utility::playOrPauseMusic(CCString::create(kBackgroundMusicFile));

    if (Utility::getAchievementStatus(1) == 0) {
        Utility::setAchievementStatus(1, 1);
        Utility::setAchievementStatus(2, 1);
        Utility::setAchievementStatus(3, 1);
    }
    
    Utility::addSpriteSheet("character");
    Utility::addSpriteSheet("bgTexture");
    Utility::addSpriteSheet("buttonTexture");
    MainMenuLayer *menuLayer = new MainMenuLayer;
    
    for (int i = 0; i <= 4; i++) {
        if (Utility::getBarsInUpgrades((PowerType) i) == 0) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForBarsInUpgrades, i)->getCString(), 1);
        }
    }
    CCUserDefault::sharedUserDefault()->flush();
    
    menuLayer->init();
    this->addChild(menuLayer,1);
    
    CC_SAFE_RELEASE(menuLayer);
    
    //code here
}

void MainMenuScene::showChartBoost() {
    if (!Utility::isAdFreeVersion()) {
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("YES"), kShowChartboostAd);
        SendMessageWithParams(string("shouldDisplayChartboostAd"), prms);
        Utility::isAppStart = false;
    }
}

void MainMenuScene:: onExit() {
    CCScene::onExit();
}
