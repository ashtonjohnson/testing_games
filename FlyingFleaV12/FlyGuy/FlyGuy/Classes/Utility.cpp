//
//  Utility.cpp
//  NobWars
//
//  Created by Er.Umesh on 30/05/13.
//
//

#include "Utility.h"
#include "cocos2d.h"
#include "NDKHelper.h"
#include "SoundConstant.h"

bool Utility::isPad = false;
bool Utility::isAndroid = false;
bool Utility::isGameScene = false;
bool Utility::isPauseScene = false;
bool Utility::isAppStart = false;
int Utility::score = 0;
int Utility::distance = 0;
int Utility::wallSmashed = 0;
int Utility::squeezes = 0;
SceneType Utility::sceneType = kSceneTypeGameScene;
static CCDictionary* dictObjective;
static CCDictionary* dictPowerup;
static CCDictionary* dictExtras;
static CCDictionary* dictCoinsStars;
SimpleAudioEngine *Utility::soundEngine = NULL;

CharacterType selectedChar = kCharacterType_NormanBlue;

bool Utility:: isIPhone() {
    bool isIPhone = false;
    CCSize winSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    if (winSize.height == kHeightiPhone) {
        isIPhone = true;
    }
    return isIPhone;
}

bool Utility:: isIPadHD() {
    bool isIPadHD = false;
    CCSize winSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    if (winSize.height == kHeightiPadHD) {
        isIPadHD = true;
    }
    return isIPadHD;
}

bool Utility:: isIPad() {
    bool isIPad = false;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (winSize.height > kHeightiPhone) {
        isIPad = true;
    }
    return isIPad;
}

CCDictionary* Utility:: objectiveDict(){
    if (dictObjective == NULL) {
        std::string plistFile = CCFileUtils::sharedFileUtils()->fullPathForFilename("objectives.plist");
        dictObjective = CCDictionary::createWithContentsOfFileThreadSafe(plistFile.c_str());
        dictObjective->retain();
    }
    return dictObjective;
}

CCDictionary* Utility:: powerupDict() {
    if (dictPowerup == NULL) {
        std::string plistFile = CCFileUtils::sharedFileUtils()->fullPathForFilename("powerUps.plist");
        dictPowerup = CCDictionary::createWithContentsOfFileThreadSafe(plistFile.c_str());
        dictPowerup->retain();
    }
    return dictPowerup;
}

CCDictionary* Utility:: extrasDict() {
    if (dictExtras == NULL) {
        std::string plistFile = CCFileUtils::sharedFileUtils()->fullPathForFilename("extras.plist");
        dictExtras = CCDictionary::createWithContentsOfFileThreadSafe(plistFile.c_str());
        dictExtras->retain();
    }
    return dictExtras;
}

CCDictionary* Utility:: coinsStarsDict() {
    if (dictCoinsStars == NULL) {
        std::string plistFile = CCFileUtils::sharedFileUtils()->fullPathForFilename("coinsStars.plist");
        dictCoinsStars = CCDictionary::createWithContentsOfFileThreadSafe(plistFile.c_str());
        dictCoinsStars->retain();
    }
    return dictCoinsStars;
}


float Utility:: getInitGameSpeed() {
    float gameSpeed = (isPad)? kInitGameSpeediPad : kInitGameSpeediPhone;
    return gameSpeed;
}

void Utility:: setResourcesAndroid() {
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    CCSize frameSize = pEGLView->getFrameSize();
    
    vector<string> searchPath;
    if (frameSize.width > 1024) {
        searchPath.push_back("iPad");
        pEGLView->setDesignResolutionSize(1024, 768, kResolutionExactFit);
        CCDirector::sharedDirector()->setContentScaleFactor(1);
    }
	else {
		searchPath.push_back("iPhone");
        pEGLView->setDesignResolutionSize(480, 320, kResolutionExactFit);
        CCDirector::sharedDirector()->setContentScaleFactor(1);
    }
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
}

