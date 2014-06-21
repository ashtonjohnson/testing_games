//
//  MainMenuLayer.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 22/10/13.
//
//

#include "MainMenuLayer.h"
#include "GameScene.h"
#include "Utility.h"
#include "ObjectiveScene.h"
#include "AboutLayer.h"
#include "AboutScene.h"
#include "UpgradeScene.h"
#include "NDKHelper.h"
#include "ScoresScene.h"
#include "SoundConstant.h"
#include "MainMenuScene.h"
#include "FlurryConstant.h"
//#include "CCEditBox.h"

using namespace cocos2d::extension;

MainMenuLayer* MainMenuLayer::create() {
    MainMenuLayer *pRet = new MainMenuLayer;
    if (pRet && pRet->init()) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool MainMenuLayer::init() {
    if (!CCLayer::init()) {
        return false;
    }
    i = 1;
    charTagForOrder = 1;
//    Utility::addSpriteSheet("character");
    Utility::setCharacterLockUnlockStatus(kCharacterType_NormanBlue, 1);
    charMenuIemList = CCArray::create();
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *bgSprite = CCSprite::create("menuBg.png");
    bgSprite->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    addChild(bgSprite);
    charAction = NULL;
//    CCScale9Sprite *sprite = CCScale9Sprite::createWithSpriteFrameName("boxTransparent.png");
//    CCEditBox *m_pEditName = CCEditBox::create(CCSize(winSize.width * 0.35, winSize.height * 0.15), sprite);
//    m_pEditName->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.77 ));
//    m_pEditName->setFontColor(ccBLACK);
//    m_pEditName->setFont(kFontChubby, 30);
//    //  m_pEditName->setPlaceHolder("");
//    m_pEditName->setMaxLength(10);
//    m_pEditName->setReturnType(kKeyboardReturnTypeDone);
////    const char *playerName = Utility::getPlayerName(0)->getCString();
//    m_pEditName->setText("upkesh");
//    m_pEditName->setPlaceHolder("Upkesh");
//    addChild(m_pEditName, 200);
//    
    
    //objective button
    setKeypadEnabled(true);
    isHelpTutorial = false;
    CCSprite *btnObjective = CCSprite::createWithSpriteFrameName("btnObjective.png");
    CCMenuItemSprite *objectiveMenuItem = CCMenuItemSprite::create(btnObjective, btnObjective, this, menu_selector(MainMenuLayer::menuCallBack));
    objectiveMenuItem->setTag(6);
    CCMenu *objectiveMenu = CCMenu::create(objectiveMenuItem, NULL);
    objectiveMenu->setPosition(ccp(winSize.width * 0.05, winSize.height * 0.08));
    addChild(objectiveMenu, 2);
    
    //play button
    CCSprite *playSprite = CCSprite::createWithSpriteFrameName("btnPlay.png");
    menuItem = CCMenuItemSprite::create(playSprite, playSprite, this, menu_selector(MainMenuLayer::menuCallBack));
    menuItem->setTag(5);
    playMenu = CCMenu::create(menuItem, NULL);
    playMenu->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    addChild(playMenu, 2);
    
    //added all other buttons
    addMenuItems("btnScore.png", 1);
    addMenuItems("btnUpgrades.png", 2);
    addMenuItems("btnHelp.png", 3);
    addMenuItems("btnAbout.png", 4);
    
    CCMenu *btnMenu = CCMenu::createWithArray(charMenuIemList);
    btnMenu->alignItemsVerticallyWithPadding(winSize.height * 0.1);
    btnMenu->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.5));
    addChild(btnMenu, 2);
    
    //add character here and other animations
    
    Utility::setCharactorType(kCharacterType_NormanBlue);
    charTag = (int)Utility::getCharactorType();
    addCharMenu(CCString::createWithFormat("char%d_", Utility::getCharactorType())->getCString(), 20, "Lenny");
    charName = "Lenny";
    
    createButton("btnMoreGames.png", 8, ccp(winSize.width * 0.75, winSize.height * 0.945), bgSprite);
    if (Utility::isAndroid) {
        createButton("btnGooglePlay.png", 10, ccp(winSize.width * 0.85, winSize.height * 0.945), bgSprite);
    }else {
        createButton("btnGameCenter.png", 10, ccp(winSize.width * 0.85, winSize.height * 0.945), bgSprite);
    }
    soundOn = CCSprite::createWithSpriteFrameName("btnSoundOn.png");
    menuItemSoundOn = CCMenuItemSprite::create(soundOn, soundOn, this, menu_selector(MainMenuLayer::soundsButtonTapped));
    menuItemSoundOn->setTag(1);    
    
    soundOff = CCSprite::createWithSpriteFrameName("btnSoundOff.png");
    menuItemSoundOff = CCMenuItemSprite::create(soundOff, soundOff, this, menu_selector(MainMenuLayer::soundsButtonTapped));
    menuItemSoundOff->setTag(2);
    
    CCMenuItemToggle *toggleSound = CCMenuItemToggle::createWithTarget(this, menu_selector(MainMenuLayer::soundsButtonTapped), menuItemSoundOn, menuItemSoundOff, NULL);
    toggleSound->setSelectedIndex((CCUserDefault::sharedUserDefault()->getBoolForKey(kSoundsKey) ? 0 : 1));
    
    menuSoundOff = CCMenu::create(toggleSound , NULL);
    menuSoundOff->setPosition(ccp(winSize.width * 0.94, winSize.height * 0.945));
    addChild(menuSoundOff, 2);
