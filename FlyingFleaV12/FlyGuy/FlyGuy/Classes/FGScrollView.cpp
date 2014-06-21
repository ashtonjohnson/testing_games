//
//  FGScrollView.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 30/10/13.
//
//

#include "FGScrollView.h"
#include "Utility.h"
#include "NDKHelper.h"
#include "SoundConstant.h"
#include "UpgradeScene.h"
#include "FlurryConstant.h"

#define kScrollBarGap 0.21

#define kNumberOfPowerUps 5
#define kNumberOfExtras   9
#define kNumberOfAch      40

using namespace cocos2d::extension;

FGScrollView* FGScrollView::create(ObjectiveStatus pObjectiveStatus) {
	FGScrollView * pRet =new FGScrollView();
    if (pRet && pRet->init(pObjectiveStatus)) {
        pRet->autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}

bool FGScrollView:: init(ObjectiveStatus pObjectiveStatus) {
    if (!CCLayer::init()) {
        return false;
    }
    objStatus = pObjectiveStatus;
    winSize = CCDirector::sharedDirector()->getWinSize();
    noOfLevels = 0;
    totalActives = 0;
    totalCompleted = 0;
    switch (objStatus) {
        case kObjectiveStatus_Active:
            noOfLevels = 3;
            break;
        case kObjectiveStatus_Completed:
        {            int levels = 0;
            for (int i = 1; i <= kNumberOfAch; i++) {
                if (Utility::getAchievementStatus(i) == 2) {
                    levels++;
                }
            }
            noOfLevels = levels;
        }
            break;
        case kObjectiveStatus_All:
            noOfLevels = kNumberOfAch;
            break;
        case kObjectiveStatus_Powerups:
            noOfLevels = kNumberOfPowerUps;
            break;
        case kObjectiveStatus_Extras:
            noOfLevels = kNumberOfExtras;
            break;
        case kObjectiveStatus_CoinStars:
            noOfLevels = 9;
            break;
            
        default:
            break;
    }
    
    deltaScrollBarGap = Utility::isIPad() ? 0 : 0;
    scrollView = CCScrollView::create();
    scrollView->setViewSize(CCSizeMake(winSize.width * 0.74, winSize.height * 0.628)); //a
    scrollView->setContentSize(ccp(winSize.width, winSize.height * (kScrollBarGap+deltaScrollBarGap) * noOfLevels/*number of elements*/)); //a+b
    scrollView->setPosition(ccp(winSize.width * 0.26, winSize.height * 0.18));
    scrollView->setContentOffset(ccp(0.0, -(winSize.height * (kScrollBarGap+deltaScrollBarGap) * noOfLevels/*number of elements */ -  winSize.height*0.628) )); // b
    scrollView->setDirection(kCCScrollViewDirectionVertical);
    scrollView->setVisible(true);
    addChild(scrollView);
    //scrollView->retain();
    addObjectives();
    return true;
}


void FGScrollView::addObjectives() {
    switch (objStatus) {
        case kObjectiveStatus_Active:
            loadObjectivesForActive();
            break;
        case kObjectiveStatus_Completed:
            loadObjectivesForCompleted();
            break;
        case kObjectiveStatus_All:
            loadObjectivesForAll();
            break;
        case kObjectiveStatus_Powerups:
            loadObjectivesForPowerups();
            break;
        case kObjectiveStatus_Extras:
            loadObjectivesForExtras();
            break;
        case kObjectiveStatus_CoinStars:
            loadObjectivesForCoinStars();
            break;
        default:
            break;
    }
    
    
}

void FGScrollView::loadObjectivesForActive() {
    int j = 0;
    noOfLevels = kNumberOfAch+1;
    if (arrayForActive == NULL) {
        arrayForActive = CCArray::create();
    }
    for (int i = 1; i <= (kNumberOfAch+1); i++) {
        if (Utility::getAchievementStatus(i) == 1) {
            arrayForActive->addObject(CCString::createWithFormat("%d", i));
            j++;         
            if (j == 3) {
                break;
            }
        }
    }
    
    CCObject *obj;
    int i = arrayForActive->count()-1;
    CCARRAY_FOREACH(arrayForActive, obj) {
        
        CCSprite *objective = CCSprite::createWithSpriteFrameName(kScrollBar);
        objective->setPositionY(winSize.height * kScrollBarGap * i--);
        
        CCString *string = (CCString*)obj;
        int level = string->intValue();
        CCString *obj_1 = (CCString*) Utility::objectiveDict()->valueForKey(CCString::createWithFormat("kAchievement_%d_0", level)->getCString());
        CCString *obj_2 = (CCString*) Utility::objectiveDict()->valueForKey(CCString::createWithFormat("kAchievement_%d_1", level)->getCString());
        createLabel(obj_1->getCString(), obj_2->getCString(), ccp(objective->getContentSize().width * 0.18, objective->getContentSize().height * 0.85), objective);
        createSprite("iconTrophy.png", ccp(objective->getContentSize().width * 0.03, objective->getContentSize().height * 0.85), objective);
        scrollView->addChild(objective, 2);
    }
}

void FGScrollView::loadObjectivesForCompleted() {
    int var = 0;
    
    if (arrayForCompleted == NULL) {
        arrayForCompleted = CCArray::create();
    }else{
        arrayForCompleted->removeAllObjects();
        arrayForCompleted->release();
        arrayForCompleted = NULL;
        arrayForCompleted = CCArray::create();
    }
    for (int i = 1; i <= kNumberOfAch; i++) {
        if (Utility::getAchievementStatus(i) == 2) {
            arrayForCompleted->insertObject(CCString::createWithFormat("%d", i), var);
            var++;
        }
    }
    for (int j = 0; j < arrayForCompleted->count(); j++) {
        CCSprite *objective = CCSprite::createWithSpriteFrameName(kScrollBar);
        objective->setPositionY(winSize.height * kScrollBarGap * j);

        CCString *string = (CCString*)arrayForCompleted->objectAtIndex(j);
        int level = string->intValue();
        
        CCString *obj_1 = (CCString*) Utility::objectiveDict()->valueForKey(CCString::createWithFormat("kAchievement_%d_0", level)->getCString());
        CCString *obj_2 = (CCString*) Utility::objectiveDict()->valueForKey(CCString::createWithFormat("kAchievement_%d_1", level)->getCString());
        createLabel(obj_1->getCString(), obj_2->getCString(), ccp(objective->getContentSize().width * 0.18, objective->getContentSize().height * 0.75), objective);
        createSprite("iconTrophyTick.png", ccp(objective->getContentSize().width * 0.03, objective->getContentSize().height * 0.85), objective);
        createSprite("iconTick.png", ccp(objective->getContentSize().width * 0.8, objective->getContentSize().height * 0.85), objective);
        scrollView->addChild(objective, 2);
    }
}

void FGScrollView::loadObjectivesForAll() {
    noOfLevels = kNumberOfAch + 1;
    for (int i = 0; i < noOfLevels-1; i++) {
        CCSprite *objective = CCSprite::createWithSpriteFrameName(kScrollBar);
        objective->setPositionY(winSize.height * kScrollBarGap * i);
        CCString *obj_1 = (CCString*) Utility::objectiveDict()->valueForKey(CCString::createWithFormat("kAchievement_%d_0", noOfLevels-1-i)->getCString());
        CCString *obj_2 = (CCString*) Utility::objectiveDict()->valueForKey(CCString::createWithFormat("kAchievement_%d_1", noOfLevels-1-i)->getCString());
       
        int getStatus = (noOfLevels-1)-i;
        
        if (Utility::getAchievementStatus(getStatus) == 2) {
            createSprite("iconTrophyTick.png", ccp(objective->getContentSize().width * 0.03, objective->getContentSize().height * 0.85), objective);
            createSprite("iconTick.png", ccp(objective->getContentSize().width * 0.8, objective->getContentSize().height * 0.85), objective);
        } else if(Utility::getAchievementStatus(getStatus) == 1){
            createSprite("iconTrophy.png", ccp(objective->getContentSize().width * 0.03, objective->getContentSize().height * 0.85), objective);
        } else {
            obj_2 = CCString::createWithFormat("-locked-");
            createSprite("btnLocked.png", ccp(objective->getContentSize().width * 0.03, objective->getContentSize().height * 0.85), objective);
        }
         createLabel(obj_1->getCString(), obj_2->getCString(), ccp(objective->getContentSize().width * 0.18, objective->getContentSize().height * 0.85), objective);
        scrollView->addChild(objective);
    }
    
}

void FGScrollView::loadObjectivesForPowerups() {
    int flag = 0;
    CCSprite *barSprite;
    if (labelPowerUpsArray == NULL) {
        labelPowerUpsArray = new CCArray;
    }
    if (objectivePowerUpArray == NULL) {
        objectivePowerUpArray = new CCArray;
    }
    float gap = Utility::isIPad() ? 0.0265 : 0.0335;
    for (int i = 0; i < noOfLevels; i++) {
        
        CCSprite *objective = CCSprite::createWithSpriteFrameName(kScrollBar);
        objective->setPositionY(winSize.height * (kScrollBarGap+deltaScrollBarGap) * i);
        objective->setTag(i);
        CCDictionary *dict = (CCDictionary*)Utility::powerupDict()->objectForKey(CCString::createWithFormat("pow_%d",noOfLevels - 1 - i)->getCString());
        
        for (int j = 1; j < dict->count()+1; j++) {
            CCString *element = (CCString*)dict->valueForKey(CCString::createWithFormat("string_%d", j)->getCString());
            const char *getValue =  element->getCString();
            if (j == 1) {
                createSprite(getValue, ccp(objective->getContentSize().width * 0.01, objective->getContentSize().height * 0.85), objective);
            } else if (j == 2) {
                createLabel(getValue, "", ccp(objective->getContentSize().width * 0.16, objective->getContentSize().height * 0.95), objective);                
            } else if (j > 2) {
//                CCLog("getvalue is %s i=%d j=%d", getValue, i, j);
                if ((i == 1 || i == 4) && (j == 3)) {
                    int bars = Utility::getBarsInUpgrades((PowerType)(noOfLevels -1 - i));
//                    CCLog("element string %s", element->getCString());
                    getValue = CCString::createWithFormat("%dx %s", bars, getValue)->getCString();
                }else if (i == 0 && j == 3) {
                    int bars = Utility::getBarsInUpgrades((PowerType)(noOfLevels -1 - i));
//                CCLog("getvalue is %s i=%d j=%d bars %d", getValue, i, j, bars);
                    switch (bars) {
                        case 2:
                            getValue = "Enable the red coins (worth 3x)";
                            break;
                        case 3:
                            getValue = "Enable the blue coins (worth 4x)";
                            break;
                        case 4:
                            getValue = "Fully upgraded (worth 4x)";
                            break;
                            
                        default:
                            break;
                    }
                }
                
                createLabel("", getValue, ccp(objective->getContentSize().width * 0.16, objective->getContentSize().height * 1.5 - j*winSize.height * gap), objective);//0.0265
            }
        }
        
        // adding small bars for powerups
        CCString *element = (CCString*)dict->valueForKey(CCString::createWithFormat("string_%d", 2)->getCString());
        const char *getValue =  element->getCString();
        
         int upgradeLevels = std:: strcmp(getValue, "Coins") ? 5 : 4;
        
        for (int k = 0; k < upgradeLevels; k++) {
            barSprite = CCSprite::createWithSpriteFrameName("iconBarBlank.png");
            barSprite->setAnchorPoint(ccp(0, 1));
            barSprite->setPosition(ccp(objective->getContentSize().width * 0.15 + k *winSize.width * 0.0735, objective->getContentSize().height * 0.24));
            objective->addChild(barSprite, 2);
        }
        
        // adding filled bars for power ups
        int noOfFilledBars = Utility::getBarsInUpgrades((PowerType)(noOfLevels - 1 - i));
//        CCLog("noOfFilledBars %d", noOfFilledBars);
        int score = Utility::getNoOfScoresAsPerBar(noOfFilledBars);
        if (noOfLevels - 1 - i == 4) { // coins layer
            score += 2 * (noOfFilledBars) * 1000;
        }
             
        for (int k = 0; k < noOfFilledBars; k++) {
            barSprite = CCSprite::createWithSpriteFrameName("iconBarFilled.png");
            barSprite->setAnchorPoint(ccp(0, 1));
            barSprite->setPosition(ccp(objective->getContentSize().width * 0.15 + k *winSize.width * 0.0735, objective->getContentSize().height * 0.24));
            objective->addChild(barSprite, 2);
        }
//        CCLog("no of levels is %d", i);
        // adding upgrade button on each layer
        if (noOfFilledBars != 5) {
                CCSprite *sprite = CCSprite::createWithSpriteFrameName("coins_0.png");
                sprite->setPosition(ccp(objective->getContentSize().width * 0.65, objective->getContentSize().height * 0.3));
                sprite->setAnchorPoint(ccp(0, 0));
                objective->addChild(sprite,22, 9090+i);
                
                float scale = Utility::isIPad() ? 1 : 0.6;
                CCLabelBMFont *labelPowerUp = CCLabelBMFont::create(CCString::createWithFormat("%d", score)->getCString(), kFontChubby, 0);
                labelPowerUp->setPosition(objective->getContentSize().width * 0.83, objective->getContentSize().height * 0.66);
                labelPowerUp->setScale(scale);
                labelPowerUp->setAnchorPoint(ccp(0, 0));
            
            if (labelPowerUpsArray->count() == 0) {
                flag = 0;
            }
                labelPowerUpsArray->insertObject(labelPowerUp, flag++);
                objective-> addChild(labelPowerUp, 10, 8080 + i);
            createButton("btnUpgrade.png", i, ccp(objective->getContentSize().width * 0.855, objective->getContentSize().height * 0.30), objective);
        }
        
        if (i == 0 && noOfFilledBars == 4) {
            objective->removeChildByTag(i, true);
            objective->removeChildByTag(9090 + i, true);
            objective->removeChildByTag(8080 + i, true);
        }
        scrollView->addChild(objective, 24,i);
        objectivePowerUpArray->insertObject(objective, i);
    }
}

void FGScrollView::loadObjectivesForExtras() {
    if (labelExtrasArray == NULL) {
        labelExtrasArray = new CCArray;
    }
    if (allToggleButtons != NULL) {
        allToggleButtons->removeAllObjects();
        allToggleButtons = NULL;
    }
        allToggleButtons = new CCArray;

        float gap = Utility::isIPad() ? 0.0265 : 0.0335;
    for (int i = 0; i < noOfLevels; i++) {
        
        CCSprite *objective = CCSprite::createWithSpriteFrameName(kScrollBar);
        objective->setPositionY(winSize.height * (kScrollBarGap+deltaScrollBarGap) * i);
        
        CCDictionary *dict = (CCDictionary*)Utility::extrasDict()->objectForKey(CCString::createWithFormat("extras_%d",noOfLevels - 1 - i)->getCString());
        
        for (int j = 1; j < dict->count()+1; j++) {
            CCString *element = (CCString*)dict->valueForKey(CCString::createWithFormat("string_%d", j)->getCString());
            const char *getValue =  element->getCString();

            if (j == 1) {
                createSprite(getValue, ccp(objective->getContentSize().width * 0.03, objective->getContentSize().height * 0.85), objective);
            } else if (j == 2) {
                createLabel(getValue, "", ccp(objective->getContentSize().width * 0.2, objective->getContentSize().height * 0.95), objective);
                
            } else if (j > 2) {
                createLabel("", getValue, ccp(objective->getContentSize().width * 0.2, objective->getContentSize().height * 1.5 - j*winSize.height * gap), objective);
            }
        }
        
        int score = Utility::getNoOfScoresAsPerExtras(noOfLevels - 1 - i);
            CCSprite *sprite = CCSprite::createWithSpriteFrameName("coins_0.png");
            sprite->setPosition(ccp(objective->getContentSize().width * 0.65, objective->getContentSize().height * 0.3));
            sprite->setAnchorPoint(ccp(0, 0));
            objective->addChild(sprite,22);
            float scale = Utility::isIPad() ? 1 : 0.6;
            CCLabelBMFont *labelExtras = CCLabelBMFont::create(CCString::createWithFormat("%d", score)->getCString(), kFontChubby, 0);
            labelExtras->setPosition(objective->getContentSize().width * 0.83, objective->getContentSize().height * 0.68);
            labelExtras->setScale(scale);
            labelExtras->setAnchorPoint(ccp(0, 0));
            objective-> addChild(labelExtras, 10);
            labelExtrasArray->insertObject(labelExtras, i);
      
        if (score == 0) {
            objective-> removeChild(sprite, true);
            labelExtras->setString("");
            CCSprite *sprite = CCSprite::createWithSpriteFrameName("iconTick.png");
            sprite->setPosition(ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.3));
            sprite->setAnchorPoint(ccp(0, 0));
            objective->addChild(sprite,22);
        }

        if(noOfLevels - 1 - i > 5){
            if (noOfLevels - 1 - i == 6 && Utility::getCharacterLockUnlockStatus(kCharacterType_JohnyOrange) == 1) {
                objective-> removeChild(sprite, true);
                labelExtras->setString("");
                CCSprite *sprite = CCSprite::createWithSpriteFrameName("iconTick.png");
                sprite->setPosition(ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.3));
                sprite->setAnchorPoint(ccp(0, 0));
                objective->addChild(sprite,22);
            }else if(noOfLevels - 1 - i == 8 && Utility::getCharacterLockUnlockStatus(kCharacterType_VinnyGreen) == 1) {
                objective-> removeChild(sprite, true);
                labelExtras->setString("");
                CCSprite *sprite = CCSprite::createWithSpriteFrameName("iconTick.png");
                sprite->setPosition(ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.3));
                sprite->setAnchorPoint(ccp(0, 0));
                objective->addChild(sprite,22);
            }else if(noOfLevels - 1 - i == 7 && Utility::getCharacterLockUnlockStatus(kCharacterType_BellaRed) == 1) {
                objective-> removeChild(sprite, true);
                labelExtras->setString("");
                CCSprite *sprite = CCSprite::createWithSpriteFrameName("iconTick.png");
                sprite->setPosition(ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.3));
                sprite->setAnchorPoint(ccp(0, 0));
                objective->addChild(sprite,22);
            }
            
        }
        if (noOfLevels - 1 - i < 5) {
            createButton("btnBuy3.png", i, ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.30), objective);
            
            extrasToggleOn = CCSprite::createWithSpriteFrameName("btnExtrasPlus.png");
            menuItemExtrasToggleOn = CCMenuItemSprite::create(extrasToggleOn, extrasToggleOn, this, menu_selector(FGScrollView::extrasToggleButtonTapped));
            
            extrasToggleOff = CCSprite::createWithSpriteFrameName("btnExtrasMinus.png");
            menuItemExtrasToggleOff = CCMenuItemSprite::create(extrasToggleOff, extrasToggleOff, this, menu_selector(FGScrollView::extrasToggleButtonTapped));
            
            CCMenuItemToggle *toggleSound = CCMenuItemToggle::createWithTarget(this, menu_selector(FGScrollView::extrasToggleButtonTapped), menuItemExtrasToggleOn, menuItemExtrasToggleOff, NULL);
            toggleSound->setTag(i-4);
            CCString *element = (CCString*)dict->valueForKey(CCString::createWithFormat("string_%d", 1)->getCString());
            const char *getValue =  element->getCString();
            toggleSound->setVisible(false);
            if (Utility::getTotalWideLaneSpecial() > 0 && std::strcmp(getValue, "iconWideLane.png") == 0) {
                toggleSound->setVisible(true);
            } else if (Utility::getTotalBrokenWallSpecial() > 0 && std::strcmp(getValue, "iconWallBreak.png") == 0) {
                toggleSound->setVisible(true);
            }else if (Utility::getTotalExtraLifeSpecial() > 0 && std::strcmp(getValue, "iconExtraLife.png") == 0) {
                toggleSound->setVisible(true);
            }else if (Utility::getTotalRocketSpecial() > 0 && std::strcmp(getValue, "iconSuperRocket.png") == 0) {
                toggleSound->setVisible(true);
            }else if (Utility::getTotalMysteryBox() > 0 && std::strcmp(getValue, "iconMysteryBox.png") == 0) {
                toggleSound->setVisible(true);
            }
            menuExtrasToggleOff = CCMenu::create(toggleSound , NULL);
            menuExtrasToggleOff->setPosition(ccp(objective->getContentSize().width * 0.15, objective->getContentSize().height * 0.19));
            objective->addChild(menuExtrasToggleOff, 2);
            allToggleButtons->addObject((CCObject*)toggleSound);
        }
        
        if(noOfLevels - 1 - i > 5){
            if (noOfLevels - 1 - i == 6 && Utility::getCharacterLockUnlockStatus(kCharacterType_JohnyOrange) == 0) {
            createButton("btnUnlock.png", i, ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.30), objective);
            }else if(noOfLevels - 1 - i == 8 && Utility::getCharacterLockUnlockStatus(kCharacterType_VinnyGreen) == 0) {
            createButton("btnUnlock.png", i, ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.30), objective);
            }else if(noOfLevels - 1 - i == 7 && Utility::getCharacterLockUnlockStatus(kCharacterType_BellaRed) == 0) {
            createButton("btnUnlock.png", i, ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.30), objective);
            }

        }
        scrollView->addChild(objective, 24);
           }
}