void Utility:: setResourcesiOS() {
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    // Set the design resolution
    
	CCSize frameSize = pEGLView->getFrameSize();
    
    std::vector<std::string> searchPath;
    
	if (frameSize.width == kWidthiPadHD) {
        searchPath.push_back("iPad-hd");
        searchPath.push_back("iPhoneHD");
        CCDirector::sharedDirector()->setContentScaleFactor(kWidthiPadHD/kWidthiPad);
        pEGLView->setDesignResolutionSize(kWidthiPad, kHeightiPad, kResolutionExactFit);
	} else if (frameSize.width == kWidthiPad) {
        searchPath.push_back("iPad");
        searchPath.push_back("iPhoneHD");
        CCDirector::sharedDirector()->setContentScaleFactor(kWidthiPad/kWidthiPad);
        pEGLView->setDesignResolutionSize(kWidthiPad, kHeightiPad, kResolutionExactFit);
    } else if (frameSize.width == kWidthiPhone5) {
        searchPath.push_back("iPhone5");
        searchPath.push_back("iPad");
        searchPath.push_back("iPhoneHD");
        CCDirector::sharedDirector()->setContentScaleFactor(kWidthiPhoneHD/kWidthiPhone);
        pEGLView->setDesignResolutionSize(kWidthiPhone5/2, kHeightiPhone, kResolutionExactFit);
    } else if (frameSize.width == kWidthiPhoneHD) {
        searchPath.push_back("iPhoneHD");
        searchPath.push_back("iPad");
        CCDirector::sharedDirector()->setContentScaleFactor(kWidthiPhoneHD/kWidthiPhone);
        pEGLView->setDesignResolutionSize(kWidthiPhone, kHeightiPhone, kResolutionExactFit);
    } else if (frameSize.width == kWidthiPhone) {
        searchPath.push_back("iPhone");
        CCDirector::sharedDirector()->setContentScaleFactor(kWidthiPhone/kWidthiPhone);
        pEGLView->setDesignResolutionSize(kWidthiPhone, kHeightiPhone, kResolutionExactFit);
    }
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
}


b2Vec2 Utility:: toMeters(cocos2d::CCPoint pointForConversion){
    return b2Vec2(pointForConversion.x / PTM_RATIO, pointForConversion.y / PTM_RATIO);
}

CCPoint Utility:: fromMeters(b2Vec2 pointForConversion){
    return CCPoint(pointForConversion.x * PTM_RATIO, pointForConversion.y *PTM_RATIO);
}

int Utility::randomIntBetween(int minValue, int maxValue){
    int range = maxValue - minValue;
    int actual = ( rand() % range ) + minValue;
    return actual;
}

float Utility::randomFloatBetween(float minValue, float maxValue){
    float range = maxValue - minValue;
	float thisNumber = minValue + CCRANDOM_0_1() * range;
	return thisNumber;
}

void Utility::addSpriteSheet(const char *spriteSheetName){
//    stringstream pngName;
//    pngName<<spriteSheetName<<".png";
    stringstream plistName;
    plistName<<spriteSheetName<<".plist";
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName.str().c_str(),pngName.str().c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistName.str().c_str());
}

void Utility::setCharactorType(CharacterType charType){
    selectedChar = charType;
}

CharacterType Utility::getCharactorType(){
    return selectedChar;
}

//int Utility::getObjectLockUnlockStatus(ObjectiveType objectiveType) {
//    int getObjectStatus = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("%s%d", kKeyForObjLockAndUnlock, objectiveType)->getCString());
//    return getObjectStatus;
//}
//
//void Utility::setObjectLockUnlockStatus(ObjectiveType objectiveType, int state) {
//    int keyForFirstObjective = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("%s%d", kKeyForObjLockAndUnlock, 1)->getCString());
//    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
//    if (keyForFirstObjective == 0) {
//        defaults->setIntegerForKey("keyForObjLockUnlock_0", 1);
//        for (int i = 1; i <= 4; i++) {
//            defaults->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForObjLockAndUnlock, i)->getCString(), 0);
//        }
//
//    }
//    defaults->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForObjLockAndUnlock, objectiveType)->getCString(), state);
//}
//
//
//int Utility::getObjectClearUnclearStatus(ObjectiveType objectiveType) {
//    int getObjectStatus = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("%s%d", kKeyForObjClearAndUnclear, objectiveType)->getCString());
//    return getObjectStatus;
//}
//
//void Utility::setObjectClearUnclearStatus(ObjectiveType objectiveType, int state) {
//    int keyForFirstObjective = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("%s%d", kKeyForObjClearAndUnclear, 1)->getCString());
//    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
//    if (keyForFirstObjective == 0) {
//        defaults->setIntegerForKey("keyForObjClearUnclear_0", 1);
//        for (int i = 1; i <= 4; i++) {
//            defaults->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForObjClearAndUnclear, i)->getCString(), 0);
//        }
//    }
//    defaults->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForObjClearAndUnclear, objectiveType)->getCString(), state);
//
//}

