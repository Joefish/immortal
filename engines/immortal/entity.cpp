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
    , _defaultSprite(kSpriteNone)
    , _type(kEntityTypeNone)
    , _state(kStateNone)
    , _parameter(0) {
}

Entity::Entity(int x, int y, SpriteId defaultSprite, EntityType type,
               EntityState state, int parameter)
    : _x(x)
    , _y(y)
    , _defaultSprite(defaultSprite)
    , _type(type)
    , _state(state)
    , _parameter(parameter) {
}


Common::Point Entity::getPos() const {
	return Common::Point(_x, _y);
}

void Entity::setPos(int x, int y) {
	_x = x;
	_y = y;
}


Wizard::Wizard()
    : Entity()
    , _wizardState(kStateNone)
    , _direction(kDirectionN)
    , _frame(0)
    , _frameStart(0)
    , _frameEnd(0) {
}

int Wizard::getFrame() const {
	return _frame;
}

Direction Wizard::getDirection() const {
	return _direction;
}

void Wizard::step(Direction direction) {
	switch (direction) {
	case kDirectionN:
		_y += -8;
		break;
	case kDirectionNE:
		_x += 8;
		_y += -8;
		break;
	case kDirectionE:
		_x += 8;
		break;
	case kDirectionSE:
		_x += 8;
		_y += 8;
		break;
	case kDirectionS:
		_y += 8;
		break;
	case kDirectionSW:
		_x += -8;
		_y += 8;
		break;
	case kDirectionW:
		_x += -8;
		break;
	case kDirectionNW:
		_x += -8;
		_y += -8;
		break;
	}

	// TODO:
	// Check for wizard state if he's on carpet, barrell or whatever and set
	// the appropriate frame range. For now limited to walking
	if (_direction != direction) {
		if (_wizardState == kStateNone) {
			_frameStart = 0;
			_frameEnd = 4;
		}
		_frame = _frameStart;
		_direction = direction;
	} else {
		if (++_frame > _frameEnd)
			_frame = _frameStart;
	}
}

}
