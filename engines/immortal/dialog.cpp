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

namespace Immortal {

// TODO:
// Change Intro string depending on game version
// Substitute \x27 with '\''
static const char *dialogText[kDialogNum] = {
	// kDialogIntro
	"\\   Electronic Arts presents&&       The Immortal&&&&      1991 Will Harvey|]]]]]]]]\\]="
	"          written by&&         Will Harvey&         Ian Gooding&      Michael Marcantel&       Brett G. Durrett&        Douglas Fulton|]]]]]]]/="
#if 0
	"&&      Amiga version by&&       Brett G. Durrett&]]]]]]]="
	"&&       Atari version by&&      Brett G. Durrett&]]]]]]]="
#endif
	"&&       IBM version by&&      Kenneth L. Hurley&|]]]]]]]=",
	// kDialogNewGame
	"New game?%"
};

const Common::Point Dialog::_cursorOrigin(40, 24);
// button pos relative to viewport
const Common::Point Dialog::_buttonNo(40 - 32, 100 - 12);
const Common::Point Dialog::_buttonYes(214 - 32, 100 - 12);
const int Dialog::_maxRows = 5;
const int Dialog::_charGaugeOff = 1;
const int Dialog::_charGaugeOn = 2;
const int Dialog::_charCopyright = 24;
const int Dialog::_charTrademark = 25;
const int Dialog::_charBlank = 26;
const int Dialog::_delay = 100;

Dialog::Dialog() {
	reset();
}

void Dialog::load(DialogId id) {
	reset();
	_text = dialogText[id];
}

void Dialog::reset() {
	_cursorPos = _cursorOrigin;
	_text = nullptr;
	_timeSinceLastUpdate = 0;
}

/**
 * TODO:
 * Add pre/post render offset table for lower ASCII chars
 * Is position even needed or should the renderer know about Dialog layouts and depending on the type
 * advance the animation during update? Probably not. Instead, confine the Renderer to rendering and store
 * as little non-render state as possible.
 * At what x value is it necessary to line break the text? -- Scan word length and check if it fits
 * The following are tokens for render behavior that should better be handled in the logic
 * 		=	end of string, fade in if TEXTFADEIN
 * 		@	end of string, wait for OKAY and fade in if TEXTFADEIN
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
 * 		[	page break with delay of 140
 * 		]	delay 40
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
DialogReturnCode Dialog::update() {
	switch (*_text) {
	case '=':
		break;
	case '@':
		break;
	case '*':
		break;
	case '&':
		break;
	case '^':
		break;
	case '#':
		break;
	case '%':
		break;
	case '+':
		break;
	case '_':
		break;
	case '~':
		break;
	case '{':
		break;
	case '}':
		break;
	case '[':
		break;
	case ']':
		break;
	case '$':
		break;
	case '(':
		break;
	case '<':
		break;
	case '>':
		break;
	case '|':
		break;
	case '\\':
		break;
	case '/':
		break;
	default:
		error("Encountered not supported token in Dialog text (%c)", *_text);
		break;
	}

	++_text;

	return kDialogRCNotFinished;
}

}
