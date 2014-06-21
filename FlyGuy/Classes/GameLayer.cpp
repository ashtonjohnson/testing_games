//
//  GameLayer.cpp
//  Fly Guy
//
//  Created by Upkesh Thakur on 10/09/13.
//
//

#include "GameLayer.h"
#include "GameScene.h"
#include "ParallaxBackground.h"
#include "NDKHelper.h"
#include "Constant.h"
#include "Utility.h"
#include "GB2ShapeCache-x.h"
#include "Obstacle.h"
#include "MainMenuScene.h"
#include "TinyMode.h"
#include "BubbleShield.h"
#include "SuperRocket.h"
#include "SpeedBurst.h"
#include "Star.h"
#include "GreenCoins.h"
#include "CoinsPattern.h"
#include "Coins.h"

#include "VinnyGreenCharacter.h"
#include "NormanBlueCharacter.h"
#include "BellaRedCharater.h"
#include "JohnyOrangeCharacter.h"

#include "ObstaclePattern.h"
#include "Extras.h"
#include "ContinueLayer.h"

#include "SoundConstant.h"
#include "PowerUps.h"

using namespace cocos2d;

GameLayer* GameLayer::create(SceneType sceneType) {
    GameLayer *pRet = new GameLayer;
    if (pRet && pRet->init(sceneType)) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void GameLayer:: onEnter() {
    CCLayer::onEnter();
    CCUserDefault::sharedUserDefault()->setBoolForKey(kBackgroundMusicKey, false);
    Utility::playOrPauseMusic(CCString::create(kBackgroundMusicFile));
    
    playBackPackThrust();
    playBackPackPadding();
    
    //code here
    setPhysics();
    gb2ShapeCache = (GB2ShapeCache*) GB2ShapeCache::sharedGB2ShapeCache();
    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
    
    gb2ShapeCache->addShapesWithFile("gamePhysics.plist");
    schedule(schedule_selector(GameLayer::tick));
    schedule(schedule_selector(GameLayer::updateMovingObjects));
//    disabledObstacleArray = new CCArray;
    loadCharactor();
    addOneTimeBg();
    addUpperInitialObjects();
    addLowerInitialObjects();
    if (sceneType == kSceneTypeGameScene) {
//        addCoins();
        this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCDelayTime::create(15), CCCallFunc::create(this, callfunc_selector(GameLayer::addPowerUps)))) );
            addStar();
    }
    
    this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCCallFunc::create(this, callfunc_selector(GameLayer::setScore)), CCDelayTime::create(0.01))));
    
    this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCCallFunc::create(this, callfunc_selector(GameLayer::setGameTime)), CCDelayTime::create(1))));
//    schedule(schedule_selector(GameLayer::updateMovingObjects), 1.0/60);
//    schedule(schedule_selector(GameLayer::updateBodyPosition));
    


    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

}

bool GameLayer::init(SceneType pSceneType) {
    if (!CCLayer::init()) {
        return false;
    }

    Utility::setSceneType(pSceneType);
    targetDistanceToAddObstacle = winSize.width * 0.15;
    distance = 0;
    score = 0;
    coinScore = 0;
    wallSmashed = 0;
    squeezes = 0;
    isCaveWideRunning = false;
        coinsBonusWhilePower = 1;
    minute = seconds = timeToStay = 0;
    isCollisionWithCave = false;
    isCollisionWithObstacle = false;
    isBackPackPadding = true;
    starsParticle = NULL;
    sceneType = pSceneType;
    winSize = CCDirector::sharedDirector()->getWinSize();
    count = 0;
    if (sceneType == kSceneTypeGameScene) {
        Utility::isPauseScene = false;
        isDecrementingUpper = true;
        isDecrementingLower = false;
        startLower = false;
        isPowerUpActive = false;
        isLevelcompleted = false;
        isPowerBubbleShield = false;
        isStrongWallBreak = false;
        isPowerExtraLifeSpecial = false;
        isMagnetEffectApply = false;
        isLaneWide = true;
        totalLaneObjects = Utility::randomIntBetween(25, 30);
        countLaneObjects = 0;
        checkFlyDirection = false;
        isTouched = true;
        isObstacleAdding = true;
        isCharCollided = false;
        speedBurst = 0;
        bubbleShield = 0;
        powerUps = 0;
        movingWall = 0;
        wallSmashedInRow = 0;
        jetPacks = 0;
        isTinyMode = false;
        isWallCollided = false;
        isCharCollidedCoinsPowerUp = false;
        brokenWall = 0;
        countContinue = 0;
        isCharCollidedLowerCave = false;
        isCharCollidedUpperCave = false;
        countHitDownAchieve = 0;
        Utility::isGameScene = true;
        isUpperGrassCollided = false;
        previousWallTag = 0;
        targetDistanceToAddCoins = winSize.width * 2;
        targetDistanceToAddPowerUps= winSize.width * 1.7;
        obstaclePosX = 0.0f;
        obstaclePosY = 0.0f;
        obstacleTag = 0;
        Utility::setTotalGamesPlayed(Utility::getTotalGamesPlayed()+1);
        isGameOver = false;
        topY = 0.0f;
        bottomY = 0.0f;
        
        resetHeightFactorForLower = kCaveLowerLimit;
        resetHeightFactorForUpper = kCaveUpperLimit;
        
        obstacleArray = new CCArray;
        powerUpArray = new CCArray;
        coinsArray = new CCDictionary;

        lowerBodyArrayWithGrass = new CCArray;
        upperBodyArrayWithGrass = new CCArray;
        lowerBodyArrayWithoutGrass = new CCArray;
        upperBodyArrayWithoutGrass = new CCArray;
        
        isFlyUpcollided = false;
        isFlyDowncollided = false;
        
        isStartAllBg = true;
        
        speedToChange = 0.01;
//        setPhysics();
//        gb2ShapeCache = (GB2ShapeCache*) GB2ShapeCache::sharedGB2ShapeCache();
//        CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
//        
//        gb2ShapeCache->addShapesWithFile("gamePhysics.plist");
        
        setKeypadEnabled(true);
//        loadCharactor();
//        coinDictionary = new CCDictionary;
        
//        addOneTimeBg();
//        addUpperInitialObjects();
//        addLowerInitialObjects();
//        addPowerUps();
//        addCoins();

       addInitialAchievementLayer();
        extras = new Extras;
//        addStar();
//        schedule(schedule_selector(GameLayer::tick));
        //schedule(schedule_selector(GameLayer::moveCoinsPattern), 0.0);
        
//        this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCDelayTime::create(15), CCCallFunc::create(this, callfunc_selector(GameLayer::addPowerUps)))) );

//        this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCDelayTime::create(10), CCCallFunc::create(this, callfunc_selector(GameLayer::addCoins)))) );

//        this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCDelayTime::create(1.25), CCCallFunc::create(this, callfunc_selector(GameLayer::addInitialObstacle)))) );

//        this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCCallFunc::create(this, callfunc_selector(GameLayer::setScore)), CCDelayTime::create(0.01))));
//
//        this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCCallFunc::create(this, callfunc_selector(GameLayer::setGameTime)), CCDelayTime::create(1))));
//        schedule(schedule_selector(GameLayer::updateMovingObjects), 1.0/60);
//        schedule(schedule_selector(GameLayer::updateBodyPosition));
        
    } else {
        isLaneWide = true;
        isDecrementingUpper = true;
        isDecrementingLower = false;
        startLower = false;
        isPowerUpActive = false;
        isLevelcompleted = false;
        isPowerBubbleShield = false;
        isStrongWallBreak = false;
        isPowerExtraLifeSpecial = false;
        isMagnetEffectApply = false;
        totalLaneObjects = 5;
        countLaneObjects = 0;
        checkFlyDirection = false;
        isTouched = false;
        score = 1;
        coinsArray = NULL;
        isContinueClicked = false;
        timeToStay = 0;
        obstacleArray = new CCArray;
        //basic 1, 2 and 3 help
        basicHelpTag = 1;
        if (basicHelpTag == 1) {
            CCSprite * basic_1_help = CCSprite::create("basics1.png");
            basic_1_help->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
            addChild(basic_1_help, 2, basicHelpTag);
            basicHelpTag++;
        }
       
        //        CCSprite * basic_2_help = CCSprite::createWithSpriteFrameName("basic2Help.png");
        //        basic_2_help->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
        //        addChild(basic_2_help, 2);
        //        CCSprite * basic_3_help = CCSprite::createWithSpriteFrameName("basic3Help.png");
        //        basic_3_help->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
        //        addChild(basic_3_help, 2);
        
        //objective button
//        createButton("btnMenu.png", 1, CCPoint(winSize.width * 0.1, winSize.height * 0.1));
        createButton("btnContinue.png", 2, CCPoint(winSize.width * 0.8, winSize.height * 0.48));
        
        tutorial1 = CCSprite::create("tutorial_0.png");
        tutorial1->setPosition(ccp(winSize.width * 0.5, -winSize.height * 0.1));
        tutorial1->runAction(CCMoveBy::create(0.5, ccp(0, winSize.height * 0.2)));
        addChild(tutorial1, 2);
        
        tutorial2 = CCSprite::create("tutorial_1.png");
        tutorial2->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.1));
        tutorial2->setVisible(false);
        addChild(tutorial2, 2);
        
        helpTutorialCharAction = runAction(CCRepeatForever::create(CCSequence::create(CCCallFunc::create(this, callfunc_selector(GameLayer::showTutorial1)), CCDelayTime::create(0.8), CCCallFunc::create(this, callfunc_selector(GameLayer::showTutorial2)), CCDelayTime::create(0.8), NULL )));
        helpCharSprite = CCSprite::createWithSpriteFrameName("char0_0.png");
        helpCharSprite->setScale(0.3);
        helpCharSprite->setPosition(ccp(winSize.width * 0.43, -winSize.height * 0.08));
        helpCharSprite->runAction(CCMoveBy::create(0.5, ccp(0, winSize.height * 0.25)));
        addChild(helpCharSprite, 2);
        resetHeightFactorForLower = kCaveLowerLimit;
        resetHeightFactorForUpper = kCaveUpperLimit;
        
        lowerBodyArrayWithGrass = new CCArray;
        upperBodyArrayWithGrass = new CCArray;
        lowerBodyArrayWithoutGrass = new CCArray;
        upperBodyArrayWithoutGrass = new CCArray;
        
        isFlyUpcollided = false;
        isFlyDowncollided = false;
        
        isStartAllBg = true;
        
        speedToChange = 0.01;
//        setPhysics();
//        gb2ShapeCache = (GB2ShapeCache*) GB2ShapeCache::sharedGB2ShapeCache();
//        CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
//        
//        gb2ShapeCache->addShapesWithFile("gamePhysics.plist");
        
        setKeypadEnabled(true);
//        loadCharactor();
        countBasic3 = 0;
//        addOneTimeBg();
//        addUpperInitialObjects();
//        addLowerInitialObjects();
        
//        schedule(schedule_selector(GameLayer::tick));
        //schedule(schedule_selector(GameLayer::moveCoinsPattern), 0.0);
        
//        this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCCallFunc::create(this, callfunc_selector(GameLayer::setScore)), CCDelayTime::create(0.01))));
//        this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCCallFunc::create(this, callfunc_selector(GameLayer::setGameTime)), CCDelayTime::create(1))));
    }
    
    CCPoint pos = CCPoint(winSize.width * 0.85, winSize.height * 0.25);
    thumbSprite_0 = CCSprite::create("thumb_0.png");
    thumbSprite_0->setPosition(pos);
    thumbSprite_0->setVisible(false);
    addChild(thumbSprite_0);
    
    thumbSprite_1 = CCSprite::create("thumb_1.png");
    thumbSprite_1->setPosition(pos);
    thumbSprite_1->setVisible(false);
    addChild(thumbSprite_1);
    
    return true;
}

void GameLayer::addInitialAchievementLayer() {
    CCSprite *scrollBarSprite = CCSprite::createWithSpriteFrameName(kScrollBar);
    scrollBarSprite->setPosition(ccp(winSize.width * 0.5, -winSize.height * 0.25));
    scrollBarSprite->runAction(CCSequence::create(CCMoveTo::create(0.8, ccp(winSize.width * 0.5, winSize.height * 0.15)), CCDelayTime::create(3), CCMoveTo::create(0.8, ccp(winSize.width * 0.5, -winSize.height * 0.25)), NULL));

    
    CCSprite *iconTrophySprite = CCSprite::createWithSpriteFrameName("iconTrophy.png");
    iconTrophySprite->setPosition(ccp(scrollBarSprite->getContentSize().width * 0.1, scrollBarSprite->getContentSize().height * 0.5));
    scrollBarSprite->addChild(iconTrophySprite, 2);
    
    for (int i = 40; i >= 1; i--) {
           float scale = Utility::isIPad() ? 1   :0.4;
        if (Utility::getAchievementStatus(i) == 1) {
             CCString *obj_2 = (CCString*) Utility::objectiveDict()->valueForKey(CCString::createWithFormat("kAchievement_%d_1", i)->getCString());
            CCLabelBMFont *achieveLabel = CCLabelBMFont::create(obj_2->getCString(), kFontChubby, winSize.width * 0.41);
            achieveLabel->setScale(scale);
            achieveLabel->setPosition(ccp(scrollBarSprite->getContentSize().width * 0.55, scrollBarSprite->getContentSize().height * 0.5));
            scrollBarSprite->addChild(achieveLabel, 3);
            break;
        }
    }
        addChild(scrollBarSprite, 2);
}

