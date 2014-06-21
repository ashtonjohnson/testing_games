//
//  CoinsPattern.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 02/10/13.
//
//

int arr1[2][5]={
    {1,1,1,1,1},
    {1,1,1,1,1}
};

int arr2[3][6]={
    {1,1,1,1},
    {1,0,0,1},
    {1,1,1,1}
};

int arr3[2][5]={
    {1,1,1,1,1},
    {1,1,1,1,1}
    
};
int arr4[3][3]={
    {1,1,1},
    {1,1,1},
    {1,1,1}
};

int arr5[3][5]={
    {0,1,1,1,0},
    {1,0,0,0,1},
    {0,1,1,1,0}
    
};


#define kPositionGap 25
#include "CoinsPattern.h"
#include "Coins.h"
#include "Utility.h"
#include "Obstacle.h"

void CoinsPattern:: createCoin(CCObject *object, CoinData* coinData) {
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    float posX = Utility::randomFloatBetween(winSize.width * 1.25, winSize.width *1.5);
//    float posY = Utility::randomFloatBetween(gameLayer->bottomY+winSize.width * 0.15, gameLayer->topY -winSize.height * 0.15);
//    int spaceGapOfCoins = Utility::isIPad() ? 2 : 1;
    int coinToDisplay = coinsToDisplay();
    const char *coinName = CCString::createWithFormat("coin_%d.png", coinToDisplay-1)->getCString();
    Coins *coins = new Coins;
    coins->createSprite(gameLayer, CCString::create(coinName), ccp(coinData->i,coinData->j), (CoinsType)(200 + coinToDisplay));
    CCString *tag = CCString::createWithFormat("%d",coins->spriteUserData->getTag());
    gameLayer->coinsArray->setObject(coins, tag->getCString());
    CC_SAFE_RELEASE(coins);
    CC_SAFE_RELEASE(coinData);
}

