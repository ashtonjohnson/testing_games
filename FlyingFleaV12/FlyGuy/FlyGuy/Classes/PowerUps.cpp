//
//  PowerUps.cpp
//  FlyGuy
//
//  Created by bakshish on 04/10/13.
//
//

#include "PowerUps.h"
#include "GameLayer.h"
#include "Utility.h"
#include "SoundConstant.h"

using namespace cocos2d;
PowerUps::PowerUps() {
    
}

void PowerUps::initPowerUp(GameLayer *gLayer, const char *frameName, int powerType, CCPoint position){
    gameLayer = gLayer;
    winSize = gameLayer->winSize;
    spriteUserData = new UserData;
    spriteUserData->initWithFrameName(frameName);
    spriteUserData->userDataType = (PowerUpType) powerType;
    spriteUserData->setCollision(false);
    
    static int powerUpTag = kTagPowerUp;
    spriteUserData->setTag(powerUpTag++);
    spriteUserData->virtualUserDataType = kPowerType_Common;
    
   spriteUserData->sprite->setTag(spriteUserData->getTag());
    spriteUserData->sprite->setPosition(position);
    gameLayer->addChild(spriteUserData->sprite, 3);
    spriteUserData->setReadyForDeletion(false);
    if (powerType == kPowerType_SuperRocket || powerType == kPowerType_Star) {
        spriteUserData->sprite-> runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCMoveBy::create(0.6, ccp(0, winSize.height * 0.04)), CCMoveBy::create(0.6, ccp(0, -winSize.height * 0.04)))));
    }
    b2BodyDef bodyDef;
    bodyDef.userData = spriteUserData;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(spriteUserData->sprite->getPositionX()*PTM_RATIO, spriteUserData->sprite->getPositionY()*PTM_RATIO);
    body = gameLayer->world->CreateBody(&bodyDef);
    gameLayer->gb2ShapeCache->addFixturesToBody(body, frameName);
    spriteUserData->sprite->setAnchorPoint(gameLayer->gb2ShapeCache->anchorPointForShape(frameName));
    
}