int Utility::getTotalCoins() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForTotalCoins);
}

void Utility::setTotalCoins(int coins) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForTotalCoins, coins);
}

// setter getter total score
int Utility::getTotalScore() {
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("currentScore");
//    return score;
}
void Utility::setTotalScore(int pScore) {
   // score = pScore;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("currentScore", pScore);
}

// setter getter total distance
int Utility::getTotalDistance() {
    return distance;
}
void Utility::setTotalDistance(int pDistance) {
    distance = pDistance;
}

// setter getter total tight squeezes
int Utility::getTotalTightSqueezes() {
    return squeezes;
}
void Utility::setTotalTightSqueezes(int pSqueezes) {
    squeezes = pSqueezes;
}

// setter getter total walll smashed
int Utility::getTotalWallSmashed() {
    return wallSmashed;
}
void Utility::setTotalWallSmashed(int pWallSmashed) {
    wallSmashed = pWallSmashed;
}

int Utility::getTotalStars() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    if (defaults->getIntegerForKey(kKeyForTotalStars) >= 0) {
        return defaults->getIntegerForKey(kKeyForTotalStars);
    }
    return 0;
}
void Utility::setTotalStars(int stars) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForTotalStars, stars);
}

// set power ups value
int Utility::getUpgradePowerups(PowerType powerType) {
    int getPowerupStatus = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("%s%d", kKeyForPowerType, powerType)->getCString());
    return getPowerupStatus;
}

void Utility::setUpgradePowerups(PowerType powerType, int value) {
    int keyForFirstPowerType = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("%s%d", kKeyForPowerType, 1)->getCString());
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    if (keyForFirstPowerType == 0) {
        defaults->setIntegerForKey("powerType_1", 1);
        for (int i = 1; i <= 5; i++) {
            defaults->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForPowerType, i)->getCString(), 2);
        }
    }
    defaults->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForPowerType, powerType)->getCString(), value);
}

// set total mystery box
int Utility::getTotalMysteryBox() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForTotalMysteryBox);
}
void Utility::setTotalMysteryBox(int totalMysteryBox) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForTotalMysteryBox, totalMysteryBox);
}

int Utility::getTotalRocketSpecial() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForTotalRocketSpecial);
}
void Utility::setTotalRocketSpecial(int totalRocketSpecial) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForTotalRocketSpecial, totalRocketSpecial);
}

int Utility::getTotalExtraLifeSpecial() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForTotalExtraLifeSpecial);
}
void Utility::setTotalExtraLifeSpecial(int totalExtraLifeSpecial) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForTotalExtraLifeSpecial, totalExtraLifeSpecial);
}

int Utility::getTotalBrokenWallSpecial() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForTotalBrokenWallSpecial);
}
void Utility::setTotalBrokenWallSpecial(int totalBrokenWallSpecial) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForTotalBrokenWallSpecial, totalBrokenWallSpecial);
}

int Utility::getTotalWideLaneSpecial() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForTotalWideLaneSpecial);
}
void Utility::setTotalWideLaneSpecial(int totalWideLaneSpecial) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForTotalWideLaneSpecial, totalWideLaneSpecial);
}

// locking unlocking of all characters
int Utility::getCharacterLockUnlockStatus(CharacterType characterType) {
    int getObjectStatus = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("%s%d", kKeyForCharacterLockUnlock, characterType)->getCString());
    return getObjectStatus;
}

