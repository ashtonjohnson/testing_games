//
//  GameScene.cpp
//  Fly Guy
//
//  Created by Upkesh Thakur on 10/09/13.
//
//

#include "GameScene.h"
#include "GameLayer.h"
#include "Utility.h"
#include "HUDLayer.h"
#include "Constant.h"
#include "SoundConstant.h"

GameScene* GameScene::create(SceneType sceneType) {
    GameScene *pRet = new GameScene;
    
    if (pRet && pRet->init(sceneType)) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool GameScene::init(SceneType pSceneType) {
    if (!CCScene::init()) {
        return false;
    }
    sceneType = pSceneType;

    //code here
    return true;
}

void GameScene::onEnter() {
    CCScene::onEnter();
    if (Utility::isIPad()) {
        Utility::addSpriteSheet("parallax_bg_grassDown");
        Utility::addSpriteSheet("parallax_bg_grassUp");
        Utility::addSpriteSheet("parallax_bg_withoutGrassDown");
        Utility::addSpriteSheet("parallax_bg_withoutGrassUp");
        //        Utility::addSpriteSheet("parallax_bg");
        //        Utility::addSpriteSheet("buttonTexture");
    } else {
        Utility::addSpriteSheet("parallax_bg");
        //        Utility::addSpriteSheet("buttonTexture");
    }
    
    FNTConfigLoadFile( kFontChubby );
    FNTConfigLoadFile( kFontMarkerFelt );
    //    Utility::addSpriteSheet("buttonTexture");
    
    GameLayer *gLayer = GameLayer::create(sceneType);
    this->addChild(gLayer);
    
    HUDLayer *hudLayer = HUDLayer::create(gLayer);
    addChild(hudLayer, 10);
    gLayer->setHUDLayer(hudLayer);

}

void GameScene::onExit() {
    //code here
    this->removeAllChildrenWithCleanup(true);
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
//    CCTextureCache::sharedTextureCache()->removeAllTextures();
    CCScene::onExit();
}