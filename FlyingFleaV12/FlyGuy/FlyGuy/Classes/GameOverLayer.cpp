//
//  GameOverLayer.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 28/10/13.
//
//

#include "GameOverLayer.h"
#include "Constant.h"
#include "Utility.h"
#include "GameLayer.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "NDKHelper.h"
#include "UpgradeScene.h"
#include "NDKHelper.h"
#include "SoundConstant.h"
#include "ScoresScene.h"

GameOverLayer* GameOverLayer::create(GameLayer *gLayer) {
	GameOverLayer * pRet =new GameOverLayer();
    if (pRet && pRet->init(gLayer)) {
        pRet->autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}
bool GameOverLayer:: init(GameLayer *gLayer) {
    if (!CCLayer::init()) {
        return false;
    }
     float scale = Utility::isIPad() ? 1 : 0.7;
    timer = 10;
    winSize = CCDirector::sharedDirector()->getWinSize();
    isScoreUpdated = false;
    CCDictionary* prms = CCDictionary::create();
    prms->setObject(CCString::create("GAME END"), "FLURRY_EVENT");
    SendMessageWithParams(string("sendFlurryReport"), prms);
    
    gameLayer = gLayer;
    starsParticle = NULL;
    isExitCalled = false;
    const char* idHighScore = Utility::isAndroid ? LEAD_HIGH_SCORE : LEAD_IOS_HIGH_SCORE;
    const char* idDistance = Utility::isAndroid ? LEAD_DISTANCE : LEAD_IOS_DISTANCE;
    postOnLeaderBoard(CCString::create(idHighScore), Utility::getTotalScore());
    postOnLeaderBoard(CCString::create(idDistance), Utility::getTotalDistance());
        SendMessageWithParams("setDefaultPlayer", NULL);
    CCLayerColor *colorLayer = CCLayerColor::create(ccc4(50, 50, 50, 100), winSize.width  , winSize.height );
    addChild(colorLayer);
    
    // show chartboost
    Utility::setChartboostTime(Utility::getChartboostTime() + 1);
    if (Utility::getChartboostTime() == 4) {
        Utility::setChartboostTime(0);
        if (!Utility::isAdFreeVersion()) {
            CCDictionary* prms = CCDictionary::create();
            prms->setObject(CCString::create("YES"), kShowChartboostAd);
            SendMessageWithParams(string("shouldDisplayChartboostAd"), prms);
        }
    }
  
    createLabel("", CCString::createWithFormat("%d", Utility::getTotalCoins())->getCString(), CCPoint(winSize.width * 0.04, winSize.height * 0.9));
    CCSprite *coinSprite = CCSprite::createWithSpriteFrameName("coins_0.png");
    coinSprite->setPosition(CCPoint(winSize.width * 0.1, winSize.height * 0.9));
    coinSprite->setAnchorPoint(ccp(1, 0.5));
    addChild(coinSprite);
    
    createLabel("score:", CCString::createWithFormat("%d", Utility::getTotalScore())->getCString(), ccp(winSize.width* 0.485, winSize.height * 0.70));
    createLabel("distance:", CCString::createWithFormat("%d meters", Utility::getTotalDistance())->getCString(), ccp(winSize.width* 0.485, winSize.height * 0.60));
    createLabel("walls smashed:", CCString::createWithFormat("%d", Utility::getTotalWallSmashed())->getCString(), ccp(winSize.width* 0.485, winSize.height * 0.50));
    createLabel("tight squeezes:", CCString::createWithFormat("%d", Utility::getTotalTightSqueezes())->getCString(), ccp(winSize.width* 0.485, winSize.height * 0.40));    
    createLabel("game time:", CCString::createWithFormat("%02dm%02ds", gLayer->minute, gLayer->seconds)->getCString(),ccp(winSize.width* 0.485, winSize.height * 0.30) );
    
    checkForMinScore();
    
    for (int i = 0; i < 3; i++) {
        if (Utility::getTotalScore() > Utility::getPlayerScore(i)) {
            runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCCallFunc::create(this, callfunc_selector(GameOverLayer::addStarsEffect)), CCDelayTime::create(1))));
                Utility::playSound(CCString::create(kSoundForFireworks), 1);
            break;
        }
    }
    
    gameOverLabel = CCLabelBMFont::create("game over", kFontChubby, 0);
    gameOverLabel->setPosition(ccp(winSize.width* 0.5, winSize.height * 0.95));
    gameOverLabel->setScale(scale * 2);
    addChild(gameOverLabel);    
    
    createButton("btnMenu.png", 1, CCPoint(winSize.width * 0.1, winSize.height * 0.1));
    createButton("btnUpgrades.png", 2, CCPoint(winSize.width * 0.7, winSize.height * 0.1));
    createButton("btnNewGame.png", 3, CCPoint(winSize.width * 0.90, winSize.height * 0.1));
    createButton("btnScore.png", 6, CCPoint(winSize.width * 0.5, winSize.height * 0.1));

    achievement23();
    
    CCSprite *sprite = CCSprite::createWithSpriteFrameName ("btnPlus.png");
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(GameOverLayer::menuCallBack));
    menuItem->setTag(5);
    CCMenu *menu = CCMenu::create(menuItem, NULL);
    menu->setPosition(ccp(winSize.width * 0.18, winSize.height * 0.9));
    addChild(menu, 3);
    
    return true;
}

