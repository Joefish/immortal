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

static const Common::KeyCode KeyMap[] = {
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
	, _keyState() {
}

void Logic::init() {
	// TODO:
	// Parameters for loading savestates/new game/start from password/..
	// init rooms and gamestate
}

void Logic::update() {
	handleInput();
}

void Logic::handleInput() {
	Common::Event event;
	while (g_system->getEventManager()->pollEvent(event)) {
		switch (event.type) {
		case Common::EVENT_KEYDOWN:
			if (event.kbd.keycode == Common::KEYCODE_d &&
				(event.kbd.flags & Common::KBD_CTRL)) {
				_console->attach();
			}
			for (int i = 0; i < kKeyNum; ++i) {
				if (event.kbd.keycode == KeyMap[i])
					_keyState[i] = true;
			}
			break;
		case Common::EVENT_KEYUP:
			for (int i = 0; i < kKeyNum; ++i) {
				if (event.kbd.keycode == KeyMap[i])
					_keyState[i] = false;
			}
			break;
		default:
			break;
		}
	}
}

}
