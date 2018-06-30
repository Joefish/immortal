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

#ifndef IMMORTAL_ROOMS_H
#define IMMORTAL_ROOMS_H

#include "common/array.h"

#include "immortal/entity.h"

namespace Immortal {

enum LevelId {
	kLevelId1,
	kLevelId2,
	kLevelId3,
	kLevelId4,
	kLevelId5,
	kLevelId6,
	kLevelId7,
	kLevelId8
};

enum DoorOrientation {
	kDoorLeft,
	kDoorRight
};

class Room {
public:
	int _x;
	int _y;
	int _flags; // depending on usage, convert to less ambiguous method
};

class Door {
public:
	Door(int x, int y, const Room *teleportFrom, const Room *teleportTo, bool isLocked,
	     DoorOrientation orientation)
	    : _x(x)
	    , _y(y)
	    , _teleportFrom(teleportFrom)
	    , _teleportTo(teleportTo)
	    , _isLocked(isLocked)
	    , _orientation(orientation) {
	}

	int _x;
	int _y;
	const Room *_teleportFrom;
	const Room *_teleportTo;
	bool _isLocked;
	DoorOrientation _orientation;
};


class Level {
public:
	void loadLevel(int level);

private:
	void initLevel1();
	void initLevel2();
	void initLevel3();
	void initLevel4();
	void initLevel5();
	void initLevel6();
	void initLevel7();
	void initLevel8();

public:
	Common::Array<Room> _rooms;
	Common::Array<Door> _doors;
};

}

#endif
