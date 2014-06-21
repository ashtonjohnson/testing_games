//
//  NetworkUtility.h
//  InterviewBuzz
//
//  Created by sdhillon on 05/08/09.
//  Copyright 2009 sdhillon. All rights reserved.
//

/*
 An enumeration that defines the return values of the network state
 of the device.
 */
typedef enum {
	NotReachable = 0,
	ReachableViaCarrierDataNetwork,
	ReachableViaWiFiNetwork
} NetworkStatus;

@interface NetworkUtility : NSObject {

}

- (NetworkStatus)internetConnectionStatus;

@end
