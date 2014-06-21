//
//  ObstaclePattern.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 17/10/13.
//
//

int obstacleArr1[4][1]={
    {1},
    {0},
    {0},
    {0}
};


int obstacleArr2[4][1]={
    {0},
    {1},
    {0},
    {0}
};


int obstacleArr3[4][1]={
    {0},
    {0},
    {1},
    {0}
};

//weak walls
int obstacleArr4[4][1]={
    {0},
    {0},
    {0},
    {1}
};


int obstacleArr5[4][1]={
    {1},
    {0},
    {0},
    {1}
};

int obstacleArr6[4][1]={
    {0},
    {0},
    {0},
    {1}
};

int obstacleArr7[4][1]={
    {0},
    {0},
    {1},
    {0}
};

int obstacleArr8[5][18]={
    {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1}
};


#define kPositionGap 22

#include "ObstaclePattern.h"
#include "Obstacle.h"
#include "PowerUps.h"
#include "SpeedBurst.h"
#include "Constant.h"

void ObstaclePattern:: addObstacle(GameLayer *gLayer, ObstacleType obstacleType, CCString *name, CCPoint pos, bool isMoving) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    Obstacle *obstacle = new Obstacle;
    obstacle->createSprite(gLayer, obstacleType, name, pos);
    obstacle->isWallMoving = isMoving;
    gLayer->obstacleArray->addObject(obstacle);
    
    if (isMoving) {
        obstacle->spriteUserData->sprite->runAction(CCRepeatForever::create((CCSequence::createWithTwoActions(CCMoveBy::create(1.5, ccp(0, winSize.height * 0.2)), CCMoveBy::create(1.5, ccp(0, -winSize.height * 0.2))))) );
    }
}

