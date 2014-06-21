//
//  Extras.cpp
//  FlyGuy
//
//  Created by Upkesh Thakur on 17/10/13.
//
//

#include "Extras.h"
#include "Constant.h"
#include "Utility.h"


void Extras::initWithExtras(GameLayer *gLayer, ExtrasType extraType) {
    gameLayer = gLayer;
    switch (extraType) {
        case kExtrasType_MysteryBox:
            performedMysteryBox();
            break;
            
        case kExtrasType_RocketSpecial:
            performedRocketspecial();
            gameLayer->hudLayer->progressTimer->setSprite(CCSprite::createWithSpriteFrameName("iconSuperRocket.png"));

            break;
            
        case kExtrasType_ExtraLifeSpecial:
            performedExtraLifeSpecial();
            gameLayer->hudLayer->progressTimer->setSprite(CCSprite::createWithSpriteFrameName("iconExtraLife.png"));
            break;
            
        case kExtrasType_BrokenWallSpecial:
            performedBrokenWallSpecial();
            gameLayer->hudLayer->progressTimer->setSprite(CCSprite::createWithSpriteFrameName("iconWallBreak.png"));
            break;
            
        case kExtrasType_WideLaneSpecial:
            performedWideLaneSpecial(10);
            gameLayer->hudLayer->progressTimer->setSprite(CCSprite::createWithSpriteFrameName("iconWideLane.png"));
            break;
            
        default:
            break;
    }
}

void Extras::performedMysteryBox() {
    int randomExtras = Utility::randomIntBetween(501, 505);
    initWithExtras(gameLayer, (ExtrasType)randomExtras);
    Utility::setMysteryBoxCount(1 + Utility::getMysteryBoxCount());
    if (Utility::getMysteryBoxCount() == 10 && Utility::getAchievementStatus(31) == 1) {
        //achieve 31
        CCLog("Mr Curious");
        Utility::setAchievementStatus(31, 2);
        Utility::setAchievementStatus(34, 1);
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_MR_CURIOUS : ACH_IOS_MR_CURIOUS);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        
        gameLayer->addFinalAchievementLayer(31);
    }
}

void Extras::performedRocketspecial() {
    gameLayer->isStrongWallBreak = true;    
    gameLayer->isPowerUpActive = true;
    gameLayer->powerActionTimer(3);
    gameLayer->character->characterUserData->sprite->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(Extras::addRocketPower)), CCDelayTime::create(3) , CCCallFunc::create(gameLayer, callfunc_selector(GameLayer::blinkAction)), CCCallFunc::create(this, callfunc_selector(Extras::removeRocketPower)), NULL));
    gameLayer->hudLayer->progressTimer->runAction(CCProgressFromTo::create(3, 0.0f, 100.0f));
}

void Extras::performedExtraLifeSpecial() {
    gameLayer->isStrongWallBreak = true;
    gameLayer->isPowerExtraLifeSpecial = true;
    float delay = 20.0f;
    gameLayer->runAction(CCSequence::create(CCDelayTime::create(delay), CCCallFunc::create(this, callfunc_selector(Extras::resetExtraLifeSpecial)), NULL));
    gameLayer->hudLayer->progressTimer->runAction(CCProgressFromTo::create(delay, 0.0f, 100.0f));
}

void Extras::resetExtraLifeSpecial() {
    gameLayer->isPowerExtraLifeSpecial = false;
    gameLayer->isStrongWallBreak = false;
    gameLayer->hudLayer->removeChildByTag(8888);
    gameLayer->hudLayer->progressTimer->removeFromParent();
}

void Extras::performedBrokenWallSpecial() {
    gameLayer->isMagnetEffectApply = true;
    gameLayer->isStrongWallBreak = true;
    float delay = 15.0f;
    gameLayer->runAction(CCSequence::create(CCDelayTime::create(delay), CCCallFunc::create(this, callfunc_selector(Extras::resetBrokenWallSpecial)), NULL));
    gameLayer->countBrokenWall();
    gameLayer->hudLayer->progressTimer->runAction(CCProgressFromTo::create(delay, 0.0f, 100.0f));
}

void Extras::performedWideLaneSpecial(float delay) {
    gameLayer->setWideLane();
    gameLayer->runAction(CCSequence::create(CCDelayTime::create(10), CCCallFunc::create(gameLayer, callfunc_selector(GameLayer::resetWideLane)), NULL));
    gameLayer->countWideLaneSeconds(delay);
    gameLayer->hudLayer->progressTimer->runAction(CCProgressFromTo::create(10, 0.0f, 100.0f));
}

void Extras::resetBrokenWallSpecial() {
    gameLayer->isMagnetEffectApply = false;
    gameLayer->isStrongWallBreak = false;
    gameLayer->hudLayer->removeChildByTag(8888);
    gameLayer->hudLayer->progressTimer->removeFromParent();
}

void Extras::addRocketPower() {
    gameLayer->character->addCharacterRocketFlame();
}

void Extras::removeRocketPower() {
    gameLayer->character->removeCharacterRocketFlame();
    gameLayer->hudLayer->removeChildByTag(8888);
    gameLayer->hudLayer->progressTimer->removeFromParent();
}
