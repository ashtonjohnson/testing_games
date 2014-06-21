//
//  MyContactListener.cpp
//  NobWars
//
//  Created by Er.Umesh on 22/07/13.
//
//

#include "MyContactListener.h"
#include "Utility.h"
#include "Box2D.h"
#include "GameLayer.h"
#include "LevelCompletionScene.h"
#include "Obstacle.h"
#include "Coins.h"

class UserData;

#define kResetSpeed 1

MyContactListener::MyContactListener(GameLayer *gameLayer){
    this->gameLayer = gameLayer;
    winSize = gameLayer->winSize;
}

void MyContactListener::BeginContact(b2Contact *contact){
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    
    const b2Body* bodyA = contact->GetFixtureA()->GetBody();
    const b2Body* bodyB = contact->GetFixtureB()->GetBody();
    
    UserData *userDataA = (UserData*) bodyA->GetUserData();
    UserData *userDataB = (UserData*) bodyB->GetUserData();
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();

    if((userDataA->userDataType == kCaveType_UpperWithGrass) && (userDataB->userDataType == KCharactor)){
        gameLayer->isCharCollided = true;
        if (!gameLayer->isPowerUpActive) {
            gameLayer->isStartAllBg = false;
            gameLayer->isFlyUpcollided = true;
            contact->SetEnabled(false);
            gameLayer->isCollisionWithCave = false;
            gameLayer->isCharCollidedUpperCave = true;
            if (!gameLayer->isUpperGrassCollided) {
                gameLayer->playGrassAnimation(userDataA);
                gameLayer->isUpperGrassCollided = true;
            }
        }  else {
            gameLayer->speedToChange = kResetSpeed;
            gameLayer->flyDirection = kFlyDown;
        }
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCaveType_UpperWithGrass)){
        gameLayer->isCharCollided = true;
        if (!gameLayer->isPowerUpActive) {
            gameLayer->isStartAllBg = false;
            gameLayer->isFlyUpcollided = true;
            gameLayer->isCollisionWithCave = false;
            gameLayer->isCharCollidedUpperCave = true;
            if (!gameLayer->isUpperGrassCollided) {
                gameLayer->playGrassAnimation(userDataB);
                gameLayer->isUpperGrassCollided = true;
            }
            contact->SetEnabled(false);
        }  else {
            gameLayer->speedToChange = kResetSpeed;
            gameLayer->flyDirection = kFlyDown;
        }
    }
    
    if((userDataA->userDataType == kCaveType_LowerWithGrass) && (userDataB->userDataType == KCharactor)){
        gameLayer->isCharCollided = true;
        if (!gameLayer->isPowerUpActive) {
            if (gameLayer->isCharCollidedUpperCave) {
                gameLayer->countHitDownAchieve++;
                if (gameLayer->countHitDownAchieve == 2 && Utility::getAchievementStatus(20) == 1) {
                    //achieve 20
                    Utility::setAchievementStatus(20, 2);
                    Utility::setAchievementStatus(23, 1);
//                    CCString *idString = CCString::createWithFormat("com.flying.flea.bigdrops");
                    CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_BIG_DROPS : ACH_IOS_BIG_DROPS);
                    CCString *msgString = CCString::createWithFormat("");
                    Utility::unlockAchievemnt(idString, msgString);
                }
            }
            gameLayer->playGrassAnimation(userDataA);
            gameLayer->isStartAllBg = false;
            gameLayer->isFlyDowncollided = true;
            gameLayer->isCollisionWithCave = false;
        } else {
            gameLayer->speedToChange = kResetSpeed;
            gameLayer->flyDirection = kFlyUp;
        }
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCaveType_LowerWithGrass)){
        gameLayer->isCharCollided = true;
        if (!gameLayer->isPowerUpActive) {
            gameLayer->isStartAllBg = false;
            gameLayer->isFlyDowncollided = true;
            gameLayer->isCollisionWithCave = false;
            gameLayer->playGrassAnimation(userDataB);
            if (gameLayer->isCharCollidedUpperCave) {
                gameLayer->countHitDownAchieve++;
                if (gameLayer->countHitDownAchieve == 2 && Utility::getAchievementStatus(20) == 1) {
                    //achieve 20
                    Utility::setAchievementStatus(20, 2);
                    Utility::setAchievementStatus(23, 1);
//                    CCString *idString = CCString::createWithFormat("com.flying.flea.bigdrops");
                    CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_BIG_DROPS : ACH_IOS_BIG_DROPS);
                    CCString *msgString = CCString::createWithFormat("");
                    Utility::unlockAchievemnt(idString, msgString);
                }
            }
        } else {
            gameLayer->speedToChange = kResetSpeed;
            gameLayer->flyDirection = kFlyUp;
        }
    }
    
    if((userDataA->userDataType == kCaveType_UpperWithoutGrass) && (userDataB->userDataType == KCharactor)){
        gameLayer->isCharCollided = true;
        if (!gameLayer->isPowerUpActive) {
            gameLayer->isStartAllBg = false;
            gameLayer->isFlyUpcollided = true;
            gameLayer->playCharDestroy();
        } else {
            gameLayer->speedToChange = kResetSpeed;
            gameLayer->flyDirection = kFlyDown;
        }
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCaveType_UpperWithoutGrass)){
        gameLayer->isCharCollided = true;
        if (!gameLayer->isPowerUpActive) {
            gameLayer->isStartAllBg = false;
            gameLayer->isFlyUpcollided = true;
            gameLayer->playCharDestroy();
        } else {
            gameLayer->speedToChange = kResetSpeed;
            gameLayer->flyDirection = kFlyDown;
        }
    }
    
    if((userDataA->userDataType == kCaveType_LowerWithoutGrass) && (userDataB->userDataType == KCharactor)){
        gameLayer->isCharCollided = true;
        if (!gameLayer->isPowerUpActive) {
            gameLayer->isStartAllBg = false;
            gameLayer->isFlyDowncollided = true;
            gameLayer->playCharDestroy();
        }    else {
            gameLayer->speedToChange = kResetSpeed;
            gameLayer->flyDirection = kFlyUp;
        }
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCaveType_LowerWithoutGrass)){
        gameLayer->isCharCollided = true;
        if (!gameLayer->isPowerUpActive) {
            gameLayer->isStartAllBg = false;
            gameLayer->isFlyDowncollided = true;
            gameLayer->playCharDestroy();
        } else {
            gameLayer->speedToChange = kResetSpeed;
            gameLayer->flyDirection = kFlyUp;
        }
    }
    
    if((userDataA->userDataType == kObstacleType_Strong) && (userDataB->userDataType == KCharactor)){
        if (gameLayer->isObstacleAdding) { //isObstacleAdding used for help screen
            if (gameLayer->isStrongWallBreak) {
                if (!userDataA->getCollision()) {
                userDataA->setCollision(true);
                gameLayer->playWallBreakAnimation(userDataA);
                contact->SetEnabled(false);
                }
            } else{
                
                gameLayer->isStartAllBg = false;
                gameLayer->playCharDestroy();
                contact->SetEnabled(false);
            }
        }        
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kObstacleType_Strong)){
        if (gameLayer->isObstacleAdding) {
            if (gameLayer->isStrongWallBreak) {
                if (!userDataB->getCollision()) {
                userDataB->setCollision(true);
                gameLayer->playWallBreakAnimation(userDataB);
                contact->SetEnabled(false);
                }
            } else {
                gameLayer->isStartAllBg = false;
                gameLayer->playCharDestroy();
                contact->SetEnabled(false);
            }
        }
        
    }
    
    if((userDataA->userDataType == kObstacleType_Weak) && (userDataB->userDataType == KCharactor)){
        if (!userDataA->getCollision()) {
            gameLayer->playWallBreakAnimation(userDataA);
            userDataA->setCollision(true);
        }
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kObstacleType_Weak)){
        if (!userDataB->getCollision()) {
            gameLayer->playWallBreakAnimation(userDataB);
            userDataB->setCollision(true);
        }
    }
    
    if((userDataA->userDataType == kPowerType_BubbleShield) && (userDataB->userDataType == KCharactor)){
        //bubble shield
        if (!userDataA->getCollision()) {
            userDataA->setCollision(true);
            gameLayer->runPower(userDataA, 5);
            gameLayer->countBubbleShield();
        }
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kPowerType_BubbleShield)){
        // bubble shield
        if (!userDataB->getCollision()) {
            userDataB->setCollision(true);
            gameLayer->runPower(userDataB, 5);
            gameLayer->countBubbleShield();
        }
    }
    
    if((userDataA->userDataType == kPowerType_SpeedBurst) && (userDataB->userDataType == KCharactor)){
        //kPowerType_SpeedBurst
        if (!userDataA->getCollision()) {
            userDataA->setCollision(true);
            contact->SetEnabled(false);
            gameLayer->runPower(userDataA, 0.8);
            gameLayer->countSpeedBurst();
        }
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kPowerType_SpeedBurst)){
        // kPowerType_SpeedBurst
        if (!userDataB->getCollision()) {
            userDataB->setCollision(true);
            contact->SetEnabled(false);
            gameLayer->runPower(userDataB, 0.8);
            gameLayer->countSpeedBurst();
        }
    }
    
    if((userDataA->userDataType == kPowerType_SuperRocket) && (userDataB->userDataType == KCharactor)){
        //kPowerType_SuperRocket
        if (!userDataA->getCollision()) {
            userDataA->setCollision(true);
            contact->SetEnabled(false);
            gameLayer->runPower(userDataA, 2);
            gameLayer->countRocket();
        }        
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kPowerType_SuperRocket)){
        // kPowerType_SuperRocket
        if (!userDataB->getCollision()) {
            userDataB->setCollision(true);
            contact->SetEnabled(false);
            gameLayer->runPower(userDataB, 2);
            gameLayer->countRocket();
        }
    }
    
    if((userDataA->userDataType == kPowerType_TinyMode) && (userDataB->userDataType == KCharactor)){
        //kPowerType_TinyMode
        if (!userDataA->getCollision()) {
            userDataA->setCollision(true);
            contact->SetEnabled(false);
            gameLayer->runPower(userDataA, 3);
        }
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kPowerType_TinyMode)){
        // kPowerType_TinyMode
        if (!userDataB->getCollision()) {
            userDataB->setCollision(true);
            contact->SetEnabled(false);
            gameLayer->runPower(userDataB, 3);
        }
    }
    
    if((userDataA->userDataType == kPowerType_Star) && (userDataB->userDataType == KCharactor)){
        //kPowerType_Star
        if (!userDataA->getCollision()) {
            userDataA->setCollision(true);
            contact->SetEnabled(false);
            gameLayer->runPower(userDataA, 0);
        }
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kPowerType_Star)){
        // kPowerType_Star
        if (!userDataB->getCollision()) {
            userDataB->setCollision(true);
            contact->SetEnabled(false);
            gameLayer->runPower(userDataB, 0);
        }
    }

    
    if((userDataA->virtualUserDataType == kCoinsType_Normal) && (userDataB->userDataType == KCharactor)){
        //kCoinsType_Normal
        const char *frameName = "coins_";
        CCString *key = CCString::createWithFormat("%d", userDataA->getTag());
        Coins *coin = (Coins*)gameLayer->coinsArray->objectForKey(key->getCString());
        if (coin != NULL && !coin->spriteUserData->getCollision()) {
            coin->spriteUserData->setCollision(true);
            coin->runAnimation(frameName);
        }
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->virtualUserDataType == kCoinsType_Normal)){
        // kCoinsType_Normal
        const char *frameName = "coins_";
        CCString *key = CCString::createWithFormat("%d", userDataB->getTag());
        Coins *coin = (Coins*)gameLayer->coinsArray->objectForKey(key->getCString());
        if (coin != NULL && !coin->spriteUserData->getCollision()) {
            coin->spriteUserData->setCollision(true);
            coin->runAnimation(frameName);
        }
    }
    