//    createButton("btnSound_0.png", 9, ccp(winSize.width * 0.97, winSize.height * 0.96), bgSprite);
    return true;
}

void  MainMenuLayer::soundsButtonTapped(CCObject *sender) {
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

void MainMenuLayer::addCharMenu(const char *frameName, int frameCount, const char *charName) {
    if (charAction != NULL) {
        stopAction(charAction);
    }
    charSprite = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("char%d_0.png", Utility::getCharactorType())->getCString());
    charSpriteSelected = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("char%d_0.png", Utility::getCharactorType())->getCString());
  //  charSprite->setAnchorPoint(ccp(0.5, 0.5));
    charMenuItem = CCMenuItemSprite::create(charSprite, charSpriteSelected, this, menu_selector(MainMenuLayer::charMenuCallBack));
    charMenuItem->setTag(charTag++);
    charMenu = new CCMenu;
    charMenu->initWithArray(CCArray::create(charMenuItem, NULL));
//    charMenu = CCMenu::create(charMenuItem, NULL);
    charMenu->setPosition(ccp(winSize.width * 0.25, winSize.height * 0.5));
    addChild(charMenu, 2);
    if (charTag == 4) {
        charTag = 0;
    }
    
    if (Utility::getCharacterLockUnlockStatus(Utility::getCharactorType()) == 0) {
        float scale = Utility::isIPad() ? 1 : 0.5;
        CCSprite *coinSprite = CCSprite::createWithSpriteFrameName("coin_0.png");
        coinSprite->setPosition(ccp(charSprite->getContentSize().width * 0.05, charSprite->getPositionY() + winSize.height * 0.22));
        charMenuItem->addChild(coinSprite, 2);
        
        
        const char *coins = CCString::createWithFormat("%d", getNoOfCoins())->getCString();
        CCLabelBMFont *coinLabel = CCLabelBMFont::create(coins, kFontMarkerFelt, 0);
        coinLabel->setScale(scale);
        coinLabel->setPosition(ccp(coinSprite->getContentSize().width * 2.45, coinSprite->getContentSize().height * 0.5));
        coinSprite-> addChild(coinLabel, 2);

        CCSprite *sprite = CCSprite::createWithSpriteFrameName("btnUnlock.png");
        sprite->setScale(0.7);
        CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(MainMenuLayer::menuCallBack));
        menuItem->setTag(7);
        CCMenu *menu = CCMenu::create(menuItem, NULL);
        menu->setPosition(CCPoint(charSprite->getContentSize().width * 0.8, charSprite->getPositionY() + winSize.height * 0.17));
        charMenuItem->addChild(menu, 2);
    }
    //add label tap to change
    if (i == 1) {
        charAction = new CCRepeatForever;
        charAction->initWithAction(CCSequence::create(CCDelayTime::create(2), CCCallFunc::create(this, callfunc_selector(MainMenuLayer::runCharacterAction)), CCDelayTime::create(3), CCCallFunc::create(this, callfunc_selector(MainMenuLayer::resetActions)), NULL));
        runAction(charAction);
        float scale = Utility::isIPad() ? 1 : 0.5;
        tapToChange = CCLabelBMFont::create("Tap To Change", kFontMarkerFelt, 0);
        tapToChange->setPosition(ccp(charSprite->getContentSize().width * 0.5, -charSprite->getContentSize().height * 0.75));
        tapToChange->setScale(scale);
        charMenuItem-> addChild(tapToChange, 2);
        menuAction = new CCRepeatForever;
        menuAction->initWithAction(CCSequence::createWithTwoActions(CCMoveTo::create(0.6, ccp(0, winSize.height * 0.05)), CCMoveTo::create(0.6, ccp(0, -winSize.height * 0.05))));
        charMenuItem->runAction(menuAction);
        i++;
    } else {
        float scale = Utility::isIPad() ? 1 : 0.6;
        label = CCLabelBMFont::create(charName, kFontMarkerFelt, 0);
        label->setPosition(CCPoint(charMenuItem->getContentSize().width * 0.5, -charMenuItem->getContentSize().height * 0.75));
        label->setScale(scale);
        charMenuItem-> addChild(label, 10);
        //adding name of the character
        if (Utility::getCharacterLockUnlockStatus(Utility::getCharactorType()) != 0) {
            menuAction = new CCRepeatForever;
            menuAction->initWithAction(CCSequence::createWithTwoActions(CCMoveTo::create(0.6, ccp(0, winSize.height * 0.05)), CCMoveTo::create(0.6, ccp(0, -winSize.height * 0.05))));
            charMenuItem->runAction(menuAction);
            charAction = new CCRepeatForever;
            charAction->initWithAction(CCSequence::create(CCDelayTime::create(2), CCCallFunc::create(this, callfunc_selector(MainMenuLayer::runCharacterAction)), CCDelayTime::create(2), CCCallFunc::create(this, callfunc_selector(MainMenuLayer::resetActions)), NULL));
            runAction(charAction);
         //   runCharacterAction();
        }
    }
    runCharAnimation(frameName, frameCount);
    addCharacterFlameAnimation();
}