void CoinsPattern::createWithCoins(GameLayer *gLayer) {
    gameLayer = gLayer;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float posX = Utility::randomFloatBetween(winSize.width * 1.25, winSize.width *1.5);
//    float posY = Utility::randomFloatBetween(winSize.height * 0.5, winSize.height * 0.75);
    float posY = Utility::randomFloatBetween(gLayer->bottomY+winSize.width * 0.15, gLayer->topY -winSize.height * 0.15);
    int randomNo = Utility::randomIntBetween(0, 5);
    float delay = 0;
    int spaceGapOfCoins = Utility::isIPad() ? 2 : 1;
        switch (randomNo) {

            case 0:
                for(int i=0;i<2;i++){
                    for(int j=0;j<5;j++){
                        if(arr1[i][j] == 1) {
                           int coinToDisplay = coinsToDisplay();
                            const char *coinName = CCString::createWithFormat("coin_%d.png", coinToDisplay-1)->getCString();
                            Coins *coins = new Coins;
                            coins->createSprite(gLayer, CCString::create(coinName), ccp(posX + j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins), (CoinsType)(200 + coinToDisplay));
                            CCString *tag = CCString::createWithFormat("%d",coins->spriteUserData->getTag());
                            gLayer->coinsArray->setObject(coins, tag->getCString());
//                            CC_SAFE_RELEASE(coins);
                   /*         CoinData *coinData = new CoinData;
                            coinData->i = posX + j * kPositionGap * spaceGapOfCoins;
                            coinData->j = posY + i * kPositionGap * spaceGapOfCoins;
                            delay += 0.01;
//                            createCoin(this, coinData);
                            CCCallFuncND *createCointAction = CCCallFuncND::create(this, callfuncND_selector(CoinsPattern::createCoin), coinData);
                            CCDelayTime *delayTimeAction = CCDelayTime::create(delay);
                            gameLayer->runAction(CCSequence::create(delayTimeAction, createCointAction, NULL)); */
                        }
                    }
                }
                break;
            case 1:
                for(int i=0;i<3;i++){
                    for(int j=0;j<6;j++){
                        if(arr2[i][j] == 1) {
                            int coinToDisplay = coinsToDisplay();
                            const char *coinName = CCString::createWithFormat("coin_%d.png", coinToDisplay-1)->getCString();
                            Coins *coins = new Coins;
                            coins->createSprite(gLayer, CCString::create(coinName), ccp(posX + j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins), (CoinsType)(200 + coinsToDisplay()));
                            CCString *tag = CCString::createWithFormat("%d",coins->spriteUserData->getTag());
                            gLayer->coinsArray->setObject(coins, tag->getCString());
//                            CC_SAFE_RELEASE(coins);
                    /*        CoinData *coinData = new CoinData;
                            coinData->i = i;
                            coinData->j = j;
                            delay += 0.0000;
                            CCCallFuncND *createCointAction = CCCallFuncND::create(this, callfuncND_selector(CoinsPattern::createCoin), coinData);
                            CCDelayTime *delayTimeAction = CCDelayTime::create(delay);
                            gameLayer->runAction(CCSequence::create(delayTimeAction, createCointAction, NULL)); */

                        }
                    }
                }
                break;

            case 2:
                for(int i=0;i<2;i++){
                    for(int j=0;j<5;j++){
                        if(arr3[i][j] == 1) {
                            int coinToDisplay = coinsToDisplay();
                            const char *coinName = CCString::createWithFormat("coin_%d.png", coinToDisplay-1)->getCString();
                            Coins *coins = new Coins;
                            coins->createSprite(gLayer, CCString::create(coinName), ccp(posX + j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins), (CoinsType)(200 + coinsToDisplay()));
                            CCString *tag = CCString::createWithFormat("%d",coins->spriteUserData->getTag());
                            gLayer->coinsArray->setObject(coins, tag->getCString());
//                            CC_SAFE_RELEASE(coins);
                  /*          CoinData *coinData = new CoinData;
                            coinData->i = i;
                            coinData->j = j;
                            delay += 0.0000;
                            CCCallFuncND *createCointAction = CCCallFuncND::create(this, callfuncND_selector(CoinsPattern::createCoin), coinData);
                            CCDelayTime *delayTimeAction = CCDelayTime::create(delay);
                            gameLayer->runAction(CCSequence::create(delayTimeAction, createCointAction, NULL)); */

                        }
                    }
                }

                break;

            case 3:
                posY = Utility::randomFloatBetween(winSize.height * 0.15, winSize.height * 0.2);
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        if(arr4[i][j] == 1) {
                            int coinToDisplay = coinsToDisplay();
                            const char *coinName = CCString::createWithFormat("coin_%d.png", coinToDisplay-1)->getCString();
                            Coins *coins = new Coins;
                            coins->createSprite(gLayer, CCString::create(coinName), ccp(posX + j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins), (CoinsType)(200 + coinsToDisplay()));
                            CCString *tag = CCString::createWithFormat("%d",coins->spriteUserData->getTag());
                            gLayer->coinsArray->setObject(coins, tag->getCString());
//                            CC_SAFE_RELEASE(coins);
                /*            CoinData *coinData = new CoinData;
                            coinData->i = i;
                            coinData->j = j;
                            delay += 0.0000;
                            CCCallFuncND *createCointAction = CCCallFuncND::create(this, callfuncND_selector(CoinsPattern::createCoin), coinData);
                            CCDelayTime *delayTimeAction = CCDelayTime::create(delay);
                            gameLayer->runAction(CCSequence::create(delayTimeAction, createCointAction, NULL));  */

                        }
                    }
                }

                break;

            case 4:
                posY = Utility::randomFloatBetween(winSize.height * 0.15, winSize.height * 0.2);
                for(int i=0;i<3;i++){
                    for(int j=0;j<5;j++){
                        if(arr5[i][j] == 1) {
                            int coinToDisplay = coinsToDisplay();
                            const char *coinName = CCString::createWithFormat("coin_%d.png", coinToDisplay-1)->getCString();
                            Coins *coins = new Coins;
                            coins->createSprite(gLayer, CCString::create(coinName), ccp(posX + j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins), (CoinsType)(200 + coinsToDisplay()));
                            CCString *tag = CCString::createWithFormat("%d",coins->spriteUserData->getTag());
                            gLayer->coinsArray->setObject(coins, tag->getCString());
//                            CC_SAFE_RELEASE(coins);
                   /*         CoinData *coinData = new CoinData;
                            coinData->i = i;
                            coinData->j = j;
                            delay += 0.0000;
                            CCCallFuncND *createCointAction = CCCallFuncND::create(this, callfuncND_selector(CoinsPattern::createCoin), coinData);
                            CCDelayTime *delayTimeAction = CCDelayTime::create(delay);
                            gameLayer->runAction(CCSequence::create(delayTimeAction, createCointAction, NULL)); */

                        }
                    }
                }

                break;
        }
}

int CoinsPattern::coinsToDisplay() {
    int noOfCoinsToUnlock = Utility::getBarsInUpgrades(kPowerUpType_Coins);
    int randomNoForCoin = Utility::randomIntBetween(1, noOfCoinsToUnlock+1);
    if (noOfCoinsToUnlock == 0) {
        randomNoForCoin = 1;
    }
    return randomNoForCoin;
}