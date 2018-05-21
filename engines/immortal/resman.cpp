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

#include "common/array.h"
#include "common/debug.h"
#include "common/file.h"
#include "common/ptr.h"
#include "common/stream.h"
#include "audio/decoders/raw.h"
#include "audio/audiostream.h"

#include "immortal/immortal.h"
#include "immortal/resman.h"

namespace Immortal {

static byte *decodeFile(byte *buffer, int encodedFilesize, int *decodedFilesize);

ResourceManager::ResourceManager() {
	init();
}

void ResourceManager::init() {
	if (loadLibrary("IMM1.LIB").getCode() != Common::kNoError)
		error("Failed loading IMM1.LIB");
	if (loadLibrary("IMM2.LIB").getCode() != Common::kNoError)
		error("Failed loading IMM2.LIB");
}

/**
 * Extracts files from the library, converts and stores them.
 *
 * @param filename Filename of the library to load. Either "IMM1.LIB" or "IMM2.LIB".
 */
Common::Error ResourceManager::loadLibrary(const char *filename) {
	Common::File file;
	if (!file.open(filename)) {
		warning("%s could not be read!", filename);
		return Common::kReadingFailed;
	}

	AssetFile elements[2];
	AssetFile *prevElement = &elements[0];
	AssetFile *currentElement = &elements[1];

	file.skip(5);	// skip lib signature "EALIB"
	int numFiles = file.readUint16LE();
	assert(numFiles > 0);
	file.read(prevElement->_name, 13);
	file.skip(1);
	prevElement->_offset = file.readUint32LE();
	// read list terminator as well
	for (int i = 1; i < numFiles + 1; ++i) {
		file.read(currentElement->_name, 13);
		file.skip(1);
		currentElement->_offset = file.readUint32LE();
		prevElement->_size = currentElement->_offset - prevElement->_offset;
		prevElement->_data.reset(new byte[prevElement->_size]);
		int listNextEntry = file.pos();
		file.seek(prevElement->_offset);
		file.read(prevElement->_data.get(), prevElement->_size);
		file.seek(listNextEntry);

		// Audio file
		if (Common::matchString(prevElement->_name, "TTT##.BIN")) {
			int filenum = Common::String::format("%2s", prevElement->_name + 3).asUint64();
			convertMusic(prevElement, &_musicContainer[filenum]);
		// Sprite File
		} else if (Common::matchString(prevElement->_name, "*.ANM")) {
		// Fullscreen image
		} else if (Common::matchString(prevElement->_name, "*.BM")) {
			if (scumm_stricmp(prevElement->_name, "TITLEVGA.BM") == 0) {
				convertImage(prevElement, &_titleScreen);
			}
		}

		SWAP(prevElement, currentElement);
	}

	return Common::kNoError;
}

/**
 * Images are fullscreen 320x200 images loaded from .BM files.
 * A pixel is packed in a nibble and will be shifted into a byte.
 *
 * @param assetFile
 * @param dest
 * @return
 */
Common::Error ResourceManager::convertImage(AssetFile *assetFile, ImageData *dest) {
	int bufferSize;
	byte *buffer = decodeFile(assetFile->_data.get(), assetFile->_size, &bufferSize);
	byte *convertedBuffer = new byte[bufferSize * 2];
	// TODO: Split .BM and .AMN file handling
	if (bufferSize == 32000) {
		dest->_width = 320;
		dest->_height = 200;
	} else {
		dest->_width = 0;
		dest->_height = 0;
	}

	byte *itSource = buffer;
	byte *itDest = convertedBuffer;
	for (int y = 0; y < dest->_height; ++y) {
		for (int x = 0; x < dest->_width / 2; ++x, ++itSource) {
			byte pixel = *itSource & 0xF0;
			*itDest++ = (pixel >> 4);
			pixel = *itSource & 0x0F;
			*itDest++ = pixel;
		}
	}
	dest->_data = convertedBuffer;
	dest->_size = dest->_width * dest->_height;

	delete[] buffer;

	return Common::kNoError;
}

/**
 * Music files are MIDI based with a custom header that needs to be rewritten to a
 * type-0 MIDI header so SMF_MidiParser can read it.
 *
 * @param assetFile
 * @param dest
 * @return
 */
Common::Error ResourceManager::convertMusic(AssetFile *assetFile, MusicData *dest) {
	int decodeSize;
	byte *buffer = decodeFile(assetFile->_data.get(), assetFile->_size, &decodeSize);
	byte *volumePerChannel = buffer + 0x12;
	byte *channelMapping = buffer + 0x22;
	Common::copy(volumePerChannel, volumePerChannel + 0x10, dest->_volume);
	Common::copy(channelMapping, channelMapping + 9, dest->_adlibToMidiChannelTable);
	if (*(buffer + decodeSize - 1) == 0x80)
		dest->_loop = true;
	else
		dest->_loop = false;

	int headerSize = *buffer;
	// Addition byte for EOF Event FF 2F 00 (overwrites FC 80 or 81)
	int midiLength = decodeSize - headerSize + 1;
	// The header is 22 bytes + 1 byte for delta time of the first event
	byte midiHeader[23] = "MThd\x00\x00\x00\x06\x00\x00\x00\x01\x00\x22"
						  "MTrk\x00\x00\x00\x00";
	dest->_size = sizeof(midiHeader) + midiLength;
	byte *convertedBuffer = new byte[dest->_size];
	dest->_data = convertedBuffer;
	byte *it = convertedBuffer;
	WRITE_BE_INT32(midiHeader + 18, midiLength);
	it = Common::copy(midiHeader, ARRAYEND(midiHeader), it);
	it = Common::copy(buffer + headerSize, buffer + decodeSize, it);
	convertedBuffer[dest->_size - 3] = 0xFF;
	convertedBuffer[dest->_size - 2] = 0x2F;
	convertedBuffer[dest->_size - 1] = 0x00;
	delete[] buffer;

	return Common::kNoError;
}

MusicData *ResourceManager::getMusic(MusicId id) {
	return &_musicContainer[id];
}

ImageData *ResourceManager::getImage(ImageId id) {
	// TODO: Depending on video mode, return EGA or VGA title screen
	return &_titleScreen;
}

/**
 * Flag-based LZSS Decoder with integrated dictionary for files in *.LIB.
 *
 * @param inBuffer encoded file buffer
 * @param encodedFilesize size of the encoded file
 * @param decodedFilesize size of the decoded file
 * @return decoded file buffer
 */
static byte *decodeFile(byte *inBuffer, int encodedFilesize, int *decodedFilesize) {
	byte lzwBuffer[4096] = {};
	byte *outBuffer = nullptr;
	int lzwBufferIndex = sizeof(lzwBuffer) - 18;
	int inBufferIndex = 0;
	int outBufferIndex = 0;
	int flags = 0;

	memset(lzwBuffer, '\0', lzwBufferIndex);
	int fileSize = READ_LE_INT32(inBuffer);
	if (decodedFilesize)
		*decodedFilesize = fileSize;
	inBuffer += 4;
	outBuffer = new byte[fileSize];

	while (inBufferIndex < encodedFilesize && outBufferIndex < fileSize) {
		flags >>= 1;
		if ((flags & 0x100) == 0)
			flags = 0xFF00 | inBuffer[inBufferIndex++];

		if (flags & 1) {
			byte tmp = inBuffer[inBufferIndex++];
			outBuffer[outBufferIndex++] = tmp;
			lzwBuffer[lzwBufferIndex++] = tmp;
			lzwBufferIndex &= sizeof(lzwBuffer) - 1;
			continue;
		}

		int seqPosition = inBuffer[inBufferIndex++];
		int seqLength = inBuffer[inBufferIndex++];
		seqPosition |= ((seqLength & 0xF0) << 4);
		seqLength = (seqLength & 0xF) + 3; // sequence pos and length + terminator?

		for (; seqLength != 0; --seqLength) {
			seqPosition &= sizeof(lzwBuffer) - 1;
			byte c = lzwBuffer[seqPosition++];
			lzwBuffer[lzwBufferIndex++] = c;
			lzwBufferIndex &= sizeof(lzwBuffer) - 1;
			outBuffer[outBufferIndex++] = c;
		}
	}

	return outBuffer;
}

}
