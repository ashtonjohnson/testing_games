//
//  HUDLayer.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 19/10/13.
//
//

#include "HUDLayer.h"
#include "GameLayer.h"
#include "Extras.h"
#include "Utility.h"
#include "PauseLayer.h"
#include "SoundConstant.h"

static int pauseLayerTag = 0;

HUDLayer* HUDLayer::create(GameLayer *glayer) {
	HUDLayer * pRet =new HUDLayer();
    if (pRet && pRet->init(glayer)) {
        pRet->autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

//void HUDLayer:: addTouchDelegate() {
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//}
//
//void HUDLayer:: removeTouchDelegate() {
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//}

bool HUDLayer:: init(GameLayer *glayer) {
    if (!CCLayer::init()) {
        return false;
    }
    gameLayer = glayer;
    winSize = CCDirector::sharedDirector()->getWinSize();
    charMenuIemList = new CCArray;
    
    if (gameLayer->sceneType == kSceneTypeGameScene) {
        getExtrasSpriteName(Utility::getSelectedExtrasPower());
        int len = std:: strlen(extraSpriteName);
        if (len != 0) {
            
            CCSprite *extrasSprite = CCSprite::createWithSpriteFrameName(extraSpriteName);
            CCMenuItemSprite *menuItemExtras = CCMenuItemSprite::create(extrasSprite, extrasSprite, this, menu_selector(HUDLayer::menuCallBack));
            menuItemExtras->setTag(Utility::getSelectedExtrasPower());
            CCMenu *menuExtras = CCMenu::create(menuItemExtras, NULL);
            menuExtras->setPosition(ccp(winSize.width * 0.05, winSize.height * 0.08));
            
            if (Utility::getSelectedExtrasPower() == kExtrasType_MysteryBox && Utility::getTotalMysteryBox() > 0) {
                addChild(menuExtras, 2, 8888);
            } else if (Utility::getSelectedExtrasPower() == kExtrasType_BrokenWallSpecial && Utility::getTotalBrokenWallSpecial() > 0) {
                addChild(menuExtras, 2, 8888);
            }else if (Utility::getSelectedExtrasPower() == kExtrasType_ExtraLifeSpecial && Utility::getTotalExtraLifeSpecial() > 0) {
                addChild(menuExtras, 2, 8888);
            }else if (Utility::getSelectedExtrasPower() == kExtrasType_WideLaneSpecial && Utility::getTotalWideLaneSpecial() > 0) {
                addChild(menuExtras, 2, 8888);
            }else if (Utility::getSelectedExtrasPower() == kExtrasType_RocketSpecial && Utility::getTotalRocketSpecial() > 0) {
                addChild(menuExtras, 2, 8888);
            }
            
            progressTimer = CCProgressTimer::create(extrasSprite);
            progressTimer->setColor(ccWHITE);
            progressTimer->setType(kCCProgressTimerTypeRadial);
            progressTimer->setMidpoint(ccp(0.5, 0.5));
            progressTimer->setBarChangeRate(ccp(1, 0));
            progressTimer->setPosition(ccp(winSize.width * 0.05, winSize.height * 0.08));
            progressTimer->setVisible(true);
            addChild(progressTimer, 2);
            
        }
    }
    
     
    
    CCMenu *charMenu = CCMenu::createWithArray(charMenuIemList);
    charMenu->alignItemsVerticallyWithPadding(winSize.width * 0.05);
    charMenu->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));

   
    
    
//add labels
    float scale = Utility::isIPad() ? 1 : 0.7;
    scoreLabel = CCLabelBMFont::create("score: 0", kFontChubby, 0);
    scoreLabel->setPosition(ccp(winSize.width* 0.01, winSize.height * 0.95));
    scoreLabel->setAnchorPoint(ccp(0, 0.5));
    scoreLabel->setScale(scale);
    addChild(scoreLabel); 


        //    add coin label
        coinLabelSprite = CCSprite::createWithSpriteFrameName("coins_0.png");
        coinLabelSprite->setPosition(ccp(-winSize.width* 0.05, winSize.height * 0.88));
        coinLabelSprite->setAnchorPoint(ccp(0, 0.5));
        addChild(coinLabelSprite);
        
        coinLabel = CCLabelBMFont::create("0", kFontChubby, 0);
        coinLabel->setPosition(ccp(winSize.width* 0.07, winSize.height * 0.88));
        coinLabel->setAnchorPoint(ccp(0, 0.5));
        coinLabel->setScale(scale);
        addChild(coinLabel);
    
    //total stars we have to show
    CCSprite *starSprite = CCSprite::createWithSpriteFrameName("coinsStars_4.png");
    starSprite->setPosition(CCPoint(winSize.width * 0.06, winSize.height * 0.79));
    starSprite->setAnchorPoint(ccp(1, 0.5));
    starSprite->setScale(0.5);
    addChild(starSprite);
    
    starLabel = CCLabelBMFont::create(CCString::createWithFormat("%d", Utility::getTotalStars())->getCString(), kFontChubby, 0);
    starLabel->setPosition(CCPoint(winSize.width * 0.07, winSize.height * 0.8));
    starLabel->setAnchorPoint(ccp(0, 0.5));
    starLabel->setScale(scale);
    addChild(starLabel);


    if (gameLayer->sceneType == kSceneTypeHelp) {
        coinLabelSprite->setVisible(false);
        coinLabel->setVisible(false);
    }
    
    //    adding pause button
    CCSprite *pauseBtnSprite = CCSprite::createWithSpriteFrameName("btnPause.png");
    CCMenuItemSprite *pauseMenuItem = CCMenuItemSprite::create(pauseBtnSprite, pauseBtnSprite, this, menu_selector(HUDLayer::menuCallBack));
    pauseMenuItem->setTag(5);
    pauseBtnMenu = CCMenu::create(pauseMenuItem, NULL);
    pauseBtnMenu->setPosition(ccp(winSize.width * 0.95, winSize.height * 0.07));
    addChild(pauseBtnMenu, 2);
        if (gameLayer->sceneType == kSceneTypeHelp) {
            pauseBtnMenu->setEnabled(false);
        }
    
    
    return true;
}

