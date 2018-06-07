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
	0xFFFF, 0x0743, 0x0B75, 0x0322,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0x0FB6,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
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

Renderer::Renderer(ResourceManager *resMan)
	: _resMan(resMan)
	, _screenWidth(320)
	, _screenHeight(200)
	, _currentPalette(kPaletteInvalid) {
	_backBuffer.create(_screenWidth, _screenHeight, g_system->getScreenFormat());
}

void Renderer::draw(ImageId id) {
	if (id == kImageTitleScreen)
		loadPalette(kPaletteTitle);
	else if (id == kImageScreenFrame)
		loadPalette(kPaletteDefault);

	const byte *buffer = _resMan->getImage(id);
	_backBuffer.copyRectToSurface(buffer, _screenWidth, 0, 0, _screenWidth, _screenHeight);
}

void Renderer::draw(AnimationId id, int x, int y, int *frame) {
	const Animation *anim = _resMan->getAnimation(id);
	if (*frame >= anim->getNumFrames())
		*frame = 0;
	const Sprite *sprite = anim->getFrame(*frame);
	*frame = *frame + 1;

	g_system->copyRectToScreen(sprite->_data, sprite->_width, x + sprite->_x,
							   y + sprite->_y, sprite->_width, sprite->_height);
}

void Renderer::draw(const byte *buffer, int x, int y, int width, int height) {
	_backBuffer.copyRectToSurface(buffer, width, x, y, width, height);
}

void Renderer::drawSprite(AnimationId id, int x, int y) {
	// TODO:
	// Add Clipping

	const Animation *animation = _resMan->getAnimation(id);
	const Sprite *sprite = animation->getFrame(0);
	byte *screenPtr = static_cast<byte *>(_backBuffer.getBasePtr(x, y));

	int currentPixel = 0;
	for (int dy = 0; dy < sprite->_height; ++dy) {
		for (int dx = 0; dx < sprite->_scanlineWidth[dy]; ++dx) {
			int pos = dy * _screenWidth + dx + sprite->_x + sprite->_scanlinePosOffset[dy];
			byte pixel = 0;
			if (currentPixel & 1)
				pixel = sprite->_data[currentPixel >> 1] & 0x0F;
			else
				pixel = (sprite->_data[currentPixel >> 1] >> 4) & 0x0F;
			if (pixel)
				screenPtr[pos] = pixel;

			++currentPixel;
		}
	}
}

void Renderer::update() {
	g_system->copyRectToScreen(_backBuffer.getPixels(), _backBuffer.pitch, 0, 0,
							   _backBuffer.w, _backBuffer.h);
//	_backBuffer.fillRect(Common::Rect(_backBuffer.w, _backBuffer.h), 0);
	g_system->updateScreen();
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
		int color = palette[i];
		convertedPalette[i * 3 + 2] = ((color & 0xF)) * 16;
		convertedPalette[i * 3 + 1] = ((color & 0xF0) >> 4) * 16;
		convertedPalette[i * 3 + 0] = ((color & 0xF00) >> 8) * 16;
	}
	g_system->getPaletteManager()->setPalette(convertedPalette, 0, 16);
}

}
