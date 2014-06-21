//
//  GameLayer.h
//  Fly Guy
//
//  Created by Upkesh Thakur on 10/09/13.
//
//

#ifndef __Fly_Guy__GameLayer__
#define __Fly_Guy__GameLayer__

#include <iostream>
#include "cocos2d.h"
#include "Character.h"
#include "Box2D.h"
#include "GLES-Render.h"
#include "GB2ShapeCache-x.h"
#include "RandomParallaxBg.h"
#include "MyContactListener.h"
#include "HUDLayer.h"

class UserData;
class Obstacle;
class Extras;
class PowerUps;
class Coins;

using namespace cocos2d;

class ParallaxBackground;

class GameLayer: public CCLayer  {
public:
    static GameLayer* create(SceneType sceneType);
    virtual bool init(SceneType pSceneType);
    virtual void keyBackClicked();
    virtual void onEnter();    virtual void onExit();
    void tick(float dt);
    void setPhysics();
    void applyForce(b2Body *coinBody, CCSprite *coinSprite);
    void createButton(const char *spriteName, int tag, CCPoint posititon);
    void menuCallBack(CCObject *menuItem);
    void playGrassAnimation(UserData *caveUserData);
    
    SceneType sceneType;
    
    void draw();
    HUDLayer *hudLayer;
    Extras *extras;
    bool isDecrementingUpper;
    bool isDecrementingLower;
    
    bool isLaneWide;
    void setWideLane();
    void resetWideLane();
    int countLaneObjects;
    int totalLaneObjects;
    int count;
    int basicHelpTag;
    bool checkFlyDirection;
    bool isTouched;
    bool isObstacleAdding;
    bool isContinueClicked;
    
    bool isCollisionWithCave;
    bool isCollisionWithObstacle;
    
    bool startLower;
    void addUpperInitialObjects();
    void addLowerInitialObjects();
    void addUpperRandomParrallaxObjectsWithGrass();
    void addLowerRandomParrallaxObjectsWithGrass();    
    void addUpperRandomParrallaxObjectsWithoutGrass();
    void addLowerRandomParrallaxObjectsWithoutGrass();
    void addOneTimeBg();
    void checkTightSqueezes(UserData *userData);
    void squeezesOccur();
    void resetSquezesVariable();
    
    GLESDebugDraw *m_debugDraw;
    b2World *world;
    
    ParallaxBackground *parallaxBackground;
    RandomParallaxBg *lastUpperRandomParallax;
    RandomParallaxBg *lastLowerRandomParallax;
    RandomParallaxBg *randomParallaxForBg;
    
    CCSize winSize;
    class Character *character;
    CCSprite *helpCharSprite;
    class ContinueLayer *continueLayer;
    std::string flyDirection;
    GB2ShapeCache *gb2ShapeCache;
    
    MyContactListener *contactListener;
    
    CCArray *lowerBodyArrayWithGrass;
    CCArray *upperBodyArrayWithGrass;
    CCArray *lowerBodyArrayWithoutGrass;
    CCArray *upperBodyArrayWithoutGrass;
    
    CCAnimate *animateAction;
    int isActiveArrayForLower[20];
    int isActiveArrayForUpper[20];
    
    CCArray *obstacleArray;
    CCArray *powerUpArray;
    CCDictionary *coinsArray;
    CCDictionary *coinDictionary;
    
    bool isStartAllBg;
    bool isFlyUpcollided;
    bool isFlyDowncollided;
    void playWallBreakAnimation(UserData *weakWall);
    
    float speedToChange;
    void characterStopFlying();
    void moveParallaxObjects();
    void moveObstacleObjects();
    void addInitialObstacle();
    void playCharDestroy();
    void goToLevelComplete();
    void goToContinueScreen();
    void blinkAction();
    
    float getGameSpeed();
    float getPowerUpValue();
    bool isPowerUpActive;
    bool isLevelcompleted;
    void powerActionTimer(float delay);
    void resetSpeed();
    
    virtual void resetListener(CCNode *sender, void *data);
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void addPowerUps();
    void movePowerUpObjects();
    void runPower(UserData *userData, float delayPowerUp);
    void removeObstacle(Obstacle *obstacle);
    
