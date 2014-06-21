//
//  PauseLayer.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 28/10/13.
//
//

#ifndef __FlyGuy__PauseLayer__
#define __FlyGuy__PauseLayer__

#include <iostream>
#include "cocos2d.h"

class GameLayer;

using namespace cocos2d;

class PauseLayer: public CCLayer {
public:
    virtual bool init(GameLayer *gameLayer);
    static PauseLayer* create(GameLayer *gameLayer);
    CCArray *charMenuIemList;
    CCSize winSize;
    GameLayer *gLayer;
    void addObjectiveLayer();
    void addStatsLayer();
    
    void addMenuItems(const char *frameName, int tag);
    void menuCallBack(CCObject *menuItem);
    void createButton(const char *spriteName, int tag, CCPoint posititon);
    void createLabelForStats(const char *labelText, const char *labelValue, CCPoint position, CCLayer *layer);
    
    void hideHUDButtons();
    void showHUDButtons();
    
    CCLayer *objectiveLayer;
    CCLayer *statsLayer;
    
    CCMenuItemLabel *thisGameItem;
    CCMenuItemLabel *recordsItem;
    
    void createSprite(const char *spriteFrameName, CCPoint pos, CCSprite *objective);
    void createLabel(const char *labelName, const char *labelNameValue, CCPoint position, CCSprite *objective);
    
    CCArray *arrayForActive;
    
    bool isCallFromRecords;
    
    CCSprite *soundOn, *soundOff;
    CCMenuItemSprite *menuItemSoundOn, *menuItemSoundOff;
    CCMenu *menuSoundOff;
    void  soundsButtonTapped(CCObject *sender) ;
};
#endif /* defined(__FlyGuy__PauseLayer__) */