void FGScrollView::loadObjectivesForCoinStars() {
    int count = 0;
    for (int i = 0; i < noOfLevels; i++) {
        CCSprite *objective = CCSprite::createWithSpriteFrameName(kScrollBar);
        objective->setPositionY(winSize.height * (kScrollBarGap+deltaScrollBarGap) * i);
        
        CCDictionary *dict = (CCDictionary*)Utility::coinsStarsDict()->objectForKey(CCString::createWithFormat("coinsStars_%d",noOfLevels - 1 - i)->getCString());
        for (int j = 1; j < dict->count()+1; j++) {
            CCString *element = (CCString*)dict->valueForKey(CCString::createWithFormat("string_%d", j)->getCString());
            const char *getValue =  element->getCString();
            if (j == 1) {
                createSprite(getValue, ccp(objective->getContentSize().width * 0.05, objective->getContentSize().height * 0.75), objective);
            } else if (j == 2) {
                createLabel(getValue, "", ccp(objective->getContentSize().width * 0.23, objective->getContentSize().height * 0.70), objective);
                
            } else if (j > 2) {
                createLabel( getValue, "", ccp(objective->getContentSize().width * 0.57, objective->getContentSize().height * 0.70), objective);
            }
        }
        CCLOG("unlock all chars %d", (noOfLevels - 1 - i));
//        createButton("btnBuy.png", i, ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.55), objective);

        CCSprite *sprite = CCSprite::createWithSpriteFrameName("btnBuy.png");
        sprite->setAnchorPoint(ccp(0, 1));
        CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(FGScrollView::menuCallBack));
        menuItem->setTag(i);
        CCMenu *menu = CCMenu::create(menuItem, NULL);
        menu->setTag(i + 1000);
        menu->setPosition(ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.55));
        objective->addChild(menu, 2);
        
        if ((noOfLevels - 1 - i) == 8) {
            
            for (int i = 0; i < 4; i++) {
                if (CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("%s%d", kKeyForCharacterLockUnlock, i)->getCString()) == 1) {
                    count++;
                    if (count == 4) {
                        Utility::setUnlockAllCharacter();
                    }
                }
            }
            if (Utility::isUnlockAllCharacter()) {
                objective->removeChildByTag(i + 1000 );
                createSprite("iconTick.png", ccp(objective->getContentSize().width * 0.8, objective->getContentSize().height * 0.85), objective);
            }
        }
        
        scrollView->addChild(objective, 24);
    }
}

