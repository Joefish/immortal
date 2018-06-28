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

#include "audio/mididrv.h"
#include "audio/midiparser.h"
#include "audio/midiplayer.h"

#include "immortal/resman.h"
#include "immortal/sound.h"

namespace Immortal {

MusicPlayer::MusicPlayer(ResourceManager *resMan)
	: _resMan(resMan)
	, _currentMusic(nullptr) {
	MidiPlayer::createDriver();
	int ec = _driver->open();
	if (ec == 0) {
		if (_nativeMT32)
			_driver->sendMT32Reset();
		else
			_driver->sendGMReset();

		_driver->setTimerCallback(this, &timerCallback);
	}
}

MusicPlayer::~MusicPlayer() {
	Audio::MidiPlayer::stop();
}

void MusicPlayer::send(uint32 msg) {
	// TODO: Instrument conversion is not working correctly (still sounds better than not doing it)
	byte channel = msg & 0x0F;
	bool isControllerEvent = ((msg & 0xF0) == 0xC0);

	if (!_nativeMT32) {
		channel = _currentMusic->_adlibToMidiChannelTable[channel];
		if (isControllerEvent) {
			int instrumentId = (msg >> 8) & 0xFF;
			msg = (msg & 0xFFFF00FF) | (MidiDriver::_mt32ToGm[instrumentId] << 8);
		}
	}

	Audio::MidiPlayer::send(msg);
}

void MusicPlayer::sendToChannel(byte channel, uint32 b) {
	if (!_channelsTable[channel]) {
		_channelsTable[channel] = (channel == 9) ? _driver->getPercussionChannel()
												 : _driver->allocateChannel();
		if (_channelsTable[channel])
			_channelsTable[channel]->volume(_channelsVolume[channel] * _masterVolume / 255);
	}

	if (_channelsTable[channel])
		_channelsTable[channel]->send(b);
}

void MusicPlayer::play(MusicId id) {
	_currentMusic = _resMan->getMusic(id);
	if (_parser)
		_parser->stopPlaying();

	for (int i = 0; i < MidiPlayer::kNumChannels; ++i) {
		// NOTE: Volume values in header may not for Adlib devices after all.. (MT32 instead)
		_channelsVolume[i] = _currentMusic->_volume[i];
	}

	MidiParser *parser = MidiParser::createParser_SMF();
	if (parser->loadMusic(_currentMusic->_data.get(), _currentMusic->_size)) {
		parser->setTrack(0);
		parser->setMidiDriver(this);
		parser->setTimerRate(_driver->getBaseTempo());
		parser->property(MidiParser::mpAutoLoop, _currentMusic->_loop);
		parser->property(MidiParser::mpCenterPitchWheelOnUnload, 1);
		_parser = parser;

		syncVolume();
		_isPlaying = true;
	}
}

}
