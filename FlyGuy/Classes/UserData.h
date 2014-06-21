
//#include "GameLayer.h"
#include "cocos2d.h"
#include "Box2D.h"

using namespace cocos2d;

class UserData:public CCSprite {
public:
    UserData();
    int userDataType;
    int virtualUserDataType;
    int tag;
    int parentTag;
    bool readyForDeletion;
    bool isForceApplied;
    CCSprite *sprite;
    void setSprite(CCSprite *pSprite);
    CCSprite *getSprite();
    
    int getUserDataType();
    void setUserDataType(int type);
    virtual int getTag();
    void setTag(int varTag);
    int getParentTag();
    void setParentTag(int varParentTag);
    void setReadyForDeletion(bool isReady);
    bool getReadyForDeletion();
    int getVirtualUserDataType();
    void setVirtualUserDataType(int type);
    
    void setCollision(bool pIsCollided);
    bool getCollision();
    
    CCSprite* initWithFileName(const char *pszFilename);
    void initWithFrameName(const char *pszSpriteFrameName);
    
    bool isCollided;
    bool isapplied;
};