void  FGScrollView::extrasToggleButtonTapped(CCObject *sender) {
    CCMenuItemToggle *toggleItem = (CCMenuItemToggle*)sender;
    if (toggleItem->getTag() == 4) {
        Utility::setSelectedExtrasPower(kExtrasType_MysteryBox);
    } else if (toggleItem ->getTag() == 3) {
        Utility::setSelectedExtrasPower(kExtrasType_RocketSpecial);
    } else if (toggleItem ->getTag() == 2) {
        Utility::setSelectedExtrasPower(kExtrasType_ExtraLifeSpecial);
    } else if (toggleItem ->getTag() == 1) {
        Utility::setSelectedExtrasPower(kExtrasType_BrokenWallSpecial);
    } else if (toggleItem ->getTag() == 0) {
        Utility::setSelectedExtrasPower(kExtrasType_WideLaneSpecial);
    }
    CCDictionary *dict = (CCDictionary*)Utility::extrasDict()->objectForKey(CCString::createWithFormat("extras_%d",4-toggleItem->getTag())->getCString());
    
    CCString *element = (CCString*)dict->valueForKey(CCString::createWithFormat("string_%d", 1)->getCString());
    const char *getValue =  element->getCString();
    
    CCSprite *extrasSprite = CCSprite::createWithSpriteFrameName(getValue);
    if (extrasSprite != NULL) {
        removeChildByTag(2121);
    }
    //        removeChildByTag(2121);
    extrasSprite->setPosition(ccp(winSize.width * 0.75, winSize.height * 0.93));
    extrasSprite->runAction(CCSequence::createWithTwoActions(CCMoveBy::create(0.1, ccp(0, -winSize.height * 0.01)), CCMoveBy::create(0.1, ccp(0, winSize.height * 0.01))));
    addChild(extrasSprite, 2, 2121);
    CCObject *obj;
    CCMenuItemToggle *toggle;
    CCARRAY_FOREACH(allToggleButtons, obj) {
        toggle = (CCMenuItemToggle*)obj;
        toggle->setSelectedIndex(0);
    }
    if (toggleItem->getSelectedIndex() == 0) {
        toggleItem->setSelectedIndex(1);
    }
}

