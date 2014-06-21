//
//  ContinueLayer.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 28/10/13.
//
//

#include "ContinueLayer.h"
#include "Constant.h"
#include "Utility.h"
#include "GameOverScene.h"
#include "GameOverLayer.h"
#include "GameLayer.h"
#include "HUDLayer.h"
#include "NDKHelper.h"
#include "SoundConstant.h"

#define kScrollBarGap 0.15
ContinueLayer* ContinueLayer::create(GameLayer *gLayer) {
	ContinueLayer * pRet =new ContinueLayer();
    if (pRet && pRet->init(gLayer)) {
        pRet->autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}
bool ContinueLayer:: init(GameLayer *gLayer) {
    if (!CCLayer::init()) {
        return false;
    }
    timer = 10;
    isContinueLayer = true;
    gLayer->countContinue++;
    
    if (gLayer->countContinue == 5 && Utility::getAchievementStatus(39) == 1) {
        //achieve 39
        CCLOG("never say die");
        Utility::setAchievementStatus(39, 2);
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_NEVER_SAY_DIE : ACH_IOS_NEVER_SAY_DIE);
        
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        gameLayer-> addFinalAchievementLayer(39);
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    gameLayer = gLayer;
    
    CCLayerColor *colorLayer = CCLayerColor::create(ccc4(50, 50, 50, 120), winSize.width  , winSize.height );
    addChild(colorLayer, 2);
    
    middleRect = CCSprite::create("middleRectangle.png");
    middleRect->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    colorLayer->addChild(middleRect);
    
    const char *totalStars = CCString::createWithFormat("%d", Utility::getTotalStars())->getCString();
    createSprite("coinsStars_4.png", ccp(middleRect->getContentSize().width * 0.01, middleRect->getContentSize().height), middleRect);
    createLabel("your stars", "", ccp(winSize.width * 0.01, middleRect->getContentSize().height * 0.83), middleRect);

    labelTotalStars = CCLabelBMFont::create(totalStars, kFontChubby, 0);
    labelTotalStars->setAnchorPoint(ccp(0, 0.5));
    labelTotalStars->setPosition(ccp(winSize.width * 0.15, middleRect->getContentSize().height * 0.9));
    middleRect->addChild(labelTotalStars, 2);    
    
    buyStarLayer = CCLayer::create();
    buyStarLayer->setVisible(false);
    
    continueLayer = CCLayer::create();
    continueLayer->setVisible(true);
    
    addContinueLayer();
    addBuyStarLayer();
    
    gLayer->hudLayer->pauseBtnMenu->setEnabled(false);    
    createButton("btnStar.png", 1, ccp(winSize.width * 0.5, winSize.height * 0.25));
    createButton("btnClose.png", 2, ccp(winSize.width * 0.9, winSize.height * 0.75));
    
    return true;
}

void ContinueLayer::addContinueLayer() {
    continueLayer->setPosition(winSize.width * 0, winSize.height * 0);
    float scale = Utility::isIPad() ? 1.5 : 0.9;
    continueLabel = CCLabelBMFont::create("continue?", kFontMarkerFelt, 0);
    continueLabel->setPosition(ccp(winSize.width* 0.5, winSize.height * 0.75));
    continueLabel->setScale(scale);
    continueLayer-> addChild(continueLabel, 2);
    
    timerLabel = CCLabelBMFont::create("10", kFontMarkerFelt, 0);
    timerLabel->setPosition(ccp(winSize.width* 0.5, winSize.height * 0.5));
    timerLabel->setScale(scale);
    timerLabel->setColor(ccc3(20, 119, 119));
    continueLayer -> addChild(timerLabel, 2);
    addChild(continueLayer, 2);
}

void ContinueLayer::addBuyStarLayer() {
    
    float scale = Utility::isIPad() ? 1 :0.4;
    CCLabelBMFont *upperLabel = CCLabelBMFont::create(CCString::createWithFormat("YOU NEED %d MORE STARS", gameLayer->countContinue)->getCString(), kFontMarkerFelt, 0);
    upperLabel->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.92));
    upperLabel->setScale(scale);
    buyStarLayer->addChild(upperLabel, 2);
    float x = 1.01, y = 0.1875;
    if (Utility::isIPad()) {
        x = 1.1;
        y = 0.165;
    }
    int noOfLevels = 4;
    for (int i = 0; i < noOfLevels; i++) {
        
        CCSprite *objective = CCSprite::createWithSpriteFrameName(kScrollBar);//0.1875 // 1.05
        objective->setPosition(ccp(winSize.width * 0.5 ,middleRect->getContentSize().height * x - i * winSize.height * y));
        objective->setScale(0.8);
        CCDictionary *dict = (CCDictionary*)Utility::coinsStarsDict()->objectForKey(CCString::createWithFormat("coinsStars_%d", i+4)->getCString());
        
        for (int j = 1; j < dict->count()+1; j++) {
            CCString *element = (CCString*)dict->valueForKey(CCString::createWithFormat("string_%d", j)->getCString());
            const char *getValue =  element->getCString();
            if (j == 1) {
                createSprite(getValue, ccp(objective->getContentSize().width * 0.01, objective->getContentSize().height * 0.75), objective);
            } else if (j == 2) {
                createLabel(getValue, "", ccp(objective->getContentSize().width * 0.2, objective->getContentSize().height * 0.70), objective);
                
            } else if (j > 2) {
                createLabel( getValue, "", ccp(objective->getContentSize().width * 0.55, objective->getContentSize().height * 0.70), objective);
            }
        }
        
        createButton("btnBuy3.png", i+4, ccp(objective->getContentSize().width * 0.85, objective->getContentSize().height * 0.55), objective);
        buyStarLayer->addChild(objective, 2);
    }
    addChild(buyStarLayer, 2);
}