void GameOverLayer::achievement23() {
    if (Utility::getPlayerScore(19) > 10000 && Utility::getAchievementStatus(23) == 1) {
        //achieve 23
        CCLog("fill them up");
        Utility::setAchievementStatus(23, 2);
        Utility::setAchievementStatus(26, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.fillthemup");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_FILL_THEM_UP : ACH_IOS_FILL_THEM_UP);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        gameLayer->addFinalAchievementLayer(23);
    }
}

void GameOverLayer::checkForMinScore() {
     float scale = Utility::isIPad() ? 1 : 0.8;   
    if (Utility::getTotalScore() > Utility::getPlayerScore(19)) {
        CCScale9Sprite *sprite = CCScale9Sprite::createWithSpriteFrameName("boxTransparent.png");
        m_pEditName = CCEditBox::create(CCSize(winSize.width * 0.35, winSize.height * 0.15), sprite);
        m_pEditName->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.77 ));
        m_pEditName->setFontColor(ccWHITE);
        m_pEditName->setFont(kFontChubby, 30);
        m_pEditName->setMaxLength(10);
        m_pEditName->setReturnType(kKeyboardReturnTypeDone);
        
//        const char *playerName = Utility::getPlayerName(0)->getCString();
        const char *playerName = CCString::createWithFormat("%s",CCUserDefault::sharedUserDefault()->getStringForKey(kKeyForDefaultPlayerName).c_str() )->getCString();
        if (std:: strcmp(playerName, "(null)") == 0) {
            playerName = "player";
        }
        if (Utility::isAndroid) {
            playerName = "player";
        }
//         =   CCUserDefault::sharedUserDefault()->getStringForKey(kKeyForDefaultPlayerName);
        m_pEditName->setPlaceHolder(playerName);
        m_pEditName->setText(playerName);
        m_pEditName->setPlaceholderFontColor(ccWHITE);
        addChild(m_pEditName, 200);
        
        CCLabelBMFont *changeNameLabel = CCLabelBMFont::create("[change]", kFontChubby, 0);
        changeNameLabel->setScale(scale);
        CCMenuItemLabel *changeNameItem = CCMenuItemLabel::create(changeNameLabel, this, menu_selector(GameOverLayer::menuCallBack));
        changeNameItem->setTag(4);
        CCMenu *changeNameMenu = CCMenu::create(changeNameItem, NULL);
        float changeLabelPos = Utility::isIPad() ? 0.6 : 1.3;
        changeNameMenu->setPosition(ccp(m_pEditName->getContentSize().width * changeLabelPos, m_pEditName->getContentSize().height * 0.5));
        m_pEditName->addChild(changeNameMenu, 2);
    }
    
}

