.set LOCALID_WALLACE, 1
.set LOCALID_RIVAL, 2
.set LOCALID_BIRCH, 3
.set LOCALID_STEVEN, 4

EverGrandeCity_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	end

EverGrandeCity_ChampionsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
	releaseall
	end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Wallace::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeechCont, MSGBOX_DEFAULT
	closemessage
	goto EverGrandeCity_ChampionsRoom_EventScript_Steven_Joins
EverGrandeCity_ChampionsRoom_EventScript_WallaceBattle::
	trainerbattle_no_intro TRAINER_WALLACE, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_Defeated
	end

EverGrandeCity_ChampionsRoom_EventScript_Steven_Joins::
	delay 40
	msgbox EverGrandeCity_ChampionsRoom_Text_HoldOn, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitse
	playse SE_DOOR
	addobject LOCALID_STEVEN
	applymovement LOCALID_STEVEN, EverGrandeCity_ChampionsRoom_Movement_StevenApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceRight
	waitmovement 0
	delay 10
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenJoins, MSGBOX_DEFAULT
EverGrandeCity_ChampionsRoom_EventScript_CheckPkmnCount::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, EverGrandeCity_ChampionsRoom_EventScript_NotEnoughMonsForDoubleRematchBattleMightGiveRope
	goto EverGrandeCity_ChampionsRoom_EventScript_WallaceBattle

EverGrandeCity_ChampionsRoom_EventScript_TalkToSteven::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_ne VAR_RESULT, DIR_EAST, end
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, EverGrandeCity_ChampionsRoom_EventScript_NotEnoughMonsForDoubleRematchBattleMightGiveRope
	msgbox EverGrandeCity_ChampionsRoom_Text_StevenJoins, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_WallaceBattle

EverGrandeCity_ChampionsRoom_EventScript_NotEnoughMonsForDoubleRematchBattleMightGiveRope::
	call EverGrandeCity_HallOfFame_EventScript_ResetEliteFour
	checkitem ITEM_ESCAPE_ROPE
	goto_if_eq VAR_RESULT, TRUE, EverGrandeCity_ChampionsRoom_EventScript_NotEnoughMonsForDoubleRematchBattle
	msgbox EverGrandeCity_ChampionsRoom_Text_NotEnoughPokemonGiveRope, MSGBOX_DEFAULT
	giveitem ITEM_ESCAPE_ROPE
	closemessage
	end

EverGrandeCity_ChampionsRoom_EventScript_NotEnoughMonsForDoubleRematchBattle::
	msgbox EverGrandeCity_ChampionsRoom_Text_NotEnoughPokemon, MSGBOX_DEFAULT
	closemessage
	end

EverGrandeCity_ChampionsRoom_EventScript_EnoughPkmnInParty::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_ne VAR_RESULT, DIR_NORTH, end
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, EverGrandeCity_ChampionsRoom_EventScript_NotEnoughMonsWallace
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeechCont, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_WallaceBattle

EverGrandeCity_ChampionsRoom_EventScript_NotEnoughMonsWallace::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_lt VAR_RESULT, 2, EverGrandeCity_ChampionsRoom_EventScript_NotEnoughMonsForDoubleRematchBattle
	msgbox EverGrandeCity_ChampionsRoom_Text_ReviveOne, MSGBOX_DEFAULT
	closemessage
	end

EverGrandeCity_ChampionsRoom_EventScript_Defeated::
	setobjectxy OBJ_EVENT_ID_PLAYER, 6, 6
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	waitmovement 0
	applymovement LOCALID_STEVEN, EverGrandeCity_ChampionsRoom_Movement_StevenExitStart
	waitmovement 0
	applymovement LOCALID_STEVEN, EverGrandeCity_ChampionsRoom_Movement_StevenExitCont
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_STEVEN, EverGrandeCity_ChampionsRoom_Movement_StevenExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart:
	walk_left
	walk_in_place_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_StevenApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_in_place_left
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_StevenExitStart:
	walk_up
	walk_left
	step_end

EverGrandeCity_ChampionsRoom_Movement_StevenExitCont:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_StevenExit:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Text_IntroSpeech:
	.string "WALLACE: Welcome, {PLAYER}{KUN}.\p"
	.string "That incident in SOOTOPOLIS CITY…\n"
	.string "That was superb work, putting an end\l"
	.string "to that crisis all by yourself.\p"
	.string "Oops!\p"
	.string "It wouldn't be fair to say that you\n"
	.string "alone ended the crisis.\p"
	.string "You overcame that difficult situation\n"
	.string "by working as one with your POKéMON.\p"
	.string "We TRAINERS raise POKéMON by giving\n"
	.string "them items and by teaching them new\l"
	.string "techniques for battle.\p"
	.string "But we ourselves also learn many\n"
	.string "things from POKéMON.\p"
	.string "And this is where your achievements\n"
	.string "are put to the test against what\l"
	.string "others like you have achieved.$"
