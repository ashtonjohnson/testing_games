//
//  FlyGuyAppController.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 11/09/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "InAppPurchaseLayer.h"
#include <MessageUI/MessageUI.h>
#import <GameKit/GameKit.h>
@class GADBannerView, GADRequest;

@interface RootViewController : UIViewController<InAppPurchaseDelegate, MFMailComposeViewControllerDelegate, GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate> {
	GADBannerView *bannerAdView;
    CGSize screenSize;
    InAppPurchaseLayer *inAppPurchase;
    CGPoint origin;
    bool isLargeAds;
    BOOL isAlertActive;
}

@property(nonatomic,retain) GADBannerView *bannerAdView;

- (void) showMoreApps:(NSObject *)prms;
- (void) shouldDisplayChartboostAd:(NSObject *)prms;
- (void) unlockAchievement:(NSObject *)prms;
- (void) achievementController:(NSObject *)prms;
- (void) leaderBoardController:(NSObject *)prms;
- (void) submitScore:(NSObject *)prms;
- (void) startPuchaseFlow:(NSObject *)prms;
- (void) restorePurchase:(NSObject *)prms;
- (void) postToAvalanche:(NSObject *)prms;
- (void) setDefaultPlayer:(NSObject *)prms;
- (void)productPurchased:(NSString *)productId;
-(void) sendFlurryReport:(NSObject *)prms;

@end

