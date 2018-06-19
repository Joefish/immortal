/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef IMMORTAL_DIALOG_H
#define IMMORTAL_DIALOG_H

#include "common/rect.h"

#include "immortal/timer.h"

namespace Immortal {

class Renderer;

enum DialogId {
	kDialogNone = -1,
	kDialogIntro,
	kDialogNewGame,
	kDialogPartyString,
	kDialogKoorsString,
	kDialogBeerManString,
	kDialogKoorsOpen,
	kDialogMerchantDescription,
	kDialogMerchant3Description,
	kDialogMapText1,
	kDialogMapText2,
	kDialogSwordString,
	kDialogSwordDescription,
	kDialogBonesText1,
	kDialogBonesText2,
	kDialogBonesText3,
	kDialogDustOfComplaisanceString,
	kDialogDustOfComplaisanceDescription,
	kDialogOpenBag,
	kDialogThrowDustOfComplaisance,
	kDialogSmithText1,
	kDialogSmithText2,
	kDialogCarpetString,
	kDialogBombString,
	kDialogBombDesc,
	kDialogPickItUp,
	kDialogYesNoString,
	kDialogOtherString,
	kDialogChestKeyString,
	kDialogChestKeyDescription,
	kDialogOpenChestDescription,
	kDialogPutItOn,
	kDialogDropItThen,
	kDialogChestDescription,
	kDialogGoodChestDescription,
	kDialogBadChestDescription,
	kDialogCantUnlockDoor = kDialogBadChestDescription,
	kDialogGoldString,
	kDialogFindGoldString,
	kDialogNullString,
	kDialogNotHere,
	kDialogUnlockDoor,
	kDialogWeak1String,
	kDialogDummyWater,
	kDialogBadWizard,
	kDialogDiesAnyway,
	kDialogDoorKeyDescription,
	kDialogNoteDescription,
	kDialogNoteString,
	kDialogLootBodyDescription,
	kDialogNotEnough,
	kDialogGameOverString,
	kDialogYouWin,
	kDialogWormFoodDescription,
	kDialogWormFoodString,
	kDialogStoneDescription,
	kDialogStoneString,
	kDialogGemDescription,
	kDialogGemString,
	kDialogFireballDescription,
	kDialogFireballString,
	kDialogDeathMapDescription,
	kDialogDeathMapString,
	kDialogBootsString,
	kDialogUseBootString,
	kDialogCharmDescription,
	kDialogCharmString,
	kDialogUseCharmString,
	kDialogWaterOpen,
	kDialogDrinkIt,
	kDialogItWorks,
	kDialogSbOpen,
	kDialogUsesFireString,
	kDialogMuscleDescription,
	kDialogMuscleString,
	kDialogSbDescription,
	kDialogSbString,
	kDialogFaceString,
	kDialogFaceDescription,
	kDialogTrndescription,
	kDialogTrnString,
	kDialogInvisDescription,
	kDialogGoodLuckDescription,
	kDialogAnaRingString,
	kDialogInvisString,
	kDialogGoesAway,
	kDialogGiveHerRing,
	kDialogGive2,
	kDialogMadKingText,
	kDialogMadKing2Text,
	kDialogMadKing3Text,
	kDialogDream1P1,
	kDialogDream1P2,
	kDialogDream1P3,
	kDialogHowToGetOut,
	kDialogRestartString,
	kDialogSporesString,
	kDialogSporesDescription,
	kDialogRequestPlayDisk,
	kDialogOldGameString,
	kDialogEnterCertificate,
	kDialogBadCertificate,
	kDialogCertificateString,
	kDialogCertificate2String,
	kDialogExitString,
	kDialogCertCheckString0,
	kDialogCertCheckString1,
	kDialogCertCheckString2,
	kDialogCertCheckFirst,
	kDialogCertCheckSecond,
	kDialogCertCheckFourth,
	kDialogCertCheckSixth,
	kDialogDream1,
	kDialogD1D2,
	kDialogPhantDescription,
	kDialogWizardText2,
	kDialogWizardText3,
	kDialogDunricDescription,
	kDialogUlindorString0,
	kDialogUlindorString1,
	kDialogGuardNote,
	kDialogDunricRingDescription,
	kDialogDunricRingString,
	kDialogUlindorString2,
	kDialogUlindorString3,
	kDialogDreamLevel2,
	kDialogWarning,
	kDialogThrowTrn,
	kDialogThrowTrn2,
	kDialogDreamLevel3,
	kDialogCoffeeDescription,
	kDialogCoffeeString,
	kDialogGimmeCoffee,
	kDialogNoCoffee,
	kDialogRefuseCoffee,
	kDialogYesCoffee,
	kDialogDragNote,
	kDialogDream5,
	kDialogDream1P2X,
	kDialogDream1P3Y,
	kDialogGeigerDescription,
	kDialogGeigerDescription2,
	kDialogGeigerString,
	kDialogEggString,
	kDialogEggDescription,
	kDialogEggCracks,
	kDialogCrackEgg,
	kDialogEatEgg,
	kDialogGeigerWorks,
	kDialogFlameThrowDescription,
	kDialogFlameThrowString,
	kDialogMerchantXDescription,
	kDialogGoblinTalk,
	kDialogPlanTalk,
	kDialogPlan2,
	kDialogPlan3,
	kDialogPlan4,
	kDialogHasSpiders,
	kDialogPourHere,
	kDialogPourOnChest,
	kDialogAlcoholDescription,
	kDialogAlcoholString,
	kDialogLevitateDescription,
	kDialogLevitateString,
	kDialogDream6,
	kDialogDream7,
	kDialogDream1P2XW,
	kDialogDream1P2YW,
	kDialogdreamXXY,
	kDialogNotHere3,
	kDialogNotHere2,
	kDialogDownVortexString,
	kDialogDunricString7,
	kDialogDunricString8,
	kDialogGiveDunricRing,
	kDialogDunricTransaction,
	kDialogUlindorString7,
	kDialogNurseText,
	kDialogAntiString,
	kDialogBlinkDescription,
	kDialogBlinkString,
	kDialogTractorString,
	kDialogBronzeString,
	kDialogImmunityDescription,
	kDialogImmunityString,
	kDialogCoinDescription,
	kDialogCoinString,
	kDialogHoldItUp,
	kDialogReadRunes,
	kDialogMordamirString1,
	kDialogMordamirString2,
	kDialogMordamir3D,
	kDialogMoradamir3,
	kDialogMordamir4,
	kDialogMordamir5,
	kDialogGoodbye,
	kDialogEndText,
	kDialogEtXX,
	kDialogEt2,
	kDialogEndText2,
	kDialogEt2P,
	kDialogNum
};

enum DialogToken {
	kDialogTokenInvalid = -1,
	kDialogTokenStringTerminator = 0,
	kDialogTokenEndOfString = '=',
	kDialogTokenEndOfStringOk = '@',
	kDialogTokenEndOfStringYesNo = '%',
	kDialogTokenDelayAndClear = '*',
	kDialogTokenDelayAndPageBreak = '[',
	kDialogTokenSlowScroll = '_',
	kDialogTokenFastScroll = '<',
	kDialogTokenFadeIn = '|',
	kDialogTokenFadeOut = '\\',
	kDialogTokenSlowFadeOut = '/',
	kDialogTokenLineBreak = '&',
	kDialogTokenDrawIcon = '#',
	kDialogTokenLoadNextString = '~',
	kDialogTokenPrintNumber = '$',
	kDialogTokenNoFormat = '>',
	kDialogTokenApostrophy = '+',
	kDialogTokenBackquote = '(',
	kDialogTokenDelay = '{',
	kDialogTokenDelay40 = ']',
	kDialogTokenCenterCursorX = '^',
	kDialogTokenAutoLineAndPageBreaks = '}'
};

class Dialog {
public:
	Dialog(Renderer *screen);
	void load(DialogId id);
	DialogToken update(bool keyPressed);
	void nextChar();
	int getDelay() const;

private:
	void reset();
	void printText();
	void newline();

public:
	static const Common::Point _cursorOrigin;
	static const Common::Point _buttonYes;
	static const Common::Point _buttonNo;
	static const int _iconWidth;
	static const int _iconHeight;
	static const int _maxCharWidth;
	static const int _maxRows;
	static const int _rowHeight;
	static const int _rowWidthLimit;
	static const int _scrollingDelay;
	static const int _charGaugeOff;
	static const int _charGaugeOn;
	static const int _charCopyright;
	static const int _charTrademark;
	static const int _charBlank;
	static const int _delayInMs;

private:
	Renderer *_screen;
	const char *_text;
	Common::Point _cursorPos;
	Timer _timeSinceLastUpdate;
	int _delay;
	bool _scrollingMode;
};

}

#endif