void Utility::setCharacterLockUnlockStatus(CharacterType characterType, int state) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    int getCharStatus = defaults->getIntegerForKey("keyForCharacterLockUnlock_0");
    if (getCharStatus != 1) {
        defaults->setIntegerForKey("keyForCharacterLockUnlock_0", 1);
    }
    defaults->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForCharacterLockUnlock, characterType)->getCString(), state);
    
    int getcharStatus = 0;
    for (int i = 0; i < 4; i++) {
        getcharStatus = CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("%s%d", kKeyForCharacterLockUnlock, i)->getCString());
        getCharStatus++;
        if (getCharStatus == 4 && Utility::getAchievementStatus(30) == 1) {
            //ACHIEVE 30
            CCLOG("Get Em All");
            Utility::setAchievementStatus(30, 2);
            Utility::setAchievementStatus(33, 1);
            
//            CCString *idString = CCString::createWithFormat("com.flying.flea.getemall");
            CCString *idString = CCString::createWithFormat((Utility::isAndroid)? ACH_GET_EM_ALL : ACH_IOS_GET_EM_ALL);
            CCString *msgString = CCString::createWithFormat("");
            Utility::unlockAchievemnt(idString, msgString);
        }
        
    }
}

int Utility::getBarsInUpgrades(PowerType powerType) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    int getNoOfBars = defaults->getIntegerForKey(CCString::createWithFormat("%s%d", kKeyForBarsInUpgrades, powerType)->getCString());
    return getNoOfBars;
}

void Utility::setBarsInUpgrades(PowerType powerType, int noOfFilledBars) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
//    if (noOfFilledBars != 0) {
        defaults->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForBarsInUpgrades, powerType)->getCString(), noOfFilledBars);
//    }
}

int Utility::getLongestDistance() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForLongestDistance);
}

void Utility::setLongestDistance(int distance) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    if (distance == 0) {
        defaults->setIntegerForKey(kKeyForLongestDistance, distance);
    }
    if (distance >= defaults->getIntegerForKey(kKeyForLongestDistance)) {
        defaults->setIntegerForKey(kKeyForLongestDistance, distance);
    }
}

int Utility::getMostWallSmashed() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForMostWallSmashed);
}

void Utility::setMostWallSmashed(int totalWalls) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    if (totalWalls == 0) {
        defaults->setIntegerForKey(kKeyForMostWallSmashed, totalWalls);
    }
    if (totalWalls >= defaults->getIntegerForKey(kKeyForMostWallSmashed)) {
        defaults->setIntegerForKey(kKeyForMostWallSmashed, totalWalls);
    }
}

int Utility::getMostTightSqueezes() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForMostTightSqueezes);
}

void Utility::setMostTightSqueezes(int totalSqueezes) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    if (totalSqueezes == 0) {
        defaults->setIntegerForKey(kKeyForMostTightSqueezes, totalSqueezes);
    }
    if (totalSqueezes >= defaults->getIntegerForKey(kKeyForMostTightSqueezes)) {
        defaults->setIntegerForKey(kKeyForMostTightSqueezes, totalSqueezes);
    }
}

int Utility::getLongestGame() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForLongestGame);
}

void Utility::setLongestGame(int min, int sec) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    int totalSeconds = (min * 60) + sec;
    if (min == 0 && sec == 0) {
        defaults->setIntegerForKey(kKeyForLongestGame, totalSeconds);
    }
    
    if (totalSeconds >= defaults->getIntegerForKey(kKeyForLongestGame)) {
        defaults->setIntegerForKey(kKeyForLongestGame, totalSeconds);
    }
}

int Utility::getTotalGamesPlayed() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForTotalGamesPlayed);
}

void Utility::setTotalGamesPlayed(int totalGames) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForTotalGamesPlayed, totalGames);
}

int Utility::getTotalWallSmashedLifeTime() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForTotalWallSmashedLifetime);
}

