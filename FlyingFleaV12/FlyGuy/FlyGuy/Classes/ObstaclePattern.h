//
//  ObstaclePattern.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 17/10/13.
//
//

#ifndef __FlyGuy__ObstaclePattern__
#define __FlyGuy__ObstaclePattern__

#include <iostream>
#include "cocos2d.h"
#include "GameLayer.h"
#include "Utility.h"

using namespace cocos2d;

class ObstaclePattern: public CCObject {
public:
    void createWithObstacle(GameLayer *gLayer, bool isObstacleStrong);
    void addObstacle(GameLayer *gLayer, ObstacleType obstacleType, CCString *name, CCPoint pos, bool isMoving);
};
#endif /* defined(__FlyGuy__ObstaclePattern__) */