//    if((userDataA->userDataType == kCoinsType_Yellow) && (userDataB->userDataType == KCharactor)){
//        gameLayer->score += 1;
//        const char *frameName = "coins_";
//        CCString *key = CCString::createWithFormat("%d", userDataB->getTag());
//        Coins *coin = (Coins*)gameLayer->coinsArray->objectForKey(key->getCString());
//        if (coin != NULL && !coin->spriteUserData->getCollision()) {
//            coin->spriteUserData->setCollision(true);
//            coin->runAnimation(frameName);
//        }
//    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCoinsType_Yellow)){
//        gameLayer->score += 1;
//        const char *frameName = "coins_";
//        CCString *key = CCString::createWithFormat("%d", userDataB->getTag());
//        Coins *coin = (Coins*)gameLayer->coinsArray->objectForKey(key->getCString());
//        if (coin != NULL && !coin->spriteUserData->getCollision()) {
//            coin->spriteUserData->setCollision(true);
//            coin->runAnimation(frameName);
//        }
//    }
//    
//    if((userDataA->userDataType == kCoinsType_Green) && (userDataB->userDataType == KCharactor)){
//        gameLayer->score += 2;
//        const char *frameName = "coins1_";
//        CCString *key = CCString::createWithFormat("%d", userDataB->getTag());
//        Coins *coin = (Coins*)gameLayer->coinsArray->objectForKey(key->getCString());
//        if (coin != NULL && !coin->spriteUserData->getCollision()) {
//            coin->spriteUserData->setCollision(true);
//            coin->runAnimation(frameName);
//        }
//    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCoinsType_Green)){
//        gameLayer->score += 2;
//        const char *frameName = "coins1_";
//        CCString *key = CCString::createWithFormat("%d", userDataB->getTag());
//        Coins *coin = (Coins*)gameLayer->coinsArray->objectForKey(key->getCString());
//        if (coin != NULL && !coin->spriteUserData->getCollision()) {
//            coin->spriteUserData->setCollision(true);
//            coin->runAnimation(frameName);
//        }
//    }
//    
//    if((userDataA->userDataType == kCoinsType_Red) && (userDataB->userDataType == KCharactor)){
//        gameLayer->score += 3;
//        const char *frameName = "coins2_";
//        CCString *key = CCString::createWithFormat("%d", userDataB->getTag());
//        Coins *coin = (Coins*)gameLayer->coinsArray->objectForKey(key->getCString());
//        if (coin != NULL && !coin->spriteUserData->getCollision()) {
//            coin->spriteUserData->setCollision(true);
//            coin->runAnimation(frameName);
//        }
//    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCoinsType_Red)){
//        gameLayer->score += 3;
//        const char *frameName = "coins2_";
//        CCString *key = CCString::createWithFormat("%d", userDataB->getTag());
//        Coins *coin = (Coins*)gameLayer->coinsArray->objectForKey(key->getCString());
//        if (coin != NULL && !coin->spriteUserData->getCollision()) {
//            coin->spriteUserData->setCollision(true);
//            coin->runAnimation(frameName);
//        }
//    }
//    
//    if((userDataA->userDataType == kCoinsType_Blue) && (userDataB->userDataType == KCharactor)){
//        gameLayer->score += 4;
//        const char *frameName = "coins3_";
//        CCString *key = CCString::createWithFormat("%d", userDataB->getTag());
//        Coins *coin = (Coins*)gameLayer->coinsArray->objectForKey(key->getCString());
//        if (coin != NULL && !coin->spriteUserData->getCollision()) {
//            coin->spriteUserData->setCollision(true);
//            coin->runAnimation(frameName);
//        }
//    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCoinsType_Blue)){
//        gameLayer->score += 4;
//        const char *frameName = "coins3_";
//        CCString *key = CCString::createWithFormat("%d", userDataB->getTag());
//        Coins *coin = (Coins*)gameLayer->coinsArray->objectForKey(key->getCString());
//        if (coin != NULL && !coin->spriteUserData->getCollision()) {
//            coin->spriteUserData->setCollision(true);
//            coin->runAnimation(frameName);
//        }
//    }
    
    if((userDataA->virtualUserDataType == kCharacterVirtual) && (userDataB->userDataType == kObstacleType_Strong || userDataB->userDataType == kObstacleType_Weak)){
            contact->SetEnabled(false);
        if (!userDataB->getCollision()) {
            gameLayer->isCollisionWithObstacle = true;
            gameLayer->checkTightSqueezes(userDataB);
            userDataB->setCollision(true);
        }
    }else if ((userDataA->userDataType == kObstacleType_Strong || userDataA->userDataType == kObstacleType_Weak) && (userDataB->virtualUserDataType == kCharacterVirtual)){
            contact->SetEnabled(false);
        if (!userDataA->getCollision()) {
            gameLayer->isCollisionWithObstacle = true;
            gameLayer->checkTightSqueezes(userDataA);
            userDataA->setCollision(true);
        }
    }
    if((fixtureA->GetFilterData().categoryBits == kCategoryBitsCharVirtual) && (fixtureB->GetFilterData().categoryBits == kCategoryBitsWalls)) {
        contact->SetEnabled(false);
        if (!userDataB->getCollision()) {
            gameLayer->isCollisionWithObstacle = true;
            gameLayer->checkTightSqueezes(userDataB);
            userDataB->setCollision(true);
        }
    }else if ((fixtureB->GetFilterData().categoryBits == kCategoryBitsCharVirtual) && (fixtureA->GetFilterData().categoryBits == kCategoryBitsWalls)){
        contact->SetEnabled(false);
        if (!userDataA->getCollision()) {
            gameLayer->isCollisionWithObstacle = true;
            gameLayer->checkTightSqueezes(userDataA);
            userDataA->setCollision(true);
        }
    }

