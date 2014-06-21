//
//  GameOverScene.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 28/10/13.
//
//

#ifndef __FlyGuy__GameOverScene__
#define __FlyGuy__GameOverScene__

#include <iostream>
#include "cocos2d.h"

class GameLayer;

using namespace cocos2d;

class GameOverScene: public CCScene {
public:
    virtual bool init();
    static GameOverScene* create();
    
    int timer;
    
    CCSize winSize;
    void createButton(const char *spriteName, int tag, CCPoint posititon);
    void menuCallBack(CCObject *menuItem);
    CCLabelBMFont *timerLabel, *continueLabel;
};
#endif /* defined(__FlyGuy__GameOverScene__) */
