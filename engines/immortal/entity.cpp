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

#include "immortal/entity.h"

namespace Immortal {

Entity::Entity()
    : _x(0)
    , _y(0)
    , _direction(kDirectionN)
    , _defaultSprite(kSpriteNone)
    , _animationFrame(0)
    , _animationFrameStart(0)
    , _animationFrameEnd(0)
    , _type(kEntityTypeNone)
    , _state(kStateNone)
    , _parameter(0) {
}

Entity::Entity(int x, int y, SpriteId defaultSprite, EntityType type,
               EntityState state, int parameter)
    : _x(x)
    , _y(y)
    , _direction(kDirectionN)
    , _defaultSprite(defaultSprite)
    , _animationFrame(0)
    , _animationFrameStart(0)
    , _animationFrameEnd(0)
    , _type(type)
    , _state(state)
    , _parameter(parameter) {
}


Common::Point Entity::getPos() const {
	return Common::Point(_x, _y);
}

void Entity::setPos(int x, int y) {
	_x = x / 8;
	_y = y / 8;
}

int Entity::getFrame() const {
	return _animationFrame;
}

Direction Entity::getDirection() const {
	return _direction;
}

void Entity::setDirection(Direction direction) {
	_direction = direction;
}

void Entity::setMonsterType(MonsterType type) {
	_monsterType = type;
}


static const int wizardMoveSpeedX[] = {
	0, 2, 3, 2, 0, -2, -3, -2
};
static const int wizardMoveSpeedY[] = {
	-4, -2, 0, 2, 4, 2, 0, -2
};

void Entity::move(Direction direction, WizardState wizardState) {
	switch (direction) {
	case kDirectionNone:
		return;
	default:
		_x += wizardMoveSpeedX[direction];
		_y += wizardMoveSpeedY[direction];
	}

	// TODO:
	// Check for wizard state if he's on carpet, barrell or whatever and set
	// the appropriate frame range. For now limited to walking
	if (_monsterType == kMonsterTypeWizard) {
		_animationFrameStart = 0;
		_animationFrameEnd = 4;
		if (_direction != direction) {
			if (wizardState == kStateNone) {
				_animationFrameStart = 0;
				_animationFrameEnd = 4;
			}
			_animationFrame = _animationFrameStart;
			_direction = direction;
		} else {
			if (++_animationFrame > _animationFrameEnd)
				_animationFrame = _animationFrameStart;
		}
	}
}

}