    void moveCoinsPattern();
    void addCoins();
    void runCoinsAnimation(UserData *coinUserData, const char *frameName);
    void removeAllObstacle();
    void loadCharactor();
    void unloadCharacter();
    
    HUDLayer*  getHUDLayer();
    void  setHUDLayer(HUDLayer* layer);
    
    void decrementFactorForUpper(bool value);
    void decrementFactorForLower(bool value);
    
    CCParticleSystemQuad *particleBreakWall;
    
    float resetHeightFactorForLower;
    float resetHeightFactorForUpper;
    
    bool isPowerBubbleShield;
    bool isPowerExtraLifeSpecial;
    
    bool isStrongWallBreak;
    bool isMagnetEffectApply;
    
    int score;
    int distance, wallSmashed, squeezes;
    void setScore();
    int coinScore;
    int minute, seconds;
    float timeToStay;
    
    CCMenuItemSprite *continueMenuSprite;
//    void updateContinueTimer();
    void setGameTime();
    CCSprite *thumbSprite_0;
    CCSprite *thumbSprite_1;
    CCAction thumbAction;
    
    void countSpeedBurst();
    void countBubbleShield();
    void countRocket();
    void countBrokenWall();
    void countWideLaneSeconds(int seconds);
    
    bool isCharCollided;
    int speedBurst;
    int bubbleShield;
    int powerUps;
    int movingWall;
    bool isCharCollidedCoinsPowerUp;
    bool isTinyMode;
    int wallSmashedInRow;
    bool isWallCollided;
    int rockets;
    int jetPacks;
    int brokenWall;
    int wideLaneSeconds;
    int countContinue;
    
    CCSprite *tutorial1;
    CCSprite *tutorial2;
    
    void pauseAllTargets();
    void resumeAllTargets();
    void resetIsStrongWallBreak();
    void showTutorial1();
    void showTutorial2();
    
    void addStar();
    void addInitialAchievementLayer();
    void addFinalAchievementLayer(int achieved);
    
    void destroyAllBodies();
    
    CCSprite *blastSprite;
    CCLabelBMFont *blastLabel;
    
    CCSprite *tightSqueezeSprite;
    CCLabelBMFont *tightSqueezeLabel;
    
    CCAction *helpTutorialCharAction;
    
    bool isCharCollidedUpperCave;
    bool isCharCollidedLowerCave;
    int countHitDownAchieve;
    void addStarsParticle();
    
    CCParticleSystemQuad *starsParticle;
    CCParticleSystemQuad *wallBreakParticle;
    int previousWallTag;
    int countWallSmashedWithoutSkip;
    
    int targetDistanceToAddObstacle;
    int targetDistanceToAddCoins;
    int targetDistanceToAddPowerUps;
    void removeBlastSprite();
    float obstaclePosX;
    float obstaclePosY;
    int obstacleTag;
    void addWallBreakParticle();
    void removeCoin(Coins *coin);
    float topY;
    float bottomY;
    
    void playBackPackThrust();
    void playBackPackPadding();
    
    void updateMovingObjects(float dt);
    
    bool isBackPackPadding;
    int paddingSoundId;
    int thrashingSoundId;
    
    void checkAchieve29();
    void resetCollisionFactor();
    void resetUpperCaveCollision(CCObject *sender, void *data);
    
    bool isUpperGrassCollided;
    int coinsBonusWhilePower, countBasic3;
    
    bool isCaveWideRunning;
    void removePowerUp (PowerUps *power);
    void removeLayerObjects ();
    
    void removeUpperWithoutGrassObject(RandomParallaxBg *randomParallax);
    void removeUpperWithGrassObject(RandomParallaxBg *randomParallax);
    void removeLowerWithoutGrassObject(RandomParallaxBg *randomParallax);
    void removeLowerWithGrassObject(RandomParallaxBg *randomParallax);
    bool isGameOver;
    void updateBodyPosition(float dt);
    CCArray *disabledObstacleArray;
    Obstacle *getobstacleObj(UserData *userData);
    void step(float dt);
};
#endif /* defined(__Fly_Guy__GameLayer__) */