/*    if((userDataA->virtualUserDataType == kCharacterVirtual) && (userDataB->userDataType == kCaveType_LowerWithGrass || userDataB->userDataType == kCaveType_LowerWithoutGrass || userDataB->userDataType == kCaveType_UpperWithGrass || userDataB->userDataType == kCaveType_UpperWithoutGrass)) {
            contact->SetEnabled(false);
        if (!userDataB->getCollision()) {
            gameLayer->checkTightSqueezes(userDataB);
            userDataB->setCollision(true);
        }
        gameLayer->isCollisionWithCave = true;
    }else if ((userDataB->virtualUserDataType == kCharacterVirtual) && (userDataA->userDataType == kCaveType_LowerWithGrass || userDataA->userDataType == kCaveType_LowerWithoutGrass || userDataA->userDataType == kCaveType_UpperWithGrass || userDataA->userDataType == kCaveType_UpperWithoutGrass)){
            contact->SetEnabled(false);
        if (!userDataA->getCollision()) {
            gameLayer->checkTightSqueezes(userDataA);
            userDataA->setCollision(true);
        }
        gameLayer->isCollisionWithCave = true;
    }
 */
}

void MyContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold){
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();
    
    
    
    UserData *userDataA = (UserData*) bodyA->GetUserData();
    UserData *userDataB = (UserData*) bodyB->GetUserData();
    
//    CCLog("groupIndexA=  %d, groupIndexB= %d", fixtureA->GetFilterData().groupIndex, fixtureB->GetFilterData().groupIndex);
//    CCLog("categoryBitsA %d, categoryBitsB %d", fixtureA->GetFilterData().categoryBits, fixtureB->GetFilterData().categoryBits);
//    if (userDataA->userDataType == kCaveType_LowerWithGrass && (userDataB->userDataType == kCaveType_LowerWithGrass || userDataB->userDataType == kCaveType_LowerWithoutGrass)) {
//        CCLog("collided");
//    }else if(userDataB->userDataType == kCaveType_LowerWithGrass && (userDataA->userDataType == kCaveType_LowerWithGrass || userDataA->userDataType == kCaveType_LowerWithoutGrass)) {
//                CCLog("collided");
//    }
//    CCLog("userDataA %d, userDataB %d", userDataA->userDataType , userDataB->userDataType);
//
    if((userDataA->virtualUserDataType == kCoinsType_Normal) && (userDataB->userDataType == kObstacleType_Strong)){
        contact->SetEnabled(false);
    }else if ((userDataA->userDataType == kObstacleType_Strong) && (userDataB->virtualUserDataType == kCoinsType_Normal)){
        contact->SetEnabled(false);
    }
    
    if((userDataA->virtualUserDataType == kCoinsType_Normal) && (userDataB->userDataType == kObstacleType_Weak)){
        contact->SetEnabled(false);
    }else if ((userDataA->userDataType == kObstacleType_Weak) && (userDataB->virtualUserDataType == kCoinsType_Normal)){
        contact->SetEnabled(false);
    }
    
    if((userDataA->virtualUserDataType == kCoinsType_Normal) && (userDataB->virtualUserDataType == kCoinsType_Normal)){
        contact->SetEnabled(false);
    }else if ((userDataA->virtualUserDataType == kCoinsType_Normal) && (userDataB->virtualUserDataType == kCoinsType_Normal)){
        contact->SetEnabled(false);
    }

    if((fixtureA->GetFilterData().categoryBits == kCategoryBitsCharVirtual) && (fixtureB->GetFilterData().categoryBits == kCategoryBitsWalls)) {
//        CCLog("fixtureA->IsSensor() = %d", fixtureA->IsSensor());
            contact->SetEnabled(false);
        if (!userDataB->getCollision()) {
            gameLayer->isCollisionWithObstacle = true;
            gameLayer->checkTightSqueezes(userDataB);
            userDataB->setCollision(true);
        }
    }else if ((fixtureB->GetFilterData().categoryBits == kCategoryBitsCharVirtual) && (fixtureA->GetFilterData().categoryBits == kCategoryBitsWalls)){
//        CCLog("fixtureA->IsSensor() = %d", fixtureA->IsSensor());
        contact->SetEnabled(false);
        if (!userDataA->getCollision()) {
            gameLayer->isCollisionWithObstacle = true;
            gameLayer->checkTightSqueezes(userDataA);
            userDataA->setCollision(true);
        }
    }
    
    if((userDataA->virtualUserDataType == kCharacterVirtual) && (userDataB->userDataType == kCaveType_LowerWithGrass || userDataB->userDataType == kCaveType_LowerWithoutGrass || userDataB->userDataType == kCaveType_UpperWithGrass || userDataB->userDataType == kCaveType_UpperWithoutGrass)) {
            contact->SetEnabled(false);
        if (!userDataB->getCollision()) {
            gameLayer->checkTightSqueezes(userDataB);
            userDataB->setCollision(true);
        }
        gameLayer->isCollisionWithCave = true;
    }else if ((userDataB->virtualUserDataType == kCharacterVirtual) && (userDataA->userDataType == kCaveType_LowerWithGrass || userDataA->userDataType == kCaveType_LowerWithoutGrass || userDataA->userDataType == kCaveType_UpperWithGrass || userDataA->userDataType == kCaveType_UpperWithoutGrass)){
            contact->SetEnabled(false);
        if (!userDataA->getCollision()) {
            gameLayer->checkTightSqueezes(userDataA);
            userDataA->setCollision(true);
        }
        gameLayer->isCollisionWithCave = true;
    }
}

