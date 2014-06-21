//
//  FlyGuyAppController.h
//  FlyGuy
//
//  Created by Upkesh Thakur on 11/09/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#import "RootViewController.h"
#import "Utility.h"
#include "IOSNDKHelper.h"
#include "NDKHelper.h"
#import "AppController.h"
#import "AlertDialog.h"
#import <Social/SLComposeViewController.h>
#import <Social/SLServiceTypes.h>
#include "Constant.h"
#include "Flurry.h"
#include "FlurryConstant.h"

@implementation RootViewController

-(void) purchaseSuccessfull:(NSString *)itemId {
    NSLog(@"purchaseSuccessfull");
    if([itemId isEqualToString:@kRemoveAds]){
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:itemId];
        [self removeAd];
        NSDictionary *dict = @{@"hiiii": @"hello"};
        [IOSNDKHelper SendMessage:@"removeAdsListener" WithParameters:dict];
    }else if ([itemId isEqualToString:@kBuy5000Coins] || [itemId isEqualToString:@kBuy25000Coins] || [itemId isEqualToString:@kBuy75000Coins] || [itemId isEqualToString:@kBuy300000Coins]){
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:itemId];
        NSDictionary *dict = @{@"COINS_ID": itemId};
        [IOSNDKHelper SendMessage:@"updateCoinsCount" WithParameters:dict];
    }else if ([itemId isEqualToString:@kBuy5Stars] || [itemId isEqualToString:@kBuy50Stars] || [itemId isEqualToString:@kBuy200Stars] || [itemId isEqualToString:@kBuy500Stars]){
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:itemId];
        NSDictionary *dict = @{@"STARS_ID": itemId};
//        CCLOG("item id is %@", itemId);
        NSLog(@"item id is %@", itemId);
        [IOSNDKHelper SendMessage:@"updateStarsCount" WithParameters:dict];
    }else if([itemId isEqualToString:@kUnlockAllCharacters]){
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:itemId];
        NSDictionary *dict = @{@"hiiii": @"hello"};
        [IOSNDKHelper SendMessage:@"replaceSceneAfterUnlock" WithParameters:dict];
    }
}

- (void)productPurchased:(NSString *)productId {
    CCLOG("product purchased");
}

-(void) purchaseFailed:(NSString *)itemId{
    NSLog(@"failed");
}

- (void) submitScore:(NSObject *)prms{
    AppController *delegate = (AppController*)[[UIApplication sharedApplication] delegate];
    NSDictionary *parameters = (NSDictionary*)prms;
    int score = [parameters[@"score"] intValue];
    NSString *leaderboardId = (NSString*)parameters[@"leaderBoardId"];
    [delegate.gameCenterManager reportScore:score forCategory:leaderboardId];
}

- (void) unlockAchievement:(NSObject *)prms{
    AppController *delegate = (AppController*)[[UIApplication sharedApplication] delegate];
    NSDictionary *parameters = (NSDictionary*)prms;
    NSString* achivementID = (NSString*)parameters[@"unlockId"];
    NSString* msgString = (NSString*)parameters[@"msgString"];
    [delegate.gameCenterManager submitAchievement:achivementID percentComplete:100];
//    [GKNotificationBanner showBannerWithTitle:@"Unlocked" message:msgString completionHandler:nil];
}

