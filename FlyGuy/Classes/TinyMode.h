//
//  TinyMode.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/10/13.
//
//

#ifndef __FlyGuy__TinyMode__
#define __FlyGuy__TinyMode__

#include <iostream>
#include "cocos2d.h"
#include "PowerUps.h"
#include "GameLayer.h"

using namespace cocos2d;

class TinyMode : public PowerUps{
public:
    TinyMode(GameLayer *gLayer, const char* frameName, int powerType, CCPoint position);
    void runPower();
};

#endif /* defined(__FlyGuy__TinyMode__) */
