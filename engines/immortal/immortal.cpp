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
#include "immortal/graphics.h"
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

Common::Error ImmortalEngine::run() {
	initGraphics(320, 200);

	_resMan = new ResourceManager();
	_console = new Console(this);
	_midiPlayer = new MusicPlayer(_resMan);
	_screen = new Renderer(_resMan);

	_midiPlayer->play(kMusicIntro);
	int anim1 = 0;
	int anim2 = 0;
	int anim3 = 0;
	while (!shouldQuit()) {
		uint32 start = _system->getMillis();

		updateEvents();
		_console->onFrame();
		_screen->draw(kImageScreenFrame);
		_screen->draw(kAnimationIconCoffee, 120, 40, &anim1);
		_screen->draw(kAnimationWizardDeathSonic, 60, 60, &anim2);
		_screen->draw(kAnimationWizardWalking, 180, 80, &anim3);
		_screen->update();

		int end = 200 - (_system->getMillis() - start);
		if (end > 0)
			_system->delayMillis(end);
	}

	return Common::kNoError;
}

}
