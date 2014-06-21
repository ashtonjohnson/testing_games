//
//  Coins.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 02/10/13.
//
//

#include "Coins.h"
#include "Utility.h"
#include "Obstacle.h"
#include <SoundConstant.h>

static int coinTag = kTagCoins;
#define kMaxMoveDistanceiPad        100
#define kMaxMoveDistanceiPhone     50

int Coins:: getMaxMoveDistance() {
	int maxMoveDistance;
	if (Utility:: isIPad) {
		maxMoveDistance = kMaxMoveDistanceiPad;
	}else {
		maxMoveDistance = kMaxMoveDistanceiPhone;
	}
	return maxMoveDistance;
}
//coinBody->ApplyLinearImpulse(b2Vec2(cosf(angle) * 5, sinf(angle) * 5), character->body->GetPosition());
void Coins:: ApplyMagnetPower() {
	float deltaX;
    float deltaY;
    float rotateToAngle;
    CCPoint newPos;
    CCMoveBy *moveAction = NULL;

    CCPoint characterPos = gameLayer->character->characterUserData->sprite->getPosition();
    deltaX = characterPos.x - spriteUserData->sprite->getPositionX();
    deltaY = characterPos.y - spriteUserData->sprite->getPositionY();
    rotateToAngle = atan2(deltaX, deltaY);
    newPos = CCPointMake(getMaxMoveDistance() * cos(CC_DEGREES_TO_RADIANS(90) - rotateToAngle), getMaxMoveDistance() * sin(CC_DEGREES_TO_RADIANS(90) - rotateToAngle));
//    spriteUserData->sprite->runAction(CCRotateTo::create(0.2/0.4, CC_RADIANS_TO_DEGREES(rotateToAngle)));
    moveAction = CCMoveBy::create(0.05, newPos);
    spriteUserData->sprite->runAction(moveAction);
	if (body != NULL) {
		CCCallFunc *followCursorAction = CCCallFunc::create(this, callfunc_selector(Coins::ApplyMagnetPower));
        CCDelayTime *delayTime = CCDelayTime::create(0.1);
        spriteUserData->sprite->runAction(CCSequence::create(delayTime, followCursorAction, NULL));
	}
}


void Coins::createSprite(GameLayer *gLayer, CCString *spriteName, CCPoint position, CoinsType pCoinsType) {
    gameLayer = gLayer;
    
    CCObject *obj;
    Obstacle *obstacleObj;
    float obstaclePosX;
    float obstaclePosY;
    CCARRAY_FOREACH(gLayer->obstacleArray, obj) {
        obstacleObj = (Obstacle*) obj;
        //        obstaclePosX = obstacleObj->spriteUserData->getBody()->GetPosition().x*PTM_RATIO;
        //        obstaclePosY = obstacleObj->spriteUserData->getBody()->GetPosition().y*PTM_RATIO;
        obstaclePosX = obstacleObj->spriteUserData->sprite->getPositionX();
        obstaclePosY = obstacleObj->spriteUserData->sprite->getPositionY();
        CCRect rect = CCRectMake(obstaclePosX - obstacleObj->spriteUserData->sprite->getTextureRect().size.width/2 , obstaclePosY - obstacleObj->spriteUserData->sprite->getTextureRect().size.height/2, obstacleObj->spriteUserData->sprite->getTextureRect().size.width, obstacleObj->spriteUserData->sprite->getTextureRect().size.height);
        
        bool isRectContatinsPoint = rect.containsPoint(CCPoint(position.x, position.y));
        if (isRectContatinsPoint) {
            CCLog("Rect Contains Point");
            position.x += obstacleObj->getContentSize().width * 3;
            //            posY += obstacleObj->getContentSize().height * 3;
        }
    } 
 
    winSize = gameLayer->winSize;
    spriteUserData = new UserData;
    spriteUserData->initWithFrameName(spriteName->getCString());

    spriteUserData->setCollision(false);
    //    character = CCSprite::createWithSpriteFrameName("char_0.png");
    spriteUserData->userDataType = pCoinsType;
    spriteUserData->virtualUserDataType = kCoinsType_Normal;
    spriteUserData->setTag(coinTag++);
    spriteUserData->sprite->setTag(spriteUserData->getTag());
//    gameLayer->coinDictionary->objectForKey(CCString::createWithFormat("%d", spriteUserData->getTag())->getCString());
//    coinTag++;
    b2BodyDef bodyDef;
    bodyDef.userData = spriteUserData;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x/ PTM_RATIO, position.y/PTM_RATIO);
    body = gameLayer->world->CreateBody(&bodyDef);
    
    gameLayer->gb2ShapeCache->addFixturesToBody(body, "coins_0.png");
    spriteUserData->sprite->setAnchorPoint(gameLayer->gb2ShapeCache->anchorPointForShape("coins_0.png"));