void Utility::setTotalWallSmashedLifeTime(int totalWallSmashed) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    //    int previousTotalWallSmashed = defaults->getIntegerForKey(kKeyForTotalWallSmashedLifetime);
    //    previousTotalWallSmashed += totalWallSmashed;
    defaults->setIntegerForKey(kKeyForTotalWallSmashedLifetime, totalWallSmashed);
}

int Utility::getTotalTightSqueezesLifeTime() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForTotalTightSqueezesLifetime);
}

void Utility::setTotalTightSqueezesLifeTime(int totalTightSqueezes) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    //    int previousTotalTightSqueezes = defaults->getIntegerForKey(kKeyForTotalTightSqueezesLifetime);
    //    previousTotalTightSqueezes += totalTightSqueezes;
    defaults->setIntegerForKey(kKeyForTotalTightSqueezesLifetime, totalTightSqueezes);
}

// score implementation
void Utility::updateScores(int score, const char *playerName){
    for (int i = 0; i < 20; i++) {
        if(score >= getPlayerScore(i)){
            int nextScore = getPlayerScore(i);
            CCString *nextName = getPlayerName(i);
            for (int j = i; j < 20; j ++) {
                if(getPlayerScore(j) > 0){
                    CCString *nextScoreKey = CCString::createWithFormat("num_%d", j+1);
                    CCString *nextNameKey = CCString::createWithFormat("Name_num_%d", j+1);
                    int preNextScore = getPlayerScore(j+1);
                    CCString *preNextName = getPlayerName(j+1);
                    CCUserDefault::sharedUserDefault()->setIntegerForKey(nextScoreKey->getCString(), nextScore);
                    CCUserDefault::sharedUserDefault()->setStringForKey(nextNameKey->getCString(), nextName->getCString());
                    nextScore = preNextScore;
                    nextName = preNextName;
                }
            }
            CCString *scoreKey = CCString::createWithFormat("num_%d", i);
            CCString *nameKey = CCString::createWithFormat("Name_num_%d", i);
            CCUserDefault::sharedUserDefault()->setIntegerForKey(scoreKey->getCString(), score);
            CCUserDefault::sharedUserDefault()->setStringForKey(nameKey->getCString(), CCString::createWithFormat("%s", playerName)->getCString());
            break;
            
            
        }
    }
    
    CCUserDefault::sharedUserDefault()->flush();
}

int Utility::getPlayerScore(int num) {
    CCString *scoreKey = CCString::createWithFormat("num_%d", num);
    int playerScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(scoreKey->getCString(), 0);
    return playerScore;
}

CCString* Utility::getPlayerName(int num) {
    CCString *nameKey = CCString::createWithFormat("Name_num_%d", num);
    CCString *playerScore = CCString::createWithFormat("%s",CCUserDefault::sharedUserDefault()->getStringForKey(nameKey->getCString(), "").c_str());
    return playerScore;
}

void Utility::setAchieveGoldRush(const char *id) {
    
}

int Utility::getTotalJetPacks() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return     defaults->getIntegerForKey(kTotalJetPacks);
}

void Utility::setTotalJetPacks(int jetPacks) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kTotalJetPacks, jetPacks);
}


int Utility::getTotalWideLaneSeconds()  {
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(kTotalWideLaneSeconds);
}
void Utility::setTotalWideLaneSeconds(int seconds) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(kTotalWideLaneSeconds, seconds);
}

int Utility::getAchievementStatus(int achievement) {
    if (getSceneType() != kSceneTypeHelp) {
        return CCUserDefault::sharedUserDefault()->getIntegerForKey(CCString::createWithFormat("kAchievement_%d", achievement)->getCString());
    }
}

void Utility::setAchievementStatus(int achievement, int status) {
    if (getSceneType() != kSceneTypeHelp) {
        CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
        // 0 for locked
        // 1 for unlocked
        // 2 achieved
        if (defaults->getIntegerForKey("kAchievement_1") == 0) {
            for (int i = 1; i <= 41; i++) {
                // all are locked initially
                defaults->setIntegerForKey(CCString::createWithFormat("kAchievement_%d", i)->getCString(), 0);
            }
            defaults->setIntegerForKey("kAchievement_1", 1);
            defaults->setIntegerForKey("kAchievement_2", 1);
            defaults->setIntegerForKey("kAchievement_3", 1);
        }
        defaults->setIntegerForKey(CCString::createWithFormat("kAchievement_%d", achievement)->getCString(), status);
        defaults->flush();
    }
}

