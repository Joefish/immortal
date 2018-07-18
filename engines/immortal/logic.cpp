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

#include "common/system.h"

#include "immortal/console.h"
#include "immortal/immortal.h"
#include "immortal/logic.h"
#include "immortal/graphics.h"
#include "immortal/sound.h"

namespace Immortal {

// TODO:
// Make keys remappable
static const Common::KeyCode keyMap[kKeyNum] = {
	Common::KEYCODE_LEFT,
	Common::KEYCODE_RIGHT,
	Common::KEYCODE_UP,
	Common::KEYCODE_DOWN,
	Common::KEYCODE_RSHIFT,
	Common::KEYCODE_RETURN,
	Common::KEYCODE_ESCAPE
};

Logic::Logic(ImmortalEngine *vm)
    : _console(vm->_console)
    , _resMan(vm->_resMan)
    , _music(vm->_midiPlayer)
    , _screen(vm->_screen)
    , _dialog(vm->_screen)
    , _lastDialogToken(kDialogTokenInvalid)
    , _buttonNoSelected(true)
    , _buttonYesSelected(false)
    , _logicState(kLogicStartup)
    , _timeInit(vm->_system->getMillis())
    , _keyState()
    , _cameraPos(0, 0)
    , _wizardState(kWizardStateNone)
    , _inventory(&_dialog) {
}

// TODO:
// Parameters for loading savestates/new game/..
// init rooms and gamestate
void Logic::init() {
	_wizard.setMonsterType(kMonsterTypeWizard);
	_inventory.addItem(kItemGoldBag, 2);
	_inventory.addItem(kItemAmulet, 1);
	_inventory.addItem(kItemCarpet, 10);
	_inventory.addItem(kItemBomb, 8);
	_inventory.addItem(kItemDragonEgg, 1);
}

void Logic::update() {
	pollInput();
	handleInput();

	switch (_logicState) {
	case kLogicStartup:
		runStartup();
		break;
	case kLogicDialog:
		runDialog();
		break;
	case kLogicInventory:
		runInventory();
		break;
	case kLogicGame:
		runGame();
		break;
	case kLogicPause:
		runPause();
		break;
	default:
		error("Game ended up in invalid state!");
		break;
	}
}

void Logic::updateEntities() {
	// non animated static objects (chests)
	// animated static objects (torches)
	// NPCs

	// wizard
	_wizard.move(_moveDirection, _wizardState);
	_moveDirection = kDirectionNone;
	int pack = _wizard.getDirection();
	int frame = _wizard.getFrame();
	// TODO: update camera pos according to wizard pos
	// entity world pos conversion to viewport pos
	// sprite clipping
	_screen->drawSprite(kSpriteWizard, _wizard.getPos().x, _wizard.getPos().y,
	                    frame, pack);

}

void Logic::pollInput() {
	Common::Event event;
	while (g_system->getEventManager()->pollEvent(event)) {
		switch (event.type) {
		case Common::EVENT_KEYDOWN:
			if (event.kbd.keycode == Common::KEYCODE_d &&
			    (event.kbd.flags & Common::KBD_CTRL)) {
				_console->attach();
			}
			for (int i = 0; i < kKeyNum; ++i) {
				if (event.kbd.keycode == keyMap[i])
					_keyState[i] = true;
			}
			if (Common::isAlnum(event.kbd.ascii) || event.kbd.keycode == Common::KEYCODE_BACKSPACE) {
				_keyInputBuffer.push_back(event.kbd.keycode);
			}
			break;
		case Common::EVENT_KEYUP:
			for (int i = 0; i < kKeyNum; ++i) {
				if (event.kbd.keycode == keyMap[i])
					_keyState[i] = false;
			}
			break;
		default:
			break;
		}
	}
}

void Logic::handleInput() {
	_keyStartAttackPressed = isKeyPressed(kKeyAttack) || isKeyPressed(kKeyStart);

	if (isKeyPressed(kKeyLeft) && isKeyPressed(kKeyUp)) {
		_moveDirection = kDirectionNW;
	} else if (isKeyPressed(kKeyUp) && isKeyPressed(kKeyRight)) {
		_moveDirection = kDirectionNE;
	} else if (isKeyPressed(kKeyRight) && isKeyPressed(kKeyDown)) {
		_moveDirection = kDirectionSE;
	} else if (isKeyPressed(kKeyDown) && isKeyPressed(kKeyLeft)) {
		_moveDirection = kDirectionSW;
	} else if (isKeyPressed(kKeyUp)) {
		_moveDirection = kDirectionN;
	} else if (isKeyPressed(kKeyRight)) {
		_moveDirection = kDirectionE;
	} else if (isKeyPressed(kKeyDown)) {
		_moveDirection = kDirectionS;
	} else if (isKeyPressed(kKeyLeft)) {
		_moveDirection = kDirectionW;
	} else {
		_moveDirection = kDirectionNone;
	}

	if (isKeyPressed(kKeyAttack)) {
		// TODO: Last bound spell (e.g. fireball)
		_keyDelay.start();
		if (_keyDelay.elapsedTime() < 300)
			return;

		switch (_wizardState) {
		case kWizardStateNone:
			_wizardState = kWizardStateOnCarpet;
			break;
		case kWizardStateLevitating:
			_wizardState = kWizardStateNone;
			break;
		case kWizardStateOnCarpet:
			_wizardState = kWizardStateOnBarrel;
			break;
		case kWizardStateOnBarrel:
			_wizardState = kWizardStateLevitating;
			break;
		default:
			break;
		}

		_keyDelay.reset();
	}
	if (isKeyPressed(kKeyStart)) {
		_keyDelay.start();
		if (_keyDelay.elapsedTime() < 300)
			return;

		debug("X:%3d  Y:%3d", _cameraPos.x, _cameraPos.y);
		debug("Wizard: X:%3d Y:%3d", _wizard.getPos().x, _wizard.getPos().y);

		if (_logicState == kLogicGame)
			setState(kLogicInventory);
		else if (_logicState == kLogicInventory)
			setState(kLogicGame);

		_keyDelay.reset();
	}
	if (isKeyPressed(kKeyQuit)) {
		if (_logicState == kLogicGame) {
			loadDialog(kDialogExitString);
		}
	}
}

void Logic::runStartup() {
	_screen->drawImage(kImageTitleScreen);
	_timer.start();
	if (_timer.elapsedTime() > 3000 || _keyStartAttackPressed) {
		_timer.stop();
		loadDialog(kDialogNewGame);
	}
}

void Logic::runDialog() {
	switch (_lastDialogToken) {
	case kDialogTokenDelay:
		_timer.start();
		if (_keyStartAttackPressed || _timer.elapsedTime() > _dialog.getDelay()) {
			_timer.stop();
			_dialog.nextChar();
			_lastDialogToken = kDialogTokenInvalid;
		}
		break;

	case kDialogTokenEndOfStringOk: {
		int buttonX = (_screen->_viewportWidth / 2) - (_screen->_iconWidth / 2);
		int buttonY = _screen->_buttonNoY;
		_screen->drawIcon(kSpriteButtonOk, buttonX, buttonY);

		if (_keyStartAttackPressed)
			setState(kLogicGame);
	} break;

	case kDialogTokenEndOfStringYesNo:
		handleDialogYesNo();
		break;

	case kDialogTokenLoadNextString:
		// TODO: Add support for 'follwoing string' in dialogText
		// Test with kDialogGiveHerRing
		break;

	case kDialogTokenStringTerminator:
		handleDialogEnd();
		break;

	default:
		_lastDialogToken = _dialog.update(_keyStartAttackPressed);
		break;
	}
}

void Logic::runGame() {
	_gameDelay.start();
	if (_gameDelay.elapsedTime() < 80)
		return;

	_screen->clear();
	_screen->drawMap(_cameraPos.x, _cameraPos.y);
	updateEntities();

	_gameDelay.reset();
}

void Logic::runPause() {

}

void Logic::setState(LogicState state) {
	_logicState = state;
}

bool Logic::isKeyPressed(KeyState key) {
	return _keyState[key];
}

void Logic::loadDialog(DialogId id) {
	// TODO:
	// Different music for intro, sleep and default
	// Draw health meter as well
	_dialog.load(id);
	_screen->clear();
	_lastDialogToken = kDialogTokenInvalid;
	setState(kLogicDialog);

	if (id == kDialogIntro)
		_music->play(kMusicIntro);
}

bool Logic::loadFromPassword(Dialog *dialog) {
	// TODO:
	// Generate password (see blog post on structure)
	// Generate/Check checksum

	return false;
}

// TODO:
// Unify coordinate systems.
// Most definitions are in pixel coordinates anyway, so adjusting the map renderer
// from tile to pixel coords would be better than dividing and multiplying everywhere
void Logic::setCamera(int x, int y) {
	_cameraPos.x = x / 8;
	_cameraPos.y = y / 8;
}

void Logic::handleDialogYesNo() {
	if (isKeyPressed(kKeyRight)) {
		_buttonNoSelected = false;
		_buttonYesSelected = true;
	} else {
		_buttonNoSelected = true;
		_buttonYesSelected = false;
	}

	SpriteId buttonNo = _buttonNoSelected ? kSpriteButtonNoActive
	                                      : kSpriteButtonNoInactive;
	SpriteId buttonYes = _buttonYesSelected ? kSpriteButtonYesActive
	                                        : kSpriteButtonYesInactive;
	_screen->drawIcon(buttonNo, _screen->_buttonNoX, _screen->_buttonNoY);
	_screen->drawIcon(buttonYes, _screen->_buttonYesX, _screen->_buttonYesY);

	switch (_dialog.getId()) {
	case kDialogExitString:
		if (_keyStartAttackPressed) {
			if (_buttonYesSelected) {
				g_system->quit();
			} else if (_buttonNoSelected) {
				setState(kLogicGame);
			}
		}
		break;
	case kDialogNewGame:
		if (_keyStartAttackPressed) {
			if (_buttonYesSelected) {
				loadLevel(1);
				setState(kLogicGame);
				_music->play(kMusic04);
			} else if (_buttonNoSelected) {
				loadDialog(kDialogEnterCertificate);
			}
		}
		break;
	default:
		break;
	}
}

void Logic::handleDialogEnd() {
	if (_dialog.getId() == kDialogEnterCertificate) {
		for (int *it = _keyInputBuffer.begin(); it < _keyInputBuffer.end(); ++it) {
			int key = *it;
			if (Common::isAlnum(key))
				_dialog.printChar(key);
			else if (key == Common::KEYCODE_BACKSPACE)
				_dialog.removeChar();
			else if (key == Common::KEYCODE_RETURN)
				loadFromPassword(&_dialog);
		}
		_keyInputBuffer.clear();

		if (isKeyPressed(kKeyQuit))
			loadDialog(kDialogNewGame);
	} else if (_dialog.getId() == kDialogIntro) {
		loadDialog(kDialogNewGame);
		_lastDialogToken = kDialogTokenInvalid;
	} else {
		_timer.start();
		if (_keyStartAttackPressed || _timer.elapsedTime() > 3000) {
			_timer.stop();
			_dialog.nextChar();
			_lastDialogToken = kDialogTokenInvalid;
		}
	}
}

static const DialogId itemList[] = {
	kDialogBootsString,         // kItemBottle
	kDialogAlcoholString,       // kItemAlcohol
	kDialogBootsString,         // kItemBootOil
	kDialogMuscleString,        // kItemShrinkPotion
	kDialogChestKeyString,      // kItemKey
	kDialogWormSensorString,    // kItemWormSensor
	kDialogSporesString,        // kItemSporesBag
	kDialogWormFoodString,      // kItemBaitBag
	kDialogGoldString,          // kItemGoldBag
	                            // kItemBook
	kDialogEggString,           // kItemDragonEgg
	kDialogDeathMapString,      // kItemMap
	kDialogGemString,           // kItemRuby
	kDialogStoneString,         // kItemStone
	kDialogNoteString,          // kItemLetter
	kDialogAmuletString,        // kItemAmulet
	kDialogBombString,          // kItemBomb
	kDialogDunricRingString,    // kItemRingDunric
	kDialogFaceString,          // kItemRingProtean
	kDialogCarpetString,        // kItemCarpet
	kDialogFireballString       // kItemFirballScroll
};

void Logic::runInventory() {
	Common::Point itemPos[6];
	itemPos[0] = Common::Point(_screen->_viewportWidth / 3, 0);
	itemPos[1] = Common::Point(0, 0);
	itemPos[2] = Common::Point(2 * _screen->_viewportWidth / 3, 0);
	itemPos[3] = Common::Point(0 , _screen->_viewportHeight / 2);
	itemPos[4] = Common::Point(_screen->_viewportWidth / 3 , _screen->_viewportHeight / 2);
	itemPos[5] = Common::Point(2 * _screen->_viewportWidth / 3, _screen->_viewportHeight / 2);

	_screen->clear();

	// render items (icons + text)
	// if more than 6 items in inventory, render 'other' at itempos[5]
	// and render items 6 - 11. (same rules apply)
	int maxItemIndex = 5 + 6 * _inventoryPage;
	if (_inventory.numItems() > 6) {
		--maxItemIndex;
	}

	for (int i = 6 * _inventoryPage; i < maxItemIndex; ++i) {
		if (i >= _inventory.numItems())
			break;

		InventoryItem *item = _inventory.getItem(i);
		const char *itemText = item->_text;
		// TODO: why does it crash with drawSprite() ?

		// render text
		_screen->drawInventoryItem(item->_text, item->_spriteId, item->_quantity,
		                           itemPos[i % 6].x, itemPos[i % 6].y);
	}

	switch (_moveDirection) {
	case kDirectionNone:
	case kDirectionN:
		_screen->drawIcon(kSpriteInventorySelect, 2 + itemPos[0].x, itemPos[0].y);
		break;
	case kDirectionNW:
	case kDirectionW:
		_screen->drawIcon(kSpriteInventorySelect, 2 + itemPos[1].x, itemPos[1].y);
		break;
	case kDirectionNE:
	case kDirectionE:
		_screen->drawIcon(kSpriteInventorySelect, 2 + itemPos[2].x, itemPos[2].y);
		break;
	case kDirectionSW:
		_screen->drawIcon(kSpriteInventorySelect, 2 + itemPos[3].x, itemPos[3].y);
		break;
	case kDirectionS:
		_screen->drawIcon(kSpriteInventorySelect, 2 + itemPos[4].x, itemPos[4].y);
		break;
	case kDirectionSE:
		_screen->drawIcon(kSpriteInventorySelect, 2 + itemPos[5].x, itemPos[5].y);
		break;
	}
}

void Logic::loadLevel(int level) {
	_level.loadLevel(level);
	setCamera(_level._initCameraPos.x, _level._initCameraPos.y);
	_wizard.setPos(_level._spawnPos.x, _level._spawnPos.y);
//	_inventory.addItem(kItemGoldBag, 20);
}


Inventory::Inventory(Dialog *dialog)
    : _dialog(dialog) {
}

int Inventory::numItems() const {
	return _inventory.size();
}

InventoryItem *Inventory::getItem(int index) {
	assert(index >= 0 && index < _inventory.size());
	return &_inventory[index];
}

void Inventory::addItem(ItemId id, int quantity) {
	// TODO: if item already there, increase quantity

	const char *text = _dialog->getDialogText(itemList[id]);
	SpriteId spriteId = _dialog->getDialogIcon(itemList[id]);
	const InventoryItem temp = {id, quantity, text, spriteId};
	_inventory.push_back(temp);
}

SpriteId Inventory::getSprite(int index) {
	InventoryItem *item = getItem(index);
	if (!item)
		return kSpriteNone;

	return kSpriteNone;
}
}