void GameOverLayer::postOnLeaderBoard(CCString *leaderBoardID,int leaderbrdScore){
    CCDictionary* prms = CCDictionary::create();
    prms->setObject(leaderBoardID, "leaderBoardId");
    CCString *leader = CCString::createWithFormat("%d",leaderbrdScore);
    prms->setObject(leader,"score");
    SendMessageWithParams(string("submitScore"), prms);
}

void GameOverLayer::addStarsEffect() {
    if (starsParticle != NULL) {
    removeChild(starsParticle, true);
    }
        float posX = Utility::randomFloatBetween(winSize.width * 0.3, winSize.width * 0.7);
        float posY = Utility::randomFloatBetween(winSize.height * 0.3, winSize.height * 0.7);
        starsParticle = CCParticleSystemQuad::create("finishStars.plist");
        starsParticle->setPosition(ccp(posX,posY));
        addChild(starsParticle, 1);
}
void GameOverLayer::createLabel(const char *labelName, const char *labelNameValue, CCPoint position) {
    float scale = Utility::isIPad() ? 1 : 0.6;
    label = CCLabelBMFont::create(labelName, kFontChubby, 0);
    label->setPosition(position);
    label->setScale(scale);
    label->setAnchorPoint(ccp(1, 0.5));
    addChild(label, 10);
    labelText = CCLabelBMFont::create(labelNameValue, kFontChubby, 0);
    labelText->setPosition(ccp(label->getPositionX() + winSize.width * 0.02, label->getPositionY()));
    labelText->setScale(scale);
    labelText->setAnchorPoint(ccp(0, 0.5));
    addChild(labelText, 10);
}

void GameOverLayer::createButton(const char *spriteName, int tag, CCPoint posititon) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(GameOverLayer::menuCallBack));
    menuItem->setTag(tag);
    CCMenu *menu = CCMenu::create(menuItem, NULL);
    menu->setPosition(posititon);
    addChild(menu, 2);
}

void GameOverLayer::disableAllButton() {

}


void GameOverLayer::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    CCMenuItemSprite *sprite = ((CCMenuItemSprite*)(menuItem));
    int tag = sprite->getTag();
    if (!isExitCalled) {
        switch (tag) {
            case 1:
                CCLOG("menus");
                isExitCalled = true;
                CCDirector::sharedDirector()->replaceScene(MainMenuScene::create());
                break;
            case 2:
                CCLOG("upgrade");
                isExitCalled = true;
                CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_Powerups));
                break;
                
            case 3:
                CCLOG("new game");
                isExitCalled = true;
                CCDirector::sharedDirector()->replaceScene(GameScene::create(kSceneTypeGameScene));
                break;
                
            case 4:
                CCLOG("open keyboard");
                m_pEditName->touchDownAction(this, 0);
                break;
            case 5:
                CCLOG("coins ");
                isExitCalled = true;
                CCDirector::sharedDirector()->replaceScene(UpgradeScene::create(kObjectiveStatus_CoinStars));
                break;
            case 6:
                CCLOG("coins ");
                isExitCalled = true;
                if (m_pEditName != NULL) {
                    const char *text = m_pEditName->getText();
                    Utility::updateScores(Utility::getTotalScore(), text);
                    isScoreUpdated = true;
                }
                CCDirector::sharedDirector()->replaceScene(ScoresScene::create());
                break;
        }
 
    }
}

void GameOverLayer::onEnter() {
    CCLayer::onEnter();
}

void GameOverLayer::onExit() {
    if (m_pEditName != NULL && !isScoreUpdated) {
        const char *text = m_pEditName->getText();
        Utility::updateScores(Utility::getTotalScore(), text);
    }
    CCLayer::onExit();
}
