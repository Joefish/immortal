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
	kDirectionNW,
	kDirectionNum
};

enum WizardState {
	kWizardStateNone             = 0,
	kWizardStateEaten            = 1 <<  0,
	kWizardStateSpiked           = 1 <<  1,
	kWizardStateSleeping         = 1 <<  2,
	kWizardStateSquished         = 1 <<  3,
	kWizardStateLevitating       = 1 <<  4,
	kWizardStateDevoured         = 1 <<  5,
	kWizardStateBadCrawl         = 1 <<  6,
	kWizardStateWebbed           = 1 <<  7,
	kWizardStateSunk             = 1 <<  8,
	kWizardStateDownVortex       = 1 <<  9,
	kWizardStateBlinked          = 1 << 10,
	kWizardStateFireProtected    = 1 << 11,
	kWizardStateBronze           = 1 << 12,
	kWizardStateLightning        = 1 << 13,
	kWizardStateGettingAmulet    = 1 << 14,
	kWizardStateHead             = 1 << 15,
	kWizardStateChop             = 1 << 16,
	kWizardStateRope             = 1 << 17,
	kWizardStateNurse            = 1 << 18,
	kWizardStateBurned           = 1 << 19,
	kWizardStateOnObject         = 1 << 20,
	kWizardStateOnBody           = 1 << 21,
	kWizardStateOnCarpet         = 1 << 22,
	kWizardStateOnBarrel         = 1 << 23,
	kWizardStateProteanGoblin    = 1 << 24,
	kWizardStateTiny             = 1 << 25,
	kWizardStateDrunk            = 1 << 26,
	kWizardStateCombat           = 1 << 27,
	kWizardStateObjectIsF1       = 1 << 28,       // ?
	kWizardStateObjectIsF2       = 1 << 29        // ?
};

enum MonsterType {
	kMonsterTypeWizard,
	kMonsterTypeGoblin,
	kMonsterTypeTroll,
	kMonsterTypeUlindor,
	kMonsterTypeOther
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
	int getFrame() const;
	Direction getDirection() const;
	void setDirection(Direction direction);
	void setMonsterType(MonsterType type);
	void move(Direction direction, WizardState state = kWizardStateNone);

private:
	int _x;
	int _y;
	Direction _direction;
	SpriteId _defaultSprite;
	int _animationFrame;
	int _animationFrameStart;
	int _animationFrameEnd;
	EntityType _type;
	MonsterType _monsterType;
	EntityState _state;
	// TODO:
	// _parameter is used in the original for all kinds of purposes.
	// Function pointers, strings, HP, ..
	int _parameter;
};

}

#endif
