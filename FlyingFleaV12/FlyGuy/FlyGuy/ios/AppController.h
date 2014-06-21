//
//  FlyGuyAppController.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 11/09/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

@class RootViewController;
#import "GameCenterManager.h"
#import "Chartboost.h"


@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate, GameCenterManagerDelegate,GKLeaderboardViewControllerDelegate,GKAchievementViewControllerDelegate,ChartboostDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    BOOL shouldDisplayCBAd;
    int chartBoostDelayTime;
    NSDate *gameStartTime;

}

@property (nonatomic, strong) UIWindow *window;
@property (nonatomic, strong) RootViewController *viewController;
@property (nonatomic,strong) GameCenterManager *gameCenterManager;
@property (nonatomic) BOOL shouldDisplayCBAd;
@property (nonatomic, strong) NSDate *gameStartTime;
@property (nonatomic) int chartBoostDelayTime;

@end

