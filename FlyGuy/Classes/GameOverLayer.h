//
//  GameOverLayer.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 28/10/13.
//
//

#ifndef __FlyGuy__GameOverLayer__
#define __FlyGuy__GameOverLayer__

#include <iostream>
#include "cocos2d.h"
#include "CCEditBox.h"
class GameLayer;

using namespace cocos2d::extension;
using namespace cocos2d;

class GameOverLayer: public CCLayer {
public:
    virtual bool init(GameLayer *gLayer);
    static GameOverLayer* create(GameLayer *gLayer);
    
    int timer;
    
    GameLayer *gameLayer;
    CCSize winSize;
    void createButton(const char *spriteName, int tag, CCPoint posititon);
    void postOnLeaderBoard(CCString *leaderBoardID,int leaderbrdScore);
    void menuCallBack(CCObject *menuItem);
    void updateTimer();
    CCLabelBMFont *gameOverLabel;
    CCLabelBMFont *label, *labelText;
    void createLabel(const char *labelName, const char *labelNameValue, CCPoint position);
    CCEditBox *m_pEditName;
    void addStarsEffect();
    void runStarsEffect();
    CCParticleSystemQuad *starsParticle;
    void checkForMinScore();
    void achievement23();
    void onEnter();
    void onExit();
    void disableAllButton();
    bool isExitCalled;
    bool isScoreUpdated;
};
#endif /* defined(__FlyGuy__GameOverLayer__) */
