//
//  PauseLayer.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 28/10/13.
//
//

#include "PauseLayer.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "HUDLayer.h"
#include "Utility.h"
#include "GameLayer.h"
#include "SoundConstant.h"

#define kScrollBarGap 0.23

PauseLayer* PauseLayer::create(GameLayer *gameLayer) {
	PauseLayer * pRet =new PauseLayer();
    if (pRet && pRet->init(gameLayer)) {
        pRet->autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}
bool PauseLayer:: init(GameLayer *gameLayer) {
    if (!CCLayer::init()) {
        return false;
    }
    float scale = Utility::isIPad() ? 1 : 0.5;
    gLayer = gameLayer;
    charMenuIemList = new CCArray;
//    Utility::addSpriteSheet("buttonTexture");
    isCallFromRecords = true;
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor *colorLayer = CCLayerColor::create(ccc4(50, 50, 50, 100), winSize.width  , winSize.height );
    addChild(colorLayer);
    
    if (gameLayer->sceneType == kSceneTypeGameScene) {
        addMenuItems("btnNewGame.png", 1);   
    }
    addMenuItems("btnMenu.png", 2);
    
    CCMenu *btnMenu = CCMenu::createWithArray(charMenuIemList);
    btnMenu->alignItemsHorizontallyWithPadding(winSize.width * 0.05);
    btnMenu->setPosition(ccp(winSize.width * 0.2, winSize.height * 0.1));
    addChild(btnMenu, 2);

    CCSprite *iconStar = CCSprite::createWithSpriteFrameName("coinsStars_4.png");
    iconStar->setScale(0.8);
    iconStar->setPosition(ccp(winSize.width * 0.05, winSize.height * 0.92));
    addChild(iconStar, 2);
    
    const char *totalStars = CCString::createWithFormat("%d", Utility::getTotalStars())->getCString();
    CCLabelBMFont *starsLabel = CCLabelBMFont::create(totalStars, kFontChubby, 0);
    starsLabel->setPosition(ccp(iconStar->getPositionX() + winSize.width * 0.05, winSize.height * 0.92));
    starsLabel->setScale(scale);
    addChild(starsLabel, 2);
    
    addObjectiveLayer();
    hideHUDButtons();
    //add resume button

    createButton("btnResume.png", 3, ccp(winSize.width * 0.9, winSize.height * 0.1));
//    createButton("btnSound.png", 4, ccp(winSize.width * 0.95,winSize.height * 0.92));
    return true;
}

void PauseLayer::hideHUDButtons() {
    gLayer->hudLayer->scoreLabel->setVisible(false);
    gLayer->hudLayer->pauseBtnMenu->setVisible(false);
    gLayer->hudLayer->coinLabel->setVisible(false);
    gLayer->hudLayer->coinLabelSprite->setVisible(false);    
}

void PauseLayer::showHUDButtons() {
    gLayer->hudLayer->scoreLabel->setVisible(true);
    gLayer->hudLayer->pauseBtnMenu->setVisible(true);
    gLayer->hudLayer->coinLabel->setVisible(true);
    gLayer->hudLayer->coinLabelSprite->setVisible(true);
    
}

void PauseLayer::addObjectiveLayer() {
    objectiveLayer = CCLayer::create();
    objectiveLayer->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    float scale = Utility::isIPad() ? 1 : 0.8;
    CCLabelBMFont *labelObj = CCLabelBMFont::create("objectives", kFontChubby, 0);
    labelObj->setPosition(ccp(winSize.width * 0, winSize.height * 0.45));
    labelObj->setScale(scale);
    objectiveLayer->addChild(labelObj, 2);
    
    createButton("btnStats.png", 5, ccp(winSize.width * 0.3, winSize.height * 0.93));
    
    int j = 0;
        arrayForActive = CCArray::create();
    for (int i = 1; i <= 41; i++) {
        //        int level = 40 - i;
        
        if (Utility::getAchievementStatus(i) == 1) {
            arrayForActive->insertObject(CCString::createWithFormat("%d", i), j);
            j++;
            if (j == 3) {
                break;
            }
        }
    }
    
    for (int i = 0; i < arrayForActive->count(); i++) {
        CCSprite *objective = CCSprite::createWithSpriteFrameName(kScrollBar);
        objective->setPositionY(winSize.height * kScrollBarGap * i - winSize.height * 0.2);
        
        CCString *string = (CCString*)arrayForActive->objectAtIndex(i);
        int level = string->intValue();
        CCString *obj_1 = (CCString*) Utility::objectiveDict()->valueForKey(CCString::createWithFormat("kAchievement_%d_0", level)->getCString());
        CCString *obj_2 = (CCString*) Utility::objectiveDict()->valueForKey(CCString::createWithFormat("kAchievement_%d_1", level)->getCString());
        createLabel(obj_1->getCString(), obj_2->getCString(), ccp(objective->getContentSize().width * 0.18, objective->getContentSize().height * 0.85), objective);
        createSprite("iconTrophy.png", ccp(objective->getContentSize().width * 0.03, objective->getContentSize().height * 0.85), objective);
        objectiveLayer->addChild(objective, 2);
    }
    addChild(objectiveLayer, 2);
    arrayForActive->removeAllObjects();
    arrayForActive->release();
    
    
    soundOn = CCSprite::createWithSpriteFrameName("btnSoundOn.png");
    menuItemSoundOn = CCMenuItemSprite::create(soundOn, soundOn, this, menu_selector(PauseLayer::soundsButtonTapped));
    menuItemSoundOn->setTag(1);
    
    soundOff = CCSprite::createWithSpriteFrameName("btnSoundOff.png");
    menuItemSoundOff = CCMenuItemSprite::create(soundOff, soundOff, this, menu_selector(PauseLayer::soundsButtonTapped));
    menuItemSoundOff->setTag(2);
    
    CCMenuItemToggle *toggleSound = CCMenuItemToggle::createWithTarget(this, menu_selector(PauseLayer::soundsButtonTapped), menuItemSoundOn, menuItemSoundOff, NULL);
    toggleSound->setSelectedIndex((CCUserDefault::sharedUserDefault()->getBoolForKey(kSoundsKey) ? 0 : 1));
    
    menuSoundOff = CCMenu::create(toggleSound , NULL);
    menuSoundOff->setPosition(ccp(winSize.width * 0.95, winSize.height * 0.92));
    addChild(menuSoundOff, 2);
}

void  PauseLayer::soundsButtonTapped(CCObject *sender) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    CCMenuItemToggle *toggleItem = (CCMenuItemToggle*)sender;
    if (toggleItem->selectedItem() == menuItemSoundOn) {
        defaults->setBoolForKey(kSoundsKey, true);
        Utility::changeVolume(1.0f);
    } else if (toggleItem->selectedItem() == menuItemSoundOff) {
        defaults->setBoolForKey(kSoundsKey, false);
        Utility::changeVolume(0.0f);
    }
}