void MainMenuLayer::runRotateAction() {
    charX = charSprite->getPositionX() + charSprite->getContentSize().width * 0.5;
    charY = charSprite->getPositionY() + charSprite->getContentSize().height * 0.5;
    charSprite->setPosition(ccp(charX, charY));
    charSprite->setAnchorPoint(ccp(0.5, 0.5));
    addStarsParticle();
    charSprite->runAction(CCSequence::create(CCRotateBy::create(0.6, 380), CCRotateBy::create(0.6, -20), NULL));
}

void MainMenuLayer::resetRotateAction() {
      charSprite->setAnchorPoint(ccp(0, 0));
    charSprite->setPosition(ccp(charSprite->getPositionX() - charSprite->getContentSize().width * 0.5, charSprite->getPositionY() - charSprite->getContentSize().height * 0.5));
}

void MainMenuLayer::runCharacterAction() {
    int randomAction = Utility::randomIntBetween(0, 2);
    switch (randomAction) {
        case 0:
            runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(MainMenuLayer::runRotateAction)), CCDelayTime::create(1.2), CCCallFunc::create(this, callfunc_selector(MainMenuLayer::resetRotateAction)), NULL));
            break;
        case 1:
            addStarsParticle();
            break;
        case 2:
//    charSprite->setPosition(charMenu->getPosition());
//        CCLog("get pos %f, %f charsprite pos %f, %f", playMenu->getPositionX(), playMenu->getPositionY(), charSprite->getPositionX(), charSprite->getPositionY());
//            charSprite->runAction(CCMoveTo::create(0.3, ccp(240, 160)));
//            
//            charSprite->runAction(CCSequence::create(CCMoveBy::create(0.3, ccp(playMenu->getPositionX()* 0.38, 0)), CCMoveBy::create(0.3, ccp(-playMenu->getPositionX()* 0.2, 0)), CCMoveBy::create(0.3, ccp(playMenu->getPositionX()* 0.18, 0)), CCMoveBy::create(0.3, ccp(-playMenu->getPositionX()* 0.25, 0)), NULL));
//            menuItem->runAction(CCSequence::create(CCDelayTime::create(0.3),  CCMoveBy::create(0.3, ccp(playMenu->getPositionX()* 0.1, 0)), CCMoveBy::create(0.3, ccp(-playMenu->getPositionX()* 0.1, 0)), CCDelayTime::create(0),  CCMoveBy::create(0.3, ccp(playMenu->getPositionX()* 0.1, 0)), CCMoveBy::create(0.3, ccp(-playMenu->getPositionX()* 0.1, 0)), NULL));
            break;

        default:
            break;
    }

}


