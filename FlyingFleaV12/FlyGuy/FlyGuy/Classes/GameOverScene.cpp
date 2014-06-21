//
//  GameOverScene.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 28/10/13.
//
//

#include "GameOverScene.h"
#include "GameOverLayer.h"
#include "Constant.h"
#include "Utility.h"

GameOverScene* GameOverScene::create() {
	GameOverScene * pRet =new GameOverScene();
    if (pRet && pRet->init()) {
        pRet->autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}
bool GameOverScene:: init() {
    if (!CCScene::init()) {
        return false;
    }
    timer = 10;
    winSize = CCDirector::sharedDirector()->getWinSize();
//    GameOverLayer *gameOverLayer = GameOverLayer::create(game);
//    addChild(gameOverLayer);
    
    return true;
}

