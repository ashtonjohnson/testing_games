//
//  Constant.h
//  Fly Guy
//
//  Created by Upkesh Thakur on 10/09/13.
//
//

#ifndef Fly_Guy_Constant_h
#define Fly_Guy_Constant_h

#define kObjectiveType_

const float FIXED_TIMESTEP = 1.0f / 60.0f;
const float MINIMUM_TIMESTEP = 1.0f / 600.0f;
const int VELOCITY_ITERATIONS = 8;
const int POSITION_ITERATIONS = 8;
const int MAXIMUM_NUMBER_OF_STEPS = 25;

#define kTagPowerUp 1000
#define kTagObstacle 2000
#define kTagCoins   30000

#define kGamePhysicsPlist   "gamePhysics.plist"

typedef enum CharacterType {
    kCharacterType_NormanBlue = 0, // Lenny
    kCharacterType_JohnyOrange,     // Dez
    kCharacterType_BellaRed,        //Fauna Flea
    kCharacterType_VinnyGreen,      //Ella
}CharacterType;

typedef enum CaveType {
    kCaveType_UpperWithGrass = 100,
    kCaveType_UpperWithoutGrass,
    kCaveType_LowerWithGrass,
    kCaveType_LowerWithoutGrass,
    KCharactor,
    kCharacterVirtual,
}CaveType;

typedef enum ObstacleType {
    kObstacleType_Strong = 20,
    kObstacleType_Weak,
    kObstacleType_Common,
}ObstacleType;

typedef enum PatternType {
    kPatternType_1 = 300,
    kPatternType_2,
    kPatternType_3,
    kPatternType_4,
    kPatternType_5,
}PatternType;

typedef enum PowerUpType {
    kPowerType_SpeedBurst = 400,
    kPowerType_SuperRocket,
    kPowerType_BubbleShield,
    kPowerType_TinyMode,
    kPowerType_Star,
    kPowerType_Common,
}PowerUpType;

typedef enum CoinsType {
    kCoinsType_Normal = 200,
    kCoinsType_Yellow,
    kCoinsType_Green,
    kCoinsType_Red,
    kCoinsType_Blue,
}CoinsType;

typedef enum ExtrasType {
    kExtrasType_MysteryBox = 500,
    kExtrasType_RocketSpecial,
    kExtrasType_ExtraLifeSpecial,
    kExtrasType_BrokenWallSpecial,
    kExtrasType_WideLaneSpecial,
}ExtrasType;

typedef enum SceneType {
    kSceneTypeHelp = 0,
    kSceneTypeGameScene,
}SceneType;

//typedef enum ObjectiveType {
//    kObjectiveType_GoldMine = 0,
//    kObjectiveType_RookieFlyer,
//    kObjectiveType_EyeballsToTheWalls,
//    kObjectiveType_Pinballer,
//    kObjectiveType_StayOnCourse,
//}ObjectiveType;

typedef enum PowerType { // used in upgrade screen
    kPowerUpType_SpeedBurst = 0,
    kPowerUpType_SuperRocket,
    kPowerUpType_BubbleShield,
    kPowerUpType_TinyMode,
    kPowerUpType_Coins,
}PowerType;

#define kInitGameSpeediPhone                                                    4
#define kInitGameSpeediPad                                                      6

#define kWidthiPad                                                              1024
#define kWidthiPadHD                                                            2048
#define kWidthiPhone                                                            480
#define kWidthiPhoneHD                                                          960
#define kWidthiPhone5                                                           1136

#define kHeightiPad                                                             768
#define kHeightiPadHD                                                           1536
#define kHeightiPhone                                                           320
#define kHeightiPhoneHD                                                         640
#define kHeightiPhone5                                                          640

#define PTM_RATIO 32

#define kFlyUp                                                                  "flyUp"
#define kFlyDown                                                                "flyDown"
#define kFlyStop                                                                ""
#define kTotalObstacles                                                         2

#define kCaveUpperLimit                                                   1.59
#define kCaveLowerLimit                                                  -0.59
#define kCavePowerVariable                                                0.6

#define kTotalCaves                                                              15

