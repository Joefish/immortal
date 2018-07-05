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

struct DialogData {
	DialogData(const char *text, SpriteId iconId = kSpriteNone, DialogId nextPage = kDialogNone)
	    : _text(text)
	    , _iconId(iconId)
	    , _nextPage(nextPage) {
	}

	const char *_text;
	SpriteId _iconId;
	DialogId _nextPage;
};

// TODO:
// Change Intro string depending on game version
static const DialogData dialog[kDialogNum] = {
	// kDialogIntro
	DialogData("\\   Electronic Arts presents&&       The Immortal\x19&&&&"
	           "     \x18 1991 Will Harvey|]]]]]]]]\\]="
	           "          written by&&         Will Harvey&         Ian Gooding&"
	           "      Michael Marcantel&       Brett G. Durrett&        Douglas Fulton|]]]]]]]/="
#if 0
	           "&&      Amiga version by&&       Brett G. Durrett&]]]]]]]="
	           "&&       Atari version by&&      Brett G. Durrett&]]]]]]]="
#endif
	           "&&       IBM version by&&      Kenneth L. Hurley&|]]]]]]]="),
	// kDialogNewGame
	DialogData("New game?%"),
	// kDialogPartyString
	DialogData("Ken Hurley and Rick &Rutkowski want you to &have this silver bullet.@"),
	// kDialogKoorsString
	DialogData("#  beer@", kSpriteKoorsLight),
	// kDialogBeerManString
	DialogData("You feel invinicible now.@"),
	// kDialogKoorsOpen
	DialogData("It's 8 am! &Shotgun the beer?%"),
	// kDialogMerchantDescription
	DialogData("_}Greetings, friend! Come, I+ve got something you need. These parts are plagued with slime. "
	           "You can+t venture safely without my slime oil for boots, a bargain at only 80 gold pieces.%"),
	// kDialogMerchant3Description
	DialogData("_}All right, 60 gold pieces for my oil. Rub it on your boots and slime won+t touch you. 60, friend.%"),
	// kDialogMapText1
	DialogData("This room isn+t on the map.&Look at the picture.@"),
	// kDialogMapText2
	DialogData("This room is on the map.&Look at the picture.@"),
	// kDialogSwordString
	DialogData("# sword@", kSpriteIconSword),
	// kDialogSwordDescription
	DialogData("You find an Elven sword of&combat agility. Take it?@"),
	// kDialogBonesText1
	DialogData("Search the bones?%"),
	// kDialogBonesText2
	DialogData("}The sword increases your quickness permanently.@"),
	// kDialogBonesText3
	DialogData("}You notice something that looks wet and green under the pile. Search further?%"),
	// kDialogDustOfComplaisanceString
	DialogData("#  dust@", kSpriteIconBaitBag),
	// kDialogDustOfComplaisanceDescription
	DialogData("}You find a bag containing Dust of Complaisance.&@"),
	// kDialogOpenBag
	DialogData("}Drop the bait on the ground here?%"),
	// kDialogThrowDustOfComplaisance
	DialogData("}To use this dust, you throw it in the air. Do that here?%"),
	// kDialogSmithText1
	DialogData("_}Don+t bother me, I+m cutting a gem. Yes, you need it. No, you can+t have it. "
	           "I wouldn+t give this gem to anyone, least of all you. Go away.]]]]="),
	// kDialogSmithText2
	DialogData("_}Let me help you. Take this gem. There you go. Good luck.]]]]="),
	// kDialogCarpetString
	DialogData("#carpet@", kSpriteIconCarpet),
	// kDialogBombString
	DialogData("# bomb@", kSpriteIconBomb),
	// kDialogBombDesc
	DialogData("A gas bomb that goblins&use to paralyze trolls.&@"),
	// kDialogPickItUp
	DialogData("Take it?<>@"),
	// kDialogYesNoString
	DialogData("%"),
	// kDialogOtherString
	DialogData(" other@"),
	// kDialogChestKeyString
	DialogData("#  key@", kSpriteIconKey),
	// kDialogChestKeyDescription
	DialogData("A key to a chest.&@"),
	// kDialogOpenChestDescription
	DialogData("The chest is open. Examine&contents?%"),
	// kDialogPutItOn
	DialogData("Put it on?%"),
	// kDialogDropItThen
	DialogData("Drop it?%"),
	// kDialogChestDescription
	DialogData("It+s unlocked. Open it?%"),
	// kDialogGoodChestDescription
	DialogData("It+s locked but you have&the key. Open it?%"),
	// kDialogBadChestDescription, kDialogCantUnlockDoor
	DialogData("It+s locked and you don+t&have the key.@"),
	// kDialogGoldString
	DialogData("#$0 gold@", kSpriteIconGoldBag),
	// kDialogFindGoldString
	DialogData("You find $0 gold pieces.&&^#@", kSpriteIconGold),
	// kDialogNullString
	DialogData("@"),
	// kDialogNotHere
	DialogData("You can+t plant them on&stone tiles.@"),
	// kDialogUnlockDoor
	DialogData("It+s locked but you are&able to unlock it with&the key.@"),
	// kDialogWeak1String
	DialogData("_}The king is not dead, but the poison is taking effect. When he sees you, he utters "
	           "(Give me water... the fountain... I give you... information... peace...+ Give him water?%"),
	// kDialogDummyWater
	DialogData("_}You dont have any water to give him. He mumbles something. Then silence... You find a key on his body.]]]]="),
	// kDialogBadWizard
	DialogData("_}He mumbles something. Then silence... You find a key on his body.]]]]="),
	// kDialogDiesAnyway
	DialogData("_}I+ll tell you how to... next level... just beyond slime... three jewels... slime... rock becomes... "
	           "floor... right, left, center of the... [Then silence. His hand opens, releasing a key.]]]]="),
	// kDialogDoorKeyDescription
	DialogData("You find a door key.&@"),
	// kDialogNoteDescription
	DialogData("You find a note.&@"),
	// kDialogNoteString
	DialogData("#  note@", kSpriteIconLetter),
	// kDialogLootBodyDescription
	DialogData("He+s dead.&Look for possessions?%"),
	// kDialogNotEnough
	DialogData("You don+t have it. Check&your inventory.@"),
	// kDialogGameOverString
	DialogData("Game Over&&Play again?@"),
	// kDialogYouWin
	DialogData("Congratulations!&&Play again?@"),
	// kDialogWormFoodDescription
	DialogData("You find a bag of bait.&@"),
	// kDialogWormFoodString
	DialogData("#   bait@", kSpriteIconBaitBag),
	// kDialogStoneDescription
	DialogData("You find a stone. @"),
	// kDialogStoneString
	DialogData("# stone@", kSpriteIconStone),
	// kDialogGemDescription
	DialogData("You find a red gem.&@"),
	// kDialogGemString
	DialogData("#  gem@", kSpriteIconRuby),
	// kDialogFireballDescription
	DialogData("You find a book with&fireball spells.&@"),
	// kDialogFireballString
	DialogData("#$ shots@", kSpriteIconScroll),
	// kDialogDeathMapDescription
	DialogData("You find a map warning&you about pit traps.&@"),
	// kDialogDeathMapString
	DialogData("#  map@", kSpriteIconMap),
	// kDialogBootsString
	DialogData("#   oil@", kSpriteIconBottle),
	// kDialogUseBootString
	DialogData("You try it out but notice&as you walk that the leather&is quickly drying out.@"),
	// kDialogCharmDescription
	DialogData("}You find a scroll with a charm spell to use on will o+ the wisps.&@"),
	// kDialogCharmString
	DialogData("# charm@", kSpriteIconScroll),
	// kDialogUseCharmString
	DialogData("}This charms the will o+ the wisps to follow you. Read the spell again to turn them against your enemies.@"),
	// kDialogWaterOpen
	DialogData("}It looks like water. Drink it?%"),
	// kDialogDrinkIt
	DialogData("Drink it?%"),
	// kDialogItWorks
	DialogData("}It works! You are much stronger.]]]="),
	// kDialogSbOpen
	DialogData("}It looks like it has green stuff inside. Open it?%"),
	// kDialogUsesFireString
	DialogData("Okay, now this will take&effect when you press the&fire button.@"),
	// kDialogMuscleDescription
	DialogData("You find a potion,&Magic Muscle.&@"),
	// kDialogMuscleString
	DialogData("#  potion@", kSpriteIconBottle),
	// kDialogSbDescription
	DialogData("You find a bottle.&@"),
	// kDialogSbString
	DialogData("#  bottle@", kSpriteIconBottle),
	// kDialogFaceString
	DialogData("#protean@", kSpriteIconRing),
	// kDialogFaceDescription
	DialogData("You find a Protean Ring.&@"),
	// kDialogTrndescription
	DialogData("You find a troll ritual knife,&used to declare a fight to&the death. @"),
	// kDialogTrnString
	DialogData("# knife@", kSpriteIconDagger),
	// kDialogInvisDescription
	DialogData("_}It is a fine woman+s garment. Folded inside is a ring with the words, "
	           "[`To Ana, so harm will never find you. Love, Dunric.+ @"),
	// kDialogGoodLuckDescription
	DialogData("You find a small, well&crafted ring. @"),
	// kDialogAnaRingString
	DialogData("#from ana@", kSpriteIconRing),
	// kDialogInvisString
	DialogData("#  ana+s@", kSpriteIconRing),
	// kDialogGoesAway
	DialogData("_}She is hurt and upset when she finds you don+t have her ring or won+t give it to her. "
	           "She scurries back into the hole. The hole is too small for you to follow.&@"),
	// kDialogGiveHerRing
	DialogData("_}`Oh sir, can you help me,+ the girl pleads. `I was kidnapped and dragged down here. "
	           "All the man would say is `Mordamir+s orders.+ I ~", kSpriteNone, kDialogGive2),
	// kDialogGive2
	DialogData("escaped using a ring my father gave me, but now I+ve lost it. Did you find it?+%"),
	// kDialogMadKingText
	DialogData("_}We have met before, old man. Do you remember? Because you helped me, you may pass. "
	           "But I warn you, we are at war with the trolls. Over this ladder, across the spikes, is troll territory.@"),
	// kDialogMadKing2Text
	DialogData("_}You are an impostor!]]]]="),
	// kDialogMadKing3Text
	DialogData("_}Old man, do you remember me? I am king of the goblins. You didn+t give me the water. "
	           "You left me to die after you took the key from me. Now you will pay.]]]]="),
	// kDialogDream1P1
	DialogData("_}Ah, a rest is exactly what you need right now. You quickly fall into a deep, dream filled sleep..."
	           "[Vivid images of a beautiful enchanted city pass by. All the city people are young. There are ~",
	           kSpriteNone, kDialogDream1P2),
	// kDialogDream1P2
	DialogData("fountains all around, water everywhere. A huge wall surrounds the city, sealing it from the outside world..."
	           "[Suddenly the images go black. A face appears... Mordamir!]][ ~", kSpriteNone, kDialogDream1P3),
	// kDialogDream1P3
	DialogData("He is different from how you remember him. His gentle features are now withered. "
	           "His kind eyes, now cold and sunken, seem to look through you with a dark, penetrating stare. "
	           "You wake rejuvenated, but disturbed.]]]]]="),
	// kDialogHowToGetOut
	DialogData("_}Here, take this ring in return. [I overheard the obnoxious little dwarf saying "
	           "(Clockwise, three rings around the triangle.+ Could that be a clue to his exit puzzle? "
	           "[I must go. Goodbye.]]]]="),
	// kDialogRestartString
	DialogData("Start over?%"),
	// kDialogSporesString
	DialogData("# spores@", kSpriteIconSporesBag),
	// kDialogSporesDescription
	DialogData("You find a sack of bad&smelling spores.&@"),
	// kDialogRequestPlayDisk
	DialogData("Please insert play disk.@"),
	// kDialogOldGameString
	DialogData("New game?%"),
	// kDialogEnterCertificate
	DialogData("Enter certificate:&-="),
	// kDialogBadCertificate
	DialogData("Invalid certificate.@"),
	// kDialogCertificateString
	DialogData("End of level!&Here is your certificate:&&="),
	// kDialogCertificate2String
	DialogData("&@"),
	// kDialogExitString
	DialogData(" Are you sure you & want to exit Immortal?%"),
	// kDialogCertCheckString0
	DialogData("Look in your manual for this&picture. Type the ="),
	// kDialogCertCheckString1
	DialogData("first&letter on row ="),
	// kDialogCertCheckString2
	DialogData("second&letter on row ="),
	// kDialogCertCheckFirst
	DialogData("fourth&letter on row ="),
	// kDialogCertCheckSecond
	DialogData("sixth&letter on row ="),
	// kDialogCertCheckFourth
	DialogData(", below.&&="),
	// kDialogCertCheckSixth
	DialogData("No, that+s not it.&One more try.]]]]="),
	// kDialogDream1
	DialogData("}_The straw is a small but welcome comfort in your first day+s travel. "
	           "As you drift into an uneasy slumber, you begin to wonder about Mordamir. "
	           "How long has he been held prisoner? Where?~", kSpriteNone, kDialogD1D2),
	// kDialogD1D2
	DialogData(" You finally fall asleep dreaming about adventures that lie ahead.]]]="),
	// kDialogPhantDescription
	DialogData("_}An image of the old wizard Mordamir leaps from the candle and begins to speak,"
	           "[(Dunric, you have come~", kSpriteNone, kDialogWizardText2),
	// kDialogWizardText2
	DialogData(" to save me. I am in the dungeons far below. I know I can count on you.+[~", kSpriteNone, kDialogWizardText3),
	// kDialogWizardText3
	DialogData("This explains your old teacher+s mysterious disappearance, "
	           "but there is one thing strange about the message...[Your name is not Dunric. ]]]]="),
	// kDialogDunricDescription
	DialogData("}The body of a fighter. Look for possessions?%"),
	// kDialogUlindorString0
	DialogData("_}You have come to save Mordamir, have you? He is held prisoner many levels below. "
	           "There is a hidden passage way. That is all I can tell you.[~", kSpriteNone, kDialogUlindorString1),
	// kDialogUlindorString1
	DialogData("Without another word, the man hands you a key and runs out the door.]]]]="),
	// kDialogGuardNote
	DialogData("_}Beware of shades. They are dangerous, invisible creatures that like darkness. "
	           "Under firelight they cast a shadow by which you can detect and avoid them.@"),
	// kDialogDunricRingDescription
	DialogData("}You find a ring. There is a name inscribed on the band: Dunric!&@"),
	// kDialogDunricRingString
	DialogData("#dunric+s@", kSpriteIconRing),
	// kDialogUlindorString2
	DialogData("_}`We are even now, wizard. Here, you will need this.+ ~", kSpriteNone, kDialogUlindorString3),
	// kDialogUlindorString3
	DialogData("He hands you a musty red carpet. (It is dangerous to step even one foot in the next two rooms. "
	           "After that, the exit is just down three ladders.+ With that advice, he turns and walks briskly away.@"),
	// kDialogDreamLevel2
	DialogData("_}When you clear your mind of the day+s troubles, you start to think about the goblins. "
	           "[They appear to be rational. Perhaps you can reach some agreement with them.]]]="),
	// kDialogWarning
	DialogData("}Stop! I forbid you to come any closer. Go back.@"),
	// kDialogThrowTrn
	DialogData("Throw it here?%"),
	// kDialogThrowTrn2
	DialogData("The knife lands near the troll.]]]="),
	// kDialogDreamLevel3
	DialogData("_}The poison from the spores must have killed the goblin king. But now he is alive! "
	           "There is something very magical in these dungeons.]]]="),
	// kDialogCoffeeDescription
	DialogData("A coffee pot? @"),
	// kDialogCoffeeString
	DialogData("# coffee@", kSpriteIconCoffee), // why 'swordFrame'? there are a few ids that don't fit the description..
	// kDialogGimmeCoffee
	DialogData("_}(Hey, what+s this?&&The wizard![Brett, I told you someone would find us.[Wake up, Mike and Ian. "
	           "We+ve got a visitor.[Listen wizard, Mike needs some coffee in the morning. Got any?+%"),
	// kDialogNoCoffee
	DialogData("_}(Don+t try to fool me, I wrote this game. You know what happens to fibbers?+]]]="),
	// kDialogRefuseCoffee
	DialogData("_}(Well, toodle-oo then. We+ve got some sleep to catch. This game took ages to write.+]]]="),
	// kDialogYesCoffee
	DialogData("_}(Now there+s a good sport. How many hit points should we give him, a million? Okay, fifteen. Good luck, guy.+]]]="),
	// kDialogDragNote
	DialogData("_}Notice: Flying lizards can be trained just after they hatch. Use bait.]]]="),
	// kDialogDream5
	DialogData("_}After your last dream, you have some apprehension about falling asleep, but physical exhaustion prevails. "
	           "[You imagine a dragon. No, many dragons. You appear to be seeing some kind of peaceful dragon civilization. ~",
	           kSpriteNone, kDialogDream1P2X),
	// kDialogDream1P2X
	DialogData("It is underground, in dungeons that look vaguely familiar. "
	           "You get a strange sense of- it+s difficult to pinpoint- eternity. It feels as if ~",
	           kSpriteNone, kDialogDream1P3Y),
	// kDialogDream1P3Y
	DialogData("the civilization has existed since the beginning of time.]]]]]="),
	// kDialogGeigerDescription
	DialogData("_}You find a strange device and instructions:[(Worm danger in room after flying lizards! "
	           "The only safe path is left, down, right, down, left, down, right, up, right, down. ~",
	           kSpriteNone, kDialogGeigerDescription2),
	// kDialogGeigerDescription2
	DialogData("Sensor pitch changes when you step off the path. Sensor only lasts 30 seconds.+[@"),
	// kDialogGeigerString
	DialogData("#sensor@", kSpriteIconSporesBag),
	// kDialogEggString
	DialogData("#  egg@", kSpriteIconBook),
	// kDialogEggDescription
	DialogData("You find a large egg.&@"),
	// kDialogEggCracks
	DialogData("_}Suddenly the egg you are carrying shakes violently. A crack develops. "
	           "A red bird-like creature pushes its way out of the shell.]]]="),
	// kDialogCrackEgg
	DialogData("}The egg is warm. It feels like something inside is moving. Crack it open?%"),
	// kDialogEatEgg
	DialogData("_}A wiry fetus spills out. It looks like some kind of a bird, but there are no feathers.[Eat it?%"),
	// kDialogGeigerWorks
	DialogData("The device starts to&ping quiety.]]]="),
	// kDialogFlameThrowDescription
	DialogData("}You find a weak fireball spell, good for one minute of constant use. @"),
	// kDialogFlameThrowString
	DialogData("#fireballs@", kSpriteIconScroll),
	// kDialogMerchantXDescription
	DialogData("_}Greetings, old friend! I+ll sell you the potion you need. Sixty gold pieces. Take it?+%"),
	// kDialogGoblinTalk
	DialogData("_}(My patrol leader wants to talk to you. Follow me.+ [He walks out the door.]]]]="),
	// kDialogPlanTalk
	DialogData("_}We need your help. [Long ago, in the Age of Dragons, there was a great spring in these dungeons, "
	           "a Fountain of Youth. ~", kSpriteNone, kDialogPlan2),
	// kDialogPlan2
	DialogData("But that was long ago. Now only a trickle of enchanted water flows, "
	           "and a norlac -water monster- blocks our access to it altogether. ~", kSpriteNone, kDialogPlan3),
	// kDialogPlan3
	DialogData("The norlac also blocks your access to the deepest level. You see, we both need the monster killed. "
	           "We have a plan... [The water drains into a whirlpool which is powerful enough to drown the norlac if he got caught in it. ~",
	           kSpriteNone, kDialogPlan4),
	// kDialogPlan4
	DialogData("There is a sluice gate at the other end of the tunnel. We need you to distract the norlac "
	           "so we can open the gate to flush him down the whirlpool. [Somehow, you must get to the access. "
	           "[Good luck. We are counting on you.+]]]]]="),
	// kDialogHasSpiders
	DialogData("It looks like there is&something crawling under&the latch. Open it anyway?%"),
	// kDialogPourHere
	DialogData("Pour it out here?%"),
	// kDialogPourOnChest
	DialogData("Pour it out on the chest?%"),
	// kDialogAlcoholDescription
	DialogData("You find a bottle of&alcohol. @"),
	// kDialogAlcoholString
	DialogData("#  alcohol@", kSpriteIconBottle),
	// kDialogLevitateDescription
	DialogData("_}You find a spell of levitation and a note: Don+t step on cobwebs or egg sacks. "
	           "Use levitation to get through the hall of webs.][@"),
	// kDialogLevitateString
	DialogData("#levitate@", kSpriteIconScroll),
	// kDialogDream6
	DialogData("_}The goblins you met on the last level had asked you to help them flush a monster out of their water supply. "
	           "But where is their water supply? You sense as you approach the next level that water is near...]]]="),
	// kDialogDream7
	DialogData("_}It is difficult to get to sleep. What visions are in store for you now? "
	           "You unwillingly fall asleep thinking about the city of fountains you dreamt of three long days ago... ~",
	           kSpriteNone, kDialogDream1P2XW),
	// kDialogDream1P2XW
	DialogData("[You are inside a room, at a meeting between city officials and wizards. The officials want water access. "
	           "They are planning a seige. The wizards are arguing over a weapon they have created. ]]~",
	           kSpriteNone, kDialogDream1P2YW),
	// kDialogDream1P2YW
	DialogData("There is some problem with it. [The dream changes.]]][You see a wall of fire. "
	           "Now, in the flames, you see men attacking dragons. There is a flash. All are dead. You see another attack. "
	           "Defending himself, a dragon ~", kSpriteNone, kDialogdreamXXY),
	// kDialogdreamXXY
	DialogData("incinerates the army, but then another flash kills him instantly. "
	           "Armies block the exits of the dungeons, trapping the dragons inside. One escapes...]]]]]="),
	// kDialogNotHere3
	DialogData("This is to be thrown, but&not here.@"),
	// kDialogNotHere2
	DialogData("Not here.@"),
	// kDialogDownVortexString
	DialogData("_}You hear a voice... Could you be dreaming?[You remember the raging current of the vortex "
	           "pulling you toward a hole in the floor.[But now it is quiet.]] Time has passed... "
	           "You sense that someone or something is nearby.]]]="),
	// kDialogDunricString7
	DialogData("_}As you approach, the man lifts his head. He seems to know you.]][(I am Dunric,+ he falters, "
	           "(I sent my servant to warn you. Mordamir isn+t a prisoner...~", kSpriteNone, kDialogDunricString8),
	// kDialogDunricString8
	DialogData("[He kidnapped my daughter... He is manipulating... you... If I had my ring I could... but... my servant...+]]]="),
	// kDialogGiveDunricRing
	DialogData("Give Dunric his ring?%"),
	// kDialogDunricTransaction
	DialogData("_}Dunric pauses, then lowers his head. Three spells appear in front of you: "
	           "Body Statue, Magnetic hands, and Sonic protection. Dunric doesn+t raise his head again.]]]="),
	// kDialogUlindorString7
	DialogData("_}You found Dunric, did you? What did he tell you? He told you about Mordamir, didn+t he? "
	           "Then I+ll have to kill you.]]]="),
	// kDialogNurseText
	DialogData("}_You wake up remembering the kind touch of the goblin who revived you with water from the Fountain. "
	           "Or was she just a dream?]]]="),
	// kDialogAntiString
	DialogData("#  sonic@", kSpriteIconScroll),
	// kDialogBlinkDescription
	DialogData("#$ blinks@", kSpriteIconScroll),
	// kDialogBlinkString
	DialogData("You find a blink spell, good&for multiple uses.&@"),
	// kDialogTractorString
	DialogData("#magnetic@", kSpriteIconScroll),
	// kDialogBronzeString
	DialogData("#$ statue@", kSpriteIconScroll),
	// kDialogImmunityDescription
	DialogData("#fire prot.@", kSpriteIconScroll),
	// kDialogImmunityString
	DialogData("You find spell of fire&protection, good for three&seconds. @"),
	// kDialogAmuletDescription
	DialogData("You find a shiny, reflective&amulet. There are runes on&one side. @"),
	// kDialogAmuletString
	DialogData("# amulet@", kSpriteIconAmulet),
	// kDialogHoldItUp
	DialogData("Hold it up to the light here?%"),
	// kDialogReadRunes
	DialogData("Read the runes here?%"),
	// kDialogMordamirString1
	DialogData("_}(Fool! Read the words! I+ve waited a thousand years for this. Read the words!]]]"
	           "[Fine, then I+ll just take back my amulet. I have other students who will come. Prepare to die.+]]]="),
	// kDialogMordamirString2
	DialogData("_}You have no more defenses, my student. [What a pity I wasted so much time on you. "
	           "You don+t think you made it here on your own, do you? Look at me. Do I remind you of a merchant, perhaps? ~",
	           kSpriteNone, kDialogMordamir3D),
	// kDialogMordamir3D
	DialogData("Who do you think left you those chests?~", kSpriteNone, kDialogMordamir3),
	// kDialogMordamir3
	DialogData("[Do you even know why I summoned you? One thousand years ago, I created this amulet to kill the dragons "
	           "that governed the Fountain of Youth. But this one escaped. He came back and destroyed my city. ~",
	           kSpriteNone, kDialogMordamir4),
	// kDialogMordamir4
	DialogData("I was the sole survivor. Now I have returned to reclaim the fountain that gave me a thousand years of life."
	           "[You were to kill the dragon for me. You see, the power the amulet takes to kill a dragon ~",
	           kSpriteNone, kDialogMordamir5),
	// kDialogMordamir5
	DialogData("will also kill the one using it. So I can+t attack the dragon myself. "
	           "But as long as I have this amulet, the dragon won+t attack me.]]]="),
	// kDialogGoodbye
	DialogData("Now you will die.]]]]="),
	// kDialogEndText
	DialogData("}_The journey out of the dungeons takes two days, but with Ana by your side, time seems unimportant. "
	           "The water invigorates you with new youth, and you discover a new spring to your walk.~",
	           kSpriteNone, kDialogEtXX),
	// kDialogEtXX
	DialogData(" As you travel, your thoughts return to Mordamir and the dragon. "
	           "They were alike, in a way, each the only~", kSpriteNone, kDialogEt2),
	// kDialogEt2
	DialogData(" survivor of a civilization destroyed by the other more than a thousand years ago. "
	           "They were an equal match also, and it seems strange that you would tilt the balance of a conflict forged so long ago...]]]]="),
	// kDialogEndText2
	DialogData("}_The journey out of the dungeons takes two days.  As you travel, your thoughts return to Mordamir and the dragon. "
	           "They were alike, in a way, each the only~", kSpriteNone, kDialogEt2P),
	// kDialogEt2P
	DialogData(" survivor of a civilization destroyed by the other more than a thousand years ago. They were an equal match also, "
	           "and it seems strange that you would tilt the balance of a conflict forged so long ago...]]]]="),

#if 0
	// Definitions that are stored in strings as well but are not dialog text
	<DIRTSPOTS1>,<1>
	<level1Ladders>,<2,0>
	<ROOM5TRAPS>,<0,80H,0,0,0,0,0,5>
	<ROOM8TRAPS>,<0,80H,0,0,0,0,0,3>
	<ROOM7TRAPS>,<0,80H,15,5,3,0,0,0>
	<DIRTSPOTS2>,<1>
	<level12Ladders>,<4,0>
	<GEMSPOTS>,<roomc,12,3,0>
	<level3spikes>,<3>
	<goblinKeyGoal>,<r2_d,0a8H,64H>
	<level3Ladders>,<12,-1>
	<turretsL2Rd>,<2,256-10>
	<turretsL2Rc>,<2,256-10>
	<wallsL2R0>,<1,256-64,0,2,1,0,1,0>
	<wallsL2R5>,<1,256-64,0,1,1,1,2,0>
	<wallsL2R9>,<1,256-64,0,0,0,0,1,0>
	<level4Ladders>,<10,0>
	<turretsL2R5>,<16,0>
	<turretsL2R0>,<17,0>
	<wallsL2Rf>,<1,256-32,0,1,0,0,0,0>
	<level5spikes>,<10>
	<shrinkholegoal>,<r5_2>
	<level5Ladders>,<8,2>
	<level6Ladders>,<8,-1>
	<bubbles>,<23>
	<level7Ladders>,<6,-1>
	<dragonTRAPS>,<0,80H,0,0,0,0,0,1>
	<level8Ladders>,<2,-1>
#endif
};