void MainMenuLayer::resetActions() {
    charMenuItem->removeChild(starsParticle, true);
}


void MainMenuLayer::addStarsParticle() {
    starsParticle = CCParticleSystemQuad::create("newStarsParticle.plist");
    starsParticle->setPosition(ccp(charMenuItem->getContentSize().width * 0.2, charMenuItem->getContentSize().height * 0.5));
    charMenuItem-> addChild(starsParticle, -1, 101);
}

void MainMenuLayer::charMenuCallBack(CCObject *charMenuItem) {
    removeChild(charMenu);
    CC_SAFE_RELEASE_NULL(charMenu);
    const char *frameName = NULL;
    charName = "";
    int frameCount = 0;
    
    
    switch (charTagForOrder) {
        case 2:
            Utility::setCharactorType(kCharacterType_BellaRed);
            frameName = "char2_";
            frameCount = 4;
            charName = "Fauna Flea";
            break;
        case 1:
            Utility::setCharactorType(kCharacterType_JohnyOrange);
            frameName = "char1_";
            frameCount = 20;
            charName = "Dez";
            break;
            
        case 3:
            Utility::setCharactorType(kCharacterType_VinnyGreen);
            frameName = "char3_";
            frameCount = 9;
            charName = "Ella";
            break;
        case 0:
            Utility::setCharactorType(kCharacterType_NormanBlue);
            frameName = "char0_";
            frameCount = 20;
            charName = "Lenny";
            addCharacterFlameAnimation();
            break;
    }
    charTagForOrder++;
    if (charTagForOrder == 4) {
        charTagForOrder = 0;
    }
    addCharMenu(frameName, frameCount, charName);
}

void MainMenuLayer::runCharAnimation(const char *frameName, int frameCount) {
    charAnimate = new CCAnimate();
    charAnimate->initWithAnimation((CMAnimation*) CMAnimation::animationWithFrame(frameName, frameCount, 0.05));
    charSprite->runAction(CCRepeatForever::create(charAnimate));
}

void MainMenuLayer::addCharacterFlameAnimation() {
    if (Utility::getCharactorType() == kCharacterType_NormanBlue) {//char 0
        CCPoint position = CCPoint(0, charSprite->getContentSize().height * 0.32);
        runFlameAnimations("flameChar0_0.png", "flameChar0_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_JohnyOrange) { // char 1
        CCPoint position = CCPoint(charSprite->getContentSize().width * 0.16, charSprite->getContentSize().height * 0.7);
        runFlameAnimations("flameChar1_0.png", "flameChar1_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_BellaRed) { // char 2
        CCPoint position = CCPoint(-charSprite->getContentSize().width * 0.1, charSprite->getContentSize().height * 0.1);
        runFlameAnimations("flameChar2_0.png", "flameChar2_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_VinnyGreen) { // char 3
        CCPoint position = CCPoint(-charSprite->getContentSize().width * 0.04, charSprite->getContentSize().height * 0.28);
        runFlameAnimations("flameChar3_0.png", "flameChar3_", 4, position);
    }
}

void MainMenuLayer::runFlameAnimations(const char *spriteName, const char *frameName, int frameCount, CCPoint position) {
    flame = CCSprite::createWithSpriteFrameName(spriteName);
    flame->setPosition(position);
    charSprite->addChild(flame, 2);
    flameAnimate = new CCAnimate();
    flameAnimate->initWithAnimation((CMAnimation*) CMAnimation::animationWithFrame(frameName, 4, 0.05));
    
    flame->runAction(CCRepeatForever::create(flameAnimate));
}

void MainMenuLayer::addMenuItems(const char *frameName, int tag) {
    CCSprite *charSprite = CCSprite::createWithSpriteFrameName(frameName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(charSprite, charSprite, this, menu_selector(MainMenuLayer::menuCallBack));
    menuItem->setTag(tag);
    charMenuIemList->addObject(menuItem);
    if (std:: strcmp(frameName, "btnUpgrades.png") == 0 && Utility::storePushPopPowerUps() > 0 && Utility::storePushPopExtras() > 0) {
        CCSprite *numberSprite = CCSprite::createWithSpriteFrameName("iconNumber.png");
        numberSprite->setPosition(ccp(charSprite->getContentSize().width * 0.05, charSprite->getContentSize().height * 0.98));
        charSprite->addChild(numberSprite, 2);
        
        int totalPushPops = Utility::storePushPopExtras() + Utility::storePushPopPowerUps();
        
        const char *pushPops = CCString::createWithFormat("%d", totalPushPops)->getCString();
        float scale = Utility::isIPad() ? 1 : 0.5;
        CCLabelBMFont *numberLabel = CCLabelBMFont::create(pushPops, kFontChubby, 0);
        numberLabel->setScale(scale); //0.5
        numberLabel->setPosition(ccp(numberSprite->getContentSize().width * 0.54, numberSprite->getContentSize().height * 0.55));
        numberSprite->addChild(numberLabel, 2);
        
        numberSprite->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleTo::create(0.5, 0.9), CCScaleTo::create(0.5, 1))));
    }
}

void MainMenuLayer::createLabel(const char *labelName, CCPoint position, CCSprite *objective) {
    float scale = Utility::isIPad() ? 1 : 0.6;
    label = CCLabelBMFont::create(labelName, kFontMarkerFelt, 0);
    label->setPosition(position);
    label->setScale(scale);
    objective-> addChild(label, 10);
}

void MainMenuLayer::createSprite(const char *spriteFrameName, CCPoint pos, CCSprite *objective) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteFrameName);
    sprite->setPosition(pos);
    objective->addChild(sprite,22);
}

