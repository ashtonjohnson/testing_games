//
//  MainLayer.h
//  TankMania
//
//  Created by Ramesh on 22/10/13.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//


#import <StoreKit/StoreKit.h>

@protocol InAppPurchaseDelegate

-(void) purchaseSuccessfull:(NSString *)itemId;
-(void) purchaseFailed:(NSString *)itemId;

@end

@interface InAppPurchaseLayer : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver> {
	NSString *strPurchaseId_;
	UIActivityIndicatorView *activityIndicator;
	CGSize screenSize;
	id <InAppPurchaseDelegate> delegate_;
    SKProductsRequest *request;
}

@property(copy) NSString *strPurchaseId_;
@property(assign) id <InAppPurchaseDelegate> delegate_;

- (id) initwithViewController:(UIViewController*)controller;
-(void) loadProductsInfo;
-(void) makePurchase:(SKProduct *) product;
-(BOOL) isPresentNonFinishedTransaction;
-(void) didFinishPaymentTransaction:(SKPaymentTransaction *) transaction;
-(void) didFailPaymentTransactionWithError:(NSError *) error;
-(void) purchaseItem: (NSString *)itemId;
-(void) onExit;
-(void) restorePurchase;
-(void) restorePurchasedItems;

@end