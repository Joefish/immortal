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

#ifndef IMMORTAL_SCREEN_H
#define IMMORTAL_SCREEN_H

#include "graphics/surface.h"

#include "immortal/resman.h"

namespace Immortal {

class Renderer {
private:
	enum PaletteId {
		kPaletteInvalid,
		kPaletteDefault,
		kPaletteTitle,
		kPaletteFade
	};

	enum PaletteFadeType {
		kPaletteFadeIn,
		kPaletteFadeOut,
		kPaletteFadeSlowOut
	};

public:
	Renderer(ResourceManager *resMan);
	void drawChar(char c, int x, int y);
	void drawImage(ImageId id);
	void drawSprite(SpriteId id, int x, int y, int offset = 0);
	void drawMap(int x, int y);
	void paletteFadeIn();
	void paletteFadeOut();
	void paletteSlowFadeOut();
	void clear();
	void update();

public:
	static const int _screenWidth;
	static const int _screenHeight;
	static const int _viewportWidth;
	static const int _viewportHeight;
	static const int _viewportPosX;
	static const int _viewportPosY;
	static const int _frameWidth;
	static const int _frameHeight;

private:
	static void convertPaletteToRGB(int palColor, byte *red, byte *green, byte *blue);
	void loadPalette(PaletteId id);
	void generateCurrentMapView(int mapX, int mapY, const Map *map);
	void drawMap(const byte bitmap[Map::_numStamps][Map::_stampStride]);
	void internalDrawImage(ImageId id);
	void internalDrawSprite(const Sprite *sprite, int x, int y, int centerX, int centerY);
	void internalPaletteFade(PaletteFadeType type);

	ResourceManager *_resMan;
	Graphics::Surface _backBuffer;
	PaletteId _currentPalette;
	uint16 _currentMap[Map::_stampsPerViewportH][Map::_stampsPerViewportW];
};

}

#endif
