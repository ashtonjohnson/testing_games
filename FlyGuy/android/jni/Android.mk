LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/GameLayer.cpp \
                   ../../Classes/Utility.cpp \
                   ../../Classes/RandomParallaxBg.cpp \
                   ../../Classes/Character.cpp \
                   ../../Classes/Obstacle.cpp \
                   ../../Classes/CMAnimation.cpp \
                   ../../Classes/GLES-Render.cpp \
                   ../../Classes/GB2ShapeCache-x.cpp \
                   ../../Classes/UserData.cpp \
                   ../../Classes/MyContactListener.cpp \
                   ../../Classes/LevelCompletionScene.cpp \
                   ../../Classes/MainMenuScene.cpp \
                   ../../Classes/HUDLayer.cpp \
                   ../../Classes/VinnyGreenCharacter.cpp \
                   ../../Classes/BellaRedCharater.cpp \
                   ../../Classes/JohnyOrangeCharacter.cpp \
                   ../../Classes/NormanBlueCharacter.cpp \
                   ../../Classes/TinyMode.cpp \
                   ../../Classes/BubbleShield.cpp \
                   ../../Classes/SpeedBurst.cpp \
                   ../../Classes/SuperRocket.cpp \
                   ../../Classes/PowerUps.cpp \
                   ../../Classes/Coins.cpp \
                   ../../Classes/ObstaclePattern.cpp \
                   ../../Classes/CoinsPattern.cpp \
                   ../../Classes/Extras.cpp \
                   ../../Classes/MainMenuLayer.cpp \
                   ../../Classes/ObjectiveScene.cpp \
                   ../../Classes/ObjectiveLayer.cpp \
                   ../../Classes/FGScrollView.cpp \
                   ../../Classes/ContinueLayer.cpp \
                   ../../Classes/UpgradeScene.cpp \
                   ../../Classes/UpgradeLayer.cpp \
                   ../../Classes/AboutScene.cpp \
                   ../../Classes/AboutLayer.cpp \
                   ../../Classes/PauseLayer.cpp \
                   ../../Classes/GameOverLayer.cpp \
                   ../../Classes/ScoresScene.cpp \
                   ../../Classes/ScoresLayer.cpp \
                   ../../Classes/Star.cpp \
                   ../../andndk/jansson/dump.c \
                   ../../andndk/jansson/error.c \
                   ../../andndk/jansson/hashtable.c \
                   ../../andndk/jansson/load.c \
                   ../../andndk/jansson/memory.c \
                   ../../andndk/jansson/pack_unpack.c \
                   ../../andndk/jansson/strbuffer.c \
                   ../../andndk/jansson/strconv.c \
                   ../../andndk/jansson/utf.c \
                   ../../andndk/jansson/value.c \
                   ../../andndk/NDKHelper/NDKCallbackNode.cpp \
                   ../../andndk/NDKHelper/NDKHelper.cpp 
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../libs/extensions/GUI/CCEditBox\
					$(LOCAL_PATH)/../../libs/external/Box2d
					

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static box2d_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions) $(call import-module,external/Box2D) \
$(call import-module,extensions)