void PauseLayer::addStatsLayer() {
    statsLayer = CCLayer::create();
    statsLayer->setPosition(ccp(winSize.width * 0, winSize.height * 0));
    float scale = Utility::isIPad() ? 1 : 0.7;
    CCLabelBMFont *labelObj = CCLabelBMFont::create("stats", kFontChubby, 0);
    labelObj->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.93));
    labelObj->setScale(scale);
    statsLayer->addChild(labelObj, 2);
    
    CCLabelBMFont *thisGameLabel = CCLabelBMFont::create("this game", kFontChubby, 0);
    thisGameLabel->setScale(scale);
    thisGameItem = CCMenuItemLabel::create(thisGameLabel, this, menu_selector(PauseLayer::menuCallBack) );
    thisGameItem->setContentSize(CCSize(thisGameItem->getContentSize() * scale));
    thisGameItem->setTag(7);
    
    CCLabelBMFont *slashLabel = CCLabelBMFont::create("/", kFontChubby, 0);
    slashLabel->setScale(scale);
    CCMenuItemLabel *slashItem = CCMenuItemLabel::create(slashLabel, this, menu_selector(PauseLayer::menuCallBack) );
    slashItem->setContentSize(CCSize(slashItem->getContentSize() * scale));
    
    CCLabelBMFont *recordsLabel = CCLabelBMFont::create("records", kFontChubby, 0);
    recordsLabel->setScale(scale);
    recordsItem = CCMenuItemLabel::create(recordsLabel, this, menu_selector(PauseLayer::menuCallBack) );
    recordsItem->setContentSize(CCSize(recordsItem->getContentSize() * scale));
    recordsItem->setTag(8);

    
    CCMenu *thisGameRecordsMenu = CCMenu::create(thisGameItem, slashItem, recordsItem, NULL);
    thisGameRecordsMenu->alignItemsHorizontallyWithPadding(winSize.width * 0.01);
    thisGameRecordsMenu->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.8));
    statsLayer->addChild(thisGameRecordsMenu, 2);
    
    createButton("btnObj.png", 6, ccp(winSize.width * 0.30, winSize.height * 0.93));
    const char *score = NULL;
    const char *distance = NULL;
    const char *wallsSmashed = NULL;
    const char *tightSqueezes = NULL;
    const char *longestGamePlayed = NULL;
    if (isCallFromRecords) {
        CCSprite *coinSprite = CCSprite::createWithSpriteFrameName("coin_0.png");
        coinSprite->setPosition(ccp(winSize.width * 0.75, winSize.height * 0.65));
        statsLayer->addChild(coinSprite, 2);
        
        const char *totalCoins = CCString::createWithFormat("%d", gLayer->coinScore)->getCString();
        createLabelForStats("", totalCoins, ccp(coinSprite->getPositionX() + winSize.width * 0.05, coinSprite->getPositionY()), statsLayer);
        
        score =  CCString::createWithFormat("%d", gLayer->score)->getCString();
        distance =  CCString::createWithFormat("%d meters", gLayer->distance)->getCString();
        wallsSmashed =  CCString::createWithFormat("%d", gLayer->wallSmashed)->getCString();
        tightSqueezes =  CCString::createWithFormat("%d", Utility::getTotalTightSqueezes())->getCString();
        longestGamePlayed = CCString::createWithFormat("%02dm%02ds", gLayer->minute, gLayer->seconds)->getCString();
    } else {
        const char *playerName = CCString::createWithFormat("(%s)", Utility::getPlayerName(0)->getCString())->getCString();
        createLabelForStats("", playerName, ccp(winSize.width * 0.65, winSize.height * 0.65), statsLayer);
        int longestGame = Utility::getLongestGame();
        int min = longestGame / 60;
        int sec = longestGame % 60;
        longestGamePlayed = CCString::createWithFormat("%02dm%02ds", min, sec)->getCString();
        score =  CCString::createWithFormat("%d", Utility::getPlayerScore(0))->getCString();
        distance =  CCString::createWithFormat("%d meters", Utility::getLongestDistance())->getCString();
        wallsSmashed =  CCString::createWithFormat("%d", Utility::getTotalWallSmashedLifeTime())->getCString();
        tightSqueezes =  CCString::createWithFormat("%d", Utility::getTotalTightSqueezesLifeTime())->getCString();
    }         
        createLabelForStats("score:", score, ccp(winSize.width * 0.55, winSize.height * 0.65), statsLayer);
        createLabelForStats("distance:", distance, ccp(winSize.width * 0.55, winSize.height * 0.55), statsLayer);
        createLabelForStats("walls smashed:", wallsSmashed, ccp(winSize.width * 0.55, winSize.height * 0.45), statsLayer);
        createLabelForStats("tight squeezes:", tightSqueezes, ccp(winSize.width * 0.55, winSize.height * 0.35), statsLayer);
        createLabelForStats("game time:", longestGamePlayed, ccp(winSize.width * 0.55, winSize.height * 0.25), statsLayer);
    
        addChild(statsLayer, 1);
    
}

