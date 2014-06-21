//
//  FGScrollView.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 30/10/13.
//
//

#ifndef __FlyGuy__FGScrollView__
#define __FlyGuy__FGScrollView__

#include <iostream>
#include "cocos2d.h"
#include "Constant.h"

typedef enum ObjectiveStatus {
    kObjectiveStatus_Active = 0,
    kObjectiveStatus_Completed,
    kObjectiveStatus_All,
    kObjectiveStatus_Powerups,
    kObjectiveStatus_Extras,
    kObjectiveStatus_CoinStars,
}ObjectiveStatus;

using namespace cocos2d;

#include "CCScrollView.h"

class FGScrollView : public CCLayer {
public:
    CCSize winSize;
    virtual bool init(ObjectiveStatus pObjectiveStatus);
    static FGScrollView* create(ObjectiveStatus pObjectiveStatus);
    cocos2d::extension::CCScrollView *scrollView;
    void createLabel(const char *labelName, const char *labelNameValue, CCPoint position, CCSprite *objective);
    void createSprite(const char *spriteFrameName, CCPoint pos, CCSprite *objective);
    void createButton(const char *spriteName, int tag, CCPoint posititon, CCSprite *objective);
    void menuCallBack(CCObject *menuItem);
    void updateCoinsCount(CCNode *sender, void *data);
    void updateStarsCount(CCNode *sender, void *data);
    void resetUpgradeLabel(int calculatedLevel, int upgradLevel);
    void resetUpgradeBars(CCSprite *objective, int calculatedLevel);
    
    CCLabelBMFont *label, *labelText;
    
    CCArray *labelPowerUpsArray;
    CCArray *objectivePowerUpArray;
    CCArray *labelExtrasArray;
    
    CCArray *arrayForActive;
    CCArray *arrayForCompleted;
    
    void addObjectives();
    int noOfLevels;
    void loadObjectivesForActive();
    void loadObjectivesForCompleted();
    void loadObjectivesForAll();
    void loadObjectivesForPowerups();
    void loadObjectivesForExtras();
    void loadObjectivesForCoinStars();
    void onEnter();
    void onExit();

    
    int arrForActive[3];
    int arrForCompleted[10];
    int totalActives;
    int totalCompleted;

//    int getNoOfScoresAsPerBar(int totalNoOfBars);
//    int getNoOfScoresAsPerExtras(int extrasLevel);
    float deltaScrollBarGap;
    ObjectiveStatus objStatus;
    
    CCSprite *extrasToggleOn, *extrasToggleOff;
    CCMenuItemSprite *menuItemExtrasToggleOn, *menuItemExtrasToggleOff;
    void extrasToggleButtonTapped(CCObject *sender);
    CCMenu *menuExtrasToggleOff;
    CCArray *allToggleButtons;
    bool isToggleOn;
    void setToggleVisible(int tag, bool visibility);
    void unlockAllChars(CCNode *sender, void *data);
};



#endif /* defined(__FlyGuy__FGScrollView__) */
