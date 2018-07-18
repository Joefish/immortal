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

#ifndef IMMORTAL_LOGIC_H
#define IMMORTAL_LOGIC_H

#include "common/error.h"
#include "common/events.h"

#include "immortal/dialog.h"
#include "immortal/rooms.h"
#include "immortal/timer.h"

namespace Immortal {

class Console;
class ResourceManager;
class MusicPlayer;
class Renderer;
class ImmortalEngine;

enum KeyState {
	kKeyLeft,
	kKeyRight,
	kKeyUp,
	kKeyDown,
	kKeyAttack,
	kKeyStart,
	kKeyQuit,
	kKeyNum
};

enum LogicState {
	kLogicStartup,
	kLogicDialog,
	kLogicInventory,
	kLogicGame,
	kLogicPause
};

enum ItemId {
	kItemBottle,
	kItemAlcohol,
	kItemBootOil,
	kItemShrinkPotion,
	kItemKey,
	kItemWormSensor,
	kItemSporesBag,
	kItemBaitBag,
	kItemGoldBag,
//	kItemBook,
	kItemDragonEgg,
	kItemMap,
	kItemRuby,
	kItemStone,
	kItemLetter,
	kItemAmulet,
	kItemBomb,
	kItemRingDunric,
	kItemRingProtean,
	kItemCarpet,
	kItemFireballScroll,
	kItemNum
};

struct InventoryItem {
	ItemId _itemId;
	int _quantity;
	const char *_text;
	SpriteId _spriteId;
};

class Inventory {
public:
	Inventory(Dialog *dialog);

	InventoryItem *getItem(int index);
	SpriteId getSprite(int index);
	void addItem(ItemId id, int quantity);
	int numItems() const;

private:
	Common::Array<InventoryItem> _inventory;
	Dialog *_dialog;
};

class Logic {
public:
	Logic(ImmortalEngine *vm);
	void init();
	void update();

private:
	void runStartup();
	void runDialog();
	void runGame();
	void runPause();
	void runInventory();

	void pollInput();
	void handleInput();
	bool isKeyPressed(KeyState key);
	void setState(LogicState state);
	void loadDialog(DialogId id);
	bool loadFromPassword(Dialog *dialog);
	void handleDialogYesNo();
	void handleDialogEnd();
	void loadLevel(int level);
	void setCamera(int x, int y);
	void updateEntities();

private:
	Console *_console;
	ResourceManager *_resMan;
	MusicPlayer *_music;
	Renderer *_screen;

	Dialog _dialog;
	DialogToken _lastDialogToken;
	bool _buttonNoSelected;
	bool _buttonYesSelected;
	Common::Array<int> _keyInputBuffer;
	Timer _timer;
	Timer _gameDelay;
	Timer _keyDelay;
	LogicState _logicState;
	int64 _timeInit;
	bool _keyState[kKeyNum];
	bool _keyStartAttackPressed;
	Level _level;
	// TODO: just temporary. Camera is centered on wizard (all the time?)
	Common::Point _cameraPos;
	Entity _wizard;
	WizardState _wizardState;
	Direction _moveDirection;
	Inventory _inventory;
	int _inventoryPage;
};

}

#endif
