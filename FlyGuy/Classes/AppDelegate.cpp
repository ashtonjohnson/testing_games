//
//  Fly_GuyAppDelegate.cpp
//  Fly Guy
//
//  Created by Upkesh Thakur on 10/09/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "Utility.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "SoundConstant.h"
#include "NDKHelper.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    CCSize frameSize = pEGLView->getFrameSize();
    pDirector->setOpenGLView(pEGLView);

//    #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//        Utility::setResourcesiOS();
//    #elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//        Utility::setResourcesAndroid();
//    #endif
    
    vector<string> searchPaths;
    if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
        Utility::isAndroid = true;
    }
    if (frameSize.width >= 768){
        Utility::isPad = true;
//		searchPaths.push_back("iPad");
        searchPaths.push_back("Images/HD");
        searchPaths.push_back("Particles/HD");
        searchPaths.push_back("Physics/HD");
        searchPaths.push_back("Sheets/HD/Backgrounds");
        searchPaths.push_back("Sheets/HD/ButtonsAndIcons");
        searchPaths.push_back("Sheets/HD/Character");
        searchPaths.push_back("Sheets/HD/LowerCave(WithGrass)");
        searchPaths.push_back("Sheets/HD/LowerCave(WithoutGrass)");
        searchPaths.push_back("Sheets/HD/UpperCave(WithGrass)");
        searchPaths.push_back("Sheets/HD/UpperCave(WithoutGrass)");

        
        pEGLView->setDesignResolutionSize(1024, 768, kResolutionExactFit);
        pDirector->setContentScaleFactor(1);
        
	}else{        
        searchPaths.push_back("Images/Normal");
        
        searchPaths.push_back("Particles/Normal");
        
        searchPaths.push_back("Physics/Normal");
        
        searchPaths.push_back("Sheets/Normal/Backgrounds");
        searchPaths.push_back("Sheets/Normal/ButtonsAndIcons");
        searchPaths.push_back("Sheets/Normal/Character");
        searchPaths.push_back("Sheets/Normal/Caves");
//		searchPaths.push_back("iPhone");
     
        
        pEGLView->setDesignResolutionSize(480, 320, kResolutionExactFit);
        pDirector->setContentScaleFactor(1);
    }
    searchPaths.push_back("sounds");
//    searchPaths.push_back("Resources");
    searchPaths.push_back("CommonPlist");
    searchPaths.push_back("Fonts");
    
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(searchPaths);
    
    // turn on display FPS
//    pDirector->setDisplayStats(false);
    
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    if(!defaults->getBoolForKey(kFirstRunKey)){
        defaults->setBoolForKey(kFirstRunKey, true);
        defaults->setBoolForKey(kBackgroundMusicKey, true);
        defaults->setBoolForKey(kSoundsKey, true);
    }
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    // create a scene. it's an autorelease object
    CCScene *pScene = MainMenuScene::create();
    
    Utility::isAppStart = true;
    
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(kBackgroundMusicFile);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForBackPackThrust);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForBackPaddle);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForBubbleShieldCollided);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForCoinCollection);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForRockCollision);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForPowerUpLaunch);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForHitGrass);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForSpecialCollection);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForRegister);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForShrinkPower);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForDieCharacter);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForFireworks);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForPowerUp2);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForPowerUp1);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForOuch);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForButtonClick);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForContinue);
    SimpleAudioEngine::sharedEngine()->preloadEffect(kSoundForCounter);
    // run
    pDirector->runWithScene(pScene);
    
    CCDirector::sharedDirector()->setDepthTest(false);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    if(Utility::isGameScene) {
            Utility::isPauseScene = true;   
    }
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
        CCDirector::sharedDirector()->pause();
    }
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
        CCLOG("applicationWillEnterForeground");
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//    Utility::playOrPauseMusic(CCString::create(kBackgroundMusicFile));
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID){
        CCDirector::sharedDirector()->resume();
    }
}
