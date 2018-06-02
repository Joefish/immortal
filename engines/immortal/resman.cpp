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

struct AnimationHeader {
	int _offsetToSpriteOffsetList;
	int _numFrames;
	int _centerX;
	int _centerY;
};

struct AnimationInfo {
	AnimationId _id;
	int _animation;
	int _frameStart;
	int _frameEnd; // inclusive
};

// INFO:
// 0, -1 means from frame 0 to last frame of animation
//
// TODO:
// Finish mapping the animations.
// Check how BIG differs from other ANM files.
// Wizard, Troll, .. have sprites for walking/dodging at same index for every
// direction. So, instead of repeating the mapping all 8 directions just adjust
// the animation index.
// Instead of treating everything the same, differentiate between single sprites and
// multiple sprites building an animation. ~
static const AnimationInfo infoGeneral1[] = {
	{kAnimationTunnelFalling, 		0,  0, -1},
	{kAnimationTorchFire, 			1,  0, -1},
	{kAnimationWoodenDoor, 			2,  0,  1},
	{kAnimationSteelDoor, 			2,  2,  3},
	{kAnimationLadder, 				3,  0,  0},
	{kAnimationLadderClimbing, 		3,  1, -1},
	{kAnimationTunnel, 				4,  0,  0},
	{kAnimationTunnelDescending, 	4,  1, -1},
	{kAnimationWizardIncinerate, 	5,  0, -1},
	{kAnimationTunnelOpening,		6,  0, -1}
};
static const AnimationInfo infoGeneral2[] = {
	{kAnimationSymbols, 					0,  0, -1},
	{kAnimationShadowBezierTopLeft, 		1,  0,  0},
	{kAnimationShadowBezierTopRight, 		1,  1,  1},
	{kAnimationShadowTriangleLightLeft, 	2,  0,  0},
	{kAnimationShadowTriangleLightRight, 	2,  1,  1},
	{kAnimationShadowTriangleDarkLeft, 		2,  2,  2},
	{kAnimationShadowTriangleDarkRight, 	2,  3,  3},
	{kAnimationBloodLeft, 					3,  0,  2},
	{kAnimationBloodRight, 					3,  3,  5},
	{kAnimationSparksLeft, 					3,  6, 10},
	{kAnimationSparksRight, 				3, 10, 15},
	{kAnimationSparksCenter, 				3, 16, 25},
	{kAnimationSparksSmall, 				3, 26, 30},
	{kAnimationFireballN, 					3, 31, 33},
	{kAnimationFireballNE, 					3, 34, 36},
	{kAnimationFireballE, 					3, 37, 39},
	{kAnimationFireballSE, 					3, 40, 42},
	{kAnimationFireballS, 					3, 43, 45},
	{kAnimationFireballSW, 					3, 46, 48},
	{kAnimationFireballW, 					3, 49, 51},
	{kAnimationFireballNW, 					3, 52, 54},
	{kAnimationArrowNE, 					3, 55, 55},
	{kAnimationArrowSE, 					3, 57, 57},
	{kAnimationArrowSW, 					3, 59, 59},
	{kAnimationArrowNW, 					3, 61, 61},
	{kAnimationFiredot, 					3, 63, -1},
	{kAnimationChestClosed, 				4,  0,  0},
	{kAnimationChestOpen, 					4,  1,  1},
	{kAnimationRing, 						4,  2,  2},
	{kAnimationDagger, 						4,  3,  3},
	{kAnimationSlainWarrior, 				4,  4,  4},
	{kAnimationIconCoffee, 					4,  5,  5},
	{kAnimationSpiderEgg, 					4,  6,  6},
	{kAnimationIconButtonYesInactive, 		4,  7,  7},
	{kAnimationIconButtonYesActive, 		4,  8,  8},
	{kAnimationIconButtonNoInactive, 		4,  9,  9},
	{kAnimationIconButtonNoActive, 			4, 10, 10},
	{kAnimationIconInventorySelect, 		4, 11, 11},
	{kAnimationIconNothing, 				4, 12, 12},
	{kAnimationIconSword, 					4, 13, 13},
	{kAnimationIconBottle, 					4, 14, 14},
	{kAnimationBottle, 						4, 15, 15},
	{kAnimationIconKey, 					4, 16, 16},
	{kAnimationIconWormSensor, 				4, 17, 17},
	{kAnimationIconBait, 					4, 18, 18},
	{kAnimationIconBook, 					4, 19, 19},
	{kAnimationIconDragonEgg, 				4, 20, 20},
	{kAnimationScroll, 						4, 21, 21},
	{kAnimationIconScroll, 					4, 22, 22},
	{kAnimationIconButtonOk, 				4, 23, 23},
	{kAnimationTable, 						4, 24, 24},
	{kAnimationIconMoneybag, 				4, 25, 25},
	{kAnimationIconMap, 					4, 26, 26},
	{kAnimationPitfall, 					4, 27, 27},
	{kAnimationSkeleton, 					4, 28, 28},
	{kAnimationIconSporesBag, 				4, 29, 29},
	{kAnimationSporesGrowing, 				4, 30, 36},
	{kAnimationRuby, 						4, 37, 38},
	{kAnimationThingy39, 					4, 39, 39},
	{kAnimationThingy40, 					4, 40, 40},
	{kAnimationIconRuby, 					4, 41, 41},
	{kAnimationIconRock, 					4, 42, 42},
	{kAnimationGold, 						4, 43, 43},
	{kAnimationIconLetter, 					4, 44, 44},
	{kAnimationMerchant, 					4, 45, 48},
	{kAnimationIconAmulet, 					4, 49, 49},
	{kAnimationIconGold, 					4, 50, 50},
	{kAnimationDragonEgg, 					4, 51, 51},
	{kAnimationShadowThingy52, 				4, 52, 52},
	{kAnimationIconBomb, 					4, 53, 53},
	{kAnimationIconRing, 					4, 54, 54},
	{kAnimationIconDagger, 					4, 55, 55},
	{kAnimationIconCarpet, 					4, 56, 56},
	{kAnimationAna, 						4, 57, 57},
	{kAnimationShadowThingy58, 				4, 58, 58},
	{kAnimationThingy59, 					4, 59, 59},
	{kAnimationFightingGaugeExhaustion, 	4, 60, 60},
	{kAnimationFightingGaugeLife, 			4, 61, 61},
	{kAnimationKoorsLight, 					4, 62, 62},
	{kAnimationFlashSmall, 					5,  0,  0},
	{kAnimationFlashBig, 					5,  1,  1},
	{kAnimationWizardAmuletUse1, 			6,  0,  0},
	{kAnimationWizardMortified, 			6,  1,  2},
	{kAnimationWizardAmuletUse2, 			6,  3,  3},
	{kAnimationWizardCharred, 				6,  4, -1}
};
static const AnimationInfo infoWizard[] = {
	// Animation for all 8 directions with same sprite index offset
	{kAnimationWizardWalking, 			3,  0,  4},
	{kAnimationWizardStaff, 			0,  5,  5},
	{kAnimationWizardDodgeRight, 		0,  6,  6},
	{kAnimationWizardDodgeBack, 		0,  7,  7},
	{kAnimationWizardDodgeLeft, 		0,  8,  8},
	{kAnimationWizardStab, 				0,  9,  9},
	{kAnimationWizard10to12, 			0, 10, 12},
	{kAnimationWizardSlashRightToLeft, 	0, 13, 17},
	{kAnimationWizardSlash, 			0, 18, 18},
	{kAnimationWizardSlashLeftToRight, 	0, 19, 20},
	{kAnimationWizardBarrelRaft, 		0, 21, 23},
	{kAnimationWizardCarpet, 			0, 24, 24},
	{kAnimationWizard25to26, 			0, 25, 26}
};
static const AnimationInfo infoGoblin[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoTroll[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoBigWizard[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoBigGoblin[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoBigTroll[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoBigSpider[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoBigUlindor[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoDragon[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoRescue[] = { // Cache8
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel1[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel1N8[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel1T5[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel1T7[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel2[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel2N3[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel2N5[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel2T4[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel3[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel4[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel5[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel6[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel7P1[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel7P2[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel8P1[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel8P2[] = {
	{kAnimationWizardDeathSonic, 	0, 0, -1},
	{kAnimationReaper, 				1, 0, -1},
	{kAnimationNursingGoblin, 		2, 0,  0},
	{kAnimationDragonFire1, 		3, 0,  8},
	{kAnimationDragonFire2, 		3, 9, -1},
	{kAnimationWizardBeheaded, 		4, 0, -1},
};
static const AnimationInfo infoLevel123[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel134[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel147[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};
static const AnimationInfo infoLevel235[] = {
	{kAnimationGoblinDummy, 0, 0, -1}
};

struct FileMap {
	const AnimationInfo *_info;
	int _size;
	const char *_filename;
};
static const FileMap fileMap[] = {
	{infoGeneral1,	ARRAYSIZE(infoGeneral1),	"GENERAL1.ANM"},
	{infoGeneral2,	ARRAYSIZE(infoGeneral2),	"GENERAL2.ANM"},
	{infoWizard,	ARRAYSIZE(infoWizard),		"WIZARD.ANM"},
	{infoGoblin,	ARRAYSIZE(infoGoblin),		"GOBLIN.ANM"},
	{infoTroll,		ARRAYSIZE(infoTroll),		"TROLL.ANM"},
	{infoBigWizard,	ARRAYSIZE(infoBigWizard),	"BIGWIZ.ANM"},
	{infoBigGoblin,	ARRAYSIZE(infoBigGoblin),	"BIGGOB.ANM"},
	{infoBigTroll,	ARRAYSIZE(infoBigTroll),	"BIGTROL.ANM"},
	{infoBigSpider,	ARRAYSIZE(infoBigSpider),	"BIGSPID.ANM"},
	{infoBigUlindor,ARRAYSIZE(infoBigUlindor),	"BIGULIN.ANM"},
	{infoDragon,	ARRAYSIZE(infoDragon),		"DRAGON.ANM"},
	{infoRescue,	ARRAYSIZE(infoRescue),		"CACHE8.ANM"},
	{infoLevel1,	ARRAYSIZE(infoLevel1),		"LEVEL1.ANM"},
	{infoLevel1N8,	ARRAYSIZE(infoLevel1N8),	"LEVEL1N8.ANM"},
	{infoLevel1T5,	ARRAYSIZE(infoLevel1T5),	"LEVEL1T5.ANM"},
	{infoLevel1T7,	ARRAYSIZE(infoLevel1T7),	"LEVEL1T7.ANM"},
	{infoLevel2,	ARRAYSIZE(infoLevel2),		"LEVEL2.ANM"},
	{infoLevel2N3,	ARRAYSIZE(infoLevel2N3),	"LEVEL2N3.ANM"},
	{infoLevel2N5,	ARRAYSIZE(infoLevel2N5),	"LEVEL2N5.ANM"},
	{infoLevel2T4,	ARRAYSIZE(infoLevel2T4),	"LEVEL2T4.ANM"},
	{infoLevel3,	ARRAYSIZE(infoLevel3),		"LEVEL3.ANM"},
	{infoLevel4,	ARRAYSIZE(infoLevel4),		"LEVEL4.ANM"},
	{infoLevel5,	ARRAYSIZE(infoLevel5),		"LEVEL5.ANM"},
	{infoLevel6,	ARRAYSIZE(infoLevel6),		"LEVEL6.ANM"},
	{infoLevel7P1,	ARRAYSIZE(infoLevel7P1),	"LEVEL7P1.ANM"},
	{infoLevel7P2,	ARRAYSIZE(infoLevel7P2),	"LEVEL7P2.ANM"},
	{infoLevel8P1,	ARRAYSIZE(infoLevel8P1),	"LEVEL8P1.ANM"},
	{infoLevel8P2,	ARRAYSIZE(infoLevel8P2),	"LEVEL8P2.ANM"},
	{infoLevel123,	ARRAYSIZE(infoLevel123),	"LEVEL123.ANM"},
	{infoLevel134,	ARRAYSIZE(infoLevel134),	"LEVEL134.ANM"},
	{infoLevel147,	ARRAYSIZE(infoLevel147),	"LEVEL147.ANM"},
	{infoLevel235,	ARRAYSIZE(infoLevel235),	"LEVEL235.ANM"}
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

	file.skip(5);	// skip lib signature "EALIB"
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
			convertAnimation(prevElement);
		else if (Common::matchString(prevElement->_name, "MAZE.CMP")){
			// TODO
		}

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

Common::Error ResourceManager::convertAnimation(AssetFile *assetFile) {
	int decodeSize;
	byte *buffer = decodeFile(assetFile->_data.get(), assetFile->_size, &decodeSize);
	Common::MemoryReadStream stream(buffer, decodeSize, DisposeAfterUse::YES);

	int id = 0;
	while (id < ARRAYSIZE(fileMap) && !Common::matchString(assetFile->_name, fileMap[id]._filename))
		++id;
	if (id >= ARRAYSIZE(fileMap))
		return Common::Error(Common::kReadingFailed, "Cannot find requested ANM file");

	Common::Array<AnimationHeader> header;
	Common::Array<Common::Array<int> > spriteOffset;
	const AnimationInfo *info = fileMap[id]._info;
	int headerSize = stream.readUint16LE();
	stream.seek(0);
	const int kSizeofAnimationHeader = 8;
	int numAnimations = headerSize / kSizeofAnimationHeader;
	header.resize(numAnimations);
	spriteOffset.resize(numAnimations);

	for (int animation = 0; animation < numAnimations; ++animation) {
		header[animation]._offsetToSpriteOffsetList = stream.readUint16LE();
		header[animation]._numFrames = stream.readUint16LE();
		header[animation]._centerX = stream.readUint16LE();
		header[animation]._centerY = stream.readUint16LE();

		int streamPos = stream.pos();
		stream.seek(header[animation]._offsetToSpriteOffsetList);
		spriteOffset[animation].resize(header[animation]._numFrames);
		for (int frame = 0; frame < header[animation]._numFrames; ++frame) {
			spriteOffset[animation][frame] = stream.readUint16LE();
		}
		stream.seek(streamPos);
	}

	// Iterate over all animations defined and save in _animationContainer
	for (int animation = 0; animation < fileMap[id]._size; ++animation) {
		Animation *container = &_animationContainer[info[animation]._id];
		AnimationHeader *currentHeader = &header[info[animation]._animation];
		int numFrames = 0;
		if (info[animation]._frameEnd == -1)
			numFrames = currentHeader->_numFrames - info[animation]._frameStart;
		else
			numFrames = info[animation]._frameEnd - info[animation]._frameStart + 1;

		container->setInfo(currentHeader->_centerX, currentHeader->_centerY, numFrames);

		for (int i = 0; i < numFrames; ++i) {
			int frame = info[animation]._frameStart + i;
			stream.seek(spriteOffset[info[animation]._animation][frame]);
			int spriteX = stream.readByte();
			int spriteY = stream.readByte();
			int spriteWidth = stream.readByte();
			int spriteHeight = stream.readByte();
			int remap = stream.readByte();
			Common::Array<int> pixelWidth(spriteHeight);
			Common::Array<int> pixelPosOffset(spriteHeight);

			for (int y = 0; y < spriteHeight; ++y) {
				pixelWidth[y] = stream.readByte();
				pixelPosOffset[y] = stream.readByte();
				if (pixelWidth[y] + pixelPosOffset[y] > spriteWidth)
					spriteWidth = pixelWidth[y] + pixelPosOffset[y];
			}

			byte *pixelBuffer = new byte[spriteWidth * spriteHeight];
			Common::Array<byte> rawPixelBuffer(spriteWidth * spriteHeight);
			memset(pixelBuffer, 0, spriteWidth * spriteHeight);
			stream.read(&rawPixelBuffer[0], spriteWidth * spriteHeight);
			int currentPixel = 0;
			for (int y = 0; y < spriteHeight; ++y) {
				for (int x = 0; x < pixelWidth[y]; ++x) {
					int pos = y * spriteWidth + x + pixelPosOffset[y];
					assert(pos < spriteWidth * spriteHeight);
					if (currentPixel & 1)
						pixelBuffer[pos] = rawPixelBuffer[currentPixel >> 1] & 0x0F;
					else
						pixelBuffer[pos] = (rawPixelBuffer[currentPixel >> 1] >> 4) & 0x0F;

					++currentPixel;
				}
			}
			container->setFrame(i, spriteX, spriteY, spriteWidth, spriteHeight, pixelBuffer);
		}
	}

	return Common::kNoError;
}

const MusicData *ResourceManager::getMusic(MusicId id) {
	return &_musicContainer[id];
}

const byte *ResourceManager::getImage(ImageId id) {
	return _imageContainer[id].get();
}

const Animation *ResourceManager::getAnimation(AnimationId id) {
	return &_animationContainer[id];
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

void Animation::setFrame(int frame, int x, int y, int width, int height, byte *buffer) {
	Sprite *sprite = &_data[frame];
	sprite->_x = x;
	sprite->_y = y;
	sprite->_width = width;
	sprite->_height = height;
	sprite->_data = buffer;
}

void Animation::setInfo(int centerX, int centerY, int numFrames) {
	_centerX = centerX;
	_centerY = centerY;
	_numFrames = numFrames;
	_data.resize(numFrames);
}

const Sprite *Animation::getFrame(int frame) const {
	return &_data[frame];
}

Common::Point Animation::getPos(int frame) const {
	return Common::Point(_data[frame]._x, _data[frame]._y);
}

Common::Point Animation::getCenter() const {
	return Common::Point(_centerX, _centerY);
}

int Animation::getNumFrames() const {
	return _numFrames;
}

}