void FGScrollView::createSprite(const char *spriteFrameName, CCPoint pos, CCSprite *objective) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteFrameName);
    sprite->setPosition(pos);
    sprite->setAnchorPoint(ccp(0, 1));
    objective->addChild(sprite,22);
}

void FGScrollView::createLabel(const char *labelName, const char *labelNameValue, CCPoint position, CCSprite *objective) {
    float scale = Utility::isIPad() ? 0.9 : 0.45;
    float val = 0.0f;
    if (std::strcmp(labelName, "Unlock all characters") == 0) {
        val = 0.2;
    }else {
        val = 0.3f;
    }
    label = CCLabelBMFont::create(labelName, kFontChubby, winSize.width * val);
    label->setPosition(position);
    label->setScale(scale);
    label->setAnchorPoint(ccp(0, 1));
    objective-> addChild(label, 10);
    labelText = CCLabelBMFont::create(labelNameValue, kFontChubby, winSize.width * 0.35);
//    labelText->
    labelText->setPosition(ccp(label->getPositionX(), label->getPositionY() - winSize.height * 0.078 ));
    labelText->setScale(scale * 0.65);
    labelText->setAnchorPoint(ccp(0, 1));
    objective->addChild(labelText, 10);
}

void FGScrollView::createButton(const char *spriteName, int tag, CCPoint posititon, CCSprite *objective) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteName);
    sprite->setAnchorPoint(ccp(0, 1));
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(FGScrollView::menuCallBack));
    menuItem->setTag(tag);
    CCMenu *menu = CCMenu::create(menuItem, NULL);
    menu->setTag(tag);
    menu->setPosition(posititon);
    objective->addChild(menu, 2);
}

