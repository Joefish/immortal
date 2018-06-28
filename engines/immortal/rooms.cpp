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

const Room Level::_level1Room[] = {
	{ 384, 256, 0},
	{ 512,  64, 0},
	{ 640, 160, 0},
	{ 768, 224, 0},
	{ 512, 416, 0},
	{ 960, 512, 0},
	{1024, 352, 0},
	{ 896,  64, 0}
};

const Room Level::_level2Room[] = {
	{   0,  64, 0},
	{   0, 256, 0},
	{   0, 480, 0},
	{ 128, 512, 0},
	{ 256, 480, 0},
	{ 320,  64, 0},
	{ 448, 640, 0},
	{ 768, 608, 0}
};

const Room Level::_level3Room[] = {
	{ 576,  64, 0},
	{ 640, 320, 0},
	{ 960, 224, 0},
	{ 256, 416, 0},
	{ 448, 512, 0},
	{ 832, 448, 0},
	{ 128, 640, 0},
	{ 448, 672, 0},
	{ 768, 608, 0}
};

const Room Level::_level4Room[] = {
	{   0,  64, 0},
	{ 384, 128, 0},
	{ 768, 192, 0},
	{ 960, 128, 0},
	{   0, 256, 0},
	{ 448, 224, 0},
	{   0, 448, 0},
};

const Room Level::_level5Room[] = {
	{ 896, 320, 0},
	{ 960, 480, 0},
	{ 960, 128, 0},
	{   0, 512, 0},
	{ 512, 128, 0},
	{ 512, 224, 0},
	{  64, 128, 0},
	{ 704, 448, 0},
	{ 768, 256, 0},
	{   0, 768, 0},
	{ 896, 864, 0},
};

const Room Level::_level6Room[] = {
	{ 896, 768, 0},
	{ 896, 640, 0},
	{ 448, 896, 0},
	{   0, 192, 0},
	{ 448, 704, 0},
};

const Room Level::_level7Room[] = {
	{ 256, 800, 0},
	{ 704, 832, 0},
	{ 896, 864, 0},
	{ 128, 896, 0},
	{   0, 512, 0},
};

const Room Level::_level8Room[] = {
	{  64, 704, 0},
	{ 448, 704, 0},
	{ 832, 416, 0},
};

const Room *Level::_room1_0 = &Level::_level2Room[0];
const Room *Level::_room1_1 = &Level::_level2Room[1];
const Room *Level::_room1_2 = &Level::_level2Room[2];
const Room *Level::_room1_3 = &Level::_level2Room[3];
const Room *Level::_room1_4 = &Level::_level2Room[4];
const Room *Level::_room1_5 = &Level::_level1Room[0];
const Room *Level::_room1_6 = &Level::_level2Room[5];
const Room *Level::_room1_7 = &Level::_level1Room[1];
const Room *Level::_room1_8 = &Level::_level1Room[2];
const Room *Level::_room1_9 = &Level::_level1Room[3];
const Room *Level::_room1_A = &Level::_level1Room[4];
const Room *Level::_room1_B = &Level::_level2Room[6];
const Room *Level::_room1_C = &Level::_level2Room[7];
const Room *Level::_room1_D = &Level::_level1Room[5];
const Room *Level::_room1_E = &Level::_level1Room[6];
const Room *Level::_room1_F = &Level::_level1Room[7];
const Room *Level::_room2_0 = &Level::_level4Room[0];
const Room *Level::_room2_1 = &Level::_level4Room[1];
const Room *Level::_room2_2 = &Level::_level3Room[0];
const Room *Level::_room2_3 = &Level::_level4Room[2];
const Room *Level::_room2_4 = &Level::_level4Room[3];
const Room *Level::_room2_5 = &Level::_level4Room[4];
const Room *Level::_room2_6 = &Level::_level4Room[5];
const Room *Level::_room2_7 = &Level::_level3Room[1];
const Room *Level::_room2_8 = &Level::_level3Room[2];
const Room *Level::_room2_9 = &Level::_level4Room[6];
const Room *Level::_room2_A = &Level::_level3Room[3];
const Room *Level::_room2_B = &Level::_level3Room[4];
const Room *Level::_room2_C = &Level::_level3Room[5];
const Room *Level::_room2_D = &Level::_level3Room[6];
const Room *Level::_room2_E = &Level::_level3Room[7];
const Room *Level::_room2_F = &Level::_level3Room[8];
const Room *Level::_room5_0 = &Level::_level5Room[0];
const Room *Level::_room5_1 = &Level::_level5Room[1];
const Room *Level::_room5_2 = &Level::_level5Room[2];
const Room *Level::_room5_3 = &Level::_level5Room[3];
const Room *Level::_room5_4 = &Level::_level5Room[4];
const Room *Level::_room5_5 = &Level::_level5Room[5];
const Room *Level::_room5_6 = &Level::_level5Room[6];
const Room *Level::_room5_7 = &Level::_level5Room[7];
const Room *Level::_room5_8 = &Level::_level5Room[8];
const Room *Level::_room5_9 = &Level::_level5Room[9];
const Room *Level::_room5_A = &Level::_level5Room[10];
const Room *Level::_room6_0 = &Level::_level6Room[0];
const Room *Level::_room6_1 = &Level::_level6Room[1];
const Room *Level::_room6_2 = &Level::_level6Room[2];
const Room *Level::_room6_3 = &Level::_level6Room[3];
const Room *Level::_room6_5 = &Level::_level7Room[0];
const Room *Level::_room6_6 = &Level::_level6Room[4];
const Room *Level::_room6_7 = &Level::_level7Room[1];
const Room *Level::_room6_8 = &Level::_level7Room[2];
const Room *Level::_room6_9 = &Level::_level7Room[3];
const Room *Level::_room6_A = &Level::_level7Room[4];
const Room *Level::_room8_0 = &Level::_level8Room[0];
const Room *Level::_room8_1 = &Level::_level8Room[1];
const Room *Level::_room8_2 = &Level::_level8Room[2];

}