void MyContactListener::EndContact(b2Contact *contact){
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    
    const b2Body* bodyA = contact->GetFixtureA()->GetBody();
    const b2Body* bodyB = contact->GetFixtureB()->GetBody();
    
    UserData *userDataA = (UserData*) bodyA->GetUserData();
    UserData *userDataB = (UserData*) bodyB->GetUserData();
    
    if((userDataA->userDataType == kCaveType_UpperWithGrass) && (userDataB->userDataType == KCharactor)){
        gameLayer->isStartAllBg = true;
        gameLayer->isFlyUpcollided = false;
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCaveType_UpperWithGrass)){
        gameLayer->isStartAllBg = true;
        gameLayer->isFlyUpcollided = false;
    }
    
    if((userDataA->userDataType == kCaveType_LowerWithGrass) && (userDataB->userDataType == KCharactor)){
        gameLayer->isStartAllBg = true;
        gameLayer->isFlyDowncollided = false;
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCaveType_LowerWithGrass)){
        gameLayer->isStartAllBg = true;
        gameLayer->isFlyDowncollided = false;
    }
    
    if((userDataA->userDataType == kCaveType_UpperWithoutGrass) && (userDataB->userDataType == KCharactor)){
        gameLayer->isStartAllBg = true;
        gameLayer->isFlyUpcollided = false;
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCaveType_UpperWithoutGrass)){
        gameLayer->isStartAllBg = true;
        gameLayer->isFlyUpcollided = false;
    }
    
    if((userDataA->userDataType == kCaveType_LowerWithoutGrass) && (userDataB->userDataType == KCharactor)){
        gameLayer->isStartAllBg = true;
        gameLayer->isFlyDowncollided = false;
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kCaveType_LowerWithoutGrass)){
        gameLayer->isStartAllBg = true;
        gameLayer->isFlyDowncollided = false;
    }
    
    if((userDataA->userDataType == kObstacleType_Strong) && (userDataB->userDataType == KCharactor)){
        gameLayer->isStartAllBg = true;
    }else if ((userDataA->userDataType == KCharactor) && (userDataB->userDataType == kObstacleType_Strong)){
        gameLayer->isStartAllBg = true;
    }
    
}

void MyContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse){
    
}

