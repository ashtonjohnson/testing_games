//
//  Character.cpp
//  NobWars
//
//  Created by Hadron Solutions on 23/07/13.
//
//

#include "Character.h"
#include "GameLayer.h"
#include "GB2ShapeCache-x.h"
#include "Utility.h"

#define Z_ORDER_BG            0
Character::Character() {}

void Character::initCharacter(class GameLayer *layer, const char *spriteName, const char *frameName, int frameCount) {
    gameLayer = layer;
    winSize = gameLayer->winSize;
    body = NULL;
    shouldShrinked = false;
    shrinked = false;
    isDead = false;
    characterUserData = new UserData;
    characterUserData->initWithFrameName(spriteName);
    //    character = CCSprite::createWithSpriteFrameName("char_0.png");
    characterUserData->userDataType = KCharactor;
    createBodyAndShape();
   // characterSprite->setAnchorPoint(gameLayer->gb2ShapeCache->anchorPointForShape(spriteName));
    
//    animateAction = animateActionCCAnimate::cre;
//    charAnim = (CMAnimation*) CMAnimation::animationWithFrame(frameName, frameCount, 0.05);
//    animateAction->initWithAnimation(charAnim);
    characterUserData->sprite->runAction(CCRepeatForever::create(CCAnimate::create((CMAnimation*) CMAnimation::animationWithFrame(frameName, frameCount, 0.05))));
    
    characterUserData->sprite->setPosition(ccp(gameLayer->winSize.width * 0.25, gameLayer->winSize.height * 0.5));
//    characterSprite->setVisible(false);
    gameLayer->addChild(characterUserData->sprite, 2);
    
    characterUserData->sprite->runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(Character::addCharacterFlameAnimation)), CCDelayTime::create(10), CCCallFunc::create(this, callfunc_selector(Character::removeCharacterFlameAnimation)), NULL));
    
    characterUserData->setReadyForDeletion(false);
//    characterUserData->setBody(charBody);
    //create virtual body for tight squeeezes
    
    characterVirtualUserData = new UserData;
    characterVirtualUserData->initWithFrameName(spriteName);
    characterVirtualUserData->virtualUserDataType = kCharacterVirtual;
    characterVirtualUserData->userDataType = kCharacterVirtual;
    gameLayer->addChild(characterVirtualUserData->sprite);
    characterVirtualUserData->sprite->setVisible(false);
    characterVirtualUserData->sprite->setPosition(characterUserData->sprite->getPosition());

    b2BodyDef obsBodyDef;
    obsBodyDef.userData = characterVirtualUserData;
    obsBodyDef.type = b2_dynamicBody;
    lineBody = gameLayer->world->CreateBody(&obsBodyDef);
    b2PolygonShape shape;
    shape.SetAsBox((10)/PTM_RATIO, (characterUserData->sprite->getTextureRect().size.height*1)/PTM_RATIO);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.friction = 0.8f;
    fixtureDef.restitution = 0.0f;
//    fixtureDef.density = 1.0f;
    fixtureDef.filter.groupIndex = -1;
    fixtureDef.filter.maskBits = 0xFFFF;
    fixtureDef.filter.categoryBits = kCategoryBitsCharVirtual;
    lineBody->CreateFixture(&fixtureDef);
//    { 23.000,-61.000 }
//    { 24.000,-59.000 }
//    { 22.000,64.000 }
//    GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile(kGamePhysicsPlist, "virtualCharBody", body);
//    gameLayer->gb2ShapeCache->addFixturesToBody(body, "virtualCharBody");
//    characterVirtualUserData->sprite->setAnchorPoint(gameLayer->gb2ShapeCache->anchorPointForShape("virtualCharBody"));
    
}

void Character::createBodyAndShape() {
    b2BodyDef charBodyDef;
    charBodyDef.type = b2_dynamicBody;
    charBodyDef.position.Set(characterUserData->sprite->getPositionX()/PTM_RATIO, characterUserData->sprite->getPositionY()/PTM_RATIO);
    charBodyDef.userData = characterUserData;
    body = gameLayer->world->CreateBody(&charBodyDef);
    b2CircleShape circleShape;
    circleShape.m_radius = ((characterUserData->sprite->getTextureRect().size.width * 0.34) ) / PTM_RATIO;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.friction = 0.8f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.density = 1.0f;
    b2Fixture *fixture =  body->CreateFixture(&fixtureDef);
    b2Filter filter=  fixture->GetFilterData();
    filter.groupIndex = -1;
    filter.categoryBits = 0x8000;
    filter.maskBits = 0xFFFF;
    fixture->SetFilterData(filter);
    //    gameLayer->gb2ShapeCache->addFixturesToBody(body, "char_0");
}