int Utility::getGamesForAchieve() {
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(kKeyForGameNo);
}

void Utility::setGamesForAchieve(int score) {//achieve 29
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForGameNo, (getGamesForAchieve() + 1) );
    setScoreForAchieve(score);
}

int Utility::getScoreForAchieve() {
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(kKeyForScoreNo);
}

void Utility::setScoreForAchieve(int score) {//achieve 29
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForScoreNo, (score + getScoreForAchieve()));
}

void Utility::unlockAchievemnt(CCString *achivementID, CCString *msgString){
    if (getSceneType() != kSceneTypeHelp) {
        if(!CCUserDefault::sharedUserDefault()->getBoolForKey(achivementID->getCString(), false)){
            CCUserDefault::sharedUserDefault()->setBoolForKey(achivementID->getCString(), true);
            if (Utility::isAndroid){
                CCDictionary* prms = CCDictionary::create();
                prms->setObject(achivementID, "unlockId");
                SendMessageWithParams(string("unlockAchievement"), prms);
            }else{
                CCDictionary* prms = CCDictionary::create();
                prms->setObject(achivementID, "unlockId");
                prms->setObject(msgString, "msgString");
                SendMessageWithParams(string("unlockAchievement"), prms);
            }
        }
    }
}

int Utility::storePushPopPowerUps() {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        int noOfFilledBars = Utility::getBarsInUpgrades((PowerType)(i));
        int coins = Utility::getNoOfScoresAsPerBar(noOfFilledBars);
        if (getTotalCoins() > coins) {
            count++;
        }
    }
    return  count;
}

int Utility::storePushPopExtras() {
    int count = 0;
    for (int i = 0; i < 9;  i++) {
        int coins = Utility::getNoOfScoresAsPerExtras(i);
        if (getTotalCoins() > coins && coins != 0) {
            count++;
        }
    }
    return count;
}



int Utility::getNoOfScoresAsPerExtras(int extrasLevel) {
    int score = 0;
    switch (extrasLevel) {
        case 0:
            score = 2500;
            break;
        case 1:
            score = 3500;
            break;
        case 2:
            score = 3000;
            break;
        case 3:
            score = 2000;
            break;
        case 4:
            score = 1000;
            break;
        case 5:
            score = 0;
            break;
        case 6:
            score = 10000;
            break;
        case 7:
            score = 15000;
            break;
        case 8:
            score = 20000;
            break;
            
        default:
            break;
    }
    return score;
}

int Utility::getNoOfScoresAsPerBar(int totalNoOfBars) {
    int score = 0;
    switch (totalNoOfBars) {
        case 0:
            score = 1000;
            break;
        case 1:
            score = 3000;
            break;
        case 2:
            score = 6000;
            break;
        case 3:
            score = 9000;
            break;
        case 4:
            score = 12000;
            break;
        case 5:
            score = 15000;
            break;
            
        default:
            break;
    }
    return score;
}

