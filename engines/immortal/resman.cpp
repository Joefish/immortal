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
#include "common/debug.h"
#include "common/file.h"
#include "common/memstream.h"
#include "common/ptr.h"
#include "common/stream.h"

#include "immortal/immortal.h"
#include "immortal/resman.h"

namespace Immortal {

struct SpritePackHeader {
	int _offsetToSpriteOffsetList;
	int _numFrames;
	int _centerX;
	int _centerY;
};

static const char *fileMap[kFileAnimationNum] = {
	"GENERAL1.ANM",
	"GENERAL2.ANM",
	"WIZARD.ANM",
	"GOBLIN.ANM",
	"TROLL.ANM",
	"BIGWIZ.ANM",
	"BIGGOB.ANM",
	"BIGTROL.ANM",
	"BIGSPID.ANM",
	"BIGULIN.ANM",
	"DRAGON.ANM",
	"CACHE8.ANM",
	"LEVEL1.ANM",
	"LEVEL1N8.ANM",
	"LEVEL1T5.ANM",
	"LEVEL1T7.ANM",
	"LEVEL2.ANM",
	"LEVEL2N3.ANM",
	"LEVEL2N5.ANM",
	"LEVEL2T4.ANM",
	"LEVEL3.ANM",
	"LEVEL4.ANM",
	"LEVEL5.ANM",
	"LEVEL6.ANM",
	"LEVEL7P1.ANM",
	"LEVEL7P2.ANM",
	"LEVEL8P1.ANM",
	"LEVEL8P2.ANM",
	"LEVEL123.ANM",
	"LEVEL134.ANM",
	"LEVEL147.ANM",
	"LEVEL235.ANM"
};

static const SpriteInfo spriteInfo[kSpriteNum] = {
	{kFileGeneral1, 3,  0},     // kSpriteLadder
	{kFileGeneral2, 0,  0},     // kSpriteAsciiBase
	{kFileGeneral2, 0,  1},     // kSpriteGaugeLifeOn
	{kFileGeneral2, 0,  2},     // kSpriteGaugeLifeOff
	{kFileGeneral2, 1,  0},     // kSpriteMaskBezierTopLeft
	{kFileGeneral2, 1,  1},     // kSpriteMaskBezierTopRight
	{kFileGeneral2, 2,  0},     // kSpriteMaskTriangleLightLeft
	{kFileGeneral2, 2,  1},     // kSpriteMaskTriangleLightRight
	{kFileGeneral2, 2,  2},     // kSpriteMaskTriangleDarkLeft
	{kFileGeneral2, 2,  3},     // kSpriteMaskTriangleDarkRight
	{kFileGeneral2, 4,  0},     // kSpriteChestClosed
	{kFileGeneral2, 4,  1},     // kSpriteChestOpen
	{kFileGeneral2, 4,  2},     // kSpriteRing
	{kFileGeneral2, 4,  3},     // kSpriteDagger
	{kFileGeneral2, 4,  4},     // kSpriteErek
	{kFileGeneral2, 4,  5},     // kSpriteIconCoffee
	{kFileGeneral2, 4,  6},     // kSpriteSpiderEgg
	{kFileGeneral2, 4,  7},     // kSpriteButtonYesInactive
	{kFileGeneral2, 4,  8},     // kSpriteButtonYesActive
	{kFileGeneral2, 4,  9},     // kSpriteButtonNoInactive
	{kFileGeneral2, 4, 10},     // kSpriteButtonNoActive
	{kFileGeneral2, 4, 11},     // kSpriteInventorySelect
	{kFileGeneral2, 4, 12},     // kSpriteInventorySelectBlack
	{kFileGeneral2, 4, 13},     // kSpriteIconSword
	{kFileGeneral2, 4, 14},     // kSpriteIconBottle
	{kFileGeneral2, 4, 15},     // kSpriteBottle
	{kFileGeneral2, 4, 16},     // kSpriteIconKey
	{kFileGeneral2, 4, 17},     // kSpriteIconWormSensor
	{kFileGeneral2, 4, 18},     // kSpriteIconBaitBag
	{kFileGeneral2, 4, 19},     // kSpriteIconBook
	{kFileGeneral2, 4, 20},     // kSpriteIconDragonEgg
	{kFileGeneral2, 4, 21},     // kSpriteScroll
	{kFileGeneral2, 4, 22},     // kSpriteIconScroll
	{kFileGeneral2, 4, 23},     // kSpriteButtonOk
	{kFileGeneral2, 4, 24},     // kSpriteTable
	{kFileGeneral2, 4, 25},     // kSpriteIconGoldBag
	{kFileGeneral2, 4, 26},     // kSpriteIconMap
	{kFileGeneral2, 4, 27},     // kSpriteTrap
	{kFileGeneral2, 4, 28},     // kSpriteSkeleton
	{kFileGeneral2, 4, 29},     // kSpriteIconSporesBag
	{kFileGeneral2, 4, 37},     // kSpriteRuby
	{kFileGeneral2, 4, 38},     // kSpriteRubyShining
	{kFileGeneral2, 4, 39},     // kSpriteStone
	{kFileGeneral2, 4, 40},     // kSpriteGreenStone
	{kFileGeneral2, 4, 41},     // kSpriteIconRuby
	{kFileGeneral2, 4, 42},     // kSpriteIconStone
	{kFileGeneral2, 4, 43},     // kSpriteGold
	{kFileGeneral2, 4, 44},     // kSpriteIconLetter
	{kFileGeneral2, 4, 49},     // kSpriteIconAmulet
	{kFileGeneral2, 4, 50},     // kSpriteIconGold
	{kFileGeneral2, 4, 51},     // kSpriteDragonEgg
	{kFileGeneral2, 4, 52},     // kSpriteShadowThingy52  -- wyvern shadow?
	{kFileGeneral2, 4, 53},     // kSpriteIconBomb
	{kFileGeneral2, 4, 54},     // kSpriteIconRing
	{kFileGeneral2, 4, 55},     // kSpriteIconDagger
	{kFileGeneral2, 4, 56},     // kSpriteIconCarpet
	{kFileGeneral2, 4, 57},     // kSpriteAna
	{kFileGeneral2, 4, 58},     // kSpriteAnaCave
	{kFileGeneral2, 4, 59},     // kSpriteThingy59
	{kFileGeneral2, 4, 60},     // kSpriteFightingGaugeExhaustion
	{kFileGeneral2, 4, 61},     // kSpriteFightingGaugeLife
	{kFileGeneral2, 4, 62},     // kSpriteKoorsLight

	{kFileWizard,   0,  0},     // kSpriteWizard
	{kFileGoblin,   0,  0},     // kSpriteGoblin
	{kFileTroll,    0,  0}      // kSpriteTroll
};

static byte *decodeFile(byte *buffer, int encodedFilesize, int *decodedFilesize);

ResourceManager::ResourceManager() {
	if (loadLibrary("IMM1.LIB").getCode() != Common::kNoError)
		error("Failed loading IMM1.LIB");
	if (loadLibrary("IMM2.LIB").getCode() != Common::kNoError)
		error("Failed loading IMM2.LIB");
}

/**
 * Extracts files from the library, converts and stores them.
 *
 * @param filename Filename of the library to load. Either "IMM1.LIB" or "IMM2.LIB".
 */
Common::Error ResourceManager::loadLibrary(const char *filename) {
	Common::File file;
	if (!file.open(filename)) {
		warning("%s could not be read!", filename);
		return Common::kReadingFailed;
	}

	AssetFile elements[2];
	AssetFile *prevElement = &elements[0];
	AssetFile *currentElement = &elements[1];

	file.skip(5);       // skip lib signature "EALIB"
	int numFiles = file.readUint16LE();
	assert(numFiles > 0);
	file.read(prevElement->_name, 13);
	file.skip(1);
	prevElement->_offset = file.readUint32LE();
	// read list terminator as well
	for (int i = 1; i < numFiles + 1; ++i) {
		file.read(currentElement->_name, 13);
		file.skip(1);
		currentElement->_offset = file.readUint32LE();
		prevElement->_size = currentElement->_offset - prevElement->_offset;
		prevElement->_data.reset(new byte[prevElement->_size]);
		int listNextEntry = file.pos();
		file.seek(prevElement->_offset);
		file.read(prevElement->_data.get(), prevElement->_size);
		file.seek(listNextEntry);

		if (Common::matchString(prevElement->_name, "TTT##.BIN"))
			convertMusic(prevElement);
		else if (Common::matchString(prevElement->_name, "*.BM"))
			convertImage(prevElement);
		else if (Common::matchString(prevElement->_name, "*.ANM"))
			convertSpritePacks(prevElement);
		else if (Common::matchString(prevElement->_name, "MAZE.CMP"))
			convertMap(prevElement);

		SWAP(prevElement, currentElement);
	}

	return Common::kNoError;
}

/**
 * Images are fullscreen 320x200 images loaded from .BM files.
 * A pixel is packed in a nibble and will be shifted into a byte.
 *
 * @param assetFile
 * @param dest
 * @return
 */
Common::Error ResourceManager::convertImage(AssetFile *assetFile) {
	int screenWidth = 320;
	int screenHeight = 200;
	Common::ScopedPtr<byte> *dest;
	if (Common::matchString(assetFile->_name, "TITLEVGA.BM"))
		dest = &_imageContainer[kImageTitleScreen];
	else if (Common::matchString(assetFile->_name, "WINDOWS.BM"))
		dest = &_imageContainer[kImageScreenFrame];
	else
		return Common::Error(Common::kReadingFailed, "file name unknown");

	int decodeSize;
	byte *buffer = decodeFile(assetFile->_data.get(), assetFile->_size, &decodeSize);
	byte *convertedBuffer = new byte[decodeSize * 2];
	byte *itSource = buffer;
	byte *itDest = convertedBuffer;
	for (int y = 0; y < screenHeight; ++y) {
		for (int x = 0; x < screenWidth / 2; ++x, ++itSource) {
			byte pixel = *itSource & 0xF0;
			*itDest++ = (pixel >> 4);
			pixel = *itSource & 0x0F;
			*itDest++ = pixel;
		}
	}

	delete[] buffer;
	dest->reset(convertedBuffer);

	return Common::kNoError;
}

/**
 * Music files are MIDI based with a custom header that needs to be rewritten to a
 * type-0 MIDI header so SMF_MidiParser can read it.
 *
 * @param assetFile
 * @param dest
 * @return
 */
Common::Error ResourceManager::convertMusic(AssetFile *assetFile) {
	int filenum = Common::String::format("%2s", assetFile->_name + 3).asUint64();
	MusicData *dest = &_musicContainer[filenum];

	int decodeSize;
	byte *buffer = decodeFile(assetFile->_data.get(), assetFile->_size, &decodeSize);
	byte *volumePerChannel = buffer + 0x12;
	byte *channelMapping = buffer + 0x22;
	Common::copy(volumePerChannel, volumePerChannel + 0x10, dest->_volume);
	Common::copy(channelMapping, channelMapping + 9, dest->_adlibToMidiChannelTable);
	if (*(buffer + decodeSize - 1) == 0x80)
		dest->_loop = true;
	else
		dest->_loop = false;

	int headerSize = *buffer;
	// Addition byte for EOF Event FF 2F 00 (overwrites FC 80 or 81)
	int midiLength = decodeSize - headerSize + 1;
	// The header is 22 bytes + 1 byte for delta time of the first event
	byte midiHeader[23] = "MThd\x00\x00\x00\x06\x00\x00\x00\x01\x00\x22"
	                      "MTrk\x00\x00\x00\x00";
	dest->_size = sizeof(midiHeader) + midiLength;
	byte *convertedBuffer = new byte[dest->_size];
	byte *it = convertedBuffer;
	WRITE_BE_INT32(midiHeader + 18, midiLength);
	it = Common::copy(midiHeader, ARRAYEND(midiHeader), it);
	it = Common::copy(buffer + headerSize, buffer + decodeSize, it);
	convertedBuffer[dest->_size - 3] = 0xFF;
	convertedBuffer[dest->_size - 2] = 0x2F;
	convertedBuffer[dest->_size - 1] = 0x00;

	delete[] buffer;
	dest->_data.reset(convertedBuffer);

	return Common::kNoError;
}

/**
 * Read sprite data for animation in.
 * An ANM file consists of "Packs" that contain sprites.
 * We keep data as it is instead of converting it to a Surface for
 * handling transparency by drawing the pixels directly to the backbuffer
 * instead of blitting and avoiding scanline offset shenanigans.
 *
 * @param assetFile
 * @return
 */
Common::Error ResourceManager::convertSpritePacks(AssetFile *assetFile) {
	int decodeSize;
	byte *buffer = decodeFile(assetFile->_data.get(), assetFile->_size, &decodeSize);
	Common::MemoryReadStream stream(buffer, decodeSize, DisposeAfterUse::YES);

	int id = 0;
	while (id < kFileAnimationNum && !Common::matchString(assetFile->_name, fileMap[id]))
		++id;
	if (id >= ARRAYSIZE(fileMap))
		return Common::Error(Common::kReadingFailed, "Cannot find requested ANM file");

	int headerSize = stream.readUint16LE();
	stream.seek(0);
	const int kSizeofAnimationHeader = 8;
	int numSpritePacks = headerSize / kSizeofAnimationHeader;
	Common::Array<SpritePack> &container = _spriteContainer[id];
	container.resize(numSpritePacks);

	for (int pack = 0; pack < numSpritePacks; ++pack) {
		int offsetToSpriteOffsetList = stream.readUint16LE();
		int numFrames = stream.readUint16LE();
		int centerX = stream.readUint16LE();
		int centerY = stream.readUint16LE();
		container[pack]._centerX = centerX;
		container[pack]._centerY = centerY;
		container[pack]._sprite.resize(numFrames);

		int headerStreamPos = stream.pos();
		stream.seek(offsetToSpriteOffsetList);
		for (int frame = 0; frame < numFrames; ++frame) {
			int frameOffset = stream.readUint16LE();
			int offsetToSpritesPos = stream.pos();
			stream.seek(frameOffset);

			Sprite *sprite = const_cast<Sprite *>(&container[pack]._sprite[frame]);
			sprite->_x = stream.readByte();
			sprite->_y = stream.readByte();
			sprite->_width = stream.readByte();
			sprite->_height = stream.readByte();
			sprite->_remap = stream.readByte();	// EGA - CGA palette remap
			sprite->_scanlineWidth.resize(sprite->_height);
			sprite->_scanlinePosOffset.resize(sprite->_height);
			sprite->_minScanlineOffset = 256;
			for (int y = 0; y < sprite->_height; ++y) {
				sprite->_scanlineWidth[y] = stream.readByte();
				sprite->_scanlinePosOffset[y] = stream.readByte();
				if (sprite->_scanlinePosOffset[y] < sprite->_minScanlineOffset)
					sprite->_minScanlineOffset = sprite->_scanlinePosOffset[y];
			}
			byte *pixelBuffer = new byte[sprite->_width * sprite->_height];
			memset(pixelBuffer, 0, sprite->_width * sprite->_height);
			stream.read(pixelBuffer, sprite->_width * sprite->_height);
			sprite->_data = pixelBuffer;

			stream.seek(offsetToSpritesPos);
		}
		stream.seek(headerStreamPos);
	}

	return Common::kNoError;
}

Common::Error ResourceManager::convertMap(AssetFile *assetFile) {
	int decodedSize;
	byte *buffer = decodeFile(assetFile->_data.get(), assetFile->_size, &decodedSize);
	Common::MemoryReadStream stream(buffer, decodedSize, DisposeAfterUse::YES);

	stream.read(_mazeMap._tileMap, sizeof(_mazeMap._tileMap));
	for (int tile = 0; tile < Map::_numTiles; ++tile)
		for (int stamp = 0; stamp < (Map::_stampsPerTileW * Map::_stampsPerTileH); ++stamp)
			_mazeMap._stampMap[tile][stamp] = stream.readUint16BE();
	stream.read(_mazeMap._bitmap, sizeof(_mazeMap._bitmap));

	return Common::kNoError;
}

const MusicData *ResourceManager::getMusic(MusicId id) const {
	return &_musicContainer[id];
}

const byte *ResourceManager::getImage(ImageId id) const {
	return _imageContainer[id].get();
}

const Sprite *ResourceManager::getSprite(SpriteId id) const {
	const SpriteInfo *info = getSpriteInfo(id);
	return getSprite(info->fileId, info->pack, info->sprite);
}

const Sprite *ResourceManager::getSprite(FileId fileId, int pack, int spriteNum) const {
	return &_spriteContainer[fileId][pack]._sprite[spriteNum];
}

Common::Point ResourceManager::getSpritePackCenter(FileId fileId, int pack) const {
	return Common::Point(static_cast<int16>(_spriteContainer[fileId][pack]._centerX),
	                     static_cast<int16>(_spriteContainer[fileId][pack]._centerY));
}

const Map *ResourceManager::getMap() {
	return &_mazeMap;
}

const SpriteInfo *ResourceManager::getSpriteInfo(SpriteId id) const {
	return &spriteInfo[id];
}

/**
 * Flag-based LZSS Decoder with integrated dictionary for files in *.LIB.
 *
 * @param inBuffer encoded file buffer
 * @param encodedFilesize size of the encoded file
 * @param decodedFilesize size of the decoded file
 * @return decoded file buffer
 */
static byte *decodeFile(byte *inBuffer, int encodedFilesize, int *decodedFilesize) {
	byte lzwBuffer[4096] = {};
	byte *outBuffer = nullptr;
	int lzwBufferIndex = sizeof(lzwBuffer) - 18;
	int inBufferIndex = 0;
	int outBufferIndex = 0;
	int flags = 0;

	memset(lzwBuffer, '\0', lzwBufferIndex);
	int fileSize = READ_LE_INT32(inBuffer);
	if (decodedFilesize)
		*decodedFilesize = fileSize;
	inBuffer += 4;
	outBuffer = new byte[fileSize];

	while (inBufferIndex < encodedFilesize && outBufferIndex < fileSize) {
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

Sprite::Sprite()
    : _x(0)
    , _y(0)
    , _width(0)
    , _height(0)
    , _minScanlineOffset(0)
    , _remap(0)
    , _data(nullptr) {
}

Sprite::~Sprite() {
	delete[] _data;
}

}