#define kButtonPlay                                                             "btnPlay.png"
#define kFontChubby                                                             "fontChubby.fnt"
#define kFontMarkerFelt                                                         "fontMarkerFelt.fnt"

#define kKeyForCharacterLockUnlock                                              "keyForCharacterLockUnlock_"
#define kKeyForObjLockAndUnlock                                                 "keyForObjLockUnlock_"
#define kKeyForObjClearAndUnclear                                               "keyForObjClearUnclear_"
#define kKeyForBarsInUpgrades                                                   "keyForBarsInUpgrades_"
#define kKeyForTotalCoins                                                       "totalCoins"
#define kKeyForTotalStars                                                       "totalStars"
#define kKeyForPowerType                                                        "powerType_"
#define kKeyForTotalMysteryBox                                                  "totalMysteryBox"
#define kKeyForTotalRocketSpecial                                               "totalRocketSpecial"
#define kKeyForTotalExtraLifeSpecial                                            "totalExtraLifeSpecial"
#define kKeyForTotalBrokenWallSpecial                                           "totalBrokenWallSpecial"
#define kKeyForTotalWideLaneSpecial                                             "totalWideLaneSpecial"
#define kKeyForLongestDistance                                                  "longestDistance"
#define kKeyForMostWallSmashed                                                  "mostWallSmashed"
#define kKeyForMostTightSqueezes                                                "mostTightSqueezes"
#define kKeyForLongestGame                                                      "longestGame"
#define kKeyForTotalGamesPlayed                                                 "totalGamesPlayed"
#define kKeyForTotalWallSmashedLifetime                                         "totalWallSmashedLifeTime"
#define kKeyForTotalTightSqueezesLifetime                                       "totalTightSqueezesLifeTime"
#define kKeyForGameNo                                                           "gameNo"
#define kKeyForScoreNo                                                          "scoreNo"
#define kKeyForTotalMysteryBoxCount                                             "mysterBoxCount"
#define kKeyForSelectedExtras                                                   "selectedExtrasPower"
#define kKeyForDefaultPlayerName                                                "defaultPlayerName"

#define kTotalObjectives                                                        41

#define kTotalNoOfLevelInScrollBar                                              5
#define kScrollBar                                                              "scrollBar.png"
#define kShowBottomBannerAd "showbottom"
#define kShowTopBannerAd "showtop"
#define kShowChartboostAd "ChartboostAd"

#define kTotalJetPacks                                                          "totalJetPacks"
#define kTotalWideLaneSeconds                                                   "wideLaneSeconds"

//Common title/text for Reset (both iOS and Android)
#define kResetScoreTitle "Reset Flying Cells?"
#define kResetScoreText "Reset your scores and progress in Flying Cells? This cannot be undone."

//Common Email/Subject (both iOS and Android)
#define kEmailTo "support@crittermap.zendesk.com"
#define kEmailSubject "Flying Cells Feedback"

//Score posting on Facebook for iOS
#define kFbPostScoreText "I got a score of %d in Flying Cells."

//App Url for iOS
#define kAppUrl "http://bit.ly/1bMssrd"

//Local notification text for iOS
#define kLocalNotificationText @"Come back to Flying Cells!"
#define kLocalNotificationPlayButton @"PLAY"


//Chartboost App Id/App Signature
#define kChartboostAppId "52afc9c7f8975c259b871831"
#define kChartboostAppSignature "40dfbc3319434f93ec13169384286045c64d0af9"

//Flurry Id
#define kFlurryId "Q53N7R38M32JGBT4XFXJ"

//In-app purchases for iOS
#define kRemoveAds "com.flying.cells.removeads"
#define kUnlockAllCharacters "com.flying.cells.unlockallcharacters"
#define kBuy5000Coins "com.flying.cells.5000coins"
#define kBuy25000Coins "com.flying.cells.25000coins"
#define kBuy75000Coins "com.flying.cells.75000coins"
#define kBuy300000Coins "com.flying.cells.300000coins"

#define kBuy5Stars "com.flying.cells.5stars"
#define kBuy50Stars "com.flying.cells.50stars"
#define kBuy200Stars "com.flying.cells.200stars"
#define kBuy500Stars "com.flying.cells.500stars"

