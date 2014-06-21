//
//  GreenCoins.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/10/13.
//
//

#ifndef __FlyGuy__GreenCoins__
#define __FlyGuy__GreenCoins__

#include <iostream>
#include "PowerUps.h"

class GreenCoins:public PowerUps {
public:
    GreenCoins(GameLayer *gLayer, const char* frameName, int powerType, CCPoint position);
};
#endif /* defined(__FlyGuy__GreenCoins__) */
