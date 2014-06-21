//
//  ScoresScene.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/11/13.
//
//

#ifndef __FlyGuy__ScoresScene__
#define __FlyGuy__ScoresScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class ScoresScene: public CCScene {
public:
    virtual bool init();
    static ScoresScene* create();
    
    CCSize winSize;
};

#endif /* defined(__FlyGuy__ScoresScene__) */