void FGScrollView::resetUpgradeLabel(int calculatedLevel, int upgradeLevel) {
    CCLog("object at index %d", calculatedLevel);
    
    CCLabelBMFont *labelString = (CCLabelBMFont*)labelPowerUpsArray->objectAtIndex(calculatedLevel);
    int getBar = Utility::getBarsInUpgrades((PowerType)upgradeLevel);
        Utility::setBarsInUpgrades((PowerType)upgradeLevel, ++getBar);
        labelString->setString(CCString::createWithFormat("%d", Utility::getNoOfScoresAsPerBar(getBar))->getCString());
}

void FGScrollView::resetUpgradeBars(CCSprite *objective, int upgradeLevel) {
    CCSprite *barSprite;
    for (int k = 0; k < Utility::getBarsInUpgrades((PowerType)upgradeLevel); k++) {
        barSprite = CCSprite::createWithSpriteFrameName("iconBarFilled.png");
        barSprite->setAnchorPoint(ccp(0, 1));
        barSprite->setPosition(ccp(objective->getContentSize().width * 0.15 + k *winSize.width * 0.0735, objective->getContentSize().height * 0.24));
        objective->addChild(barSprite, 2);
    }
}

void FGScrollView::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    CCMenuItemSprite *sprite = ((CCMenuItemSprite*)(menuItem));
    int tag = sprite->getTag();
    int totalCoins = Utility::getTotalCoins();
    int upgradeLevel = noOfLevels - 1 - tag;
    int needCoins = 0;
    if (objStatus == kObjectiveStatus_Extras) {
        needCoins = Utility::getNoOfScoresAsPerExtras(upgradeLevel);
    } else if (objStatus == kObjectiveStatus_Powerups) {
        int noOfFilledBars = Utility::getBarsInUpgrades((PowerType)(noOfLevels - 1 - tag));
        needCoins = Utility:: getNoOfScoresAsPerBar(noOfFilledBars);
    }
    CCLOG("total coins %d, need coins %d", totalCoins, needCoins);
    
    CCDictionary* prms = CCDictionary::create();
    prms->setObject(CCString::create("Not enough coins!"), "title");
    prms->setObject(CCString::create("Get more coins now?"), "message");
    prms->setObject(CCString::create("Yes"), "button0");
    prms->setObject(CCString::create("No"), "button2");
    prms->setObject(CCString::create("upgradeScreen"), "callFromScreen");
    
    int calculatedLevel = noOfLevels - upgradeLevel -1;
    switch (upgradeLevel) {
        case 0:
            if (objStatus != kObjectiveStatus_CoinStars) {
                if (totalCoins < needCoins) {
                    SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
                    CCLOG("total mystery box %d", Utility::getTotalMysteryBox());
                    if (Utility::getTotalMysteryBox() != 0) {
                        setToggleVisible(4, true);
                    }else {
                        setToggleVisible(4, false);
                    }
                } else {
                    if (objStatus ==  kObjectiveStatus_Extras) {
                        int resetCoins = totalCoins - needCoins;
                        Utility::setTotalCoins(resetCoins);
                        CCLog("mystery box");
                        Utility::setSelectedExtrasPower(kExtrasType_MysteryBox);
                        Utility::setTotalMysteryBox(3 + Utility::getTotalMysteryBox());
                        CCLOG("total mystery box11 %d", Utility::getTotalMysteryBox());
                        setToggleVisible(4, true);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Extras));
                        
                        CCDictionary* prms = CCDictionary::create();
                        prms->setObject(CCString::create(kFlurryExtrasMysteryBox), "FLURRY_EVENT");
                        SendMessageWithParams(string("sendFlurryReport"), prms);
                    } else if (objStatus == kObjectiveStatus_Powerups && Utility::getBarsInUpgrades(kPowerUpType_SpeedBurst) != 5) {
                        int resetCoins = totalCoins - needCoins;
                        Utility::setTotalCoins(resetCoins);
                        CCLOG("speed burst");
                        resetUpgradeLabel(labelPowerUpsArray->count()-1, upgradeLevel);
                        resetUpgradeBars((CCSprite*)objectivePowerUpArray->objectAtIndex(calculatedLevel), upgradeLevel);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Powerups));
                        
                        CCDictionary* prms = CCDictionary::create();
                        prms->setObject(CCString::create(kFlurryPowerupJetPack), "FLURRY_EVENT");
                        SendMessageWithParams(string("sendFlurryReport"), prms);
                    }
                }
            } else {
                CCLOG("5000 coins");
                CCDictionary* prms = CCDictionary::create();
                prms->setObject(CCString::create("PURCHASE 5000 COINS"), "PURCHASE_ITEM");
                SendMessageWithParams(string("sendFlurryReport"), prms);
                SendMessageWithParams(string("startPuchaseFlow"), prms);
            }
            break;
            
        case 1:
            if (objStatus != kObjectiveStatus_CoinStars) {
                if (totalCoins < needCoins) {
                    SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
                    if (Utility::getTotalRocketSpecial() > 0) {
                        setToggleVisible(3, true);
                    }else {
                        setToggleVisible(3, false);
                    }
                } else {
                    if (objStatus == kObjectiveStatus_Extras) {
                        int resetCoins = totalCoins - needCoins;
                        Utility::setTotalCoins(resetCoins);
                        Utility::setTotalRocketSpecial(3 + Utility::getTotalRocketSpecial());
                        Utility::setSelectedExtrasPower(kExtrasType_RocketSpecial);
                        setToggleVisible(3, true);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Extras));
                        
                        CCDictionary* prms = CCDictionary::create();
                        prms->setObject(CCString::create(kFlurryExtrasJetPackSpecial), "FLURRY_EVENT");
                        SendMessageWithParams(string("sendFlurryReport"), prms);
                    } else if (objStatus == kObjectiveStatus_Powerups && Utility::getBarsInUpgrades(kPowerUpType_SuperRocket) != 5) {
                        int resetCoins = totalCoins - needCoins;
                        Utility::setTotalCoins(resetCoins);
                        CCLOG("super rocket");
                        resetUpgradeLabel(labelPowerUpsArray->count()-1, upgradeLevel);
                        resetUpgradeBars((CCSprite*)objectivePowerUpArray->objectAtIndex(calculatedLevel), upgradeLevel);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Powerups));
                        
                        CCDictionary* prms = CCDictionary::create();
                        prms->setObject(CCString::create(kFlurryPowerupJetPack), "FLURRY_EVENT");
                        SendMessageWithParams(string("sendFlurryReport"), prms);
                    }
                }
            }else {
                CCLOG("25000 coins");
                CCDictionary* prms = CCDictionary::create();
                prms->setObject(CCString::create("PURCHASE 25000 COINS"), "PURCHASE_ITEM");
                SendMessageWithParams(string("sendFlurryReport"), prms);
                SendMessageWithParams(string("startPuchaseFlow"), prms);
            }
            break;
            
        case 2:
            if (objStatus != kObjectiveStatus_CoinStars) {
                if (totalCoins < needCoins) {
                    SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
                    if (Utility::getTotalExtraLifeSpecial() > 0) {
                        setToggleVisible(2, true);
                    }else {
                        setToggleVisible(2, false);
                    }
                } else {
                    if (objStatus == kObjectiveStatus_Extras) {
                        int resetCoins = totalCoins - needCoins;
                        Utility::setTotalCoins(resetCoins);
                        Utility::setTotalExtraLifeSpecial(3 + Utility::getTotalExtraLifeSpecial());
                        Utility::setSelectedExtrasPower(kExtrasType_ExtraLifeSpecial);
                        setToggleVisible(2, true);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Extras));
                        
                        CCDictionary* prms = CCDictionary::create();
                        prms->setObject(CCString::create(kFlurryExtrasInvincible), "FLURRY_EVENT");
                        SendMessageWithParams(string("sendFlurryReport"), prms);
                    } else if (objStatus == kObjectiveStatus_Powerups && Utility::getBarsInUpgrades(kPowerUpType_BubbleShield) != 5) {
                        int resetCoins = totalCoins - needCoins;
                        Utility::setTotalCoins(resetCoins);
                        CCLOG("bubble shield");
                        resetUpgradeLabel(labelPowerUpsArray->count()-1, upgradeLevel);
                        resetUpgradeBars((CCSprite*)objectivePowerUpArray->objectAtIndex(calculatedLevel), upgradeLevel);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Powerups));
                        
                        CCDictionary* prms = CCDictionary::create();
                        prms->setObject(CCString::create(kFlurryPowerupShield), "FLURRY_EVENT");
                        SendMessageWithParams(string("sendFlurryReport"), prms);
                    }                }
            }else {
                CCLOG("75000 coins");
                CCDictionary* prms = CCDictionary::create();
                prms->setObject(CCString::create("PURCHASE 75000 COINS"), "PURCHASE_ITEM");
                SendMessageWithParams(string("sendFlurryReport"), prms);
                SendMessageWithParams(string("startPuchaseFlow"), prms);
            }
            
            break;
            
        case 3:
            if (objStatus != kObjectiveStatus_CoinStars) {
                if (totalCoins < needCoins) {
                    SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
                    if (Utility::getTotalBrokenWallSpecial() > 0) {
                        setToggleVisible(1, true);
                    }else {
                        setToggleVisible(1, false);
                    }
                } else {
                    if (objStatus == kObjectiveStatus_Extras) {
                        int resetCoins = totalCoins - needCoins;
                        Utility::setTotalCoins(resetCoins);
                        Utility::setTotalBrokenWallSpecial(3 + Utility::getTotalBrokenWallSpecial());
                        Utility::setSelectedExtrasPower(kExtrasType_BrokenWallSpecial);
                        setToggleVisible(1, true);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Extras));
                        CCDictionary* prms = CCDictionary::create();
                        prms->setObject(CCString::create(kFlurryExtrasBrokenWallSpecial), "FLURRY_EVENT");
                        SendMessageWithParams(string("sendFlurryReport"), prms);
                    } else if (objStatus == kObjectiveStatus_Powerups && Utility::getBarsInUpgrades(kPowerUpType_TinyMode) != 5) {
                        int resetCoins = totalCoins - needCoins;
                        Utility::setTotalCoins(resetCoins);
                        CCLOG("tiny mode");
                        resetUpgradeLabel(labelPowerUpsArray->count()-1, upgradeLevel);
                        resetUpgradeBars((CCSprite*)objectivePowerUpArray->objectAtIndex(calculatedLevel), upgradeLevel);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Powerups));
                        
                        CCDictionary* prms = CCDictionary::create();
                        prms->setObject(CCString::create(kFlurryPowerupShrinkMode), "FLURRY_EVENT");
                        SendMessageWithParams(string("sendFlurryReport"), prms);
                    }
                }
            }else {
                CCLOG("300000 coins");
                CCDictionary* prms = CCDictionary::create();
                prms->setObject(CCString::create("PURCHASE 300000 COINS"), "PURCHASE_ITEM");
                SendMessageWithParams(string("sendFlurryReport"), prms);
                SendMessageWithParams(string("startPuchaseFlow"), prms);
            }
            break;
            
        case 4:
            if (objStatus != kObjectiveStatus_CoinStars) {
                if (totalCoins < needCoins) {
                    SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
                    if (Utility::getTotalWideLaneSpecial() > 0) {
                        setToggleVisible(0, true);
                    }else {
                        setToggleVisible(0, false);
                    }
                } else {
                    if (objStatus == kObjectiveStatus_Extras) {
                        int resetCoins = totalCoins - needCoins;
                        Utility::setTotalCoins(resetCoins);
                        Utility::setTotalWideLaneSpecial(3 + Utility::getTotalWideLaneSpecial());
                        Utility::setSelectedExtrasPower(kExtrasType_WideLaneSpecial);
                        setToggleVisible(0, true);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Extras));
                        
                        CCDictionary* prms = CCDictionary::create();
                        prms->setObject(CCString::create(kFlurryExtrasWideCaveSpecial), "FLURRY_EVENT");
                        SendMessageWithParams(string("sendFlurryReport"), prms);
                        
                        CCLOG("wide lane special");
                    } else if (objStatus == kObjectiveStatus_Powerups && Utility::getBarsInUpgrades(kPowerUpType_Coins) != 4) {
                        int noOfFilledBars = Utility::getBarsInUpgrades(kPowerUpType_Coins);
                        int score =  Utility::getNoOfScoresAsPerBar(noOfFilledBars);
                        score += 2 * (noOfFilledBars) * 1000;
                        int resetCoins = totalCoins - score;
                        Utility::setTotalCoins(resetCoins);
                        CCLOG("coins");
                        resetUpgradeLabel(labelPowerUpsArray->count()-1, upgradeLevel);
                        resetUpgradeBars((CCSprite*)objectivePowerUpArray->objectAtIndex(calculatedLevel), upgradeLevel);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Powerups));
                        
                        CCDictionary* prms = CCDictionary::create();
                        prms->setObject(CCString::create(kFlurryPowerupCoins), "FLURRY_EVENT");
                        SendMessageWithParams(string("sendFlurryReport"), prms);
                    }
                }
                
            }else {
                CCLOG("5 stars");
                CCDictionary* prms = CCDictionary::create();
                prms->setObject(CCString::create("PURCHASE 5 STARS"), "PURCHASE_ITEM");
                SendMessageWithParams(string("sendFlurryReport"), prms);
                SendMessageWithParams(string("startPuchaseFlow"), prms);
            }
            break;
            
        case 5:
            if (objStatus != kObjectiveStatus_CoinStars) {
                CCLOG("55");
                if (totalCoins < needCoins) {
                    SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
                } else {
                    int resetCoins = totalCoins - needCoins;
                    Utility::setTotalCoins(resetCoins);
                    if (objStatus == kObjectiveStatus_Extras) {
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Extras));
                    }
                }
                
            }else {
                CCLOG("50 stars");
                prms->setObject(CCString::create("PURCHASE 50 STARS"), "PURCHASE_ITEM");
                SendMessageWithParams(string("sendFlurryReport"), prms);
                SendMessageWithParams(string("startPuchaseFlow"), prms);
            }
            break;
            
        case 6:
            if (objStatus != kObjectiveStatus_CoinStars) {
                if (totalCoins < needCoins) {
                    SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
                } else {
                    int resetCoins = totalCoins - needCoins;
                    Utility::setTotalCoins(resetCoins);
                    if (objStatus == kObjectiveStatus_Extras) {
                        Utility::setCharacterLockUnlockStatus(kCharacterType_JohnyOrange, 1);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Extras));
                    }
                }
                
            }else {
                CCLOG("200 stars");
                prms->setObject(CCString::create("PURCHASE 200 STARS"), "PURCHASE_ITEM");
                SendMessageWithParams(string("sendFlurryReport"), prms);
                SendMessageWithParams(string("startPuchaseFlow"), prms);
            }
            break;
            
        case 7:
            if (objStatus != kObjectiveStatus_CoinStars) {
                if (totalCoins < needCoins) {
                    SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
                } else {
                    int resetCoins = totalCoins - needCoins;
                    Utility::setTotalCoins(resetCoins);
                    if (objStatus == kObjectiveStatus_Extras) {
                        Utility::setCharacterLockUnlockStatus(kCharacterType_BellaRed, 1);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Extras));
                    }
                }
            }else {
                CCLOG("500 stars");
                prms->setObject(CCString::create("PURCHASE 500 STARS"), "PURCHASE_ITEM");
                SendMessageWithParams(string("sendFlurryReport"), prms);
                SendMessageWithParams(string("startPuchaseFlow"), prms);
            }
            break;
            
        case 8:
            if (objStatus != kObjectiveStatus_CoinStars) {
                if (totalCoins < needCoins) {
                    SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
                } else {
                    int resetCoins = totalCoins - needCoins;
                    Utility::setTotalCoins(resetCoins);
                    if (objStatus == kObjectiveStatus_Extras) {
                        Utility::setCharacterLockUnlockStatus(kCharacterType_VinnyGreen, 1);
                        CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Extras));
                    }
                }
            }else {
                if (Utility::isUnlockAllCharacter()) {
                    CCLOG("already purchased");
                }else {
                    CCLOG("unlock all characters");
                    prms->setObject(CCString::create("UNLOCK ALL CHARACTERS"), "PURCHASE_ITEM");
                    SendMessageWithParams(string("sendFlurryReport"), prms);
                    SendMessageWithParams(string("startPuchaseFlow"), prms);
                }
            }
            break;
    }
}

