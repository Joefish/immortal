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
 * aint32 with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * Based on the original sources
 *   Faery Tale II -- The Halls of the Dead
 *   (c) 1993-1996 The Wyrmkeep Entertainment Co.
 */

#include "common/debug.h"
#include "graphics/surface.h"

#include "saga2/std.h"
#include "saga2/gdraw.h"

namespace Saga2 {

void _BltPixels(uint8 *srcPtr, uint32 srcMod, uint8 *dstPtr, uint32 dstMod, uint32 width, uint32 height) {
	for (uint y = 0; y < height; y++) {
		uint8 *src = srcPtr + srcMod * y;
		uint8 *dst = dstPtr + dstMod * y;
		for (uint x = 0; x < width; x++) {
			*dst++ = *src++;
		}
	}
}

void _BltPixelsT(uint8 *srcPtr, uint32 srcMod, uint8 *dstPtr, uint32 dstMod, uint32 width, uint32 height) {
	for (uint y = 0; y < height; y++) {
		uint8 *src = srcPtr + srcMod * y;
		uint8 *dst = dstPtr + dstMod * y;
		for (uint x = 0; x < width; x++) {
			byte c = *src++;

			if (c == 0)
				dst++;
			else
				*dst++ = c;
		}
	}
}

void _FillRect(uint8 *dstPtr, uint32 dstMod, uint32 width, uint32 height, uint32 color) {
	for (uint y = 0; y < height; y++) {
		memset(dstPtr, color, width);

		dstPtr += dstMod;
	}
}

void _HLine(uint8 *dstPtr, uint32 width, uint32 color) {
	memset(dstPtr, color, width);
}

void unpackImage(gPixelMap &map, int16 width, int16 rowCount, int8 *srcData) {
	int8  *dest = (int8 *)map.data;
	int16 bytecount = (width + 1) & ~1;
	int16 rowMod = map.size.x - bytecount;

	while (rowCount--) {
		for (int16 k = 0; k < bytecount;) {
			int16 p = *srcData++;

			if (p == -128)
				continue;
			else if (p >= 0) {
				p++;
				k += p;
				while (p--)
					*dest++ = *srcData++;
			} else {
				p = 1 - p;
				k += p;
				while (p--)
					*dest++ = *srcData;
				srcData++;
			}
		}

		if (bytecount & 1)
			srcData++;
		dest += rowMod;
	}
}

void unpackImage(gPixelMap *map, int32 width, int32 rowCount, int8 *srcData) {
	unpackImage(*map, (int16)width, (int16)rowCount, srcData);
}

void unpackSprite(gPixelMap *map, uint8 *sprData) {
	byte *dst = map->data;
	int bytes = map->size.x * map->size.y;

	while (true) {
		byte trans = *sprData++;
		memset(dst, 0, trans);
		dst += trans;
		bytes -= trans;

		if (bytes < 0)
			break;

		byte fill = *sprData++;
		memcpy(dst, sprData, fill);
		dst += fill;
		bytes -= fill;
		sprData += fill;
	}
}

void drawTile(gPixelMap *map, int32 x, int32 y, int32 height, uint8 *srcData, bool mask) {
	const byte *tilePointer;
	const byte *readPointer;
	byte *drawPointer;
	Point32 drawPoint;
	int widthCount = 0;
	int row, col, count, lowBound;
	int bgRunCount;
	int fgRunCount;
	const int32 SAGA_ISOTILE_WIDTH = 64;
	Point16 point(x, y);

	if (point.x + SAGA_ISOTILE_WIDTH < 0)
		return;

	if (point.x - SAGA_ISOTILE_WIDTH >= map->size.x)
		return;

	tilePointer = srcData;

	drawPoint = point;

	drawPoint.y -= height;

	if (drawPoint.y >= map->size.y)
		return;

	readPointer = tilePointer;
	lowBound = MIN((int)(drawPoint.y + height), (int)map->size.y);
	for (row = drawPoint.y; row < lowBound; row++) {
		widthCount = 0;
		if (row >= 0) {
			drawPointer = map->data + drawPoint.x + (row * map->size.x);
			col = drawPoint.x;
			for (;;) {
				bgRunCount = *readPointer++;
				widthCount += bgRunCount;
				if (widthCount >= SAGA_ISOTILE_WIDTH)
					break;

				drawPointer += bgRunCount;
				col += bgRunCount;
				fgRunCount = *readPointer++;
				widthCount += fgRunCount;

				count = 0;
				int colDiff = - col;
				if (colDiff > 0) {
					if (colDiff > fgRunCount)
						colDiff = fgRunCount;

					count = colDiff;
					col += colDiff;
				}

				colDiff = map->size.x - col;
				if (colDiff > 0) {
					int countDiff = fgRunCount - count;
					if (colDiff > countDiff)
						colDiff = countDiff;

					if (colDiff > 0) {
						byte *dst = (byte *)(drawPointer + count);
						if (mask)
							memset(dst, 0, colDiff);
						else
							memcpy(dst, (readPointer + count), colDiff);
						col += colDiff;
					}
				}

				readPointer += fgRunCount;
				drawPointer += fgRunCount;
			}
		} else {
			for (;;) {
				bgRunCount = *readPointer++;
				widthCount += bgRunCount;
				if (widthCount >= SAGA_ISOTILE_WIDTH)
					break;

				fgRunCount = *readPointer++;
				widthCount += fgRunCount;

				readPointer += fgRunCount;
			}
		}
	}

	// Compute dirty rect
	int rectX = MAX<int>(drawPoint.x, 0);
	int rectY = MAX<int>(drawPoint.y, 0);
	int rectX2 = MIN<int>(drawPoint.x + SAGA_ISOTILE_WIDTH, map->size.x);
	int rectY2 = lowBound;
	debugC(3, kDebugTiles, "Rect = (%d,%d,%d,%d)", rectX, rectY, rectX2, rectY2);

#if 0
	Graphics::Surface sur;
	sur.create(map->size.x, map->size.y, Graphics::PixelFormat::createFormatCLUT8());
	sur.setPixels(map->data);
	//sur.debugPrint();
	g_system->copyRectToScreen(sur.getPixels(), sur.pitch, 0, 0, sur.w, sur.h);
	g_system->updateScreen();
#endif
}


void maskTile(gPixelMap *map, int32 x, int32 y, int32 height, uint8 *srcData) {
	drawTile(map, x, y, height, srcData, true);
}

void TBlit(gPixelMap *dstMap, gPixelMap *srcMap, int xpos, int ypos) {
	int16 w = srcMap->size.x;
	int16 h = srcMap->size.y;
	int32 offset = 0;

	if (ypos < 0) {
		h += ypos;
		offset -= (ypos * w);
		ypos = 0;
	}

	if (xpos < 0) {
		w += xpos;
		offset -= xpos;
		xpos = 0;
	}

	if (w > dstMap->size.x - xpos)
		w = dstMap->size.x - xpos;
	if (h > dstMap->size.y - ypos)
		h = dstMap->size.y - ypos;
	if (w < 0 || h < 0)
		return;

	int16 dstMod = dstMap->size.x - w;
	int16 srcMod = srcMap->size.x - w;

	byte *srcPtr = srcMap->data + offset;
	byte *dstPtr = dstMap->data + xpos + ypos * dstMap->size.x;

	for (int16 y = 0; y < h; y++) {
		for (int16 x = 0; x < w; x++) {
			byte c = *srcPtr++;

			if (c == 0)
				dstPtr++;
			else
				*dstPtr++ = c;
		}
		dstPtr += dstMod;
		srcPtr += srcMod;
	}
}

void TBlit4(gPixelMap *d, gPixelMap *s, int32 x, int32 y) {
	TBlit(d, s, x, y);
}

void compositePixels(gPixelMap *compMap, gPixelMap *sprMap, int xpos, int ypos, byte *lookup) {
	byte *srcPtr = sprMap->data;
	byte *dstPtr = compMap->data + xpos + ypos * compMap->size.x;
	int16 rowMod = compMap->size.x - sprMap->size.x;

	for (int16 y = 0; y < sprMap->size.y; y++) {
		for (int16 x = 0; x < sprMap->size.x; x++) {
			byte c = *srcPtr++;

			if (c == 0)
				dstPtr++;
			else
				*dstPtr++ = lookup[ c ];
		}
		dstPtr += rowMod;
	}
}

void compositePixelsRvs(gPixelMap *compMap, gPixelMap *sprMap, int xpos, int ypos, byte *lookup) {
	byte *srcPtr = sprMap->data + sprMap->bytes();
	byte *dstPtr = compMap->data + xpos + (ypos + sprMap->size.y) * compMap->size.x;

	int16 rowMod = compMap->size.x + sprMap->size.x;

	for (int16 y = 0; y < sprMap->size.y; y++) {
		dstPtr -= rowMod;

		for (int16 x = 0; x < sprMap->size.x; x++) {
			byte c = *--srcPtr;

			if (c == 0)
				dstPtr++;
			else
				*dstPtr++ = lookup[c];
		}
	}
}

bool initGraphics(void) {
	warning("STUB: initGraphics()");
	return false;
}

bool initProcessResources(void) {
        return true;
}

void termProcessResources(void) {
}

} // end of namespace Saga2