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

#include "common/array.h"
#include "common/file.h"
#include "common/ptr.h"
#include "common/stream.h"

#include "immortal/immortal.h"
#include "immortal/resman.h"

namespace Immortal {

struct AssetMap {
	const char *_filename;
	AssetId _id;
};

static const AssetMap idMap[] = {
	{"TITLEEGA.BM", kAssetEGATitleScreen},
	{"TITLEVGA.BM", kAssetVGATitleScreen},
	{"WINDOWS.BM", kAssetScreenBorder},
	{"MAZE.CMP", kAssetInvalid},
	{"GENERAL1.ANM", kAssetInvalid},
	{"GENERAL2.ANM", kAssetInvalid},
	{"WIZARD.ANM", kAssetInvalid},
	{"BIGWIZ.ANM", kAssetInvalid},
	{"MTCAMP.BIN", kAssetInvalid},
	{"ADCAMP.BIN", kAssetInvalid},
	{"TNCAMP.BIN", kAssetInvalid},
	{"PCCAMP.BIN", kAssetInvalid},
	{"TTT02.BIN", kAssetInvalid},
	{"TTT03.BIN", kAssetInvalid},
	{"TTT12.BIN", kAssetInvalid},
	{"TTT16.BIN", kAssetInvalid},
	{"TTT19.BIN", kAssetInvalid},
	{"LEVEL1.ANM", kAssetInvalid},
	{"LEVEL1N8.ANM", kAssetInvalid},
	{"LEVEL1T5.ANM", kAssetInvalid},
	{"LEVEL1T7.ANM", kAssetInvalid},
	{"LEVEL2.ANM", kAssetInvalid},
	{"LEVEL2N3.ANM", kAssetInvalid},
	{"LEVEL2N5.ANM", kAssetInvalid},
	{"LEVEL2T4.ANM", kAssetInvalid},
	{"LEVEL3.ANM", kAssetInvalid},
	{"LEVEL4.ANM", kAssetInvalid},
	{"LEVEL5.ANM", kAssetInvalid},
	{"LEVEL6.ANM", kAssetInvalid},
	{"LEVEL7P1.ANM", kAssetInvalid},
	{"LEVEL7P2.ANM", kAssetInvalid},
	{"LEVEL8P1.ANM", kAssetInvalid},
	{"LEVEL8P2.ANM", kAssetInvalid},
	{"LEVEL123.ANM", kAssetInvalid},
	{"LEVEL134.ANM", kAssetInvalid},
	{"LEVEL147.ANM", kAssetInvalid},
	{"LEVEL235.ANM", kAssetInvalid},
	{"GOBLIN.ANM", kAssetInvalid},
	{"TROLL.ANM", kAssetInvalid},
	{"WIZARD.ANM", kAssetInvalid},
	{"CACHE8.ANM", kAssetInvalid},
	{"DRAGON.ANM", kAssetInvalid},
	{"BIGGOB.ANM", kAssetInvalid},
	{"BIGTROL.ANM", kAssetInvalid},
	{"BIGSPID.ANM", kAssetInvalid},
	{"BIGULIN.ANM", kAssetInvalid},
	{"TTT00.BIN", kAssetInvalid},
	{"TTT01.BIN", kAssetInvalid},
	{"TTT04.BIN", kAssetInvalid},
	{"TTT05.BIN", kAssetInvalid},
	{"TTT06.BIN", kAssetInvalid},
	{"TTT07.BIN", kAssetInvalid},
	{"TTT08.BIN", kAssetInvalid},
	{"TTT09.BIN", kAssetInvalid},
	{"TTT10.BIN", kAssetInvalid},
	{"TTT11.BIN", kAssetInvalid},
	{"TTT13.BIN", kAssetInvalid},
	{"TTT14.BIN", kAssetInvalid},
	{"TTT15.BIN", kAssetInvalid},
	{"TTT17.BIN", kAssetInvalid},
	{"TTT18.BIN", kAssetInvalid},
	{"TTT20.BIN", kAssetInvalid}
};

static void setAssetId(AssetFile *assetFile);
static byte *lzwDecode(byte *buffer, int bufferSize);

ResourceManager::ResourceManager() {
	init();
}

void ResourceManager::init() {
	if (loadLibrary("IMM1.LIB").getCode() != Common::kNoError)
		error("Failed loading IMM1.LIB");
	if (loadLibrary("IMM2.LIB").getCode() != Common::kNoError)
		error("Failed loading IMM2.LIB");
}

/**
 * Extracts files from the library and converts them.
 *
 * @param filename Filename of the library to load. Either "IMM1.LIB" or "IMM2.LIB".
 * @return Error code
 */
Common::Error ResourceManager::loadLibrary(const char *filename) {
	Common::File file;
	if (!file.open(filename)) {
		warning("%s could not be read!", filename);
		return Common::kReadingFailed;
	}

	file.skip(5);	// skip lib signature "EALIB"
	int numFiles = file.readUint16LE();
	assert(numFiles > 0);

	AssetFile elements[2];
	AssetFile *prevElement = &elements[0];
	AssetFile *currentElement = &elements[1];

	file.read(prevElement->_filename, 13);
	file.skip(1);
	prevElement->_offset = file.readUint32LE();
	// read list terminator as well
	for (int i = 1; i < numFiles + 1; ++i) {
		file.read(currentElement->_filename, 13);
		file.skip(1);
		currentElement->_offset = file.readUint32LE();
		prevElement->_size = currentElement->_offset - prevElement->_offset;
		prevElement->_data.reset(new byte[prevElement->_size]);
		int offsetListNextEntry = file.pos();

		// TODO: Implement conversion for all file types
		file.seek(prevElement->_offset);
		file.read(prevElement->_data.get(), prevElement->_size);
		file.seek(offsetListNextEntry);
		setAssetId(prevElement);
		convertImage(prevElement);

		SWAP(prevElement, currentElement);
	}

	return Common::kNoError;
}

/**
 * Images are fullscreen 320x200 images loaded from .BM files that get
 * converted to Graphics::Surface.
 *
 * @param assetFile Asset that is about to be converted to a surface
 * @return Error code
 */
Common::Error ResourceManager::convertImage(const AssetFile *assetFile) {
	Graphics::Surface *surface;
	switch (assetFile->_id) {
	case kAssetVGATitleScreen:
		surface = &_titleScreen;
		break;
	case kAssetScreenBorder:
		surface = &_screenBorder;
		break;
	default:
		return Common::kUnknownError;
	}

	int width = 320;
	int height = 200;
	byte *buffer = lzwDecode(assetFile->_data.get(), assetFile->_size);
	byte *ptr = buffer;

	surface->create(width, height, Graphics::PixelFormat::createFormatCLUT8());
	byte *surfacePixels = static_cast<byte *>(surface->getPixels());
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width / 2; ++x, ++ptr) {
			byte pixel = *ptr & 0xF0;
			*surfacePixels++ = (pixel >> 4);
			pixel = *ptr & 0x0F;
			*surfacePixels++ = pixel;
		}
	}

	delete[] buffer;

	return Common::kNoError;
}