void PauseLayer::createLabelForStats(const char *labelText, const char *labelValue, CCPoint position, CCLayer *layer) {
    float scale = Utility::isIPad() ? 1 : 0.6;
    CCLabelBMFont *label1 = CCLabelBMFont::create(labelText, kFontChubby, 0);
    label1->setPosition(position);
    label1->setScale(scale);
    label1->setAnchorPoint(ccp(1, 0.5));
    layer-> addChild(label1, 10);
    
    CCLabelBMFont *label2 = CCLabelBMFont::create(labelValue, kFontChubby, 0);
    label2->setPosition(label1->getPositionX() + winSize.width * 0.025, position.y);
    label2->setScale(scale);
    label2->setAnchorPoint(ccp(0, 0.5));
    layer-> addChild(label2, 10);
    
}


void PauseLayer::createSprite(const char *spriteFrameName, CCPoint pos, CCSprite *objective) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteFrameName);
    sprite->setPosition(pos);
    sprite->setAnchorPoint(ccp(0, 1));
    objective->addChild(sprite,22);
}

void PauseLayer::createLabel(const char *labelName, const char *labelNameValue, CCPoint position, CCSprite *objective) {
    float scale = Utility::isIPad() ? 1 : 0.5;
    CCLabelBMFont *label = CCLabelBMFont::create(labelName, kFontChubby,  0, kCCTextAlignmentLeft);
    label->setPosition(position);
    label->setScale(scale);
    label->setAnchorPoint(ccp(0, 1));
    objective-> addChild(label, 10);
    CCLabelBMFont *labelText = CCLabelBMFont::create(labelNameValue, kFontChubby, winSize.width * 0.4);
    //    labelText->
    labelText->setPosition(ccp(label->getPositionX(), label->getPositionY() - winSize.height * 0.078 ));
    labelText->setScale(scale * 0.65);
    labelText->setAnchorPoint(ccp(0, 1));
    objective->addChild(labelText, 10);
}

