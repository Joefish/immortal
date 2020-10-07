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
#include "immortal/logic.h"
#include "immortal/resman.h"
#include "immortal/sound.h"


namespace Immortal {

ImmortalEngine::ImmortalEngine(OSystem *syst, const ADGameDescription *gameDesc)
    : Engine(syst)
    , _gameDescription(gameDesc)
    , _resMan(nullptr)
    , _midiPlayer(nullptr)
    , _screen(nullptr)
    , _console(nullptr)
    , _logic(nullptr) {
	DebugMan.addDebugChannel(kDebugGeneral, "general", "Immortal general debug channel");
}

ImmortalEngine::~ImmortalEngine() {
	DebugMan.clearAllDebugChannels();

	delete _logic;
	delete _screen;
	delete _midiPlayer;
	delete _console;
	delete _resMan;
}


Common::Error ImmortalEngine::run() {
	initGraphics(320, 200);

	_resMan = new ResourceManager();
	_midiPlayer = new MusicPlayer(_resMan);
	_screen = new Renderer(_resMan);
	_console = new Console(this);
	_logic = new Logic(this);

	_logic->init();

	while (!shouldQuit()) {
		int64 loopStart = g_system->getMillis();
		_logic->update();
		_screen->update();

		int64 loopEnd = 16 - (g_system->getMillis() - loopStart);
		if (loopEnd > 0)
			g_system->delayMillis(loopEnd);
	}

	return Common::kNoError;
}

bool ImmortalEngine::hasFeature(EngineFeature f) const {
    return false;
}

}
