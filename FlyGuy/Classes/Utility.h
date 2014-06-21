//
//  UtilityFiles.h
//  NobWars
//
//  Created by Er.Umesh on 30/05/13.
//
//

#ifndef __NobWars__UtilityFiles__
#define __NobWars__UtilityFiles__

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"
#include "Constant.h"
#include "SimpleAudioEngine.h"
//#include "IOSPlistData.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


class Utility:public CCObject {
public:
    static void setResourcesiOS();
    static void setResourcesAndroid();
    static b2Vec2 toMeters(CCPoint pointForConversion);
    static CCPoint fromMeters(b2Vec2 pointForConversion);
    static int randomIntBetween(int minValue, int maxValue);
    static float randomFloatBetween(float minValue, float maxValue);
    static void addSpriteSheet(const char* spriteSheetName);
    
    static CCDictionary* objectiveDict();
    static CCDictionary* powerupDict();
    static CCDictionary* extrasDict();
    static CCDictionary* coinsStarsDict();
    
    static bool isPad;
    static bool isAndroid;
    static bool isAppStart;
    
    static bool isIPad();
    static bool isIPadHD();
    static bool isIPhone();
    
    static bool isGameScene;
    static bool isPauseScene;
    
    static void setCharactorType(CharacterType charType);
    static CharacterType getCharactorType();
    static float getInitGameSpeed();
    
//    static void setObjectLockUnlockStatus(ObjectiveType objectiveType, int state);
//    static int getObjectLockUnlockStatus(ObjectiveType objectiveType);
//    
//    static void setObjectClearUnclearStatus(ObjectiveType objectiveType, int state);
//    static int getObjectClearUnclearStatus(ObjectiveType objectiveType);
    
    static int getTotalCoins();
    static void setTotalCoins(int coins);
    
    static int score, distance, wallSmashed, squeezes;
    static void setTotalDistance(int pDistance);
    static int getTotalDistance();
    
    static void setTotalScore(int pScore);
    static int getTotalScore();
    
    static void setTotalWallSmashed(int pWallSmashed);
    static int getTotalWallSmashed();
    
    static void setTotalTightSqueezes(int pSqueezes);
    static int getTotalTightSqueezes();
    
    static int getTotalStars();
    static void setTotalStars(int stars);
    
    static int getUpgradePowerups(PowerType powerType);
    static void setUpgradePowerups(PowerType powerType, int value);
    
    static int getTotalMysteryBox();
    static void setTotalMysteryBox(int totalMysteryBox);
    
    static int getTotalRocketSpecial();
    static void setTotalRocketSpecial(int totalRocketSpecial);
    
    static int getTotalExtraLifeSpecial();
    static void setTotalExtraLifeSpecial(int totalExtraLifeSpecial);
    
    static int getTotalBrokenWallSpecial();
    static void setTotalBrokenWallSpecial(int totalBrokenWallSpecial);
    
    static int getTotalWideLaneSpecial();
    static void setTotalWideLaneSpecial(int totalWideLaneSpecial);
    
    static int getCharacterLockUnlockStatus(CharacterType characterType);
    static void setCharacterLockUnlockStatus(CharacterType characterType, int state);
    
    CCArray *scoreList;
    
    static int getBarsInUpgrades(PowerType powerType);
    static void setBarsInUpgrades(PowerType powerType, int noOfFilledBars);
    
    static int getLongestDistance();
    static void setLongestDistance(int distance);
    
    static int getMostWallSmashed();
    static void setMostWallSmashed(int totalWalls);
    
    static int getMostTightSqueezes();
    static void setMostTightSqueezes(int totalSqueezes);
    
    static int getTotalGamesPlayed();
    static void setTotalGamesPlayed(int totalGames);
    
    static int getTotalWallSmashedLifeTime();
    static void setTotalWallSmashedLifeTime(int totalWallSmashed);
    
    static int getTotalTightSqueezesLifeTime();
    static void setTotalTightSqueezesLifeTime(int totalTightSqueezes);
    
    static int getLongestGame();
    static void setLongestGame(int min, int sec);
    
    static void updateScores(int score, const char *playerName);
    static int getPlayerScore(int num);
    static CCString* getPlayerName(int num);
    
    //achievements
    static void setAchieveGoldRush(const char *id);
    
    static int getTotalJetPacks();
    static void setTotalJetPacks(int jetPacks);
    
    static int getTotalWideLaneSeconds();
    static void setTotalWideLaneSeconds(int seconds);
    
    static int getAchievementStatus(int achievement);
    static void setAchievementStatus(int achievement, int status);
    
    static int getGamesForAchieve();
    static void setGamesForAchieve(int score);
    
    static int getScoreForAchieve();
    static void setScoreForAchieve(int score);
    static void unlockAchievemnt(CCString *achivementID, CCString *msgString);
    
    static int getNoOfScoresAsPerExtras(int extrasLevel);
    static int getNoOfScoresAsPerBar(int totalNoOfBars);
    
    static int storePushPopPowerUps();
    static int storePushPopExtras();
    static void resetAllUserDefault();
    
    static bool shouldPlayBackgroundMusic();
    static bool shouldPlaySounds();
    static void playOrPauseMusic(CCString *bgMusicFile);
    static void changeVolume(float volume);
    static void playMusic(CCString *bgMusicFile);
    static void stopMusic();
    static SimpleAudioEngine *soundEngine;
    static int playSound(CCString *sound ,float volume );
    static void pauseSound(int soundId );
    static void resumeSound(int soundId  );
    
    static SceneType sceneType;
    static void setSceneType(SceneType pSceneType);
    static SceneType getSceneType();
    
    static void setMysteryBoxCount(int count);
    static int getMysteryBoxCount();
    
    static ExtrasType getSelectedExtrasPower();
    static void setSelectedExtrasPower(ExtrasType pExtrasType);
    
    static void setDefaultPlayerName(const char* playerName);
    
    static void setAdFreeVersion();
    static bool isAdFreeVersion();
    static void setUnlockAllCharacter();
    static bool isUnlockAllCharacter();
    static void setChartboostTime(int value);
    static int getChartboostTime();
    
    static int getValueAsPerPurchase(int itemId);
};


#endif /* defined(__NobWars__UtilityFiles__) */
