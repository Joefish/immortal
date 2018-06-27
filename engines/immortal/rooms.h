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

struct Room {
	int _x;
	int _y;
	int _flags; // depending on usage, convert to less ambiguous method
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
	// TODO:
	// objects, doors, ..
};

}

#endif