//    spriteUserData->setBody(body);
//    spriteUserData->setSprite(sprite);
    spriteUserData->sprite->setPosition(position);
    spriteUserData->setPosition(spriteUserData->sprite->getPosition());
    gameLayer->addChild(spriteUserData->sprite, gameLayer->character->getZOrder(), spriteUserData->getTag());
    spriteUserData->setReadyForDeletion(false);
    
    
  
    
//    winSize = CCDirector::sharedDirector()->getWinSize();
//    gLayer = gLayer;
//    spriteUserData = new UserData;
//    sprite = spriteUserData->initWithFrameName(spriteName->getCString());
//    spriteUserData->userDataType = coinsPatternType;
//    sprite->setPosition(position);
//    spriteUserData->setPosition(sprite->getPosition());
//    gLayer->addChild(sprite, 2);
//    
//    b2BodyDef obsBodyDef;
//    obsBodyDef.userData = spriteUserData;
//    obsBodyDef.type = b2_staticBody;
//    //    obsBodyDef.position.Set(160/PTM_RATIO, 160/PTM_RATIO);
//    b2Body *body = gameLayer->world->CreateBody(&obsBodyDef);
//    gameLayer->gb2ShapeCache->addFixturesToBody(body, spriteName->getCString());
//    sprite->setAnchorPoint(gameLayer->gb2ShapeCache->anchorPointForShape(spriteName->getCString()));

}

void Coins::setDeletionForCoin() {
    spriteUserData->sprite->setPosition(ccp(-55, spriteUserData->sprite->getPositionY()));

}

void Coins::runFinalAnimation(const char *frameName) {
    spriteUserData->sprite->stopAllActions();
    setDeletionForCoin();
}


void Coins::resetCoins() {
//    CCString *key = CCString::createWithFormat("%d", this->spriteUserData->getTag());
//    gameLayer->removeChild(sprite, true);
//    spriteUserData->readyForDeletion = true;
//    gameLayer->removeCoin(this);
//    onExit();
//    gameLayer->coinsArray->removeObjectForKey(key->getCString());
}

void Coins::runAnimation(const char* frameName) {
    shouldApplyMagnet = true;
    //update coin score
    gameLayer->hudLayer->updateCoinScore(++gameLayer->coinScore);
    Utility::playSound(CCString::create(kSoundForCoinCollection), 1);
    if (gameLayer->coinScore == 75 && Utility::getAchievementStatus(1) == 1) {
        //achieve 1
        Utility::setAchievementStatus(1, 2);
        Utility::setAchievementStatus(4, 1);
        
        //        CCString *idString = CCString::createWithFormat("com.flying.flea.goldrush");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_GOLD_RUSH : ACH_IOS_GOLD_RUSH);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        
        gameLayer->addFinalAchievementLayer(1);
    }
    gameLayer->isCharCollidedCoinsPowerUp = true;
    runFinalAnimation(frameName);
}

//void Coins::applyForce(b2Body *otherBody ,float delta, CCSprite  *charSprite) {
//    CCPoint pos = ccp(charSprite->getPositionX() - body->GetPosition().x*PTM_RATIO, charSprite->getPositionY() - body->GetPosition().y*PTM_RATIO);
//	b2Vec2 u12 = b2Vec2(pos.x/PTM_RATIO, Utility::toMeters(pos).Normalize());
//	
//	float32 absDist = b2Distance(Utility::toMeters(charSprite->getPosition()), body->GetPosition());
//	float32 absDistSquare = pow(absDist, 2);
//	float32 multFactor = 1500 * 1500 / absDistSquare;
//	b2Vec2 impulse = b2Vec2(multFactor*u12.x, multFactor*u12.y);
////    cpvmult(u12, multFactor * delta * 60);
////	cpBodyApplyImpulse(otherBody, impulse, cpvzero);
//    body->ApplyLinearImpulse(impulse, b2Vec2_zero);
//}

void Coins::updateBodyPos() {
    b2Vec2 vect = b2Vec2(Utility::toMeters(CCPoint(spriteUserData->getSprite()->getPositionX(),spriteUserData->getSprite()->getPositionY())));
    body->SetTransform(vect, CC_DEGREES_TO_RADIANS(-spriteUserData->getSprite()->getRotation()));
}


void Coins::onExit() {
    CC_SAFE_RELEASE_NULL(spriteUserData);
}