EverGrandeCity_ChampionsRoom_Text_IntroSpeechCont:
	.string "Now!\p"
	.string "Who can most elegantly dance with\n"
	.string "their POKéMON in HOENN?\p"
	.string "Show me right here and now!$"

EverGrandeCity_ChampionsRoom_Text_HoldOn:
	.string "HOLD ON!$"

EverGrandeCity_ChampionsRoom_Text_StevenJoins:
	.string "STEVEN: Show us right here\n"
	.string "and now!$"

EverGrandeCity_ChampionsRoom_Text_NotEnoughPokemon:
	.string "What? You don't have enough.\n"
	.string "POKéMON for a double battle!\p"
	.string "That was irresponsible of you.\n"
	.string "Use your Escape Rope to leave.\p"
	.string "Enjoy going through all of the\n"
	.string "ELITE FOUR again...$"

EverGrandeCity_ChampionsRoom_Text_NotEnoughPokemonGiveRope:
	.string "What? You don't have enough.\n"
	.string "POKéMON for a double battle!\p"
	.string "Here's an escape rope.\n"
	.string "Use it to leave.\p"
	.string "Enjoy going through all of the\n"
	.string "ELITE FOUR again...$"

EverGrandeCity_ChampionsRoom_Text_ReviveOne:
	.string "It looks like you may have enough\n"
	.string "POKéMON if you can revive one.$"

EverGrandeCity_ChampionsRoom_Text_Defeat:
	.string "I, the CHAMPION, fall in defeat...\p"
	.string "Kudos to you, {PLAYER}{KUN}!\p"
	.string "You are a truly noble POKéMON\n"
	.string "TRAINER!$"

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech:
	.string "STEVEN: Congratulations!\p"
	.string "The feelings you have for your\n"
	.string "POKéMON...\p"
	.string "And the POKéMON that responded to\n"
	.string "those feelings with all their might...\p"
	.string "They came together as one, and created\n"
	.string "an even greater power.\p"
	.string "And thus, you were able to grasp\n"
	.string "victory today!\p"
	.string "You are rightfully the HOENN region's\n"
	.string "new...$"

EverGrandeCity_ChampionsRoom_Text_MayAdvice:
	.string "MAY: {PLAYER}{KUN}!\p"
	.string "Here's some advice before you challenge\n"
	.string "the CHAMPION…$"

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver:
	.string "MAY: Huh?\n"
	.string "What, what, what?\p"
	.string "{PLAYER}{KUN}…\n"
	.string "Could it be that…\l"
	.string "It's already over?$"

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice:
	.string "BRENDAN: {PLAYER}!\p"
	.string "How would you like some advice before\n"
	.string "you challenge the CHAMPION?…$"

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon:
	.string "BRENDAN: {PLAYER}…\p"
	.string "Are you trying to tell me…\n"
	.string "You've beaten the CHAMPION?$"

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex:
	.string "PROF. BIRCH: See?\n"
	.string "What did I tell you, {RIVAL}?\p"
	.string "Didn't I tell you that you don't need\n"
	.string "to worry about {PLAYER}{KUN}?\p"
	.string "… … … … … … … …\n"
	.string "{PLAYER}{KUN}, you've finally done it.\p"
	.string "When I heard that you defeated your\n"
	.string "own father at the PETALBURG GYM,\l"
	.string "I thought perhaps you had a chance…\p"
	.string "But to think you've actually become\n"
	.string "the CHAMPION!\p"
	.string "Ah, yes!\p"
	.string "What became of your POKéDEX?\n"
	.string "Here, let me see.$"

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations:
	.string "PROF. BIRCH: Anyways,\n"
	.string "congratulations!\p"
	.string "Now, go proudly into the final room!$"

EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe:
	.string "STEVEN: {PLAYER}{KUN}...\p"
	.string "No, the new CHAMPION!\p"
	.string "Come with me.$"

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside:
	.string "STEVEN: I'm sorry, but...\p"
	.string "From here on, only those TRAINERS who\n"
	.string "have become CHAMPIONS may enter.\p"
	.string "You'll have to wait outside with the\n"
	.string "PROFESSOR.$"

EverGrandeCity_ChampionsRoom_Text_MayCongratulations:
	.string "MAY: Groan…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "I'm just joking! That's okay!\n"
	.string "That's the rule!\p"
	.string "{PLAYER}{KUN}!\n"
	.string "Honestly, congratulations!$"

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations:
	.string "BRENDAN: Whaaaat?! … … … … …\n"
	.string "… … … … … … … …\p"
	.string "It can't be helped if that's the rule.\p"
	.string "{PLAYER}, way to go!\n"
	.string "Congratulations!$"

