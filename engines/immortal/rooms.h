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

struct Room {
	int _x;
	int _y;
	int _flags; // depending on usage, convert to less ambiguous method
};

struct Door {
	int _x;
	int _y;
	const Room *_teleportFrom;
	const Room *_teleportTo;
	bool _isLocked;
	DoorOrientation _orientation;
};


class Level {
	static const Room _level1Room[];
	static const Room _level2Room[];
	static const Room _level3Room[];
	static const Room _level4Room[];
	static const Room _level5Room[];
	static const Room _level6Room[];
	static const Room _level7Room[];
	static const Room _level8Room[];
	static const Door _level1Door[];
	static const Door _level2Door[];
	static const Door _level3Door[];
	static const Door _level4Door[];
	static const Door _level5Door[];
	static const Door _level6Door[];
	static const Door _level7Door[];
	static const Door _level8Door[];

	// TODO: Rename rooms once reference is not needed anymore (like for doors)
	static const Room *_room1_0;
	static const Room *_room1_1;
	static const Room *_room1_2;
	static const Room *_room1_3;
	static const Room *_room1_4;
	static const Room *_room1_5;
	static const Room *_room1_6;
	static const Room *_room1_7;
	static const Room *_room1_8;
	static const Room *_room1_9;
	static const Room *_room1_A;
	static const Room *_room1_B;
	static const Room *_room1_C;
	static const Room *_room1_D;
	static const Room *_room1_E;
	static const Room *_room1_F;
	static const Room *_room2_0;
	static const Room *_room2_1;
	static const Room *_room2_2;
	static const Room *_room2_3;
	static const Room *_room2_4;
	static const Room *_room2_5;
	static const Room *_room2_6;
	static const Room *_room2_7;
	static const Room *_room2_8;
	static const Room *_room2_9;
	static const Room *_room2_A;
	static const Room *_room2_B;
	static const Room *_room2_C;
	static const Room *_room2_D;
	static const Room *_room2_E;
	static const Room *_room2_F;
	static const Room *_room5_0;
	static const Room *_room5_1;
	static const Room *_room5_2;
	static const Room *_room5_3;
	static const Room *_room5_4;
	static const Room *_room5_5;
	static const Room *_room5_6;
	static const Room *_room5_7;
	static const Room *_room5_8;
	static const Room *_room5_9;
	static const Room *_room5_A;
	static const Room *_room6_0;
	static const Room *_room6_1;
	static const Room *_room6_2;
	static const Room *_room6_3;
	// INFO: _room6_4 missing on purpose
	static const Room *_room6_5;
	static const Room *_room6_6;
	static const Room *_room6_7;
	static const Room *_room6_8;
	static const Room *_room6_9;
	static const Room *_room6_A;
	static const Room *_room8_0;
	static const Room *_room8_1;
	static const Room *_room8_2;
};

}

#endif
