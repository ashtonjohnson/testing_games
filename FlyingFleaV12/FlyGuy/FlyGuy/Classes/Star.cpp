//
//  Star.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 20/11/13.
//
//

#include "Star.h"

Star::Star(GameLayer *gLayer, const char* frameName, int powerType, CCPoint position){
    initPowerUp(gLayer, frameName, powerType, position);
}