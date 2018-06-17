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

#include "common/system.h"

#include "immortal/dialog.h"
#include "immortal/graphics.h"

namespace Immortal {

// TODO:
// Change Intro string depending on game version
// Substitute \x27 with '\''
// Substitute placeholder with int (see kDialogKoorsString)
static const char *dialogText[kDialogNum] = {
	// kDialogIntro
	"\\   Electronic Arts presents&&       The Immortal\x19&&&&     \x18 1991 Will Harvey|]]]]]]]]\\]="
	"          written by&&         Will Harvey&         Ian Gooding&      Michael Marcantel&       Brett G. Durrett&        Douglas Fulton|]]]]]]]/="
#if 0
	"&&      Amiga version by&&       Brett G. Durrett&]]]]]]]="
	"&&       Atari version by&&      Brett G. Durrett&]]]]]]]="
#endif
	"&&       IBM version by&&      Kenneth L. Hurley&|]]]]]]]=",
	// kDialogNewGame
	"New game?%",
	// kDialogPartyString
	"Ken Hurley and Rick &Rutkowski want you to &have this silver bullet.@",
	// kDialogKoorsString
//	"#", kAnimationKoorsLight, "  beer@",
	// kDialogBeerManString
	"You feel invinicible now.@",
	// kDialogKoorsOpen
	"It's 8 am! &Shotgun the beer?%",
	// kDialogMerchantDescription
	"_}Greetings, friend! Come, I+ve got something you need. These parts are plagued with slime. You can+t venture safely without my slime oil for boots, a bargain at only 80 gold pieces.%",
	// kDialogMerchant3Description
	"_}All right, 60 gold pieces for my oil. Rub it on your boots and slime won+t touch you. 60, friend.%",
	// kDialogMapText1
	"This room isn+t on the map.&Look at the picture.@",
	// kDialogMapText2
	"This room is on the map.&Look at the picture.@",
	// kDialogSwordString
//	"#", kAnimationIconSword, " sword@",
	// kDialogSwordDescription
	"You find an Elven sword of&combat agility. Take it?@",
	// kDialogBonesText1
	"Search the bones?%",
	// kDialogBonesText2
	"}The sword increases your quickness permanently.@",
	// kDialogBonesText3
	"}You notice something that looks wet and green under the pile. Search further?%",
	// kDialogDustOfComplaisanceString
//	"#', kAnimationIconBait,'  dust@",
	// kDialogDustOfComplaisanceDescription
	"}You find a bag containing Dust of Complaisance.&@",
	// kDialogOpenBag
	"}Drop the bait on the ground here?%",
	// kDialogThrowDustOfComplaisance
	"}To use this dust, you throw it in the air. Do that here?%",
	// kDialogSmithText1
	"_}Don+t bother me, I+m cutting a gem. Yes, you need it. No, you can+t have it. I wouldn+t give this gem to anyone, least of all you. Go away.]]]]=",
	// kDialogSmithText2
	"_}Let me help you. Take this gem. There you go. Good luck.]]]]=",
	// kDialogCarpetString
//	"#', kAnimationIconCarpet,'carpet@",
	// kDialogBombString
//	"#', kAnimationIconBomb,' bomb@",
	// kDialogBombDesc
	"A gas bomb that goblins&use to paralyze trolls.&@",
	// kDialogPickItUp
	"Take it?<>@",
	// kDialogYesNoString
	"%",
	// kDialogOtherString
	" other@",
	// kDialogChestKeyString
//	"#', kAnimationIconKey,'  key@",
	// kDialogChestKeyDescription
	"A key to a chest.&@",
	// kDialogOpenChestDescription
	"The chest is open. Examine&contents?%",
	// kDialogPutItOn
	"Put it on?%",
	// kDialogDropItThen
	"Drop it?%",
	// kDialogChestDescription
	"It+s unlocked. Open it?%",
	// kDialogGoodChestDescription
	"It+s locked but you have&the key. Open it?%",
	// kDialogBadChestDescription, kDialogCantUnlockDoor
	"It+s locked and you don+t&have the key.@",
	// kDialogGoldString
//	"#', kAnimationIconMoneybag,'$0 gold@",
	// kDialogFindGoldString
//	"You find $0 gold pieces.&&^#', kAnimationIconGold,'@",
	// kDialogNullString
	"@",
	// kDialogNotHere
	"You can+t plant them on&stone tiles.@",
	// kDialogUnlockDoor
	"It+s locked but you are&able to unlock it with&the key.@",
	// kDialogWeak1String
	"_}The king is not dead, but the poison is taking effect. When he sees you, he utters (Give me water... the fountain... I give you... information... peace...+ Give him water?%",
	// kDialogDummyWater
	"_}You dont have any water to give him. He mumbles something. Then silence... You find a key on his body.]]]]=",
	// kDialogBadWizard
	"_}He mumbles something. Then silence... You find a key on his body.]]]]=",
	// kDialogDiesAnyway
	"_}I+ll tell you how to... next level... just beyond slime... three jewels... slime... rock becomes... floor... right, left, center of the... [Then silence. His hand opens, releasing a key.]]]]=",
	// kDialogDoorKeyDescription
	"You find a door key.&@",
	// kDialogNoteDescription
	"You find a note.&@",
	// kDialogNoteString
//	"#', kAnimationIconLetter,'  note@",
	// kDialogLootBodyDescription
	"He+s dead.&Look for possessions?%",
	// kDialogNotEnough
	"You don+t have it. Check&your inventory.@",
	// kDialogGameOverString
	"Game Over&&Play again?@",
	// kDialogYouWin
	"Congratulations!&&Play again?@",
	// kDialogWormFoodDescription
	"You find a bag of bait.&@",
	// kDialogWormFoodString
//	"#', kAnimationIconBait,'   bait@",
	// kDialogStoneDescription
	"You find a stone. @",
	// kDialogStoneString
//	"#', kAnimationIconStone,' stone@",
	// kDialogGemDescription
	"You find a red gem.&@",
	// kDialogGemString
//	"#', kAnimationIconRuby,'  gem@",
	// kDialogFireballDescription
	"You find a book with&fireball spells.&@",
	// kDialogFireballString
//	"#', kAnimationIconScroll,'$ shots@",
	// kDialogDeathMapDescription
	"You find a map warning&you about pit traps.&@",
	// kDialogDeathMapString
//	"#', kAnimationIconMap,'  map@",
	// kDialogBootsString
//	"#',VASEBIGFRAME,'   oil@",
	// kDialogUseBootString
	"You try it out but notice&as you walk that the leather&is quickly drying out.@",
	// kDialogCharmDescription
	"}You find a scroll with a charm spell to use on will o+ the wisps.&@",
	// kDialogCharmString
//	"#', kAnimationIconScroll,' charm@",
	// kDialogUseCharmString
	"}This charms the will o+ the wisps to follow you. Read the spell again to turn them against your enemies.@",
	// kDialogWaterOpen
	"}It looks like water. Drink it?%",
	// kDialogDrinkIt
	"Drink it?%",
	// kDialogItWorks
	"}It works! You are much stronger.]]]=",
	// kDialogSbOpen
	"}It looks like it has green stuff inside. Open it?%",
	// kDialogUsesFireString
	"Okay, now this will take&effect when you press the&fire button.@",
	// kDialogMuscleDescription
	"You find a potion,&Magic Muscle.&@",
	// kDialogMuscleString
//	"#',VASEBIGFRAME,'  potion@",
	// kDialogSbDescription
	"You find a bottle.&@",
	// kDialogSbString
//	"#',VASEBIGFRAME,'  bottle@",
	// kDialogFaceString
//	"#', kAnimationIconRing,'protean@",
	// kDialogFaceDescription
	"You find a Protean Ring.&@",
	// kDialogTrndescription
	"You find a troll ritual knife,&used to declare a fight to&the death. @",
	// kDialogTrnString
//	"#', kAnimationIconDagger,' knife@",
	// kDialogInvisDescription
	"_}It is a fine woman+s garment. Folded inside is a ring with the words,[`To Ana, so harm will never find you. Love, Dunric.+ @",
	// kDialogGoodLuckDescription
	"You find a small, well&crafted ring. @",
	// kDialogAnaRingString
//	"#', kAnimationIconRing,'from ana@",
	// kDialogInvisString
//	"#', kAnimationIconRing,'  ana+s@",
	// kDialogGoesAway
	"_}She is hurt and upset when she finds you don+t have her ring or won+t give it to her. She scurries back into the hole. The hole is too small for you to follow.&@",
	// kDialogGiveHerRing
	"_}`Oh sir, can you help me,+ the girl pleads. `I was kidnapped and dragged down here. All the man would say is `Mordamir+s orders.+ I ~',GIVE",
	// kDialogGive2
	"escaped using a ring my father gave me, but now I+ve lost it. Did you find it?+%",
	// kDialogMadKingText
	"_}We have met before, old man. Do you remember? Because you helped me, you may pass. But I warn you, we are at war with the trolls. Over this ladder, across the spikes, is troll territory.@",
	// kDialogMadKing2Text
	"_}You are an impostor!]]]]=",
	// kDialogMadKing3Text
	"_}Old man, do you remember me? I am king of the goblins. You didn+t give me the water. You left me to die after you took the key from me. Now you will pay.]]]]=",
	// kDialogDream1
	"_}Ah, a rest is exactly what you need right now. You quickly fall into a deep, dream filled sleep...[Vivid images of a beautiful enchanted city pass by. All the city people are young. There are ~',DREAM1p",
	// kDialogDream1P2
	"fountains all around, water everywhere. A huge wall surrounds the city, sealing it from the outside world...[Suddenly the images go black. A face appears... Mordamir!]][ ~',DREAM1P",
	// kDialogDream1P3
	"He is different from how you remember him. His gentle features are now withered. His kind eyes, now cold and sunken, seem to look through you with a dark, penetrating stare. You wake rejuvenated, but disturbed.]]]]]=",
	// kDialogHowToGetOut
	"_}Here, take this ring in return. [I overheard the obnoxious little dwarf saying (Clockwise, three rings around the triangle.+ Could that be a clue to his exit puzzle? [I must go. Goodbye.]]]]=",
	// kDialogRestartString
	"Start over?%",
	// kDialogSporesString
//	"#', kAnimationIconSporesBag,' spores@",
	// kDialogSporesDescription
	"You find a sack of bad&smelling spores.&@",
	// kDialogRequestPlayDisk
	"Please insert play disk.@",
	// kDialogOldGameString
	"New game?%",
	// kDialogEnterCertificate
	"Enter certificate:&-=",
	// kDialogBadCertificate
	"Invalid certificate.@",
	// kDialogCertificateString
	"End of level!&Here is your certificate:&&=",
	// kDialogCertificate2String
	"&@",
	// kDialogExitString
	" Are you sure you & want to exit Immortal?%",
	// kDialogCertCheckString0
	"Look in your manual for this&picture. Type the =",
	// kDialogCertCheckString1
	"first&letter on row =",
	// kDialogCertCheckString2
	"second&letter on row =",
	// kDialogCertCheckFirst
	"fourth&letter on row =",
	// kDialogCertCheckSecond
	"sixth&letter on row =",
	// kDialogCertCheckFourth
	", below.&&=",
	// kDialogCertCheckSixth
	"No, that+s not it.&One more try.]]]]="
};

const Common::Point Dialog::_cursorOrigin(40, 24);
// TODO:
// button pos relative to viewport. Look close at source what's going on here..
const Common::Point Dialog::_buttonNo(40 - 32, 100 - 12);
const Common::Point Dialog::_buttonYes(214 - 32, 100 - 12);
const int Dialog::_iconWidth = 64;
const int Dialog::_iconHeight = 48;
const int Dialog::_maxCharWidth = 16;
const int Dialog::_rowHeight = 16;
const int Dialog::_rowWidthLimit = 288; // 256 px viewport + 32 px border
const int Dialog::_maxRows = 5;
const int Dialog::_charGaugeOff = 1;
const int Dialog::_charGaugeOn = 2;
const int Dialog::_charCopyright = 24;
const int Dialog::_charTrademark = 25;
const int Dialog::_charBlank = 26;
const int Dialog::_scrollingDelay = 100;
const int Dialog::_delayInMs = (1 / 72.8) * 1000;

Dialog::Dialog(Renderer *screen)
	: _screen(screen) {
	reset();
}

void Dialog::load(DialogId id) {
	reset();
	_text = dialogText[id];
	_timeSinceLastUpdate.start();
}

void Dialog::reset() {
	_cursorPos = _cursorOrigin;
	_text = nullptr;
	_timeSinceLastUpdate.stop();
	_scrollingMode = false;
}

int Dialog::getDelay() const {
	return _delay;
}

void Dialog::nextChar() {
	assert(*_text != '\0');
	++_text;
	_delay = 0;
}

/**
 * TODO:
 * Add pre/post render offset table for lower ASCII chars
 * Is position even needed or should the renderer know about Dialog layouts and depending on the type
 * advance the animation during update? Probably not. Instead, confine the Renderer to rendering and store
 * as little non-render state as possible.
 * At what x value is it necessary to line break the text? -- Scan word length and check if it fits
 * Difference between fast and slow scroll?
 * The following are tokens for render behavior that should better be handled in the logic
 * 		=	end of string
 * 		@	end of string, wait for OKAY
 * 		*n	wait for n cycles, then clear screen
 * 		&	line break
 * 		^	center penx
 * 		#n	draw icon number n
 * 		%	end of string, return yes/no
 * 		+	apostrophy
 * 		_	print the string in slow text
 * 		~n	continue printing string ID n
 * 		{n	wait for n cycles
 * 		}	do automatic line and page breaks
 * 		[	page break with delay of 490ms
 * 		]	delay 140ms
 * 		$	print the number passed to text_print in ACC
 * 		(	backquote
 * 		<	fast text
 * 		>	no format
 * 		|	do fadein
 *		\	fadeout
 *		/	slow fadeout
 *
 * @brief Dialog::update iterates over the dialog text one char at a time
 * @return kDialogRCNotFinished if there are still chars left to print.
 * 		   kDialogRCYes/No/Ok represent what button was selected.
 * 		   For dialog without buttons we just return Ok as well.
 */
DialogToken Dialog::update(bool keyPressed) {
	switch (*_text) {
	case kDialogTokenEndOfString:
		_screen->clear();
		_cursorPos = _cursorOrigin;
		return kDialogTokenDelay;

	case kDialogTokenDelay40:
		_delay = 40 * _delayInMs;
		return kDialogTokenDelay;

	case kDialogTokenDelayAndPageBreak:
		_delay = 140 * _delayInMs;
		return kDialogTokenDelay;

	case kDialogTokenDelay:
		_delay = 0;
		++_text;
		while (Common::isDigit(*_text)) {
			_delay = _delay * 10 + (*_text - '0');
			++_text;
		}
		--_text;
		_delay *= _delayInMs;
		return kDialogTokenDelay;

	case kDialogTokenDelayAndClear:
		// parse number after token
		break;

	case kDialogTokenEndOfStringOk:
	case kDialogTokenEndOfStringYesNo:
	case kDialogTokenLoadNextString:
		return (DialogToken)*_text;

	case kDialogTokenSlowScroll:
		_scrollingMode = true;
		break;

	case kDialogTokenFastScroll:
		_scrollingMode = true;
		break;

	case kDialogTokenFadeIn:
		_screen->paletteFadeIn();
		break;

	case kDialogTokenFadeOut:
		_screen->paletteFadeOut();
		break;

	case kDialogTokenSlowFadeOut:
		_screen->paletteSlowFadeOut();
		break;

	case kDialogTokenLineBreak:
		newline();
		break;

	case kDialogTokenDrawIcon:
		break;

	case kDialogTokenPrintNumber:
		break;

	case kDialogTokenNoFormat:
		break;

	case kDialogTokenApostrophy:
		printText();
		break;

	case kDialogTokenBackquote:
		printText();
		break;

	case kDialogTokenCenterCursorX:
		_cursorPos.x = _screen->_frameWidth +
					   ((_screen->_viewportWidth / 2) - (_iconWidth / 2));
		break;

	case kDialogTokenAutoLineAndPageBreaks:
		break;

	default:
		printText();
		break;
	}

	++_text;
	_timeSinceLastUpdate.reset();

	return (DialogToken)*_text;
}

void Dialog::printText() {
	// TODO:
	// Advance to next line if word does not fit in row (test row limit to be sure)
	// Current linebreak is just a workaround
	// If dialog not in scrolling mode, render whole page instead of single char
	// return if *_text is a token
	if (_cursorPos.x + _maxCharWidth > _rowWidthLimit)
		newline();

	switch (*_text) {
	case ' ':
		_cursorPos.x += 8;
		return;
	case '\'':
		_cursorPos.x -= 2;
		break;
	case 'm':
	case 'M':
	case 'w':
	case 'W':
		_cursorPos.x += 8;
		break;
	case 'i':
	case 'l':
		_cursorPos.x -= 4;
		break;
	case 'j':
	case 't':
		_cursorPos.x -= 2;
		break;
	}
	if (Common::isUpper(*_text))
		_cursorPos.x += 8;

	_screen->drawSprite(kAnimationSymbols, *_text, _cursorPos.x, _cursorPos.y);

	switch (*_text) {
	case '\'':
	case 'T':
		_cursorPos.x += 6;
		break;
	default:
		_cursorPos.x += 8;
		break;
	}
}

void Dialog::newline() {
	_cursorPos.x = _cursorOrigin.x;
	_cursorPos.y += 16;
}

}
