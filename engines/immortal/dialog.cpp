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

#include "immortal/dialog.h"
#include "immortal/graphics.h"

namespace Immortal {

Dialog::Dialog(Renderer *screen)
    : _screen(screen)
    , _text(nullptr)
    , _cursorPos(_cursorOriginX, _cursorOriginY)
    , _timeSinceLastUpdate()
    , _delay(0)
    , _scrollingMode(false)
    , _id(kDialogNone)
    , _passwordCharIndex(0) {
	reset();
	memset(_password, 0, sizeof(_password));

// TODO:
// Change Intro string depending on game version
	_dialog[kDialogIntro]._text =
	        "\\   Electronic Arts presents&&       The Immortal\x19&&&&"
	        "     \x18 1991 Will Harvey|]]]]]]]]\\]="
	        "          written by&&         Will Harvey&         Ian Gooding&"
	        "      Michael Marcantel&       Brett G. Durrett&        Douglas Fulton|]]]]]]]/="
#if 0
	        "&&      Amiga version by&&       Brett G. Durrett&]]]]]]]="
	        "&&       Atari version by&&      Brett G. Durrett&]]]]]]]="
#endif
	        "&&       IBM version by&&      Kenneth L. Hurley&|]]]]]]]=";
	_dialog[kDialogNewGame]._text = "New game?%";
	_dialog[kDialogPartyString]._text =
	        "Ken Hurley and Rick &Rutkowski want you to &have this silver bullet.@";
	_dialog[kDialogKoorsString]._text = "#  beer@";
	_dialog[kDialogKoorsString]._iconId = kSpriteKoorsLight;
	_dialog[kDialogBeerManString]._text = "You feel invinicible now.@";
	_dialog[kDialogKoorsOpen]._text = "It's 8 am! &Shotgun the beer?%";
	_dialog[kDialogMerchantDescription]._text =
	        "_}Greetings, friend! Come, I've got something you need. These parts are plagued with slime. "
	        "You can't venture safely without my slime oil for boots, a bargain at only 80 gold pieces.%";
	_dialog[kDialogMerchant3Description]._text =
	        "_}All right, 60 gold pieces for my oil. "
	        "Rub it on your boots and slime won't touch you. 60, friend.%";
	_dialog[kDialogMapText1]._text = "This room isn't on the map.&Look at the picture.@";
	_dialog[kDialogMapText2]._text = "This room is on the map.&Look at the picture.@";
	_dialog[kDialogSwordString]._text = "# sword@";
	_dialog[kDialogSwordString]._iconId = kSpriteIconSword;
	_dialog[kDialogSwordDescription]._text = "You find an Elven sword of&combat agility. Take it?@";
	_dialog[kDialogBonesText1]._text = "Search the bones?%";
	_dialog[kDialogBonesText2]._text = "}The sword increases your quickness permanently.@";
	_dialog[kDialogBonesText3]._text = "}You notice something that looks wet and green under the pile. Search further?%";
	_dialog[kDialogDustOfComplaisanceString]._text = "#  dust@";
	_dialog[kDialogDustOfComplaisanceString]._iconId = kSpriteIconBaitBag;
	_dialog[kDialogDustOfComplaisanceDescription]._text =
	        "}You find a bag containing Dust of Complaisance.&@";
	_dialog[kDialogOpenBag]._text = "}Drop the bait on the ground here?%";
	_dialog[kDialogThrowDustOfComplaisance]._text =
	        "}To use this dust, you throw it in the air. Do that here?%";
	_dialog[kDialogSmithText1]._text =
	        "_}Don't bother me, I'm cutting a gem. Yes, you need it. No, you can't have it. "
	        "I wouldn't give this gem to anyone, least of all you. Go away.]]]]=";
	_dialog[kDialogSmithText2]._text = "_}Let me help you. Take this gem. There you go. Good luck.]]]]=";
	_dialog[kDialogCarpetString]._text = "#carpet@";
	_dialog[kDialogCarpetString]._iconId = kSpriteIconCarpet;
	_dialog[kDialogBombString]._text = "# bomb@";
	_dialog[kDialogBombString]._iconId = kSpriteIconBomb;
	_dialog[kDialogBombDesc]._text = "A gas bomb that goblins&use to paralyze trolls.&@";
	_dialog[kDialogPickItUp]._text = "Take it?<>@";
	_dialog[kDialogYesNoString]._text = "%";
	_dialog[kDialogOtherString]._text = " other@";
	_dialog[kDialogChestKeyString]._text = "#  key@";
	_dialog[kDialogChestKeyString]._iconId = kSpriteIconKey;
	_dialog[kDialogChestKeyDescription]._text = "A key to a chest.&@";
	_dialog[kDialogOpenChestDescription]._text = "The chest is open. Examine&contents?%";
	_dialog[kDialogPutItOn]._text = "Put it on?%";
	_dialog[kDialogDropItThen]._text = "Drop it?%";
	_dialog[kDialogChestDescription]._text = "It's unlocked. Open it?%";
	_dialog[kDialogGoodChestDescription]._text = "It's locked but you have&the key. Open it?%";
	_dialog[kDialogBadChestDescription]._text = "It's locked and you don't&have the key.@";
	_dialog[kDialogGoldString]._text = "#$0 gold@";
	_dialog[kDialogGoldString]._iconId = kSpriteIconGoldBag;
	_dialog[kDialogFindGoldString]._text = "You find $0 gold pieces.&&^#@";
	_dialog[kDialogFindGoldString]._iconId = kSpriteIconGold;
	_dialog[kDialogNullString]._text = "@";
	_dialog[kDialogNotHere]._text = "You can't plant them on&stone tiles.@";
	_dialog[kDialogUnlockDoor]._text = "It's locked but you are&able to unlock it with&the key.@";
	_dialog[kDialogWeak1String]._text =
	        "_}The king is not dead, but the poison is taking effect. When he sees you, he utters "
	        "(Give me water... the fountain... I give you... information... peace...' Give him water?%";
	_dialog[kDialogDummyWater]._text =
	        "_}You dont have any water to give him. He mumbles something. Then silence... You find a key on his body.]]]]=";
	_dialog[kDialogBadWizard]._text = "_}He mumbles something. Then silence... You find a key on his body.]]]]=";
	_dialog[kDialogDiesAnyway]._text =
	        "_}I'll tell you how to... next level... just beyond slime... three jewels... slime... rock becomes... "
	        "floor... right, left, center of the... [Then silence. His hand opens, releasing a key.]]]]=";
	_dialog[kDialogDoorKeyDescription]._text = "You find a door key.&@";
	_dialog[kDialogNoteDescription]._text = "You find a note.&@";
	_dialog[kDialogNoteString]._text = "#  note@";
	_dialog[kDialogNoteString]._iconId = kSpriteIconLetter;
	_dialog[kDialogLootBodyDescription]._text = "He's dead.&Look for possessions?%";
	_dialog[kDialogNotEnough]._text = "You don't have it. Check&your inventory.@";
	_dialog[kDialogGameOverString]._text = "Game Over&&Play again?@";
	_dialog[kDialogYouWin]._text = "Congratulations!&&Play again?@";
	_dialog[kDialogWormFoodDescription]._text = "You find a bag of bait.&@";
	_dialog[kDialogWormFoodString]._text = "#   bait@";
	_dialog[kDialogWormFoodString]._iconId = kSpriteIconBaitBag;
	_dialog[kDialogStoneDescription]._text = "You find a stone. @";
	_dialog[kDialogStoneString]._text = "# stone@";
	_dialog[kDialogStoneString]._iconId = kSpriteIconStone;
	_dialog[kDialogGemDescription]._text = "You find a red gem.&@";
	_dialog[kDialogGemString]._text = "#  gem@";
	_dialog[kDialogGemString]._iconId = kSpriteIconRuby;
	_dialog[kDialogFireballDescription]._text = "You find a book with&fireball spells.&@";
	_dialog[kDialogFireballString]._text = "#$ shots@";
	_dialog[kDialogFireballString]._iconId = kSpriteIconScroll;
	_dialog[kDialogDeathMapDescription]._text = "You find a map warning&you about pit traps.&@";
	_dialog[kDialogDeathMapString]._text = "#  map@";
	_dialog[kDialogDeathMapString]._iconId = kSpriteIconMap;
	_dialog[kDialogBootsString]._text = "#   oil@";
	_dialog[kDialogBootsString]._iconId = kSpriteIconBottle;
	_dialog[kDialogUseBootString]._text =
	        "You try it out but notice&as you walk that the leather&is quickly drying out.@";
	_dialog[kDialogCharmDescription]._text =
	        "}You find a scroll with a charm spell to use on will o' the wisps.&@";
	_dialog[kDialogCharmString]._text = "# charm@";
	_dialog[kDialogCharmString]._iconId = kSpriteIconScroll;
	_dialog[kDialogUseCharmString]._text =
	        "}This charms the will o' the wisps to follow you. Read the spell again to turn them against your enemies.@";
	_dialog[kDialogWaterOpen]._text = "}It looks like water. Drink it?%";
	_dialog[kDialogDrinkIt]._text = "Drink it?%";
	_dialog[kDialogItWorks]._text = "}It works! You are much stronger.]]]=";
	_dialog[kDialogSbOpen]._text = "}It looks like it has green stuff inside. Open it?%";
	_dialog[kDialogUsesFireString]._text = "Okay, now this will take&effect when you press the&fire button.@";
	_dialog[kDialogMuscleDescription]._text = "You find a potion,&Magic Muscle.&@";
	_dialog[kDialogMuscleString]._text = "#  potion@";
	_dialog[kDialogMuscleString]._iconId = kSpriteIconBottle;
	_dialog[kDialogSbDescription]._text = "You find a bottle.&@";
	_dialog[kDialogSbString]._text = "#  bottle@";
	_dialog[kDialogSbString]._iconId = kSpriteIconBottle;
	_dialog[kDialogFaceString]._text = "#protean@";
	_dialog[kDialogFaceString]._iconId = kSpriteIconRing;
	_dialog[kDialogFaceDescription]._text = "You find a Protean Ring.&@";
	_dialog[kDialogTrndescription]._text =
	        "You find a troll ritual knife,&used to declare a fight to&the death. @";
	_dialog[kDialogTrnString]._text = "# knife@";
	_dialog[kDialogTrnString]._iconId = kSpriteIconDagger;
	_dialog[kDialogInvisDescription]._text =
	        "_}It is a fine woman's garment. Folded inside is a ring with the words, "
	        "[`To Ana, so harm will never find you. Love, Dunric.' @";
	_dialog[kDialogGoodLuckDescription]._text = "You find a small, well&crafted ring. @";
	_dialog[kDialogAnaRingString]._text = "#from ana@";
	_dialog[kDialogAnaRingString]._iconId = kSpriteIconRing;
	_dialog[kDialogInvisString]._text = "#  ana's@";
	_dialog[kDialogInvisString]._iconId = kSpriteIconRing;
	_dialog[kDialogGoesAway]._text =
	        "_}She is hurt and upset when she finds you don't have her ring or won't give it to her. "
	        "She scurries back into the hole. The hole is too small for you to follow.&@";
	_dialog[kDialogGiveHerRing]._text =
	        "_}`Oh sir, can you help me,' the girl pleads. `I was kidnapped and dragged down here. "
	        "All the man would say is `Mordamir's orders.' I ~";
	_dialog[kDialogGiveHerRing]._nextPage = kDialogGive2;
	_dialog[kDialogGive2]._text =
	        "escaped using a ring my father gave me, but now I've lost it. Did you find it?'%";
	_dialog[kDialogMadKingText]._text =
	        "_}We have met before, old man. Do you remember? Because you helped me, you may pass. "
	        "But I warn you, we are at war with the trolls. Over this ladder, across the spikes, is troll territory.@";
	_dialog[kDialogMadKing2Text]._text = "_}You are an impostor!]]]]=";
	_dialog[kDialogMadKing3Text]._text =
	        "_}Old man, do you remember me? I am king of the goblins. You didn't give me the water. "
	        "You left me to die after you took the key from me. Now you will pay.]]]]=";
	_dialog[kDialogDream1P1]._text =
	        "_}Ah, a rest is exactly what you need right now. You quickly fall into a deep, dream filled sleep..."
	        "[Vivid images of a beautiful enchanted city pass by. All the city people are young. There are ~";
	_dialog[kDialogDream1P1]._nextPage = kDialogDream1P2;
	_dialog[kDialogDream1P2]._text =
	        "fountains all around, water everywhere. A huge wall surrounds the city, sealing it from the outside world..."
	        "[Suddenly the images go black. A face appears... Mordamir!]][ ~";
	_dialog[kDialogDream1P2]._nextPage = kDialogDream1P3;
	_dialog[kDialogDream1P3]._text =
	        "He is different from how you remember him. His gentle features are now withered. "
	        "His kind eyes, now cold and sunken, seem to look through you with a dark, penetrating stare. "
	        "You wake rejuvenated, but disturbed.]]]]]=";
	_dialog[kDialogHowToGetOut]._text =
	        "_}Here, take this ring in return. [I overheard the obnoxious little dwarf saying "
	        "(Clockwise, three rings around the triangle.' Could that be a clue to his exit puzzle? "
	        "[I must go. Goodbye.]]]]=";
	_dialog[kDialogRestartString]._text = "Start over?%";
	_dialog[kDialogSporesString]._text = "# spores@";
	_dialog[kDialogSporesString]._iconId = kSpriteIconSporesBag;
	_dialog[kDialogSporesDescription]._text = "You find a sack of bad&smelling spores.&@";
	_dialog[kDialogRequestPlayDisk]._text = "Please insert play disk.@";
	_dialog[kDialogOldGameString]._text = "New game?%";
	_dialog[kDialogEnterCertificate]._text = "Enter certificate:&-=";
	_dialog[kDialogBadCertificate]._text = "Invalid certificate.@";
	_dialog[kDialogCertificateString]._text = "End of level!&Here is your certificate:&&=";
	_dialog[kDialogCertificate2String]._text = "&@";
	_dialog[kDialogExitString]._text = " Are you sure you & want to exit Immortal?%";
	_dialog[kDialogCertCheckString0]._text = "Look in your manual for this&picture. Type the =";
	_dialog[kDialogCertCheckString1]._text = "first&letter on row =";
	_dialog[kDialogCertCheckString2]._text = "second&letter on row =";
	_dialog[kDialogCertCheckFirst]._text = "fourth&letter on row =";
	_dialog[kDialogCertCheckSecond]._text = "sixth&letter on row =";
	_dialog[kDialogCertCheckFourth]._text = ", below.&&=";
	_dialog[kDialogCertCheckSixth]._text = "No, that's not it.&One more try.]]]]=";
	_dialog[kDialogDream1]._text =
	        "}_The straw is a small but welcome comfort in your first day's travel. "
	        "As you drift into an uneasy slumber, you begin to wonder about Mordamir. "
	        "How long has he been held prisoner? Where?~";
	_dialog[kDialogDream1]._nextPage = kDialogD1D2;
	_dialog[kDialogD1D2]._text = " You finally fall asleep dreaming about adventures that lie ahead.]]]=";
	_dialog[kDialogPhantDescription]._text =
	        "_}An image of the old wizard Mordamir leaps from the candle and begins to speak,"
	        "[(Dunric, you have come~";
	_dialog[kDialogPhantDescription]._nextPage = kDialogWizardText2;
	_dialog[kDialogWizardText2]._text =
	        " to save me. I am in the dungeons far below. I know I can count on you.'[~";
	_dialog[kDialogWizardText2]._nextPage = kDialogWizardText3;
	_dialog[kDialogWizardText3]._text = "This explains your old teacher's mysterious disappearance, "
	           "but there is one thing strange about the message...[Your name is not Dunric. ]]]]=";
	_dialog[kDialogDunricDescription]._text = "}The body of a fighter. Look for possessions?%";
	_dialog[kDialogUlindorString0]._text =
	        "_}You have come to save Mordamir, have you? He is held prisoner many levels below. "
	        "There is a hidden passage way. That is all I can tell you.[~";
	_dialog[kDialogUlindorString0]._nextPage = kDialogUlindorString1;
	_dialog[kDialogUlindorString1]._text =
	        "Without another word, the man hands you a key and runs out the door.]]]]=";
	_dialog[kDialogGuardNote]._text =
	        "_}Beware of shades. They are dangerous, invisible creatures that like darkness. "
	        "Under firelight they cast a shadow by which you can detect and avoid them.@";
	_dialog[kDialogDunricRingDescription]._text =
	        "}You find a ring. There is a name inscribed on the band: Dunric!&@";
	_dialog[kDialogDunricRingString]._text = "#dunric's@";
	_dialog[kDialogDunricRingString]._iconId = kSpriteIconRing;
	_dialog[kDialogUlindorString2]._text =
	        "_}`We are even now, wizard. Here, you will need this.' ~";
	_dialog[kDialogUlindorString2]._nextPage = kDialogUlindorString3;
	_dialog[kDialogUlindorString3]._text =
	        "He hands you a musty red carpet. (It is dangerous to step even one foot in the next two rooms. "
	        "After that, the exit is just down three ladders.' With that advice, he turns and walks briskly away.@";
	_dialog[kDialogDreamLevel2]._text =
	        "_}When you clear your mind of the day's troubles, you start to think about the goblins. "
	        "[They appear to be rational. Perhaps you can reach some agreement with them.]]]=";
	_dialog[kDialogWarning]._text = "}Stop! I forbid you to come any closer. Go back.@";
	_dialog[kDialogThrowTrn]._text = "Throw it here?%";
	_dialog[kDialogThrowTrn2]._text = "The knife lands near the troll.]]]=";
	_dialog[kDialogDreamLevel3]._text =
	        "_}The poison from the spores must have killed the goblin king. But now he is alive! "
	        "There is something very magical in these dungeons.]]]=";
	_dialog[kDialogCoffeeDescription]._text = "A coffee pot? @";
	_dialog[kDialogCoffeeString]._text = "# coffee@";
	// why 'swordFrame'? there are a few ids that don't fit the description..
	_dialog[kDialogCoffeeString]._iconId = kSpriteIconCoffee;
	_dialog[kDialogGimmeCoffee]._text =
	        "_}(Hey, what's this?&&The wizard![Brett, I told you someone would find us.[Wake up, Mike and Ian. "
	        "We've got a visitor.[Listen wizard, Mike needs some coffee in the morning. Got any?'%";
	_dialog[kDialogNoCoffee]._text =
	        "_}(Don't try to fool me, I wrote this game. You know what happens to fibbers?']]]=";
	_dialog[kDialogRefuseCoffee]._text =
	        "_}(Well, toodle-oo then. We've got some sleep to catch. This game took ages to write.']]]=";
	_dialog[kDialogYesCoffee]._text =
	        "_}(Now there's a good sport. How many hit points should we give him, a million? "
	        "Okay, fifteen. Good luck, guy.']]]=";
	_dialog[kDialogDragNote]._text =
	        "_}Notice: Flying lizards can be trained just after they hatch. Use bait.]]]=";
	_dialog[kDialogDream5]._text =
	        "_}After your last dream, you have some apprehension about falling asleep, but physical exhaustion prevails. "
	        "[You imagine a dragon. No, many dragons. You appear to be seeing some kind of peaceful dragon civilization. ~";
	_dialog[kDialogDream5]._nextPage = kDialogDream1P2X;
	_dialog[kDialogDream1P2X]._text =
	        "It is underground, in dungeons that look vaguely familiar. "
	        "You get a strange sense of- it's difficult to pinpoint- eternity. It feels as if ~";
	_dialog[kDialogDream1P2X]._nextPage = kDialogDream1P3Y;
	_dialog[kDialogDream1P3Y]._text = "the civilization has existed since the beginning of time.]]]]]=";
	_dialog[kDialogWormSensorDescription]._text =
	        "_}You find a strange device and instructions:[(Worm danger in room after flying lizards! "
	        "The only safe path is left, down, right, down, left, down, right, up, right, down. ~";
	_dialog[kDialogWormSensorDescription]._nextPage = kDialogWormSensorDescription2;
	_dialog[kDialogWormSensorDescription2]._text =
	        "Sensor pitch changes when you step off the path. Sensor only lasts 30 seconds.'[@";
	_dialog[kDialogWormSensorString]._text = "#sensor@";
	_dialog[kDialogWormSensorString]._iconId = kSpriteIconSporesBag;
	_dialog[kDialogEggString]._text = "#  egg@";
	_dialog[kDialogEggString]._iconId = kSpriteIconBook;
	_dialog[kDialogEggDescription]._text = "You find a large egg.&@";
	_dialog[kDialogEggCracks]._text =
	        "_}Suddenly the egg you are carrying shakes violently. A crack develops. "
	        "A red bird-like creature pushes its way out of the shell.]]]=";
	_dialog[kDialogCrackEgg]._text =
	        "}The egg is warm. It feels like something inside is moving. Crack it open?%";
	_dialog[kDialogEatEgg]._text =
	        "_}A wiry fetus spills out. It looks like some kind of a bird, but there are no feathers.[Eat it?%";
	_dialog[kDialogGeigerWorks]._text = "The device starts to&ping quiety.]]]=";
	_dialog[kDialogFlameThrowDescription]._text =
	        "}You find a weak fireball spell, good for one minute of constant use. @";
	_dialog[kDialogFlameThrowString]._text = "#fireballs@";
	_dialog[kDialogFlameThrowString]._iconId = kSpriteIconScroll;
	_dialog[kDialogMerchantXDescription]._text =
	        "_}Greetings, old friend! I'll sell you the potion you need. Sixty gold pieces. Take it?'%";
	_dialog[kDialogGoblinTalk]._text =
	        "_}(My patrol leader wants to talk to you. Follow me.' [He walks out the door.]]]]=";
	_dialog[kDialogPlanTalk]._text =
	        "_}We need your help. [Long ago, in the Age of Dragons, there was a great spring in these dungeons, "
	        "a Fountain of Youth. ~";
	_dialog[kDialogPlanTalk]._nextPage = kDialogPlan2;
	_dialog[kDialogPlan2]._text =
	        "But that was long ago. Now only a trickle of enchanted water flows, "
	        "and a norlac -water monster- blocks our access to it altogether. ~";
	_dialog[kDialogPlan2]._nextPage = kDialogPlan3;
	_dialog[kDialogPlan3]._text =
	        "The norlac also blocks your access to the deepest level. You see, we both need the monster killed. "
	        "We have a plan... [The water drains into a whirlpool which is powerful enough to drown the norlac if he got caught in it. ~";
	_dialog[kDialogPlan3]._nextPage = kDialogPlan4;
	_dialog[kDialogPlan4]._text =
	        "There is a sluice gate at the other end of the tunnel. We need you to distract the norlac "
	        "so we can open the gate to flush him down the whirlpool. [Somehow, you must get to the access. "
	        "[Good luck. We are counting on you.']]]]]=";
	_dialog[kDialogHasSpiders]._text =
	        "It looks like there is&something crawling under&the latch. Open it anyway?%";
	_dialog[kDialogPourHere]._text = "Pour it out here?%";
	_dialog[kDialogPourOnChest]._text = "Pour it out on the chest?%";
	_dialog[kDialogAlcoholDescription]._text = "You find a bottle of&alcohol. @";
	_dialog[kDialogAlcoholString]._text = "#  alcohol@";
	_dialog[kDialogAlcoholString]._iconId = kSpriteIconBottle;
	_dialog[kDialogLevitateDescription]._text =
	        "_}You find a spell of levitation and a note: Don't step on cobwebs or egg sacks. "
	        "Use levitation to get through the hall of webs.][@";
	_dialog[kDialogLevitateString]._text = "#levitate@";
	_dialog[kDialogLevitateString]._iconId = kSpriteIconScroll;
	_dialog[kDialogDream6]._text =
	        "_}The goblins you met on the last level had asked you to help them flush a monster out of their water supply. "
	        "But where is their water supply? You sense as you approach the next level that water is near...]]]=";
	_dialog[kDialogDream7]._text =
	        "_}It is difficult to get to sleep. What visions are in store for you now? "
	        "You unwillingly fall asleep thinking about the city of fountains you dreamt of three long days ago... ~";
	_dialog[kDialogDream7]._nextPage = kDialogDream1P2XW;
	_dialog[kDialogDream1P2XW]._text =
	        "[You are inside a room, at a meeting between city officials and wizards. The officials want water access. "
	        "They are planning a seige. The wizards are arguing over a weapon they have created. ]]~";
	_dialog[kDialogDream1P2XW]._nextPage = kDialogDream1P2YW;
	_dialog[kDialogDream1P2YW]._text =
	        "There is some problem with it. [The dream changes.]]][You see a wall of fire. "
	        "Now, in the flames, you see men attacking dragons. There is a flash. All are dead. You see another attack. "
	        "Defending himself, a dragon ~";
	_dialog[kDialogDream1P2YW]._nextPage = kDialogDreamXXY;
	_dialog[kDialogDreamXXY]._text =
	        "incinerates the army, but then another flash kills him instantly. "
	        "Armies block the exits of the dungeons, trapping the dragons inside. One escapes...]]]]]=";
	_dialog[kDialogNotHere3]._text = "This is to be thrown, but&not here.@";
	_dialog[kDialogNotHere2]._text = "Not here.@";
	_dialog[kDialogDownVortexString]._text =
	        "_}You hear a voice... Could you be dreaming?[You remember the raging current of the vortex "
	        "pulling you toward a hole in the floor.[But now it is quiet.]] Time has passed... "
	        "You sense that someone or something is nearby.]]]=";
	_dialog[kDialogDunricString7]._text =
	        "_}As you approach, the man lifts his head. He seems to know you.]][(I am Dunric,' he falters, "
	        "(I sent my servant to warn you. Mordamir isn't a prisoner...~";
	_dialog[kDialogDunricString7]._nextPage = kDialogDunricString8;
	_dialog[kDialogDunricString8]._text =
	        "[He kidnapped my daughter... He is manipulating... you... "
	        "If I had my ring I could... but... my servant...']]]=";
	_dialog[kDialogGiveDunricRing]._text = "Give Dunric his ring?%";
	_dialog[kDialogDunricTransaction]._text =
	        "_}Dunric pauses, then lowers his head. Three spells appear in front of you: "
	        "Body Statue, Magnetic hands, and Sonic protection. Dunric doesn't raise his head again.]]]=";
	_dialog[kDialogUlindorString7]._text =
	        "_}You found Dunric, did you? What did he tell you? He told you about Mordamir, didn't he? "
	        "Then I'll have to kill you.]]]=";
	_dialog[kDialogNurseText]._text =
	        "}_You wake up remembering the kind touch of the goblin who revived you with water from the Fountain. "
	        "Or was she just a dream?]]]=";
	_dialog[kDialogAntiString]._text = "#  sonic@";
	_dialog[kDialogAntiString]._iconId = kSpriteIconScroll;
	_dialog[kDialogBlinkDescription]._text = "#$ blinks@";
	_dialog[kDialogBlinkDescription]._iconId = kSpriteIconScroll;
	_dialog[kDialogBlinkString]._text = "You find a blink spell, good&for multiple uses.&@";
	_dialog[kDialogTractorString]._text = "#magnetic@";
	_dialog[kDialogTractorString]._iconId = kSpriteIconScroll;
	_dialog[kDialogBronzeString]._text = "#$ statue@";
	_dialog[kDialogBronzeString]._iconId = kSpriteIconScroll;
	_dialog[kDialogImmunityDescription]._text = "#fire prot.@";
	_dialog[kDialogImmunityDescription]._iconId = kSpriteIconScroll;
	_dialog[kDialogImmunityString]._text =
	        "You find spell of fire&protection, good for three&seconds. @";
	_dialog[kDialogAmuletDescription]._text =
	        "You find a shiny, reflective&amulet. There are runes on&one side. @";
	_dialog[kDialogAmuletString]._text = "# amulet@";
	_dialog[kDialogAmuletString]._iconId = kSpriteIconAmulet;
	_dialog[kDialogHoldItUp]._text = "Hold it up to the light here?%";
	_dialog[kDialogReadRunes]._text = "Read the runes here?%";
	_dialog[kDialogMordamirString1]._text =
	        "_}(Fool! Read the words! I've waited a thousand years for this. Read the words!]]]"
	        "[Fine, then I'll just take back my amulet. I have other students who will come. Prepare to die.']]]=";
	_dialog[kDialogMordamirString2]._text =
	        "_}You have no more defenses, my student. [What a pity I wasted so much time on you. "
	        "You don't think you made it here on your own, do you? Look at me. Do I remind you of a merchant, perhaps? ~";
	_dialog[kDialogMordamirString2]._nextPage = kDialogMordamir3D;
	_dialog[kDialogMordamir3D]._text = "Who do you think left you those chests?~";
	_dialog[kDialogMordamir3D]._nextPage = kDialogMordamir3;
	_dialog[kDialogMordamir3]._text =
	        "[Do you even know why I summoned you? One thousand years ago, I created this amulet to kill the dragons "
	        "that governed the Fountain of Youth. But this one escaped. He came back and destroyed my city. ~";
	_dialog[kDialogMordamir3]._nextPage = kDialogMordamir4;
	_dialog[kDialogMordamir4]._text =
	        "I was the sole survivor. Now I have returned to reclaim the fountain that gave me a thousand years of life."
	        "[You were to kill the dragon for me. You see, the power the amulet takes to kill a dragon ~";
	_dialog[kDialogMordamir4]._nextPage = kDialogMordamir5;
	_dialog[kDialogMordamir5]._text =
	        "will also kill the one using it. So I can't attack the dragon myself. "
	        "But as long as I have this amulet, the dragon won't attack me.]]]=";
	_dialog[kDialogGoodbye]._text = "Now you will die.]]]]=";
	_dialog[kDialogEndText]._text =
	        "}_The journey out of the dungeons takes two days, but with Ana by your side, time seems unimportant. "
	        "The water invigorates you with new youth, and you discover a new spring to your walk.~";
	_dialog[kDialogEndText]._nextPage = kDialogEtXX;
	_dialog[kDialogEtXX]._text =
	        " As you travel, your thoughts return to Mordamir and the dragon. "
	        "They were alike, in a way, each the only~";
	_dialog[kDialogEtXX]._nextPage = kDialogEt2;
	_dialog[kDialogEt2]._text =
	        " survivor of a civilization destroyed by the other more than a thousand years ago. "
	        "They were an equal match also, and it seems strange that you would tilt the balance of a conflict forged so long ago...]]]]=";
	_dialog[kDialogEndText2]._text =
	        "}_The journey out of the dungeons takes two days.  As you travel, your thoughts return to Mordamir and the dragon. "
	        "They were alike, in a way, each the only~";
	_dialog[kDialogEndText2]._nextPage = kDialogEt2P;
	_dialog[kDialogEt2P]._text =
	        " survivor of a civilization destroyed by the other more than a thousand years ago. They were an equal match also, "
	        "and it seems strange that you would tilt the balance of a conflict forged so long ago...]]]]=";
}

void Dialog::load(DialogId id) {
	reset();
	_text = _dialog[id]._text;
	_id = id;
	_timeSinceLastUpdate.start();
}

void Dialog::reset() {
	_cursorPos.x = _cursorOriginX;
	_cursorPos.y = _cursorOriginY;
	_text = nullptr;
	_timeSinceLastUpdate.stop();
	_scrollingMode = false;
	_id = kDialogNone;
}

int Dialog::getDelay() const {
	return _delay;
}

DialogId Dialog::getId() const {
	return _id;
}

void Dialog::nextChar() {
	assert(*_text != '\0');
	++_text;
	_delay = 0;
}

// Those functions are only needed when entering a password.
// Redraws whole line on every change
void Dialog::printChar(int c) {
	c = tolower(c);
	bool isHex = Common::isDigit(c) || (c >= 'a' && c <= 'f');
	const int passwordLengthMax = ARRAYSIZE(_password) - 2;
	if (isHex && _passwordCharIndex < passwordLengthMax) {
		_password[_passwordCharIndex++] = c;
		_password[_passwordCharIndex] = '-';

		resetCursor();
		newline();
		_screen->fillRect(_cursorPos.x, _cursorPos.y,
		                  _rowWidthLimit, _cursorPos.y + _rowHeight, 0);
		_text = _password;
		while (*_text)
			update(false);
	}
}

bool Dialog::removeChar() {
	if (_passwordCharIndex) {
		_password[_passwordCharIndex--] = 0;
		_password[_passwordCharIndex] = '-';

		_screen->fillRect(_cursorOriginX, _cursorPos.y,
		                  _rowWidthLimit, _cursorPos.y + _rowHeight, 0);
		_text = _password;
		_cursorPos.x = _cursorOriginX;
		while (*_text)
			update(false);

		return true;
	} else {
		return false;
	}
}

/**
 * TODO:
 * Is position even needed or should the renderer know about Dialog layouts and depending on the type
 * advance the animation during update? Probably not. Instead, confine the Renderer to rendering and store
 * as little non-render state as possible.
 * At what x value is it necessary to line break the text? -- Scan word length and check if it fits
 * Difference between fast and slow scroll?
 * The following are tokens for render behavior that should better be handled in the logic
 *      =       end of string
 *      @       end of string, wait for OKAY
 *      *n      wait for n cycles, then clear screen    -- not used
 *      &       line break
 *      ^       center penx
 *      #n      draw icon number n
 *      %       end of string, return yes/no
 *      +       apostrophy
 *      _       print the string in slow text
 *      ~n      continue printing string ID n
 *      {n      wait for n cycles                       -- not used
 *      }       do automatic line and page breaks
 *      [       page break with delay of 490ms
 *      ]       delay 140ms
 *      $       print the number passed to text_print in ACC
 *      (       backquote
 *      <       fast text
 *      >       no format
 *      |       do fadein
 *      \       fadeout
 *      /       slow fadeout
 *
 * @brief Dialog::update iterates over the dialog text one char at a time
 * @return kDialogRCNotFinished if there are still chars left to print.
 *         kDialogRCYes/No/Ok represent what button was selected.
 *         For dialog without buttons we just return Ok as well.
 */
DialogToken Dialog::update(bool keyPressed) {
	switch (*_text) {
	case kDialogTokenEndOfStringOk:
	case kDialogTokenEndOfStringYesNo:
	case kDialogTokenLoadNextString:
	case kDialogTokenStringTerminator:
		return (DialogToken)*_text;

	case kDialogTokenEndOfString:
		_cursorPos.x = _cursorOriginX;
		_cursorPos.y = _cursorOriginY;
		return kDialogTokenDelay;

	case kDialogTokenDelay40:
		_delay = 40 * _delayInMs;
		return kDialogTokenDelay;

	case kDialogTokenDelayAndPageBreak:
		_delay = 140 * _delayInMs;
		return kDialogTokenDelay;

	case kDialogTokenDelay:
		_delay = 0;
		++_text;
		while (Common::isDigit(*_text)) {
			_delay = _delay * 10 + (*_text - '0');
			++_text;
		}
		--_text;
		_delay *= _delayInMs;
		return kDialogTokenDelay;

	case kDialogTokenDelayAndClear:
		// parse number after token
		break;

	case kDialogTokenSlowScroll:
		_scrollingMode = true;
		break;

	case kDialogTokenFastScroll:
		_scrollingMode = true;
		break;

	case kDialogTokenFadeIn:
		_screen->paletteFadeIn();
		break;

	case kDialogTokenFadeOut:
		_screen->paletteFadeOut();
		break;

	case kDialogTokenSlowFadeOut:
		_screen->paletteSlowFadeOut();
		break;

	case kDialogTokenLineBreak:
		newline();
		break;

	case kDialogTokenDrawIcon:
		break;

	case kDialogTokenPrintNumber:
		break;

	case kDialogTokenNoFormat:
		break;

	case kDialogTokenApostrophy:
		printText();
		break;

	case kDialogTokenBackquote:
		printText();
		break;

	case kDialogTokenCenterCursorX:
		_cursorPos.x = _screen->_frameWidth +
		               ((_screen->_viewportWidth / 2) - (_iconWidth / 2));
		break;

	case kDialogTokenAutoLineAndPageBreaks:
		break;

	default:
		printText();
		break;
	}

	++_text;
	_timeSinceLastUpdate.reset();

	return (DialogToken)*_text;
}

void Dialog::printText() {
	// TODO:
	// Advance to next line if word does not fit in row (test row limit to be sure)
	// Current linebreak is just a workaround
	// If dialog not in scrolling mode, render whole page instead of single char
	// return if *_text is a token
	if (_cursorPos.x + _maxCharWidth > _rowWidthLimit)
		newline();

	switch (*_text) {
	case ' ':
		_cursorPos.x += 8;
		return;
	case '\'':
		_cursorPos.x -= 2;
		break;
	case 'm':
	case 'M':
	case 'w':
	case 'W':
		_cursorPos.x += 8;
		break;
	case 'i':
	case 'l':
		_cursorPos.x -= 4;
		break;
	case 'j':
	case 't':
		_cursorPos.x -= 2;
		break;
	}
	if (Common::isUpper(*_text))
		_cursorPos.x += 8;

	_screen->drawChar(*_text, _cursorPos.x, _cursorPos.y);

	switch (*_text) {
	case '\'':
	case 'T':
		_cursorPos.x += 6;
		break;
	default:
		_cursorPos.x += 8;
		break;
	}
}

void Dialog::resetCursor() {
	_cursorPos.x = _cursorOriginX;
	_cursorPos.y = _cursorOriginY;
}

void Dialog::newline() {
	_cursorPos.x = _cursorOriginX;
	_cursorPos.y += _rowHeight;
}

}
