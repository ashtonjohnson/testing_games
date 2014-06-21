//
//  Star.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 20/11/13.
//
//

#ifndef __FlyGuy__Star__
#define __FlyGuy__Star__

#include <iostream>
#include "PowerUps.h"

class Star: public PowerUps {
public:
    Star(GameLayer *gLayer, const char* frameName, int powerType, CCPoint position);
};
#endif /* defined(__FlyGuy__Star__) */
