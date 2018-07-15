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

enum Direction {
	kDirectionNone = -1,
	kDirectionN = 0,
	kDirectionNE,
	kDirectionE,
	kDirectionSE,
	kDirectionS,
	kDirectionSW,
	kDirectionW,
	kDirectionNW
};

enum EntityType {
	kEntityTypeNone = -1,
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
	typedef int EntityState;
	static const EntityState kStateNone             = 1 <<  0;
	static const EntityState kStateInvisible        = 1 <<  1;        // won't be drawn
	static const EntityState kStateRunning          = 1 <<  2;        // routine bound to object gets called every frame
	static const EntityState kStateChest            = 1 <<  3;        // may contain objects
	static const EntityState kStateOnGround         = 1 <<  4;        // low priority?
	static const EntityState kStateTough            = 1 <<  5;
	static const EntityState kStateDead             = 1 <<  6;        // set after death sequence
	static const EntityState kStatePossessive       = 1 <<  7;        // possessions die with entity
	static const EntityState kStateBaby             = 1 <<  8;        // something with the wisps
	static const EntityState kStateEngageable       = 1 <<  9;
	static const EntityState kStateUsesFireButton   = 1 << 10;

public:
	Entity();
	Entity(int x, int y, SpriteId defaultSprite, EntityType type,
	       EntityState state, int parameter);

	Common::Point getPos() const;
	void setPos(int x, int y);

public:
	int _x;
	int _y;
	SpriteId _defaultSprite;
	EntityType _type;
	EntityState _state;
	int _parameter;
};


class Wizard : public Entity {
public:
	enum WizardState {
		kStateNone             = 0,
		kStateEaten            = 1 <<  0,
		kStateSpiked           = 1 <<  1,
		kStateSleeping         = 1 <<  2,
		kStateSquished         = 1 <<  3,
		kStateLevitating       = 1 <<  4,
		kStateDevoured         = 1 <<  5,
		kStateBadCrawl         = 1 <<  6,
		kStateWebbed           = 1 <<  7,
		kStateSunk             = 1 <<  8,
		kStateDownVortex       = 1 <<  9,
		kStateBlinked          = 1 << 10,
		kStateFireProtected    = 1 << 11,
		kStateBronze           = 1 << 12,
		kStateLightning        = 1 << 13,
		kStateGettingAmulet    = 1 << 14,
		kStateHead             = 1 << 15,
		kStateChop             = 1 << 16,
		kStateRope             = 1 << 17,
		kStateNurse            = 1 << 18,
		kStateBurned           = 1 << 19,
		kStateOnObject         = 1 << 20,
		kStateOnBody           = 1 << 21,
		kStateOnCarpet         = 1 << 22,
		kStateProteanGoblin    = 1 << 23,
		kStateTiny             = 1 << 24,
		kStateDrunk            = 1 << 25,
		kStateCombat           = 1 << 26,
		kStateObjectIsF1       = 1 << 27,       // ?
		kStateObjectIsF2       = 1 << 28        // ?
	};

public:
	Wizard();

	void step(Direction direction);
	int getFrame() const;
	Direction getDirection() const;

private:
	WizardState _wizardState;
	Direction _direction;
	int _frame;
	int _frameStart;
	int _frameEnd;
};

}

#endif