void MainMenuLayer::createButton(const char *spriteName, int tag, CCPoint posititon, CCSprite *objective) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteName);
//    sprite->setScale(0.7);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(MainMenuLayer::menuCallBack));
    menuItem->setTag(tag);
    CCMenu *menu = CCMenu::create(menuItem, NULL);
    menu->setPosition(posititon);
    objective->addChild(menu, 2);
}

void MainMenuLayer::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    CCMenuItemSprite *sprite = ((CCMenuItemSprite*)(menuItem));
    int tag = sprite->getTag();
    switch (tag) {
        case 1:{
            CCDictionary* prms = CCDictionary::create();
            prms->setObject(CCString::create(kFlurryScoresButton), "FLURRY_EVENT");
            SendMessageWithParams(string("sendFlurryReport"), prms);
            CCDirector::sharedDirector()->replaceScene(ScoresScene::create());
        }
            break;
        case 2:{
            CCDictionary* prms = CCDictionary::create();
            prms->setObject(CCString::create(kFlurryUpgradesButton), "FLURRY_EVENT");
            SendMessageWithParams(string("sendFlurryReport"), prms);
            CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Powerups));
        }
            break;
        case 3:{            
            CCDictionary* prms = CCDictionary::create();
            prms->setObject(CCString::create(kFlurryHelpButton), "FLURRY_EVENT");
            SendMessageWithParams(string("sendFlurryReport"), prms);
            isHelpTutorial = true;
//            CCDirector::sharedDirector()->replaceScene(GameScene::create(kSceneTypeHelp));
            playGame();
        }
            break;
        case 4:
        {
            CCDictionary* prms = CCDictionary::create();            
            prms->setObject(CCString::create(kFlurryAboutButton), "FLURRY_EVENT");
            SendMessageWithParams(string("sendFlurryReport"), prms);
            
            CCDirector::sharedDirector()->replaceScene(AboutScene::create());
        }
            break;
        case 5:{
            isHelpTutorial = false;
            playGame();
            CCDictionary* prms = CCDictionary::create();
            prms->setObject(CCString::create("GAME START"), "FLURRY_EVENT");
            SendMessageWithParams(string("sendFlurryReport"), prms);
        }
            break;
            
        case 6:
            CCDirector::sharedDirector()->replaceScene(ObjectiveScene::create());
            break;
        case 8:{
            //show more apps after a delay of 0.5 seconds to avoid flickering
            if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
                //stop character animations
                stopAnimations();
                CCDelayTime *delay = CCDelayTime::create(0.5);
                runAction(CCSequence::create(delay, CCCallFunc::create(this, callfunc_selector(MainMenuLayer::showMoreApps)), NULL));
            } else {
                CCDictionary* prms = CCDictionary::create();
                prms->setObject(CCString::create("YES"), kShowChartboostAd);
                SendMessageWithParams(string("showMoreApps"), prms);
            }
                
            }
            break;
            
        case 9:
            CCLog("Sounds");
            break;
        case 10: {
            //show more apps after a delay of 0.5 seconds to avoid flickering
            if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
                //stop character animations
                stopAnimations();
                CCDelayTime *delay = CCDelayTime::create(0.5);
                runAction(CCSequence::create(delay, CCCallFunc::create(this, callfunc_selector(MainMenuLayer::showLeaderboards)), NULL));
            }else
                SendMessageWithParams(string("leaderBoardController"), NULL);
            }
            break;
            
        case 7:
            CCLOG("unlock button clicked---> character type %d", Utility::getCharactorType());
            int charCoins = getNoOfCoins();
            int totalCoins = Utility::getTotalCoins();
            if (totalCoins >= charCoins) {
                int restCoins = totalCoins - charCoins;
                Utility::setCharacterLockUnlockStatus(Utility::getCharactorType(), 1);
                Utility::setTotalCoins(restCoins);
                charSprite->removeAllChildrenWithCleanup(true);
                runCharacterAction();
                createLabel(charName, CCPoint(charSprite->getContentSize().width * 0.5, -charSprite->getContentSize().height * 0.25), charSprite);
                CCDirector::sharedDirector()->replaceScene(MainMenuScene::create());
            } else {
                CCDictionary* prms = CCDictionary::create();
                prms->setObject(CCString::createWithFormat("Not enough coins to unlock %s!", charName), "title");
                if (Utility::isAndroid) {
                    prms->setObject(CCString::create(""), "message");
                }
                prms->setObject(CCString::create("Visit characters"), "button0");
                prms->setObject(CCString::create("Unlock all characters"), "button1");
                prms->setObject(CCString::create("Cancel"), "button2");
                prms->setObject(CCString::create("mainScreen"), "callFromScreen");
                SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
            }
            break;
            
    }
}

