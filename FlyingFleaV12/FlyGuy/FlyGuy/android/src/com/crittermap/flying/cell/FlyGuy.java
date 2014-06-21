/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.crittermap.flying.cell;

import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import net.robotmedia.billing.BillingController;
import net.robotmedia.billing.BillingRequest.ResponseCode;
import net.robotmedia.billing.helper.AbstractBillingObserver;
import net.robotmedia.billing.model.Transaction;
import net.robotmedia.billing.model.Transaction.PurchaseState;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHelper;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.widget.EditText;
import android.widget.Toast;

import com.chartboost.sdk.Chartboost;
import com.crittermap.flying.cell.GameHelper.GameHelperListener;
import com.easyndk.classes.AndroidNDKHelper;
import com.flurry.android.FlurryAgent;
import com.google.android.gms.appstate.AppStateClient;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.games.GamesClient;
import com.google.android.gms.games.OnSignOutCompleteListener;
import com.google.android.gms.plus.PlusClient;

import com.mopub.mobileads.MoPubView;


public class FlyGuy extends Cocos2dxActivity implements GameHelperListener, OnSignOutCompleteListener{
	static boolean isGooglePlay = true;
	public boolean isBillingSupported = true;
	protected static boolean showChartBoostAd = true;
	protected static long prevAdTime;
	protected GameHelper mHelper;
	public static final int CLIENT_GAMES = GameHelper.CLIENT_GAMES;
	public static final int CLIENT_APPSTATE = GameHelper.CLIENT_APPSTATE;
	public static final int CLIENT_PLUS = GameHelper.CLIENT_PLUS;
	public static final int CLIENT_ALL = GameHelper.CLIENT_ALL;
	protected int mRequestedClients = CLIENT_GAMES;
	
	static SharedPreferences gamePrefrence;
	String calling;
	public static AbstractBillingObserver mBillingObserver;
	static FlyGuy flyGuyActivity;
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		AndroidNDKHelper.SetNDKReciever(this);
		ChartboostSetup.init(this);
		
