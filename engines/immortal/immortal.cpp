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

#include "audio/mixer.h"
#include "common/debug.h"
#include "common/debug-channels.h"
#include "common/error.h"
#include "common/events.h"
#include "common/system.h"
#include "engines/util.h"
#include "graphics/palette.h"
#include "graphics/surface.h"

#include "immortal/console.h"
#include "immortal/immortal.h"
#include "immortal/resman.h"
#include "immortal/sound.h"


namespace Immortal {

ImmortalEngine::ImmortalEngine(OSystem *syst)
	: Engine(syst) {
	DebugMan.addDebugChannel(kDebugGeneral, "general", "Immortal general debug channel");
}

ImmortalEngine::~ImmortalEngine() {
	DebugMan.clearAllDebugChannels();

	delete _console;
	delete _resMan;
}

void ImmortalEngine::updateEvents() {
	Common::Event event;
	while (_system->getEventManager()->pollEvent(event)) {
		switch (event.type) {
		case Common::EVENT_KEYDOWN:
			if (event.kbd.keycode == Common::KEYCODE_d &&
				(event.kbd.flags & Common::KBD_CTRL)) {
				_console->attach();
			}
			break;
		default:
			break;
		}
	}
}

static const int titlePalette[16] = {
	0x0000,
	0x0007,
	0x0363,
	0x00AA,
	0x0A00,
	0x0999,
	0x090A,
	0x0CBB,
	0x0555,
	0x085F,
	0x0995,
	0x05FF,
	0x0F33,
	0x0B6F,
	0x0CC4,
	0x0FFF
};


Common::Error ImmortalEngine::run() {
	initGraphics(320, 200);
	byte convertedPalette[48] = {};
	for (int i = 0; i < 16; ++i) {
		int color = titlePalette[i];
		convertedPalette[i * 3 + 2] = ((color & 0xF)) * 17;
		convertedPalette[i * 3 + 1] = ((color & 0xF0) >> 4) * 17;
		convertedPalette[i * 3 + 0] = ((color & 0xF00) >> 8) * 17;
	}
	_system->getPaletteManager()->setPalette(convertedPalette, 0, 16);

	_console = new Console(this);
	_resMan = new ResourceManager();
	_midiPlayer = new MusicPlayer(_resMan);

	ImageData *image = _resMan->getImage(kImageTitleScreen);
	_midiPlayer->play(kMusicSleeping);

	while (!shouldQuit()) {
		uint32 start = _system->getMillis();
		updateEvents();
		_system->copyRectToScreen(image->_data, image->_width, 0, 0, image->_width, image->_height);
		_console->onFrame();
		_system->updateScreen();

		int end = 30 - (_system->getMillis() - start);
		if (end > 0)
			_system->delayMillis(end);
	}

	return Common::kNoError;
}

}
