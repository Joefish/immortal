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
#include "graphics/palette.h"

#include "immortal/graphics.h"

namespace Immortal {

static const int titlePalette[16] = {
	0x0000, 0x0007,	0x0363,	0x00AA,
	0x0A00, 0x0999,	0x090A,	0x0CBB,
	0x0555,	0x085F,	0x0995,	0x05FF,
	0x0F33,	0x0B6F,	0x0CC4,	0x0FFF
};
static const int defaultPalette[16] = {
	0x0000, 0x0743, 0x0B75, 0x0322,
	0x0E00, 0x0A00, 0x0B69, 0x0808,
	0x0AA0, 0x0333, 0x0666, 0x0FB6,
	0x0781, 0x0FFF, 0x0000, 0x0999
};
static const int fadePalette[16] = {
		-1, 0x0743, 0x0B75, 0x0322,
		-1,     -1,     -1,     -1,
		-1,     -1,     -1, 0x0FB6,
		-1,     -1,     -1,     -1
};
static const int whitecmap[16] = {
	0x0000, 0x0FFF, 0x0FFF, 0x0FFF,
	0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF,
	0x0FFF, 0x0333, 0x0666, 0x0FB6,
	0x0FFF, 0x0FFF, 0x0000, 0x0999
};
static const int blackcmap[16] = {
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0333, 0x0666, 0x0FB6,
	0x0000, 0x0FFF, 0x0000, 0x0999
};
static const int dimcmap[16] = {
	0x0000, 0x0532, 0x0742, 0x0322,
	0x0C00, 0x0800, 0x0B69, 0x0808,
	0x0A0A, 0x0222, 0x0444, 0x0FB6,
	0x0781, 0x0AAA, 0x0000, 0x0666
};

const int Renderer::_screenWidth = 320;
const int Renderer::_screenHeight = 200;
const int Renderer::_viewportWidth = 256;
const int Renderer::_viewportHeight = 128;
const int Renderer::_frameWidth = 32;
const int Renderer::_frameHeight = 20;	// 12 px frame + 8 px health bar
const Common::Point Renderer::_viewportPos(Renderer::_frameWidth, Renderer::_frameHeight);

void Renderer::convertPaletteToRGB(int palColor, byte *red, byte *green, byte *blue) {
	*blue = ((palColor & 0xF)) * 16;
	*green = ((palColor & 0xF0) >> 4) * 16;
	*red = ((palColor & 0xF00) >> 8) * 16;
}

Renderer::Renderer(ResourceManager *resMan)
	: _resMan(resMan)
	, _currentPalette(kPaletteInvalid) {
	_backBuffer.create(_screenWidth, _screenHeight, g_system->getScreenFormat());
}

void Renderer::drawImage(ImageId id) {
	internalDrawImage(id);
}

void Renderer::drawSprite(AnimationId id, int frame, int x, int y) {
	internalDrawSprite(id, frame, x, y);
}

void Renderer::paletteFadeIn() {
	internalPaletteFade(kPaletteFadeIn);
}

void Renderer::paletteFadeOut() {
	internalPaletteFade(kPaletteFadeOut);
}

void Renderer::paletteSlowFadeOut() {
	internalPaletteFade(kPaletteFadeSlowOut);
}

void Renderer::clear() {
	drawImage(kImageScreenFrame);
}

void Renderer::update() {
	g_system->copyRectToScreen(_backBuffer.getPixels(), _backBuffer.pitch, 0, 0,
							   _backBuffer.w, _backBuffer.h);
	g_system->updateScreen();
}

void Renderer::drawMap(int x, int y) {
	const Map *map = _resMan->getMap();

	// set index map for current position
	for (int dy = 0; dy < Map::_tilesScreenHeight; ++dy) {
		for (int dx = 0; dx < Map::_tilesScreenWidth; ++dx) {
			int indexX = (x + dx) / 8;
			int indexY = (y + dy) / 4;
			int tileIndex = map->_indexMap[indexX][indexY];
			int offset = tileIndex * 64;

			// TODO:
			// this is getting ridiculous.. maybe convert in resman in easier
			// to handle format. But for now just get it running
			int cy = (y + dy) % 4;
			for (; cy < 4; ++cy) {
				int cx = (x + dx) % 8;
				const byte *tileIndexForSmallMaps = &map->_tileMap[0][0] + offset;
				tileIndexForSmallMaps += cy * 8 + cx;
				for (; cx < 8; ++cx) {
					int index1 = *tileIndexForSmallMaps++;
					int index2 = *tileIndexForSmallMaps++;
					_currentIndexMap[x][y] = (index1 << 8) | index2;
					++dx;
					if (dx >= Map::_tilesScreenWidth)
						break;
				}

				++dy;
				if (dy >= Map::_tilesScreenHeight)
					break;
			}
		}
	}

	drawMapTile(x + _viewportPos.x, y + _viewportPos.y, &map->_tileBitmap[0][0]);
}

// INFO: In MAZE.CMP are 146 tiles of 8x8 16 color
void Renderer::drawMapTile(int x, int y, const byte *tileBitmap) {
	// TODO: name constants
	byte *backBuffer = static_cast<byte *>(_backBuffer.getPixels());
	for (int dy = 0; dy < Map::_tilesScreenHeight; ++dy) {
		for (int dx = 0; dx < Map::_tilesScreenWidth; ++dx) {
			int offset = (_currentIndexMap[dx][dy] & 0x07FF);
			const byte *pixelData = &tileBitmap[offset * 32];
			for (int pixelY = 0; pixelY < Map::_tileHeight; ++pixelY) {
				for (int pixelX = 0; pixelX < Map::_tileWidth / 2; ++pixelX) {
					byte *screenPtr = backBuffer + (pixelY * _screenWidth + pixelX);
					*(screenPtr + 0) = *pixelData >> 4;
					*(screenPtr + 1) = *pixelData++ & 0x0F;
				}
			}
		}
	}
}


void Renderer::loadPalette(PaletteId id) {
	if (_currentPalette == id)
		return;

	const int *palette = nullptr;
	_currentPalette = id;

	switch (id) {
	case kPaletteTitle:
		palette = titlePalette;
		break;
	case kPaletteFade:
		palette = fadePalette;
		break;
	default:
		palette = defaultPalette;
		break;
	}

	byte convertedPalette[48] = {};
	for (int i = 0; i < 16; ++i) {
		byte *dest = &convertedPalette[i * 3];
		convertPaletteToRGB(palette[i], dest, dest + 1, dest + 2);
	}
	g_system->getPaletteManager()->setPalette(convertedPalette, 0, 16);
}

// TODO:
// Rather than drawing the screen frame and limiting viewport to 256x128
// why not drawing full 320x200 of the map and make frame togglable.
// Extending/Reducing the viewport on the fly and update clipping would be better
// than just overdraw for performance (measure).
// For this to work, drawImage() need to support transparency or predefine frame
// dimensions to not overdraw viewport. Don't forget to memset the backBuffer
// after blitting in update() to remove garbage.
void Renderer::internalDrawImage(ImageId id) {
	if (id == kImageTitleScreen)
		loadPalette(kPaletteTitle);
	else if (id == kImageScreenFrame)
		loadPalette(kPaletteDefault);

	const byte *buffer = _resMan->getImage(id);
	_backBuffer.copyRectToSurface(buffer, _screenWidth, 0, 0, _screenWidth, _screenHeight);
}

// TODO:
// Add Clipping
void Renderer::internalDrawSprite(AnimationId id, int frame, int x, int y) {
	const Animation *animation = _resMan->getAnimation(id);
	const Sprite *sprite = animation->getFrame(frame);
	byte *screenPtr = static_cast<byte *>(_backBuffer.getBasePtr(x, y));
	int currentPixel = 0;

	for (int dy = 0; dy < sprite->_height; ++dy) {
		for (int dx = 0; dx < sprite->_scanlineWidth[dy]; ++dx) {
			int pos = (dy + sprite->_y - animation->getCenter().y) * _screenWidth +
					  (dx + sprite->_scanlinePosOffset[dy] - animation->getCenter().x);
			byte pixel = sprite->_data[currentPixel >> 1];
			if (currentPixel & 1)
				pixel &= 0x0F;
			else
				pixel = (pixel >> 4) & 0x0F;
			if (pixel)
				screenPtr[pos] = pixel;

			++currentPixel;
		}
	}
}

// INFO: Right now this will block until fading is done.
void Renderer::internalPaletteFade(PaletteFadeType type) {
	byte tmpPalette[16 * 3];
	int colorMultiplier = (type == kPaletteFadeIn) ? 0 : 15;
	int colorMultiplierEnd = (type == kPaletteFadeIn) ? 15: 0;
	int colorMultiplierStep = (type == kPaletteFadeIn) ? 1 : -1;

	for (; colorMultiplier != colorMultiplierEnd; colorMultiplier += colorMultiplierStep) {
		g_system->getPaletteManager()->grabPalette(tmpPalette, 0, 16);
		for (int i = 0; i < 16; ++i) {
			if (fadePalette[i] != -1) {
				byte *dest = &tmpPalette[i * 3];
				convertPaletteToRGB(fadePalette[i], dest, dest + 1, dest + 2);
				dest[0] = (dest[0] * colorMultiplier / 16);
				dest[1] = (dest[1] * colorMultiplier / 16);
				dest[2] = (dest[2] * colorMultiplier / 16);
			}
		}
		g_system->getPaletteManager()->setPalette(tmpPalette, 0, 16);
		update();

		if (type == kPaletteFadeSlowOut)
			g_system->delayMillis(28 * 4); // one 'jiffy' = 1 / (72.8 Hz * 4)
		else
			g_system->delayMillis(15 * 4);
	}
}

}
