//
//  ScoresLayer.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/11/13.
//
//

#include "ScoresLayer.h"
#include "Constant.h"
#include "Utility.h"
#include "MainMenuScene.h"
#include "NDKHelper.h"
#include "CCEditBox.h"
#include "SoundConstant.h"
using namespace cocos2d::extension;

ScoresLayer* ScoresLayer::create() {
	ScoresLayer * pRet =new ScoresLayer();
    if (pRet && pRet->init()) {
        pRet->autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}
bool ScoresLayer:: init() {
    if (!CCLayer::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();   
    
    float scale = Utility::isIPad() ? 1 : 0.6;
    CCLabelBMFont *scoreLabel = CCLabelBMFont::create("score", kFontChubby, 0);
    CCMenuItemLabel *scoreMenuItem = CCMenuItemLabel::create(scoreLabel, this, menu_selector(ScoresLayer::menuCallBack));
    scoreMenuItem->setScale(scale);
    scoreMenuItem->setTag(0);
    
    CCLabelBMFont *statLabel = CCLabelBMFont::create("stat", kFontChubby, 0);
    CCMenuItemLabel *statMenuItem = CCMenuItemLabel::create(statLabel, this, menu_selector(ScoresLayer::menuCallBack));
    statMenuItem->setTag(1);
    statMenuItem->setScale(scale);
    
    CCLabelBMFont *labelSlash = CCLabelBMFont::create("/", kFontChubby, 0);
    labelSlash->setScale(scale);
    labelSlash->setPosition(ccp(winSize.width * 0.16, winSize.height * 0.9));
    addChild(labelSlash, 10);
    
    CCMenu *menu = CCMenu::create(scoreMenuItem, statMenuItem, NULL);
    menu->setPosition(ccp(winSize.width * 0.15, winSize.height * 0.9));
    menu->alignItemsHorizontallyWithPadding(winSize.width * 0.02);
    addChild(menu, 10);
    
    createButton("btnBack.png", 2, ccp(winSize.width * 0.1, winSize.height * 0.1), this);
//    createButton("btnRefresh.png", 3, ccp(winSize.width * 0.5, winSize.height * 0.1), this);
    createButton("btnGameCenterAchievemnts.png", 4, ccp(winSize.width * 0.7, winSize.height * 0.1), this);
    createButton("btnGameCenterLeaderboards.png", 5, ccp(winSize.width * 0.9, winSize.height * 0.1), this);
    addScoreLayer();
    addStatLayer();
    colorLayerStats->setVisible(false);
    
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("btnRefresh.png");
    menuItemRefresh = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(ScoresLayer::menuCallBack));
    menuItemRefresh->setTag(3);
    CCMenu *menuRefresh = CCMenu::create(menuItemRefresh, NULL);
    menuRefresh->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.1));
    addChild(menuRefresh, 2);
    
    //Just for testing
//    Utility::setTotalCoins(10000);
//    Utility::setTotalStars(10000);
    return  true;
}

void ScoresLayer::addScoreLayer() {
colorLayerScore = CCLayerColor::create(ccc4(50, 50, 50, 100), winSize.width  , winSize.height);
//    createButton("btnChallenges.png", 6, ccp(winSize.width * 0.9, winSize.height * 0.9), colorLayerScore);
    
    float scale = Utility::isIPad() ? 1 : 0.6;
    CCLabelBMFont *labelHead = CCLabelBMFont::create("local scores", kFontChubby, 0);
    labelHead->setScale(scale);
    labelHead->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.9));
    colorLayerScore->addChild(labelHead);
    
    for (int i = 0; i < 20; i++) {
                const char *indexValue = CCString::createWithFormat("%d. ", i+1)->getCString();
        const char *score = (Utility::getPlayerScore(i)!=0)? CCString::createWithFormat("%d",  Utility::getPlayerScore(i))->getCString():"--";
        const char *playerName = (Utility::getPlayerScore(i)!=0)? Utility::getPlayerName(i)->getCString():"--";
        float xMultiplier = 0.15;
        float startY = winSize.height * 0.8 - i * winSize.height * 0.06;
        if(i >= 10){
            xMultiplier = 0.6;
            startY = winSize.height * 0.8 - (i-10) * winSize.height * 0.06;
        }
        if (i < 3) {
            CCSprite *iconRibbon = CCSprite::createWithSpriteFrameName(CCString::createWithFormat("iconRibbon_%d.png", i)->getCString());
            iconRibbon->setPosition(ccp(winSize.width * xMultiplier * 0.7, startY * 0.99));
            colorLayerScore->addChild(iconRibbon);
        }

        createLabelsForScores(indexValue , score, playerName, ccp(winSize.width * xMultiplier, startY), colorLayerScore);
    }
    addChild(colorLayerScore, 1);
}

