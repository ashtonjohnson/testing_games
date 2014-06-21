//
//  TinyMode.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/10/13.
//
//

#include "TinyMode.h"
#include "GameLayer.h"
#include "PowerUps.h"

TinyMode::TinyMode(GameLayer *gLayer, const char* frameName, int powerType, CCPoint position){
    initPowerUp(gLayer, frameName, powerType, position);
}

void TinyMode::runPower() {
    gameLayer->character->characterUserData->sprite->setScale(0.5);
}