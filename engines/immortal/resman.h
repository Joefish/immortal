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
#include "graphics/surface.h"

namespace Immortal {

class ImmortalEngine;

enum AssetId {
	kAssetEGATitleScreen,
	kAssetVGATitleScreen,
	kAssetScreenBorder,
	kAssetInvalid
};

struct AssetFile {
	AssetFile()
		: _id(kAssetInvalid)
		, _filename()
		, _size(0)
		, _offset(0)
		, _data(nullptr) {
	}

	AssetId _id;
	char _filename[13];	// 8.3
	int _size;
	int _offset;
	Common::ScopedPtr<byte> _data;
};

class ResourceManager {
public:
	ResourceManager();
	Graphics::Surface *getImage(AssetId id);

private:
	void init();
	Common::Error loadLibrary(const char *filename);
	Common::Error convertImage(const AssetFile *assetFile);

private:
	Graphics::Surface _titleScreen;
	Graphics::Surface _screenBorder;

};

}

#endif
