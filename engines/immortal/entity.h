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

#ifndef IMMORTAL_ENTITY_H
#define IMMORTAL_ENTITY_H

#include "immortal/resman.h"

namespace Immortal {

enum EntityType {
	// Items
	kEntityTypeGold,
	kEntityTypeSonicProtectionScroll,
	kEntityTypeBlinkScroll,
	kEntityTypeTractorScroll,
	kEntityTypeBronzeScroll,
	kEntityTypeFireProtectionScroll,
	kEntityTypeLevitationScroll,
	kEntityTypeWispCharm,
	kEntityTypeFireballScroll,
	kEntityTypeDeathMap,
	kEntityTypeCoffee,
	kEntityTypeAmulet,
	kEntityTypeCoors,           // beer can
	kEntityTypeDustOfComplaisance,
	kEntityTypeBait,
	kEntityTypeGasBomb,
	kEntityTypeCarpet,
	kEntityTypeTeleportGem,
	kEntityTypeWater,
	kEntityTypeNote,
	kEntityTypeWormDetector,    // aka 'geiger'
	kEntityTypeAnaRing,
	kEntityTypeDunricRing,
	kEntityTypeProteanRing,
	kEntityTypeSpores,

	// Actors
	kEntityTypeAuthors,
	kEntityTypeWraith,
	kEntityTypeDragon,
	kEntityTypeMordamir,
	kEntityTypeMordamirPhantasm,
	kEntityTypeAna,
	kEntityTypeErek,
	kEntityTypeNorlac,
	kEntityTypeDunric2,
	kEntityTypeKing,
	kEntityTypeMadKing,
	kEntityTypeMerchant,
	kEntityTypeMerchant3,
	kEntityTypeMerchantx,
	kEntityTypeUlindor2,
	kEntityTypePlanners,
	kEntityTypeSmith,

	// Misc
	kEntityTypeBeam,
	kEntityTypeSkeleton,
	kEntityTypeDull,
	kEntityTypeTeleport1,
	kEntityTypeTeleport2,
	kEntityTypeWorm,
	kEntityTypeSpike,
	kEntityTypeFloor,
	kEntityTypeWall,
	kEntityTypeRings,
	kEntityTypeSlimeBottle,
	kEntityTypeShrinkPotion,
	kEntityTypeRitualKnife,     // aka TRNTYPE
	kEntityTypeInvisible,
	kEntityTypeGlimpse,         // blink scroll?
	kEntityTypeHay,
	kEntityTypeMusclePotion,    // same use function and string as shrink potion ??
	kEntityTypeSpider,
	kEntityTypeSpiderEgg,
	kEntityTypeAlcohol,
	kEntityTypeBoots,
	kEntityTypeSpores2,
	kEntityTypeChestKey,
	kEntityTypeTrap,
	kEntityTypeChest,
	kEntityTypeGem,
	kEntityTypeStone,
	kEntityTypeDoorKey,
	kEntityTypeGoldPile,
	kEntityTypeChest2,
	kEntityTypeChest3,
	kEntityTypeChest4,          // spider chest
	kEntityTypeShrinkHole,
	kEntityTypeGSpike,
	kEntityTypeTrigger,
	kEntityTypeEgg,
	kEntityTypeCrawl,
	kEntityTypeFlameThrow,
	kEntityTypeVortex,

	kEntityTypeNum
};

class Entity {
public:
	// TODO:
	// Split states up in 'general' states that every entity can go in and
	// state that is specifically for the wizard

	typedef int64 EntityState;

	static const EntityState kStateNone             = 0;
	static const EntityState kStateInvisible        = 1UL <<  1;        // won't be drawn
	static const EntityState kStateRunning          = 1UL <<  2;        // routine bound to object gets called every frame
	static const EntityState kStateChest            = 1UL <<  3;        // may contain objects
	static const EntityState kStateOnGround         = 1UL <<  4;        // low priority?

	static const EntityState kStateUsesFireButton   = 1UL <<  5;
	static const EntityState kStateEaten            = 1UL <<  6;
	static const EntityState kStateSpiked           = 1UL <<  7;
	static const EntityState kStateSleeping         = 1UL <<  8;
	static const EntityState kStateSquished         = 1UL <<  9;
	static const EntityState kStateLevitating       = 1UL << 10;
	static const EntityState kStateDevoured         = 1UL << 11;
	static const EntityState kStateBadCrawl         = 1UL << 12;
	static const EntityState kStateWebbed           = 1UL << 13;
	static const EntityState kStateSunk             = 1UL << 14;
	static const EntityState kStateDownVortex       = 1UL << 15;
	static const EntityState kStateBlinked          = 1UL << 16;
	static const EntityState kStateFireProtected    = 1UL << 17;
	static const EntityState kStateBronze           = 1UL << 18;
	static const EntityState kStateLightning        = 1UL << 19;
	static const EntityState kStateGettingAmulet    = 1UL << 20;
	static const EntityState kStateHead             = 1UL << 21;
	static const EntityState kStateChop             = 1UL << 22;
	static const EntityState kStateRope             = 1UL << 23;
	static const EntityState kStateNurse            = 1UL << 24;
	static const EntityState kStateBurned           = 1UL << 25;
	static const EntityState kStateOnObject         = 1UL << 26;
	static const EntityState kStateOnBody           = 1UL << 27;
	static const EntityState kStateOnCarpet         = 1UL << 28;
	static const EntityState kStateProteanGoblin    = 1UL << 29;
	static const EntityState kStateTiny             = 1UL << 30;
	static const EntityState kStateDrunk            = 1UL << 31;
	static const EntityState kStateCombat           = 1UL << 32;
	static const EntityState kStateObjectIsF1       = 1UL << 33;        // ?
	static const EntityState kStateObjectIsF2       = 1UL << 34;

	static const EntityState kStateTough            = 1UL << 35;
	static const EntityState kStateDead             = 1UL << 36;        // set after death sequence
	static const EntityState kStatePossessive       = 1UL << 37;        // possessions die with entity
	static const EntityState kStateBaby             = 1UL << 38;        // something with the wisps
	static const EntityState kStateEngageable       = 1UL << 39;

public:
	Entity(int x, int y, SpriteId defaultSprite, EntityType type,
	       EntityState state, int parameter);

	int _x;
	int _y;
	SpriteId _defaultSprite;
	EntityType _type;
	EntityState _state;
	int _parameter;
};

}

#endif
