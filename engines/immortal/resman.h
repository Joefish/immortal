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
#include "common/rect.h"

namespace Immortal {

enum FileId {
//	kFileTTT00,
//	kFileTTT01,
//	kFileTTT02,
//	kFileTTT03,
//	kFileTTT04,
//	kFileTTT05,
//	kFileTTT06,
//	kFileTTT07,
//	kFileTTT08,
//	kFileTTT09,
//	kFileTTT10,
//	kFileTTT11,
//	kFileTTT12,
//	kFileTTT13,
//	kFileTTT14,
//	kFileTTT15,
//	kFileTTT16,
//	kFileTTT17,
//	kFileTTT18,
//	kFileTTT19,
//	kFileTTT20,
//	kFileMaze,
//	kFileEgaTitle,
//	kFileVgaTitle,
//	kFileWindows,
	kFileGeneral1,
	kFileGeneral2,
	kFileWizard,
	kFileGoblin,
	kFileTroll,
	kFileBigWizard,
	kFileBigGoblin,
	kFileBigTroll,
	kFileBigSpider,
	kFileBigUlindor,
	kFileDragon,
	kFileCache8,
	kFileLevel1,
	kFileLevel1N8,
	kFileLevel1T5,
	kFileLevel1T7,
	kFileLevel2,
	kFileLevel2N3,
	kFileLevel2N5,
	kFileLevel2T4,
	kFileLevel3,
	kFileLevel4,
	kFileLevel5,
	kFileLevel6,
	kFileLevel7P1,
	kFileLevel7P2,
	kFileLevel8P1,
	kFileLevel8P2,
	kFileLevel123,
	kFileLevel134,
	kFileLevel147,
	kFileLevel235,
	kFileAnimationNum
};

enum MusicId {
	kMusic00,
	kMusic01,
	kMusicSleeping,
	kMusic03,
	kMusic04,
	kMusic05,
	kMusic06,
	kMusic07,
	kMusic08,
	kMusic09,
	kMusic10,
	kMusic11,
	kMusicLevelCompleted,
	kMusic13,
	kMusic14,
	kMusicBattle,
	kMusicDied,
	kMusic17,
	kMusic18,
	kMusicIntro,
	kMusic20,
	kMusicNum
};

enum ImageId {
	kImageTitleScreen,
	kImageScreenFrame,
	kImageNum
};

// TODO: Check all sprites as files from source differ from release
enum AnimationId {
	kAnimationNone = -1,
	// GENERAL1
	kAnimationTunnelFalling,
	kAnimationTorchFire,
	kAnimationWoodenDoor,
	kAnimationSteelDoor,
	kAnimationLadder, // single sprite
	kAnimationLadderClimbing,
	kAnimationTunnel,
	kAnimationTunnelDescending,
	kAnimationWizardIncinerate,
	kAnimationTunnelOpening,

	// GENERAL2
	kAnimationSymbols, // Alphabet + symbols [0;122]
	kAnimationShadowBezierTopLeft,
	kAnimationShadowBezierTopRight,
	kAnimationShadowTriangleLightLeft,
	kAnimationShadowTriangleLightRight,
	kAnimationShadowTriangleDarkLeft,
	kAnimationShadowTriangleDarkRight,
	// Effects
	kAnimationBloodLeft,
	kAnimationBloodRight,
	kAnimationSparksLeft,
	kAnimationSparksRight,
	kAnimationSparksCenter,
	kAnimationSparksSmall,
	kAnimationFireballN,
	kAnimationFireballNE,
	kAnimationFireballE,
	kAnimationFireballSE,
	kAnimationFireballS,
	kAnimationFireballSW,
	kAnimationFireballW,
	kAnimationFireballNW,
	kAnimationArrowNE,
	kAnimationArrowSE,
	kAnimationArrowSW,
	kAnimationArrowNW,
	kAnimationFiredot,
	// Icons
	kAnimationChestClosed,
	kAnimationChestOpen,
	kAnimationRing,
	kAnimationDagger,
	kAnimationSlainWarrior,
	kAnimationIconCoffee,
	kAnimationSpiderEgg,
	kAnimationIconButtonYesInactive,
	kAnimationIconButtonYesActive,
	kAnimationIconButtonNoInactive,
	kAnimationIconButtonNoActive,
	kAnimationIconInventorySelect,
	kAnimationIconInventorySelectBlack,
	kAnimationIconSword,
	kAnimationIconBottle,
	kAnimationBottle,
	kAnimationIconKey,
	kAnimationIconWormSensor,
	kAnimationIconBait,
	kAnimationIconBook,
	kAnimationIconDragonEgg,
	kAnimationScroll,
	kAnimationIconScroll,
	kAnimationIconButtonOk,
	kAnimationTable,
	kAnimationIconMoneybag,
	kAnimationIconMap,
	kAnimationTrapdoor,
	kAnimationSkeleton,
	kAnimationIconSporesBag,
	kAnimationSporesGrowing,
	kAnimationRuby,
	kAnimationStone,
	kAnimationGreenStone,
	kAnimationIconRuby,
	kAnimationIconStone,
	kAnimationGold,
	kAnimationIconLetter,
	kAnimationMerchant,
	kAnimationIconAmulet,
	kAnimationIconGold,
	kAnimationDragonEgg,
	kAnimationShadowThingy52,
	kAnimationIconBomb,
	kAnimationIconRing,
	kAnimationIconDagger,
	kAnimationIconCarpet,
	kAnimationAna,
	kAnimationAnaCave,
	kAnimationThingy59,
	kAnimationFightingGaugeExhaustion,
	kAnimationFightingGaugeLife,
	kAnimationKoorsLight,
	kAnimationFlashSmall,
	kAnimationFlashBig,
	kAnimationWizardAmuletUse1,
	kAnimationWizardMortified,
	kAnimationWizardAmuletUse2,
	kAnimationWizardCharred,

