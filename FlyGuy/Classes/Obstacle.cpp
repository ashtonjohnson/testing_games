//
//  Abstacle.h
//  Speriminator
//
//  Created by Ramesh on 16/09/13.
//
//

#include "Obstacle.h"
#include "GameLayer.h"
#include "Utility.h"
#include "Coins.h"

using namespace cocos2d;
#define Z_ORDER_BG            0

void Obstacle::createSprite(GameLayer *gameLayer, ObstacleType obstacleType, CCString *spriteName, CCPoint position) {    
    winSize = CCDirector::sharedDirector()->getWinSize();
    gLayer = gameLayer;
    
    spriteUserData = new UserData;
    spriteUserData->setCollision(false);
    spriteUserData->initWithFrameName(spriteName->getCString());
    spriteUserData->userDataType = obstacleType;

    CCObject *obj;
    Coins *coinsObj;
    float coinsPosX;
    float coinsPosY;
    if (gLayer->sceneType == kSceneTypeGameScene) {
        CCArray *coinsKeyArray = gameLayer->coinsArray->allKeys();
        CCARRAY_FOREACH(coinsKeyArray, obj) {
            CCString *keyString = (CCString*)obj;
            const char *key = keyString->getCString();
            coinsObj = (Coins*) gLayer->coinsArray->objectForKey(key);
            //        obstaclePosX = obstacleObj->spriteUserData->getBody()->GetPosition().x*PTM_RATIO;
            //        obstaclePosY = obstacleObj->spriteUserData->getBody()->GetPosition().y*PTM_RATIO;
            coinsPosX = coinsObj->spriteUserData->sprite->getPositionX();
            coinsPosY = coinsObj->spriteUserData->sprite->getPositionY();
            CCRect rect = CCRectMake(position.x - spriteUserData->sprite->getTextureRect().size.width/2 , position.y - spriteUserData->sprite->getTextureRect().size.height/2, spriteUserData->sprite->getTextureRect().size.width, spriteUserData->sprite->getTextureRect().size.height);
            
            bool isRectContatinsPoint = rect.containsPoint(CCPoint(coinsPosX, coinsPosY));
            if (isRectContatinsPoint) {
                position.x += coinsObj->spriteUserData->sprite->getContentSize().width;
                //            posY += obstacleObj->getContentSize().height * 3;
            }
        }

    }
    
    isActive = false;
    static int userDataTag = kTagObstacle;
    spriteUserData->sprite->setTag(userDataTag++);
    spriteUserData->setTag(spriteUserData->sprite->getTag());
    spriteUserData->sprite->setPosition(position);
    spriteUserData->virtualUserDataType = kObstacleType_Common;
    gLayer->addChild(spriteUserData->sprite, gLayer->character->getZOrder());
    
    b2BodyDef obsBodyDef;
    obsBodyDef.userData = spriteUserData;
    obsBodyDef.type = b2_dynamicBody;
    body = gameLayer->world->CreateBody(&obsBodyDef);
//    spriteUserData->setBody(body);
    gameLayer->gb2ShapeCache->addFixturesToBody(body, spriteName->getCString());
    spriteUserData->sprite->setAnchorPoint(gameLayer->gb2ShapeCache->anchorPointForShape(spriteName->getCString()));
    isWallMoving = false;
}

void Obstacle::removeWeakWallAnimation() {
    spriteUserData->sprite->setPosition(ccp(-55, spriteUserData->sprite->getPosition().y));
//    gLayer->removeObstacle(this);
//    gLayer->removeChild(spriteUserData->sprite, true);
//    spriteUserData->readyForDeletion = true;
//    onExit();
//    gLayer->obstacleArray->removeObject(this);
}

void Obstacle::updateBodyPos() {
    b2Vec2 vect = b2Vec2(Utility::toMeters(CCPoint(spriteUserData->getSprite()->getPositionX(),spriteUserData->getSprite()->getPositionY())));
    body->SetTransform(vect, CC_DEGREES_TO_RADIANS(-spriteUserData->getSprite()->getRotation()));
}

void Obstacle::onExit() {
    CC_SAFE_RELEASE_NULL(spriteUserData);
}

