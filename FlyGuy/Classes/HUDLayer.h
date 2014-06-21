//
//  HUDLayer.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 19/10/13.
//
//

#ifndef __FlyGuy__HUDLayer__
#define __FlyGuy__HUDLayer__

#include <iostream>
#include "cocos2d.h"
#include "Constant.h"

class GameLayer;

using namespace cocos2d;

class HUDLayer: public CCLayer {
public:
    virtual bool init(GameLayer *glayer);
    virtual void onExit();
    static HUDLayer* create(GameLayer *glayer);
    
    void addMenuItems(const char *frameName, int tag);
    void menuCallBack(CCObject *menuItem);
    
    CCSize winSize;
    GameLayer *gameLayer;
    CCArray *charMenuIemList;
    CCLabelBMFont *scoreLabel;
    CCLabelBMFont *coinLabel;
    void updateScore(int score);
    void updateCoinScore(int coinScore);
    CCMenu *pauseBtnMenu;
    void pauseScreen();
    CCSprite *coinLabelSprite;
    void getExtrasSpriteName(ExtrasType extrasType);
    const char *extraSpriteName;
    CCProgressTimer *progressTimer;
    CCLabelBMFont *starLabel;
};

#endif /* defined(__FlyGuy__HUDLayer__) */