const Common::Point Dialog::_cursorOrigin(40, 24);
// TODO:
// button pos relative to viewport. Look close at source what's going on here..
const Common::Point Dialog::_buttonNo(40 - 32, 100 - 12);
const Common::Point Dialog::_buttonYes(214 - 32, 100 - 12);
const int Dialog::_iconWidth = 64;
const int Dialog::_iconHeight = 48;
const int Dialog::_maxCharWidth = 16;
const int Dialog::_rowHeight = 16;
const int Dialog::_rowWidthLimit = 288; // 256 px viewport + 32 px border
const int Dialog::_maxRows = 5;
const int Dialog::_charGaugeOff = 1;
const int Dialog::_charGaugeOn = 2;
const int Dialog::_charCopyright = 24;
const int Dialog::_charTrademark = 25;
const int Dialog::_charBlank = 26;
const int Dialog::_scrollingDelay = 100;
const int Dialog::_delayInMs = (1 / 72.8) * 1000;

Dialog::Dialog(Renderer *screen)
    : _screen(screen) {
	reset();
}

void Dialog::load(DialogId id) {
	reset();
	_text = dialog[id]._text;
	_timeSinceLastUpdate.start();
}

void Dialog::reset() {
	_cursorPos = _cursorOrigin;
	_text = nullptr;
	_timeSinceLastUpdate.stop();
	_scrollingMode = false;
}

int Dialog::getDelay() const {
	return _delay;
}

void Dialog::nextChar() {
	assert(*_text != '\0');
	++_text;
	_delay = 0;
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
	case kDialogTokenEndOfString:
		_screen->clear();
		_cursorPos = _cursorOrigin;
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

	case kDialogTokenEndOfStringOk:
	case kDialogTokenEndOfStringYesNo:
	case kDialogTokenLoadNextString:
		return (DialogToken)*_text;

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

void Dialog::newline() {
	_cursorPos.x = _cursorOrigin.x;
	_cursorPos.y += 16;
}

}
