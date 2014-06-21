//
//  SpeedBurst.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/10/13.
//
//

#include "SpeedBurst.h"

SpeedBurst::SpeedBurst(GameLayer *gLayer, const char* frameName, int powerType, CCPoint position){
    initPowerUp(gLayer, frameName, powerType, position);
}