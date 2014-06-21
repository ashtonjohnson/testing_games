//
//  AboutLayer.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 25/10/13.
//
//

#ifndef __FlyGuy__AboutLayer__
#define __FlyGuy__AboutLayer__

#include <iostream>
#include "cocos2d.h"

class GameLayer;

using namespace cocos2d;

class AboutLayer: public CCLayer {
public:
    virtual bool init();
    static AboutLayer* create();
    CCArray *charMenuIemList;
    CCSize winSize;
    
    void addMenuItems(const char *frameName, int tag);
    void menuCallBack(CCObject *menuItem);
    virtual void  onExit();
    virtual void  onEnter();
};

#endif /* defined(__FlyGuy__AboutLayer__) */
