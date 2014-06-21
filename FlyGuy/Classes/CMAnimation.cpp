//
//  CMAnimation.cpp
//  Sperim
//
//  Created by Ramesh on 29/06/13.
//
//

#include "CMAnimation.h"

CCAnimation* CMAnimation::animateWithFile( const char *firstFrameName, int numberOfFrames,float delay, bool reverse){
    CCArray* frames;
    if (reverse == true) {
        frames = CCArray::createWithCapacity(numberOfFrames * 2);
    }else{
        frames = CCArray::createWithCapacity(numberOfFrames);
    }

    static int i = 0;
	for (i = 0; i < numberOfFrames; i++)
	{
        char firstFrame[50];
        sprintf(firstFrame, "%s%d.png",firstFrameName,i);
		
		CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		CCSpriteFrame* frame = frameCache->spriteFrameByName(firstFrame);
        frames->addObject(frame);
	}
    if (reverse == true) {
        for (i = numberOfFrames - 1; i>=0; i--) {
            char firstFrame[50];
            sprintf(firstFrame, "%s%d.png",firstFrameName,i);
            CCLOG("%d",i);
            CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
            CCSpriteFrame* frame = frameCache->spriteFrameByName(firstFrame);
            frames->addObject(frame);
        }
    }
    
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, delay);
	// return an animation object from all the sprite animation frames
    return animation;
}

CCAnimation* CMAnimation::animationWithFrame(const char *frameName, int frameCount, float delay){
    CCArray * frames = CCArray::createWithCapacity(frameCount);
    for (int i = 0; i < frameCount; i++) {
        CCString *spriteName = CCString::createWithFormat("%s%d.png", frameName, i);
		CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		CCSpriteFrame* frame = frameCache->spriteFrameByName(spriteName->getCString());
        frames->addObject(frame);
    }
    return CCAnimation::createWithSpriteFrames(frames,delay);
}

