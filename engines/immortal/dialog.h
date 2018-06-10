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
	kDialogIntro,
	kDialogNewGame,
	kDialogNum
};

enum DialogReturnCode {
	kDialogRCNotFinished,
	kDialogRCYes,
	kDialogRCNo,
	kDialogRCOk
};

class Dialog {
public:
	Dialog(Renderer *screen);
	void load(DialogId id);
	DialogReturnCode update();

private:
	void reset();
	void printChar(char c);
	void newline();

private:
	static const Common::Point _cursorOrigin;
	static const Common::Point _buttonYes;
	static const Common::Point _buttonNo;
	static const int _maxCharWidth;
	static const int _maxRows;
	static const int _rowHeight;
	static const int _rowWidthLimit;
	static const int _delay;
	static const int _charGaugeOff;
	static const int _charGaugeOn;
	static const int _charCopyright;
	static const int _charTrademark;
	static const int _charBlank;

	Renderer *_screen;
	const char *_text;
	Common::Point _cursorPos;
	Timer _timeSinceLastUpdate;
};

}

#endif
