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

#include "immortal/animation.h"

namespace Immortal {

// INFO:
// Constants in AnimationInfo differ from the source because the compression
// algorithm apparently changed mid development and also changed the order
// of the sprites. Thus before drawing a sprite there's a lookup table that
// adjusts the values accordingly...

// TODO: Remove once Animation structure is implemented (current level data?)
static const int placeholder = 0;

static const int mordamirPhantomFrames[] = {
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	17, 16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,
	 1,  0, -1
};
static const AnimationInfo mordamirPhantom = {
	kAnimationMordamirPhantom, kFileLevel1, 3, 1, mordamirPhantomFrames
};

static const int spikeSmallFrames[] = {
	 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	-1
};
static const AnimationInfo spikeSmall = {
	kAnimationSpikeSmall, kFileLevel3, 2, 1, spikeSmallFrames
};

static const int wizardShrinkFrames[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1
};
static const AnimationInfo wizardShrink = {
	 kAnimationWizardShrink, kFileLevel5, 12, 1, wizardShrinkFrames
};

static const int wizardGrowFrames[] = {
	8, 7, 6, 5, 4, 3, 2, 1, 0, -1
};
static const AnimationInfo wizardGrow = {
	kAnimationWizardGrow, kFileLevel5, 12, 1, wizardGrowFrames
};


static const int attackShortFrames[] = {
	0, 1, 2, 3, 4, 4, 4, 4, 5, 6, 7, 7, 7, 7, 7, 7,
	7, 0, -1
};
static const AnimationInfo attackShort = {
	kAnimationAttackShort, (FileId)placeholder, placeholder, 1, attackShortFrames
};

static const int attackLongFrames[] = {
	 0,  1,  2,  2,  2,  1,  0,  0,  1,  2,  3,  4,  4,  4,  4,  4,
	 5,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  9,
	10, 10, 10, 10,  8,  8,  8,  9, 10, 10, 10,  9,  8,  8,  8,  9,
	10, 10, 10,  9,  8,  8,  8,  8,  9, 10, 10, 10,  9,  8,  0, -1
};
static const AnimationInfo attackLong = {
	kAnimationAttackLong, (FileId)placeholder, placeholder, 1, attackLongFrames
};

static const int attackWaitFrames[] = {
	0, 0, 0, 0, 0, 0, 0, -1
};
static const AnimationInfo attackWait = {
	kAnimationAttackWait, (FileId)placeholder, placeholder, 1, attackWaitFrames
};

static const int mordamirIncineratedFrames[] = {
	12, 13, 13, 13, 13, 13, 14, 15, 16, 17, 18, 19, 19, 19, 19, 19,
	19, 19, 19, 19, 18, 17, 16, 15, 14, 13, 12,  0, -1
};
static const AnimationInfo mordamirIncinerated = {
	kAnimationMordamirIncinerated, (FileId)placeholder, placeholder, 1, mordamirIncineratedFrames
};

static const int recoilFrames[] = {
	 0,  1,  2, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,  2,  1,
	 0, 12, 13, -1
};
static const AnimationInfo recoil = {
	kAnimationRecoil, (FileId)placeholder, placeholder, 1, recoilFrames
};

static const int mordamirAppearsFrames[] = {
	12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0, -1
};
static const AnimationInfo mordamirAppears = {
	kAnimationMordamirAppears, (FileId)placeholder, placeholder, 1, mordamirAppearsFrames
};

static const int mordamirLight0Frames[] = {
	 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,  0,  0,  0,  0,  0,
	 0,  0,  0,  0, -1
};
static const AnimationInfo mordamirLight0 = {
	kAnimationMordamirLight0, (FileId)placeholder, placeholder, 1, mordamirLight0Frames
};

static const int mordamirLight1Frames[] = {
	 1,  2,  3,  4,  5,  6,  7,  8,  9, 10,  8,  9, 10,  8,  9, 10,
	11,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1
};
static const AnimationInfo mordamirLight1 = {
	kAnimationMordamirLight1, (FileId)placeholder, placeholder, 1, mordamirLight1Frames
};

// amulet from wizard to mordamir
static const int mordamirTractorFrames[] = {
	28, 29, 30, 31, 31, 31, 31, 31, 31, 32, 0, -1
};
static const AnimationInfo mordamirTractor = {
	kAnimationMordamirTractorAmulet, (FileId)placeholder, placeholder, 1, mordamirTractorFrames
};

static const int mordamirAttackSonicFrames[] = {
	56, 56, 56, 56, 56, 56, 56, 57, 58, 59, 60, 0, -1
};
static const AnimationInfo mordamirAttackSonic = {
	kAnimationMordamirAttackSonic, (FileId)placeholder, placeholder, 1, mordamirAttackSonicFrames
};

static const int mordamirWraithFrames[] = {
	53, 53, 53, 54, 54, 54, 55, 55, 55, 0, -1
};
static const AnimationInfo mordamirWraith = {
	kAnimationMordamirAttackWraith, (FileId)placeholder, placeholder, 1, mordamirWraithFrames
};

static const int mordamirWaitFrames[] = {
	0, 0, 0, 0, 0, 0, -1
};
static const AnimationInfo mordamirWait = {
	kAnimationMordamirWait, (FileId)placeholder, placeholder, 1, mordamirWaitFrames
};

// moradmir holds amulet
static const int mordamirTalkFrames[] = {
	 0, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
	31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
	31, 31, 31, 31, 31, 31, 31, 31, -1
};
static const AnimationInfo mordamirTalk = {
	kAnimationMordamirTalk, (FileId)placeholder, placeholder, 1, mordamirTalkFrames
};

// wizard tractor amulet, mordamir incinerated and falls
static const int mordamirDeathFrames[] = {
	31, 30, 29, 28,  0,  0,  0,  0,  0,  0,  0,  0,  0, 35, 33, 34,
	35, 33, 34, 35, 33, 34, 35, 33, 34, 35, 36, 37, 38, 39, 40, 41,
	42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, -2, -1
};
static const AnimationInfo mordamirDeath = {
	kAnimationMordamirDeath, (FileId)placeholder, placeholder, 1, mordamirDeathFrames
};

static const int postLightFrames[] = {
	0, 0, 0, 0, 0, 0, -1
};
static const AnimationInfo postLight = {
	kAnimationPostLight, (FileId)placeholder, placeholder, 1, postLightFrames
};

// puts amulet away
static const int postTalkFrames[] = {
	32, 0, -1
};
static const AnimationInfo postTalk = {
	kAnimationPostTalk, (FileId)placeholder, placeholder, 1, postTalkFrames
};

static const int lightningFrames[] = {
	0, 1, 2, 3, 4, 5, 6, -1
};
static const AnimationInfo lightning = {
	kAnimationLightning, kFileLevel8P1, 2, 1, lightningFrames
};

static const int wizardFire0Frames[] = {
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, -1
};
static const AnimationInfo wizardFire0 = {
	kAnimationWizardFire0, kFileLevel8P2, 3, 1, wizardFire0Frames
};

static const int wizardFire1Frames[] = {
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-2, -2,  9, 10, 11, 12, 13, 14, 15, 16, 11, 12, 13, 14, 15, 17,
	18, 19, 20, -1
};
static const AnimationInfo wizardFire1 = {
	kAnimationWizardFire1, kFileLevel8P2, 3, 1, wizardFire1Frames
};

static const int mordamirFireFrames[] = {
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,  0,  1,  2,  3,  4,
	 2,  3,  4,  2,  3,  5,  6,  7,  8, -1
};
static const AnimationInfo mordamirFire = {
	kAnimationMordamirFire, kFileLevel8P2, 3, 1, mordamirFireFrames
};

static const int norlacBubbles0Frames[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, -1
};
static const AnimationInfo norlacBubbles0 = {
	kAnimationNorlacBubbles0, kFileLevel7P2, 3, 1, norlacBubbles0Frames
};

static const int norlacBubbles1Frames[] = {
	15, 16, 17, 18, 19, 20, 21, 22, -1
};
static const AnimationInfo norlacBubbles1 = {
	kAnimationNorlacBubbles1, kFileLevel7P2, 3, 1, norlacBubbles1Frames
};

static const int bloodSplatterLeftFrames[] = {
	0, 1, 2, -1
};
static const AnimationInfo bloodSplatter = {
	kAnimationBloodSplatterLeft, kFileGeneral2, 3, 1,bloodSplatterLeftFrames
};

static const int bloodSplatterRightFrames[] = {
	3, 4, 5, -1
};
static const AnimationInfo bloodSplatterRight = {
	kAnimationBloodSplatterRight, kFileGeneral2, 3, 1, bloodSplatterRightFrames
};

static const int wizardSparksLeftFrames[] = {
	6, 7, 8, 9, 10, -1
};
static const AnimationInfo wizardSparksLeft = {
	kAnimationWizardSparksLeft, kFileGeneral2, 3, 1, wizardSparksLeftFrames
};

static const int wizardSparksRightFrames[] = {
	11, 12, 13, 14, 15, -1
};
static const AnimationInfo wizardSparksRight = {
	kAnimationWizardSparksRight, kFileGeneral2, 3, 1, wizardSparksRightFrames
};

static const int wizardSparksCenterFrames[] = {
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, -1
};
static const AnimationInfo wizardSparksCenter = {
	kAnimationWizardSparksCenter, kFileGeneral2, 3, 1, wizardSparksCenterFrames
};

static const int turretBarrelLeftFrames[] = {
	0, 1, 2, 3, 4, -1
};
static const AnimationInfo turretBarrelLeft = {
	kAnimationTurretBarrelLeft, kFileLevel134, 0, 1, turretBarrelLeftFrames
};

static const int turretBarrelRightFrames[] = {
	5, 6, 7, 8, 9, -1
};
static const AnimationInfo turretBarrelRight = {
	kAnimationTurretBarrelRight, kFileLevel134, 0, 1, turretBarrelRightFrames
};

static const int turretSkullRightFrames[] = {
	10,  11,  12,  13,  14,  -1
};
static const AnimationInfo turretSkullRight = {
	kAnimationTurretSkullRight, kFileLevel134, 0, 1, turretSkullRightFrames
};

static const int turretSkullLeftFrames[] = {
	15,  16,  17,  18,  19,  -1
};
static const AnimationInfo turretSkullLeft = {
	kAnimationTurretSkullLeft, kFileLevel134, 0, 1, turretSkullLeftFrames
};

static const int anaDisappearsFrames[] = {
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, -1
};
static const AnimationInfo anaDisappears = {
	kAnimationAnaDisappears, kFileLevel4, 0, 1, anaDisappearsFrames
};

static const int anaGlimpseFrames[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1
};
static const AnimationInfo anaGlimpse = {
	kAnimationAnaGlimpse, kFileLevel2T4, 0, 1, mordamirFireFrames
};

static const int knifeFrames[] = {
	 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
	 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3,
	-1
};
static const AnimationInfo knife = {
	kAnimationKnife, kFileLevel2T4, 1, 0, mordamirFireFrames
};

static const int fireball0Frames[] = {
	31, 32, 33, 32, 34, 35, 36, 35, 37, 38, 39, 38, 40, 41, 42, 41,
	43, 44, 45, 44, 46, 47, 48, 47, 49, 50, 51, 50, 52, 53, 54, 53,
	-1
};
static const AnimationInfo fireball0 = {
	kAnimationFireball0, kFileGeneral2, 3, 0, mordamirFireFrames
};

static const int arrowFrames[] = {
	55, -1
};
static const AnimationInfo arrow = {
	kAnimationArrow, kFileGeneral2, 3, 0, mordamirFireFrames
};

static const int miniBallFrames[] = {
	63, 64, 65, 66, 63, 64, 65, 66, 63, 64, 65, 66, 63, 64, 65, 66,
	63, 64, 65, 66, 63, 64, 65, 66, 63, 64, 65, 66, 63, 64, 65, 66,
	-1
};
static const AnimationInfo miniBall = {
	kAnimationMiniBall, kFileGeneral2, 3, 0, mordamirFireFrames
};

static const int bigSparksFrames[] = {
	0, 1, 0, -1
};
static const AnimationInfo bigSparks = {
	kAnimationBigSparks, kFileGeneral2, 5, 1, mordamirFireFrames
};


static const int flameFlicker0Frames[] = {
	0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 2, 1, -1
};
static const AnimationInfo flameFlicker0 = {
	kAnimationFlameFlicker0, kFileGeneral1, 1, 1, mordamirFireFrames
};

static const int flameFlicker1Frames[] = {
	0, 0, 1, 2, 13, 14, 15, 16, 4, 2, 3, -1
};
static const AnimationInfo flameFlicker1 = {
	kAnimationFlameFlicker1, kFileGeneral1, 1, 1, mordamirFireFrames
};

static const int flameFlicker2Frames[] = {
	0, 1, 2, 3, 20, 21, 22, 23, 24, 25, 26, 27, 5, 4, 3, -1
};
static const AnimationInfo flameFlicker2 = {
	kAnimationFlameFlicker2, kFileGeneral1, 1, 1, mordamirFireFrames
};

static const int flameNormal0Frames[] = {
	0, 1, 2, 3, -1
};
static const AnimationInfo flameNormal0 = {
	kAnimationFlameNormal0, kFileGeneral1, 1, 1, mordamirFireFrames
};

static const int flameNormal1Frames[] = {
	0, 17, 18, 19, 3, -1
};
static const AnimationInfo flameNormal1 = {
	kAnimationFlameNormal1, kFileGeneral1, 1, 1, mordamirFireFrames
};

static const int flameNormal2Frames[] = {
	0, 1, -1
};
static const AnimationInfo flameNormal2 = {
	kAnimationFlameNormal2, kFileGeneral1, 1, 1, mordamirFireFrames
};

static const int flameOutFrames[] = {
	28, 28, 28, 28, -1
};
static const AnimationInfo flameOut = {
	kAnimationFlameOut, kFileGeneral1, 1, 1, mordamirFireFrames
};

static const int flameCandleFlickerFrames[] = {
	15, 16, 15, 16, 15, 16, 16, -1
};
static const AnimationInfo flameCandleFlicker = {
	kAnimationFlameCandleFlicker, kFileLevel1, 1, 1, mordamirFireFrames
};

static const int flameCandleLeapFrames[] = {
	25, 26, 27, 28, 29, 30, 31, -1
};
static const AnimationInfo flameCandleLeap = {
	kAnimationFlameCandleLeap, kFileLevel1, 1, 1, mordamirFireFrames
};

static const int flameCandleJumpFrames[] = {
	17, 18, 19, 20, -1
};
static const AnimationInfo flameCandleJump = {
	kAnimationFlameCandleJump, kFileLevel1, 1, 1, mordamirFireFrames
};

static const int flameCandleSwayFrames[] = {
	21, 22, 23, 24, -1
};
static const AnimationInfo flameCandleSway= {
	kAnimationFlameCandleSway, kFileLevel1, 1, 1, mordamirFireFrames
};

static const int flameCandleBurstFrames[] = {
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
	11, 12, 13, 14, -1
};
static const AnimationInfo flameCandleBurst = {
	kAnimationFlameCandleBurst, kFileLevel1, 1, 1, mordamirFireFrames
};

static const int floorTileSinkFrames[] = {
	0, 1, 2, 3, 3, 3, 3, 4, 5, 6, -1
};
static const AnimationInfo floorTileSink = {
	kAnimationFloorTileSink, kFileLevel1, 0, 1, mordamirFireFrames
};

static const int norlacDownFrames[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, -1
};
static const AnimationInfo norlacDown = {
	kAnimationNorlacDown, kFileLevel7P1, 1, 1, mordamirFireFrames
};

}