void PauseLayer::createButton(const char *spriteName, int tag, CCPoint posititon) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(PauseLayer::menuCallBack));
    menuItem->setTag(tag);
    CCMenu *menu = CCMenu::create(menuItem, NULL);
    menu->setPosition(posititon);
    addChild(menu, 2);
}


void PauseLayer::addMenuItems(const char *frameName, int tag) {
    CCSprite *charSprite = CCSprite::createWithSpriteFrameName(frameName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(charSprite, charSprite, this, menu_selector(PauseLayer::menuCallBack));
    menuItem->setTag(tag);
    charMenuIemList->addObject(menuItem);
}

void PauseLayer::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    CCMenuItemSprite *sprite = ((CCMenuItemSprite*)(menuItem));
    int tag = sprite->getTag();
    switch (tag) {
        case 1:
            CCLOG("newgame");
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(gLayer);
            CCDirector::sharedDirector()->resume();
            CCDirector::sharedDirector()->replaceScene(GameScene::create(kSceneTypeGameScene));
            break;
        case 2:
            CCLOG("menuscreen");
            CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(gLayer);
            CCDirector::sharedDirector()->resume();
            CCDirector::sharedDirector()->replaceScene(MainMenuScene::create());
            break;
            
        case 3:
            CCLOG("resume");
            showHUDButtons();
            CCDirector::sharedDirector()->resume();
            gLayer->hudLayer->pauseBtnMenu->setVisible(true);
            removeFromParent();
            break;
        case 4:
            CCLOG("sound");
            break;
        case 5:
            CCLOG("records");
//            if (arrayForActive != NULL) {
//                arrayForActive->removeAllObjects();   
//            }
            removeChild(objectiveLayer, true);
            addStatsLayer();
            break;
        case 6:
            CCLOG("objective");
            removeChild(statsLayer, true);
            addObjectiveLayer();
            break;
            
            case 7:
            CCLog("this game");
            isCallFromRecords = false;
            removeChild(statsLayer, true);
            addStatsLayer();
            break;
            case 8:
            CCLog("records");
            isCallFromRecords = true;
            removeChild(statsLayer, true);
            addStatsLayer();
            break;
        default:
            break;
    }
    
}