//Leaderboard Ids for Android
#define LEAD_HIGH_SCORE "CgkIuMrpiqkPEAIQAA"
#define LEAD_DISTANCE "CgkIuMrpiqkPEAIQAQ"

// Achievement Ids for Android
#define ACH_GOLD_RUSH "CgkIuMrpiqkPEAIQAg"
#define ACH_SPREAD_YOUR_WINGS "CgkIuMrpiqkPEAIQAw"
#define ACH_STAY_FOCUSED "CgkIuMrpiqkPEAIQBA"
#define ACH_CRUSH_EM "CgkIuMrpiqkPEAIQBQ"
#define ACH_HIT_IT "CgkIuMrpiqkPEAIQBg"
#define ACH_HALF_MILE "CgkIuMrpiqkPEAIQBw"
#define ACH_SPEED_BUMP "CgkIuMrpiqkPEAIQCA"
#define ACH_NOTHING_TO_SEE_HERE "CgkIuMrpiqkPEAIQCQ"
#define ACH_LIGHTNING "CgkIuMrpiqkPEAIQCg"
#define ACH_4_SCORE "CgkIuMrpiqkPEAIQCw"
#define ACH_10K "CgkIuMrpiqkPEAIQDA"
#define ACH_MR_BUBBLES "CgkIuMrpiqkPEAIQDQ"
#define ACH_NOTHING_LEFT_BEHIND "CgkIuMrpiqkPEAIQDg"
#define ACH_OVER_UNDER "CgkIuMrpiqkPEAIQDw"
#define ACH_DOUBLE_UP "CgkIuMrpiqkPEAIQEA"
#define ACH_MOVING_TARGET "CgkIuMrpiqkPEAIQEg"
#define ACH_5_BUCKS "CgkIuMrpiqkPEAIQEw"
#define ACH_60_MINUTES_REALLY_SECONDS "CgkIuMrpiqkPEAIQFA"
#define ACH_THE_BIG_BREAK "CgkIuMrpiqkPEAIQFQ"
#define ACH_BIG_DROPS "CgkIuMrpiqkPEAIQFg"
#define ACH_THE_BIG_SQUEEZE "CgkIuMrpiqkPEAIQFw"
#define ACH_MINI_ME "CgkIuMrpiqkPEAIQGA"
#define ACH_FILL_THEM_UP "CgkIuMrpiqkPEAIQGQ"
#define ACH_10K_METER_TARGET "CgkIuMrpiqkPEAIQGg"
#define ACH_THE_TINY_SQUEEZE "CgkIuMrpiqkPEAIQGw"
#define ACH_DOUBLE_CRUSH "CgkIuMrpiqkPEAIQHA"
#define ACH_SILK_FLOW "CgkIuMrpiqkPEAIQHQ"
#define ACH_QUAD_MOVING_TARGET "CgkIuMrpiqkPEAIQHg"
#define ACH_CONSISTENT_PERFORMER "CgkIuMrpiqkPEAIQHw"
#define ACH_GET_EM_ALL "CgkIuMrpiqkPEAIQIA"
#define ACH_MR_CURIOUS "CgkIuMrpiqkPEAIQIQ"
#define ACH_THE_ASTRONAUT "CgkIuMrpiqkPEAIQIg"
#define ACH_MISSION_JET_25 "CgkIuMrpiqkPEAIQIw"
#define ACH_JETPACK_ON_FIRE "CgkIuMrpiqkPEAIQJA"
#define ACH_MR_CONQUERER "CgkIuMrpiqkPEAIQJQ"
#define ACH_ROCK_N_ROLL "CgkIuMrpiqkPEAIQJg"
#define ACH_CALL_YOUR_BUDDIES "CgkIuMrpiqkPEAIQJw"
#define ACH_MR_RITCHIE_RICH "CgkIuMrpiqkPEAIQKA"
#define ACH_NEVER_SAY_DIE "CgkIuMrpiqkPEAIQKQ"
#define ACH_MR_STRIKER "CgkIuMrpiqkPEAIQKg"
#define ACH_HIGHWAY_RUNNER "CgkIuMrpiqkPEAIQKw"