void ObstaclePattern:: createWithObstacle(GameLayer *gLayer, bool isObstacleStrong) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float posX = Utility::randomFloatBetween(winSize.width * 1.25, winSize.width * 1.35);
    float posY = Utility::randomFloatBetween(winSize.height * 0.3, winSize.height * 0.5);
    
    int randomNo = Utility::randomIntBetween(0, 8);
    int spaceGapOfCoins = Utility::isIPad() ? 2 : 1;
    ObstacleType obstacleType;
    if (randomNo < 6) {
        obstacleType = kObstacleType_Strong;
    } else {
        obstacleType = kObstacleType_Weak;
    }
    if (gLayer->sceneType == kSceneTypeHelp) {
        if (isObstacleStrong) {
            obstacleType = kObstacleType_Strong;
        } else {
            obstacleType = kObstacleType_Weak;
        }
    }
    if (randomNo == 5 && gLayer->sceneType == kSceneTypeGameScene && !gLayer->isLaneWide) {
        randomNo = 6;
    }
    switch (randomNo) {
        {
        case 0:
            CCPoint pos = CCPoint(posX, posY);
            /*            if (gLayer->disabledObstacleArray->count() > 0) {
             CCLog("Using Old obstacle");
             Obstacle *obstacle = (Obstacle*)gLayer->disabledObstacleArray->lastObject();
             
             obstacle->spriteUserData->setCollision(false);
             gLayer->removeChild(obstacle->spriteUserData->sprite, true);
             obstacle->spriteUserData->sprite = obstacle->spriteUserData->initWithFrameName(CCString::createWithFormat("obstacle_%d.png", obstacle->spriteUserData->userDataType)->getCString());
             gLayer->addChild( obstacle->spriteUserData->sprite, 2);
             obstacle->spriteUserData->sprite->setPosition(pos);
             obstacle->isActive = false;
             obstacle->isWallMoving = false;
             obstacle->body->SetActive(true);
             
             gLayer->disabledObstacleArray->removeObject(obstacle);
             } else { */
            addObstacle(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), pos, true);
            //            }
            //            Obstacle *obstacle = new Obstacle;
            //            obstacle->createSprite(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), CCPoint(posX, posY));
            //            obstacle->spriteUserData->sprite->runAction(CCRepeatForever::create((CCSequence::createWithTwoActions(CCMoveBy::create(1.5, ccp(0, winSize.height * 0.2)), CCMoveBy::create(1.5, ccp(0, -winSize.height * 0.2))))) );
            //            gLayer->obstacleArray->addObject(obstacle);
            //            obstacle->isWallMoving = true;
            //            CC_SAFE_RELEASE(obstacle);
            break;
        }
        case 1:
            for(int i=0;i<4;i++){
                for(int j=0;j<1;j++){
                    if(obstacleArr1[i][j] == 1) {
                        CCPoint pos = ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins);
                        addObstacle(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), pos, false);
                        //                            Obstacle *obstacle = new Obstacle;
                        //                            obstacle->createSprite(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins));
                        //                            gLayer->obstacleArray->addObject(obstacle);
                        //                            CC_SAFE_RELEASE(obstacle);
                        
                    }
                }
            }
            break;
            
        case 2:
            for(int i=0;i<4;i++){
                for(int j=0;j<1;j++){
                    if(obstacleArr2[i][j] == 1) {
                        CCPoint pos = ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins);
                        addObstacle(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), pos, false);
                        
                        //                            Obstacle *obstacle = new Obstacle;
                        //                            obstacle->createSprite(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins));
                        //                            gLayer->obstacleArray->addObject(obstacle);
                        //                            CC_SAFE_RELEASE(obstacle);
                        
                    }
                }
            }
            break;
            
        case 3:
            for(int i=0;i<4;i++){
                for(int j=0;j<1;j++){
                    if(obstacleArr3[i][j] == 1) {
                        CCPoint pos = ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins);
                        addObstacle(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), pos, false);
                        //                            Obstacle *obstacle = new Obstacle;
                        //                            obstacle->createSprite(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins));
                        //                            gLayer->obstacleArray->addObject(obstacle);
                        //                            CC_SAFE_RELEASE(obstacle);
                        
                    }
                }
            }
            break;
            
        case 4:
            for(int i=0;i<4;i++){
                for(int j=0;j<1;j++){
                    if(obstacleArr4[i][j] == 1) {
                        CCPoint pos = ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins);
                        addObstacle(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), pos, false);
                        //                        Obstacle *obstacle = new Obstacle;
                        //                        obstacle->createSprite(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins));
                        //                        gLayer->obstacleArray->addObject(obstacle);
                        //                        CC_SAFE_RELEASE(obstacle);
                        
                    }
                }
            }
            break;
            
        case 5:
            for(int i=0;i<4;i++){
                for(int j=0;j<1;j++){
                    if(obstacleArr5[i][j] == 1) {
                        CCPoint pos = ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins);
                        addObstacle(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), pos, false);
                        //                        Obstacle *obstacle = new Obstacle;
                        //                        obstacle->createSprite(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins));
                        //                        gLayer->obstacleArray->addObject(obstacle);
                        //                        CC_SAFE_RELEASE(obstacle);
                        
                    }
                }
            }
            break;
            
        case 6:
            for(int i=0;i<4;i++){
                for(int j=0;j<1;j++){
                    if(obstacleArr6[i][j] == 1) {
                        CCPoint pos = ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins);
                        addObstacle(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), pos, false);
                        
                        //                        Obstacle *obstacle = new Obstacle;
                        //                        obstacle->createSprite(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins));
                        //                        gLayer->obstacleArray->addObject(obstacle);
                        //                        CC_SAFE_RELEASE(obstacle);
                        
                    }
                }
            }
            break;
            
        case 7:
            for(int i=0;i<4;i++){
                for(int j=0;j<1;j++){
                    if(obstacleArr7[i][j] == 1) {
                        CCPoint pos = ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins);
                        addObstacle(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), pos, false);
                        //                        Obstacle *obstacle = new Obstacle;
                        //                        obstacle->createSprite(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins));
                        //                        gLayer->obstacleArray->addObject(obstacle);
                        //                        CC_SAFE_RELEASE(obstacle);
                    }
                }
            }
            break;
            
            // special case of patterns for an obstacle runs randomly
        case 8:
            obstacleType = kObstacleType_Strong;
            /*     for(int i=0;i<5;i++){
             for(int j=0;j<11;j++){
             if(obstacleArr8[i][j] == 2) {
             //                        PowerUps *powerUp = new SpeedBurst(gLayer,"powerUp_0.png", kPowerType_SpeedBurst, ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins));
             //                            gLayer->powerUpArray->addObject(powerUp);
             }
             if(obstacleArr8[i][j] == 1) {
             Obstacle *obstacle = new Obstacle;
             obstacle->createSprite(gLayer, obstacleType, CCString::createWithFormat("obstacle_%d.png", obstacleType), ccp(posX+ j * kPositionGap * spaceGapOfCoins, posY + i * kPositionGap * spaceGapOfCoins));
             gLayer->obstacleArray->addObject(obstacle);
             }
             }
             } */
            break;
    }
    
}