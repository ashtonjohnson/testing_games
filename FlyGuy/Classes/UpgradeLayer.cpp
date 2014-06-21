//
//  UpgradeLayer.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 29/10/13.
//
//

#include "UpgradeLayer.h"
#include "Utility.h"
#include "MainMenuScene.h"
#include "NDKHelper.h"
#include "SoundConstant.h"
#include "FGScrollView.h"
#include "UpgradeScene.h"

using namespace cocos2d;

UpgradeLayer* UpgradeLayer::create(ObjectiveStatus pObjectiveStatus) {
    UpgradeLayer *pRet = new UpgradeLayer;
    if (pRet && pRet->init(pObjectiveStatus)) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool UpgradeLayer::init(ObjectiveStatus pObjectiveStatus) {
    if (!CCLayer::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    charMenuIemList = CCArray::create();
    float scale = Utility::isIPad() ? 1 : 0.7;
    
    headLabel = CCLabelBMFont::create(CCString::create("power ups")->getCString(), kFontChubby, 0);
    headLabel->setPosition(CCPoint(winSize.width * 0.5, winSize.height * 0.95));
    headLabel->setAnchorPoint(ccp(0, 0.5));
    headLabel->setScale(scale * 1.5);
    addChild(headLabel);
    
    CCSprite *colorLayerLeft = CCSprite::create("colorLayerLeft.png");
    colorLayerLeft->setPosition(ccp(winSize.width * 0.125, winSize.height * 0.5));
    addChild(colorLayerLeft);
    
    CCSprite *colorLayerRight = CCSprite::create("colorLayerRight.png");
    colorLayerRight->setPosition(ccp(winSize.width * 0.62, winSize.height * 0.5));
    addChild(colorLayerRight);
    
   // createLabel(CCString::createWithFormat("%d", Utility::getTotalCoins())->getCString(), CCPoint(winSize.width * 0.08, winSize.height * 0.9));
    CCSprite *coinSprite = CCSprite::createWithSpriteFrameName("coins_0.png");
    coinSprite->setPosition(CCPoint(winSize.width * 0.13, winSize.height * 0.95));
    coinSprite->setAnchorPoint(ccp(1, 0.5));
    addChild(coinSprite);
    
    coinLabel = CCLabelBMFont::create(CCString::createWithFormat("%d", Utility::getTotalCoins())->getCString(), kFontChubby, 0);
    coinLabel->setPosition(CCPoint(winSize.width * 0.08, winSize.height * 0.96));
    coinLabel->setAnchorPoint(ccp(0, 0.5));
    coinLabel->setScale(scale);
    addChild(coinLabel);
    
    //total stars we have to show
    CCSprite *starSprite = CCSprite::createWithSpriteFrameName("coinsStars_4.png");
    starSprite->setPosition(CCPoint(winSize.width * 0.07, winSize.height * 0.85));
    starSprite->setAnchorPoint(ccp(1, 0.5));
    starSprite->setScale(0.5);
    addChild(starSprite, 2);
    
    starLabel = CCLabelBMFont::create(CCString::createWithFormat("%d", Utility::getTotalStars())->getCString(), kFontChubby, 0);
    starLabel->setPosition(CCPoint(winSize.width * 0.08, winSize.height * 0.86));
    starLabel->setAnchorPoint(ccp(0, 0.5));
    starLabel->setScale(scale);
    addChild(starLabel);
    
    //add button  active, all, completed
    addMenuItems("btnPowerUp.png", 1);
    addMenuItems("btnExtra.png", 2);
    addMenuItems("btnCoins.png", 3);
    if (!Utility::isAdFreeVersion()) {
        addMenuItems("btnRemoveAds.png", 6);   
    }
    
    CCMenu *btnMenu = CCMenu::createWithArray(charMenuIemList);
    btnMenu->alignItemsVerticallyWithPadding(winSize.height * 0.03);
    btnMenu->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
    addChild(btnMenu, 2);
    
    //add back button
    CCSprite *backBtnSprite = CCSprite::createWithSpriteFrameName("btnBack.png");
    CCMenuItemSprite *backMenuItem = CCMenuItemSprite::create(backBtnSprite, backBtnSprite, this, menu_selector(UpgradeLayer::menuCallBack));
    backMenuItem->setTag(4);
    CCMenu *backBtnMenu = CCMenu::create(backMenuItem, NULL);
    backBtnMenu->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.08));
    addChild(backBtnMenu, 2);
    
    //add restore purchases button
    CCSprite *restoreBtnSprite = CCSprite::createWithSpriteFrameName("btnRestorePurchases.png");
    CCMenuItemSprite *restoreMenuItem = CCMenuItemSprite::create(restoreBtnSprite, restoreBtnSprite, this, menu_selector(UpgradeLayer::menuCallBack));
    restoreMenuItem->setTag(5);
    CCMenu *restoreBtnMenu = CCMenu::create(restoreMenuItem, NULL);
    restoreBtnMenu->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.08));
    addChild(restoreBtnMenu, 2);
    
    if (pObjectiveStatus == kObjectiveStatus_Extras) {
        headLabel->setString("extras");
    } else if (pObjectiveStatus == kObjectiveStatus_Powerups) {
        headLabel->setString("power ups");
    }

    fgScrollView = FGScrollView::create(pObjectiveStatus);
    addChild(fgScrollView, 2);
    return true;
}