void MainMenuLayer::restartCharacterAnimations() {
    CCDelayTime *delay = CCDelayTime::create(0.5);
    runAction(CCSequence::create(delay, CCCallFunc::create(this, callfunc_selector(MainMenuLayer::startAnimations)), NULL));
}

void MainMenuLayer::showLeaderboards() {
    restartCharacterAnimations();
    SendMessageWithParams(string("leaderBoardController"), NULL);
}

void MainMenuLayer::showMoreApps(){
    restartCharacterAnimations();
    CCDictionary* prms = CCDictionary::create();
    prms->setObject(CCString::create("YES"), kShowChartboostAd);
    SendMessageWithParams(string("showMoreApps"), prms);
}

void MainMenuLayer::goToUpgradeScreenWithExtras(CCNode *sender, void *data){
    CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Extras));
}

void MainMenuLayer::playGame() {
    if(Utility::getCharactorType() == kCharacterType_VinnyGreen && Utility::getCharacterLockUnlockStatus(kCharacterType_VinnyGreen) == 1 ){
        playGameWithChar();
    }else if (Utility::getCharactorType() == kCharacterType_BellaRed && Utility::getCharacterLockUnlockStatus(kCharacterType_BellaRed) == 1){
        playGameWithChar();
    }else if(Utility::getCharactorType() == kCharacterType_JohnyOrange && Utility::getCharacterLockUnlockStatus(kCharacterType_JohnyOrange) == 1){
        playGameWithChar();
    }else if (Utility::getCharactorType() == kCharacterType_NormanBlue ) {
        playGameWithChar();
    } else {
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("Not enough coins to unlock this character!"), "title");
        prms->setObject(CCString::create("Visit characters"), "button0");
        prms->setObject(CCString::create("Unlock all characters"), "button1");
        prms->setObject(CCString::create("Cancel"), "button2");
        prms->setObject(CCString::create("mainScreen"), "callFromScreen");
        SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
    }
    
    CCDictionary* prms = CCDictionary::create();
    prms->setObject(CCString::createWithFormat("%s character played", charName), "FLURRY_EVENT");
    SendMessageWithParams(string("sendFlurryReport"), prms);
}