void ContinueLayer::createSprite(const char *spriteFrameName, CCPoint pos, CCSprite *objective) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteFrameName);
    sprite->setPosition(pos);
    sprite->setAnchorPoint(ccp(0, 1));
    objective->addChild(sprite,22);
}

void ContinueLayer::createLabel(const char *labelName, const char *labelNameValue, CCPoint position, CCSprite *objective) {
    float scale = Utility::isIPad() ? 1 : 0.6;
    label = CCLabelBMFont::create(labelName, kFontChubby,  0, kCCTextAlignmentLeft);
    label->setPosition(position);
    label->setScale(scale);
    label->setAnchorPoint(ccp(0, 1));
    objective-> addChild(label, 10);
    labelText = CCLabelBMFont::create(labelNameValue, kFontChubby, winSize.width * 0.4);
    //    labelText->
    labelText->setPosition(ccp(label->getPositionX(), label->getPositionY() - winSize.height * 0.078 ));
    labelText->setScale(scale * 0.65);
    labelText->setAnchorPoint(ccp(0, 1));
    objective->addChild(labelText, 10);
}

void ContinueLayer::createButton(const char *spriteName, int tag, CCPoint posititon, CCSprite *objective) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteName);
    sprite->setAnchorPoint(ccp(0, 1));
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(ContinueLayer::menuCallBack));
    menuItem->setTag(tag);
    CCMenu *menu = CCMenu::create(menuItem, NULL);
    menu->setPosition(posititon);
    objective->addChild(menu, 2);
}


void ContinueLayer::updateTimer() {

    if (timer == 0) {
        showGameOver();
        timer = 10;
    }else {
    Utility::playSound(CCString::createWithFormat(kSoundForCounter), 1);
    timerLabel->setString(CCString::createWithFormat("%d", --timer)->getCString());
    }
}

void ContinueLayer::createButton(const char *spriteName, int tag, CCPoint posititon) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(ContinueLayer::menuCallBack));
    menuItem->setTag(tag);
    CCMenu *menu = CCMenu::create(menuItem, NULL);
    menu->setPosition(posititon);
    if (std:: strcmp(spriteName, "btnStar.png") == 0 ) {
        continueLayer->addChild(menu, 2);
        
        float scale = Utility::isIPad() ? 1 : 0.7;
        CCLabelBMFont *labelButton = CCLabelBMFont::create(CCString::createWithFormat("%d", gameLayer->countContinue)->getCString(), kFontChubby, 0);
        labelButton->setPosition(ccp(menu->getPositionX() * 1.05, menu->getPositionY() * 1.04));
        labelButton->setScale(scale);
        continueLayer-> addChild(labelButton, 2);
    } else if (std:: strcmp(spriteName, "btnClose.png") == 0 ) {
        addChild(menu, 2);
    }
}