void ScoresLayer::addStatLayer() {
    colorLayerStats = CCLayerColor::create(ccc4(50, 50, 50, 100), winSize.width  , winSize.height );
    createButton("btnResetAll.png", 7, ccp(winSize.width * 0.9, winSize.height * 0.9), colorLayerStats);
    
    float scale = Utility::isIPad() ? 1 : 0.6;
    CCLabelBMFont *labelHead = CCLabelBMFont::create("local stats", kFontChubby, 0);
    labelHead->setScale(scale);
    labelHead->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.9));
    colorLayerStats->addChild(labelHead);
    
    int longestGame = Utility::getLongestGame();
    int min = longestGame / 60;
    int sec = longestGame % 60;
    const char *longestGamePlayed = CCString::createWithFormat("%02d:%02d", min, sec)->getCString();
    
    const char *longestDistance =  CCString::createWithFormat("%d", Utility::getLongestDistance())->getCString();
    const char *mostWallSmashed =  CCString::createWithFormat("%d", Utility::getMostWallSmashed())->getCString();
    const char *mostTightSqueezes =  CCString::createWithFormat("%d", Utility::getMostTightSqueezes())->getCString();
    
    const char *totalGamesPlayed =  CCString::createWithFormat("%d", Utility::getTotalGamesPlayed())->getCString();
    const char *totalWallsSmashed =  CCString::createWithFormat("%d", Utility::getTotalWallSmashedLifeTime())->getCString();
    const char *totalTightSqueezes =  CCString::createWithFormat("%d", Utility::getTotalTightSqueezesLifeTime())->getCString();
    
    createLabelForStats("in one game:", "", ccp(winSize.width * 0.3, winSize.height * 0.8), colorLayerStats);
    createLabelForStats("longest distance:", longestDistance, ccp(winSize.width * 0.55, winSize.height * 0.74), colorLayerStats);
    createLabelForStats("most walls smashed:", mostWallSmashed, ccp(winSize.width * 0.55, winSize.height * 0.68), colorLayerStats);
    createLabelForStats("most tight squeezes:", mostTightSqueezes, ccp(winSize.width * 0.55, winSize.height * 0.62), colorLayerStats);
    createLabelForStats("longest game:", longestGamePlayed, ccp(winSize.width * 0.55, winSize.height * 0.56), colorLayerStats);
    
    createLabelForStats("in lifetime:", "", ccp(winSize.width * 0.3, winSize.height * 0.48), colorLayerStats);
    createLabelForStats("total games played:", totalGamesPlayed, ccp(winSize.width * 0.55, winSize.height * 0.42), colorLayerStats);
    createLabelForStats("total walls smashed:", totalWallsSmashed, ccp(winSize.width * 0.55, winSize.height * 0.36), colorLayerStats);
    createLabelForStats("total tight squeezes:", totalTightSqueezes, ccp(winSize.width * 0.55, winSize.height * 0.30), colorLayerStats);
//    createLabelForStats(":", "--", ccp(winSize.width * 0.25, winSize.height * 0.26), colorLayerStats);
    
    addChild(colorLayerStats, 1);
}

void ScoresLayer::createButton(const char *spriteName, int tag, CCPoint posititon, CCLayer *layer) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(ScoresLayer::menuCallBack));
    menuItem->setTag(tag);
    CCMenu *menu = CCMenu::create(menuItem, NULL);
    menu->setPosition(posititon);
    layer->addChild(menu, 2);
}

void ScoresLayer::createLabelsForScores(const char *indexValue, const char *labelName, const char *labelNameValue, CCPoint position, CCLayerColor *layer) {
    float scale = Utility::isIPad() ? 1 : 0.6;
    labelIndex = CCLabelBMFont::create(indexValue, kFontChubby, 0);
    labelIndex->setPosition(position);
    labelIndex->setScale(scale);
    layer-> addChild(labelIndex, 10);
    
    labelScore = CCLabelBMFont::create(labelName, kFontChubby, 0);
    labelScore->setPosition(ccp(labelIndex->getPositionX() + winSize.width * 0.06, labelIndex->getPositionY()));
    labelScore->setScale(scale);
    layer-> addChild(labelScore, 10);
    
    labelPlayerName = CCLabelBMFont::create(labelNameValue, kFontChubby, 0);
    labelPlayerName->setPosition(ccp(labelScore->getPositionX() + winSize.width * 0.14, labelScore->getPositionY()));
    labelPlayerName->setScale(scale);
    layer->addChild(labelPlayerName, 10);
}