void MainMenuLayer::playGameWithChar() {
    if (isHelpTutorial) {
        CCDirector::sharedDirector()->replaceScene(GameScene::create(kSceneTypeHelp));
        isHelpTutorial = false;
    }else {
        CCDirector::sharedDirector()->replaceScene(GameScene::create(kSceneTypeGameScene));
    }
}

void MainMenuLayer::unlockAllChars() {
    CCLOG("unlock all characters");
        CCDictionary* prms = CCDictionary::create();
    prms->setObject(CCString::create("UNLOCK ALL CHARACTERS"), "PURCHASE_ITEM");
    SendMessageWithParams(string("startPuchaseFlow"), prms);
    SendMessageWithParams(string("sendFlurryReport"), prms);
}

void MainMenuLayer::replaceSceneAfterUnlock() {
    Utility::setUnlockAllCharacter();
    CCDirector::sharedDirector()->replaceScene(MainMenuScene::create());
}

int MainMenuLayer::getNoOfCoins() {
    int coins = 0;
    switch (Utility::getCharactorType()) {
        case kCharacterType_JohnyOrange:
            coins = 10000;
            break;
            
        case kCharacterType_VinnyGreen:
            coins = 20000;
            break;
            
        case kCharacterType_NormanBlue:
            coins = 0;
            break;
            
        case kCharacterType_BellaRed:
            coins = 15000;
            break;         
    }
    return  coins;
}
void MainMenuLayer:: keyBackClicked() {    
    NDKHelper::AddSelector("MenuSceneSelectors", "resetListener", callfuncND_selector(MainMenuLayer::resetListener), this);
    SendMessageWithParams(string("quitGame"), NULL);
}

void MainMenuLayer::resetListener(CCNode *sender, void *data){
    CCDirector::sharedDirector()->end();
}

void MainMenuLayer::removeCharacter() {
    charMenuItem->removeChildByTag(101);
    charMenuItem->stopAction(menuAction);
    stopAction(charAction);
    cleanup();
}

void MainMenuLayer::stopAnimations(){
    CCLog("stopAnimations called ...");
    if(charAction != NULL){
        removeCharacter();
    }
}

void MainMenuLayer::startAnimations(){
    CCLog("startAnimations called ...");
    if(charAction != NULL) {
        
        //Remove character
        removeCharacter();
        
        //Reset position and angle
        charMenuItem->setPosition(ccp(0, 0));
        charMenu->setPosition(ccp(winSize.width * 0.25, winSize.height * 0.5));
        charSprite->setRotation(0);
        charSprite->setPosition(charSprite->getPosition());
        
        //Run actions again
        if(Utility::getCharacterLockUnlockStatus(Utility::getCharactorType())){
           runAction(charAction);
           charMenuItem->runAction(menuAction);
        }
        charSprite->runAction(CCRepeatForever::create(charAnimate));
        flame->runAction(CCRepeatForever::create(flameAnimate));
    }
}

void MainMenuLayer::onEnter(){
    CCLayer::onEnter();
    NDKHelper::AddSelector("getCoinsSelector", "goToUpgradeScreenWithExtras", callfuncND_selector(MainMenuLayer::goToUpgradeScreenWithExtras), this);
        NDKHelper::AddSelector("getCoinsSelector", "unlockAllChars", callfuncND_selector(MainMenuLayer::unlockAllChars), this);
    NDKHelper::AddSelector("getCoinsSelector", "replaceSceneAfterUnlock", callfuncND_selector(MainMenuLayer::replaceSceneAfterUnlock), this);
    
    NDKHelper::AddSelector("getCoinsSelector", "stopAnimations", callfuncND_selector(MainMenuLayer::stopAnimations), this);
    NDKHelper::AddSelector("getCoinsSelector", "startAnimations", callfuncND_selector(MainMenuLayer::startAnimations), this);

}

void MainMenuLayer::onExit() {
    NDKHelper::RemoveSelectorsInGroup("getCoinsSelector");
//    //    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LevelSelectionScene.plist");
    this->removeAllChildrenWithCleanup(true);
    CCLayer::onExit();
}