void ContinueLayer::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    CCMenuItemSprite *sprite = ((CCMenuItemSprite*)(menuItem));
    int tag = sprite->getTag();
                CCDictionary* prms = CCDictionary::create();
    switch (tag) {
        case 1:
            CCLOG("buy stars");
            if (Utility::getTotalStars() >= gameLayer->countContinue ) {
                Utility::playSound(CCString::create(kSoundForContinue), 1);
                Utility::setTotalStars(Utility::getTotalStars()- gameLayer->countContinue);
                gameLayer->hudLayer->starLabel->setString(CCString::createWithFormat("%d", Utility::getTotalStars())->getCString());
                gameLayer->isGameOver = false;
                removeFromParentAndCleanup(true);
                CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(gameLayer, 0, true);
                gameLayer->resumeAllTargets();
            } else {
                timerLabel->setString(CCString::createWithFormat("%d", 10)->getCString());
                stopAllActions();
                continueLayer->setVisible(false);
                buyStarLayer->setVisible(true);
                isContinueLayer = false;
                gameLayer->hudLayer->starLabel->setString(CCString::createWithFormat("%d", Utility::getTotalStars())->getCString());
            }          
            break;
        case 2:
            CCLOG("gameover layer");//button close
            if (isContinueLayer) {
                CCLog("jetpacks are %d", gameLayer->jetPacks);
                Utility::setTotalJetPacks(Utility::getTotalJetPacks() + gameLayer-> jetPacks);
                if (Utility::getAchievementStatus(34) == 1 && Utility::getTotalJetPacks() > 25000) {
                    //achieve 34
                    CCLOG("Jetpack on Fire");
                    Utility::setAchievementStatus(34, 2);
                    Utility::setAchievementStatus(37, 1);
                    
                    //            CCString *idString = CCString::createWithFormat("com.flying.flea.jetpackonfire");
                    CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_JETPACK_ON_FIRE : ACH_IOS_JETPACK_ON_FIRE);
                    CCString *msgString = CCString::createWithFormat("");
                    Utility::unlockAchievemnt(idString, msgString);
                    gameLayer->addFinalAchievementLayer(34);
                }
//                gameLayer->unscheduleAllSelectors();
//                gameLayer->lowerBodyArrayWithGrass->removeAllObjects();
//                gameLayer->upperBodyArrayWithGrass->removeAllObjects();
//                gameLayer->lowerBodyArrayWithoutGrass->removeAllObjects();
//                gameLayer->upperBodyArrayWithoutGrass->removeAllObjects();
//                gameLayer->obstacleArray->removeAllObjects();
//                gameLayer->powerUpArray->removeAllObjects();
//                gameLayer->coinsArray->removeAllObjects();
//                gameLayer->destroyAllBodies();
//                gameLayer->removeLayerObjects();
                showGameOver();
//                gameLayer->hudLayer->removeFromParentAndCleanup(true);
                isContinueLayer = false;
            } else {                
                isContinueLayer = true;
                runTimer();
                continueLayer->setVisible(true);
                buyStarLayer->setVisible(false);
            }
            break;
            
        case 4:
            CCLOG("5 stars");

            prms->setObject(CCString::create("PURCHASE 5 STARS"), "PURCHASE_ITEM");
            SendMessageWithParams(string("startPuchaseFlow"), prms);
                SendMessageWithParams(string("sendFlurryReport"), prms);
            break;
            
        case 5:
            CCLOG("50 stars");
            prms->setObject(CCString::create("PURCHASE 50 STARS"), "PURCHASE_ITEM");
            SendMessageWithParams(string("startPuchaseFlow"), prms);
            SendMessageWithParams(string("sendFlurryReport"), prms);
            break;
            
        case 6:
            CCLOG("200 stars");
            prms->setObject(CCString::create("PURCHASE 200 STARS"), "PURCHASE_ITEM");
            SendMessageWithParams(string("startPuchaseFlow"), prms);
            SendMessageWithParams(string("sendFlurryReport"), prms);
            break;
            
        case 7:
            CCLOG("500 stars");
            prms->setObject(CCString::create("PURCHASE 500 STARS"), "PURCHASE_ITEM");
            SendMessageWithParams(string("startPuchaseFlow"), prms);
            SendMessageWithParams(string("sendFlurryReport"), prms);
            break;
    }
}

void ContinueLayer::updateStarsCount(CCNode *sender, void *data){
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
    int totalStars = Utility::getTotalStars() + starsToAdd;
    Utility::setTotalStars(totalStars);
    labelTotalStars->setString(CCString::createWithFormat("%d", totalStars)->getCString());
    isContinueLayer = true;
    runTimer();
    continueLayer->setVisible(true);
    buyStarLayer->setVisible(false);
    gameLayer->hudLayer->starLabel->setString(CCString::createWithFormat("%d", Utility::getTotalStars())->getCString());
}

void ContinueLayer::showGameOver() {
    stopAllActions();
//    gameLayer->stopAllActions();
    GameOverLayer *gameOverLayer = GameOverLayer::create(gameLayer);
    gameLayer->addChild(gameOverLayer, 4);
    removeFromParentAndCleanup(true);
    gameLayer->hudLayer->removeFromParentAndCleanup(true);
}

void ContinueLayer::runTimer() {
    timer = 10;
     runAction(CCRepeat::create(CCSequence::createWithTwoActions(CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(ContinueLayer::updateTimer))), 12));
}

void ContinueLayer::onEnter() {
    CCLayer::onEnter();
    NDKHelper::AddSelector("StoreSceneSelectors", "updateStarsCount", callfuncND_selector(ContinueLayer::updateStarsCount), this);
}

void ContinueLayer::onExit() {
    NDKHelper::RemoveSelectorsInGroup("StoreSceneSelectors");
    CCLayer::onExit();
}