void Utility::resetAllUserDefault() {
    CCUserDefault *def = CCUserDefault::sharedUserDefault();
    def->setIntegerForKey(kKeyForObjLockAndUnlock, 0);
    def->setIntegerForKey(kKeyForObjClearAndUnclear, 0);
    def->setIntegerForKey(kKeyForTotalCoins, 0);
    def->setIntegerForKey(kKeyForTotalStars, 0);
    def->setIntegerForKey(kKeyForPowerType, 0);
    def->setIntegerForKey(kKeyForTotalStars, 0);
    def->setIntegerForKey(kKeyForTotalMysteryBox, 0);
    def->setIntegerForKey(kKeyForTotalRocketSpecial, 0);
    def->setIntegerForKey(kKeyForTotalBrokenWallSpecial, 0);
    def->setIntegerForKey(kKeyForTotalWideLaneSpecial, 0);
    def->setIntegerForKey(kKeyForCharacterLockUnlock, 0);
    def->setIntegerForKey(kKeyForBarsInUpgrades, 0);
    def->setIntegerForKey(kKeyForLongestDistance, 0);
    def->setIntegerForKey(kKeyForMostWallSmashed, 0);
    def->setIntegerForKey(kKeyForMostTightSqueezes, 0);
    def->setIntegerForKey(kKeyForLongestGame, 0);
    def->setIntegerForKey(kKeyForTotalGamesPlayed, 0);
    def->setIntegerForKey(kKeyForTotalWallSmashedLifetime, 0);
    def->setIntegerForKey(kKeyForTotalTightSqueezesLifetime, 0);
    def->setIntegerForKey(kTotalJetPacks, 0);
    def->setIntegerForKey(kTotalWideLaneSeconds, 0);
    
    for (int i = 1; i <= 41; i++) {
        def->setIntegerForKey(CCString::createWithFormat("kAchievement_%d", i)->getCString(), 0);
    }
    for (int j = 0; j < 20; j ++) {
        CCString *nextScoreKey = CCString::createWithFormat("num_%d", j);
        CCString *nextNameKey = CCString::createWithFormat("Name_num_%d", j);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(nextScoreKey->getCString(), 0);
        CCUserDefault::sharedUserDefault()->setStringForKey(nextNameKey->getCString(), "");
    }
    
    for (int i = 0; i < 5; i++) {
        def->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForBarsInUpgrades, i)->getCString(), 0);
    }
    
    for (int i = 0; i < 4; i++) {
        def->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForCharacterLockUnlock, i)->getCString(), 0);
    }
    
    for (int i = 1; i <= 4; i++) {
        def->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForObjLockAndUnlock, i)->getCString(), 0);
    }
    
    for (int i = 1; i <= 4; i++) {
        def->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForObjClearAndUnclear, i)->getCString(), 0);
    }
    
    for (int i = 1; i <= 5; i++) {
        def->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForPowerType, i)->getCString(), 2);
    }
    def->setIntegerForKey("powerType_1", 1);
    def->setIntegerForKey("keyForObjClearUnclear_0", 1);
    def->setIntegerForKey("keyForObjLockUnlock_0", 1);
    def->setIntegerForKey("keyForCharacterLockUnlock_0", 1);
    
    def->flush();
}

bool Utility::shouldPlayBackgroundMusic() {
	bool playBgMusic = CCUserDefault::sharedUserDefault()->getBoolForKey(kBackgroundMusicKey);
	return playBgMusic;
}

bool Utility::shouldPlaySounds(){
	bool playSounds = CCUserDefault::sharedUserDefault()->getBoolForKey(kSoundsKey);
	return playSounds;
}

void Utility::playOrPauseMusic(CCString *bgMusicFile) {
	if (soundEngine == NULL) {
		//Get the sound engine instance, if something went wrong this will be nil
		soundEngine = SimpleAudioEngine::sharedEngine();
	}
	if(shouldPlayBackgroundMusic()) {
		if(!soundEngine->isBackgroundMusicPlaying()) {
			soundEngine->playBackgroundMusic(bgMusicFile->getCString(), true);
		}
	}else if (soundEngine->isBackgroundMusicPlaying()) {
		soundEngine->stopBackgroundMusic();
	}
}

void Utility::changeVolume(float volume) {
    Utility::soundEngine->setBackgroundMusicVolume(volume);
}

void Utility::playMusic(CCString *bgMusicFile) {
    CCUserDefault::sharedUserDefault()->setBoolForKey(kBackgroundMusicKey, true);
	if(shouldPlayBackgroundMusic()) {
		if (soundEngine == NULL) {
			//Get the sound engine instance, if something went wrong this will be nil
			soundEngine = SimpleAudioEngine::sharedEngine();
		}
		if(!(soundEngine->isBackgroundMusicPlaying())) {
			float volume = CCUserDefault::sharedUserDefault()->getFloatForKey(bgMusicFile->getCString());
			soundEngine->setBackgroundMusicVolume(volume);
			soundEngine->playBackgroundMusic(bgMusicFile->getCString(), true);
		}
	}
}

