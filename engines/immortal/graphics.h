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
	void drawImage(ImageId id);
	void drawSprite(AnimationId id, int frame, int x, int y);
	void paletteFadeIn();
	void paletteFadeOut();
	void paletteSlowFadeOut();
	void update();

public:
	static const int _screenWidth;
	static const int _screenHeight;
	static const int _viewportWidth;
	static const int _viewportHeight;
	static const Common::Point _viewportPos;
	static const int _frameWidth;
	static const int _frameHeight;

private:
	static void convertPaletteToRGB(int palColor, byte *red, byte *green, byte *blue);
	void loadPalette(PaletteId id);
	void internalDrawImage(ImageId id);
	void internalDrawSprite(AnimationId id, int frame, int x, int y);
	void internalPaletteFade(PaletteFadeType type);

	ResourceManager *_resMan;
	Graphics::Surface _backBuffer;
	PaletteId _currentPalette;
};

}

#endif