	// WIZARD -- Animations 0-7 directions
	kAnimationWizardWalking,
	kAnimationWizardStaff,
	kAnimationWizardDodgeRight,
	kAnimationWizardDodgeBack,
	kAnimationWizardDodgeLeft,
	kAnimationWizardStab,
	kAnimationWizard10to12,
	kAnimationWizardSlashRightToLeft,
	kAnimationWizardSlash,
	kAnimationWizardSlashLeftToRight,
	kAnimationWizardBarrelRaft,
	kAnimationWizardCarpet,
	kAnimationWizard25to26,

	// GOBLIN
	kAnimationGoblinDummy,

	// TROLL
	kAnimationTrollDummy,

	// BIGWIZ
	kAnimationBigWizardDummy,

	// BIGGOB
	kAnimationBigGoblinDummy,

	// BIGTROL
	kAnimationBigTrollDummy,

	// BIGSPID
	kAnimationBigSpiderDummy,

	// BIGULIN
	kAnimationBigUlindorDummy,

	// DRAGON
	kAnimationDragonDummy,

	// CACHE8
	kAnimationRescueAna,
	kAnimationRescueGoblin,

	// LEVEL1
	kAnimationLevel1Dummy,

	// LEVEL1N8
	kAnimationLevel1N8Dummy,

	// LEVEL1T5
	kAnimationLevel1T5Dummy,

	// LEVEL1T7
	kAnimationLevel1T7Dummy,

	// LEVEL2
	kAnimationLevel2Dummy,

	// LEVEL2N3
	kAnimationLevel2N3Dummy,

	// LEVEL2N5
	kAnimationLevel2N5Dummy,

	// LEVEL2T4
	kAnimationLevel2T4Dummy,

	// LEVEL3
	kAnimationLevel3Dummy,

	// LEVEL4
	kAnimationLevel4Dummy,

	// LEVEL5
	kAnimationLevel5Dummy,

	// LEVEL6
	kAnimationLevel6Dummy,

	// LEVEL7P1
	kAnimationLevel7P1Dummy,

	// LEVEL7P2
	kAnimationLevel7P2Dummy,

	// LEVEL8P1
	kAnimationLevel8P1Dummy,

	// LEVEL8P2
	kAnimationWizardDeathSonic,
	kAnimationReaper,
	kAnimationNursingGoblin,
	kAnimationDragonFire1,
	kAnimationDragonFire2,
	kAnimationWizardBeheaded,

	// LEVEL123
	kAnimationLevel123Dummy,

	// LEVEL134
	kAnimationLevel134Dummy,

	// LEVEL147
	kAnimationLevel147Dummy,

	// LEVEL235
	kAnimationLevel235Dummy,

	kAnimationNum
};

struct MusicData {
	Common::ScopedPtr<byte> _data;
	int _size;
	bool _loop;
	byte _volume[16];
	byte _adlibToMidiChannelTable[9];
};

struct Sprite {
	Sprite();
	~Sprite();

	int _x;
	int _y;
	int _width;
	int _height;
	int _minScanlineOffset;
	int _remap;
	Common::Array<int> _scanlineWidth;
	Common::Array<int> _scanlinePosOffset;
	byte *_data;
};

class Animation {
public:
	Common::Point getCenter() const;
	Common::Point getPos(int frame) const;
	const Sprite *getFrame(int frame) const;
	int getNumFrames() const;
	void setFrame(int frame, int x, int y, int width, int height, byte *buffer);
	void setInfo(int centerX, int centerY, int numFrames);

private:
	int _centerX;
	int _centerY;
	int _numFrames;
	Common::Array<Sprite> _data;
};

struct Map {
	static const int _numTiles = 146;
	static const int _numStamps = 1892;	// 8x8 tiles
	static const int _tileMapWidth = 20;
	static const int _tileMapHeight = 128;
	static const int _stampsPerViewportW = 34;
	static const int _stampsPerViewportH = 18;
	static const int _stampWidth = 8;
	static const int _stampHeight = 8;
	static const int _stampStride = _stampWidth * _stampHeight / 2;
	static const int _stampsPerTileW = 64 / _stampWidth;
	static const int _stampsPerTileH = 32 / _stampHeight;

	byte _tileMap[_tileMapHeight][_tileMapWidth];
	uint16 _stampMap[_numTiles][_stampsPerTileW * _stampsPerTileH];
	byte _bitmap[_numStamps][_stampStride];
};


class ResourceManager {
struct AssetFile {
	char _name[13];
	int _size;
	int _offset;
	Common::ScopedPtr<byte> _data;
};

public:
	ResourceManager();
	const byte *getImage(ImageId id);
	const MusicData *getMusic(MusicId id);
	const Animation *getAnimation(AnimationId id);
	const Map *getMap();

private:
	Common::Error loadLibrary(const char *filename);
	Common::Error convertImage(AssetFile *assetFile);
	Common::Error convertAnimation(AssetFile *assetFile);
	Common::Error convertMusic(AssetFile *assetFile);
	Common::Error convertMap(AssetFile *assetFile);

private:
	Map _mazeMap;
	Common::ScopedPtr<byte> _imageContainer[kImageNum];
	Animation _animationContainer[kAnimationNum];
	MusicData _musicContainer[kMusicNum];
};

}

#endif
