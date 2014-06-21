//
//  LevelCompletionScene.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 01/10/13.
//
//

#ifndef __FlyGuy__MainMenuScene__
#define __FlyGuy__MainMenuScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class MainMenuScene: public CCScene {
public:
    virtual bool init();
    static MainMenuScene* create();
    void addMenuItems(const char *frameName, int tag);
    void menuCallBack(CCObject *menuItem);
    CCSize winSize;
    void playGame();
    CCArray *charMenuIemList;
    CCLabelTTF *label;
    virtual void onEnter();
    virtual void onExit();
    void showChartBoost();
};

#endif /* defined(__FlyGuy__LevelCompletionScene__) */
