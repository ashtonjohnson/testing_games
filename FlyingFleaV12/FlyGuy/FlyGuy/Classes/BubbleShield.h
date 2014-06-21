//
//  BubbleShield.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/10/13.
//
//

#ifndef __FlyGuy__BubbleShield__
#define __FlyGuy__BubbleShield__

#include <iostream>
#include "PowerUps.h"

class BubbleShield:public PowerUps {
public:
    BubbleShield(GameLayer *gLayer, const char* frameName, int powerType, CCPoint position);
};
#endif /* defined(__FlyGuy__BubbleShield__) */
