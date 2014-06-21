//
//  Character.h
//  FlyGuy
//
//  Created by Ramesh on 16/09/13.
//
//

#ifndef __FlyGuy__Character__
#define __FlyGuy__Character__

#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"
#include "CMAnimation.h"
#include "Box2D.h"
class UserData;

using namespace cocos2d;

class Character : public CCSprite {
public:
    class GameLayer *gameLayer;
    CCSize winSize;
    Character();
//    CCSprite *character;
    UserData *characterUserData;
    UserData *characterVirtualUserData;
//    CCSprite *characterSprite;
//    CCSprite *characterVirtualSprite;
    CCSprite *flame, *flameRocket;
    CCSprite *flameUnTapped;
    
    CCSprite *eyeSprite;
    
    b2Body *body;
    b2Body *lineBody;
    float speedToChange;
    void flyUp();
    void flyDown();
    float getMultiplier();
    void addCharacterFlameAnimation();
    void removeCharacterFlameAnimation();
    void stopCharacter();
    void createBodyAndShape();
    void addCharacterRocketFlame();
    void removeCharacterRocketFlame();
    void initCharacter(GameLayer *layer, const char *spriteName, const char *frameName, int frameCount);
    void runFlameAnimations(const char *spriteName, const char *frameName, int frameCount, CCPoint position);
    void stopFlameAnimations(const char *spriteName, const char *frameName, int frameCount, CCPoint position);
    void runCharacterRocketFlame(const char *spriteName, const char *frameName, int frameCount, CCPoint position);
    void addEyesAnimation();
    void removeEyesAnimation();
    
    CMAnimation *charAnim;
    CCAnimate *animateAction;
    
    bool shouldShrinked;
    bool shrinked;
    bool shouldResetBody;
    bool isDead;
    void updateBodyPos();
};

#endif /* defined(__FlyGuy__Character__) */