void Character::addCharacterFlameAnimation() {
    removeCharacterFlameAnimation();
        characterUserData->sprite->removeChild(flameUnTapped, true);
    if (Utility::getCharactorType() == kCharacterType_NormanBlue) {//char 0
        CCPoint position = CCPoint(0, characterUserData->sprite->getContentSize().height * 0.32);
        runFlameAnimations("flameChar0_0.png", "flameChar0_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_JohnyOrange) { // char 1
        CCPoint position = CCPoint(characterUserData->sprite->getContentSize().width * 0.16, characterUserData->sprite->getContentSize().height * 0.7);
        runFlameAnimations("flameChar1_0.png", "flameChar1_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_BellaRed) { // char 2
        CCPoint position = CCPoint(-characterUserData->sprite->getContentSize().width * 0.1, characterUserData->sprite->getContentSize().height * 0.1);
        runFlameAnimations("flameChar2_0.png", "flameChar2_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_VinnyGreen) { // char 3
        CCPoint position = CCPoint(-characterUserData->sprite->getContentSize().width * 0.04, characterUserData->sprite->getContentSize().height * 0.28);
        runFlameAnimations("flameChar3_0.png", "flameChar3_", 4, position);
    }
}

void Character::runFlameAnimations(const char *spriteName, const char *frameName, int frameCount, CCPoint position) {
    flame = CCSprite::createWithSpriteFrameName(spriteName);
    flame->setPosition(position);
    characterUserData->sprite->addChild(flame, characterUserData->sprite->getZOrder()-10);
//    animateAction = new CCAnimate();
//    charAnim = (CMAnimation*) CMAnimation::animationWithFrame(frameName, 4, 0.05);
//    animateAction->initWithAnimation(charAnim);
    flame->runAction(CCRepeatForever::create(CCAnimate::create((CMAnimation*) CMAnimation::animationWithFrame(frameName, 4, 0.05))));
}

void Character::removeCharacterFlameAnimation() {
        characterUserData->sprite->removeChild(flame, true);
    if (Utility::getCharactorType() == kCharacterType_NormanBlue) { //lenny
        CCPoint position = CCPoint(0, characterUserData->sprite->getContentSize().height * 0.37);
        stopFlameAnimations("withoutFlameChar0_0.png", "withoutFlameChar0_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_JohnyOrange) { //dez
        CCPoint position = CCPoint(characterUserData->sprite->getContentSize().width * 0.30, characterUserData->sprite->getContentSize().height * 0.74);
        stopFlameAnimations("withoutFlameChar1_0.png", "withoutFlameChar1_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_BellaRed) { //fauna flea
        CCPoint position = CCPoint(characterUserData->sprite->getContentSize().width * 0.04, characterUserData->sprite->getContentSize().height * 0.22);
        stopFlameAnimations("withoutFlameChar2_0.png", "withoutFlameChar2_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_VinnyGreen) {
        CCPoint position = CCPoint(characterUserData->sprite->getContentSize().width * 0.05, characterUserData->sprite->getContentSize().height * 0.42);
        stopFlameAnimations("withoutFlameChar3_0.png", "withoutFlameChar3_", 4, position);
    }
}

void Character::stopFlameAnimations(const char *spriteName, const char *frameName, int frameCount, CCPoint position) {
    flameUnTapped = CCSprite::createWithSpriteFrameName(spriteName);
    flameUnTapped->setPosition(position);
    characterUserData->sprite->addChild(flameUnTapped);
//    animateAction = new CCAnimate();
//    charAnim = (CMAnimation*) CMAnimation::animationWithFrame(frameName, 2, 0.05);
//    animateAction->initWithAnimation(charAnim);
    flameUnTapped->runAction(CCRepeatForever::create(CCAnimate::create((CMAnimation*) CMAnimation::animationWithFrame(frameName, 2, 0.05))));
}

void Character::addCharacterRocketFlame() {
    if (Utility::getCharactorType() == kCharacterType_BellaRed) {//char 0
        CCPoint position = CCPoint(characterUserData->sprite->getContentSize().width * 0.15, characterUserData->sprite->getContentSize().height * 0.38);
        runCharacterRocketFlame("flameRocketChar0_0.png", "flameRocketChar0_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_JohnyOrange) { // char 1
        CCPoint position = CCPoint(characterUserData->sprite->getContentSize().width * 0.18, characterUserData->sprite->getContentSize().height * 0.62);
        runCharacterRocketFlame("flameRocketChar1_0.png", "flameRocketChar1_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_NormanBlue) { // char 2
        CCPoint position = CCPoint(characterUserData->sprite->getContentSize().width * 0.15, characterUserData->sprite->getContentSize().height * 0.35);
        runCharacterRocketFlame("flameRocketChar2_0.png", "flameRocketChar2_", 4, position);
    }
    
    if (Utility::getCharactorType() == kCharacterType_VinnyGreen) { // char 3
        CCPoint position = CCPoint(characterUserData->sprite->getContentSize().width * 0.17, characterUserData->sprite->getContentSize().height * 0.35);
        runCharacterRocketFlame("flameRocketChar3_0.png", "flameRocketChar3_", 4, position);
    }
    CCLog("addCharacterRocketFlame");

}

void Character::runCharacterRocketFlame(const char *spriteName, const char *frameName, int frameCount, CCPoint position) {
    flameRocket = CCSprite::createWithSpriteFrameName(spriteName);
    flameRocket->setPosition(position);
    characterUserData->sprite->addChild(flameRocket, characterUserData->sprite->getZOrder()-10);
//    animateAction = new CCAnimate();
//    charAnim = (CMAnimation*) CMAnimation::animationWithFrame(frameName, frameCount, 0.05);
//    animateAction->initWithAnimation(charAnim);
    flameRocket->runAction(CCRepeatForever::create(CCAnimate::create((CMAnimation*) CMAnimation::animationWithFrame(frameName, frameCount, 0.05))));
}

void Character::removeCharacterRocketFlame() {
    flameRocket->stopAllActions();
    characterUserData->sprite->removeChild(flameRocket, true);
}

void Character::flyUp() {
   float guyPosY = characterUserData->sprite->getPositionY();
        body->SetLinearVelocity(b2Vec2(0, 22));
        if(!gameLayer->isFlyUpcollided) {
            characterUserData->sprite->setPositionY(characterUserData->sprite->getPositionY() + getMultiplier());
            characterVirtualUserData->sprite->setPosition(characterUserData->sprite->getPosition());
        }
    if (guyPosY > winSize.height && gameLayer->isStartAllBg) {
            characterUserData->sprite->setPosition(ccp(characterUserData->sprite->getPositionX(), -winSize.height * 0.1));
    }
//    characterUserData->sprite->setPosition(characterUserData->sprite->getPosition());
    characterVirtualUserData->setPosition(characterUserData->sprite->getPosition());
}

float Character::getMultiplier(){
    float deltaChange = ((Utility::isIPad())? 0.4:0.20) + gameLayer->getGameSpeed()*0.01;
    speedToChange = gameLayer->speedToChange+= deltaChange;
    return speedToChange;
}

void Character::flyDown() {
    float guyPosY = characterUserData->sprite->getPositionY();
        if(!gameLayer->isFlyDowncollided) {
            characterUserData->sprite->setPositionY(characterUserData->sprite->getPositionY() - getMultiplier());
            characterVirtualUserData->sprite->setPosition(characterUserData->sprite->getPosition());
        }
    if (guyPosY < 0 && gameLayer->isTouched) {
            characterUserData->sprite->setPosition(ccp(characterUserData->sprite->getPositionX(), winSize.height * 1.1));
    }
//    characterUserData->sprite->setPosition(characterUserData->sprite->getPosition());
    characterVirtualUserData->setPosition(characterUserData->sprite->getPosition());
}

void Character::addEyesAnimation() {
    removeEyesAnimation();
    if (Utility::getCharactorType() == kCharacterType_JohnyOrange) { // Dez
        eyeSprite = CCSprite::createWithSpriteFrameName("eyesChar1.png");
        eyeSprite->setPosition(ccp(characterUserData->sprite->getContentSize().width * 0.87, characterUserData->sprite->getContentSize().height * 0.66));
    characterUserData->sprite->addChild(eyeSprite, characterUserData->sprite->getZOrder());
    } else if (Utility::getCharactorType() == kCharacterType_BellaRed) { // flying flea
        eyeSprite = CCSprite::createWithSpriteFrameName("eyesChar2.png");
        eyeSprite->setPosition(ccp(characterUserData->sprite->getContentSize().width * 0.76, characterUserData->sprite->getContentSize().height * 0.45));
    characterUserData->sprite->addChild(eyeSprite, characterUserData->sprite->getZOrder());
    } else if (Utility::getCharactorType() == kCharacterType_VinnyGreen){ // Ella
        eyeSprite = CCSprite::createWithSpriteFrameName("eyesChar3.png");
        eyeSprite->setScale(0.52);
        eyeSprite->setPosition(ccp(characterUserData->sprite->getContentSize().width * 0.828, characterUserData->sprite->getContentSize().height * 0.54));
    characterUserData->sprite->addChild(eyeSprite, characterUserData->sprite->getZOrder());
    }
}

void Character::removeEyesAnimation() {
    characterUserData->sprite->removeChild(eyeSprite, true);
}

void Character::updateBodyPos() {
    
    b2Vec2 vect = b2Vec2(Utility::toMeters(CCPoint(characterUserData->getSprite()->getPositionX(),characterUserData->getSprite()->getPositionY())));
    body->SetTransform(vect, CC_DEGREES_TO_RADIANS(-characterUserData->getSprite()->getRotation()));
    lineBody->SetTransform(vect, 0);
}