void GameLayer::addFinalAchievementLayer(int achieved) {
    CCSprite *scrollBarSprite = CCSprite::createWithSpriteFrameName(kScrollBar);
    scrollBarSprite->setPosition(ccp(winSize.width * 0.5, -winSize.height * 0.25));
    scrollBarSprite->runAction(CCSequence::create(CCMoveTo::create(0.8, ccp(winSize.width * 0.5, winSize.height * 0.15)), CCDelayTime::create(3), CCMoveTo::create(0.8, ccp(winSize.width * 0.5, -winSize.height * 0.25)), NULL));
    addChild(scrollBarSprite);

    CCSprite *iconTrophySprite = CCSprite::createWithSpriteFrameName("iconTick.png");
    iconTrophySprite->setPosition(ccp(scrollBarSprite->getContentSize().width * 0.1, scrollBarSprite->getContentSize().height * 0.5));
    scrollBarSprite->addChild(iconTrophySprite, 2);
    
//    for (int i = 41; i >= 1; i--) {
        float scale = Utility::isIPad() ? 1   :0.4;
//        CCLog("final achievement %d %d", i, Utility::getAchievementStatus(i));
//        if (Utility::getAchievementStatus(i) == 2) {
            CCString *obj_2 = (CCString*) Utility::objectiveDict()->valueForKey(CCString::createWithFormat("kAchievement_%d_0", achieved)->getCString());
            CCLabelBMFont *achieveLabel = CCLabelBMFont::create(CCString::createWithFormat("%s", obj_2->getCString())->getCString(), kFontChubby, winSize.width * 0.41);
            achieveLabel->setScale(scale);
            achieveLabel->setPosition(ccp(scrollBarSprite->getContentSize().width * 0.55, scrollBarSprite->getContentSize().height * 0.5));
            scrollBarSprite->addChild(achieveLabel, 2);
//            break;
//        }
//    }
    
    CCUserDefault::sharedUserDefault()->flush();
}

void GameLayer::addStar() {
    int random = Utility::randomIntBetween(1, 11);
    if (random < 4) {
        float randomY = Utility::randomFloatBetween(winSize.height * 0.3, winSize.height * 0.6);
        float randonX = Utility::randomFloatBetween(winSize.width * 2.2, winSize.width * 4.2);
        CCPoint pos = CCPoint(randonX, randomY);
        PowerUps *starPower = new Star(this,"iconStar.png", kPowerType_Star, pos);
        powerUpArray->addObject(starPower);
        CC_SAFE_RELEASE(starPower);
    }
}

void GameLayer::showTutorial1() {
    helpCharSprite->runAction(CCMoveBy::create(0.8, ccp(0, -winSize.height * 0.08)));
    tutorial1->setVisible(true);
    tutorial2->setVisible(false);
}

void GameLayer::showTutorial2() {
    helpCharSprite->runAction(CCMoveBy::create(0.8, ccp(0, winSize.height * 0.08)));
    tutorial1->setVisible(false);
    tutorial2->setVisible(true);
}

void GameLayer::checkAchieve29() {
    if (Utility::getScoreForAchieve() >= 5000 && Utility::getAchievementStatus(29) == 1) {
        //achieve 29 consistent performer
        Utility::setAchievementStatus(29, 2);
        Utility::setAchievementStatus(32, 1);

//        CCString *idString = CCString::createWithFormat("com.flying.flea.consistentperformer");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_CONSISTENT_PERFORMER : "com.flying.flea.consistentperformer");
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
    }
}

void GameLayer::setGameTime() {
    seconds++;
    checkAchieve29();
    if (seconds == 60) {
        minute++;
        seconds = 0;
        if (!isCharCollidedCoinsPowerUp && Utility::getAchievementStatus(8) == 1) {
            //achieve 8
            CCLOG("nothing  to see here");
            Utility::setAchievementStatus(8, 2);
            Utility::setAchievementStatus(11, 1);
//            CCString *idString = CCString::createWithFormat("com.flying.flea.nothingtoseehere");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_NOTHING_TO_SEE_HERE : ACH_IOS_NOTHING_TO_SEE_HERE);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            
        addFinalAchievementLayer(8);
        }
        if (Utility::getAchievementStatus(18) == 1) {
            //achieve 18
            CCLOG(".60 Minutes (really seconds)");
            Utility::setAchievementStatus(18, 2);
            Utility::setAchievementStatus(21, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.60minutes");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_60_MINUTES_REALLY_SECONDS : ACH_IOS_60_MINUTES_REALLY_SECONDS);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(18);
        }
    }
    if (seconds == 30 && Utility::getAchievementStatus(2) == 1) {
        //achieve 2
        CCLOG("Spread Your Wings");
            Utility::setAchievementStatus(2, 2);
            Utility::setAchievementStatus(5, 1);
//        CCString *idString = CCString::createWithFormat("com.flying.flea.spreadyourwings");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_SPREAD_YOUR_WINGS : ACH_IOS_SPREAD_YOUR_WINGS);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        
        addFinalAchievementLayer(2);
    }
    
    if (seconds == 30 && !isCharCollided && Utility::getAchievementStatus(3) == 1) {
        //achieve 3
        CCLOG("Stay Focused");
            Utility::setAchievementStatus(3, 2);
            Utility::setAchievementStatus(6, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.stayfocused");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_STAY_FOCUSED : ACH_IOS_STAY_FOCUSED);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        
        addFinalAchievementLayer(3);
    }
    
    //for char destroy animation, if character stayed over grass more than five seconds
    if (!isStartAllBg) {
        if (isTouched && sceneType == kSceneTypeGameScene) {
            if (timeToStay == 0) {
                thumbSprite_0->setVisible(true);
            } else if (timeToStay == 1) {
                thumbSprite_0->setVisible(false);
                thumbSprite_1->setVisible(true);
            }
        }
       
        timeToStay++;
        if (timeToStay > 2) {
            playCharDestroy();
            timeToStay = 0;
        } else if (timeToStay > 1.5) {
            character->characterUserData->sprite->runAction(CCBlink::create(1, 6));
        }
    } else {
        timeToStay = 0;
        thumbSprite_0->setVisible(false);
        thumbSprite_1->setVisible(false);
    }
}

//void GameLayer::showThumb_0() {
//    
//}
//
//void GameLayer::showThumb_1() {
//    
//}
//                                
void GameLayer::setScore() {
    if (isStartAllBg && !character->characterUserData->readyForDeletion && sceneType == kSceneTypeGameScene) {
        score++;
        if (score == 4000 && Utility::getAchievementStatus(10) == 1) {
            //achieve 10
            CCLOG("4 Score");
            Utility::setAchievementStatus(10, 2);
            Utility::setAchievementStatus(13, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.4score");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_4_SCORE : ACH_IOS_4_SCORE);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(10);
        }
        if (score >=5000 && Utility::getAchievementStatus(17) == 1) {
            //achieve 17
            CCLOG("5 Bucks");
            Utility::setAchievementStatus(17, 2);
            Utility::setAchievementStatus(20, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.5bucks");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_5_BUCKS : ACH_IOS_5_BUCKS);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(17);
        }
        if (!isWallCollided && score == 10000 && Utility::getAchievementStatus(27) == 1) {
            //achieve 27
            CCLOG("silk flow");
            Utility::setAchievementStatus(27, 2);
            Utility::setAchievementStatus(30, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.silkflow");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_SILK_FLOW : ACH_IOS_SILK_FLOW);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(27);
        }
        hudLayer->updateScore(score);
//    Utility::setGamesForAchieve(score);
        
    } else if (isStartAllBg && !character->characterUserData->readyForDeletion && sceneType == kSceneTypeHelp) {
        if (isContinueClicked) {
            score++;
            hudLayer->updateScore(score);
        }
    }
    
}

void GameLayer::checkTightSqueezes(UserData *userData) {
    runAction(CCSequence::create(CCCallFunc::create(this, callfunc_selector(GameLayer::squeezesOccur)), CCDelayTime::create(0.5), CCCallFunc::create(this, callfunc_selector(GameLayer::resetSquezesVariable)), NULL));
//        userData->setCollision(true);
}

void GameLayer::squeezesOccur() {
    if (isCollisionWithCave && isCollisionWithObstacle) {
        Utility::playSound(CCString::create(kSoundForOuch), 1);
        
        isCollisionWithObstacle = false;
        isCollisionWithCave = false;
        squeezes++;
        
        float scale = Utility::isIPad() ? 1 : 0.6;
        tightSqueezeSprite = CCSprite::createWithSpriteFrameName("iconUpDown.png");
        tightSqueezeSprite->setPosition(character->characterUserData->sprite->getPosition());
        tightSqueezeLabel = CCLabelBMFont::create(CCString::createWithFormat("+%d", 100)->getCString(), kFontChubby, 0);
        tightSqueezeLabel->setPosition(ccp(tightSqueezeSprite->getContentSize().width * 1.5, tightSqueezeSprite->getContentSize().height * 0.5));
        tightSqueezeLabel->setScale(scale);
        tightSqueezeSprite->addChild(tightSqueezeLabel, 2);
        score += 100 * coinsBonusWhilePower;
        addChild(tightSqueezeSprite, 2);
        tightSqueezeSprite->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(tightSqueezeSprite->getPositionX(), winSize.height * 0.85)), CCDelayTime::create(0.3), CCFadeOut::create(0.5), NULL));
        tightSqueezeLabel->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(0.6), CCFadeOut::create(0.5)));
        
        //achieve 21
        if (Utility::getAchievementStatus(21) == 1) {
            CCLOG("big squeeze");
            Utility::setAchievementStatus(21, 2);
            Utility::setAchievementStatus(24, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.bigsqueeze");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_THE_BIG_SQUEEZE : ACH_IOS_THE_BIG_SQUEEZE);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(21);
        }
        
        //achieve 22
        if (isTinyMode && squeezes >= 2 && Utility::getAchievementStatus(22) == 1) {
            CCLOG("Mini Me");
            Utility::setAchievementStatus(22, 2);
            Utility::setAchievementStatus(25, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.minime");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_MINI_ME : ACH_IOS_MINI_ME);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(22);
        }
        //achieve 25
        if (isTinyMode && squeezes >= 4 && Utility::getAchievementStatus(25) == 1) {
            CCLOG("The Tiny Squeeze");
            Utility::setAchievementStatus(25, 2);
            Utility::setAchievementStatus(28, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.thetinysqueeze");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_THE_TINY_SQUEEZE : ACH_IOS_THE_TINY_SQUEEZE);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(25);
        }
        
//        float scale =  Utility::isIPad()?1:0.6;
//        CCLabelBMFont *label = CCLabelBMFont::create("tight squeeze occur", kFontChubby, 10);
//        label->setScale(scale);
//        label->setPosition(character->characterSprite->getPosition());
//        addChild(label, 2);
//        label->runAction(CCSequence::createWithTwoActions(CCFadeIn::create(0.5), CCFadeOut::create(0.5)));
    }
}

void GameLayer::resetSquezesVariable() {
    isCollisionWithObstacle = false;
    isCollisionWithCave = false;
}

void GameLayer::createButton(const char *spriteName, int tag, CCPoint posititon) {
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(spriteName);
    CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite, sprite, this, menu_selector(GameLayer::menuCallBack));
    menuItem->setTag(tag);
    CCMenu *menu = CCMenu::create(menuItem, NULL);
    menu->setPosition(posititon);
    addChild(menu, 2);
}

void GameLayer::menuCallBack(CCObject *menuItem) {
    Utility::playSound(CCString::create(kSoundForButtonClick), 1);
    continueMenuSprite = ((CCMenuItemSprite*)(menuItem));
    int tag = continueMenuSprite->getTag();
    if (tag == 1){
        CCDirector::sharedDirector()->replaceScene(MainMenuScene::create());
    }else if (tag == 2){
        isContinueClicked = true;
        hudLayer->pauseBtnMenu->setEnabled(true);
        stopAction(helpTutorialCharAction);
        tutorial1->setVisible(false);
        tutorial2->setVisible(false);
        helpCharSprite->setVisible(false);
        if (basicHelpTag == 3) {
            isObstacleAdding = true;
            addInitialObstacle();
        } else if (basicHelpTag == 4) {
            isObstacleAdding = true;
            addInitialObstacle();
            this->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCDelayTime::create(10), CCCallFunc::create(this, callfunc_selector(GameLayer::addInitialObstacle)))) );
        }
        continueMenuSprite->setVisible(false);
        isGameOver = false;
        flyDirection = kFlyDown;
        int basicTag = basicHelpTag;
        removeChildByTag(--basicTag);
        checkFlyDirection = false;
        isTouched = true;
    } else if (tag == 3){
        isTouched = true;
        CCDirector::sharedDirector()->replaceScene(GameScene::create(kSceneTypeGameScene));
    }
}

