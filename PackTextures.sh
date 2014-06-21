#!/bin/sh

TP="/Applications/TexturePacker.app/Contents/MacOS/TexturePacker"

#rm streetFighter/resources/chars/a_arnold_special_a.pvr.ccz
#rm streetFighter/resources/chars/a_arnold_special_a.plist

# ....
# add all files to be removed in clean phase
# ....
#create bg atlas

#....HD data......

${TP} --smart-update \
--format cocos2d \
--padding 0 \
--data FlyGuy/Resources/Sheets/HD/Backgrounds/bgTexture.plist \
--sheet FlyGuy/Resources/Sheets/HD/Backgrounds/bgTexture.png \
FlyGuy/Art/Images/HD/Backgrounds/*.png

${TP} --smart-update \
--format cocos2d \
--padding 2 \
--data  FlyGuy/Resources/Sheets/HD/ButtonsAndIcons/buttonTexture.plist \
--sheet  FlyGuy/Resources/Sheets/HD/ButtonsAndIcons/buttonTexture.png \
FlyGuy/Art/Images/HD/ButtonsAndIcons/*.png

${TP} --smart-update \
--format cocos2d \
--padding 2 \
--data  FlyGuy/Resources/Sheets/HD/Character/character.plist \
--sheet  FlyGuy/Resources/Sheets/HD/Character/character.png \
FlyGuy/Art/Images/HD/Character/*.png

${TP} --smart-update \
--format cocos2d \
--padding 2 \
--data  FlyGuy/Resources/Sheets/HD/LowerCave\(WithGrass\)/parallax_bg_grassDown.plist \
--sheet  FlyGuy/Resources/Sheets/HD/LowerCave\(WithGrass\)/parallax_bg_grassDown.png \
FlyGuy/Art/Images/HD/LowerCave\(WithGrass\)/*.png


${TP} --smart-update \
--format cocos2d \
--padding 2 \
--data  FlyGuy/Resources/Sheets/HD/LowerCave\(WithoutGrass\)/parallax_bg_withoutGrassDown.plist \
--sheet FlyGuy/Resources/Sheets/HD/LowerCave\(WithoutGrass\)/parallax_bg_withoutGrassDown.png \
FlyGuy/Art/Images/HD/LowerCave\(WithoutGrass\)/*.png


${TP} --smart-update \
--format cocos2d \
--padding 2 \
--data  FlyGuy/Resources/Sheets/HD/UpperCave\(WithGrass\)/parallax_bg_grassUp.plist \
--sheet FlyGuy/Resources/Sheets/HD/UpperCave\(WithGrass\)/parallax_bg_grassUp.png \
FlyGuy/Art/Images/HD/UpperCave\(WithGrass\)/*.png

${TP} --smart-update \
--format cocos2d \
--padding 2 \
--data  FlyGuy/Resources/Sheets/HD/UpperCave\(WithoutGrass\)/parallax_bg_withoutGrassUp.plist \
--sheet FlyGuy/Resources/Sheets/HD/UpperCave\(WithoutGrass\)/parallax_bg_withoutGrassUp.png \
FlyGuy/Art/Images/HD/UpperCave\(WithoutGrass\)/*.png


#....Normal data......
${TP} --smart-update \
--format cocos2d \
--padding 0 \
--data  FlyGuy/Resources/Sheets/Normal/Backgrounds/bgTexture.plist \
--sheet  FlyGuy/Resources/Sheets/Normal/Backgrounds/bgTexture.png \
FlyGuy/Art/Images/Normal/Backgrounds/*.png

${TP} --smart-update \
--format cocos2d \
--padding 2 \
--data  FlyGuy/Resources/Sheets/Normal/ButtonsAndIcons/buttonTexture.plist \
--sheet FlyGuy/Resources/Sheets/Normal/ButtonsAndIcons/buttonTexture.png \
FlyGuy/Art/Images/Normal/ButtonsAndIcons/*.png


${TP} --smart-update \
--format cocos2d \
--padding 2 \
--data  FlyGuy/Resources/Sheets/Normal/Caves/parallax_bg.plist \
--sheet  FlyGuy/Resources/Sheets/Normal/Caves/parallax_bg.png \
FlyGuy/Art/Images/Normal/Caves/*.png


${TP} --smart-update \
--format cocos2d \
--padding 2 \
--data FlyGuy/Resources/Sheets/Normal/Character/character.plist \
--sheet FlyGuy/Resources/Sheets/Normal/Character/character.png \
FlyGuy/Art/Images/Normal/Character/*.png
# ....
# add other sheets to create here
# ....
exit 0