void HUDLayer::addMenuItems(const char *frameName, int tag) {
    CCSprite *charSprite = CCSprite::create(frameName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(charSprite, charSprite, this, menu_selector(HUDLayer::menuCallBack));
    menuItem->setTag(tag);
    charMenuIemList->addObject(menuItem);
}

void HUDLayer::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    CCMenuItemSprite *sprite = ((CCMenuItemSprite*)(menuItem));
    int tag = sprite->getTag();
    CCLOG("tag is %d", tag);
    switch (tag) {
        case 5:
            CCLOG("pause button pressed");
            pauseScreen();
            break;
            
        case 500:
            CCLOG("mystery"); {
            gameLayer->extras->initWithExtras(gameLayer, kExtrasType_MysteryBox);
                Utility::setTotalMysteryBox(Utility::getTotalMysteryBox() - 1);
                removeChildByTag(8888);
        }
            break;
        case 501:
            CCLOG("kExtrasType_RocketSpecial"); {
            gameLayer->extras->initWithExtras(gameLayer, kExtrasType_RocketSpecial);
                Utility::setTotalRocketSpecial(Utility::getTotalRocketSpecial() - 1);
                removeChildByTag(8888);

        }

            break;
        case 502:
            CCLOG("kExtrasType_ExtraLifeSpecial"); {
            gameLayer->extras->initWithExtras(gameLayer, kExtrasType_ExtraLifeSpecial);
                Utility::setTotalExtraLifeSpecial(Utility::getTotalExtraLifeSpecial() - 1);
                removeChildByTag(8888);

        }

            break;
        case 503:
            CCLOG("kExtrasType_BrokenWallSpecial"); {
            gameLayer->extras->initWithExtras(gameLayer, kExtrasType_BrokenWallSpecial);
                Utility::setTotalBrokenWallSpecial(Utility::getTotalBrokenWallSpecial() - 1);
                removeChildByTag(8888);

        }

            break;
        case 504:
            CCLOG("kExtrasType_WideLaneSpecial"); {
            gameLayer-> extras->initWithExtras(gameLayer, kExtrasType_WideLaneSpecial);
                Utility::setTotalWideLaneSpecial(Utility::getTotalWideLaneSpecial() - 1);
                removeChildByTag(8888);

        }
            
            
            
            
            break;
    }
}

void HUDLayer::updateScore(int score) {
    scoreLabel->setString(CCString::createWithFormat("score: %d", score)->getCString());
}

void HUDLayer::updateCoinScore(int coinScore) {
    coinLabel->setString(CCString::createWithFormat("%d", coinScore)->getCString());
}

void HUDLayer::pauseScreen() {
    PauseLayer *pauseLayer = PauseLayer::create(gameLayer);
    removeChildByTag(pauseLayerTag, true);
    addChild(pauseLayer, 2, ++pauseLayerTag);
    pauseBtnMenu->setVisible(false);
    CCDirector::sharedDirector()->pause();
}

void HUDLayer::getExtrasSpriteName(ExtrasType extrasType) {
    extraSpriteName = "";
    switch (extrasType) {
        case kExtrasType_MysteryBox:
            extraSpriteName = "iconMysteryBox.png";
            break;
        case kExtrasType_BrokenWallSpecial:
            extraSpriteName = "iconWallBreak.png";
            break;
        case kExtrasType_ExtraLifeSpecial:
            extraSpriteName = "iconExtraLife.png";
            break;
        case kExtrasType_RocketSpecial:
            extraSpriteName = "iconSuperRocket.png";
            break;
        case kExtrasType_WideLaneSpecial:
            extraSpriteName = "iconWideLane.png";
            break;
            
        default:
            break;
    }
}

void HUDLayer::onExit() {
    charMenuIemList->removeAllObjects();
    CC_SAFE_RELEASE(charMenuIemList);
    removeAllChildrenWithCleanup(true);
    CCLayer::onExit();
}