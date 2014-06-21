//
//  SpeedBurst.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/10/13.
//
//

#ifndef __FlyGuy__SpeedBurst__
#define __FlyGuy__SpeedBurst__

#include <iostream>
#include "PowerUps.h"

class SpeedBurst: public PowerUps {
public:
    SpeedBurst(GameLayer *gLayer, const char* frameName, int powerType, CCPoint position);
};
#endif /* defined(__FlyGuy__SpeedBurst__) */