void GameLayer:: unloadCharacter() {
//    this->removeChild(character->characterUserData->sprite);
    character->characterUserData->sprite->stopAllActions();
    character->characterUserData->readyForDeletion = true;
    character->characterVirtualUserData->readyForDeletion = true;
    CC_SAFE_RELEASE_NULL(character);
}

void GameLayer::loadCharactor(){
    if(Utility::getCharactorType() == kCharacterType_VinnyGreen){
        character = new VinnyGreenCharacter(this);
    }else if (Utility::getCharactorType() == kCharacterType_BellaRed){
        character = new BellaRedCharater(this);
    }else if(Utility::getCharactorType() == kCharacterType_JohnyOrange){
        character = new JohnyOrangeCharacter(this);
    }else if (Utility::getCharactorType() == kCharacterType_NormanBlue) {
        character = new NormanBlueCharacter(this);
    }
}

void GameLayer::addPowerUps() {
    //  powerUpArray->removeAllObjects();
    float randomY = Utility::randomFloatBetween(winSize.height * 0.3, winSize.height * 0.6);
    float randonX = Utility::randomFloatBetween(winSize.width * 1.3, winSize.width * 2.1);
    CCPoint pos = CCPoint(randonX, randomY);
    int random = Utility::randomIntBetween(400, 404);
    PowerUps *powerUp;
    switch ((PowerUpType)random) {
        case kPowerType_SpeedBurst:
            powerUp = new SpeedBurst(this,"powerUp_0.png", kPowerType_SpeedBurst, pos);
            break;
        case kPowerType_SuperRocket:
            powerUp = new SuperRocket(this,"powerUp_1.png", kPowerType_SuperRocket, pos);
            break;
        case kPowerType_BubbleShield:
            powerUp = new BubbleShield(this,"powerUp_2.png", kPowerType_BubbleShield, pos);
            break;
        case kPowerType_TinyMode:
            powerUp = new TinyMode(this,"powerUp_3.png", kPowerType_TinyMode, pos);
            break;
        default:
            break;
    }
    powerUpArray->addObject(powerUp);
    CC_SAFE_RELEASE(powerUp);
}

void GameLayer::movePowerUpObjects() {
    CCObject *obj;
    PowerUps *powerUpObj = NULL;
    CCARRAY_FOREACH(powerUpArray, obj) {
        powerUpObj = (PowerUps*) obj;
        float pos = powerUpObj->spriteUserData->sprite->getPositionX();
        pos +=  -getGameSpeed();
        if (pos  <  -10) {
//            this->removeChild(powerUpObj->spriteUserData->sprite, true);
            powerUpObj->spriteUserData->readyForDeletion = true;
//            powerUpArray->removeObject(powerUpObj);
        } else {
            powerUpObj->spriteUserData->sprite->setPositionX(pos);
//            powerUpObj->spriteUserData->setPosition(powerUpObj->spriteUserData->sprite->getPosition());
        }
    }
}

float GameLayer::getGameSpeed(){
    float gameSpeed = Utility::getInitGameSpeed();
    gameSpeed += getPowerUpValue();
    return gameSpeed;
}

float GameLayer::getPowerUpValue(){
    float value = 0;
    if (this->isPowerUpActive) {
        value = ((Utility::isPad)? 10 : 5) * 2;
    }
    return value;
}

void GameLayer::powerActionTimer(float delay) {
    runAction(CCSequence::create(CCDelayTime::create(0.5),CCCallFunc::create(this, callfunc_selector(GameLayer::blinkAction)),CCDelayTime::create(delay), CCCallFunc::create(this, callfunc_selector(GameLayer::resetSpeed)),CCDelayTime::create(3), CCCallFunc::create(this, callfunc_selector(GameLayer::resetCollisionFactor)),  NULL));
}

void GameLayer::resetSpeed() {
    if (starsParticle != NULL) {
        removeChild(starsParticle, true);
        CC_SAFE_RELEASE_NULL(starsParticle);
    }
    flyDirection = kFlyDown;
    isPowerUpActive = false;
    speedToChange = 0.001;
    character->characterUserData->sprite->runAction(CCBlink::create(2, 10));
}

void GameLayer::resetCollisionFactor() {
    isStrongWallBreak = false;
    isMagnetEffectApply = false;
    coinsBonusWhilePower = 1;
}

void GameLayer::blinkAction() {
    character->runAction(CCBlink::create(1, 10));
}

