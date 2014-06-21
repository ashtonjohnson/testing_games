//
//  SuperRocket.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/10/13.
//
//

#ifndef __FlyGuy__SuperRocket__
#define __FlyGuy__SuperRocket__

#include <iostream>
#include "PowerUps.h"

class SuperRocket:public PowerUps {
public:
    SuperRocket(GameLayer *gLayer, const char* frameName, int powerType, CCPoint position);
};
#endif /* defined(__FlyGuy__SuperRocket__) */