void ScoresLayer::createLabelForStats(const char *labelText, const char *labelValue, CCPoint position, CCLayerColor *layer) {
    float scale = Utility::isIPad() ? 1 : 0.6;
    label1 = CCLabelBMFont::create(labelText, kFontChubby, 0);
    label1->setPosition(position);
    label1->setScale(scale);
    label1->setAnchorPoint(ccp(1, 0.5));
    layer-> addChild(label1, 10);
    
    label2 = CCLabelBMFont::create(labelValue, kFontChubby, 0);
    label2->setPosition(label1->getPositionX() + winSize.width * 0.025, position.y);
    label2->setScale(scale);
    label2->setAnchorPoint(ccp(0, 0.5));
    layer-> addChild(label2, 10);

}
void ScoresLayer::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    CCMenuItemSprite *sprite = ((CCMenuItemSprite*)(menuItem));
    int tag = sprite->getTag();
    switch (tag) {
            
        case 0:
            CCLog("score label");
//            addScoreLayer();
            colorLayerScore->setVisible(true);
            colorLayerStats->setVisible(false);
            break;
        case 1:
            CCLog("stat label");
            colorLayerScore->setVisible(false);
            colorLayerStats->setVisible(true);
//            addStatLayer();
            break;
        case 2:
            CCLOG("back button");
            CCDirector::sharedDirector()->replaceScene(MainMenuScene::create());
            break;
            
        case 3:
            CCLOG("refresh button");
            postOnLeaderBoard(CCString::create("com.flying.flea.highscore"), Utility::getPlayerScore(0));
            menuItemRefresh->runAction(CCFadeOut::create(1));           
            break;
        case 4:
            CCLOG("gc achieve button");
                SendMessageWithParams(string("achievementController"), NULL);
            break;
        case 5:
            CCLOG("gc leader button");
                SendMessageWithParams(string("leaderBoardController"), NULL);            
            break;
        case 6:
            CCLOG("challenge");
            break;
        case 7:
            CCLOG("reset all");            
            resetAllStats();
//            removeChild(colorLayerStats, true);
//            addStatLayer();
            break;
            
        default:
            break;
    }    
}

void ScoresLayer::postOnLeaderBoard(CCString *leaderBoardID,int leaderbrdScore){
    CCDictionary* prms = CCDictionary::create();
    prms->setObject(leaderBoardID, "leaderBoardId");
    CCString *leader = CCString::createWithFormat("%d",leaderbrdScore);
    prms->setObject(leader,"score");
    SendMessageWithParams(string("submitScore"), prms);
}

void ScoresLayer::resetAllStats() {
    CCDictionary* prms = CCDictionary::create();
    prms->setObject(CCString::createWithFormat("%s", kResetScoreTitle), "title");
    prms->setObject(CCString::createWithFormat("%s", kResetScoreText), "message");
    prms->setObject(CCString::create("Yes, Reset"), "button0");
    if (Utility::isAndroid) {
        prms->setObject(CCString::create(""), "button1");
    }
    prms->setObject(CCString::create("Cancel"), "button2");
    prms->setObject(CCString::create("scoreScreen"), "callFromScreen");
  SendMessageWithParams(string("showNotEnoughCoinsDialogue"), prms);
//    Utility::setLongestGame(0, 0);
//    Utility::setLongestDistance(0);
//    CCLog("dist %d",Utility::getLongestDistance());
//    Utility::setMostWallSmashed(0);
//    Utility::setMostTightSqueezes(0);
//    Utility::setTotalGamesPlayed(0);
//    Utility::setTotalWallSmashedLifeTime(0);
//    Utility::setTotalTightSqueezesLifeTime(0);
}

void ScoresLayer::replaceWithMainMenuScreen() {
    Utility::resetAllUserDefault();
    CCDirector::sharedDirector()->replaceScene(MainMenuScene::create());
}

void ScoresLayer::onEnter(){
    CCLayer::onEnter();
    if (!Utility::isAdFreeVersion()) {
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("YES"), kShowChartboostAd);
        SendMessageWithParams(string("shouldDisplayChartboostAd"), prms);
    }
    NDKHelper::AddSelector("scoreScreenSelector", "replaceWithMainMenuScreen", callfuncND_selector(ScoresLayer::replaceWithMainMenuScreen), this);
}

void ScoresLayer::onExit(){
    CCLayer::onExit();
    this->removeAllChildrenWithCleanup(true);
    NDKHelper::RemoveSelectorsInGroup("scoreScreenSelector");
    //    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LevelSelectionScene.plist");
}
