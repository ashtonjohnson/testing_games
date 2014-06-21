//
//  ContinueLayer.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 28/10/13.
//
//

#ifndef __FlyGuy__ContinueLayer__
#define __FlyGuy__ContinueLayer__

#include <iostream>
#include "cocos2d.h"

class GameLayer;

using namespace cocos2d;

class ContinueLayer: public CCLayer {
public:
    virtual bool init(GameLayer *gLayer);
    static ContinueLayer* create(GameLayer *gLayer);
    
    int timer;
    GameLayer *gameLayer;
    CCSize winSize;
    void createButton(const char *spriteName, int tag, CCPoint posititon);
    void menuCallBack(CCObject *menuItem);
    void addContinueLayer();
    void addBuyStarLayer();
    void updateTimer();
    void runTimer();
    CCLabelBMFont *timerLabel, *continueLabel;
    void showGameOver() ;
    CCLayer *buyStarLayer;
    CCSprite *middleRect;
    CCLayer *continueLayer;
    bool isContinueLayer;
    CCLabelBMFont *labelTotalStars;
    CCLabelBMFont *label, *labelText;
    
    void createSprite(const char *spriteFrameName, CCPoint pos, CCSprite *objective);
    void createLabel(const char *labelName, const char *labelNameValue, CCPoint position, CCSprite *objective);
    void createButton(const char *spriteName, int tag, CCPoint posititon, CCSprite *objective);
    
    void updateCoinsCount(CCNode *sender, void *data);
    void updateStarsCount(CCNode *sender, void *data);
    void onEnter();
    void onExit();
};

#endif /* defined(__FlyGuy__ContinueLayer__) */