void GameLayer::runPower(UserData *userData, float delayPowerUp) {
    isCharCollidedCoinsPowerUp = true;

    powerUps++;
    if (powerUps == 2 && Utility::getAchievementStatus(15) == 1) {
        CCLOG("double up");
        //achieve 15        
        Utility::setAchievementStatus(15, 2);
        Utility::setAchievementStatus(18, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.doubleup");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_DOUBLE_UP : ACH_IOS_DOUBLE_UP);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(15);
    }
    CCObject *obj;
    PowerUps *powerUpObj;
    CCARRAY_FOREACH(powerUpArray, obj) {
        powerUpObj = (PowerUps*) obj;
        if (powerUpObj->spriteUserData->userDataType == kPowerType_TinyMode) {
            isTinyMode = true;
            Utility::playSound(CCString::create(kSoundForShrinkPower), 1);
        }
        
        if (powerUpObj->spriteUserData->userDataType == kPowerType_SuperRocket) {
            Utility::playSound(CCString::create(kSoundForPowerUpLaunch), 1);
        }
        
        if (powerUpObj->spriteUserData->userDataType == kPowerType_SpeedBurst) {
            Utility::playSound(CCString::create(kSoundForPowerUpLaunch), 1);
        }
        
        if (userData->sprite->getTag() == powerUpObj->spriteUserData->getTag()) {
            powerUpObj->actionPerformed(userData, delayPowerUp);
            removePowerUp(powerUpObj);
            break;
//            this->removeChild(powerUpObj->spriteUserData->sprite, true);
//            powerUpObj->spriteUserData->readyForDeletion = true;
//            powerUpArray->removeObject(powerUpObj);
//            removePowerUp(powerUpObj);
        }
    }
}

void GameLayer::removePowerUp (PowerUps *powerUp) {
//    this->removeChild(powerUp->spriteUserData->sprite);
    powerUp->spriteUserData->readyForDeletion = true;
    powerUpArray->removeObject(powerUp);
    powerUp = NULL;
}

void GameLayer::countSpeedBurst() {
    speedBurst++;
    if (speedBurst == 2 && Utility::getAchievementStatus(7) == 1) {
        //achieve 7
        CCLOG("speed bump");
        
        Utility::setAchievementStatus(7, 2);
        Utility::setAchievementStatus(10, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.speedbump");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_SPEED_BUMP : ACH_IOS_SPEED_BUMP);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(7);
    }
}

void GameLayer::countWideLaneSeconds(int seconds) {
    wideLaneSeconds = Utility::getTotalWideLaneSeconds() + seconds;
    Utility::setTotalWideLaneSeconds(wideLaneSeconds);
    if (wideLaneSeconds == 120 && Utility::getAchievementStatus(41) == 1) {
        //achieve 41
        CCLOG("Highway Runner");
        
        Utility::setAchievementStatus(41, 2);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.highwayrunner");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_HIGHWAY_RUNNER : ACH_IOS_HIGHWAY_RUNNER);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(41);
    }
}

void GameLayer::countRocket() {
    rockets++;
    if (rockets == 10 && Utility::getAchievementStatus(32) == 1) {
        //achieve 32
        CCLOG("The Astronaut");
        Utility::setAchievementStatus(32, 2);
        Utility::setAchievementStatus(35, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.theastronaut");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_THE_ASTRONAUT : ACH_IOS_THE_ASTRONAUT);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(32);
    }
}

void GameLayer::countBrokenWall() {
    brokenWall++;
    if (brokenWall == 5 && Utility::getAchievementStatus(36) == 1) {
        //achieve 36
        CCLOG("com.flying.flea.rockandroll");
        
        Utility::setAchievementStatus(36, 2);
        Utility::setAchievementStatus(39, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.rockandroll");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_ROCK_N_ROLL : ACH_IOS_ROCK_N_ROLL);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(36);
    }
}

void GameLayer::countBubbleShield() {
    if (Utility::getAchievementStatus(12) == 1) {
        //achieve 12
        CCLOG("Mr Bubbles");
        CCLOG("get achieve status %d", Utility::getAchievementStatus(12));
        Utility::setAchievementStatus(12, 2);
        Utility::setAchievementStatus(15, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.MrBubbles");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_MR_BUBBLES : ACH_IOS_MR_BUBBLES);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(12);
    }
}

void GameLayer::addCoins() {
//    CCObject *keyObject;
//    CCArray* allKeys = coinsArray->allKeys();
//    CCARRAY_FOREACH(allKeys, keyObject) {
//        CCString *keyString = (CCString *)keyObject;
//        Coins *coinsObj = (Coins*)coinsArray->objectForKey(keyString->getCString());
////        this->removeChild(coinsObj->spriteUserData->sprite, true);
//        coinsObj->spriteUserData->readyForDeletion = true;
////        coinsArray->removeObjectForKey(keyString->getCString());
//    }
    CoinsPattern *coinsPattern = new CoinsPattern;
    coinsPattern->createWithCoins(this);
    CC_SAFE_RELEASE(coinsPattern);
}

void GameLayer::moveCoinsPattern() {
    CCObject *keyObject;
    CCArray* allKeys = coinsArray->allKeys();
    CCARRAY_FOREACH(allKeys, keyObject) {
        CCString *keyString = (CCString *)keyObject;
        Coins *coinsObj = (Coins*)coinsArray->objectForKey(keyString->getCString());
        UserData *data= coinsObj->spriteUserData;
        if (!data->getReadyForDeletion()) {
            float pos = coinsObj->spriteUserData->sprite->getPositionX();
            pos +=  -getGameSpeed();
            if (pos  <  -coinsObj->spriteUserData->sprite->getContentSize().width) {
                coinsObj->resetCoins();
            } else {
                coinsObj->spriteUserData->sprite->setPositionX(pos);
//                coinsObj->spriteUserData->sprite->setPosition(coinsObj->spriteUserData->sprite->getPosition());
            }
            
        }
    }
}

void GameLayer::runCoinsAnimation(UserData *coinUserData, const char *frameName) {
    //update coin score
    hudLayer->updateCoinScore(++coinScore);
    Utility::playSound(CCString::create(kSoundForCoinCollection), 1);
    if (coinScore == 75 && Utility::getAchievementStatus(1) == 1) {
        //achieve 1
        Utility::setAchievementStatus(1, 2);
        Utility::setAchievementStatus(4, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.goldrush");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_GOLD_RUSH : ACH_IOS_GOLD_RUSH);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        
        addFinalAchievementLayer(1);
    }
    isCharCollidedCoinsPowerUp = true;
//    CMAnimation *animation;
//    animateAction = new CCAnimate();
//    animation = (CMAnimation*) CMAnimation::animationWithFrame(frameName, 10, 0.05);
//    animateAction->initWithAnimation(animation);
//    coinUserData->readyForDeletion = true;
//    CCString *key = CCString::createWithFormat("%d", coinUserData->getTag());
//    Coins *coin = (Coins*)coinsArray->objectForKey(key->getCString());
//    coin->runAnimation(frameName);
//    CCString *string = CCString::create(frameName);
//    coin->spriteUserData->sprite->runAction(CCSequence::createWithTwoActions(CCCallFunc::create(coin, callfunc_selector(Coins::setDeletionForCoin)), CCCallFuncND::create(coin, callfuncND_selector(Coins::setDeletionForCoin), (void*)frameName) ));
//    removeCoin(coin);
    
//    CCObject *keyObject;
//    CCArray* allKeys = coinsArray->allKeys();
//    CCString *key = CCString::createWithFormat("%d", coinUserData->getTag());
//    Coins *coinObj = (Coins*)coinsArray->objectForKey(key->getCString());
//    if (coinObj != NULL) {
//    coinObj->resetCoins();
//    }

//    CCARRAY_FOREACH(allKeys, keyObject) {
//        CCString *keyString = (CCString *)keyObject;
//        Coins *coinsObj = (Coins*)coinsArray->objectForKey(keyString->getCString());
//        if (coinsObj->spriteUserData->getTag() == coinUserData->getTag()) {
////            coinsObj->sprite->runAction(CCSequence::createWithTwoActions(animateAction, CCCallFunc::create(coinsObj, callfunc_selector(Coins::resetCoins))));
//            coinsObj->sprite->runAction( CCCallFunc::create(coinsObj, callfunc_selector(Coins::resetCoins)));
//        }
//    }
}

void GameLayer::characterStopFlying() {
    flyDirection = kFlyStop;
}

void GameLayer::updateBodyPosition(float dt) {

    int coinsArrayCount = coinsArray->count();
    if (coinsArrayCount > 0) {
        for (int i = coinsArrayCount - 1; i >= 0; i--) {
            CCString *string = (CCString*) coinsArray->allKeys()->objectAtIndex(i);
            Coins *coin = (Coins*)coinsArray->objectForKey(string->getCString());
            if (coin != NULL) {
                if(isStartAllBg){
                    coin->updateBodyPos();
                }
            }
        }
    }
    
    int obstacleArrayCount = obstacleArray->count();
    if (obstacleArrayCount > 0) {
        for (int i = obstacleArrayCount - 1; i >= 0; i--) {
            Obstacle *obstacle = (Obstacle*) obstacleArray->objectAtIndex(i);
            if (obstacle != NULL) {
                if(isStartAllBg) {
                    obstacle->updateBodyPos();
                }
            }
        }
    }
    RandomParallaxBg *randomObj;
    CCObject *obj;
    CCARRAY_FOREACH(lowerBodyArrayWithGrass, obj) {
        randomObj = (RandomParallaxBg*) obj;
        if (randomObj->isActive) {
            randomObj->updateBodyPos();
        }
    }
    
    CCARRAY_FOREACH(upperBodyArrayWithGrass, obj) {
        randomObj = (RandomParallaxBg*) obj;
        if (randomObj->isActive) {
            randomObj->updateBodyPos();
        }
    }
    
    CCARRAY_FOREACH(lowerBodyArrayWithoutGrass, obj) {
        if (randomObj->isActive){
            randomObj->updateBodyPos();
        }
    }
    
    CCARRAY_FOREACH(upperBodyArrayWithoutGrass, obj) {
        randomObj = (RandomParallaxBg*) obj;
        if (randomObj->isActive) {
            randomObj->updateBodyPos();
        }
    }
    character->updateBodyPos();

}

void GameLayer::updateMovingObjects(float dt) {
    if (starsParticle != NULL) {
        starsParticle->setPosition(ccp(character->characterUserData->sprite->getPositionX() * 0.8, character->characterUserData->sprite->getPositionY()));
    }
  

    if (!isStartAllBg) {
        Utility::pauseSound(paddingSoundId);
        Utility::pauseSound(thrashingSoundId);
    }
    
    if (Utility::isPauseScene) {
        hudLayer->pauseScreen();
        Utility::isPauseScene = false;
    }
    
//    if (flyDirection == kFlyDown && !isGameOver) {
//        character->flyDown();
//    } else if(flyDirection == kFlyUp && !isGameOver){
//        character->flyUp();
//    }
    // to placed character at center afer help basic complete
    if (sceneType == kSceneTypeHelp && checkFlyDirection) {
        isTouched = false;
        if (character->characterUserData->sprite->getPositionY() < winSize.height * 0.5) {
            flyDirection = kFlyUp;
        } else if (character->characterUserData->sprite->getPositionY() > winSize.height * 0.5) {
            flyDirection = kFlyDown;
        }
        if (character->characterUserData->sprite->getPositionY() < winSize.height * 0.55 && character->characterUserData->sprite->getPositionY() > winSize.height * 0.45) {
            flyDirection = kFlyStop;
        }
    }
    
    
    if (isStartAllBg && !isLevelcompleted) {
        if (randomParallaxForBg != NULL) {
            randomParallaxForBg->moveBg();
        }
        moveParallaxObjects();
        if (sceneType != kSceneTypeHelp) {
//            movePowerUpObjects();
            //            moveCoinsPattern();
//            moveObstacleObjects();
            int coinsArrayCount = coinsArray->count();
            if (coinsArrayCount > 0) {
                for (int i = coinsArrayCount - 1; i >= 0; i--) {
                    CCString *string = (CCString*) coinsArray->allKeys()->objectAtIndex(i);
                    Coins *coin = (Coins*)coinsArray->objectForKey(string->getCString());
                    if (coin != NULL) {
                        if(!coin->spriteUserData->getReadyForDeletion() && coin->spriteUserData->getSprite() != NULL) {
                            if(isMagnetEffectApply &&  !coin->spriteUserData->isForceApplied && coin->spriteUserData->getSprite()->getPosition().x <= winSize.width * 0.5 && coin->spriteUserData->getSprite()->getPosition().x > 0) {
                                coin->spriteUserData->isForceApplied = true;
                                coin->ApplyMagnetPower();
                            }
                                float pos = coin->spriteUserData->sprite->getPositionX();
                                pos +=  -getGameSpeed();
                                if (pos < -coin->spriteUserData->sprite->getContentSize().width) {
                                    removeCoin(coin);
                                } else if(isStartAllBg && !coin->spriteUserData->isForceApplied ){
                                    coin->spriteUserData->sprite->setPositionX(pos);
                                }
                        }
                        
                    }
                    
                }
            }
            int powerUpsArrayCount = powerUpArray->count();
            if (powerUpsArrayCount > 0) {
                for (int i = powerUpsArrayCount - 1; i >= 0; i--) {
                    PowerUps *powerUp = (PowerUps*)powerUpArray->objectAtIndex(i);
                    if (powerUp != NULL) {
                        float pos = powerUp->spriteUserData->sprite->getPositionX();
                        pos +=  -getGameSpeed();
                        if (pos  <  -50 ) {
                            removePowerUp(powerUp);
                        } else if(isStartAllBg) {
                            powerUp->spriteUserData->sprite->setPositionX(pos);
                        }
                    }
                }
            }
            
        }
//        else {
//            if (basicHelpTag > 2) {
//                moveObstacleObjects();
//            }
//        }
    }
    
    if (basicHelpTag > 2 || sceneType == kSceneTypeGameScene ) {
        int obstacleArrayCount = obstacleArray->count();
        if (obstacleArrayCount > 0) {
            //        for (int i = 0; i < obstacleArrayCount ; i++) {
            for (int i = obstacleArrayCount - 1; i >= 0; i--) {
                Obstacle *obstacle = (Obstacle*) obstacleArray->objectAtIndex(i);
                if (obstacle != NULL) {
                    float pos = obstacle->spriteUserData->sprite->getPositionX();
                    pos +=  -getGameSpeed();
                    if ( pos  <  -50 ) {
                        removeObstacle(obstacle);
                        obstacleArray->removeObject(obstacle);
                    } else if(isStartAllBg) {
                        obstacle->spriteUserData->sprite->setPositionX(pos);
                    }
                }
            }
        }
    }
 
    if (lastUpperRandomParallax->spriteUserData->getSprite()->getPosition().x < winSize.width + 10) {
        if (isContinueClicked || sceneType == kSceneTypeGameScene) {
            countLaneObjects++;
        }
        if (countLaneObjects > totalLaneObjects) {
            if (sceneType == kSceneTypeHelp) {
                if (basicHelpTag == 2 && count == 0) {
                    isContinueClicked = false;
                    isObstacleAdding = false;
                    hudLayer->pauseBtnMenu->setEnabled(false);
                    continueMenuSprite->setVisible(true);
                    checkFlyDirection = true;
                    CCSprite * basic_1_help = CCSprite::create("basics2.png");
                    basic_1_help->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
                    addChild(basic_1_help, 2, basicHelpTag);
                    basicHelpTag++;
                    totalLaneObjects += 10;
                    count = 0;
                }
                else if (basicHelpTag == 4 && count == 0) {
                    isContinueClicked = false;
                    isObstacleAdding = false;
                    hudLayer->pauseBtnMenu->setEnabled(false);
                    removeChild(continueMenuSprite);
                    checkFlyDirection = true;
                    CCSprite * basic_1_help = CCSprite::create("basics4.png");
                    basic_1_help->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
                    addChild(basic_1_help, 2, basicHelpTag);
                    createButton(kButtonPlay, 3, CCPoint(winSize.width * 0.5, winSize.height * 0.25));
                    totalLaneObjects += 10;
                    count = 0;
                }
                
            }
            isLaneWide = false;
            if (sceneType == kSceneTypeHelp) {
                isLaneWide = true;
            }
            count++;
            if (count > 30 && sceneType == kSceneTypeGameScene) {
                isLaneWide = true;
                totalLaneObjects += 50;
                count = 0;
            }
        }
        if (basicHelpTag == 3 && isContinueClicked) {
            countBasic3++;
        }
        if (countBasic3 > 10 ) {
            if (sceneType == kSceneTypeHelp) {
                if (basicHelpTag == 3) {
                    isContinueClicked = false;
                    isObstacleAdding = false;
                    hudLayer->pauseBtnMenu->setEnabled(false);
                    continueMenuSprite->setVisible(true);
                    checkFlyDirection = true;
                    CCSprite * basic_1_help = CCSprite::create("basics3.png");
                    basic_1_help->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
                    addChild(basic_1_help, 2, basicHelpTag);
                    basicHelpTag++;
                    countBasic3 = 0;
                    totalLaneObjects += 10;
                    count = 0;
                }
            }
        }
        
        int random = Utility::randomIntBetween(0, 10);
        if (random < 8) {
            addUpperRandomParrallaxObjectsWithGrass();
        } else {
            addUpperRandomParrallaxObjectsWithoutGrass();
        }
    }
    
    if (lastLowerRandomParallax->spriteUserData->getSprite()->getPosition().x < winSize.width + 10) {
        int random = Utility::randomIntBetween(0, 10);
        if (random < 8) {
            addLowerRandomParrallaxObjectsWithGrass();
        } else {
            addLowerRandomParrallaxObjectsWithoutGrass();
        }
    }
    if(isStartAllBg) {
    distance += getGameSpeed() * 0.25;
    //add an obstacles
    if (distance > targetDistanceToAddObstacle) {
        float val = Utility::isIPad() ? 0.08 : 0.1;
        targetDistanceToAddObstacle += winSize.width * val;
        addInitialObstacle();
        
        //add coins
        if (distance >targetDistanceToAddCoins && sceneType == kSceneTypeGameScene) {
            targetDistanceToAddCoins += winSize.width * 1;
            runAction(CCSequence::createWithTwoActions(CCDelayTime::create(0.1), CCCallFunc::create(this, callfunc_selector(GameLayer::addCoins))));

        }
    }
    }

}

void GameLayer::step(float dt) {
    float32 frameTime = dt;
    int stepsPerformed = 0;
    while ( (frameTime > 0.0) && (stepsPerformed < MAXIMUM_NUMBER_OF_STEPS) ){
        float32 deltaTime = std::min( frameTime, FIXED_TIMESTEP );
        frameTime -= deltaTime;
        if (frameTime < MINIMUM_TIMESTEP) {
            deltaTime += frameTime;
            frameTime = 0.0f;
        }
        world->Step(deltaTime,VELOCITY_ITERATIONS,POSITION_ITERATIONS);
        character->characterUserData->sprite->update(dt);
        stepsPerformed++;
//        [self afterStep]; // process collisions and result from callbacks called by the step
    }
    world->ClearForces ();
}

void GameLayer:: tick(float dt){
    world->Step(dt, 8, 1);
//    step(dt);
    if (flyDirection == kFlyDown && !isGameOver) {
        character->flyDown();
    } else if(flyDirection == kFlyUp && !isGameOver){
        character->flyUp();
    }
    for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
        if ((UserData *)(b->GetUserData()) != NULL) {
            UserData *userData = (UserData *)b->GetUserData();
            if (userData!= NULL && userData->getReadyForDeletion() == true) {
                this->removeChild(userData->sprite);
                CC_SAFE_RELEASE(userData->sprite);
                CC_SAFE_RELEASE_NULL(userData);
                world->DestroyBody(b);
            }else if (userData != NULL) {
                
                    b2Vec2 vect = b2Vec2(Utility::toMeters(CCPoint(userData->getSprite()->getPositionX(),userData->getSprite()->getPositionY())));
                    b->SetTransform(vect, CC_DEGREES_TO_RADIANS(-userData->getSprite()->getRotation()));
                if (userData != NULL && userData->getUserDataType() == KCharactor) {
                    if ( character->shouldShrinked) {
                        if (!character->shrinked) {
                            character->shrinked = true;
                            character->shouldResetBody = false;
                            world->DestroyBody(b);
                            character->createBodyAndShape();
                        } else if (character->shouldResetBody){
                            character->shouldShrinked = false;
                            world->DestroyBody(b);
                            character->createBodyAndShape();
                        }
                    }
                }
            }
        }
    }
}

void GameLayer::removeCoin(Coins *coin) {
    CCString *key = CCString::createWithFormat("%d", coin->spriteUserData->getTag());
//    removeChild(coin->spriteUserData->getSprite(), true);
    coin->spriteUserData->readyForDeletion = true;
    coinsArray->removeObjectForKey(key->getCString());
    CC_SAFE_RELEASE_NULL(coin);
}

void GameLayer::setWideLane() {
    isCaveWideRunning = true;
    isLaneWide = true;
}

void GameLayer::resetWideLane() {
    isCaveWideRunning = false;
    isLaneWide = false;
    hudLayer->progressTimer->removeFromParent();
}

void GameLayer::playCharDestroy() {
    isCharCollided = true;
    if (isPowerBubbleShield) {
        Utility::playSound(CCString::create(kSoundForBubbleShieldCollided), 1);
    }
    if (!isPowerBubbleShield && !isPowerExtraLifeSpecial && !isStrongWallBreak && !character->isDead) {
        pauseAllTargets();
        isGameOver = true;
    Utility::playSound(CCString::create(kSoundForDieCharacter), 1);
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        if (starsParticle != NULL) {
            removeChild(starsParticle, true);
            CC_SAFE_RELEASE_NULL(starsParticle);
        }
        character->characterUserData->sprite->runAction(CCSequence::createWithTwoActions(CCSpawn::createWithTwoActions(CCRotateBy::create(0.5, 360), CCMoveBy::create(1.5, ccp(winSize.width * 0.5, -winSize.height * 2))), CCCallFunc::create(this, callfunc_selector(GameLayer::goToLevelComplete))));
    }
}

void GameLayer::pauseAllTargets() {
    pauseSchedulerAndActions();
    isTouched = false;
    isStartAllBg = false;
    hudLayer->pauseBtnMenu->setEnabled(false);
    flyDirection = kFlyDown;
//    character->characterUserData->readyForDeletion = true;
    character->isDead = true;
}


void GameLayer::resumeAllTargets() {
    resumeSchedulerAndActions();
    loadCharactor();
    isStrongWallBreak = true;
    runAction(CCSequence::createWithTwoActions(CCDelayTime::create(1), CCCallFunc::create(this, callfunc_selector(GameLayer::resetIsStrongWallBreak))));
    isTouched = true;
    isStartAllBg = true;
    hudLayer->pauseBtnMenu->setEnabled(true);
    flyDirection = kFlyStop;
    character->isDead = false;
}

void GameLayer::resetIsStrongWallBreak() {
    isStrongWallBreak = false;
}

void GameLayer::addWallBreakParticle() {
    wallBreakParticle = CCParticleSystemQuad::create("nawBrokenWallParticles.plist");
    wallBreakParticle->setTotalParticles(10);
    wallBreakParticle->setPosition(ccp(character->characterUserData->sprite->getPositionX(), character->characterUserData->sprite->getPositionY()));
    addChild(wallBreakParticle, 1);
    wallBreakParticle->setAutoRemoveOnFinish(true);
}

Obstacle* GameLayer::getobstacleObj(UserData *userData) {
    Obstacle *obsObj;
    CCObject *obj;
    CCARRAY_FOREACH(obstacleArray, obj) {
        obsObj = (Obstacle*) obj;
        if (obsObj->spriteUserData->sprite->getTag() == userData->getTag()) {
            break;
        }
    }
    return obsObj;
}

void GameLayer::playWallBreakAnimation(UserData *weakWall) {
     //   if (!weakWall->getCollision()) {
            addWallBreakParticle();
    Utility::playSound(CCString::create(kSoundForRockCollision), 1);
    if (isPowerUpActive) {
        wallSmashedInRow++;
        if (wallSmashedInRow == 10 && Utility::getAchievementStatus(26) == 1) {
            //achieve 26
            CCLOG("Double Crush");
            Utility::setAchievementStatus(26, 2);
            Utility::setAchievementStatus(29, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.doublecrush");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_DOUBLE_CRUSH : ACH_IOS_DOUBLE_CRUSH);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(26);
        }
    }
    int tagDifference = 0;
    if (weakWall->getTag() != previousWallTag) {
         tagDifference = weakWall->sprite->getTag() - previousWallTag;
    }
    if (tagDifference == 1) {
        countWallSmashedWithoutSkip++;
        if (countWallSmashedWithoutSkip == 10 && Utility::getAchievementStatus(13) == 1) {
            //achieve 13
            CCLOG("Nothing Left Behind");
            Utility::setAchievementStatus(13, 2);
            Utility::setAchievementStatus(16 , 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.nothingleftbehind");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_NOTHING_LEFT_BEHIND : ACH_IOS_NOTHING_LEFT_BEHIND);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(13);
            countWallSmashedWithoutSkip = 0;
        }
    } else {
        countWallSmashedWithoutSkip = 0;
    }
    previousWallTag = weakWall->sprite->getTag();
    
    isWallCollided = true;
    isCharCollided = true;
    
        wallSmashed++;
    if (wallSmashed == 5 && Utility::getAchievementStatus(4) == 1) {
        //achieve 4
        CCLOG("Crush Em");
        Utility::setAchievementStatus(4, 2);
        Utility::setAchievementStatus(7 , 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.crushem");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_CRUSH_EM : ACH_IOS_CRUSH_EM);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(4);
    }
    if (wallSmashed == 10 && Utility::getAchievementStatus(5) == 1) {
        //achieve 5
        CCLOG("Hit It!");
        Utility::setAchievementStatus(5, 2);
        Utility::setAchievementStatus(8 , 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.hitit");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_HIT_IT : ACH_IOS_HIT_IT);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(5);
    }
    if (wallSmashed == 100 && Utility::getAchievementStatus(19) == 1) {
        //achieve 19
        CCLOG("The big break");
        Utility::setAchievementStatus(19, 2);
        Utility::setAchievementStatus(22 , 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.bigbreak");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_THE_BIG_BREAK : ACH_IOS_THE_BIG_BREAK);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(19);
    }

    if (Utility::getTotalWallSmashedLifeTime() == 5000  && Utility::getAchievementStatus(40) == 1) {
        CCLOG("Striker");
        //achieve 40
        Utility::setAchievementStatus(40, 2);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.striker");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_MR_STRIKER : ACH_IOS_MR_STRIKER);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(40);
    }
    
    //    CCObject *obj;
    Obstacle *obstacleObj;
    //    CCARRAY_FOREACH(obstacleArray, obj) {
    obstacleObj = getobstacleObj(weakWall);
    if(obstacleObj->spriteUserData->getTag() == weakWall->sprite->getTag()) {
        if (obstacleObj->isWallMoving) {
            movingWall++;
            if (Utility::getAchievementStatus(16) == 1) {
                //achieve 16
                CCLOG(".Moving Target");
                Utility::setAchievementStatus(16, 2);
                Utility::setAchievementStatus(19 , 1);
                
                //                    CCString *idString = CCString::createWithFormat("com.flying.flea.movingtarget");
                CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_MOVING_TARGET : ACH_IOS_MOVING_TARGET);
                CCString *msgString = CCString::createWithFormat("");
                Utility::unlockAchievemnt(idString, msgString);
                addFinalAchievementLayer(16);
            }
            //achieve 28
            if (movingWall == 4 && Utility::getAchievementStatus(28) == 1) {
                CCLOG("Quad Moving target");
                Utility::setAchievementStatus(28, 2);
                Utility::setAchievementStatus(31 , 1);
                
                //                    CCString *idString = CCString::createWithFormat("com.flying.flea.quadmovingtarget");
                CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_QUAD_MOVING_TARGET : ACH_IOS_QUAD_MOVING_TARGET);
                CCString *msgString = CCString::createWithFormat("");
                Utility::unlockAchievemnt(idString, msgString);
                addFinalAchievementLayer(28);
            }
        }
        int obstacleBreakScore = 50;
        if (obstacleObj->spriteUserData->userDataType == kObstacleType_Strong) {
            obstacleBreakScore = 100 * coinsBonusWhilePower;
        } else  if (obstacleObj->spriteUserData->userDataType == kObstacleType_Weak){
            obstacleBreakScore = 50 * coinsBonusWhilePower;
        }
        score += obstacleBreakScore;
        float scale = Utility::isIPad() ? 1 : 0.6;
        blastSprite = CCSprite::createWithSpriteFrameName("iconBlast.png");
        blastSprite->setPosition(obstacleObj->spriteUserData->sprite->getPosition());
        //            if (obstacleBreakScore == 0) {
        //                obstacleBreakScore = 50;
        //            }
        
        blastLabel = CCLabelBMFont::create(CCString::createWithFormat("+%d", obstacleBreakScore)->getCString(), kFontChubby, 0);
        blastLabel->setPosition(ccp(blastSprite->getContentSize().width * 1.5, blastSprite->getContentSize().height * 0.5));
        blastLabel->setScale(scale);
        blastSprite->addChild(blastLabel, 2);
        
        addChild(blastSprite, 2);
        blastSprite->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(blastSprite->getPositionX(), winSize.height * 0.85)), CCDelayTime::create(0.3), CCFadeOut::create(0.5), CCCallFunc::create(this, callfunc_selector(GameLayer::removeBlastSprite)),  NULL));
        blastLabel->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(0.6), CCFadeOut::create(0.5)));
        
        if (obstacleObj->spriteUserData->sprite->numberOfRunningActions() == 0 || (obstacleObj->spriteUserData->sprite->numberOfRunningActions() == 1 && obstacleObj->isWallMoving)) {
            obstacleObj->spriteUserData->sprite->runAction(CCSequence::createWithTwoActions(CCAnimate::create((CMAnimation*) CMAnimation::animationWithFrame("brokenWall_", 5, 0.05)), CCCallFunc::create(obstacleObj, callfunc_selector(Obstacle::removeWeakWallAnimation))));
        }
        //        }
    }
    this->runAction(CCSequence::create(CCCallFunc::create(character, callfunc_selector(Character::addEyesAnimation)), CCDelayTime::create(0.15), CCCallFunc::create(character, callfunc_selector(Character::removeEyesAnimation)), NULL));
}

void GameLayer::removeBlastSprite() {
removeChild(blastSprite, true);
}
//void GameLayer::updateContinueTimer() {
//    continueLayer->updateTimer();
//}

void GameLayer::goToLevelComplete() {
//    character->characterSprite->setPosition(ccp(winSize.width * 0.25, winSize.height * 0.5));
//    isCharCollided = false;
//    isTouched = true;
//    isStartAllBg = true;
//    hudLayer->pauseBtnMenu->setEnabled(true);
//    character->characterUserData->readyForDeletion = false;
//    isTouched = true;
//    character->isDead = false;
    
    if (sceneType == kSceneTypeGameScene) {
        //in a game
        if (score > Utility::getPlayerScore(0) && (Utility::getCharactorType() == kCharacterType_BellaRed || Utility::getCharactorType() == kCharacterType_VinnyGreen) && Utility::getAchievementStatus(37) == 1) {
            //achieve 37
            CCLOG("The chameleon");
            Utility::setAchievementStatus(37, 2);
            Utility::setAchievementStatus(40, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.callyourbuddies");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_CALL_YOUR_BUDDIES : ACH_IOS_CALL_YOUR_BUDDIES);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(37);
        }
        
        int totalBars = 0;
        for (int i = 0; i < 5; i++) {
            int getStatus = Utility::getBarsInUpgrades((PowerType)i);
            if (getStatus == 5) {
                totalBars++;
                if (totalBars == 5 && Utility::getAchievementStatus(38) == 1) {
                    //achieve 38
                    CCLOG("Mr. Ritchie Rich");
                    Utility::setAchievementStatus(38, 2);
                    Utility::setAchievementStatus(41, 1);
                    
//                    CCString *idString = CCString::createWithFormat("com.flying.flea.ritchierich");
                    CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_MR_RITCHIE_RICH : ACH_IOS_MR_RITCHIE_RICH);
                    CCString *msgString = CCString::createWithFormat("");
                    Utility::unlockAchievemnt(idString, msgString);
                    addFinalAchievementLayer(38);
                }
            }
        }
        
        Utility::setTotalDistance(distance);
        Utility::setTotalScore(score);
        Utility::setTotalWallSmashed(wallSmashed);
        Utility::setTotalTightSqueezes(squeezes);
        
        int totalCoins = Utility::getTotalCoins() + coinScore;
        Utility::setTotalCoins(totalCoins);
        if (Utility::getTotalCoins() == 10000 && Utility::getAchievementStatus(11) == 1) {
            //achieve 11
            CCLOG("10 K");
            Utility::setAchievementStatus(11, 2);
            Utility::setAchievementStatus(14, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.10K");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_10K : ACH_IOS_10K);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(11);
        }
        
        //for stats in a score screen
        Utility::setLongestDistance(Utility::getTotalDistance());
        Utility::setMostWallSmashed(Utility::getTotalWallSmashed());
        Utility::setMostTightSqueezes(Utility::getTotalTightSqueezes());
        Utility::setLongestGame(minute, seconds);
        Utility::setTotalWallSmashedLifeTime(Utility::getTotalWallSmashed()+ Utility::getTotalWallSmashedLifeTime());
        Utility::setTotalTightSqueezesLifeTime(squeezes+Utility::getTotalTightSqueezesLifeTime());
//        Utility::updateScores(score, "Upkesh");
        
//        character->characterUserData->readyForDeletion = true;
//        character->characterVirtualUserData->readyForDeletion = true;
        unloadCharacter();
        continueLayer = ContinueLayer::create(this);
        continueLayer->runTimer();
        hudLayer->addChild(continueLayer);
        isStartAllBg = false;

    }   else {
        CCDirector::sharedDirector()->replaceScene(GameScene::create(kSceneTypeHelp));
    }
  
}

void GameLayer::addStarsParticle() {
    starsParticle = new CCParticleSystemQuad;
    starsParticle->initWithFile("newStarsParticle.plist");
    starsParticle->setTotalParticles(10);
//    starsParticle = CCParticleSystemQuad::create("newStarsParticle.plist");
        starsParticle->setPosition(ccp(character->characterUserData->sprite->getPositionX() * 0.1, character->characterUserData->sprite->getPositionY()));
    addChild(starsParticle, 1);
}

void GameLayer::playGrassAnimation(UserData *caveUserData) {
//    if (grassParticle == NULL) {
//        grassParticle = new CCParticleSystemQuad;
//        grassParticle->initWithFile("grassParticle.plist");
    
        CCParticleSystemQuad *grassParticle = CCParticleSystemQuad::create("grassParticle.plist");
        grassParticle->setTotalParticles(10);
        grassParticle->setPosition(ccp(character->characterUserData->sprite->getPositionX(), character->characterUserData->sprite->getPositionY()));
        addChild(grassParticle, 1);
        caveUserData->setCollision(true);
//    }
    runAction(CCSequence::createWithTwoActions(CCDelayTime::create(1), CCCallFuncND::create(this, callfuncND_selector(GameLayer::resetUpperCaveCollision), caveUserData)));
}

void GameLayer::resetUpperCaveCollision(CCObject *sender, void *data) {
    isUpperGrassCollided = false;
}

void GameLayer::addUpperRandomParrallaxObjectsWithGrass() {
    RandomParallaxBg *randomObj = NULL;
    CCObject *obj = NULL;
    int i = 0;
    CCARRAY_FOREACH(upperBodyArrayWithGrass, obj) {
        
        randomObj = (RandomParallaxBg*) obj;
        if(randomObj->isActive == false) {
            
            break;
        }
        i++;
    }
    if(!randomObj->isActive) {
        randomObj->isActive = true;
        randomObj->body->SetActive(true);

        float randomObjHeight = lastUpperRandomParallax->spriteUserData->sprite->getPositionY() - lastUpperRandomParallax->spriteUserData->sprite->getContentSize().height;
        topY = randomObjHeight;
        
        if (isLaneWide) {
            randomObj->spriteUserData->sprite->setPosition(ccp(lastUpperRandomParallax->spriteUserData->sprite->getPosition().x + lastUpperRandomParallax->spriteUserData->sprite->getContentSize().width , winSize.height * kCaveUpperLimit));
            lastUpperRandomParallax = randomObj;
        } else {
            randomObj->spriteUserData->sprite->setPosition(ccp(lastUpperRandomParallax->spriteUserData->sprite->getPosition().x + lastUpperRandomParallax->spriteUserData->sprite->getContentSize().width , lastUpperRandomParallax->spriteUserData->sprite->getPositionY() + resetHeightFactorForUpper));
            lastUpperRandomParallax = randomObj;
            float randomObjHeight = lastUpperRandomParallax->spriteUserData->sprite->getPositionY() - lastUpperRandomParallax->spriteUserData->sprite->getContentSize().height;
            if (isDecrementingUpper) {
                decrementFactorForUpper(isDecrementingUpper);
                if(randomObjHeight <= winSize.height*0.66) {
                    isDecrementingUpper = false;
                    if (!startLower) {
                        startLower = true;
                    }
                    
                }
            } else  {
                decrementFactorForUpper(isDecrementingUpper);
                if (lastUpperRandomParallax->spriteUserData->sprite->getPositionY() >= winSize.height*1.5) {
                    isDecrementingUpper = true;
                }
            }
        }
    }
}

void GameLayer::addUpperRandomParrallaxObjectsWithoutGrass() {
    RandomParallaxBg *randomObj = NULL;
    CCObject *obj = NULL;
    int i = 0;
    CCARRAY_FOREACH(upperBodyArrayWithoutGrass, obj) {
        
        randomObj = (RandomParallaxBg*) obj;
        if(randomObj->isActive == false) {
            
            break;
        }
        i++;
    }
    if(!randomObj->isActive) {
        randomObj->isActive = true;
        randomObj->body->SetActive(true);

        float randomObjHeight = lastUpperRandomParallax->spriteUserData->sprite->getPositionY() - lastUpperRandomParallax->spriteUserData->sprite->getContentSize().height;
        topY = randomObjHeight;

        if (isLaneWide) {
            randomObj->spriteUserData->sprite->setPosition(ccp(lastUpperRandomParallax->spriteUserData->sprite->getPosition().x + lastUpperRandomParallax->spriteUserData->sprite->getContentSize().width , winSize.height * kCaveUpperLimit));
            lastUpperRandomParallax = randomObj;
        } else {
            randomObj->spriteUserData->sprite->setPosition(ccp(lastUpperRandomParallax->spriteUserData->sprite->getPosition().x + lastUpperRandomParallax->spriteUserData->sprite->getContentSize().width , lastUpperRandomParallax->spriteUserData->sprite->getPositionY() + resetHeightFactorForUpper));
            
            lastUpperRandomParallax = randomObj;
            
            float randomObjHeight = lastUpperRandomParallax->spriteUserData->sprite->getPositionY() - lastUpperRandomParallax->spriteUserData->sprite->getContentSize().height;
            if (isDecrementingUpper) {
                decrementFactorForUpper(isDecrementingUpper);
                if(randomObjHeight <= winSize.height*0.66) {
                    isDecrementingUpper = false;
                    if (!startLower) {
                        startLower = true;
                    }
                }
            } else  {
                decrementFactorForUpper(isDecrementingUpper);
                if (lastUpperRandomParallax->spriteUserData->sprite->getPositionY() >= winSize.height*1.5) {
                    isDecrementingUpper = true;
                }
            }
        }
    }
}




void GameLayer::addLowerRandomParrallaxObjectsWithGrass() {
    RandomParallaxBg *randomObj = NULL;
    CCObject *obj;
    int i = 0;
    CCARRAY_FOREACH(lowerBodyArrayWithGrass, obj) {
        randomObj = (RandomParallaxBg*) obj;
        if(randomObj->isActive == false) {
            
            break;
        }
        i++;
    }
    if (!randomObj->isActive) {
        randomObj->isActive = true;
        randomObj->body->SetActive(true);
        
        float randomObjHeight = lastLowerRandomParallax->spriteUserData->sprite->getPositionY() + lastLowerRandomParallax->spriteUserData->sprite->getContentSize().height;
        bottomY = randomObjHeight;
        
        if (isLaneWide) {
            randomObj->spriteUserData->sprite->setPosition(ccp(lastLowerRandomParallax->spriteUserData->sprite->getPosition().x + lastLowerRandomParallax->spriteUserData->sprite->getContentSize().width , winSize.height * kCaveLowerLimit ));
            lastLowerRandomParallax = randomObj;
        } else {
            
            randomObj->spriteUserData->sprite->setPosition(ccp(lastLowerRandomParallax->spriteUserData->sprite->getPosition().x + lastLowerRandomParallax->spriteUserData->sprite->getContentSize().width , lastLowerRandomParallax->spriteUserData->sprite->getPositionY() + resetHeightFactorForLower ));
            lastLowerRandomParallax = randomObj;
            float randomObjHeight = lastLowerRandomParallax->spriteUserData->sprite->getPositionY() + lastLowerRandomParallax->spriteUserData->sprite->getContentSize().height;
            if (startLower) {
                if (!isDecrementingLower) {
                    decrementFactorForLower(isDecrementingLower);
                    if(randomObjHeight >= winSize.height*0.3) {
                        isDecrementingLower = true;
                    }
                } else {
                    decrementFactorForLower(isDecrementingLower);
                    if (lastLowerRandomParallax->spriteUserData->sprite->getPositionY() <= -winSize.height*0.5) {
                        isDecrementingLower = false;
                    }
                }
            }
        }
    }
}


void GameLayer::addLowerRandomParrallaxObjectsWithoutGrass() {
    RandomParallaxBg *randomObj = NULL;
    CCObject *obj;
    int i = 0;
    CCARRAY_FOREACH(lowerBodyArrayWithoutGrass, obj) {
        randomObj = (RandomParallaxBg*) obj;
        if(randomObj->isActive == false) {
            
            break;
        }
        i++;
    }
    if (!randomObj->isActive) {
        randomObj->isActive = true;
        randomObj->body->SetActive(true);
        
        float randomObjHeight = lastLowerRandomParallax->spriteUserData->sprite->getPositionY() + lastLowerRandomParallax->spriteUserData->sprite->getContentSize().height;
        bottomY = randomObjHeight;
        
        if (isLaneWide) {
            randomObj->spriteUserData->sprite->setPosition(ccp(lastLowerRandomParallax->spriteUserData->sprite->getPosition().x + lastLowerRandomParallax->spriteUserData->sprite->getContentSize().width , winSize.height * kCaveLowerLimit ));
            lastLowerRandomParallax = randomObj;
        } else {
            randomObj->spriteUserData->sprite->setPosition(ccp(lastLowerRandomParallax->spriteUserData->sprite->getPosition().x + lastLowerRandomParallax->spriteUserData->sprite->getContentSize().width , lastLowerRandomParallax->spriteUserData->sprite->getPositionY() + resetHeightFactorForLower));
            lastLowerRandomParallax = randomObj;
            
            float randomObjHeight = lastLowerRandomParallax->spriteUserData->sprite->getPositionY() + lastLowerRandomParallax->spriteUserData->sprite->getContentSize().height;
            if (startLower) {
                if (!isDecrementingLower) {
                    decrementFactorForLower(isDecrementingLower);
                    if(randomObjHeight >= winSize.height*0.3) {
                        isDecrementingLower = true;
                    }
                } else  {
                    decrementFactorForLower(isDecrementingLower);
                    if (lastLowerRandomParallax->spriteUserData->sprite->getPositionY() <= -winSize.height*0.5) {
                        isDecrementingLower = false;
                    }
                }
            }
        }
    }
}

void GameLayer::removeUpperWithoutGrassObject(RandomParallaxBg *randomParallax) {
//    removeChild(randomParallax->spriteUserData->sprite, true);
    randomParallax->spriteUserData->readyForDeletion = true;
    upperBodyArrayWithoutGrass->removeObject(randomParallax);
}

void GameLayer::removeUpperWithGrassObject(RandomParallaxBg *randomParallax) {
//    removeChild(randomParallax->spriteUserData->sprite, true);
    randomParallax->spriteUserData->readyForDeletion = true;
    upperBodyArrayWithGrass->removeObject(randomParallax);
}

void GameLayer::removeLowerWithoutGrassObject(RandomParallaxBg *randomParallax) {
//    removeChild(randomParallax->spriteUserData->sprite, true);
    randomParallax->spriteUserData->readyForDeletion = true;
    lowerBodyArrayWithoutGrass->removeObject(randomParallax);
}

void GameLayer::removeLowerWithGrassObject(RandomParallaxBg *randomParallax) {
//    removeChild(randomParallax->spriteUserData->sprite, true);
    randomParallax->spriteUserData->readyForDeletion = true;
    lowerBodyArrayWithGrass->removeObject(randomParallax);
}

void GameLayer::addUpperInitialObjects() {
    //adding with grass
    float prevX = 0;
    int count = kTotalCaves;
    for (int i = 0; i < count; i++) {
        if (i >= ((count/2)+1) ) {
            RandomParallaxBg *randomParallaxForWithoutGrass = new RandomParallaxBg;
            randomParallaxForWithoutGrass->createSprite(CCString::createWithFormat("withoutGrassUp_%d.png", i), this, ccp(winSize.width , winSize.height * kCaveUpperLimit), kCaveType_UpperWithoutGrass);
            upperBodyArrayWithoutGrass->addObject(randomParallaxForWithoutGrass);
            randomParallaxForWithoutGrass->isActive = true;
            CC_SAFE_RELEASE(randomParallaxForWithoutGrass);
            
        } else {
            RandomParallaxBg *randomParallax = new RandomParallaxBg;
            if (prevX == 0) {
                randomParallax->createSprite(CCString::createWithFormat("grassUp_%d.png", i), this, CCPoint(0 , winSize.height * kCaveUpperLimit ), kCaveType_UpperWithGrass);
                randomParallax->spriteUserData->sprite->setPosition(ccp(winSize.width , winSize.height * kCaveUpperLimit));
                prevX = randomParallax->spriteUserData->sprite->getContentSize().width;

            }else {
                randomParallax->createSprite(CCString::createWithFormat("grassUp_%d.png", i), this, ccp(prevX , winSize.height * kCaveUpperLimit), kCaveType_UpperWithGrass);
                randomParallax->spriteUserData->sprite->setPosition(ccp(prevX + winSize.width , winSize.height * kCaveUpperLimit));
                prevX += randomParallax->spriteUserData->sprite->getContentSize().width;
                if (i == count/2) {
                    lastUpperRandomParallax = randomParallax;
                }
            }
            randomParallax->isActive = true;
            upperBodyArrayWithGrass->addObject(randomParallax);
            isActiveArrayForUpper[i] = 1;
            CC_SAFE_RELEASE(randomParallax);
        }
    }
}

void GameLayer::addLowerInitialObjects() {
    float prevX = 0;
    for (int i = kTotalCaves; i >= 0; i--) {
        if (i >= ((kTotalCaves/2) + 1)) {
            RandomParallaxBg *randomParallaxForWithoutGrass = new RandomParallaxBg;
            randomParallaxForWithoutGrass->createSprite(CCString::createWithFormat("withoutGrassDown_%d.png", i), this, ccp(0 , winSize.height * kCaveLowerLimit), kCaveType_LowerWithoutGrass);
            lowerBodyArrayWithoutGrass->addObject(randomParallaxForWithoutGrass);
            randomParallaxForWithoutGrass->isActive = true;
            
        } else {
            RandomParallaxBg *randomParallax = new RandomParallaxBg;
            if (prevX == 0) {
                randomParallax->createSprite(CCString::createWithFormat("grassDown_%d.png", i), this, CCPoint(0 , winSize.height * kCaveLowerLimit ), kCaveType_LowerWithGrass);
                randomParallax->spriteUserData->sprite->setPosition(ccp(winSize.width , winSize.height * kCaveLowerLimit));
                prevX = randomParallax->spriteUserData->sprite->getContentSize().width;
            }else {
                randomParallax->createSprite(CCString::createWithFormat("grassDown_%d.png", i), this, ccp(prevX , winSize.height * kCaveLowerLimit), kCaveType_LowerWithGrass);
                randomParallax->spriteUserData->sprite->setPosition(ccp(prevX + winSize.width , winSize.height * kCaveLowerLimit ));
                prevX += randomParallax->spriteUserData->sprite->getContentSize().width;
                
                if (i == 0) {
                    lastLowerRandomParallax = randomParallax;
                }
            }
            randomParallax->isActive = true;
            lowerBodyArrayWithGrass->addObject(randomParallax);
        }
    }
}

//-(void)applyForce:(cpBody *)otherBody  delta:(ccTime)delta {
//	cpVect u12 = cpvnormalize(cpvsub(sprite.position, otherBody->p));
//
//	cpFloat absDist = cpvdist(sprite.position, otherBody->p);
//	cpFloat absDistSquare = pow(absDist, 2);
//	cpFloat multFactor = 1500 * 1500 / absDistSquare;
//	cpVect impulse = cpvmult(u12, multFactor * delta * 60);
//	cpBodyApplyImpulse(otherBody, impulse, cpvzero);
//}

//void GameLayer::applyForce(b2Body *coinBody, CCSprite *coinSprite) {
////    b2Vec2 u12 = operator - (character->charBody->GetPosition(), coinBody->GetPosition());
//    b2Vec2 u12 =  coinBody->GetPosition() - character->charBody->GetPosition();
//    float absDist = b2Distance(character->charBody->GetPosition(), coinBody->GetPosition());
//    float absDistSquare = pow(absDist, 2);
//    float multiFactor = 0.2 * 0.2/ absDistSquare;
////    coinBody->SetLinearVelocity(b2Vec2_zero);
//    b2Vec2 impulse = b2Vec2(u12.x * multiFactor, u12.y * multiFactor);
//    coinBody->ApplyLinearImpulse(impulse, coinBody->GetWorldCenter());
//}

void GameLayer::applyForce(b2Body *coinBody, CCSprite *coinSprite) {
    b2Vec2 newVect = character->body->GetPosition() - coinBody->GetPosition();
    newVect.Normalize();
//    coinBody->SetTransform(b2Vec2(coinBody->GetPosition().x - newVect.x/3, coinBody->GetPosition().y - newVect.y/3), 0);
//    coinSprite->setPosition(Utility::fromMeters(b2Vec2(coinBody->GetPosition().x - (newVect.x/2), coinBody->GetPosition().y - (newVect.y/2))));
//    coinBody->ApplyLinearImpulse(b2Vec2(newVect.x*10, newVect.y*10), character->charBody->GetPosition());
//    coinBody->SetLinearVelocity(b2Vec2(newVect.x*10, newVect.y*10));
    
//    / Get the angle
    float angle = atan2f(character->body->GetPosition().y*PTM_RATIO - coinSprite->getPositionY(), character->body->GetPosition().x*PTM_RATIO - coinSprite->getPositionX());
    //NSLog(@" distance:%0.2f,force:%0.2f", distance, force);
    // Apply an impulse to the body, using the angle
//    coinBody->ApplyLinearImpulse(newVect, character->charBody->GetPosition());
    coinBody->ApplyLinearImpulse(b2Vec2(cosf(angle) * 5, sinf(angle) * 5), character->body->GetPosition());
//    coinBody->SetLinearVelocity(b2Vec2(cosf(angle) * 300, sinf(angle) * 300));
}

void GameLayer:: setPhysics() {
    b2Vec2 gravity = b2Vec2(0.0f,0.0f);// Initializing World
    world = new b2World(gravity);
    
//    m_debugDraw = new GLESDebugDraw( PTM_RATIO );
//    world->SetDebugDraw(m_debugDraw);
    world->SetContinuousPhysics(true);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
//    m_debugDraw->SetFlags(flags);
    contactListener = new MyContactListener(this);
    world->SetContactListener(contactListener);
}

void GameLayer::addOneTimeBg() {
    randomParallaxForBg = new RandomParallaxBg;
    randomParallaxForBg->createOneTimeBg(this, CCString::create("game_bg_0.png"));
    this->addChild(randomParallaxForBg);
}

void GameLayer::moveParallaxObjects() {
    CCObject *obj;
/*    distance += getGameSpeed() * 0.25;
    //add an obstacles
    if (distance > targetDistanceToAddObstacle) {
        float val = Utility::isIPad() ? 0.08 : 0.1;
        targetDistanceToAddObstacle += winSize.width * val;
        addInitialObstacle();
        
        //add coins
        if (distance >targetDistanceToAddCoins && sceneType == kSceneTypeGameScene) {
            targetDistanceToAddCoins += winSize.width * 1;
            runAction(CCSequence::createWithTwoActions(CCDelayTime::create(0.1), CCCallFunc::create(this, callfunc_selector(GameLayer::addCoins))));
        }
        
//        if (distance >targetDistanceToAddPowerUps && sceneType == kSceneTypeGameScene) {
//            runAction(CCSequence::createWithTwoActions(CCDelayTime::create(0.1), CCCallFunc::create(this, callfunc_selector(GameLayer::addPowerUps))));
//            targetDistanceToAddPowerUps += winSize.width * 1.3;
//        }
    }
 */
    if (distance == 800 && Utility::getAchievementStatus(6) == 1) {
        //achieve 6
        CCLOG("Half mile");
            Utility::setAchievementStatus(6, 2);
            Utility::setAchievementStatus(9, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.halfmile");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_HALF_MILE : ACH_IOS_HALF_MILE);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(6);
    }
    
    if (distance == 300 && seconds <= 15 && Utility::getAchievementStatus(9) == 1) {
        //achieve 9
        CCLOG("Lightning");
        Utility::setAchievementStatus(9, 2);
        Utility::setAchievementStatus(12, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.lightning");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_LIGHTNING : ACH_IOS_LIGHTNING);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(9);
    }
    
    if (distance == 10000 && Utility::getAchievementStatus(24) == 1) {
        //achieve 24
        CCLOG("10 k meter");
        Utility::setAchievementStatus(24, 2);
        Utility::setAchievementStatus(27, 1);
        
//        CCString *idString = CCString::createWithFormat("com.flying.flea.10kmetertarget");
        CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_10K_METER_TARGET : ACH_IOS_10K_METER_TARGET);
        CCString *msgString = CCString::createWithFormat("");
        Utility::unlockAchievemnt(idString, msgString);
        addFinalAchievementLayer(24);
    }
    RandomParallaxBg *randomObj;
    CCARRAY_FOREACH(lowerBodyArrayWithGrass, obj) {
        randomObj = (RandomParallaxBg*) obj;
        if(randomObj->isActive == true) {
            float pos = randomObj->spriteUserData->sprite->getPositionX();
            pos +=  -getGameSpeed();
            if (isCaveWideRunning) {
//                randomObj->sprite->setPositionY(-winSize.height * kCavePowerVariable);
                if (randomObj->spriteUserData->sprite->numberOfRunningActions() == 0) {
                    randomObj->spriteUserData->sprite->runAction(CCMoveTo::create(2, ccp(randomObj->spriteUserData->sprite->getPositionX(), -winSize.height * kCavePowerVariable)));
                }
            }
            if (randomObj->isActive && pos + randomObj->spriteUserData->sprite->getContentSize().width/2 <  -winSize.width) {
                randomObj->isActive = false;
                randomObj->body->SetActive(false);
            } else if(randomObj->isActive) {
                randomObj->spriteUserData->sprite->setPositionX(pos);
                
                float randomObjHeight = randomObj->spriteUserData->sprite->getPositionY() + randomObj->spriteUserData->sprite->getContentSize().height;
                bottomY = randomObjHeight;
//                b2Vec2 vect = b2Vec2(Utility::toMeters(CCPoint(randomObj->spriteUserData->getSprite()->getPositionX(),randomObj->spriteUserData->getSprite()->getPositionY())));
//                randomObj->body->SetTransform(vect, CC_DEGREES_TO_RADIANS(-randomObj->spriteUserData->getSprite()->getRotation()));
            }
        }
    }
    
    CCARRAY_FOREACH(upperBodyArrayWithGrass, obj) {
        randomObj = (RandomParallaxBg*) obj;
        if(randomObj->isActive == true) {
            float pos = randomObj->spriteUserData->sprite->getPositionX();
            pos +=  -getGameSpeed();
            if (isCaveWideRunning) {
//                randomObj->sprite->setPositionY(winSize.height * kCavePowerVariable + winSize.height);
                if (randomObj->spriteUserData->sprite->numberOfRunningActions() == 0) {
                    randomObj->spriteUserData->sprite->runAction(CCMoveTo::create(2, ccp(randomObj->spriteUserData->sprite->getPositionX(), winSize.height * kCavePowerVariable + winSize.height)));
                }
            }
            if (randomObj->isActive && pos + randomObj->spriteUserData->sprite->getContentSize().width/2 <  -winSize.width) {
                randomObj->isActive =false;
                randomObj->body->SetActive(false);
            } else if (randomObj->isActive) {
                randomObj->spriteUserData->sprite->setPositionX(pos);
                float randomObjHeight = randomObj->spriteUserData->sprite->getPositionY() - randomObj->spriteUserData->sprite->getContentSize().height;
                topY = randomObjHeight;
//                b2Vec2 vect = b2Vec2(Utility::toMeters(CCPoint(randomObj->spriteUserData->getSprite()->getPositionX(),randomObj->spriteUserData->getSprite()->getPositionY())));
//                randomObj->body->SetTransform(vect, CC_DEGREES_TO_RADIANS(-randomObj->spriteUserData->getSprite()->getRotation()));
            }
        }
    }
    CCARRAY_FOREACH(lowerBodyArrayWithoutGrass, obj) {
        randomObj = (RandomParallaxBg*) obj;
        if(randomObj->isActive == true) {
            float pos = randomObj->spriteUserData->sprite->getPositionX();
            pos +=  -getGameSpeed();
            if (isCaveWideRunning) {
//                randomObj->sprite->setPositionY(-winSize.height * kCavePowerVariable);
                if (randomObj->spriteUserData->sprite->numberOfRunningActions() == 0) {
                    randomObj->spriteUserData->sprite->runAction(CCMoveTo::create(2, ccp(randomObj->spriteUserData->sprite->getPositionX(), -winSize.height * kCavePowerVariable)));
                }
            }
            if (randomObj->isActive && pos + randomObj->spriteUserData->sprite->getContentSize().width/2 <  -winSize.width) {
                randomObj->isActive = false;
                randomObj->body->SetActive(false);
            } else if (randomObj->isActive){
                randomObj->spriteUserData->sprite->setPositionX(pos);
                float randomObjHeight = randomObj->spriteUserData->sprite->getPositionY() + randomObj->spriteUserData->sprite->getContentSize().height;
                bottomY = randomObjHeight;
//                b2Vec2 vect = b2Vec2(Utility::toMeters(CCPoint(randomObj->spriteUserData->getSprite()->getPositionX(),randomObj->spriteUserData->getSprite()->getPositionY())));
//                randomObj->body->SetTransform(vect, CC_DEGREES_TO_RADIANS(-randomObj->spriteUserData->getSprite()->getRotation()));
            }
        }
    }
    
    CCARRAY_FOREACH(upperBodyArrayWithoutGrass, obj) {
        randomObj = (RandomParallaxBg*) obj;
        if(randomObj->isActive == true) {
            float pos = randomObj->spriteUserData->sprite->getPositionX();
            pos +=  -getGameSpeed();
            if (isCaveWideRunning) {
//                randomObj->sprite->setPositionY(winSize.height * kCavePowerVariable + winSize.height);
                if (randomObj->spriteUserData->sprite->numberOfRunningActions() == 0) {
                    randomObj->spriteUserData->sprite->runAction(CCMoveTo::create(2, ccp(randomObj->spriteUserData->sprite->getPositionX(), winSize.height * kCavePowerVariable + winSize.height)));
                }
            }
            if (randomObj->isActive && pos + randomObj->spriteUserData->sprite->getContentSize().width/2 <  -winSize.width) {
                randomObj->isActive = false;
                randomObj->body->SetActive(false);
            } else if (randomObj->isActive) {
                randomObj->spriteUserData->sprite->setPositionX(pos);
                float randomObjHeight = randomObj->spriteUserData->sprite->getPositionY() - randomObj->spriteUserData->sprite->getContentSize().height;
                topY = randomObjHeight;
//                b2Vec2 vect = b2Vec2(Utility::toMeters(CCPoint(randomObj->spriteUserData->getSprite()->getPositionX(),randomObj->spriteUserData->getSprite()->getPositionY())));
//                randomObj->body->SetTransform(vect, CC_DEGREES_TO_RADIANS(-randomObj->spriteUserData->getSprite()->getRotation()));
            }
        }
    }
}

void GameLayer::decrementFactorForUpper(bool value) {
    if (value) {
        if (resetHeightFactorForUpper > 0) {
            resetHeightFactorForUpper = 0;
        }
        resetHeightFactorForUpper -= winSize.height * 0.00625;
    } else {
        if (resetHeightFactorForUpper < 0) {
            resetHeightFactorForUpper = 0;
        }
        resetHeightFactorForUpper += winSize.height * 0.00625;
    }
}

void GameLayer::decrementFactorForLower(bool value) {
    if (value) {
        if (resetHeightFactorForLower > 0) {
            resetHeightFactorForLower = 0;
        }
        resetHeightFactorForLower -= 2;
    } else {
        if (resetHeightFactorForLower < 0) {
            resetHeightFactorForLower = 0;
        }
        resetHeightFactorForLower += 2;
    }
    
}

void GameLayer::moveObstacleObjects() {
    CCObject *obj;
    Obstacle *obstacleObj;
    CCARRAY_FOREACH(obstacleArray, obj) {
        obstacleObj = (Obstacle*) obj;
        if (obstacleObj->spriteUserData->sprite != NULL) {
//            float pos = obstacleObj->spriteUserData->sprite->getPositionX();
            
            if (character->characterUserData->sprite->getPositionY() > (obstacleObj->spriteUserData->sprite->getPositionY()) && obstacleObj->spriteUserData->sprite->getPositionX() < winSize.width * 0.25 && obstacleObj->spriteUserData->sprite->getPositionX() > winSize.width * 0.24 ) {
                obstacleTag = obstacleObj->spriteUserData->getTag();
            }
            
            if (character->characterUserData->sprite->getPositionY() < (obstacleObj->spriteUserData->sprite->getPositionY()) && obstacleObj->spriteUserData->sprite->getPositionX() < winSize.width * 0.25 && obstacleObj->spriteUserData->sprite->getPositionX() > winSize.width * 0.24 ) {
                if (obstacleObj->spriteUserData->getTag() == (obstacleTag+1) && Utility::getAchievementStatus(14) == 1) {
                    CCLOG("achieved over under");
                    //achieve 14
                    Utility::setAchievementStatus(14, 2);
                    Utility::setAchievementStatus(17, 1);
                    
                    //                CCString *idString = CCString::createWithFormat("com.flying.flea.overunder");
                    CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_OVER_UNDER : ACH_IOS_OVER_UNDER);
                    CCString *msgString = CCString::createWithFormat("");
                    Utility::unlockAchievemnt(idString, msgString);
                    addFinalAchievementLayer(14);
                    
                }
            }
//            pos +=  -getGameSpeed();
//            if (pos  <  -50 ){//&& obstacleArray->lastObject() == obstacleObj) {
//                obstacleObj->spriteUserData->readyForDeletion = true;
//            } else {
//                obstacleObj->spriteUserData->sprite->setPositionX(pos);
//                obstacleObj->spriteUserData->setPosition(obstacleObj->spriteUserData->sprite->getPosition());
//            }
        }
    }
}

void GameLayer::removeObstacle(Obstacle *obstacle) {
//    this->removeChild(obstacle->spriteUserData->sprite);
    obstacle->spriteUserData->readyForDeletion = true;
//    obstacleArray->removeObject(obstacle);
   CC_SAFE_RELEASE_NULL(obstacle);
}

void GameLayer::addInitialObstacle() {
 ObstaclePattern *obstaclePattern = new ObstaclePattern;
    if (sceneType == kSceneTypeHelp) {
        if (basicHelpTag == 3 && isObstacleAdding) {
                obstaclePattern->createWithObstacle(this, true);
        } else if (basicHelpTag == 4 && isObstacleAdding) {
                obstaclePattern->createWithObstacle(this, false);
        }
    } else {
            obstaclePattern->createWithObstacle(this, false);
    }
    CC_SAFE_RELEASE_NULL(obstaclePattern);

}

HUDLayer* GameLayer:: getHUDLayer() {
    return hudLayer;
}

void GameLayer:: setHUDLayer(HUDLayer* layer) {
    hudLayer = layer;
}

void GameLayer::draw() {
    CCLayer::draw();
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    //    glPushMatrix();
    //    kmGLScalef( CC_CONTENT_SCALE_FACTOR(), CC_CONTENT_SCALE_FACTOR(), 1.0f);
    //       world->DrawDebugData();
    //    kmGLPopMatrix();
    
//    world->DrawDebugData();// comment this line to hide bodies
    kmGLPopMatrix();
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    if (isTouched) {
        Utility::resumeSound(paddingSoundId);
        Utility::resumeSound(thrashingSoundId);
        isCharCollidedUpperCave = false;
        flyDirection = kFlyUp;
        character->addCharacterFlameAnimation();
        speedToChange = 0.001;
        jetPacks++;
        if (jetPacks == 2500 && Utility::getAchievementStatus(33) == 1) {
            //achieve 33
            CCLOG("tapmaster Jet 25");
            Utility::setAchievementStatus(33, 2);
            Utility::setAchievementStatus(36, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.tapmaster");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_MISSION_JET_25 : ACH_IOS_MISSION_JET_25);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
            addFinalAchievementLayer(33);
        }
        return true;
    }
    return false;
}

void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    flyDirection = kFlyDown;
    if (character != NULL) {
        character->removeCharacterFlameAnimation();
    }
    speedToChange = 0.001;
    isUpperGrassCollided = false;
    Utility::pauseSound(paddingSoundId);
    Utility::pauseSound(thrashingSoundId);
}


void GameLayer:: keyBackClicked() {
    NDKHelper::AddSelector("GameSceneSelectors", "resetListener", callfuncND_selector(GameLayer::resetListener), this);
    SendMessageWithParams(string("quitGame"), NULL);
}

void GameLayer::resetListener(CCNode *sender, void *data){
    CCDirector::sharedDirector()->end();
}

void GameLayer::playBackPackThrust() {
   thrashingSoundId = Utility::playSound(CCString::create(kSoundForBackPackThrust), 1);
}

void GameLayer::playBackPackPadding() {
   paddingSoundId = Utility::playSound(CCString::create(kSoundForBackPaddle), 1);
    if (isBackPackPadding) {
        runAction(CCSequence::createWithTwoActions(CCDelayTime::create(3), CCCallFunc::create(this, callfunc_selector(GameLayer::playBackPackPadding)) ));
    }
}

void GameLayer:: removeLayerObjects () {
    this->stopAllActions();

    if ((sceneType == kSceneTypeGameScene) &&coinsArray != NULL) {
        int coinsArrayCount = coinsArray->count();
        if (coinsArrayCount > 0) {
            for (int i = coinsArrayCount - 1; i >= 0; i--) {
                CCString *string = (CCString*) coinsArray->allKeys()->objectAtIndex(i);
                Coins *coin = (Coins*)coinsArray->objectForKey(string->getCString());
                if (coin != NULL) {
                    removeCoin(coin);
                }
            }
        }
        CC_SAFE_RELEASE_NULL(coinsArray);
    }
    
    if (obstacleArray != NULL) {
        int obstacleArrayCount = obstacleArray->count();
        if (obstacleArrayCount > 0) {
            for (int i = obstacleArrayCount - 1; i >= 0; i--) {
                Obstacle *obstacle = (Obstacle*) obstacleArray->objectAtIndex(i);
                if (obstacle != NULL) {
                    removeObstacle(obstacle);
                }
            }
        }
        CC_SAFE_RELEASE_NULL(obstacleArray);
    }
    
    if ((sceneType == kSceneTypeGameScene) && powerUpArray != NULL) {
        int powerUpsArrayCount = powerUpArray->count();
        if (powerUpsArrayCount > 0) {
            for (int i = powerUpsArrayCount - 1; i >= 0; i--) {
                PowerUps *powerUp = (PowerUps*)powerUpArray->objectAtIndex(i);
                if (powerUp != NULL) {
                    removePowerUp(powerUp);
                }
            }
        }
        CC_SAFE_RELEASE_NULL(powerUpArray);
    }   

    int lowerBodyArrayWithGrassCount = lowerBodyArrayWithGrass->count();
    if (lowerBodyArrayWithGrassCount > 0) {
        for (int i = lowerBodyArrayWithGrassCount - 1; i >= 0; i--) {
            RandomParallaxBg *randomParallax = (RandomParallaxBg*)lowerBodyArrayWithGrass->objectAtIndex(i);
            if (randomParallax != NULL) {
                removeLowerWithGrassObject(randomParallax);
            }
        }
    }
    CC_SAFE_RELEASE_NULL(lowerBodyArrayWithGrass);

    
    int lowerBodyArrayWithoutGrassCount = lowerBodyArrayWithoutGrass->count();
    if (lowerBodyArrayWithoutGrassCount > 0) {
        for (int i = lowerBodyArrayWithoutGrassCount - 1; i >= 0; i--) {
            RandomParallaxBg *randomParallax = (RandomParallaxBg*)lowerBodyArrayWithoutGrass->objectAtIndex(i);
            if (randomParallax != NULL) {
                removeLowerWithoutGrassObject(randomParallax);
            }
        }
    }
    CC_SAFE_RELEASE_NULL(lowerBodyArrayWithoutGrass);
    
    int upperBodyArrayWithGrassCount = upperBodyArrayWithGrass->count();
    if (upperBodyArrayWithGrassCount > 0) {
        for (int i = upperBodyArrayWithGrassCount - 1; i >= 0; i--) {
            RandomParallaxBg *randomParallax = (RandomParallaxBg*)upperBodyArrayWithGrass->objectAtIndex(i);
            if (randomParallax != NULL) {
                removeUpperWithGrassObject(randomParallax);
            }
        }
    }
    CC_SAFE_RELEASE_NULL(upperBodyArrayWithGrass);
    
    int upperBodyArrayWithoutGrassCount = upperBodyArrayWithoutGrass->count();
    if (upperBodyArrayWithoutGrassCount > 0) {
        for (int i = upperBodyArrayWithoutGrassCount - 1; i >= 0; i--) {
            RandomParallaxBg *randomParallax = (RandomParallaxBg*)upperBodyArrayWithoutGrass->objectAtIndex(i);
            if (randomParallax != NULL) {
                removeUpperWithoutGrassObject(randomParallax);
            }
        }
    }
    CC_SAFE_RELEASE_NULL(upperBodyArrayWithoutGrass);

    destroyAllBodies();
    this->removeAllChildrenWithCleanup(true);
    unscheduleAllSelectors();

}

void GameLayer::destroyAllBodies() {
    for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL){
            UserData *userData = (UserData *)b->GetUserData();
            this->removeChild(userData->sprite);
            CC_SAFE_RELEASE(userData->sprite);
            CC_SAFE_RELEASE_NULL(userData);
            world->DestroyBody(b);
        }
    }
}

void GameLayer:: onExit() {
    CCLog("onexit called");
    removeLayerObjects();
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
    CCLayer::onExit();
}
