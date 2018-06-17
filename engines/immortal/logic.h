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

#ifndef IMMORTAL_LOGIC_H
#define IMMORTAL_LOGIC_H

#include "common/error.h"
#include "common/events.h"

#include "immortal/dialog.h"
#include "immortal/timer.h"

namespace Immortal {

class Console;
class ResourceManager;
class MusicPlayer;
class Renderer;
class ImmortalEngine;

enum KeyState {
	kKeyLeft,
	kKeyRight,
	kKeyUp,
	kKeyDown,
	kKeyAttack,
	kKeyStart,
	kKeyQuit,
	kKeyNum
};

enum LogicState {
	kLogicStartup,
	kLogicDialog,
	kLogicGame,
	kLogicPause
};

class Logic {
public:
	Logic(ImmortalEngine *vm);
	void init();
	void update();

private:
	void runStartup();
	void runDialog();
	void runGame();
	void runPause();

	void pollInput();
	void handleInput();
	bool isKeyPressed(KeyState key);
	void setState(LogicState state);
	void loadDialog(DialogId id);

private:
	Console *_console;
	ResourceManager *_resMan;
	MusicPlayer *_music;
	Renderer *_screen;

	Dialog _dialog;
	DialogToken _lastDialogToken;
	bool _buttonNoSelected;
	bool _buttonYesSelected;
	Timer _timer;
	LogicState _logicState;
	int64 _timeInit;
	bool _keyState[kKeyNum];
	// TODO: just temporary. Camera is centered on wizard (all the time?)
	Common::Point _cameraPos;
};

}

#endif
