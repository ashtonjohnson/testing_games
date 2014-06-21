//
//  NetworkUtility.m
//  InterviewBuzz
//
//  Created by sdhillon on 05/08/09.
//  Copyright 2009 sdhillon. All rights reserved.
//

#import "NetworkUtility.h"
#import <SystemConfiguration/SCNetworkReachability.h>
#import <netinet/in.h>

@implementation NetworkUtility

- (BOOL)isReachableWithoutRequiringConnection:(SCNetworkReachabilityFlags)flags
{
    // kSCNetworkReachabilityFlagsReachable indicates that the specified nodename or address can
	// be reached using the current network configuration.
	BOOL isReachable = flags & kSCNetworkReachabilityFlagsReachable;
	
	// This flag indicates that the specified nodename or address can
	// be reached using the current network configuration, but a
	// connection must first be established.
	//
	// If the flag is false, we don't have a connection. But because CFNetwork
    // automatically attempts to bring up a WWAN connection, if the WWAN reachability
    // flag is present, a connection is not required.
	BOOL noConnectionRequired = !(flags & kSCNetworkReachabilityFlagsConnectionRequired);

	#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
	if ((flags & kSCNetworkReachabilityFlagsIsWWAN)) {		
	#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED)
	if ((flags & kSCNetworkReachabilityFlagsReachable)) {			
	#endif
		
		noConnectionRequired = YES;
	}
	
	return (isReachable && noConnectionRequired) ? YES : NO;
}

// Perform a reachability query for the address 0.0.0.0. If that address is reachable without
// requiring a connection, a network interface is available. We'll have to do more work to
// determine which network interface is available.
- (BOOL)isNetworkAvailableFlags:(SCNetworkReachabilityFlags *)outFlags
{

	struct sockaddr_in zeroAddress;
	bzero(&zeroAddress, sizeof(zeroAddress));
	zeroAddress.sin_len = sizeof(zeroAddress);
	zeroAddress.sin_family = AF_INET;
	
	SCNetworkReachabilityRef defaultRouteReachability = SCNetworkReachabilityCreateWithAddress(NULL, (struct sockaddr *)&zeroAddress);
	
	
	SCNetworkReachabilityFlags flags;
	BOOL gotFlags = SCNetworkReachabilityGetFlags(defaultRouteReachability, &flags);
	if (!gotFlags) {
        return NO;
    }
    
	BOOL isReachable = [self isReachableWithoutRequiringConnection:flags];
	
	// Callers of this method might want to use the reachability flags, so if an 'out' parameter
	// was passed in, assign the reachability flags to it.
	if (outFlags) {
		*outFlags = flags;
	}
	
	return isReachable;
	return NO;
}

- (NetworkStatus)internetConnectionStatus
{
	/*
     To determine if the device has an Internet connection, query the address
     0.0.0.0. If it's reachable without requiring a connection, first check
     for the kSCNetworkReachabilityFlagsIsDirect flag, which tell us if the connection
     is to an ad-hoc WiFi network. If it is not, the device can access the Internet.
     The next thing to determine is how the device can access the Internet, which
     can either be through the carrier data network (EDGE or other service) or through
     a WiFi connection.
     
     Note: Knowing that the device has an Internet connection is not the same as
     knowing if the device can reach a particular host. To know that, use
     -[Reachability remoteHostStatus].
     */
	
	SCNetworkReachabilityFlags defaultRouteFlags;
	BOOL defaultRouteIsAvailable = [self isNetworkAvailableFlags:&defaultRouteFlags];
	if (defaultRouteIsAvailable) {
        
		if (defaultRouteFlags & kSCNetworkReachabilityFlagsIsDirect) {
            
			// The connection is to an ad-hoc WiFi network, so Internet access is not available.
			return NotReachable;
		}
		else if (defaultRouteFlags & ReachableViaCarrierDataNetwork) {
			return ReachableViaCarrierDataNetwork;
		}
		
		return ReachableViaWiFiNetwork;
	}
	
	return NotReachable;
}

@end
