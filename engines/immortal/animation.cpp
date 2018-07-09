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
	kAnimationWorm, kFileLevel1T5, 2, 1, spikeSmallFrames
};

// TODO: Find file that has shrinking animation
static const int shrinkFrames[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1
};
static const AnimationInfo shrink = {
	// TODO: file not found for shrink animation
	// kAnimationShrink, kfile , 9, 1, shrinkFrames
};

static const int shrinkReverseFrames[] = {
	8, 7, 6, 5, 4, 3, 2, 1, 0, -1
};
static const AnimationInfo shrinkReverse = {
	// TODO: file not found for shrink animation
//	kAnimationWizardGrow, kfile , 9, 1, shrinkReverseFrames
};


static const int attackShortFrames[] = {
	0, 1, 2, 3, 4, 4, 4, 4, 5, 6, 7, 7, 7, 7, 7, 7,
	7, 0, -1
};
static const AnimationInfo attackShort = {
	// TODO: file not found for shrink animation
	kAnimationAttackShort, (FileId)placeholder, placeholder, 1, attackShortFrames
};

static const int attackLongFrames[] = {
	 0,  1,  2,  2,  2,  1,  0,  0,  1,  2,  3,  4,  4,  4,  4,  4,
	 5,  6,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  9,
	10, 10, 10, 10,  8,  8,  8,  9, 10, 10, 10,  9,  8,  8,  8,  9,
	10, 10, 10,  9,  8,  8,  8,  8,  9, 10, 10, 10,  9,  8,  0, -1
};
static const AnimationInfo attackLong = {
	// TODO: file not found for shrink animation
	kAnimationAttackLong, (FileId)placeholder, placeholder, 1, attackLongFrames
};

static const int attackWaitFrames[] = {
	0, 0, 0, 0, 0, 0, 0, -1
};
static const AnimationInfo attackWait = {
	// TODO: file not found for shrink animation
	kAnimationAttackWait, (FileId)placeholder, placeholder, 1, attackWaitFrames
};

static const int mordamirIncineratedFrames[] = {
	12, 13, 13, 13, 13, 13, 14, 15, 16, 17, 18, 19, 19, 19, 19, 19,
	19, 19, 19, 19, 18, 17, 16, 15, 14, 13, 12,  0, -1
};
static const AnimationInfo mordamirIncinerated = {
	// TODO: file not found for shrink animation
	kAnimationMordamirIncinerated, (FileId)placeholder, placeholder, 1, mordamirIncineratedFrames
};

static const int recoilFrames[] = {
	 0,  1,  2, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,  2,  1,
	 0, 12, 13, -1
};
static const AnimationInfo recoil = {
	kAnimationRecoil, (FileId)placeholder, placeholder, 1, recoilFrames
};

static const int mordamirAppearFrames[] = {
	12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0, -1
};
static const AnimationInfo mordamirAppear = {
	kAnimationMordamirAppears, (FileId)placeholder, placeholder, 1, mordamirAppearFrames
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

// from wizard to mordamir
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

}