- (void) startPuchaseFlow:(NSObject *)prms{
    inAppPurchase = [[InAppPurchaseLayer alloc]initwithViewController:self];
    inAppPurchase.delegate_ = self;
    
    NSDictionary *parameters = (NSDictionary*)prms;
    NSString* purchaseItem = (NSString*)parameters[@"PURCHASE_ITEM"];
    if([purchaseItem isEqualToString:@"REMOVE_ADS"]) {
        [inAppPurchase purchaseItem:@kRemoveAds];
    }else if([purchaseItem isEqualToString:@"UNLOCK ALL CHARACTERS"]) {
        [inAppPurchase purchaseItem:@kUnlockAllCharacters];
    }else if([purchaseItem isEqualToString:@"PURCHASE 5000 COINS"]) {
        [inAppPurchase purchaseItem:@kBuy5000Coins];
    }else if([purchaseItem isEqualToString:@"PURCHASE 25000 COINS"]) {
        [inAppPurchase purchaseItem:@kBuy25000Coins];
    }else if([purchaseItem isEqualToString:@"PURCHASE 75000 COINS"]) {
        [inAppPurchase purchaseItem:@kBuy75000Coins];
    }else if([purchaseItem isEqualToString:@"PURCHASE 300000 COINS"]) {
        [inAppPurchase purchaseItem:@kBuy300000Coins];
    }else if([purchaseItem isEqualToString:@"PURCHASE 5 STARS"]) {
        [inAppPurchase purchaseItem:@kBuy5Stars];
    }else if([purchaseItem isEqualToString:@"PURCHASE 50 STARS"]) {
        [inAppPurchase purchaseItem:@kBuy50Stars];
    }else if([purchaseItem isEqualToString:@"PURCHASE 200 STARS"]) {
        [inAppPurchase purchaseItem:@kBuy200Stars];
    }else if([purchaseItem isEqualToString:@"PURCHASE 500 STARS"]) {
        [inAppPurchase purchaseItem:@kBuy500Stars];
    }
    NSLog(@"purchase item %@", purchaseItem);
}

- (void) postToAvalanche:(NSObject *)prms {
  NSURL *url = [NSURL URLWithString:@"http://www.avalanchemountainapps.com/"];
        [[UIApplication sharedApplication] openURL:url];
}

- (void) setDefaultPlayer:(NSObject *)prms {
    if ([GameCenterManager isGameCenterAvailable]) {
        AppController *delegate = (AppController*)[[UIApplication sharedApplication] delegate];
        [delegate.gameCenterManager authenticateLocalUser];
         NSLog(@"User alias: %@",[[GKLocalPlayer localPlayer]alias]);
        NSString *name = [NSString stringWithFormat:@"%@", [[GKLocalPlayer localPlayer]alias]];
        Utility::setDefaultPlayerName([name cString]);
    } else {
        CCLOG("game center not available");
    }

}

- (void) restorePurchase:(NSObject *)prms{
    CCLOG("restroe purchasess");
    inAppPurchase = [[InAppPurchaseLayer alloc]initwithViewController:self];
    inAppPurchase.delegate_ = self;
    [inAppPurchase restorePurchasedItems];
}

-(void) leaderBoardController:(NSObject *)prms {
    GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc] init];
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    if ([appDelegate.gameCenterManager isPlayerLoggedIn]) {
        NSLog(@"leaderboardController is %@", leaderboardController);
        if (leaderboardController != NULL){
            //            leaderboardController.leaderboardDelegate = self;
            [self presentModalViewController: leaderboardController animated: YES];
            leaderboardController.leaderboardDelegate = self;
        }
    }else{
        [appDelegate.gameCenterManager authenticateLocalUser];
    }
}

- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController{
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate.viewController dismissModalViewControllerAnimated:YES];
}

-(void)  achievementController:(NSObject *)prms{
    GKAchievementViewController *achievementController = [[GKAchievementViewController alloc] init];
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    if ([appDelegate.gameCenterManager isPlayerLoggedIn]) {
        if (achievementController != NULL){
            //            achievementController.achievementDelegate = self;
            [self presentModalViewController:achievementController animated: YES];
            achievementController.achievementDelegate = self;
        }
    }else{
        [appDelegate.gameCenterManager authenticateLocalUser];
    }
}

