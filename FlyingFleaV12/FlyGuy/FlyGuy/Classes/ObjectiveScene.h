//
//  ObjectiveScene.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 23/10/13.
//
//

#ifndef __FlyGuy__ObjectiveScene__
#define __FlyGuy__ObjectiveScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class ObjectiveScene: public CCScene {
public:
    virtual bool init();
    static ObjectiveScene* create();
    
    CCSize winSize;
};

#endif /* defined(__FlyGuy__ObjectiveScene__) */
