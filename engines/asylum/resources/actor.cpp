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
 * $URL$
 * $Id$
 *
 */

#include "asylum/resources/actor.h"

#include "asylum/resources/actionlist.h"
#include "asylum/resources/encounters.h"
#include "asylum/resources/object.h"
#include "asylum/resources/polygons.h"
#include "asylum/resources/worldstats.h"

#include "asylum/system/config.h"
#include "asylum/system/cursor.h"
#include "asylum/system/graphics.h"
#include "asylum/system/screen.h"
#include "asylum/system/speech.h"

#include "asylum/views/scene.h"

#include "asylum/asylum.h"
#include "asylum/data.h"
#include "asylum/staticres.h"

#include "common/endian.h"

namespace Asylum {

Actor::Actor(AsylumEngine *engine, ActorIndex index) : _vm(engine), _index(index) {
 	// Init all variables
 	_resourceId = kResourceNone;
 	_objectIndex = 0;
 	_frameIndex = 0;
 	_frameCount = 0;
 	_direction = kDirectionN;
 	_field_3C = 0;
 	_status = kActorStatusNone;
 	_field_44 = 0;
 	_priority = 0;
 	flags = 0;
 	_field_50 = 0;
 	_field_54 = 0;
 	_field_58 = 0;
 	_field_5C = 0;
 	_field_60 = 0;
 	_actionIdx3 = 0;
 	// TODO field_68 till field_617
 	memset(&_reaction, 0, sizeof(_reaction));
 	_field_638 = 0;
 	_walkingSound1 = 0;
 	_walkingSound2 = 0;
 	_walkingSound3 = 0;
 	_walkingSound4 = 0;
 	_field_64C = 0;
 	_field_650 = 0;
 	memset(_graphicResourceIds, 0 , sizeof(_graphicResourceIds));
 	memset(&_name, 0, sizeof(_name));
 	memset(&_field_830, 0, sizeof(_field_830));
 	memset(&_field_880, 0, sizeof(_field_880));
 	memset(&_field_8D0, 0, sizeof(_field_8D0));
 	_actionIdx2 = 0;
 	_field_924 = 0;
 	_lastScreenUpdate = 0;
 	_field_92C = 0;
 	actionType = 0;
 	_field_934 = 0;
 	_field_938 = 0;
 	_soundResourceId = kResourceNone;
 	_numberValue01 = 0;
 	_field_944 = 0;
 	_field_948 = 0;
 	_field_94C = 0;
 	_numberFlag01 = 0;
 	_numberStringWidth = 0;
 	_numberStringX = 0;
 	_numberStringY = 0;
 	memset(&_numberString01, 0, 8);
 	_field_968 = 0;
 	_field_96C = 0;
 	_field_970 = 0;
 	_field_974 = 0;
 	_field_978 = 0;
 	_actionIdx1 = 0;
 	_field_980 = 0;
 	_field_984 = 0;
 	_field_988 = 0;
 	_field_98C = 0;
 	_field_990 = 0;
 	_field_994 = 0;
 	_field_998 = 0;
 	_field_99C = 0;
 	_field_9A0 = 0;

	// Instance data
	_tickCount = -1;
}

Actor::~Actor() {
	// TODO destroy data

	// Zero passed pointers
	_vm = NULL;
}

/////////////////////////////////////////////////////////////////////////
// Loading
//////////////////////////////////////////////////////////////////////////
void Actor::load(Common::SeekableReadStream *stream) {
	if (!stream)
		error("[Actor::load] invalid stream");

	_point.x              = stream->readSint32LE();
	_point.y              = stream->readSint32LE();
	_resourceId          = (ResourceId)stream->readSint32LE();
	_objectIndex         = stream->readSint32LE();
	_frameIndex          = stream->readUint32LE();
	_frameCount          = stream->readUint32LE();
	_point1.x             = stream->readSint32LE();
	_point1.y             = stream->readSint32LE();
	_point2.x             = stream->readSint32LE();
	_point2.y             = stream->readSint32LE();

	_boundingRect.left   = (int16)(stream->readSint32LE() & 0xFFFF);
	_boundingRect.top    = (int16)(stream->readSint32LE() & 0xFFFF);
	_boundingRect.right  = (int16)(stream->readSint32LE() & 0xFFFF);
	_boundingRect.bottom = (int16)(stream->readSint32LE() & 0xFFFF);

	_direction  = (ActorDirection)stream->readSint32LE();
	_field_3C   = stream->readSint32LE();
	_status     = (ActorStatus)stream->readSint32LE();
	_field_44   = stream->readSint32LE();
	_priority   = stream->readSint32LE();
	flags       = stream->readSint32LE();
	_field_50   = stream->readSint32LE();
	_field_54   = stream->readSint32LE();
	_field_58   = stream->readSint32LE();
	_field_5C   = stream->readSint32LE();
	_field_60   = stream->readSint32LE();
	_actionIdx3 = stream->readSint32LE();

	// TODO skip field_68 till field_617
	stream->skip(0x5B0);

	for (int32 i = 0; i < 8; i++)
		_reaction[i] = stream->readSint32LE();

	_field_638     = stream->readSint32LE();
	_walkingSound1 = stream->readSint32LE();
	_walkingSound2 = stream->readSint32LE();
	_walkingSound3 = stream->readSint32LE();
	_walkingSound4 = stream->readSint32LE();
	_field_64C     = stream->readSint32LE();
	_field_650     = stream->readSint32LE();

	for (int32 i = 0; i < 55; i++)
		_graphicResourceIds[i] = (ResourceId)stream->readSint32LE();

	stream->read(_name, sizeof(_name));

	for (int32 i = 0; i < 20; i++)
		_field_830[i] = stream->readSint32LE();

	for (int32 i = 0; i < 20; i++)
		_field_880[i] = stream->readSint32LE();

	for (int32 i = 0; i < 20; i++)
		_field_8D0[i] = stream->readSint32LE();

	_actionIdx2 = stream->readSint32LE();
	_field_924  = stream->readSint32LE();
	_lastScreenUpdate = stream->readUint32LE();
	_field_92C  = stream->readSint32LE();
	actionType     = stream->readSint32LE();
	_field_934  = stream->readSint32LE();
	_field_938  = stream->readSint32LE();
	_soundResourceId = (ResourceId)stream->readSint32LE();
	_numberValue01 = stream->readSint32LE();
	_field_944  = stream->readSint32LE();
	_field_948  = stream->readSint32LE();
	_field_94C  = stream->readSint32LE();
	_numberFlag01 = stream->readSint32LE();
	_numberStringWidth  = stream->readSint32LE();
	_numberStringX  = stream->readSint32LE();
	_numberStringY  = stream->readSint32LE();
	stream->read(_numberString01, sizeof(_numberString01));
	_field_968  = stream->readSint32LE();
	_field_96C  = stream->readSint32LE();
	_field_970  = stream->readSint32LE();
	_field_974  = stream->readSint32LE();
	_field_978  = stream->readSint32LE();
	_actionIdx1 = stream->readSint32LE();
	_field_980  = stream->readSint32LE();
	_field_984  = stream->readSint32LE();
	_field_988  = stream->readSint32LE();
	_field_98C  = stream->readSint32LE();
	_field_990  = stream->readSint32LE();
	_field_994  = stream->readSint32LE();
	_field_998  = stream->readSint32LE();
	_field_99C  = stream->readSint32LE();
	_field_9A0  = stream->readSint32LE();
}

void Actor::loadData(Common::SeekableReadStream *stream) {
	_data.count = stream->readUint32LE();

	_data.field_4 = stream->readUint32LE();

	for (int32 i = 0; i < 240; i++)
		_data.field_8[i] = stream->readSint32LE();

	for (int32 i = 0; i < 120; i++)
		_data.field_3C8[i] = stream->readSint32LE();
}

/////////////////////////////////////////////////////////////////////////
// Update & status
//////////////////////////////////////////////////////////////////////////
void Actor::draw() {
	if (!isVisible())
		return;

	// Draw the actor
	Common::Point point;
	Common::Rect frameRect = GraphicResource::getFrameRect(_vm, _resourceId, _frameIndex);
	getScene()->adjustCoordinates(frameRect.left + _point.x + _point1.x, frameRect.top + _point.y + _point1.y, &point);

	// Compute frame index
	uint32 frameIndex = _frameIndex;
	if (_frameIndex >= _frameCount)
		frameIndex = 2 * _frameCount - (_frameIndex + 1);

	if (LOBYTE(flags) & kActorFlagMasked) {
		Object *object = getWorld()->objects[_objectIndex];
		Common::Point objPoint;
		getScene()->adjustCoordinates(object->x, object->y, &objPoint);

		getScreen()->addGraphicToQueueMasked(_resourceId, frameIndex, point, object->getResourceId(), objPoint, getGraphicsFlags(), _priority);

		// Update flags
		flags &= ~kActorFlagMasked;
	} else {
		getScreen()->addGraphicToQueue(_resourceId, frameIndex, point, getGraphicsFlags(), _field_96C, _priority);
	}
}

void Actor::update() {
	if (!isVisible())
		return;

	switch (_status) {
	default:
		break;

	case kActorStatus16:
		if (_index != getScene()->getPlayerIndex())
			break;

		if (getWorld()->chapter == 2) {
			updateStatus16_Chapter2();
		} else if (getWorld()->chapter == 11) {
			updateStatus16_Chapter11();
		}
		break;

	case kActorStatus17:
		if (getWorld()->chapter == kChapter2) {
			if (_index > 12) {
				if (_frameIndex <= _frameCount - 1) {
					++_frameIndex;
				} else {
					hide();
					getScene()->getActor(_index + 9)->hide();
				}
			}

			if (_index == 11) {
				if (_frameIndex <= _frameCount - 1) {
					// Looks like a simple check using the counter, since it doesn't seem to be used anywhere else
					if (getSharedData()->getUpdateCounter() <= 0) {
						getSharedData()->setUpdateCounter(getSharedData()->getUpdateCounter() + 1);
					} else {
						getSharedData()->setUpdateCounter(0);
						++_frameIndex;
					}
				} else {
					if (_vm->isGameFlagSet(kGameFlag556)) {
						Actor *player = getScene()->getActor();

						getSpeech()->playPlayer(453);
						hide();

						player->updateStatus(kActorStatus3);
						player->setResourceId(player->getResourcesId(35));
						player->setDirection(kDirectionS);
						player->setFrameCount(GraphicResource::getFrameCount(_vm, player->getResourceId()));

						getCursor()->hide();
						getScene()->getActor(0)->updateFromDirection(kDirectionS);

						// Queue script
						getScene()->actions()->queueScript(getWorld()->getActionAreaById(2696)->scriptIndex, getScene()->getPlayerIndex());

						_vm->setGameFlag(kGameFlag279);
						_vm->setGameFlag(kGameFlag368);

						player->setFrameIndex(0);
						getScene()->getActor(0)->setLastScreenUpdate(_vm->getTick());

						getSound()->playMusic(MAKE_RESOURCE(kResourcePackMusic, 1));

						getWorld()->musicCurrentResourceIndex = 1;

						if (getSound()->isPlaying(getWorld()->soundResourceIds[7]))
							getSound()->stop(getWorld()->soundResourceIds[7]);

						if (getSound()->isPlaying(getWorld()->soundResourceIds[6]))
							getSound()->stop(getWorld()->soundResourceIds[6]);

						if (getSound()->isPlaying(getWorld()->soundResourceIds[5]))
							getSound()->stop(getWorld()->soundResourceIds[5]);

						_vm->setGameFlag(kGameFlag1131);
					} else {
						updateGraphicData(25);
						_vm->setGameFlag(kGameFlag556);
					}
				}
			}

			if (_index == getScene()->getPlayerIndex()) {
				if (_frameIndex <= _frameCount - 1) {
					++_frameIndex;
				} else {
					_vm->clearGameFlag(kGameFlag239);
					getScene()->getActor(10)->updateStatus(kActorStatus14);
					hide();
					_vm->setGameFlag(kGameFlag238);

					// Queue script
					getScene()->actions()->queueScript(getWorld()->getActionAreaById(1000)->scriptIndex, getScene()->getPlayerIndex());
				}
			}

		} else if (getWorld()->chapter == kChapter11) {
			if (_index == getScene()->getPlayerIndex()) {
				if (_frameIndex <= _frameCount - 1)
					++_frameIndex;
				else
					getScene()->resetActor0();
			}

			if (_index >= 10)
				updateStatus17_Chapter2();
		}
		break;

	case kActorStatus15:
		if (getWorld()->chapter == kChapter2) {
			if (_index > 12)
				updateStatus15_Chapter2();

			if (_index == getScene()->getPlayerIndex())
				updateStatus15_Chapter2_Player();

			if (_index == 11)
				updateStatus15_Chapter2_Actor11();

		} else if (getWorld()->chapter == kChapter11) {
			if (_index >= 10 && _index < 16)
				updateStatus15_Chapter11();

			if (_index == getScene()->getPlayerIndex())
				updateStatus15_Chapter11_Player();
		}
		break;

	case kActorStatus18:
		if (getWorld()->chapter == kChapter2) {
			if (_index > 12)
				updateStatus18_Chapter2();

			if (_index == 11)
				updateStatus18_Chapter2_Actor11();
		}
		break;

	case kActorStatusDisabled:
		_frameIndex = (_frameIndex + 1) % _frameCount;

		if (_vm->screenUpdateCount - _lastScreenUpdate > 300) {
			if (_vm->getRandom(100) < 50) {
				if (!getSpeech()->getSoundResourceId() || !getSound()->isPlaying(getSpeech()->getSoundResourceId())) {
					if (isDefaultDirection(10))
						updateStatus(kActorStatus9);
				}
			}
			_lastScreenUpdate = _vm->screenUpdateCount;
		}
		break;

	case kActorStatus12:
		if (getWorld()->chapter == kChapter2) {
			if (_index > 12)
				updateStatus12_Chapter2();

			if (_index == 11)
				updateStatus12_Chapter2_Actor11();

			return;
		} else if (getWorld()->chapter == kChapter11) {
			switch (_index)	{
			default:
				break;

			case 1:
				updateStatus12_Chapter11_Actor1();
				return;

			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				updateStatus12_Chapter11();
				return;

			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				return;
			}
		}
		// Fallback to next case

	case kActorStatus1:
		// TODO: do actor direction
		error("[Actor::update] kActorStatus1 / kActorStatus12 case not implemented");
		break;

	case kActorStatus2:
	case kActorStatus13:
		// TODO: do actor direction
		error("[Actor::update] kActorStatus2 / kActorStatus13 case not implemented");
		break;

	case kActorStatus3:
	case kActorStatus19:
		updateStatus3_19();
		break;

	case kActorStatus7:
		if (getSharedData()->getActorEnableForStatus7()) {
			getSharedData()->setActorEnableForStatus7(false);
			enable();
		}
		break;

	case kActorStatusEnabled:
		if (_field_944 != 5)
			updateStatusEnabled();
		break;

	case kActorStatus14:
		updateStatus14();
		break;

	case kActorStatus21:
		updateStatus21();
		break;

	case kActorStatus9:
		updateStatus9();
		break;

	case kActorStatus6:
	case kActorStatus10:
		_frameIndex = (_frameIndex + 1) % _frameCount;
		break;

	case kActorStatus8:
		if (getSharedData()->getFlag(kFlagEncounter2)
		 || !_soundResourceId
		 || getSound()->isPlaying(_soundResourceId)) {
			_frameIndex = (_frameIndex + 1) % _frameCount;
		} else {
			enable();
			_soundResourceId = kResourceNone;
		}
		break;
	}

	if (_soundResourceId && getSound()->isPlaying(_soundResourceId))
		setVolume();

	if (_index != getScene()->getPlayerIndex() && getWorld()->chapter != kChapter9)
		error("[Actor::update] call to actor sound functions missing!");

	updateDirection();

	if (_field_944 != 5)
		updateFinish();
}


void Actor::updateStatus(ActorStatus actorStatus) {
	switch (actorStatus) {
	default:
		break;

	case kActorStatus1:
	case kActorStatus12:
		if ((getWorld()->chapter == kChapter2
		 && _index == getScene()->getPlayerIndex() && (_status == kActorStatus18 || _status == kActorStatus16 || _status == kActorStatus17))
		 || (_status != kActorStatusEnabled && _status != kActorStatus9 && _status != kActorStatus14 && _status != kActorStatus15 && _status != kActorStatus18))
			return;

		updateGraphicData(0);

		// Force status in some cases
		if (_status == kActorStatus14 || _status == kActorStatus15 || _status == kActorStatus18) {
			_status = kActorStatus12;
			return;
		}
		break;

	case kActorStatus2:
	case kActorStatus13:
		updateGraphicData(0);
		break;

	case kActorStatus3:
	case kActorStatus19:
		if (!strcmp(_name, "Big Crow"))
			_status = kActorStatusEnabled;
		break;

	case kActorStatusEnabled:
	case kActorStatus6:
	case kActorStatus14:
		updateGraphicData(5);
		break;

	case kActorStatusDisabled:
		updateGraphicData(15);
		_resourceId = _graphicResourceIds[(_direction > kDirectionS ? kDirection8 - _direction : _direction) + 15];

		// TODO set word_446EE4 to -1. This global seems to be used with screen blitting
		break;

	case kActorStatus7:
		if (getWorld()->chapter == kChapter2 && _index == 10 && _vm->isGameFlagSet(kGameFlag279)) {
			Actor *actor = getScene()->getActor(0);
			actor->getPoint1()->x = _point2.x + _point1.x - actor->getPoint2()->x;
			actor->getPoint1()->y = _point2.y + _point1.y - actor->getPoint2()->y;
			actor->setDirection(kDirectionS);

			getScene()->setPlayerActorIndex(0);

			// Hide this actor and the show the other one
			hide();
			actor->show();

			_vm->clearGameFlag(kGameFlag279);

			getCursor()->show();
		}
		break;

	case kActorStatus8:
	case kActorStatus10:
	case kActorStatus17:
		updateGraphicData(20);
		break;

	case kActorStatus9:
		if (getSharedData()->getFlag(kFlagEncounter2))
			return;

		if (_vm->getRandomBit() == 1 && isDefaultDirection(15))
			updateGraphicData(15);
		else
			updateGraphicData(10);
		break;

	case kActorStatus15:
	case kActorStatus16:
		updateGraphicData(actorStatus == kActorStatus15 ? 10 : 15);
		break;

	case kActorStatus18:
		if (getWorld()->chapter == kChapter2) {
			GraphicResource *resource = new GraphicResource(_vm);
			_frameIndex = 0;

			if (_index > 12)
				_resourceId = _graphicResourceIds[_direction + 30];

			if (getScene()->getPlayerIndex() == _index) {
				resource->load(_resourceId);
				_frameIndex = resource->count() - 1;
			}

			if (_index == 11)
				_resourceId = _graphicResourceIds[getScene()->getGlobalDirection() > 4 ? 8 - getScene()->getGlobalDirection() : getScene()->getGlobalDirection()];

			// Reload the graphic resource if the resource ID has changed
			if (resource->getResourceId() != _resourceId)
				resource->load(_resourceId);

			_frameCount = resource->count();

			delete resource;
		}
		break;
	}

	_status = actorStatus;
}

/////////////////////////////////////////////////////////////////////////
// Direction & position
//////////////////////////////////////////////////////////////////////////

void Actor::updateDirection() {
	if(_field_970) {
		// TODO
		// This update is only ever done if action script 0x5D is called, and
		// the resulting switch sets field_970. Investigate 401A30 for further
		// details
		error("[Actor::updateDirection] logic not implemented");
	}
}

void Actor::updateFromDirection(ActorDirection actorDirection) {
	_direction = actorDirection;

	if (_field_944 == 5)
		return;

	switch (_status) {
	default:
		break;

	case kActorStatusDisabled:
	case kActorStatusEnabled:
	case kActorStatus14:
		_resourceId = _graphicResourceIds[(actorDirection > kDirectionS ? kDirection8 - actorDirection : actorDirection) + 5];
		_frameCount = GraphicResource::getFrameCount(_vm, _resourceId);
		break;

	case kActorStatus18:
		if (getWorld()->chapter == kChapter2)
			if (_index == 11) // we are actor 11
				_resourceId = _graphicResourceIds[(actorDirection > kDirectionS) ? kDirection8 - actorDirection : actorDirection];
		break;

	case kActorStatus1:
	case kActorStatus2:
	case kActorStatus12:
		_resourceId = _graphicResourceIds[(actorDirection > kDirectionS ? kDirection8 - actorDirection : actorDirection)];
		break;

	case kActorStatus8:
		_resourceId = _graphicResourceIds[(actorDirection > kDirectionS ? kDirection8 - actorDirection : actorDirection) + 20];
		break;
	}
}

void Actor::faceTarget(uint32 target, DirectionFrom from) {
	debugC(kDebugLevelActor, "[Actor::faceTarget] Facing target %d using direction from %d", target, from);

	Common::Point point;

	switch (from) {
	default:
		error("[Actor::faceTarget] Invalid direction input: %d (should be 0-3)", from);

	case kDirectionFromObject: {
		Object *object = getWorld()->getObjectById((ObjectId)target);
		if (!object) {
			warning("[Actor::faceTarget] No Object found for id %d", target);
			return;
		}

		Common::Rect frameRect = GraphicResource::getFrameRect(_vm, object->getResourceId(), object->getFrameIndex());

		point.x = Common::Rational(frameRect.width(), 2).toInt()  + object->x;
		point.y = Common::Rational(frameRect.height(), 2).toInt() + object->y;
		}
		break;

	case kDirectionFromPolygons: {
		int32 actionIndex = getWorld()->getActionAreaIndexById(target);
		if (actionIndex == -1) {
			warning("[Actor::faceTarget] No ActionArea found for id %d", target);
			return;
		}

		PolyDefinitions *polygon = &getScene()->polygons()->entries[getWorld()->actions[actionIndex]->polyIdx];

		point.x = polygon->boundingRect.left + (polygon->boundingRect.right  - polygon->boundingRect.left) / 2;
		point.y = polygon->boundingRect.top  + (polygon->boundingRect.bottom - polygon->boundingRect.top)  / 2;
		}
		break;

	case kDirectionFromActor:
		point.x = _point1.x + _point2.x;
		point.y = _point1.y + _point2.y;
		break;

	case kDirectionFromParameters:
		point.x = point.y = target;
		break;
	}

	Common::Point mid(_point1.x + _point2.x, _point1.y + _point2.y);
	updateFromDirection(direction(mid, point));
}

void Actor::setPosition(int32 newX, int32 newY, ActorDirection newDirection, uint32 frame) {
	_point1.x = newX - _point2.x;
	_point1.y = newY - _point2.y;

	if (_direction != kDirection8)
		updateFromDirection(newDirection);

	if (frame > 0)
		_frameIndex = frame;
}

/////////////////////////////////////////////////////////////////////////
// Misc
//////////////////////////////////////////////////////////////////////////
void Actor::stopSound() {
	if (_soundResourceId && getSound()->isPlaying(_soundResourceId))
		getSound()->stop(_soundResourceId);
}

Common::String Actor::toString(bool shortString) {
	Common::String output;

	output += Common::String::format("Actor %d: %s\n", _index, _name);
	if (!shortString) {
		output += Common::String::format("resourceId:   %d (0x%X): \n", _resourceId, _resourceId);
		output += Common::String::format("objectIndex:  %d: \n", _objectIndex);
		output += Common::String::format("frameIndex:   %d: \n", _frameIndex);
		output += Common::String::format("frameCount:   %d: \n", _frameCount);
		output += Common::String::format("(x, y):       (%d , %d): \n", _point.x, _point.y);
		output += Common::String::format("(x1, y1):     (%d , %d): \n", _point1.x, _point1.y);
		output += Common::String::format("(x2, y2):     (%d , %d): \n", _point2.x, _point2.y);
		output += Common::String::format("flags:        %d: \n", flags);
		output += Common::String::format("actionType:   %d: \n", actionType);
		output += Common::String::format("boundingRect: top[%d] left[%d] right[%d] bottom[%d]: \n", _boundingRect.top, _boundingRect.left, _boundingRect.right, _boundingRect.bottom);
		output += Common::String::format("direction:    %d: \n", _direction);
		output += Common::String::format("field_3C:     %d: \n", _field_3C);
		output += Common::String::format("status:       %d: \n", _status);
		output += Common::String::format("field_44:     %d: \n", _field_44);
		output += Common::String::format("priority:     %d: \n", _priority);
	}

	return output;
}

//////////////////////////////////////////////////////////////////////////
// Unknown methods
//////////////////////////////////////////////////////////////////////////

bool Actor::isResourcePresent() const {
	if (_status != kActorStatus9)
		return false;

	int index;
	for (index = 10; index < 20; index++) {
		if (_graphicResourceIds[index] == _resourceId)
			break;
	}

	return (index >= 15);
}

bool Actor::process(int32 actorX, int32 actorY) {
	error("[Actor::process] not implemented!");
}

void Actor::processStatus(int32 actorX, int32 actorY, bool doSpeech) {
	if (process(actorX, actorY)) {
		if (_status <= kActorStatus11)
			updateStatus(kActorStatus2);
		else
			updateStatus(kActorStatus13);
	} else if (doSpeech) {
		getSpeech()->playIndexed(1);
	}
}

void Actor::process_401830(int32 field980, int32 actionAreaId, int32 field978, int field98C, int32 field990, int32 field974, int32 param8, int32 param9) {
	error("[Actor::process_401830] not implemented!");
}

bool Actor::process_408B20(Common::Point *point, ActorDirection direction, int count, bool hasDelta) {
	error("[Actor::process_408B20] not implemented!");
}

void Actor::process_41BC00(int32 reactionIndex, int32 numberValue01Add) {
	if (reactionIndex > 16)
		return;

	uint32 count = 0;
	for (int i = 0; i < 8; i++)
		if (_reaction[i])
			count++;

	if (count == 8)
		return;

	if (!process_41BDB0(reactionIndex, false))
		_reaction[count] = reactionIndex;

	if (numberValue01Add)
		_numberValue01 += numberValue01Add;

	getSound()->playSound(MAKE_RESOURCE(kResourcePackHive, 0));
}

void Actor::process_41BCC0(int32 reactionIndex, int32 numberValue01Substract) {
	if (reactionIndex > 16)
		return;

	if (numberValue01Substract) {
		_numberValue01 -= numberValue01Substract;
		if (_numberValue01 < 0)
			_numberValue01 = 0;
	}

	if (!numberValue01Substract || !_numberValue01) {

		uint32 count = 0;
		for (int i = 0; i < 8; i++)
			if (_reaction[i])
				count++;

		if (count == 8)
			return;

		if (count == 7) {
			_reaction[7] = 0;
		} else {
			memcpy(&_reaction[count], &_reaction[count + 1], 28 - 4 * count);
			_reaction[7] = 0;
		}
	}
}

bool Actor::process_41BDB0(int32 reactionIndex, int32 testNumberValue01) {
	if (reactionIndex > 16)
		return false;

	uint32 count = 0;
	for (int i = 0; i < 8; i++)
		if (_reaction[i])
			count++;

	if (count == 8)
		return false;

	if (testNumberValue01)
		return _numberValue01 >= testNumberValue01;

	return true;
}

void Actor::updateAndDraw() {
	error("[Actor::update_40DE20] not implemented!");
}

void Actor::update_409230() {
	updateStatus(_status <= 11 ? kActorStatusEnabled : kActorStatus14);
	_data.field_4 = 0;
}

//////////////////////////////////////////////////////////////////////////
// Static update methods
//////////////////////////////////////////////////////////////////////////
void Actor::enableActorsChapter2(AsylumEngine *engine) {
	engine->clearGameFlag(kGameFlag438);
	engine->clearGameFlag(kGameFlag439);
	engine->clearGameFlag(kGameFlag440);
	engine->clearGameFlag(kGameFlag441);
	engine->clearGameFlag(kGameFlag442);

	// Reset shared data
	engine->getData()->resetActorData();

	engine->scene()->getActor(13)->enable();
	engine->scene()->getActor(13)->processStatus(2300, 71, false);

	engine->scene()->getActor(14)->enable();
	engine->scene()->getActor(14)->processStatus(2600, 1300, false);

	engine->scene()->getActor(15)->enable();
	engine->scene()->getActor(15)->processStatus(2742, 615, false);

	engine->scene()->getActor(16)->enable();
	engine->scene()->getActor(16)->processStatus(2700, 1200, false);

	engine->scene()->getActor(17)->enable();
	engine->scene()->getActor(17)->processStatus(2751, 347, false);

	engine->scene()->getActor(18)->enable();
	engine->scene()->getActor(18)->processStatus(2420, 284, false);

	engine->scene()->getActor(19)->enable();
	engine->scene()->getActor(19)->processStatus(2800, 370, false);

	engine->scene()->getActor(20)->enable();
	engine->scene()->getActor(20)->processStatus(1973, 1, false);

	engine->scene()->getActor(21)->enable();
	engine->scene()->getActor(21)->processStatus(2541, 40, false);

	error("[Actor::enableActorsChapter2] Missing update shared data part!");
}

void Actor::updatePlayerChapter9(AsylumEngine *engine, int type) {
	error("[Actor::updatePlayerChapter9] Not implemented!");
}

//////////////////////////////////////////////////////////////////////////
// Update methods
//////////////////////////////////////////////////////////////////////////

void Actor::updateStatus3_19() {
	if (getWorld()->chapter != kChapter2 || _frameIndex != 6 || _status == kActorStatus3) { /* Original check: _status  <= kActorStatus11 */
		if (_frameIndex < _frameCount - 1) {
			++_frameIndex;
		} else {
			if (_status == kActorStatus3)
				updateStatus(kActorStatus7);
			else
				updateStatus(kActorStatus20);
		}
	} else {
		if (_index == getScene()->getPlayerIndex())
			updateStatus19_Player();

		++_frameIndex;
	}
}

void Actor::updateStatus19_Player() {
	updatePumpkin(kGameFlag263, kGameFlag270, kObjectPumpkin2Dies, kObjectPumpkin2Loop);
	updatePumpkin(kGameFlag264, kGameFlag271, kObjectPumpkin3Dies, kObjectPumpkin3Loop);
	updatePumpkin(kGameFlag265, kGameFlag272, kObjectPumpkin4Dies, kObjectPumpkin4Loop);
	updatePumpkin(kGameFlag266, kGameFlag273, kObjectPumpkin5Dies, kObjectPumpkin5Loop);
	updatePumpkin(kGameFlag267, kGameFlag274, kObjectPumpkin6Dies, kObjectPumpkin6Loop);
	updatePumpkin(kGameFlag268, kGameFlag275, kObjectPumpkin7Dies, kObjectPumpkin7Loop);
	updatePumpkin(kGameFlag269, kGameFlag276, kObjectPumpkin1Dies, kObjectPumpkin1Loop);
}

void Actor::updatePumpkin(GameFlag flagToCheck, GameFlag flagToSet, ObjectId objectToUpdate, ObjectId objectToDisable) {
	if (_vm->isGameFlagSet(flagToCheck)) {
		_vm->setGameFlag(flagToSet);
		_vm->clearGameFlag(flagToCheck);

		getSharedData()->setActorUpdateFlag2(getSharedData()->getActorUpdateFlag2() + 1);

		getWorld()->getObjectById(objectToUpdate)->setNextFrame(8);
		getSound()->playSound(getWorld()->soundResourceIds[17], false, Config.sfxVolume - 10);
		getWorld()->getObjectById(objectToDisable)->disable();
	}
}

void Actor::updateStatusEnabled() {
	if (_frameCount == 0)
		error("[Actor::updateStatusEnabled] Actor has no frame!");

	_frameIndex = (_frameIndex + 1) % _frameCount;

	if (_vm->screenUpdateCount - _lastScreenUpdate > 300) {
		// All actors except Crow
		if (strcmp((char *)&_name, "Crow")) {
			if (_vm->getRandom(100) < 50
			 && (!getSpeech()->getSoundResourceId() || !getSound()->isPlaying(getSpeech()->getSoundResourceId()))
			 && isDefaultDirection(10))
				updateStatus(kActorStatus9);

			_lastScreenUpdate = _vm->screenUpdateCount;
		}
	}

	// Actor: Player
	if (_index == getScene()->getPlayerIndex()) {
		if (_vm->lastScreenUpdate && (_vm->screenUpdateCount - _vm->lastScreenUpdate) > 500) {

			if (_vm->isGameFlagNotSet(kGameFlagScriptProcessing)
			 && isVisible()
			 && !getSharedData()->getFlag(kFlagEncounter2)
			 && !getSpeech()->getSoundResourceId()) {
				if (_vm->getRandom(100) < 50) {
					if (getWorld()->chapter == kChapter13)
						getSpeech()->playPlayer(507);
					else
						getSpeech()->playIndexed(4);
				}
			}
			_lastScreenUpdate = _vm->screenUpdateCount;
			_vm->lastScreenUpdate = _vm->screenUpdateCount;
		}

		return;
	}

	// Actor:: BigCrow
	if (!strcmp(_name, "Big Crow")) {
		if (_vm->getRandom(10) < 5) {
			switch (_vm->getRandom(4)) {
			default:
				break;

			case 0:
				setPosition(10, 1350, kDirectionN, 0);
				processStatus(1460, -100, false);
				break;

			case 1:
				setPosition(300, 0, kDirectionN, 0);
				processStatus(1700, 1400, false);
				break;

			case 2:
				setPosition(1560, -100, kDirectionN, 0);
				processStatus(-300, 1470, false);
				break;

			case 3:
				setPosition(1150, 1400, kDirectionN, 0);
				processStatus(-250, 0, false);
				break;
			}
		}

		return;
	}

	// All other actors
	if (getWorld()->chapter != kChapter2 || _index != 8) {
		if (_field_944 == 4) {
			Common::Rect frameRect = GraphicResource::getFrameRect(_vm, getWorld()->backgroundImage, 0);
			processStatus(rnd(frameRect.width() + 200) - 100, rnd(frameRect.height() + 200) - 100, false);
		} else {
			// Actor: Crow
			if (rnd(1000) < 5 || !strcmp(_name, "Crow")) {
				if (_actionIdx2 != -1) {

					// Process action area
					int32 areaIndex = getWorld()->getRandomActionAreaIndexById(_actionIdx2);
					if (areaIndex != -1) {

						ActionArea *area = getWorld()->actions[areaIndex];
						PolyDefinitions *poly = &getScene()->polygons()->entries[area->polyIdx];

						Common::Point pt(poly->boundingRect.left + rnd(poly->boundingRect.width()),
						                 poly->boundingRect.top + rnd(poly->boundingRect.height()));

						if (!getSharedData()->getActorUpdateEnabledCheck()) {
							if (getScene()->isInActionArea(pt, area)) {
								Common::Point *polyPoint = &poly->points[rnd(poly->count())];
								processStatus(polyPoint->x, polyPoint->y, false);
							} else {
								processStatus(pt.x, pt.y, false);
							}
						}
					}
				}
			}
		}
	} else {
		switch (getSharedData()->getActorUpdateEnabledCounter()) {
		default:
			break;

		case 0:
			updateStatusEnabledProcessStatus(1055, 989, 1, 1088, 956);
			break;

		case 1:
			updateStatusEnabledProcessStatus(1088, 956, 2, _point1.x + _point2.x, 900);
			break;

		case 2:
			updateStatusEnabledProcessStatus(1088, 900, 3, 1018, 830);
			break;

		case 3:
			updateStatusEnabledProcessStatus(1018, 830, 4, 970, 830);
			break;

		case 4:
			updateStatusEnabledProcessStatus(970, 830, 5, 912, 936);
			break;

		case 5:
			updateStatusEnabledProcessStatus(912, 936, 0, 1055, 989);
			break;
		}
	}
}

void Actor::updateStatusEnabledProcessStatus(int32 testX, int32 testY, uint32 counter, int32 setX, int32 setY) {
	int32 xsum = _point1.x + _point2.x;
	int32 ysum = _point1.y + _point2.y;

	if (xsum != testX || ysum != testY) {
		if (rnd(1000) < 5)
			processStatus(testX, testY, false);
	} else {
		getSharedData()->setActorUpdateEnabledCounter(counter);

		if (rnd(1000) < 5)
			processStatus(setX, setY, false);
	}
}

void Actor::updateStatus9() {
	if (_index == getScene()->getPlayerIndex()
	 && getWorld()->chapter != kChapter9
	 && getWorld()->actorType == 0
	 && _frameIndex == 0
	 && isResourcePresent()) {
		if (!getSpeech()->getSoundResourceId() || !getSound()->isPlaying(getSpeech()->getSoundResourceId()))
			getSpeech()->playPlayer(13);
	}

	++_frameIndex;
	if (_frameIndex == _frameCount) {
		enable();
		_lastScreenUpdate = _vm->screenUpdateCount;
	}
}

void Actor::updateStatus12_Chapter2() {
	error("[Actor::updateStatus12_Chapter2] not implemented!");
}

void Actor::updateStatus12_Chapter2_Actor11() {
	error("[Actor::updateStatus12_Chapter2_Actor11] not implemented!");
}

void Actor::updateStatus12_Chapter11_Actor1() {
	// Original seems to have lots of dead code here
	Actor *actor0 = getScene()->getActor(0);
	if (actor0->isVisible())
		return;

	if (_vm->isGameFlagNotSet(kGameFlag560))
		_frameIndex = (_frameIndex + 1) & _frameCount;

	if (getWorld()->tickCount1 < (int32)_vm->getTick()
	 && !_frameIndex
	 && _vm->isGameFlagNotSet(kGameFlag560)) {
		_vm->setGameFlag(kGameFlag560);
		hide();
		updateStatus(kActorStatusEnabled);
		actor0->updateStatus(kActorStatusEnabled);

		getWorld()->field_E848C = 0;
		getScene()->actions()->queueScript(getWorld()->getActionAreaById(1574)->scriptIndex, 1);
	}
}

void Actor::updateStatus12_Chapter11() {
	if (!_frameIndex)
		getSound()->playSound(getWorld()->soundResourceIds[6]);

	++_frameIndex;

	if (_frameIndex >= _frameCount) {
		_frameIndex = 0;
		updateStatus(kActorStatus14);
		getWorld()->tickValueArray[_index] = rnd(4000) + _vm->getTick();
	}

	Common::Point *vector1 = getSharedData()->getVector1();
	Common::Point *vector2 = getSharedData()->getVector2();
	Actor *actor0 = getScene()->getActor(0);

	vector1->x = actor0->getPoint1()->x + actor0->getPoint2()->x;
	vector1->y = actor0->getPoint1()->y + actor0->getPoint2()->y - 5;

	vector2->x = _point1.x + _point2.x;
	vector2->y = _point1.y + _point2.y;

	updateCoordinates(*vector1, *vector2);
}

void Actor::updateStatus14() {
	_frameIndex = (_frameIndex + 1) % _frameCount;
	_lastScreenUpdate = _vm->screenUpdateCount;

	switch (getWorld()->chapter) {
	default:
		break;

	case kChapter2:
		if (_index == 11)
			updateStatus(kActorStatus12);
		else if (_index > 12)
			updateStatus14_Chapter2();
		break;

	case kChapter11:
		if (_index >= 10 && _index < 16)
			updateStatus14_Chapter11();
		break;
	}
}

void Actor::updateStatus14_Chapter2() {
	if (!getSharedData()->getData2(_index)) {
		updateStatus(kActorStatus12);
		return;
	}


	error("[Actor::updateStatus14_Chapter2] not implemented!");
}

void Actor::updateStatus14_Chapter11() {
	Common::Point *vector1 = getSharedData()->getVector1();
	Common::Point *vector2 = getSharedData()->getVector2();
	Actor *actor0 = getScene()->getActor(0);

	vector1->x = actor0->getPoint1()->x + actor0->getPoint2()->x;
	vector1->y = actor0->getPoint1()->y + actor0->getPoint2()->y - 5;

	vector2->x = _point1.x + _point2.x;
	vector2->y = _point1.y + _point2.y;

	if (getWorld()->tickValueArray[_index] == -666)
		getWorld()->tickValueArray[_index] = rnd(4000) + _vm->getTick();

	faceTarget(kActorMax, kDirectionFromActor);
	updateCoordinates(*vector1, *vector2);

	if (getWorld()->tickValueArray[_index] < (int)_vm->getTick()) {
		if (distance(*vector1, *vector2) >= 75) {
			getWorld()->tickValueArray[_index] = rnd(1000) + 2000 + _vm->getTick();
		} else {
			if (actor0->getStatus() == kActorStatus12 || actor0->getStatus() == kActorStatus14 || actor0->getStatus() == kActorStatus15)
				updateStatus(kActorStatus15);

			getWorld()->tickValueArray[_index] = -666;
		}
	}
}

void Actor::updateStatus15_Chapter2() {
	error("[Actor::updateStatus15_Chapter2] not implemented!");
}

void Actor::updateStatus15_Chapter2_Player() {
	error("[Actor::updateStatus15_Chapter2_Player] not implemented!");
}

void Actor::updateStatus15_Chapter2_Helper() {
	// we are the current player
	Actor *actor11 = getScene()->getActor(11);
	Actor *actor40 = getScene()->getActor(40);

	Common::Point point(_point1.x + _point2.x, _point1.y + _point2.y);
	Common::Point point11(actor11->getPoint1()->x + actor11->getPoint2()->x, actor11->getPoint1()->y + actor11->getPoint2()->y);

	if (actor11->getStatus() == kActorStatus15 && distance(point, point11) < 100) {
		Actor *actor = getScene()->getActor(getSharedData()->getData(38));

		actor40->show();
		actor40->setFrameIndex(0);
		actor40->getPoint1()->x = actor->getPoint1()->x;
		actor40->getPoint1()->y = actor->getPoint1()->y;

		if (actor11->getFrameIndex() <= 7) {
			getSound()->playSound(getWorld()->soundResourceIds[9], false, Config.sfxVolume - 10);
		} else if (getSharedData()->getData(36) <= 6) {
			getSound()->playSound(getWorld()->soundResourceIds[9], false, Config.sfxVolume - 10);
		} else {
			getScene()->getActor(10)->updateStatus(kActorStatus17);
			getSound()->playSound(getWorld()->soundResourceIds[10], false, Config.sfxVolume - 10);
		}
	}
}

bool Actor::updateStatus15_isNoVisibleOrStatus17() {
	return (!isVisible() || _status == kActorStatus17);
}

void Actor::updateStatus15_Chapter2_Actor11() {
	error("[Actor::updateStatus15_Chapter2_Actor11] not implemented!");
}

void Actor::updateStatus15_Chapter11() {
	Common::Point *vector1 = getSharedData()->getVector1();
	Common::Point *vector2 = getSharedData()->getVector2();
	Actor *actor0 = getScene()->getActor(0);

	// Update vectors
	vector1->x = actor0->getPoint1()->x + actor0->getPoint2()->x;
	vector1->y = actor0->getPoint1()->y + actor0->getPoint2()->y - 5;

	vector2->x = actor0->getPoint1()->x + actor0->getPoint2()->x;
	vector2->y = actor0->getPoint1()->y + actor0->getPoint2()->y;

	updateCoordinates(*vector1, *vector2);

	++_frameIndex;
	if (_frameIndex >= _frameCount)
		updateStatus(kActorStatus14);

	if (_frameIndex == 14) {
		if (Actor::distance(*vector1, *vector2) < 75) {

			actor0->updateStatus(kActorStatus16);
			++getWorld()->field_E848C;

			getSound()->stop(getWorld()->soundResourceIds[3]);
			getSound()->stop(getWorld()->soundResourceIds[4]);
			getSound()->stop(getWorld()->soundResourceIds[5]);

			getSpeech()->playPlayer(131);
		}
	}
}

void Actor::updateStatus15_Chapter11_Player() {
	error("[Actor::updateStatus15_Chapter11_Player] not implemented!");
}

void Actor::updateStatus16_Chapter2() {
	// We are sure to be the current player

	++_frameIndex;

	if (_frameIndex > _frameCount - 1) {
		if (getSharedData()->getData(40) <= 2) {
			_frameIndex = 0;
			updateStatus(kActorStatus14);
		} else {
			_vm->clearGameFlag(kGameFlag438);
			_vm->clearGameFlag(kGameFlag439);
			_vm->clearGameFlag(kGameFlag440);
			_vm->clearGameFlag(kGameFlag441);
			_vm->clearGameFlag(kGameFlag442);

			getSpeech()->playPlayer(53);

			_vm->setGameFlag(kGameFlag219);

			_frameIndex = 0;
			updateStatus(kActorStatus17);

			_vm->clearGameFlag(kGameFlag369);
			_vm->clearGameFlag(kGameFlag370);

			if (getSound()->isPlaying(getWorld()->soundResourceIds[5]))
				getSound()->stop(getWorld()->soundResourceIds[5]);

			if (getSound()->isPlaying(getWorld()->soundResourceIds[6]))
				getSound()->stop(getWorld()->soundResourceIds[6]);

			if (getSound()->isPlaying(getWorld()->soundResourceIds[7]))
				getSound()->stop(getWorld()->soundResourceIds[7]);

			if (_vm->isGameFlagSet(kGameFlag235)) {
				Actor::enableActorsChapter2(_vm);
				_vm->clearGameFlag(kGameFlag235);
			}
		}
	}
}

void Actor::updateStatus16_Chapter11() {
	// We are sure to be the current player
	getCursor()->show();
	getSharedData()->setFlag(kFlag1, false);

	if (_frameIndex != -5 || _vm->isGameFlagNotSet(kGameFlag570))
		++_frameIndex;

	if (_frameIndex > _frameCount - 1) {
		if (getWorld()->field_E848C >= 3) {
			_frameIndex = 0;

			getScene()->getActor(0)->updateStatus(kActorStatus17);

			_tickCount = _vm->getTick() + 2000;
		} else {
			getScene()->getActor(0)->updateStatus(kActorStatus14);
		}
	}
}

void Actor::updateStatus17_Chapter2() {
	++_frameIndex;

	if (_frameIndex >= _frameCount) {
		_frameIndex = 0;
		updateStatus(kActorStatus14);
		hide();

		if (_vm->getRandomBit() == 1) {
			_vm->setGameFlag(kGameFlag219);
			getSpeech()->playPlayer(133);
		}
	}
}

void Actor::updateStatus18_Chapter2() {
	Actor *player = getScene()->getActor();

	_point1.x = player->getPoint1()->x - getSharedData()->getData(2 * _index + 19);
	_point1.y = player->getPoint1()->y - getSharedData()->getData(2 * _index + 20);

	_frameIndex++;

	if (_frameIndex > _frameCount - 1) {
		getSharedData()->setData2(_index, true);
		updateStatus(kActorStatus14);

		_point1.y += 54;
		getSound()->playSound(getWorld()->soundResourceIds[1], false, Config.sfxVolume - 10);

		getSharedData()->setData(_index, getSharedData()->getData(_index) - 54);
	}
}

void Actor::updateStatus18_Chapter2_Actor11() {
	error("[Actor::updateStatus18_Chapter2_Actor11] not implemented!");
}

void Actor::updateStatus21() {
	if (_resourceId == getWorld()->graphicResourceIds[3] || _resourceId == getWorld()->graphicResourceIds[4] || _resourceId == getWorld()->graphicResourceIds[5]) {
		if (_frameIndex < _frameCount - 1) {
			++_frameIndex;

			if (_frameIndex == _frameCount / 2) {
				getWorld()->currentPaletteId = getWorld()->graphicResourceIds[getWorld()->nextPlayer - 1];
				getScreen()->setPalette(getWorld()->currentPaletteId);
				getScreen()->setGammaLevel(getWorld()->currentPaletteId, 0);
			}

			return;
		}
	} else {
		if (_frameIndex > 0) {
			--_frameIndex;

			if (_frameIndex == _frameCount / 2)
				getScreen()->setPalette(getWorld()->graphicResourceIds[getWorld()->nextPlayer - 1]);

			getWorld()->currentPaletteId = getWorld()->graphicResourceIds[getWorld()->nextPlayer - 1];
			getScreen()->setGammaLevel(getWorld()->currentPaletteId, 0);
			return;
		}
	}

	getScene()->changePlayer(getWorld()->nextPlayer);
	updateStatus(kActorStatusEnabled);
	getWorld()->nextPlayer = kActorInvalid;
}

void Actor::updateFinish() {
	if (_field_944 == 4 || !isVisible())
		return;

	int32 areaIndex = getScene()->findActionArea(Common::Point((int16)(_point1.x + _point2.x), (int16)(_point1.y + _point2.y)));
	if (areaIndex == _actionIdx3 || areaIndex == -1)
		return;

	ActionArea *area = getWorld()->actions[areaIndex];
	ActionArea *actorArea = getWorld()->actions[_actionIdx3];
	if (!getScene()->actions()->isProcessingSkipped()) {
		getScene()->actions()->queueScript(actorArea->scriptIndex2, _index);
		getScene()->actions()->queueScript(area->scriptIndex, _index);
	}

	if (!area->paletteResourceId || area->paletteResourceId == actorArea->paletteResourceId || _index) {
		if (area->paletteResourceId != actorArea->paletteResourceId && !_index)
			_vm->screen()->startPaletteFade(area->paletteResourceId, 50, 3);

		_actionIdx3 = areaIndex;
	} else {
		_vm->screen()->startPaletteFade(area->paletteResourceId, 50, 3);
		_actionIdx3 = areaIndex;
	}
}

void Actor::updateCoordinates(Common::Point vec1, Common::Point vec2) {
	if (getScene()->getActor(1)->isVisible())
		return;

	uint32 diffY = abs(vec2.y - vec1.y);
	if (diffY > 5)
		diffY = 5;

	if (diffY == 0)
		return;

	ActorDirection direction = (diffY > 0) ? kDirectionS : kDirectionN;

	if (process_408B20(&vec2, direction, diffY + 3, false))
		updateCoordinatesForDirection(direction, diffY - 1, &_point);
}

void Actor::resetActors() {
	getCursor()->hide();
	getScene()->getActor(0)->hide();
	getScene()->getActor(1)->setFrameIndex(0);

	getWorld()->tickCount1 = _vm->getTick() + 3000;
}

void Actor::updateNumbers(int32 reaction, int32 x, int32 y) {
	if (reaction != 1)
		return;

	_numberStringX = x;
	_numberStringY = y + 8;
	_numberStringWidth = 40;

	// XXX use sprintf instead of itoa as itoa isn't part of standard
	// C++ and therefore isn't available in GCC
	sprintf(_numberString01, "%d", _numberValue01);

	_numberFlag01 = 1;
}

//////////////////////////////////////////////////////////////////////////
// Misc
//////////////////////////////////////////////////////////////////////////

void Actor::setVisible(bool value) {
	if (value)
		flags |= kActorFlagVisible;
	else
		flags &= ~kActorFlagVisible;

	stopSound();
}

bool Actor::isOnScreen() {
	Common::Rect scene(getWorld()->yTop, getWorld()->xLeft, getWorld()->yTop + 480, getWorld()->xLeft + 640);
	Common::Rect actor(_boundingRect);
	actor.moveTo(_point1.x, _point1.y);

	return isVisible() && scene.intersects(actor);
}

void Actor::setVolume() {
	if (!_soundResourceId || !getSound()->isPlaying(_soundResourceId))
		return;

	// Compute volume
	int32 volume = Config.voiceVolume + getSound()->calculateVolumeAdjustement(_point1.x + _point2.x, _point1.y + _point2.y, _field_968, 0);
	if (volume < -10000)
		volume = -10000;

	getSound()->setVolume(_soundResourceId, volume);
}

//////////////////////////////////////////////////////////////////////////
// Helper methods
//////////////////////////////////////////////////////////////////////////

ActorDirection Actor::direction(Common::Point vec1, Common::Point vec2) const {
	int32 diffX = (vec2.x - vec1.x) * 2^16;
	int32 diffY = (vec1.y - vec2.y) * 2^16;
	int32 adjust = 0;

	if (diffX < 0) {
		adjust = 2;
		diffX = -diffX;
	}

	if (diffY < 0) {
		adjust |= 1;
		diffY = -diffY;
	}

	int32 angle = -1;

	if (diffX) {
		uint32 index = (diffY * 256) / diffX;

		if (index < 256)
			angle = angleTable01[index];
		else if (index < 4096)
			angle = angleTable02[index / 16];
		else if (index < 65536)
			angle = angleTable03[index / 256];
	} else {
		angle = 90;
	}

	switch (adjust) {
	default:
		break;

	case 1:
		angle = 360 - angle;
		break;

	case 2:
		angle = 180 - angle;
		break;

	case 3:
		angle += 180;
		break;
	}

	if (angle >= 360)
		angle -= 360;

	ActorDirection direction;

	if (angle < 157 || angle >= 202) {
		if (angle < 112 || angle >= 157) {
			if (angle < 67 || angle >= 112) {
				if (angle < 22 || angle >= 67) {
					if ((angle < 0 || angle >= 22) && (angle < 337 || angle > 359)) {
						if (angle < 292 || angle >= 337) {
							if (angle < 247 || angle >= 292) {
								if (angle < 202 || angle >= 247) {
									error("[Actor::angle] returned a bad angle: %d!", angle);
								} else {
									direction = kDirectionSO;
								}
							} else {
								direction = kDirectionS;
							}
						} else {
							direction = kDirectionSE;
						}
					} else {
						direction = kDirectionE;
					}
				} else {
					direction = kDirectionNE;
				}
			} else {
				direction = kDirectionN;
			}
		} else {
			direction = kDirectionNO;
		}
	} else {
		direction = kDirectionO;
	}

	return direction;
}

void Actor::updateGraphicData(uint32 offset) {
	int32 index = ((_direction > kDirectionS) ? kDirection8 - _direction : _direction) + (int32)offset;
	_resourceId = _graphicResourceIds[index];
	_frameCount = GraphicResource::getFrameCount(_vm, _resourceId);
	_frameIndex = 0;
}

bool Actor::isDefaultDirection(int index) const {
	return _graphicResourceIds[index] != _graphicResourceIds[5];
}

int32 Actor::getGraphicsFlags() {
	if (getWorld()->chapter == kChapter11) {
		int res = strcmp((char *)&_name, "Dead Sarah");

		if (res == 0)
			return res;
	}

	// TODO replace by readable version
	return ((_direction < kDirectionSE) - 1) & 2;
}

int32 Actor::getDistance() const {
	int32 index = (_frameIndex >= _frameCount) ? (2 * _frameCount) - (_frameIndex + 1): _frameIndex;

	if (index >= 20)
		error("[Actor::getFieldValue] Invalid index calculation (was: %d, max: 20)", index);

	switch (_direction) {
	default:
	case kDirectionN:
	case kDirectionS:
		return 0;

	case kDirectionNO:
	case kDirectionSO:
		return -_field_8D0[index];

	case kDirectionO:
		return -_field_830[index];

	case kDirectionSE:
	case kDirectionNE:
		return _field_8D0[index];

	case kDirectionE:
		return _field_830[index];
	}
}

uint32 Actor::getDistanceForFrame(ActorDirection direction, uint32 frameIndex) {
	switch (_direction) {
	default:
	case kDirectionN:
	case kDirectionS:
		return _field_880[frameIndex];

	case kDirectionNO:
	case kDirectionSO:
	case kDirectionSE:
	case kDirectionNE:
		return _field_8D0[frameIndex];

	case kDirectionO:
	case kDirectionE:
		return _field_830[frameIndex];
	}
}

void Actor::updateCoordinatesForDirection(ActorDirection direction, int32 delta, Common::Point *point) {
	if (!point)
		error("[Actor::updateCoordinatesForDirection] Invalid point (NULL)!");

	switch (direction) {
	default:
		break;

	case kDirectionN:
		point->y -= delta;
		break;

	case kDirectionNO:
		point->x -= delta;
		point->y -= delta;
		break;

	case kDirectionO:
		point->x -= delta;
		break;

	case kDirectionSO:
		point->x -= delta;
		point->y += delta;
		break;

	case kDirectionS:
		point->y += delta;
		break;

	case kDirectionSE:
		point->x += delta;
		point->y += delta;
		break;

	case kDirectionE:
		point->x += delta;
		break;

	case kDirectionNE:
		point->y += delta;
		point->y -= delta;
		break;
	}
}

uint32 Actor::distance(Common::Point vec1, Common::Point vec2) {
	return sqrt(pow((double)(vec2.y - vec1.y), 2) + pow((double)(vec2.x - vec1.x), 2));
}

uint32 Actor::angle(Common::Point vec1, Common::Point vec2) {
	int32 result = ((long)(180 - acos((double)(vec2.y - vec1.y) / distance(vec1, vec2)) * 180 / PI)) % 360;

	if (vec1.x < vec2.x)
		return 360 - result;

	return result;
}

void Actor::rect(Common::Rect *rect, ActorDirection direction, Common::Point point) {
	if (!rect)
		error("[Actor::rect] Invalid rect (NULL)!");

	switch (direction) {
	default:
		rect->top = 0;
		rect->left = 0;
		rect->bottom = 0;
		rect->right = 0;
		return;

	case kDirectionN:
		rect->top = point.x - 9;
		rect->left = point.y - 84;
		break;

	case kDirectionNO:
		rect->top = point.x - 55;
		rect->left = point.y - 84;
		break;

	case kDirectionO:
		rect->top = point.x - 34;
		rect->left = point.y - 93;
		break;

	case kDirectionSO:
		rect->top = point.x + 27;
		rect->left = point.y - 94;
		break;

	case kDirectionS:
		rect->top = point.x + 41;
		rect->left = point.y - 9;
		break;

	case kDirectionSE:
		rect->top = point.x + 27;
		rect->left = point.y + 54;
		break;

	case kDirectionE:
		rect->top = point.x - 34;
		rect->left = point.y + 53;
		break;

	case kDirectionNE:
		rect->top = point.x - 55;
		rect->left = point.y + 44;
		break;
	}

	rect->setWidth(40);
	rect->setHeight(40);
}

bool Actor::compareAngles(Common::Point vec1, Common::Point vec2) {
	Common::Point vec3(2289, 171);

	int32 diff = angle(vec1, vec3) - angle(vec1, vec2);

	if (diff < 0)
		diff += 359;

	return (diff != 180);
}

bool Actor::compare(Common::Point vec1, Common::Point vec2, Common::Point vec) {
	if (vec.y >= vec1.y && vec.y <= vec2.y && vec.x >= vec1.x && vec.x <= vec2.x)
		return true;

	return false;
}

int32 Actor::compareX(Common::Point vec1, Common::Point vec2, Common::Point vec) {
	if (vec.y > vec2.y)
		return 3;

	if (vec.y < vec1.y)
		return 2;

	return 0;
}

int32 Actor::compareY(Common::Point vec1, Common::Point vec2, Common::Point vec) {
	if (vec.y > vec2.y)
		return 3;

	if (vec.y < vec1.y)
		return 2;

	return 0;
}


} // end of namespace Asylum