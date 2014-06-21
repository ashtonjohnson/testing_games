//
//  LevelCompletionScene.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 01/10/13.
//
//

#ifndef __FlyGuy__LevelCompletionScene__
#define __FlyGuy__LevelCompletionScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class LevelCompletionScene: public CCScene {
public:
    virtual bool init();
    static LevelCompletionScene* create();
    
    CCSize winSize;
    void playGame();
};

#endif /* defined(__FlyGuy__LevelCompletionScene__) */
