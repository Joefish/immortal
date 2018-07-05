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

#include "immortal/rooms.h"

namespace Immortal {

// TODO: Rename rooms once reference is not needed anymore (like for doors)
static const Room _room1_0 = {   0,  64, 0};
static const Room _room1_1 = {   0, 256, 0};
static const Room _room1_2 = {   0, 480, 0};
static const Room _room1_3 = { 128, 512, 0};
static const Room _room1_4 = { 256, 480, 0};
static const Room _room1_5 = { 384, 256, 0};
static const Room _room1_6 = { 320,  64, 0};
static const Room _room1_7 = { 512,  64, 0};
static const Room _room1_8 = { 640, 160, 0};
static const Room _room1_9 = { 768, 224, 0};
static const Room _room1_A = { 512, 416, 0};
static const Room _room1_B = { 448, 640, 0};
static const Room _room1_C = { 768, 608, 0};
static const Room _room1_D = { 960, 512, 0};
static const Room _room1_E = {1024, 352, 0};
static const Room _room1_F = { 896,  64, 0};
static const Room _room2_0 = {   0,  64, 0};
static const Room _room2_1 = { 384, 128, 0};
static const Room _room2_2 = { 576,  64, 0};
static const Room _room2_3 = { 768, 192, 0};
static const Room _room2_4 = { 960, 128, 0};
static const Room _room2_5 = {   0, 256, 0};
static const Room _room2_6 = { 448, 224, 0};
static const Room _room2_7 = { 640, 320, 0};
static const Room _room2_8 = { 960, 224, 0};
static const Room _room2_9 = {   0, 448, 0};
static const Room _room2_A = { 256, 416, 0};
static const Room _room2_B = { 448, 512, 0};
static const Room _room2_C = { 832, 448, 0};
static const Room _room2_D = { 128, 640, 0};
static const Room _room2_E = { 448, 672, 0};
static const Room _room2_F = { 768, 608, 0};
static const Room _room5_0 = { 896, 320, 0};
static const Room _room5_1 = { 960, 480, 0};
static const Room _room5_2 = { 960, 128, 0};
static const Room _room5_3 = {   0, 512, 0};
static const Room _room5_4 = { 512, 128, 0};
static const Room _room5_5 = { 512, 224, 0};
static const Room _room5_6 = {  64, 128, 0};
static const Room _room5_7 = { 704, 448, 0};
static const Room _room5_8 = { 768, 256, 0};
static const Room _room5_9 = {   0, 768, 0};
static const Room _room5_A = { 896, 864, 0};
static const Room _room6_0 = { 896, 768, 0};
static const Room _room6_1 = { 896, 640, 0};
static const Room _room6_2 = { 448, 896, 0};
static const Room _room6_3 = {   0, 192, 0};
// INFO: _room6_4 missing on purpose
static const Room _room6_5 = { 256, 800, 0};
static const Room _room6_6 = { 448, 704, 0};
static const Room _room6_7 = { 704, 832, 0};
static const Room _room6_8 = { 896, 864, 0};
static const Room _room6_9 = { 128, 896, 0};
static const Room _room6_A = {   0, 512, 0};
static const Room _room8_0 = {  64, 704, 0};
static const Room _room8_1 = { 448, 704, 0};
static const Room _room8_2 = { 832, 416, 0};


void Level::loadLevel(int level) {
	switch (level) {
	case 1:
		initLevel1();
		break;
	case 2:
		initLevel2();
		break;
	case 3:
		initLevel3();
		break;
	case 4:
		initLevel4();
		break;
	case 5:
		initLevel5();
		break;
	case 6:
		initLevel6();
		break;
	case 7:
		initLevel7();
		break;
	case 8:
		initLevel8();
		break;
	default:
		break;
	}
}

void Level::initLevel1() {
	_rooms.clear();
	_doors.clear();

	_rooms.push_back(_room1_5); // room with invisible enemies
	_rooms.push_back(_room1_7);
	_rooms.push_back(_room1_8);
	_rooms.push_back(_room1_9);
	_rooms.push_back(_room1_A);
	_rooms.push_back(_room1_D);
	_rooms.push_back(_room1_E);
	_rooms.push_back(_room1_F);

	_doors.push_back(Door( 704, 224, &_room1_5, &_room1_8, false, kDoorLeft));
	_doors.push_back(Door( 576, 352, &_room1_A, &_room1_5,  true, kDoorRight));
	_doors.push_back(Door( 704,  96, &_room1_8, &_room1_7, false, kDoorRight));
	_doors.push_back(Door( 960, 128, &_room1_F, &_room1_7, false, kDoorRight));
	_doors.push_back(Door(1088, 160, &_room1_9, &_room1_F, false, kDoorRight));
	_doors.push_back(Door(1088, 320, &_room1_E, &_room1_9, false, kDoorRight));
	_doors.push_back(Door( 896, 416, &_room1_A, &_room1_9, false, kDoorRight));

	_object.reserve(_rooms.size());
	Common::Array<Entity> *roomObjects = nullptr;
	roomObjects = &_object[0];   // room1_5
	roomObjects->push_back(Entity(0, 0, kSpriteNone, kEntityTypeTrap,
	                              Entity::kStateRunning | Entity::kStateInvisible, 42)); // TODO: id to 'room5traps'
	roomObjects->push_back(Entity(459, 379, kSpriteRing, kEntityTypeAmulet,
	                              Entity::kStateNone, 5));
	roomObjects->push_back(Entity(446, 327, kSpriteScroll, kEntityTypeWispCharm,
	                              Entity::kStateNone, 0));

	roomObjects = &_object[1];   // room1_7
	roomObjects->push_back(Entity(145, 138, kSpriteNone, kEntityTypeTrap,
	                              Entity::kStateRunning | Entity::kStateInvisible, 42)); // TODO: id to 'room7traps'

	roomObjects = &_object[2];   // room1_8
	roomObjects->push_back(Entity(0, 0, kSpriteNone, kEntityTypeTrap,
	                              Entity::kStateRunning | Entity::kStateInvisible, 42)); // TODO: id to 'room8traps'

	roomObjects = &_object[3];   // room1_9
	roomObjects->push_back(Entity(1052, 309, kSpriteErek, kEntityTypeErek,
	                              Entity::kStateChest | Entity::kStateOnGround, 0));
	roomObjects->push_back(Entity(0, 0, kSpriteScroll, kEntityTypeFireballScroll,
	                              Entity::kStateUsesFireButton, 3));
	roomObjects->push_back(Entity(128, 464, kSpriteRing, kEntityTypeDunricRing,
	                              Entity::kStateNone, 0));
	roomObjects->push_back(Entity(837, 421, kSpriteChestClosed, kEntityTypeChest,
	                              Entity::kStateChest, 0));
	roomObjects->push_back(Entity(0, 0, kSpriteScroll, kEntityTypeDeathMap,
	                              Entity::kStateNone, 0));
	roomObjects->push_back(Entity(597, 457, kSpriteBottle, kEntityTypeWater,
	                              Entity::kStateNone, 0));
	roomObjects->push_back(Entity(0, 0, kSpriteIconSporesBag, kEntityTypeSpores,
	                              Entity::kStateNone, 0));
	roomObjects->push_back(Entity(0, 0, kSpriteNone, kEntityTypeBait,
	                              Entity::kStateNone, 0));
	roomObjects->push_back(Entity(205, 158, kSpriteIconKey, kEntityTypeChestKey,
	                              Entity::kStateNone, 0));

	roomObjects = &_object[4];   // room1_A
	roomObjects->push_back(Entity(671, 461, kSpriteNone, kEntityTypeHay,
	                              Entity::kStateRunning | Entity::kStateInvisible, 0));
	roomObjects->push_back(Entity(780, 508, kSpriteNone, kEntityTypeBeam,
	                              Entity::kStateRunning | Entity::kStateInvisible, 0));
	roomObjects->push_back(Entity(700, 480, kSpriteNone, kEntityTypeTeleport2,
	                              Entity::kStateRunning | Entity::kStateInvisible, 42)); // TODO: 'roomd' Id as parm

	roomObjects = &_object[5];   // room1_D
	roomObjects->push_back(Entity(1150, 560, kSpriteNone, kEntityTypeTeleport2,
	                              Entity::kStateRunning | Entity::kStateInvisible, 42)); // TODO: 'rooma' Id as parm
	roomObjects->push_back(Entity(205, 158, kSpriteKoorsLight, kEntityTypeCoors,
	                              Entity::kStateNone, 0));

	roomObjects = &_object[6];   // room1_E
	roomObjects->push_back(Entity(1184, 426, kSpriteTable, kEntityTypeMordamirPhantasm, Entity::kStateNone, 0));
	roomObjects->push_back(Entity( 145, 138, kSpriteNone, kEntityTypeGold, Entity::kStateRunning, 2));

	roomObjects = &_object[7];   // room1_F
	roomObjects->push_back(Entity(1192, 109, kSpriteGold, kEntityTypeGoldPile,
	                              Entity::kStateOnGround, 3));
	roomObjects->push_back(Entity(0, 0, kSpriteNone, kEntityTypeDoorKey,
	                              Entity::kStateNone, 42));     // TODO: parm: room5 + 16 * roomA
	roomObjects->push_back(Entity(0, 0, kSpriteNone, kEntityTypeNote,
	                              Entity::kStateNone, 42));     // TODO: id to guardnote
}

void Level::initLevel2() {
	_rooms.clear();
	_doors.clear();

	_rooms.push_back(_room1_0);
	_rooms.push_back(_room1_1);
	_rooms.push_back(_room1_2);
	_rooms.push_back(_room1_3);
	_rooms.push_back(_room1_4);
	_rooms.push_back(_room1_6);
	_rooms.push_back(_room1_B);
	_rooms.push_back(_room1_C);
	_doors.push_back(Door(  64, 224, &_room1_1, &_room1_0, false, kDoorRight));
	_doors.push_back(Door( 256, 224, &_room1_1, &_room1_0, false, kDoorLeft));
	_doors.push_back(Door( 384, 128, &_room1_0, &_room1_6, false, kDoorLeft));
	_doors.push_back(Door(  64, 416, &_room1_2, &_room1_1, false, kDoorLeft));
	_doors.push_back(Door( 320, 448, &_room1_4, &_room1_1, false, kDoorRight));
	_doors.push_back(Door( 192, 608, &_room1_2, &_room1_3, false, kDoorLeft));
	_doors.push_back(Door( 320, 576, &_room1_3, &_room1_4, false, kDoorLeft));
	_doors.push_back(Door( 448, 640, &_room1_3, &_room1_B, false, kDoorLeft));
	_doors.push_back(Door( 640, 608, &_room1_B, &_room1_A, false, kDoorRight));
	_doors.push_back(Door( 832, 640, &_room1_B, &_room1_C,  true, kDoorLeft));
}

void Level::initLevel3() {
	_rooms.clear();
	_doors.clear();

	_rooms.push_back(_room2_2);
	_rooms.push_back(_room2_7);
	_rooms.push_back(_room2_8);
	_rooms.push_back(_room2_A);
	_rooms.push_back(_room2_B);
	_rooms.push_back(_room2_C);
	_rooms.push_back(_room2_D);
	_rooms.push_back(_room2_E);
	_rooms.push_back(_room2_F);
	_doors.push_back(Door( 832, 448, &_room2_C, &_room2_7, false, kDoorRight));
	_doors.push_back(Door( 896, 576, &_room2_F, &_room2_C, false, kDoorRight));
	_doors.push_back(Door( 448, 704, &_room2_E, &_room2_D,  true, kDoorRight));
	_doors.push_back(Door(1088, 576, &_room2_F, &_room2_C, false, kDoorLeft));
}

void Level::initLevel4() {
	_rooms.clear();
	_doors.clear();

	_rooms.push_back(_room2_0);
	_rooms.push_back(_room2_1);
	_rooms.push_back(_room2_3);
	_rooms.push_back(_room2_4);
	_rooms.push_back(_room2_5);
	_rooms.push_back(_room2_6);
	_rooms.push_back(_room2_9);
	_doors.push_back(Door(  64, 256, &_room2_5, &_room2_0, false, kDoorRight));
	_doors.push_back(Door( 384,  96, &_room2_1, &_room2_0, false, kDoorRight));
	_doors.push_back(Door( 320, 384, &_room2_9, &_room2_5, false, kDoorLeft));
}

void Level::initLevel5() {
	_rooms.clear();
	_doors.clear();

	_rooms.push_back(_room5_0);
	_rooms.push_back(_room5_1);
	_rooms.push_back(_room5_2);
	_rooms.push_back(_room5_3);
	_rooms.push_back(_room5_4);
	_rooms.push_back(_room5_5);
	_rooms.push_back(_room5_6);
	_rooms.push_back(_room5_7);
	_rooms.push_back(_room5_8);
	_rooms.push_back(_room5_9);
	_rooms.push_back(_room5_A);
	_doors.push_back(Door( 768, 384, &_room5_7, &_room5_5, false, kDoorRight));
	_doors.push_back(Door( 896, 320, &_room5_0, &_room5_8, false, kDoorRight));
	_doors.push_back(Door( 960, 128, &_room5_1, &_room5_0, false, kDoorRight));
	_doors.push_back(Door(1088, 416, &_room5_1, &_room5_0, false, kDoorRight));
	_doors.push_back(Door( 640, 196, &_room5_5, &_room5_4,  true, kDoorLeft));

}

// TODO: Missing Doors..
void Level::initLevel6() {
	_rooms.clear();
	_doors.clear();

	_rooms.push_back(_room6_0);
	_rooms.push_back(_room6_1);
	_rooms.push_back(_room6_2);
	_rooms.push_back(_room6_3);
	_rooms.push_back(_room6_6);
}

// TODO: Missing Doors..
void Level::initLevel7() {
	_rooms.clear();
	_doors.clear();

	_rooms.push_back(_room6_5);
	_rooms.push_back(_room6_7);
	_rooms.push_back(_room6_8);
	_rooms.push_back(_room6_9);
	_rooms.push_back(_room6_A);
}

// TODO: Missing Doors..
void Level::initLevel8() {
	_rooms.clear();
	_doors.clear();

	_rooms.push_back(_room8_0);
	_rooms.push_back(_room8_1);
	_rooms.push_back(_room8_2);
}

}
