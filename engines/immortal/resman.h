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

#ifndef IMMORTAL_RESMAN_H
#define IMMORTAL_RESMAN_H

#include "common/array.h"
#include "common/error.h"
#include "common/ptr.h"

namespace Immortal {

class AssetFile;

enum MusicId {
	kMusic00,
	kMusic01,
	kMusicSleeping,
	kMusic03,
	kMusic04,
	kMusic05,
	kMusic06,
	kMusic07,
	kMusic08,
	kMusic09,
	kMusic10,
	kMusic11,
	kMusicLevelCompleted,
	kMusic13,
	kMusic14,
	kMusicBattle,
	kMusicDied,
	kMusic17,
	kMusic18,
	kMusicIntro,
	kMusic20,
	kMusicNum
};

enum ImageId {
	kImageTitleScreen,
	kImageScreenFrame,
	kImageNum
};

struct MusicData {
	byte *_data;
	int _size;
	bool _loop;
	byte _volume[16];
	byte _adlibToMidiChannelTable[9];
};

struct ImageData {
	byte *_data;
	int _size;
	int _width;
	int _height;
};

class ResourceManager {
struct AssetFile {
	char _name[13];
	int _size;
	int _offset;
	Common::ScopedPtr<byte> _data;
};

public:
	ResourceManager();
	ImageData *getImage(ImageId id);
	MusicData *getMusic(MusicId id);

private:
	void init();
	Common::Error loadLibrary(const char *filename);
	Common::Error convertImage(AssetFile *assetFile, ImageData *dest);
	Common::Error convertMusic(AssetFile *assetFile, MusicData *dest);

private:
	Common::Array<ImageData> _imageContainer;
	MusicData _musicContainer[kMusicNum];
	ImageData _titleScreen;
};

}

#endif