void PowerUps::actionPerformed(UserData* userData, float delayPowerUp) {
    int i = 0, j = 0, k = 0, l = 0;
  switch (userData->userDataType) {
//    switch (kPowerType_TinyMode) {
        case kPowerType_SpeedBurst:
            i = 1;
            actionPerformedSpeedBurst(delayPowerUp + Utility::getBarsInUpgrades(kPowerUpType_SpeedBurst) + 2);
            break;
        case kPowerType_SuperRocket:
            j = 1;
            actionPerformedSuperRocket(delayPowerUp + Utility::getBarsInUpgrades(kPowerUpType_SuperRocket) + 2);
            break;
        case kPowerType_BubbleShield:
            k = 1;
            actionPerformedBubbleShield(delayPowerUp + Utility::getBarsInUpgrades(kPowerUpType_BubbleShield) + 2);
            break;
        case kPowerType_TinyMode:
            l = 1;
            actionPerformedTinyMode(delayPowerUp + Utility::getBarsInUpgrades(kPowerUpType_TinyMode) + 2);
            break;
           
        case  kPowerType_Star:
            actionPerformedByStar();
            break;
        default:
            break;
    }
    if ((i+j+k+l) == 4 && Utility::getAchievementStatus(35) == 1) {
        //achieve 35
        CCLog("Mr. Conquerer");
        Utility::setAchievementStatus(35, 2);
        Utility::setAchievementStatus(38, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.Mrconquerer");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_MR_CONQUERER : ACH_IOS_MR_CONQUERER);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        gameLayer->addFinalAchievementLayer(35);
    }
}

void PowerUps::actionPerformedBubbleShield(float delayPowerUp) {
    gameLayer->isPowerBubbleShield = true;
    CCSprite *bubbleSprite = CCSprite::createWithSpriteFrameName("bigBubble.png");
    bubbleSprite->setPosition(ccp(gameLayer->character->characterUserData->sprite->getContentSize().width * 0.5, gameLayer->character->characterUserData->sprite->getContentSize().height * 0.5));
    gameLayer->character->characterUserData->sprite->addChild(bubbleSprite, 3, 58);
    gameLayer->character->characterUserData->sprite->runAction(CCSequence::create(CCDelayTime::create(delayPowerUp),(CCBlink::create(1, 10)), CCCallFunc::create(this, callfunc_selector(PowerUps::removeBubbleSprite)), NULL));
}

void PowerUps::removeBubbleSprite() {
    gameLayer->isPowerBubbleShield = false;
    gameLayer->character->characterUserData->sprite->removeChildByTag(58, true);
}

void PowerUps::actionPerformedSpeedBurst(float delayPowerUp) {
    gameLayer->coinsBonusWhilePower = Utility::getBarsInUpgrades(kPowerUpType_SpeedBurst);
    gameLayer->isStrongWallBreak = true;
    gameLayer->isPowerUpActive = true;
    gameLayer->isObstacleAdding = true;
    gameLayer->isMagnetEffectApply = true;
    gameLayer->powerActionTimer(delayPowerUp);
    gameLayer->addStarsParticle();
    gameLayer->character->characterUserData->sprite->runAction(CCSequence::create(CCRotateBy::create(0.3,  360), (CCBlink::create(1, 10)), NULL) );
}

void PowerUps::actionPerformedSuperRocket(float delayPowerUp) {
    gameLayer->isStrongWallBreak = true;
    gameLayer->isPowerUpActive = true;
    gameLayer->isMagnetEffectApply = true;
    gameLayer->powerActionTimer(delayPowerUp);
    gameLayer->addStarsParticle();
   // gameLayer->character->characterSprite->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(PowerUps::addRocketPower)), CCDelayTime::create(delayPowerUp) ,CCCallFunc::create(this, callfunc_selector(PowerUps::removeRocketPower)), NULL));
}

void PowerUps::actionPerformedTinyMode(float delayPowerUp) {
    gameLayer->coinsBonusWhilePower = Utility::getBarsInUpgrades(kPowerUpType_TinyMode);
    CCSprite *charSprite = gameLayer->character->characterUserData->sprite;
    charSprite->setScale(0.7);
    gameLayer->character->shouldShrinked = true;
    gameLayer->isMagnetEffectApply = true;
    gameLayer->character->characterUserData->sprite->runAction(CCSequence::create(CCDelayTime::create(delayPowerUp),CCCallFunc::create(this, callfunc_selector(PowerUps::blinkSpriteDuringPowerEnd)), CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(PowerUps::resetCharSize)), NULL));
}

void PowerUps::actionPerformedByStar() {
    Utility::setTotalStars(Utility::getTotalStars()+1);
    gameLayer->hudLayer->starLabel->setString(CCString::createWithFormat("%d", Utility::getTotalStars())->getCString());
}

void PowerUps::blinkSpriteDuringPowerEnd() {
    if (gameLayer->character != NULL) {
    gameLayer->character->characterUserData->sprite->runAction(CCBlink::create(1, 10));
    }

}

void PowerUps::resetCharSize() {
    Utility::playSound(CCString::create(kSoundForOuch), 1);
    gameLayer->character->characterUserData->sprite->setScale(1);
    gameLayer->isMagnetEffectApply = false;
    gameLayer->character->shouldResetBody = true;
    gameLayer->isTinyMode = false;
    gameLayer->coinsBonusWhilePower = 1;
}

void PowerUps::addRocketPower() {
    gameLayer->character->addCharacterRocketFlame();
}

void PowerUps::removeRocketPower() {
    gameLayer->character->removeCharacterRocketFlame();
}

void PowerUps:: onExit() {
    CC_SAFE_RELEASE_NULL(spriteUserData);
}
