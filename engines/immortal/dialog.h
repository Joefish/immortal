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

#include "immortal/resman.h"
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
	kDialogDreamXXY,
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
	kDialogAmuletDescription,
	kDialogAmuletString,
	kDialogHoldItUp,
	kDialogReadRunes,
	kDialogMordamirString1,
	kDialogMordamirString2,
	kDialogMordamir3D,
	kDialogMordamir3,
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
private:
	struct DialogData {
		DialogData()
		    : _text(nullptr)
		    , _iconId(kSpriteNone)
		    , _nextPage(kDialogNone) {
		}

		DialogData(const char *text, SpriteId iconId = kSpriteNone,
		           DialogId nextPage = kDialogNone)
		    : _text(text)
		    , _iconId(iconId)
		    , _nextPage(nextPage) {
		}

		const char *_text;
		SpriteId _iconId;
		DialogId _nextPage;
	};

public:
	Dialog(Renderer *screen);
	void load(DialogId id);
	DialogToken update(bool keyPressed);
	void nextChar();
	void printChar(int c);
	bool removeChar();
	int getDelay() const;
	DialogId getId() const;

private:
	void reset();
	void printText();
	void newline();
	void resetCursor();

public:
	// TODO:
	// button pos relative to viewport. Look close at source what's going on here..
	static const int _cursorOriginX = 40;
	static const int _cursorOriginY = 24;
	static const int _buttonYesX = 214 - 32;
	static const int _buttonYesY = 100 - 12;
	static const int _buttonNoX = 40 - 32;
	static const int _buttonNoY = 100 - 12;
	static const int _iconWidth = 64;
	static const int _iconHeight = 48;
	static const int _maxCharWidth = 16;
	static const int _rowHeight = 16;
	static const int _rowWidthLimit = 288;  // 256 px viewport + 32 px border
	static const int _maxRows = 5;
	static const int _charGaugeOff = 1;
	static const int _charGaugeOn = 2;
	static const int _charCopyright = 24;
	static const int _charTrademark = 25;
	static const int _charBlank = 26;
	static const int _scrollingDelay = 100;
	static const int _delayInMs = (1 / 72.8) * 1000;

private:
	Renderer *_screen;
	const char *_text;
	Common::Point _cursorPos;
	Timer _timeSinceLastUpdate;
	int _delay;
	bool _scrollingMode;
	DialogId _id;
	DialogData _dialog[kDialogNum];
	char _password[18];     // 16 char password + '-' + terminator
	int _passwordCharIndex;
};

}

#endif
