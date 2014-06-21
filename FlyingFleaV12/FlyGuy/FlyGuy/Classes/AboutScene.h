//
//  AboutScene.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 25/10/13.
//
//

#ifndef __FlyGuy__AboutScene__
#define __FlyGuy__AboutScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class AboutScene: public CCScene {
public:
    virtual bool init();
    static AboutScene* create();
    
    CCSize winSize;
};

#endif /* defined(__FlyGuy__AboutScene__) */