void UpgradeLayer::createLabel(const char *labelName, CCPoint position) {
    float scale = Utility::isIPad() ? 1 : 0.7;
    label = CCLabelBMFont::create(labelName, kFontChubby, 0);
    label->setPosition(position);
    label->setAnchorPoint(ccp(0, 0.5));
    label->setScale(scale * 2);
    addChild(label);
}

void UpgradeLayer::addMenuItems(const char *frameName, int tag) {
    CCSprite *charSprite = CCSprite::createWithSpriteFrameName(frameName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(charSprite, charSprite, this, menu_selector(UpgradeLayer::menuCallBack));
    menuItem->setTag(tag);
    charMenuIemList->addObject(menuItem);
    
    if (std:: strcmp(frameName, "btnPowerUp.png") == 0 && Utility::storePushPopPowerUps() > 0){
        CCSprite *numberSprite = CCSprite::createWithSpriteFrameName("iconNumber.png");
        numberSprite->setPosition(ccp(charSprite->getContentSize().width * 0.05, charSprite->getContentSize().height * 0.98));
        charSprite->addChild(numberSprite, 2);
        
        int totalPushPops = Utility::storePushPopPowerUps();
        
        const char *pushPops = CCString::createWithFormat("%d", totalPushPops)->getCString();
        float scale = Utility::isIPad() ? 1 : 0.5;
        CCLabelBMFont *numberLabel = CCLabelBMFont::create(pushPops, kFontChubby, 0);
        numberLabel->setScale(scale); //0.5
        numberLabel->setPosition(ccp(numberSprite->getContentSize().width * 0.54, numberSprite->getContentSize().height * 0.55));
        numberSprite->addChild(numberLabel, 2);
        numberSprite->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleTo::create(0.5, 0.9), CCScaleTo::create(0.5, 1))));
    }
    
    if (std:: strcmp(frameName, "btnExtra.png") == 0 && Utility::storePushPopExtras() > 0){
        CCSprite *numberSprite = CCSprite::createWithSpriteFrameName("iconNumber.png");
        numberSprite->setPosition(ccp(charSprite->getContentSize().width * 0.05, charSprite->getContentSize().height * 0.98));
        charSprite->addChild(numberSprite, 2);
        
        int totalPushPops = Utility::storePushPopExtras();
        
        const char *pushPops = CCString::createWithFormat("%d", totalPushPops)->getCString();
        float scale = Utility::isIPad() ? 1 : 0.5;
        CCLabelBMFont *numberLabel = CCLabelBMFont::create(pushPops, kFontChubby, 0);
        numberLabel->setScale(scale); //0.5
        numberLabel->setPosition(ccp(numberSprite->getContentSize().width * 0.54, numberSprite->getContentSize().height * 0.55));
        numberSprite->addChild(numberLabel, 2);
        numberSprite->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleTo::create(0.5, 0.9), CCScaleTo::create(0.5, 1))));
    }
}

