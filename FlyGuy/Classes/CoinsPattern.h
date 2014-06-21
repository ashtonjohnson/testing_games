//
//  CoinsPattern.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 02/10/13.
//
//

#ifndef __FlyGuy__CoinsPattern__
#define __FlyGuy__CoinsPattern__

#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"
#include "Utility.h"
#include "CoinData.h"

using namespace cocos2d;

class CoinsPattern: public CCObject {
public:
    GameLayer *gameLayer;
    void createWithCoins(GameLayer *gLayer);
    int  coinsToDisplay();
    void createCoin(CCObject *object, CoinData *coinData);
    
};
#endif /* defined(__FlyGuy__CoinsPattern__) */