Graphics::Surface *ResourceManager::getImage(AssetId id) {
	switch (id) {
	case kAssetEGATitleScreen:
	case kAssetVGATitleScreen:
		return &_titleScreen;
	case kAssetScreenBorder:
		return &_screenBorder;
	default:
		return nullptr;
	}
}


static void setAssetId(AssetFile *assetFile) {
	for (int i = 0; i < ARRAYSIZE(idMap); ++i) {
		if (scumm_stricmp(idMap[i]._filename, assetFile->_filename) == 0) {
			assetFile->_id = idMap[i]._id;
			return;
		}
	}
}

/**
 * Flag-based LZW Decoder with integrated dictionary for files in *.LIB.
 *
 * @param inBuffer encoded file buffer
 * @param bufferSize size of the encoded file
 * @return decoded file buffer
 */
static byte *lzwDecode(byte *inBuffer, int bufferSize) {
	byte lzwBuffer[4096] = {};
	byte *outBuffer = nullptr;
	int lzwBufferIndex = sizeof(lzwBuffer) - 18;
	int inBufferIndex = 0;
	int outBufferIndex = 0;
	int flags = 0;

	memset(lzwBuffer, ' ', lzwBufferIndex);
	int fileSize = READ_LE_INT32(inBuffer);
	inBuffer += 4;
	outBuffer = new byte[fileSize];

	while (inBufferIndex < bufferSize && outBufferIndex < fileSize) {
		flags >>= 1;
		if ((flags & 0x100) == 0)
			flags = 0xFF00 | inBuffer[inBufferIndex++];

		if (flags & 1) {
			byte tmp = inBuffer[inBufferIndex++];
			outBuffer[outBufferIndex++] = tmp;
			lzwBuffer[lzwBufferIndex++] = tmp;
			lzwBufferIndex &= sizeof(lzwBuffer) - 1;
			continue;
		}

		int seqPosition = inBuffer[inBufferIndex++];
		int seqLength = inBuffer[inBufferIndex++];
		seqPosition |= ((seqLength & 0xF0) << 4);
		seqLength = (seqLength & 0xF) + 3; // sequence pos and length + terminator?

		for (; seqLength != 0; --seqLength) {
			seqPosition &= sizeof(lzwBuffer) - 1;
			byte c = lzwBuffer[seqPosition++];
			lzwBuffer[lzwBufferIndex++] = c;
			lzwBufferIndex &= sizeof(lzwBuffer) - 1;
			outBuffer[outBufferIndex++] = c;
		}
	}

	return outBuffer;
}

}