void UpgradeLayer::removeAdsListener(CCNode *sender, void *data){
    Utility::setAdFreeVersion();
    CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Powerups));
//    menuRemoveAds->setVisible(false);
//    this->removeChild(menuRemoveAds);
}
void UpgradeLayer::replaceSceneAfterUnlock(CCNode *sender, void *data){
    Utility::setUnlockAllCharacter();
    CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_CoinStars));
    //    menuRemoveAds->setVisible(false);
    //    this->removeChild(menuRemoveAds);
}

void UpgradeLayer::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    CCMenuItemSprite *sprite = ((CCMenuItemSprite*)(menuItem));
    int tag = sprite->getTag();
    switch (tag) {
        case 1:
            headLabel->setString("power ups");
            removeChild(fgScrollView, true);
            fgScrollView = FGScrollView::create(kObjectiveStatus_Powerups);
            addChild(fgScrollView, 2);
            break;
        case 2:
            headLabel->setString("extras");
            removeChild(fgScrollView, true);
            fgScrollView = FGScrollView::create(kObjectiveStatus_Extras);
            addChild(fgScrollView, 2);
            break;
            
        case 3:
            headLabel->setString("coins + stars");
            removeChild(fgScrollView, true);
            fgScrollView = FGScrollView::create(kObjectiveStatus_CoinStars);
            addChild(fgScrollView, 2);
            break;
            
        case 4:
                CCDirector::sharedDirector()->replaceScene(MainMenuScene::create());
                break;
            
        case 5:
                CCLOG("restore purchases");
                SendMessageWithParams(string("restorePurchase"), NULL);
                break;
        case 6:{
                CCLOG("REMOVE ADS");
            if (Utility::isAdFreeVersion()) {
                CCLOG("already purchased");
            }else {
                CCDictionary* prms = CCDictionary::create();
                prms->setObject(CCString::create("REMOVE_ADS"), "PURCHASE_ITEM");
                SendMessageWithParams(string("startPuchaseFlow"), prms);
                SendMessageWithParams(string("sendFlurryReport"), prms);
            }
        }
            break;
            
        default:
            break;
    }
    
}

void UpgradeLayer::goToUpgradeScreenWithCoinsStars(CCNode *sender, void *data){
    removeChild(fgScrollView, true);
    fgScrollView = FGScrollView::create(kObjectiveStatus_CoinStars);
    addChild(fgScrollView, 2);
}

void UpgradeLayer::restorePurchases() {
    CCDirector::sharedDirector()->replaceScene(UpgradeScene::create((kObjectiveStatus_Powerups)));
}

void UpgradeLayer::onEnter(){
    CCLayer::onEnter();
    NDKHelper::AddSelector("getCoinsSelector", "goToUpgradeScreenWithCoinsStars", callfuncND_selector(UpgradeLayer::goToUpgradeScreenWithCoinsStars), this);
    NDKHelper::AddSelector("getCoinsSelector", "removeAdsListener", callfuncND_selector(UpgradeLayer::removeAdsListener),                         this);
     NDKHelper::AddSelector("getCoinsSelector", "replaceSceneAfterUnlock", callfuncND_selector(UpgradeLayer::replaceSceneAfterUnlock), this);
     NDKHelper::AddSelector("getCoinsSelector", "restorePurchases", callfuncND_selector(UpgradeLayer::restorePurchases), this);
}

void UpgradeLayer::onExit(){
    CCLayer::onExit();
    this->removeAllChildrenWithCleanup(true);
    NDKHelper::RemoveSelectorsInGroup("getCoinsSelector");
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LevelSelectionScene.plist");
}


