//
//  CMAnimation.h
//  Sperm
//
//  Created by Ramesh on 29/06/13.
//
//

#ifndef __Sperm__CMAnimation__
#define __Sperm__CMAnimation__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class CMAnimation:public CCAnimation {
public:
    static CCAnimation* animateWithFile( const char *firstFrameName, int numberOfFrames,float delay, bool reverse);
    static CCAnimation* animationWithFrame(const char *frameName, int frameCount, float delay);
};

#endif /* defined(__NobWars__CMAnimation__) */
