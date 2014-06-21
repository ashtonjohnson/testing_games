//
//  LevelCompletionScene.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 01/10/13.
//
//

#include "LevelCompletionScene.h"
#include "GameScene.h"

LevelCompletionScene* LevelCompletionScene::create() {
    LevelCompletionScene *pRet = new LevelCompletionScene;
    if (pRet && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool LevelCompletionScene::init() {
    if (!CCScene::init()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *bgSprite = CCSprite::create("game_bg_0.png");
    bgSprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    addChild(bgSprite);
    
    CCLabelTTF *label = CCLabelTTF::create("LevelCompleted", "Ariel", 55);
    label->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.8));
    addChild(label);
    
    CCSprite *playSprite = CCSprite::create("bird.png");
    
    CCLabelTTF *label1 = CCLabelTTF::create("Play", "Ariel", 50);
    CCMenuItemLabel *menuItemName = CCMenuItemLabel::create(label1, this, menu_selector(LevelCompletionScene::playGame));
    //    CCMenuItemSprite *menuItemName = CCMenuItemSprite::create(playSprite, playSprite, this,menu_selector(MainMenuScene::playGame));
    CCMenu *menuName = CCMenu::create(menuItemName, NULL);
    menuName->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    addChild(menuName, 1);
    
    return true;
}

void LevelCompletionScene::playGame() {
    CCDirector::sharedDirector()->replaceScene(GameScene::create(kSceneTypeGameScene));
}