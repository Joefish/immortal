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
	void drawInventoryItem(const char *text, SpriteId spriteId, int parameter, int x, int y);
	void drawChar(char c);
	void drawImage(ImageId id);
	void drawSprite(SpriteId id, int x, int y, int offsetFrame = 0, int offsetPack = 0);
	void drawIcon(SpriteId id, int x, int y);
	void drawMap(int x, int y);
	void fillRect(int x1, int y1, int x2, int y2, int color);
	void paletteFadeIn();
	void paletteFadeOut();
	void paletteSlowFadeOut();
	void clear();
	void update();
	void cursorPosNewline();
	void cursorPosReset();
	void cursorPosCenter();
	void cursorClearLine();
	Common::Point getCursorPos() const;
	void setCursorPos(int x, int y);

private:
	static void convertPaletteToRGB(int palColor, byte *red, byte *green, byte *blue);

	void loadPalette(PaletteId id);
	void generateCurrentMapView(int mapX, int mapY, const Map *map);
	void drawMap(const byte bitmap[Map::_numStamps][Map::_stampStride]);
	void internalDrawImage(ImageId id);
	void internalDrawSprite(const Sprite *sprite, int x, int y, int centerX, int centerY, bool addDeltaX = false);
	void internalPaletteFade(PaletteFadeType type);

public:
	static const int _screenWidth = 320;
	static const int _screenHeight = 200;
	static const int _viewportWidth = 256;
	static const int _viewportHeight = 128;
	static const int _frameWidth = 32;
	static const int _frameHeight = 20;  // 12 px frame + 8 px health bar
	static const int _viewportPosX = _frameWidth;
	static const int _viewportPosY = _frameHeight;
	static const int _iconWidth = 64;
	static const int _iconHeight = 48;
	static const int _cursorOriginX = 40;
	static const int _cursorOriginY = 24;
	static const int _buttonYesX = 214 - 32;
	static const int _buttonYesY = 100 - 12;
	static const int _buttonNoX = 40 - 32;
	static const int _buttonNoY = 100 - 12;
	static const int _maxCharWidth = 16;
	static const int _rowHeight = 16;
	static const int _rowWidthLimit = 288;  // 256 px viewport + 32 px border
	static const int _maxRows = 5;
	static const int _charGaugeOff = 1;
	static const int _charGaugeOn = 2;
	static const int _charCopyright = 24;
	static const int _charTrademark = 25;
	static const int _charBlank = 26;

private:
	ResourceManager *_resMan;
	Graphics::Surface _backBuffer;
	PaletteId _currentPalette;
	uint16 _currentMap[Map::_stampsPerViewportH][Map::_stampsPerViewportW];
	Common::Point _cursorPos;
};

}

#endif
