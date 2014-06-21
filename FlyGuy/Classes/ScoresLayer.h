//
//  ScoresLayer.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 09/11/13.
//
//

#ifndef __FlyGuy__ScoresLayer__
#define __FlyGuy__ScoresLayer__

#include <iostream>
#include "cocos2d.h"


class GameLayer;

using namespace cocos2d;

class ScoresLayer: public CCLayer {
public:
    virtual bool init();
    static ScoresLayer* create();
    CCArray *charMenuIemList;
    CCSize winSize;
    CCLayerColor *colorLayerScore;
    CCLayerColor *colorLayerStats;
    CCLabelBMFont *labelIndex,*labelScore, *labelPlayerName;
    CCLabelBMFont *label1, *label2;
    CCMenuItemSprite *menuItemRefresh;
    
    void addMenuItems(const char *frameName, int tag);
    void menuCallBack(CCObject *menuItem);
    void createButton(const char *spriteName, int tag, CCPoint posititon, CCLayer *layer);
    void createLabelsForScores(const char *indexValue, const char *labelName, const char *labelNameValue, CCPoint position, CCLayerColor *layer);
    void createLabelForStats(const char *label, const char *labelText, CCPoint position, CCLayerColor *layer);
    void addScoreLayer();
    void addStatLayer();
    void resetAllStats() ;
    void replaceWithMainMenuScreen() ;
    void postOnLeaderBoard(CCString *leaderBoardID,int leaderbrdScore);
    void onEnter();
    void onExit();
};

#endif /* defined(__FlyGuy__ScoresLayer__) */
