//
//  AboutLayer.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 25/10/13.
//
//

#include "AboutLayer.h"
#include "MainMenuScene.h"
#include "NDKHelper.h"
#include "Constant.h"
#include "SoundConstant.h"
#include "Utility.h"

AboutLayer* AboutLayer::create() {
	AboutLayer * pRet =new AboutLayer();
    if (pRet && pRet->init()) {
        pRet->autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}
bool AboutLayer:: init() {
    if (!CCLayer::init()) {
        return false;
    }
    charMenuIemList = new CCArray;
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor *colorLayer = CCLayerColor::create(ccc4(50, 50, 50, 100), winSize.width  , winSize.height );
    addChild(colorLayer);
    
    addMenuItems("btnFacebook.png", 1);
    addMenuItems("btnFeedback.png", 2);
        float scale = Utility::isIPad() ? 1 : 0.5;
    CCMenu *btnMenu = CCMenu::createWithArray(charMenuIemList);
    btnMenu->alignItemsHorizontallyWithPadding(winSize.width * 0.1);
    btnMenu->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.75));
    addChild(btnMenu, 2);

    CCSprite *moreBtnSprite = CCSprite::createWithSpriteFrameName("btnMoreGames.png");
    CCMenuItemSprite *moreGameItem = CCMenuItemSprite::create(moreBtnSprite, moreBtnSprite, this, menu_selector(AboutLayer::menuCallBack));
    moreGameItem->setTag(4);
    CCMenu *moreGameMenu = CCMenu::create(moreGameItem, NULL);
    moreGameMenu->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.89));
    addChild(moreGameMenu, 2);
    
    CCLabelBMFont *labelAvalanche = CCLabelBMFont::create("Avalanche Mountain Apps", kFontChubby, 0);
    labelAvalanche->setScale(scale);
    labelAvalanche->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    addChild(labelAvalanche, 2);
    
    CCLabelBMFont *labelLinkAvalanche = CCLabelBMFont::create("www.avalanchemountainapps.com", kFontChubby, 0);
    labelLinkAvalanche->setScale(scale);
    CCMenuItemLabel *linkAvalancheItem = CCMenuItemLabel::create(labelLinkAvalanche, this, menu_selector(AboutLayer::menuCallBack));
    float delta = Utility::isIPad() ? 0.25 : 0.5;
    linkAvalancheItem->setPosition(ccp(winSize.width * delta, winSize.height * 0.4));
    linkAvalancheItem->setPosition(ccp(winSize.width * 0.25, winSize.height * 0.4));
    linkAvalancheItem->setTag(5);
    CCMenu *linkAvalancheMenu = CCMenu::create(linkAvalancheItem, NULL);
    addChild(linkAvalancheMenu, 2);
    linkAvalancheMenu->setPosition(ccp(winSize.width * delta, winSize.height * 0));
    
    //add back button
    CCSprite *backBtnSprite = CCSprite::createWithSpriteFrameName("btnBack.png");
    CCMenuItemSprite *backMenuItem = CCMenuItemSprite::create(backBtnSprite, backBtnSprite, this, menu_selector(AboutLayer::menuCallBack));
    backMenuItem->setTag(3);
    CCMenu *backBtnMenu = CCMenu::create(backMenuItem, NULL);
    backBtnMenu->setPosition(ccp(winSize.width * 0.8, winSize.height * 0.1));
    addChild(backBtnMenu, 2);

    
    return true;
}

void AboutLayer::addMenuItems(const char *frameName, int tag) {
    CCSprite *charSprite = CCSprite::createWithSpriteFrameName(frameName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(charSprite, charSprite, this, menu_selector(AboutLayer::menuCallBack));
    menuItem->setTag(tag);
    charMenuIemList->addObject(menuItem);
}

void AboutLayer::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    CCMenuItemSprite *sprite = ((CCMenuItemSprite*)(menuItem));
    int tag = sprite->getTag();
    switch (tag) {
        case 1:{
            int score = Utility::getTotalScore();
            CCDictionary* prms = CCDictionary::create();
            prms->setObject(CCString::createWithFormat("%d", score), "CurrentScore");
            SendMessageWithParams(string("initiateFacebookLogin"), prms);
        }
            break;
        case 2:{
            CCDictionary* prms = CCDictionary::create();
            prms->setObject(CCString::createWithFormat("%s", kEmailTo), "MailTo");
            prms->setObject(CCString::createWithFormat("%s", kEmailSubject), "Subject");
            SendMessageWithParams(string("sendFeedbackByMail"), prms);
            break;
        }
        case 3:
            CCDirector::sharedDirector()->replaceScene(MainMenuScene::create());
            break;
            
        case 4:{
            CCDictionary* prms = NULL;
            SendMessageWithParams(string("showMoreApps"), prms);
        }
            break;
        case 5:{
                SendMessageWithParams(string("postToAvalanche"), NULL);
            }
            break;
            
        default:
            break;
    }
    
}

void AboutLayer::onEnter(){
    CCLayer::onEnter();
    if (!Utility::isAdFreeVersion()) {
        CCDictionary* prms = CCDictionary::create();
        prms->setObject(CCString::create("YES"), kShowChartboostAd);
        SendMessageWithParams(string("shouldDisplayChartboostAd"), prms);
    }
    
}

void AboutLayer:: onExit() {
    CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
    this->removeAllChildrenWithCleanup(true);
    this->stopAllActions();
    this->unscheduleAllSelectors();
    //    obstacleArray->removeAllObjects();
    CCLayer::onExit();
}

