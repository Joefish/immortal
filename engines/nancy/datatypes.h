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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef NANCY_DATATYPES_H
#define NANCY_DATATYPES_H

#include "common/str.h"
#include "common/rect.h"

namespace Common {
class SeekableReadStream;
}

namespace Nancy {

// Various data types we need to extract from chunks go here

// Describes a scene
struct SceneSummary {
    SceneSummary() { chunkData = nullptr; }
    SceneSummary(Common::SeekableReadStream *stream);
    ~SceneSummary() { delete[] chunkData; }

    Common::String description; // 0x00
    Common::String videoFile;   // 0x32
    //
    uint16 videoFormat;         // 0x3E, value is 1 or 2
    Common::String audioFile;   // 0x40
    int16 audioID;              // 0x4A
    uint16 audioVolume;         // 0x5A
    //
    uint16 verticalScrollDelta; // 0x72
    uint16 horizontalEdgeSize;  // 0x74
    uint16 verticalEdgeSize;    // 0x76
    uint16 slowMoveTimeDelta;   // 0x78
    uint16 fastMoveTimeDelta;   // 0x7A
    byte unknown7C;             // 0x7C, enum with 4 values
    //
    byte *chunkData;
};

// Describes the viewport
struct View {
    View() =default;
    View(Common::SeekableReadStream *stream);
    // The bounds of the destination rectangle on screen
    Common::Rect destination;
    // The bounds of the source rectangle (Background -> screen)
    Common::Rect source;
    // VideoFileFormat 1 rectangle bounds (video -> Background)
    Common::Rect f1Dest;
    // VideoFileFormat 2 rectangle bounds (video -> Background)
    Common::Rect f2Dest;
};

// Holds the coordinates for the bitmaps of all cursors
struct Cursors {
    Cursors() =default;
    Cursors(Common::SeekableReadStream *stream);
    Common::Rect rects[85];
    // The cursor gets set to this location at some point during PrimaryVideoSequence 
    uint16 primaryVideoCursorX;
    uint16 primaryVideoCursorY;
};

} // End of namespace Nancy

#endif // NANCY_DATATYPES_H