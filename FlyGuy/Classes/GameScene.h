//
//  GameScene.h
//  Fly Guy
//
//  Created by Upkesh Thakur on 10/09/13.
//
//

#ifndef __Fly_Guy__GameScene__
#define __Fly_Guy__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "Constant.h"

using namespace cocos2d;

class GameScene:public CCScene {
public:
    virtual bool init(SceneType pSceneType);
    
    static GameScene* create(SceneType sceneType);
    virtual void onEnter();
    virtual void onExit();
    CCSize winSize;
    SceneType sceneType;
};

#endif /* defined(__Fly_Guy__GameScene__) */
