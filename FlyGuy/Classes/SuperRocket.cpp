//
//  SuperRocket.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/10/13.
//
//

#include "SuperRocket.h"

SuperRocket::SuperRocket(GameLayer *gLayer, const char* frameName, int powerType, CCPoint position){
    initPowerUp(gLayer, frameName, powerType, position);
}