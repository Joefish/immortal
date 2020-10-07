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

#ifndef IMMORTAL_IMMORTAL_H
#define IMMORTAL_IMMORTAL_H

#include "audio/mixer.h"
#include "common/error.h"
#include "common/platform.h"
#include "engines/engine.h"

struct ADGameDescription;

namespace Immortal {

class Console;
class ResourceManager;
class MusicPlayer;
class Renderer;
class Logic;

class ImmortalEngine : public Engine {
public:
	ImmortalEngine(OSystem *syst, const ADGameDescription *gameDesc);
	~ImmortalEngine();

	Common::Error run() override;
    bool hasFeature(EngineFeature f) const override;
    const char *getGameId() const;
    Common::Platform getPlatform() const;
    // bool canLoadGameStateCurrently() override { return true; }
    // bool canSaveGameStateCurrently() override { return true; }
    // Common::Error loadGameStream(Common::SeekableReadStream *stream) override;
    // Common::Error saveGameStream(Common::WriteStream *stream, bool isAutosave = false) override;
    // void syncGameStream(Common::Serializer &s);

public:
    const ADGameDescription *_gameDescription;

	ResourceManager *_resMan;
	MusicPlayer *_midiPlayer;
	Renderer *_screen;
	Console *_console;
	Logic *_logic;
	Audio::SoundHandle _soundHandle;
};

}

#endif
