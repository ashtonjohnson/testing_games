//
//  MainLayer.m
//  TankMania
//
//  Created by Ramesh on 22/10/13.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "InAppPurchaseLayer.h"
#import "Utility.h"
//#import "Constants.h"
#import "NetworkUtility.h"
//#import "SoundConstants.h"
#import "AppController.h"
#include "IOSNDKHelper.h"
@implementation InAppPurchaseLayer

@synthesize strPurchaseId_;
@synthesize delegate_;

#define kTagTheme1 80
#define kTagTheme2 81
#define kTagTheme3 82


- (id) initwithViewController:(UIViewController*)controller {
    self = [super init];
    if (self != nil) {
        screenSize = [[controller view] frame].size;
        CGRect frameRect = (Utility::isPad)? CGRectMake(0.0f, 0.0f, 64.0f, 64.0f) : CGRectMake(0.0f, 0.0f, 32.0f, 32.0f);
        activityIndicator = [[UIActivityIndicatorView alloc] initWithFrame:frameRect];
        [activityIndicator setCenter:CGPointMake(screenSize.height/2, screenSize.width/2)];
        [activityIndicator setActivityIndicatorViewStyle:UIActivityIndicatorViewStyleWhiteLarge];
        [controller.view addSubview:activityIndicator];
    }
    return self;
}

- (void)restoreTransaction:(NSString *)productIdentifier {
    [self productPurchased:productIdentifier];
}

-(void) restorePurchase {
    NetworkUtility *networkUtility = [[NetworkUtility alloc] init];
    UIAlertView *alert;
    if ([networkUtility internetConnectionStatus] == NotReachable) {
        alert = [[UIAlertView alloc] initWithTitle:@"Internet Access not available" message:@"Please connect to the Internet and try again."
                                          delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
    } else {
        alert = [[UIAlertView alloc] initWithTitle:@"Restore Purchases" message:@"This will restore all previous in-app purchases, if any. Press OK to continue"
                                          delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles: @"OK", nil];
    }
    [alert show];
    [alert release];
    [networkUtility release];
}

-(void) restorePurchasedItems {
    [activityIndicator startAnimating];
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

- (void)alertView:(UIAlertView *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex{
    if (buttonIndex == 1) {
        [self restorePurchasedItems];
    }else if (buttonIndex == 0){
//        [self enableTouch];
    }
}

-(void) purchaseItem: (NSString *)itemId{
    strPurchaseId_  = itemId;
	NetworkUtility *networkUtility = [[NetworkUtility alloc] init]; 
	if ([networkUtility internetConnectionStatus] == NotReachable) {
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Internet Access not available" message:@"Please connect to the Internet and try again."
                                                       delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
		[alert show];	
		[alert release];
	} else {
		[self loadProductsInfo];		
	}
	[networkUtility release];
}


-(void) loadProductsInfo {
	[activityIndicator startAnimating];
    if ([SKPaymentQueue canMakePayments]) {
        request = [[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithObject:strPurchaseId_]];
        [request setDelegate:self];
        [request start];
    }
}

-(void) makePurchase:(SKProduct *)product {
	[activityIndicator startAnimating];
	if (![SKPaymentQueue canMakePayments]) {
		[self didFailPaymentTransactionWithError:[NSError errorWithDomain: @"paymentDomain" code: 123 userInfo: @{NSLocalizedDescriptionKey: @"can not make payments"}]];
	}
    
	SKPayment *payment = [SKPayment paymentWithProduct:product];
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
	[[SKPaymentQueue defaultQueue] addPayment:payment];
}

-(void) didLoadInfo:(SKProduct *) products {
	[activityIndicator stopAnimating];
	[self makePurchase:products];	
}

-(void)didFailLoadProductInfo:(NSError *) error {
	[activityIndicator stopAnimating];
    [delegate_ purchaseFailed:strPurchaseId_];
}

-(BOOL) isPresentNonFinishedTransaction {
	NSArray *arrTransactions = [[SKPaymentQueue defaultQueue] transactions];
	for (SKPaymentTransaction *transaction in arrTransactions) {
		if ([transaction.payment.productIdentifier isEqualToString: strPurchaseId_]) {
			if (transaction.transactionState == SKPaymentTransactionStatePurchasing) {
				return YES;
			} else if (transaction.transactionState == SKPaymentTransactionStateFailed) {
				[[SKPaymentQueue defaultQueue] finishTransaction: transaction];
			}

		}
	}
	return NO;
}

-(void) productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
	NSArray *invalidIdentifires = [response invalidProductIdentifiers];
	NSArray *products = [response products];
	for (SKProduct *product in products) {
		NSString *strId = product.productIdentifier;
		if ([strId isEqualToString: strPurchaseId_]) {
			[self didLoadInfo:product];
			return;
		}
	}
	if ([invalidIdentifires count]) {
		[self didFailLoadProductInfo: [NSError errorWithDomain: @"purchaseDomain" code: 143 userInfo:@{NSLocalizedDescriptionKey: @"No Products found"}]];
	}
}


#pragma mark ---transaction observer---

-(void) paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
	for (SKPaymentTransaction *transaction in transactions) {
		SKPayment *payment = [transaction payment];
		if ([payment.productIdentifier isEqualToString: strPurchaseId_]) {
			if (transaction.transactionState == SKPaymentTransactionStatePurchased) {
				[self didFinishPaymentTransaction: transaction];
				[queue finishTransaction: transaction];
			} else if (transaction.transactionState == SKPaymentTransactionStateFailed) {
				[self didFailPaymentTransactionWithError: [NSError errorWithDomain:@"purchaseDomain" code:1542 userInfo: nil]];
				[queue finishTransaction: transaction];
			}else if (transaction.transactionState == SKPaymentTransactionStateRestored) {
                [self restoreTransaction: transaction.payment.productIdentifier];
				[queue finishTransaction: transaction];
			}
		}
	}
}

// saves a record of the transaction by storing the receipt to disk
- (void)productPurchased:(NSString *)productId {
	[delegate_ purchaseSuccessfull:strPurchaseId_];
}


-(void)didFinishPaymentTransaction:(SKPaymentTransaction *) transaction {
	[activityIndicator stopAnimating];
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    [self productPurchased:transaction.payment.productIdentifier];
}

-(void)didFailPaymentTransactionWithError:(NSError *) error { 
	[activityIndicator stopAnimating];
    [delegate_ purchaseFailed:strPurchaseId_];
}

-(void) paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray *)transactions {
    [activityIndicator stopAnimating];
}

- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error {
	NSLog(@"%@",error);
    [activityIndicator stopAnimating];
}

- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue {
    [activityIndicator stopAnimating];
    for (SKPaymentTransaction *transaction in queue.transactions){
        CCLog("hello");
        NSString *productID = transaction.payment.productIdentifier;
        NSLog( @"PROD ID = %@",productID);
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:productID];
        if([productID isEqualToString:@kRemoveAds]){
            Utility::setAdFreeVersion();
        }
        else if([productID isEqualToString:@kUnlockAllCharacters]){
            Utility::setUnlockAllCharacter();
        }
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:productID];

    }
    UIAlertView *alert;
    alert = [[UIAlertView alloc] initWithTitle:@"Purchases Restored" message:@"Your previously purchased products have been restored" delegate:self cancelButtonTitle:nil otherButtonTitles: @"Thanks", nil];	
    [alert show];	
    [alert release];
    
    NSDictionary *dict = @{@"hiiii": @"hello"};
    [IOSNDKHelper SendMessage:@"restorePurchases" WithParameters:dict];
}


- (void) dealloc{
    [activityIndicator stopAnimating];
//    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    if(request != nil) {
        [request release];
        request = nil;
    }
    if(activityIndicator != nil) {
        [activityIndicator release];
        activityIndicator = nil;
    }
    
    if(delegate_ != nil) {
        delegate_ = nil;
    }
	[super dealloc];
}

@end
