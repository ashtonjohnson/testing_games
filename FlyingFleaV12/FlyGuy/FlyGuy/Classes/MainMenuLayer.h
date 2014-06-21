//
//  MainMenuLayer.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 22/10/13.
//
//

#ifndef __FlyGuy__MainMenuLayer__
#define __FlyGuy__MainMenuLayer__

#include <iostream>
#include "cocos2d.h"
#include "CMAnimation.h"


using namespace cocos2d;

class MainMenuLayer: public CCLayer {
public:
    virtual bool init();
    static MainMenuLayer* create();
    virtual void keyBackClicked();
    virtual void resetListener(CCNode *sender, void *data);
    CCLabelTTF *labelPressButton;
    void addMenuItems(const char *frameName, int tag);
    void menuCallBack(CCObject *menuItem);
    void charMenuCallBack(CCObject *charMenuItem);
    void addCharMenu(const char *frameName, int frameCount, const char *charName);
    void runCharAnimation(const char *frameName, int frameCount);
    void createLabel(const char *labelName, CCPoint position, CCSprite *objective);
    void createSprite(const char *spriteFrameName, CCPoint pos, CCSprite *objective);
    void createButton(const char *spriteName, int tag, CCPoint posititon, CCSprite *objective);
    void goToUpgradeScreenWithExtras(CCNode *sender, void *data);
    void runCharacterAction();
    
    void addCharacterFlameAnimation();
    void runFlameAnimations(const char *spriteName, const char *frameName, int frameCount, CCPoint position);
    
    int getNoOfCoins();
    void onEnter();
    void onExit();
    
    CCMenu *charMenu;
    CCSize winSize;
    int charTag;
    void playGame();
    CCArray *charMenuIemList;
    CCSprite *charSprite, *charSpriteSelected;
    
    int i;
    
    CMAnimation *charAnim;
    CCAnimate *animateAction;
    CCLabelBMFont *tapToChange;
    CCLabelBMFont *label;
    const char *charName;
    CCMenuItemSprite *charMenuItem , *menuItemSoundOn, *menuItemSoundOff;
    
    CCSprite *flame, *soundOn, *soundOff;
    CCParticleSystemQuad *starsParticle;
    void addStarsParticle();
    
    CCMenu *playMenu, *menuSoundOff;
    CCMenuItemSprite *menuItem;
    void resetActions();
    void runRotateAction();
    void resetRotateAction();
    void playGameWithChar();
    CCRepeatForever *charAction;
    void soundsButtonTapped(CCObject *sender);
    int charTagForOrder;
    void unlockAllChars();
    void replaceSceneAfterUnlock();
    
    bool isHelpTutorial;
    
    void removeCharacter();
    void stopAnimations();
    void startAnimations();
    void restartCharacterAnimations();
    
    CCRepeatForever *menuAction;
    float charX;
    float charY;
    
    void showMoreApps();
    void showLeaderboards();
    CCAnimate *charAnimate;
    CCAnimate *flameAnimate;
};

#endif /* defined(__FlyGuy__MainMenuLayer__) */