//Leaderboard Ids for Android
#define LEAD_IOS_HIGH_SCORE "com.flying.cells.highscore"
#define LEAD_IOS_DISTANCE "com.flying.cells.distance"

// Achievement Ids for iOS
#define ACH_IOS_GOLD_RUSH "com.flying.cells.goldrush"
#define ACH_IOS_SPREAD_YOUR_WINGS "com.flying.cells.spreadyourwings"
#define ACH_IOS_STAY_FOCUSED "com.flying.cells.stayfocused"
#define ACH_IOS_CRUSH_EM "com.flying.cells.crushem"
#define ACH_IOS_HIT_IT "com.flying.cells.hitit"
#define ACH_IOS_HALF_MILE "com.flying.cells.halfmile"
#define ACH_IOS_SPEED_BUMP "com.flying.cells.speedbump"
#define ACH_IOS_NOTHING_TO_SEE_HERE "com.flying.cells.nothingtoseehere"
#define ACH_IOS_LIGHTNING "com.flying.cells.lightning"
#define ACH_IOS_4_SCORE "com.flying.cells.4score"
#define ACH_IOS_10K "com.flying.cells.10K"
#define ACH_IOS_MR_BUBBLES "com.flying.cells.MrBubbles"
#define ACH_IOS_NOTHING_LEFT_BEHIND "com.flying.cells.nothingleftbehind"
#define ACH_IOS_OVER_UNDER "com.flying.cells.overunder"
#define ACH_IOS_DOUBLE_UP "com.flying.cells.doubleup"
#define ACH_IOS_MOVING_TARGET "com.flying.cells.quadmovingtarget"
#define ACH_IOS_5_BUCKS "com.flying.cells.5bucks"
#define ACH_IOS_60_MINUTES_REALLY_SECONDS "com.flying.cells.60minutes"
#define ACH_IOS_THE_BIG_BREAK "com.flying.cells.bigbreak"
#define ACH_IOS_BIG_DROPS "com.flying.cells.bigdrops"
#define ACH_IOS_THE_BIG_SQUEEZE "com.flying.cells.bigsqueeze"
#define ACH_IOS_MINI_ME "com.flying.cells.minime"
#define ACH_IOS_FILL_THEM_UP "com.flying.cells.fillthemup"
#define ACH_IOS_10K_METER_TARGET "com.flying.cells.10kmetertarget"
#define ACH_IOS_THE_TINY_SQUEEZE "com.flying.cells.thetinysqueeze"
#define ACH_IOS_DOUBLE_CRUSH "com.flying.cells.doublecrush"
#define ACH_IOS_SILK_FLOW "com.flying.cells.silkflow"
#define ACH_IOS_QUAD_MOVING_TARGET "com.flying.cells.quadmovingtarget"
#define ACH_IOS_CONSISTENT_PERFORMER "com.flying.cells.consistentperformer"
#define ACH_IOS_GET_EM_ALL "com.flying.cells.getemall"
#define ACH_IOS_MR_CURIOUS "com.flying.cells.Mrcurious"
#define ACH_IOS_THE_ASTRONAUT "com.flying.cells.theastronaut"
#define ACH_IOS_MISSION_JET_25 "com.flying.cells.tapmaster"
#define ACH_IOS_JETPACK_ON_FIRE "com.flying.cells.jetpackonfire"
#define ACH_IOS_MR_CONQUERER "com.flying.cells.Mrconquerer"
#define ACH_IOS_ROCK_N_ROLL "com.flying.cells.rockandroll"
#define ACH_IOS_CALL_YOUR_BUDDIES "com.flying.cells.callyourbuddies"
#define ACH_IOS_MR_RITCHIE_RICH "com.flying.cells.ritchierich"
#define ACH_IOS_NEVER_SAY_DIE "com.flying.cells.neversaydie"
#define ACH_IOS_MR_STRIKER "com.flying.cells.striker"
#define ACH_IOS_HIGHWAY_RUNNER "com.flying.cells.highwayrunner"

#endif

#define kCategoryBitsCharVirtual    0x2000
#define kCategoryBitsWalls          0x0040