int Utility::playSound(CCString *sound ,float volume ){
	int soundId = -1;
	if(shouldPlaySounds()){
		if (soundEngine == NULL) {
			//Get the sound engine instance, if something went wrong this will be nil
			soundEngine = SimpleAudioEngine::sharedEngine();
		}
		soundId = soundEngine->playEffect(sound->getCString());
	}
	return soundId;
}


void Utility::stopMusic() {
	if (soundEngine == NULL) {
		//Get the sound engine instance, if something went wrong this will be nil
		soundEngine = SimpleAudioEngine::sharedEngine();
	}
	soundEngine->stopBackgroundMusic();
}

void Utility::pauseSound(int soundId ){
    //	int soundId = -1;
	if(shouldPlaySounds()){
		if (soundEngine == NULL) {
			//Get the sound engine instance, if something went wrong this will be nil
			soundEngine = SimpleAudioEngine::sharedEngine();
		}
		soundEngine->pauseEffect(soundId);
	}
}

void Utility::resumeSound(int pSoundId  ){
	if(shouldPlaySounds()){
		if (soundEngine == NULL) {
			//Get the sound engine instance, if something went wrong this will be nil
			soundEngine = SimpleAudioEngine::sharedEngine();
		}
        soundEngine->resumeEffect(pSoundId);
	}
}

void Utility::setSceneType(SceneType pSceneType) {
    sceneType = pSceneType;
}

SceneType Utility::getSceneType() {
    return sceneType;
}


int Utility::getMysteryBoxCount() {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    return defaults->getIntegerForKey(kKeyForTotalMysteryBoxCount);
}

void Utility::setMysteryBoxCount(int count) {
    CCUserDefault *defaults = CCUserDefault::sharedUserDefault();
    defaults->setIntegerForKey(kKeyForTotalMysteryBoxCount, count);
}

ExtrasType Utility::getSelectedExtrasPower() {
    return (ExtrasType)CCUserDefault::sharedUserDefault()->getIntegerForKey(kKeyForSelectedExtras);
}

void Utility::setSelectedExtrasPower(ExtrasType pExtrasType) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey(kKeyForSelectedExtras, pExtrasType);
}

void Utility::setDefaultPlayerName(const char* playerName) {
    CCUserDefault::sharedUserDefault()->setStringForKey(kKeyForDefaultPlayerName, playerName);
}

void Utility::setAdFreeVersion(){
    CCString *key = CCString::createWithFormat("adfreeversion");
	CCUserDefault::sharedUserDefault()->setBoolForKey(key->getCString(), true);
}

bool Utility::isAdFreeVersion(){
    CCString *key = CCString::createWithFormat("adfreeversion");
	bool adFreeVersion = 	CCUserDefault::sharedUserDefault()->getBoolForKey(key->getCString(), false);
	return adFreeVersion;
}

void Utility::setUnlockAllCharacter(){
    CCString *key = CCString::createWithFormat("unlockCharacter");
	CCUserDefault::sharedUserDefault()->setBoolForKey(key->getCString(), true);
    
    for (int i = 0; i < 4; i++) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey(CCString::createWithFormat("%s%d", kKeyForCharacterLockUnlock, i)->getCString(), 1);
    }
}

bool Utility::isUnlockAllCharacter(){
    CCString *key = CCString::createWithFormat("unlockCharacter");
	bool unlockAllCharacter = 	CCUserDefault::sharedUserDefault()->getBoolForKey(key->getCString(), false);
	return unlockAllCharacter;
}

int Utility::getChartboostTime() {
    return CCUserDefault::sharedUserDefault()->getIntegerForKey("chartBoostTime");
}

void Utility::setChartboostTime(int value) {
    CCUserDefault::sharedUserDefault()->setIntegerForKey("chartBoostTime", value);
}

int Utility::getValueAsPerPurchase(int itemId) {
    CCDictionary *dict = (CCDictionary*)Utility::coinsStarsDict()->objectForKey(CCString::createWithFormat("coinsStars_%d",itemId)->getCString());
    CCString *element = (CCString*)dict->valueForKey(CCString::create("value")->getCString());
    int value = element->intValue();
    return value;
}