		FlurryAgent.onStartSession(this, Constants.FLURRY_ID);
		FlurryAgent.setLogEnabled(true);
		loadIAP();
		gamePrefrence = getSharedPreferences("null", MODE_PRIVATE);
        mHelper.setup(this, mRequestedClients);
        flyGuyActivity = this;
	}
	
	static FlyGuy getActivity(){
		
		return flyGuyActivity;
	}

	public void pauseAnimations(){
		AndroidNDKHelper.SendMessageWithParameters("stopAnimations", getDict());
	    Timer t = new Timer();
	    t.schedule(new TimerTask() {
	        @Override
	        public void run() {
	        	resumeAnimations(); 
	        }
	    },1000);
	}
	
	public void resumeAnimations(){
		AndroidNDKHelper.SendMessageWithParameters("startAnimations", getDict());
	}
	
	private void loadIAP() {
		BillingController.setDebug(true);
		mBillingObserver = new AbstractBillingObserver(this) {
			@Override
			public void onBillingChecked(boolean supported) {
				FlyGuy.this.onBillingChecked(supported);
			}

			@Override
			public void onPurchaseStateChanged(String itemId, PurchaseState state) {
				FlyGuy.this.onPurchaseStateChanged(itemId, state);
			}

			@Override
			public void onRequestPurchaseResponse(String itemId, ResponseCode response) {
				FlyGuy.this.onRequestPurchaseResponse(itemId, response);
			}
		};
		BillingController.registerObserver(mBillingObserver);
		BillingController.checkBillingSupported(this);
	}

	public void startPurchase(String mSku) {
		BillingController.requestPurchase(this, mSku, true /* confirm */);
	}
	
	public void restorePurchase() {
		if (!mBillingObserver.isTransactionsRestored()) {
			FlyGuy.this.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					BillingController.setDebug(true);
	    			BillingController.restoreTransactions(FlyGuy.this);
				}
			});
		}else {
			FlyGuy.this.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Toast.makeText(FlyGuy.this, "No purchased items available", Toast.LENGTH_SHORT).show();
				}
			});
		}
	}
	
	public void onBillingChecked(boolean supported) {
		if (supported) {
		} else {
		}
	}
	
	public void onPurchaseStateChanged(String itemId, PurchaseState state) {
		updateOwnedItems();
	}

	public void onRequestPurchaseResponse(String itemId, ResponseCode response) {
	}
	
	public void updateOwnedItems() {
		List<Transaction> transactions = BillingController.getTransactions(this);
		
		for (Transaction t : transactions) {
			if (t.purchaseState == PurchaseState.PURCHASED) {
				if((t.productId).equalsIgnoreCase(Constants.REMOVE_ADS_SKU)){
					setAdsFreeVersion();
				}else if((t.productId).equalsIgnoreCase(Constants.kUnlockAllCharacters)){
					unlockAllchar();
				}else if ((t.productId).equalsIgnoreCase(Constants.kBuy5000Coins)||(t.productId).equalsIgnoreCase(Constants.kBuy25000Coins)||(t.productId).equalsIgnoreCase(Constants.kBuy75000Coins)||(t.productId).equalsIgnoreCase(Constants.kBuy300000Coins)) {
					updateCoinsCount(t.productId);
				}else if ((t.productId).equalsIgnoreCase(Constants.kBuy5Stars)||(t.productId).equalsIgnoreCase(Constants.kBuy50Stars)||(t.productId).equalsIgnoreCase(Constants.kBuy200Stars)||(t.productId).equalsIgnoreCase(Constants.kBuy500Stars)) {
					updateStarsCount(t.productId);
				}
			}
		}
	}
	
	@Override
	protected void onStart() {
		super.onStart();
		Chartboost.sharedChartboost().onStart(this);
	}
	
	public void initiateFacebookLogin(JSONObject prms){
//		Session session = Session.getActiveSession();
//        if (!session.isOpened() && !session.isClosed()) {
//            session.openForRead(new Session.OpenRequest(this).setCallback(statusCallback));
//        } else {
//            Session.openActiveSession(this, true, statusCallback);
//        }
		
		Intent shareIntent = new Intent(android.content.Intent.ACTION_SEND);
	    shareIntent.setType("text/plain");
	    shareIntent.putExtra(Intent.EXTRA_TEXT, "https://play.google.com/store/apps/details?id=" + FlyGuy.getContext().getPackageName());    
	    this.startActivity(Intent.createChooser(shareIntent, "Check out this awesome game"));
	}
	
	public JSONObject getDict() {
		String jsonStr = "{\"fake_dictionary\":\"have_fun\"}";
		JSONObject prmsToSend = null;
		try{
			prmsToSend = new JSONObject(jsonStr);
		}
		catch (JSONException e){
			e.printStackTrace();
		} 
		return prmsToSend;
	}
	
	public void quitGame(JSONObject prms) {
		AlertDialog.Builder exitbuilder = new AlertDialog.Builder(this);
		exitbuilder.setTitle("FlyGuy")
		.setMessage("Do You Want To Quit")
		.setCancelable(false)
		.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
				AndroidNDKHelper.SendMessageWithParameters("resetListener", getDict());
			}
		})
		.setNegativeButton("No", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
				dialog.cancel();
			}
		});
		AlertDialog stopalert = exitbuilder.create();
		stopalert.show();
	}
    static {
         System.loadLibrary("game");
    }
    
    public void setAdsFreeVersion() {
		removeAd();
		AndroidNDKHelper.SendMessageWithParameters("removeAdsListener", getDict());
	}
    
    public void showAlertWithTitle(JSONObject prms){
		String title = null;
		String message = null;
		try{
			title = prms.getString("Title");
			message = prms.getString("Message");
		}
		catch (JSONException e){
			e.printStackTrace();
		}
		AlertDialog.Builder alertBuilder = new AlertDialog.Builder(this);
		alertBuilder.setTitle(title)
		.setMessage(message)
		.setCancelable(false)
		.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
				AndroidNDKHelper.SendMessageWithParameters("promoteToStore", getDict());
			}
		})
		.setNegativeButton("No", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
				dialog.cancel();
			}
		});
		AlertDialog showAlert = alertBuilder.create();
		showAlert.show();
	}
    
    public void showMoreApps(JSONObject prms){
		Chartboost chartBoost = Chartboost.sharedChartboost();
		chartBoost.showMoreApps();
		chartBoost.cacheMoreApps();
	}
    
    public void postToAvalanche(JSONObject prms){
		String url = Constants.WEB_URL;
		Intent urlIntent = new Intent(Intent.ACTION_VIEW);
		urlIntent.setData(Uri.parse(url));
		urlIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		startActivity(urlIntent);
	}
    
    public void showNotEnoughCoinsDialogue(JSONObject prms){
    	String title = null;
		String message = null;
		String button0 = null;
		String button1 = null;
		String button2 = null;
		try{
			title = prms.getString("title");
			calling = prms.getString("callFromScreen");
			button0 = prms.getString("button0");
			button2 = prms.getString("button2");
			button1 = prms.getString("button1");
			message = prms.getString("message");
		}catch (JSONException e){
			e.printStackTrace();
		}
    	
		AlertDialog.Builder exitbuilder = new AlertDialog.Builder(this); 
		exitbuilder.setTitle(title)
		.setMessage(message)
		.setCancelable(false)
		.setPositiveButton(button0, new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
				if(calling == null){
					return;
				}
				if (calling.equalsIgnoreCase("mainScreen")) {
					AndroidNDKHelper.SendMessageWithParameters("goToUpgradeScreenWithExtras", getDict());
		        } else if (calling.equalsIgnoreCase("upgradeScreen")){
		        	AndroidNDKHelper.SendMessageWithParameters("goToUpgradeScreenWithCoinsStars", getDict());
		        }else if (calling.equalsIgnoreCase("scoreScreen")){
		        	showDialogWithTextBox("Type Yes to confirm reset:");
		        }
			}
		})
		.setNeutralButton(button1, new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
				if (calling.equalsIgnoreCase("mainScreen")) {
					AndroidNDKHelper.SendMessageWithParameters("unlockAllChars", getDict());
		        } else if (calling.equalsIgnoreCase("upgradeScreen")){
		        } else if (calling.equalsIgnoreCase("scoreScreen")){
		        }
			}
		})
		.setNegativeButton(button2, new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {
				dialog.cancel();
			}
		});
		AlertDialog stopalert = exitbuilder.create();
		stopalert.show();
    }
    
    public void showDialogWithTextBox(String title){
    	final AlertDialog.Builder alert = new AlertDialog.Builder(this);
        final EditText input = new EditText(this);
        alert.setView(input);
        alert.setCancelable(false);
        alert.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
                String value = input.getText().toString().trim();
                if (!value.equalsIgnoreCase("yes")) {
                	showAlertMsz();
                } else {
                	AndroidNDKHelper.SendMessageWithParameters("replaceWithMainMenuScreen", getDict());
                }
            }
        });
        alert.show();
    }
    
    public void showAlertMsz(){
    	AlertDialog.Builder okay = new AlertDialog.Builder(FlyGuy.this);
    	okay.setTitle("You must type Yes, Reset cancelled");
    	okay.setCancelable(false);
    	okay.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
            }
        });
    	okay.show();
    }
	
	public void removeAd() {
		this.runOnUiThread(new Runnable() {
			@Override
			public void run() {
//				LinearLayout layoutBottom = (LinearLayout) findViewById(R.id.bottom);
//				layoutBottom.removeAllViews();
//				LinearLayout layoutTop = (LinearLayout) findViewById(R.id.top);
//				layoutTop.removeAllViews();
			}
		});
	}
	
	public void setUnlockAllLevels() {
		AndroidNDKHelper.SendMessageWithParameters("unlockLevelsListener", getDict());
	}
	
	public void shouldDisplayChartboostAd(JSONObject prms) {
		String cbadEnabled = null;
		try{
			cbadEnabled = prms.getString("ChartboostAd");
		}
		catch (JSONException e){
			e.printStackTrace();
		}		
//		if(cbadEnabled.equalsIgnoreCase("YES")) {
			showChartBoostAd = true;
			Chartboost chartBoost = Chartboost.sharedChartboost();
			chartBoost.showInterstitial();
			chartBoost.cacheInterstitial();
//		}
	}
	
	public void sendFlurryReport(JSONObject prms){
		String purchaseItem = null;
		String eveltItem = null;
		try{
			purchaseItem = prms.getString("PURCHASE_ITEM");
			eveltItem = prms.getString("FLURRY_EVENT");
		}
		catch (JSONException e){
			e.printStackTrace();
		}	
		if(purchaseItem != null){
	        eveltItem = purchaseItem;
	    }
		
		if (eveltItem.equalsIgnoreCase("GAME START")) {
	        FlurryAgent.logEvent("Play Button Pressed", true);
	    }else if(eveltItem.equalsIgnoreCase("GAME END")){
	        FlurryAgent.logEvent("Play Button Pressed");
	    }else {
	    	FlurryAgent.logEvent(eveltItem);
	    }
	}
	
	public static Boolean shouldDisplayAds() {
		long currentTime = System.currentTimeMillis();
		long adResultTime = ((currentTime - prevAdTime)/1000)/60;
		Boolean adEnabled;
		if(adResultTime >= 0){
			adEnabled = true;
		}else {
			adEnabled = false;
		}
		return adEnabled;
	}
	
	public void sendFeedbackByMail(JSONObject prms){
		String mailTo = null;
		String subject = null;
		try{
			mailTo = prms.getString("MailTo");
			subject = prms.getString("Subject");
		}
		catch (JSONException e){
			e.printStackTrace();
		}
		Intent mailToAction = new Intent(Intent.ACTION_SENDTO);
		Uri uri = Uri.parse("mailto:" + mailTo);
		mailToAction.setData(uri);
		mailToAction.putExtra("subject", subject);
		mailToAction.putExtra("body", "");
		startActivity(mailToAction);
	}
	
	public void startPuchaseFlow(JSONObject prms){
		if(isGooglePlay){
			String purchaseItem = null;
			try{
				purchaseItem = prms.getString("PURCHASE_ITEM");
			}
			catch (JSONException e){
				e.printStackTrace();
			}
			if(purchaseItem.equalsIgnoreCase("REMOVE_ADS")) {
				startPurchase(Constants.REMOVE_ADS_SKU);
			}else if (purchaseItem.equalsIgnoreCase("PURCHASE 5000 COINS")) {
				startPurchase(Constants.kBuy5000Coins);
			}else if (purchaseItem.equalsIgnoreCase("PURCHASE 25000 COINS")) {
				startPurchase(Constants.kBuy25000Coins);
			}else if (purchaseItem.equalsIgnoreCase("PURCHASE 75000 COINS")) {
				startPurchase(Constants.kBuy75000Coins);
			}else if (purchaseItem.equalsIgnoreCase("PURCHASE 300000 COINS")) {
				startPurchase(Constants.kBuy300000Coins);
			}else if (purchaseItem.equalsIgnoreCase("PURCHASE 5 STARS")) {
				startPurchase(Constants.kBuy5Stars);
			}else if (purchaseItem.equalsIgnoreCase("PURCHASE 50 STARS")) {
				startPurchase(Constants.kBuy50Stars);
			}else if (purchaseItem.equalsIgnoreCase("PURCHASE 200 STARS")) {
				startPurchase(Constants.kBuy200Stars);
			}else if (purchaseItem.equalsIgnoreCase("PURCHASE 500 STARS")) {
				startPurchase(Constants.kBuy500Stars);
			}else if (purchaseItem.equalsIgnoreCase("UNLOCK ALL CHARACTERS")) {
				startPurchase(Constants.kUnlockAllCharacters);
			}
		}
	}
	
	@Override
    protected void onActivityResult(int requestCode, int responseCode, Intent data) {
    	super.onActivityResult(requestCode, responseCode, data);
    	if(requestCode == 9001){
    		mHelper.onActivityResult(requestCode, responseCode, data);
    	}
    }
	
	public void unlockAllchar() {
		AndroidNDKHelper.SendMessageWithParameters("replaceSceneAfterUnlock", getDict());
	}
	
	public void updateCoinsCount(String resultSKU) {
//		String jsonStr = "{\"fake_dictionary\":\"have_fun\"}";
		String jsonStr = "{"+"COINS_ID"+":"+resultSKU+"}";
		JSONObject prmsToSend = null;
		try{
			prmsToSend = new JSONObject(jsonStr);
		}
		catch (JSONException e){
			e.printStackTrace();
		} 
		AndroidNDKHelper.SendMessageWithParameters("updateCoinsCount", prmsToSend);
		Log.v("RAM", "updateCoinsCount = " + prmsToSend);
	}
	
	public void updateStarsCount(String resultSKU) {
//		String jsonStr = "{\"fake_dictionary\":\"have_fun\"}";
		String jsonStr = "{"+"STARS_ID"+":"+resultSKU+"}";
		JSONObject prmsToSend = null;
		try{
			prmsToSend = new JSONObject(jsonStr);
		}
		catch (JSONException e){
			e.printStackTrace();
		} 
		AndroidNDKHelper.SendMessageWithParameters("updateStarsCount", prmsToSend);
		Log.v("RAM", "updateStarsCount = " + prmsToSend);
	}
	
	//-----------------------------------Google play Game Service methods------------- //
    public FlyGuy() {
        super();
        mHelper = new GameHelper(this);
    }

    public FlyGuy(int requestedClients) {
        super();
        setRequestedClients(requestedClients);
    }

    protected void setRequestedClients(int requestedClients) {
        mRequestedClients = requestedClients;
    }
    
    @Override
    protected void onResume() {
    	Log.v("Tag FF","Resume");
        super.onResume();
        Cocos2dxHelper.onResume();
    }
    
    @Override
    protected void onPause() {
    	Log.v("Tag FF","Paused");
        super.onPause();
        Cocos2dxHelper.onPause();
        
    }

 /*   @Override
	public void onWindowFocusChanged(boolean hasFocus) {
		super.onWindowFocusChanged(hasFocus);
		if (!hasFocus) {
			onPause();
		}else {
			onResume();
		}
//		Handler h = new Handler();
//		Runnable r = new Runnable() {
//			@Override
//			public void run() {
//				onResume();	
//			}
//		};
//		h.post(r);
	}
   */
    protected GamesClient getGamesClient() {
        return mHelper.getGamesClient();
    }

    protected AppStateClient getAppStateClient() {
        return mHelper.getAppStateClient();
    }

    protected PlusClient getPlusClient() {
        return mHelper.getPlusClient();
    }
    
    public void getSignedStatus(JSONObject prms) {
    	String jsonStr = "{\"dictionary\":{\"bool_val\":\"false\"}}";
    	
		if(mHelper.isSignedIn()){
			jsonStr = "{\"dictionary\":{\"bool_val\":\"true\"}}";
		}
		try{
			final JSONObject prmsToSend = new JSONObject(jsonStr);
			if(prmsToSend!=null){
				AndroidNDKHelper.SendMessageWithParameters("mHelperListener",prmsToSend);
				
			}
		}
		catch (JSONException e){
			
			e.printStackTrace();
		} 
		
    }

    public void beginUserInitiatedSignIn(JSONObject prms) {
    	this.runOnUiThread(new Runnable() {
            public void run() {
            	mHelper.beginUserInitiatedSignIn();
            }
        });
    }

    public void signOut(JSONObject prms) {
    	mHelper.signOut();
    }
    
    @Override
    public void onSignOutComplete() {
    	mHelper.dismissDialog();
        if (mHelper.getGamesClient().isConnected()) {
        	mHelper.getGamesClient().disconnect();
        }
        AndroidNDKHelper.SendMessageWithParameters("signOutCompleteListener", getDict());
        Toast.makeText(this, R.string.SIGN_OUT, Toast.LENGTH_SHORT).show();
    }
    
    protected void showAlert(String title, String message) {
        mHelper.showAlert(title, message);
    }

    protected void showAlert(String message) {
        mHelper.showAlert(message);
    }

    protected void enableDebugLog(boolean enabled, String tag) {
        mHelper.enableDebugLog(enabled, tag);
    }

    protected String getInvitationId() {
        return mHelper.getInvitationId();
    }

    protected void reconnectClients(int whichClients) {
        mHelper.reconnectClients(whichClients);
    }

    protected String getScopes() {
        return mHelper.getScopes();
    }

    protected boolean hasSignInError() {
        return mHelper.hasSignInError();
    }

    protected ConnectionResult getSignInError() {
        return mHelper.getSignInError();
    }
    
    
    protected void setSignInMessages(String signingInMessage, String signingOutMessage) {
        mHelper.setSigningInMessage(signingInMessage);
        mHelper.setSigningOutMessage(signingOutMessage);
    }

	@Override
	public void onSignInFailed() {
	}

	@Override
	public void onSignInSucceeded() {
		String[] achievementArray = Constants.ACHIEVEMENTS_IDS;
		for(String achStr : achievementArray){
			if(gamePrefrence.getBoolean(achStr, false)){
				unlockAchievement(achStr);
			}
		}
//		AndroidNDKHelper.SendMessageWithParameters("signInCompleteListener", getDict());				
	}
	
	public void submitScore(final String leaderboardId, final int score) {
		runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				if(isGooglePlay) {
					if(mHelper.getGamesClient().isConnected()){
						getGamesClient().submitScore(leaderboardId, score);		
					}	
				}
			}
		});

	}
	
	public void submitScore(JSONObject prms) {
		String leaderboardId = null;
		String scoreString = null;
		int score = 0;
		try{
			leaderboardId = prms.getString("leaderBoardId");
			scoreString = prms.getString("score");
			score = Integer.parseInt(scoreString);
		}
		catch (JSONException e){
			e.printStackTrace();
		}
		submitScore(leaderboardId, score);
	}
	
	public void unlockAchievement (final String achId) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Editor editor = gamePrefrence.edit();
				if(!gamePrefrence.getBoolean(achId, false)){
					editor.putBoolean(achId, true);
			    	editor.commit();
				}
				if(isGooglePlay) {
					if(mHelper.getGamesClient().isConnected()){
						getGamesClient().unlockAchievement(achId);		
					}					
				}
			}
		});
	}
	
	public void unlockAchievement (JSONObject prms) {
		String achievementID = null;
		try{
			achievementID = prms.getString("unlockId");
		}
		catch (JSONException e){
			e.printStackTrace();
		}
		
		unlockAchievement(achievementID);
	}
	
	public void achievementController(JSONObject prms){
		if(isGooglePlay) {
			if(mHelper.getGamesClient().isConnected()){
				startActivityForResult(mHelper.getGamesClient().getAchievementsIntent(), 5001);
			}else{
				Toast.makeText(FlyGuy.this, R.string.SIGN_IN, Toast.LENGTH_LONG).show();
			}	
		}	
	}
	
	public void leaderBoardController(JSONObject prms){
		if(isGooglePlay) {
			if(mHelper.getGamesClient().isConnected()){
				startActivityForResult(mHelper.getGamesClient().getAllLeaderboardsIntent(), 5001);
			}else{
				beginUserInitiatedSignIn(null);
				Toast.makeText(FlyGuy.this, R.string.SIGN_IN, Toast.LENGTH_LONG).show();
			}	
		}
	}
}
