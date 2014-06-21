//
//  MyContactListener.h
//  NobWars
//
//  Created by Er.Umesh on 22/07/13.
//
//

#ifndef __NobWars__MyContactListener__
#define __NobWars__MyContactListener__

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"

using namespace cocos2d;

class GameLayer;
class UserData;

class MyContactListener : public b2ContactListener {
public:
//    CCSprite *userDataA, *userDataB;
    GameLayer *gameLayer;
    CCSize winSize;
    MyContactListener(GameLayer *gameLayer);
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif /* defined(__NobWars__MyContactListener__) */