void FGScrollView::setToggleVisible(int tag, bool visibility) {
    CCObject *obj;
    CCMenu *toggle;
    CCARRAY_FOREACH(allToggleButtons, obj) {
        toggle = (CCMenu*)obj;
        CCLOG("toggle tag is %d", toggle->getTag());
        if (toggle->getTag() == tag) {
            toggle->setVisible(visibility);
        }
    }
}

void FGScrollView::updateCoinsCount(CCNode *sender, void *data){
    CCDictionary *dict = (CCDictionary*)data;
    CCObject *key = dict->objectForKey("COINS_ID");
    int coinsToAdd = 0;
    if(key->isEqual(CCString::create(kBuy5000Coins))){
        coinsToAdd = Utility::getValueAsPerPurchase(0);
    }else if (key->isEqual(CCString::create(kBuy25000Coins))){
        coinsToAdd = Utility::getValueAsPerPurchase(1);
    }else if (key->isEqual(CCString::create(kBuy75000Coins))){
        coinsToAdd = Utility::getValueAsPerPurchase(2);
    }else if (key->isEqual(CCString::create(kBuy300000Coins))){
        coinsToAdd = Utility::getValueAsPerPurchase(3);
    }
    CCLOG("now coins %d", coinsToAdd);
    
    Utility::setTotalCoins(coinsToAdd + Utility::getTotalCoins());
    CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_CoinStars));
}