- (void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController {
    AppController *appDelegate = (AppController *)[[UIApplication sharedApplication] delegate];
    [appDelegate.viewController dismissModalViewControllerAnimated:YES];
}

-(void)repositionAd{
    //    bannerAdView.frame = CGRectMake(origin.x, origin.y, bannerAdView.frame.size.width, bannerAdView.frame.size.height);
    //    [self.view addSubview:self.bannerAdView];
}

-(void)attachAd{
    //    if (bannerAdView == nil) {
    //        [self makeAdRequest];
    //        [self repositionAd];
    //    }else {
    //        [self repositionAd];
    //    }
}

-(void)showTopAd {
    [self removeAd];
    //    GADAdSize adSize = isLargeAds ? kGADAdSizeLeaderboard : kGADAdSizeBanner;
    //    origin = CGPointMake(screenSize.height/2 - adSize.size.width/2 , 0.0);
    [self attachAd];
}

-(void)showBottomAd {
    [self removeAd];
    //    GADAdSize adSize = isLargeAds ? kGADAdSizeLeaderboard : kGADAdSizeBanner;
    //    origin = CGPointMake(screenSize.height/2 - adSize.size.width/2, screenSize.width - adSize.size.height);
    [self attachAd];
}

-(void)removeAd {
    if(bannerAdView != nil) {
        [bannerAdView removeFromSuperview];
        /* uncomment these lines if want new request on every scene
         [bannerAdView setDelegate:nil];
         [bannerAdView release];
         bannerAdView = nil;
         */
    }
}

- (void) makeAdRequest{
//        GADAdSize adSize = isLargeAds ? kGADAdSizeLeaderboard : kGADAdSizeBanner;
//        self.bannerAdView = [[[GADBannerView alloc] initWithAdSize:adSize origin:origin] autorelease];
//        self.bannerAdView.adUnitID = @"9d1f89091b704bb0";
//        self.bannerAdView.delegate = self;
//        [self.bannerAdView setRootViewController:self];
//        [self.bannerAdView loadRequest:[self createRequest]];
}

-(void)hideAds {
//        bannerAdView.hidden = YES;
}

- (void) controlAds:(NSObject *)prms{
    NSDictionary *parameters = (NSDictionary*)prms;
    NSString* showbottom = (NSString*)parameters[@"showbottom"];
    NSString* showtop = (NSString*)parameters[@"showtop"];
    [self removeAd];
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    CCSize frameSize = pEGLView->getFrameSize();
    
    if(frameSize.height > 640) {
        isLargeAds = YES;
    }
    if([showbottom isEqualToString:@"YES"]) {
        [self showBottomAd];
    }
    
    if([showtop isEqualToString:@"YES"]) {
        [self showTopAd];
    }
    [self shouldDisplayChartboostAd:prms];
}

-(void) sendFlurryReport:(NSObject *)prms {
    NSLog(@"sendFlurryReport called ..");
    NSDictionary *parameters = (NSDictionary*)prms;
//    NSLog(@"purchase item is %@", purchaseItem);
        NSString* eventItem = (NSString*)parameters[@"FLURRY_EVENT"];
        NSString* purchaseItem = (NSString*)parameters[@"PURCHASE_ITEM"];
    if(purchaseItem != nil){
        eventItem = purchaseItem;
    }
    
    if ([eventItem isEqualToString:@"GAME START"]) {
        [Flurry logEvent:@"Play Button Pressed" timed:YES];
    }else if([eventItem isEqualToString:@"GAME END"]){
        [Flurry endTimedEvent:@"Play Button Pressed" withParameters:nil];
    }else {
        [Flurry logEvent:eventItem];
    }
}

- (void) shouldDisplayChartboostAd:(NSObject *)prms{
    NSLog(@"shouldDisplayChartboostAd");
    AppController *appController = (AppController*)[[UIApplication sharedApplication] delegate];
    NSDictionary *parameters = (NSDictionary*)prms;
    NSString* cbadEnabled = (NSString*)parameters [@"ChartboostAd"];
    appController.shouldDisplayCBAd = [cbadEnabled isEqualToString:@"YES"];
    NSDate *currentTime = [NSDate date];
    float timeInterval = [currentTime timeIntervalSinceDate:appController.gameStartTime];
//    if(((int)timeInterval > appController.chartBoostDelayTime)) {
//        if(appController.shouldDisplayCBAd) {
            Chartboost *cb = [Chartboost sharedChartboost];
            [cb showInterstitial];
//        }
//    }
}

-(void) showMoreApps:(NSObject *)prms {
    CCLOG("show more apps");
    Chartboost *cb = [Chartboost sharedChartboost];
    [cb showMoreApps];
}

-(void)sendFeedbackByMail:(NSObject *)prms {
    NSDictionary *parameters = (NSDictionary*)prms;
    NSString* title = (NSString*)parameters[@"MailTo"];
    NSString* message = (NSString*)parameters[@"Subject"];
    NSMutableArray *usersTo = [[NSMutableArray alloc] init];
    [usersTo addObject:title];
    
    CCDirector::sharedDirector()->pause();
    CCDirector::sharedDirector()->stopAnimation();
    
    MFMailComposeViewController *picker = [[MFMailComposeViewController alloc] init];
    if (!picker) //happens if no email is configured on your device
    {
        CCDirector::sharedDirector()->resume();
        CCDirector::sharedDirector()->startAnimation();
        return;
    }
    picker.mailComposeDelegate = self;
    [picker setToRecipients:usersTo];
    [picker setSubject:message];
    [picker setMessageBody:@"" isHTML:YES];

    CCDirector::sharedDirector()->getOpenGLView();
    if ([self respondsToSelector:@selector(presentViewController:animated:completion:)]){
        [self presentViewController:picker animated:YES completion:nil];
    } else {
        [self presentModalViewController:picker animated:YES];
    }
    [picker release];
}

-(void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error {
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->startAnimation();
    if ([self respondsToSelector:@selector(presentViewController:animated:completion:)]){
        [controller dismissViewControllerAnimated:NO completion:nil];
    } else {
        [controller dismissModalViewControllerAnimated:NO];
    }
    
}

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
 
*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskLandscape;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


-(void)initiateFacebookLogin:(NSObject *)prms{
//    if([[[UIDevice currentDevice] systemVersion] floatValue]  >= 6.0){
        [self postToFacebook:prms];
//    }else{
//        FacebookScorer *facebookScorer = [[FacebookScorer alloc] init];
//        [facebookScorer postToWallWithDialogNewHighscore:25];
//    }
}

- (void) postToFacebook:(NSObject *)prms {
   // if([SLComposeViewController isAvailableForServiceType:SLServiceTypeFacebook]) {
    if ( [[UIDevice currentDevice].systemVersion floatValue] >= 6.0) {
        SLComposeViewController *controller = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeFacebook];
        int score = [(NSString*)[prms valueForKey:@"CurrentScore"] intValue];
        [controller setInitialText:[NSString stringWithFormat:@kFbPostScoreText, score]];
        [controller addURL:[NSURL URLWithString:@kAppUrl]];
                [controller addImage:[UIImage imageNamed:@"socialsharing-facebook-image.jpg"]];
        [self presentViewController:controller animated:YES completion:Nil];
    }
 //   }
}

-(void)showNotEnoughCoinsDialogue:(NSObject *)prms{
    NSDictionary *parameters = (NSDictionary*)prms;
    NSString* title = (NSString*)parameters[@"title"];
    NSString* message = (NSString*)parameters[@"message"];
    NSString* button0 = (NSString*)parameters[@"button0"];
    NSString* button1 = (NSString*)parameters[@"button1"];
    NSString* button2 = (NSString*)parameters[@"button2"];
    NSString* calling = (NSString*)parameters[@"callFromScreen"];
    [[AlertDialog instance] showNotEnoughCoinsDialogue:title messageAlert:message button0:button0 button1:button1 button2:button2 calling:calling];
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        [IOSNDKHelper SetNDKReciever:self];
    }
    return self;
}


- (void)dealloc {
    [super dealloc];
}


@end
