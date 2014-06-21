

#include "UserData.h"

UserData:: UserData() {
    readyForDeletion = false;
}


CCSprite* UserData:: initWithFileName(const char *pszFilename) {
    return CCSprite::create(pszFilename);
}

void UserData::initWithFrameName(const char *pszSpriteFrameName) {
    isForceApplied = false;    
    sprite =  CCSprite::createWithSpriteFrameName(pszSpriteFrameName);
    sprite->retain();
//    return sprite;
}

int UserData::getUserDataType()  {
    return userDataType;
}

void UserData::setUserDataType(int type) {
    userDataType =  type;
}

int UserData::getVirtualUserDataType()  {
    return userDataType;
}

void UserData::setVirtualUserDataType(int type) {
    userDataType =  type;
}

int UserData::getTag(){
    return tag;
}

void UserData::setTag(int varTag){
    tag = varTag;
}

int UserData::getParentTag(){
    return parentTag;
}

void UserData::setParentTag(int varParentTag){
    parentTag = varParentTag;
}

void UserData::setReadyForDeletion(bool isReady){
    readyForDeletion = isReady;
}

bool UserData::getReadyForDeletion(){
    return readyForDeletion;
}

void UserData::setCollision(bool pIsCollided){
    isCollided = pIsCollided;
}

bool UserData::getCollision(){
    return isCollided;
}

void UserData::setSprite(CCSprite *pSprite) {
    sprite = pSprite;
}

CCSprite *UserData::getSprite() {
    return sprite;
}