void FGScrollView::unlockAllChars(CCNode *sender, void *data){
    Utility::setUnlockAllCharacter();
}
void FGScrollView::updateStarsCount(CCNode *sender, void *data){
    CCDictionary *dict = (CCDictionary*)data;
    CCObject *key = dict->objectForKey("STARS_ID");
    int starsToAdd = 0;
    if(key->isEqual(CCString::create(kBuy5Stars))){
        starsToAdd = Utility::getValueAsPerPurchase(4);
    }else if (key->isEqual(CCString::create(kBuy50Stars))){
        starsToAdd = Utility::getValueAsPerPurchase(5);
    }else if (key->isEqual(CCString::create(kBuy200Stars))){
        starsToAdd = Utility::getValueAsPerPurchase(6);
    }else if (key->isEqual(CCString::create(kBuy500Stars))){
        starsToAdd = Utility::getValueAsPerPurchase(7);
    }
    Utility::setTotalStars(starsToAdd + Utility::getTotalStars());
    CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_CoinStars));
}

void FGScrollView::onEnter() {
        CCLayer::onEnter();
        NDKHelper::AddSelector("StoreSceneSelectors", "updateCoinsCount", callfuncND_selector(FGScrollView::updateCoinsCount), this);
            NDKHelper::AddSelector("StoreSceneSelectors", "unlockAllChars", callfuncND_selector(FGScrollView::unlockAllChars), this);
 NDKHelper::AddSelector("StoreSceneSelectors", "updateStarsCount", callfuncND_selector(FGScrollView::updateStarsCount), this);
}

void FGScrollView::onExit() {
NDKHelper::RemoveSelectorsInGroup("StoreSceneSelectors");
        CCLayer::onExit();
}

