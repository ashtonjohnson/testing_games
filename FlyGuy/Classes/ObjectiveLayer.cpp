//
//  ObjectiveLayer.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 23/10/13.
//
//

#include "ObjectiveLayer.h"
#include "MainMenuScene.h"
#include "Utility.h"
#include "FGScrollView.h"
#include "SoundConstant.h"

using namespace cocos2d;

ObjectiveLayer* ObjectiveLayer::create() {
    ObjectiveLayer *pRet = new ObjectiveLayer;
    if (pRet && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ObjectiveLayer::init() {
    if (!CCLayer::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    charMenuIemList = CCArray::create();
    
    fgScrollView = FGScrollView::create(kObjectiveStatus_Active);
    addChild(fgScrollView, 2);
    atLeastOneAchieved = false;
    CCSprite *colorLayerLeft = CCSprite::create("colorLayerLeft.png");
    colorLayerLeft->setPosition(ccp(winSize.width * 0.125, winSize.height * 0.5));
    addChild(colorLayerLeft);
    
    colorLayerRight = CCSprite::create("colorLayerRight.png");
    colorLayerRight->setPosition(ccp(winSize.width * 0.62, winSize.height * 0.5));
    addChild(colorLayerRight);
    
    //add button  active, all, completed
    addMenuItems("btnActive.png", 1);
    addMenuItems("btnAll.png", 2);
    addMenuItems("btnCompleted.png", 3);
    
    CCMenu *btnMenu = CCMenu::createWithArray(charMenuIemList);
    btnMenu->alignItemsVerticallyWithPadding(winSize.height * 0.1);
    btnMenu->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
    addChild(btnMenu, 2);
    
    //add back button    
    CCSprite *backBtnSprite = CCSprite::createWithSpriteFrameName("btnBack.png");
    CCMenuItemSprite *backMenuItem = CCMenuItemSprite::create(backBtnSprite, backBtnSprite, this, menu_selector(ObjectiveLayer::menuCallBack));
    backMenuItem->setTag(4);
    CCMenu *backBtnMenu = CCMenu::create(backMenuItem, NULL);
    backBtnMenu->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.08));
    addChild(backBtnMenu, 2);
        float scale = Utility::isIPad() ? 1 : 0.7;
    loadObjectiveAchieved();
    updateObjAchievedLayer();

    label = CCLabelBMFont::create(CCString::create("active")->getCString(), kFontChubby, 0);
    label->setPosition(CCPoint(winSize.width * 0.5, winSize.height * 0.93));
    label->setAnchorPoint(ccp(0, 0.5));
    label->setScale(scale * 1.5);
    addChild(label);
    
    return true;
}

// progress bar
void ObjectiveLayer::loadObjectiveAchieved() {
    objAchieved = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("bar_2.png"));
    if (objAchieved != NULL) {
        CCSprite *baseBar = CCSprite::createWithSpriteFrameName("bar_1.png");
        baseBar->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.9));
        addChild(baseBar);
        
        objAchieved->setType(kCCProgressTimerTypeBar);
        objAchieved->setMidpoint(ccp(0, 0));
        objAchieved->setBarChangeRate(ccp(1, 0));
        objAchieved->setPercentage(0);
//        objAchieved->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.9));
        objAchieved->setPosition(baseBar->getContentSize().width * 0.5, baseBar->getContentSize().height * 0.545);
        baseBar->addChild(objAchieved);
        
        //percentage label
        float scale = Utility::isIPad() ? 1 : 0.5;
        perLabel = CCLabelBMFont::create("0%", kFontChubby, 0);
        perLabel->setPosition(ccp(objAchieved->getContentSize().width * 0.5, objAchieved->getContentSize().height * 0.5));
        perLabel->setScale(scale);
        objAchieved-> addChild(perLabel);
        
        //add trophy sprite with progressbar
        CCSprite *trophyProgress = CCSprite::createWithSpriteFrameName("progressTrophy.png");
        trophyProgress->setPosition(ccp(-objAchieved->getContentSize().width * 0.2, objAchieved->getContentSize().height * 0.5));
        objAchieved->addChild(trophyProgress);
    }
}

void ObjectiveLayer::updateObjAchievedLayer() {
    float getTotalObjCleared = 0;
    float getClearObejct = 0;
    for (int i = 1; i <= kTotalObjectives; i++) {
        getClearObejct = Utility::getAchievementStatus(i);
        if (getClearObejct == 2) {
            getTotalObjCleared++;
        }
    }
    float getPercentage =  (getTotalObjCleared / kTotalObjectives)*100;
    objAchieved->setPercentage(getPercentage);
    perLabel->setString(CCString::createWithFormat("%d%%", (int)getPercentage)->getCString());
}

void ObjectiveLayer::addMenuItems(const char *frameName, int tag) {
    CCSprite *charSprite = CCSprite::createWithSpriteFrameName(frameName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(charSprite, charSprite, this, menu_selector(ObjectiveLayer::menuCallBack));
    menuItem->setTag(tag);
    charMenuIemList->addObject(menuItem);
}

void ObjectiveLayer::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    CCMenuItemSprite *sprite = ((CCMenuItemSprite*)(menuItem));
    int tag = sprite->getTag();
    switch (tag) {
        case 1:
            removeChild(fgScrollView, true);
            fgScrollView = FGScrollView::create(kObjectiveStatus_Active);
            addChild(fgScrollView, 2);
            label->setString("active");
            colorLayerRight->removeChild(notYetClearedLabel, true);
            break;
        case 2:
            removeChild(fgScrollView, true);
            fgScrollView = FGScrollView::create(kObjectiveStatus_All);
            addChild(fgScrollView, 2);
            label->setString("all");
            colorLayerRight->removeChild(notYetClearedLabel, true);
            break;

        case 3:        {
            removeChild(fgScrollView, true);
            fgScrollView = FGScrollView::create(kObjectiveStatus_Completed);
            addChild(fgScrollView, 2);
        float scale = Utility::isIPad() ? 1 : 0.6;
            for (int i = 1; i <= 41; i++) {
                //        int level = 40 - i;
                if (Utility::getAchievementStatus(i) == 2) {
                    atLeastOneAchieved = true;
                }
            }
            if (!atLeastOneAchieved) {
            colorLayerRight->removeChild(notYetClearedLabel, true);
                notYetClearedLabel = CCLabelBMFont::create("None yet, get to it", kFontChubby, 0);
                notYetClearedLabel->setScale(scale);
                notYetClearedLabel->setPosition(ccp(colorLayerRight->getContentSize().width * 0.25, colorLayerRight->getContentSize().height * 0.85));
                colorLayerRight->addChild(notYetClearedLabel, 25);
            }
            label->setString("completed");
        }
            break;
        case 4:
                    CCDirector::sharedDirector()->replaceScene(MainMenuScene::create());
            break;

            
        default:
            break;
    }
    
}
