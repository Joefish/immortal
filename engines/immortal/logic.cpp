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

#include "immortal/console.h"
#include "immortal/immortal.h"
#include "immortal/logic.h"
#include "immortal/graphics.h"
#include "immortal/sound.h"

namespace Immortal {

// TODO:
// Make keys remappable
static const Common::KeyCode keyMap[kKeyNum] = {
	Common::KEYCODE_LEFT,
	Common::KEYCODE_RIGHT,
	Common::KEYCODE_UP,
	Common::KEYCODE_DOWN,
	Common::KEYCODE_RSHIFT,
	Common::KEYCODE_RETURN,
	Common::KEYCODE_ESCAPE
};

Logic::Logic(ImmortalEngine *vm)
    : _console(vm->_console)
    , _resMan(vm->_resMan)
    , _music(vm->_midiPlayer)
    , _screen(vm->_screen)
    , _keyState()
    , _logicState(kLogicStartup)
    , _timeInit(vm->_system->getMillis())
    , _lastDialogToken(kDialogTokenInvalid)
    , _buttonNoSelected(true)
    , _buttonYesSelected(false)
    , _cameraPos(0, 0)
    , _dialog(vm->_screen) {
}

// TODO:
// Parameters for loading savestates/new game/..
// init rooms and gamestate
void Logic::init() {
}

void Logic::update() {
	pollInput();
	handleInput();

	switch (_logicState) {
	case kLogicStartup:
		runStartup();
		break;
	case kLogicDialog:
		runDialog();
		break;
	case kLogicGame:
		runGame();
		break;
	case kLogicPause:
		runPause();
		break;
	default:
		error("Game ended up in invalid state!");
		break;
	}
}

void Logic::pollInput() {
	Common::Event event;
	while (g_system->getEventManager()->pollEvent(event)) {
		switch (event.type) {
		case Common::EVENT_KEYDOWN:
			if (event.kbd.keycode == Common::KEYCODE_d &&
			    (event.kbd.flags & Common::KBD_CTRL)) {
				_console->attach();
			}
			for (int i = 0; i < kKeyNum; ++i) {
				if (event.kbd.keycode == keyMap[i])
					_keyState[i] = true;
			}
			if (Common::isAlnum(event.kbd.ascii) || event.kbd.keycode == Common::KEYCODE_BACKSPACE) {
				_keyInputBuffer.push_back(event.kbd.keycode);
			}
			break;
		case Common::EVENT_KEYUP:
			for (int i = 0; i < kKeyNum; ++i) {
				if (event.kbd.keycode == keyMap[i])
					_keyState[i] = false;
			}
			break;
		default:
			break;
		}
	}
}

void Logic::handleInput() {
	_keyStartAttackPressed = isKeyPressed(kKeyAttack) || isKeyPressed(kKeyStart);

	if (isKeyPressed(kKeyLeft)) {
		if (_cameraPos.x > 0)
			--_cameraPos.x;
	}
	if (isKeyPressed(kKeyRight)) {
		if (_cameraPos.x <= 159)
			++_cameraPos.x;
	}
	if (isKeyPressed(kKeyUp)) {
		if (_cameraPos.y > 0)
			--_cameraPos.y;
	}
	if (isKeyPressed(kKeyDown)) {
		if (_cameraPos.y <= 511)
			++_cameraPos.y;
	}
	if (isKeyPressed(kKeyAttack)) {
		_cameraPos.x = 0;
		_cameraPos.y = 0;
	}
	if (isKeyPressed(kKeyStart)) {

	}
	if (isKeyPressed(kKeyQuit)) {
		if (_logicState == kLogicGame) {
			loadDialog(kDialogExitString);
		}
	}
}

void Logic::runStartup() {
	_screen->drawImage(kImageTitleScreen);
	_timer.start();
	if (_timer.elapsedTime() > 3000 || _keyStartAttackPressed) {
		_timer.stop();
		loadDialog(kDialogIntro);
	}
}

void Logic::runDialog() {

	switch (_lastDialogToken) {
	case kDialogTokenDelay:
		_timer.start();
		if (_keyStartAttackPressed || _timer.elapsedTime() > _dialog.getDelay()) {
			_timer.stop();
			_dialog.nextChar();
			_lastDialogToken = kDialogTokenInvalid;
		}
		break;

	case kDialogTokenEndOfStringOk: {
		int buttonX = (_screen->_viewportWidth / 2) - (_screen->_iconWidth / 2);
		int buttonY = _dialog._buttonNoY;
		_screen->drawIcon(kSpriteButtonOk, buttonX, buttonY);

		if (_keyStartAttackPressed)
			setState(kLogicGame);
	} break;

	case kDialogTokenEndOfStringYesNo:
		handleDialogYesNo();
		break;

	case kDialogTokenLoadNextString:
		// TODO: Add support for 'follwoing string' in dialogText
		// Test with kDialogGiveHerRing
		break;

	case kDialogTokenStringTerminator:
		handleDialogEnd();
		break;

	default:
		_lastDialogToken = _dialog.update(_keyStartAttackPressed);
		break;
	}
}

void Logic::runGame() {
	_screen->clear();
	_screen->drawMap(_cameraPos.x, _cameraPos.y);
}

void Logic::runPause() {

}

void Logic::setState(LogicState state) {
	_logicState = state;
}

bool Logic::isKeyPressed(KeyState key) {
	return _keyState[key];
}

void Logic::loadDialog(DialogId id) {
	// TODO:
	// Different music for intro, sleep and default
	// Draw health meter as well
	_dialog.load(id);
	_screen->clear();
	_lastDialogToken = kDialogTokenInvalid;
	setState(kLogicDialog);

	if (id == kDialogIntro)
		_music->play(kMusicIntro);
}

bool Logic::loadFromPassword(Dialog *dialog) {
	return false;
}

void Logic::handleDialogYesNo() {
	if (isKeyPressed(kKeyLeft)) {
		_buttonNoSelected = true;
		_buttonYesSelected = false;
	}
	if (isKeyPressed(kKeyRight)) {
		_buttonNoSelected = false;
		_buttonYesSelected = true;
	}

	SpriteId buttonNo = _buttonNoSelected ? kSpriteButtonNoActive
	                                      : kSpriteButtonNoInactive;
	SpriteId buttonYes = _buttonYesSelected ? kSpriteButtonYesActive
	                                        : kSpriteButtonYesInactive;
	_screen->drawIcon(buttonNo, _dialog._buttonNoX, _dialog._buttonNoY);
	_screen->drawIcon(buttonYes, _dialog._buttonYesX, _dialog._buttonYesY);

	switch (_dialog.getId()) {
	case kDialogExitString:
		if (_keyStartAttackPressed) {
			if (_buttonYesSelected) {
				g_system->quit();
			} else if (_buttonNoSelected) {
				setState(kLogicGame);
			}
		}
		break;
	case kDialogNewGame:
		if (_keyStartAttackPressed) {
			if (_buttonYesSelected) {
				_level.loadLevel(1);
				setState(kLogicGame);
				_music->play(kMusic04);
			} else if (_buttonNoSelected) {
				loadDialog(kDialogEnterCertificate);
			}
		}
		break;
	default:
		break;
	}
}

void Logic::handleDialogEnd() {
	if (_dialog.getId() == kDialogEnterCertificate) {
		for (int *it = _keyInputBuffer.begin(); it < _keyInputBuffer.end(); ++it) {
			int key = *it;
			if (Common::isAlnum(key))
				_dialog.printChar(key);
			else if (key == Common::KEYCODE_BACKSPACE)
				_dialog.removeChar();
			else if (key == Common::KEYCODE_RETURN)
				loadFromPassword(&_dialog);
		}
		_keyInputBuffer.clear();

		if (isKeyPressed(kKeyQuit))
			loadDialog(kDialogNewGame);
	} else if (_dialog.getId() == kDialogIntro) {
		loadDialog(kDialogNewGame);
		_lastDialogToken = kDialogTokenInvalid;
	} else {
		_timer.start();
		if (_keyStartAttackPressed || _timer.elapsedTime() > 3000) {
			_timer.stop();
			_dialog.nextChar();
			_lastDialogToken = kDialogTokenInvalid;
		}
	}
}

}
