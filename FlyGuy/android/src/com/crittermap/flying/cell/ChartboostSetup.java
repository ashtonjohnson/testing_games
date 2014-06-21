package com.crittermap.flying.cell;

import android.app.Activity;
import android.util.Log;

import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.ChartboostDelegate;

public class ChartboostSetup {
	static Chartboost chartboost;
	
	public static Chartboost init(Activity pActivity) {
		chartboost = Chartboost.sharedChartboost();
		chartboost.onCreate(pActivity, Constants.CHARTBOOST_APP_ID, Constants.CHARTBOOST_APP_SIGN, ChartboostSetup.getChartboostDelegate());		
		chartboost.setImpressionsUseActivities(true);
		chartboost.startSession();
		chartboost.cacheInterstitial();
		chartboost.cacheMoreApps();
		return chartboost;
	}
	
	public static ChartboostDelegate getChartboostDelegate() {
		ChartboostDelegate chartBoostDelegate = new ChartboostDelegate() {
			@Override
			public boolean shouldDisplayInterstitial(String location) {
				FlyGuy.getActivity().pauseAnimations();
				return FlyGuy.showChartBoostAd;
			}
			
			@Override
			public boolean shouldRequestInterstitial(String location) {
				return FlyGuy.showChartBoostAd;
			}
			
			@Override
			public void didCacheInterstitial(String location) {
			}

			@Override
			public void didFailToLoadInterstitial(String location) {

			}

			@Override
			public void didDismissInterstitial(String location) {
				chartboost.cacheInterstitial(location);
				FlyGuy.prevAdTime = System.currentTimeMillis();
			}

			@Override
			public void didCloseInterstitial(String location) {
				FlyGuy.prevAdTime = System.currentTimeMillis();
			}
			
			@Override
			public void didClickInterstitial(String location) {
				FlyGuy.prevAdTime = System.currentTimeMillis();	
			}

			@Override
			public void didShowInterstitial(String location) {
			}

			@Override
			public boolean shouldDisplayLoadingViewForMoreApps() {
				return true;
			}
			
			@Override
			public boolean shouldRequestMoreApps() {

				return true;
			}

			@Override
			public boolean shouldDisplayMoreApps() {
				return true;
			}
			
			@Override
			public void didFailToLoadMoreApps() {
			}

			@Override
			public void didCacheMoreApps() {
			}
			
			@Override
			public void didDismissMoreApps() {
			}

			
			@Override
			public void didCloseMoreApps() {
			}

			@Override
			public void didClickMoreApps() {
			}

			@Override
			public void didShowMoreApps() {
			}

			public boolean shouldRequestInterstitialsInFirstSession() {
				return true;
			}

			@Override
			public void didFailToLoadUrl(String arg0) {
				
			}
		};
		return chartBoostDelegate;
	}
}
