.set LOCALID_TWIN, 1
.set LOCALID_JAIME, 2
.set LOCALID_MOM, 4
.set LOCALID_RIVAL, 7
.set LOCALID_BIRCH, 8

LittlerootTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_OnWarp
	.byte 0

	@ State descriptions for VAR_LITTLEROOT_TOWN_STATE
	@ 1: Met Rival
	@ 2: Saving Birch
	@ 3: Received Pokedex
	@ 4: Received Running Shoes

	@ State descriptions for VAR_LITTLEROOT_INTRO_STATE
	@ 1: In truck male
	@ 2: In truck female
	@ 3: Entered house
	@ 4: Told to go set clock
	@ 5: Entered 2F to set clock
	@ 6: Set clock
	@ 7: Told to go meet rival

	@ State descriptions for VAR_LITTLEROOT_HOUSES_STATE_MAY
	@                    and VAR_LITTLEROOT_HOUSES_STATE_BRENDAN
	@ 1: On Truck (and is corresponding gender)
	@ 2: Met Rival's Mom (and is corresponding gender)
	@ 3: Entered Hall of Fame
	@ 4: Completed Lati TV / SS Ticket event
	@ 5: Exited house after above event

	@ State descriptions for VAR_LITTLEROOT_RIVAL_STATE
	@ 1: Never occurs
	@ 2: Entered Rival's bedroom
	@ 3: Met Rival
	@ 4: Received Pokedex


LittlerootTown_OnTransition:
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	call Common_EventScript_SetupRivalGfxId
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_MoveMomToMaysDoor
	call_if_unset FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_SetTwinPos
	call_if_eq VAR_LITTLEROOT_TOWN_STATE, 3, LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_MAY, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_OLDALE_RIVAL_STATE, 1, LittlerootTown_EventScript_MoveRivalFromOldale
	call_if_eq VAR_LITTLEROOT_RIVAL_STATE, 3, LittlerootTown_EventScript_SetRivalLeftForRoute103
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_HideMapNamePopup
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_EventScript_LeftLabAfterDexUpgrade
	end

LittlerootTown_EventScript_LeftLabAfterDexUpgrade::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	return

LittlerootTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_EventScript_SetRivalLeftForRoute103::
	setflag FLAG_RIVAL_LEFT_FOR_ROUTE103
	return

LittlerootTown_EventScript_MoveRivalFromOldale::
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	return

LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent::
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 5
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 5
	return

LittlerootTown_EventScript_MoveMomToMaysDoor::
	setobjectxyperm LOCALID_MOM, 14, 8
	return

LittlerootTown_EventScript_SetTwinPos::
	goto_if_eq VAR_LITTLEROOT_TOWN_STATE, 0, LittlerootTown_EventScript_SetTwinGuardingRoutePos
	setobjectxyperm LOCALID_TWIN, 10, 1
	setobjectmovementtype LOCALID_TWIN, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_EventScript_SetTwinGuardingRoutePos::
	setobjectxyperm LOCALID_TWIN, 7, 2
	setobjectmovementtype LOCALID_TWIN, MOVEMENT_TYPE_FACE_DOWN
	return

LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_DOWN
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetMomInFrontOfDoorMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetMomInFrontOfDoorFemale
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorMale::
	setobjectxyperm LOCALID_MOM, 5, 9
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorFemale::
	setobjectxyperm LOCALID_MOM, 14, 9
	return

LittlerootTown_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 1, LittlerootTown_EventScript_StepOffTruckMale
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_StepOffTruckFemale
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_BeginDexUpgradeScene
	.2byte 0

LittlerootTown_EventScript_StepOffTruckMale::
	lockall
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F, 8, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_StepOffTruckFemale::
	lockall
	setvar VAR_0x8004, 14
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F, 2, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_GoInsideWithMom::
	delay 15
	playse SE_LEDGE
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerStepOffTruck
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	addobject LOCALID_MOM
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitHouse
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	delay 10
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerAtTruck
	waitmovement 0
	msgbox LittlerootTown_Text_OurNewHomeLetsGoInside, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachDoor
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerApproachDoor
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomEnterHouse
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerEnterHouse
	waitmovement 0
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_Movement_MomExitHouse:
	walk_down
	step_end

LittlerootTown_Movement_MomApproachPlayerAtTruck:
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_Movement_MomApproachDoor:
	delay_16
	delay_8
	walk_up
	step_end

LittlerootTown_Movement_MomEnterHouse:
	walk_up
	set_invisible
	step_end

LittlerootTown_Movement_PlayerApproachDoor:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_PlayerEnterHouse:
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_PlayerStepOffTruck:
	jump_right
	delay_16
	delay_16
	delay_16
	step_end

LittlerootTown_EventScript_BeginDexUpgradeScene::
	lockall
	playse SE_PIN
	applymovement LOCALID_BIRCH, Common_Movement_ExclamationMark
	waitmovement 0
	delay 80
	msgbox LittlerootTown_Text_BirchSomethingToShowYouAtLab, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
	delay 20
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
	waitstate
	releaseall
	end

LittlerootTown_OnWarp:
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade
	.2byte 0

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade::
	addobject LOCALID_BIRCH
	addobject LOCALID_RIVAL
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale
	goto LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale
	end

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale::
	setobjectxy LOCALID_RIVAL, 6, 10
	setobjectxy LOCALID_BIRCH, 5, 10
	end

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale::
	setobjectxy LOCALID_RIVAL, 13, 10
	setobjectxy LOCALID_BIRCH, 14, 10
	end

LittlerootTown_EventScript_FatMan::
	goto_if_set FLAG_IS_CHAMPION, LittlerootTown_EventScript_FatMan_EliteFourWon
	callnative CanGetNatureMintFromJaime
	goto_if_eq VAR_RESULT, TRUE, LittlerootTown_EventScript_FatManGiveMints
	msgbox LittlerootTown_Text_HeyJaime, MSGBOX_NPC
	end

LittlerootTown_EventScript_FatManGiveMints::
	lock
	applymovement LOCALID_JAIME, Common_Movement_FacePlayer
	goto_if_set FLAG_GOT_MINT_FROM_JAIME, LittlerootTown_EventScript_FatManGiveMintsNotFirstTime
	waitmovement 0
	setflag FLAG_GOT_MINT_FROM_JAIME
	playse SE_PIN
	applymovement LOCALID_JAIME, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox LittlerootTown_Text_JaimeFirstMints, MSGBOX_DEFAULT
	closemessage
LittlerootTown_EventScript_FatManGiveMintsNotFirstTime::
	msgbox LittlerootTown_Text_JaimeHasMints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LittlerootTown_EventScript_MintEnd
	message LittlerootTown_Text_JaimeWhichMint
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_NATURE_MINTS
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, LittlerootTown_EventScript_GiveAdamant
	case 1, LittlerootTown_EventScript_GiveBold
	case 2, LittlerootTown_EventScript_GiveBrave
	case 3, LittlerootTown_EventScript_GiveCalm
	case 4, LittlerootTown_EventScript_GiveCareful
	case 5, LittlerootTown_EventScript_GiveGentle
	case 6, LittlerootTown_EventScript_GiveHasty
	case 7, LittlerootTown_EventScript_GiveImpish
	case 8, LittlerootTown_EventScript_GiveJolly
	case 9, LittlerootTown_EventScript_GiveLax
	case 10, LittlerootTown_EventScript_GiveLonely
	case 11, LittlerootTown_EventScript_GiveMild
	case 12, LittlerootTown_EventScript_GiveModest
	case 13, LittlerootTown_EventScript_GiveNaive
	case 14, LittlerootTown_EventScript_GiveNaughty
	case 15, LittlerootTown_EventScript_GiveQuiet
	case 16, LittlerootTown_EventScript_GiveRash
	case 17, LittlerootTown_EventScript_GiveRelaxed
	case 18, LittlerootTown_EventScript_GiveSassy
	case 19, LittlerootTown_EventScript_GiveSerious
	case 20, LittlerootTown_EventScript_GiveTimid
	case 21, LittlerootTown_EventScript_MintEnd
	case MULTI_B_PRESSED, LittlerootTown_EventScript_MintEnd
	end

LittlerootTown_EventScript_GiveAdamant::
	giveitem ITEM_ADAMANT_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveBold::
	giveitem ITEM_BOLD_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveBrave::
	giveitem ITEM_BRAVE_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveCalm::
	giveitem ITEM_CALM_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveCareful::
	giveitem ITEM_CAREFUL_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveGentle::
	giveitem ITEM_GENTLE_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveHasty::
	giveitem ITEM_HASTY_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveImpish::
	giveitem ITEM_IMPISH_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveJolly::
	giveitem ITEM_JOLLY_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveLax::
	giveitem ITEM_LAX_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveLonely::
	giveitem ITEM_LONELY_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveMild::
	giveitem ITEM_MILD_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveModest::
	giveitem ITEM_MODEST_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveNaive::
	giveitem ITEM_NAIVE_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveNaughty::
	giveitem ITEM_NAUGHTY_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveQuiet::
	giveitem ITEM_QUIET_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveRash::
	giveitem ITEM_RASH_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveRelaxed::
	giveitem ITEM_RELAXED_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveSassy::
	giveitem ITEM_SASSY_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveSerious::
	giveitem ITEM_SERIOUS_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_GiveTimid::
	giveitem ITEM_TIMID_MINT
	goto LittlerootTown_EventScript_MintGiveEnd
LittlerootTown_EventScript_MintGiveEnd::
	addvar VAR_JAIME_MINTS_GIVEN, 1
LittlerootTown_EventScript_MintEnd::
	callnative CanGetNatureMintFromJaime
	goto_if_eq VAR_RESULT, TRUE, LittlerootTown_EventScript_FatManGiveMintsNotFirstTime
	msgbox LittlerootTown_Text_JaimeSold, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_FatMan_EliteFourWon::
	lock
	applymovement LOCALID_JAIME, Common_Movement_FacePlayer
	goto_if_set FLAG_GOT_MINT_FROM_JAIME, LittlerootTown_EventScript_FatMan_EliteFourNotFirstTime
	waitmovement 0
	setflag FLAG_GOT_MINT_FROM_JAIME
	playse SE_PIN
	applymovement LOCALID_JAIME, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox LittlerootTown_Text_JaimeSellingFirstMints, MSGBOX_DEFAULT
	closemessage
LittlerootTown_EventScript_FatMan_EliteFourNotFirstTime:
	msgbox LittlerootTown_Text_JaimeSelling, MSGBOX_DEFAULT
	setflag FLAG_TEMP_MEAN_ZIGZAGOON
	pokemart LittlerootTown_EventScript_FatMan_Vitamins
	clearflag FLAG_TEMP_MEAN_ZIGZAGOON
	msgbox LittlerootTown_Text_JaimeSold, MSGBOX_DEFAULT
	release
	end

	.align 2
LittlerootTown_EventScript_FatMan_Vitamins:
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	.2byte ITEM_RARE_CANDY
	.2byte ITEM_ADAMANT_MINT
	.2byte ITEM_BOLD_MINT
	.2byte ITEM_BRAVE_MINT
	.2byte ITEM_CALM_MINT
	.2byte ITEM_CAREFUL_MINT
	.2byte ITEM_GENTLE_MINT
	.2byte ITEM_HASTY_MINT
	.2byte ITEM_IMPISH_MINT
	.2byte ITEM_JOLLY_MINT
	.2byte ITEM_LAX_MINT
	.2byte ITEM_LONELY_MINT
	.2byte ITEM_MILD_MINT
	.2byte ITEM_MODEST_MINT
	.2byte ITEM_NAIVE_MINT
	.2byte ITEM_NAUGHTY_MINT
	.2byte ITEM_QUIET_MINT
	.2byte ITEM_RASH_MINT
	.2byte ITEM_RELAXED_MINT
	.2byte ITEM_SASSY_MINT
	.2byte ITEM_SERIOUS_MINT
	.2byte ITEM_TIMID_MINT
	.2byte ITEM_BOTTLE_CAP_HP
	.2byte ITEM_BOTTLE_CAP_ATK
	.2byte ITEM_BOTTLE_CAP_DEF
	.2byte ITEM_BOTTLE_CAP_SPEED
	.2byte ITEM_BOTTLE_CAP_SPATK
	.2byte ITEM_BOTTLE_CAP_SPDEF
	.2byte ITEM_GOLD_BOTTLE_CAP
	.2byte ITEM_RUSTY_BOTTLE_CAP
	.2byte ITEM_NONE
	release
	end

LittlerootTown_EventScript_Boy::
	msgbox LittlerootTown_Text_BirchSpendsDaysInLab, MSGBOX_NPC
	end

LittlerootTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, LittlerootTown_EventScript_GoodLuck
	goto_if_set FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_YouSavedBirch
	goto_if_ne VAR_LITTLEROOT_TOWN_STATE, 0, LittlerootTown_EventScript_GoSaveBirch
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_GoSaveBirch::
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	release
	end

LittlerootTown_EventScript_YouSavedBirch::
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_YouSavedBirch, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_GoodLuck::
	msgbox LittlerootTown_Text_GoodLuckCatchingPokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_NeedPokemonTriggerLeft::
	lockall
	applymovement LOCALID_TWIN, LittlerootTown_Movement_TwinApproachPlayerLeft
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_TWIN, LittlerootTown_Movement_TwinReturnLeft
	waitmovement 0
	releaseall
	end

LittlerootTown_EventScript_DangerousWithoutPokemon::
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TWIN, LittlerootTown_Movement_TwinPushPlayerFromRoute
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PushPlayerBackFromRoute
	waitmovement 0
	msgbox LittlerootTown_Text_DangerousIfYouDontHavePokemon, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_Movement_TwinApproachPlayerLeft:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	face_down
	step_end

LittlerootTown_Movement_TwinPushPlayerFromRoute:
	walk_down
	step_end

LittlerootTown_Movement_TwinReturnLeft:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_in_place_faster_down
	step_end

LittlerootTown_Movement_PushPlayerBackFromRoute:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

LittlerootTown_EventScript_NeedPokemonTriggerRight::
	lockall
	applymovement LOCALID_TWIN, LittlerootTown_Movement_TwinApproachPlayerRight
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_TWIN, LittlerootTown_Movement_TwinReturnRight
	waitmovement 0
	releaseall
	end

LittlerootTown_Movement_TwinApproachPlayerRight:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_right
	face_down
	step_end

LittlerootTown_Movement_TwinReturnRight:
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

LittlerootTown_EventScript_GoSaveBirchTrigger::
	lockall
	applymovement LOCALID_TWIN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	releaseall
	end

LittlerootTown_EventScript_TownSign::
	msgbox LittlerootTown_Text_TownSign, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BirchsLabSign::
	msgbox LittlerootTown_Text_ProfBirchsLab, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BrendansHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_PlayersHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_BirchsHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_PlayersHouseSignMale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_BirchsHouseSignFemale::
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_MaysHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_BirchsHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_PlayersHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_Basketball::
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_WEST, LittlerootTown_EventScript_BackOfHoop
	goto LittlerootTown_EventScript_BasketballShot
LittlerootTown_EventScript_BasketballEnd::
	end

LittlerootTown_EventScript_BasketballShot:
	msgbox LittlerootTown_Text_BasketballShotSignAttempt, MSGBOX_DEFAULT
	delay 10
	closemessage
	random 10
	compare VAR_RESULT, 3
	goto_if_lt LittlerootTown_EventScript_BasketballShotSignMade
    playse SE_FAILURE
	msgbox LittlerootTown_Text_BasketballShotSignMiss, MSGBOX_DEFAULT
	waitse
	clearflag FLAG_BASKETBALL_SHOT_MADE
LittlerootTown_EventScript_BasketballShotEnd::
	closemessage
	return

LittlerootTown_EventScript_BasketballShotAttempt:
	msgbox LittlerootTown_Text_BasketballShotSignAttempt, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_BasketballShotSignMade:
	playse SE_SUCCESS
	msgbox LittlerootTown_Text_BasketballShotSignMade, MSGBOX_DEFAULT
	waitse
	setflag FLAG_BASKETBALL_SHOT_MADE
	goto LittlerootTown_EventScript_BasketballShotEnd

LittlerootTown_EventScript_BackOfHoop:
	msgbox LittlerootTown_Text_BackOfHoop, MSGBOX_DEFAULT
	closemessage
	goto LittlerootTown_EventScript_BasketballEnd

LittlerootTown_EventScript_BirchsHouseSignMale::
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_PlayersHouseSignFemale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_GivePokeVialTrigger0::
	lockall
	setvar VAR_0x8008, 0
	setobjectxy LOCALID_MOM, 10, 9
	goto LittlerootTown_EventScript_GivePokeVialTrigger
	end

LittlerootTown_EventScript_GivePokeVialTrigger1::
	lockall
	setvar VAR_0x8008, 1
	setobjectxy LOCALID_MOM, 11, 9
	goto LittlerootTown_EventScript_GivePokeVialTrigger
	end

LittlerootTown_EventScript_GivePokeVialTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_EventScript_GivePokeVialTrigger
	end

LittlerootTown_EventScript_GivePokeVialTrigger3::
	lockall
	setvar VAR_0x8008, 3
	goto LittlerootTown_EventScript_GivePokeVialTrigger
	end

LittlerootTown_EventScript_GivePokeVialTrigger4::
	lockall
	setvar VAR_0x8008, 4
	goto LittlerootTown_EventScript_GivePokeVialTrigger
	end

LittlerootTown_EventScript_GivePokeVialTrigger5::
	lockall
	setvar VAR_0x8008, 5
	goto LittlerootTown_EventScript_GivePokeVialTrigger
	end

LittlerootTown_EventScript_GivePokeVialTrigger::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomNoticePlayerMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomNoticePlayerFemale
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetHomeDoorCoordsMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetHomeDoorCoordsFemale
	msgbox LittlerootTown_Text_WaitPlayer, MSGBOX_DEFAULT
	closemessage
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomApproachPlayerMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomApproachPlayerFemale
	call LittlerootTown_EventScript_GivePokeVial
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomReturnHomeMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomReturnHomeFemale
	goto LittlerootTown_EventScript_SetReceivedPokeVial
	end

LittlerootTown_EventScript_SetHomeDoorCoordsMale::
	setvar VAR_0x8009, 5
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_SetHomeDoorCoordsFemale::
	setvar VAR_0x8009, 14
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_MomNoticePlayerMale::
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LittlerootTown_EventScript_MomNoticePlayerFemale::
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomApproachPlayerMale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomApproachPlayerMale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomApproachPlayerMale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomApproachPlayerMale5
	return

LittlerootTown_EventScript_MomApproachPlayerFemale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomApproachPlayerFemale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomApproachPlayerFemale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomApproachPlayerFemale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomApproachPlayerFemale5
	return

LittlerootTown_EventScript_MomApproachPlayer0::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayer0
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayer1::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayer1
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale2::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerMale2
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale3::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerMale3
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale4::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerMale4
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale5::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerMale5
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale2::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerFemale2
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale3::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerFemale3
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale4::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerFemale4
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale5::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerFemale5
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHomeMale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomReturnHome0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomReturnHome1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomReturnHomeMale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomReturnHomeMale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomReturnHomeMale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomReturnHomeMale5
	return

LittlerootTown_EventScript_MomReturnHomeFemale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomReturnHome0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomReturnHome1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomReturnHomeFemale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomReturnHomeFemale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomReturnHomeFemale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomReturnHomeFemale5
	return

LittlerootTown_EventScript_MomReturnHome0::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHome0
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHome1::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHome1
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHomeMale2::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeMale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale3::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeMale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale4::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeMale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale5::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeMale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale2::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeFemale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale3::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeFemale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale4::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeFemale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale5::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeFemale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_Movement_MomApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_MomApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_MomApproachPlayerMale2:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale3:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale4:
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale5:
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale2:
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale3:
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale4:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale5:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomReturnHome0:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_Movement_MomReturnHome1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_Movement_MomReturnHomeMale2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale4:
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale5:
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale2:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale3:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale4:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale5:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomExitThroughDoor:
	walk_up
	step_end

LittlerootTown_EventScript_Mom::
	lock
	faceplayer
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetHomeDoorCoordsMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetHomeDoorCoordsFemale
	call LittlerootTown_EventScript_GivePokeVial
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	goto LittlerootTown_EventScript_SetReceivedPokeVial
	end

LittlerootTown_EventScript_SetReceivedPokeVial::
	removeobject LOCALID_MOM
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
	release
	end

LittlerootTown_EventScript_GivePokeVial::
	msgbox LittlerootTown_Text_UseThisVial, MSGBOX_DEFAULT
	giveitem ITEM_POKEVIAL	
	msgbox LittlerootTown_Text_ExplainPokeVial, MSGBOX_DEFAULT
	msgbox LittlerootTown_Text_ComeHomeIfAnythingHappens, MSGBOX_DEFAULT
	closemessage
	delay 30
	return

LittlerootTown_Text_OurNewHomeLetsGoInside:
	.string "MOM: {PLAYER}, we're here, honey!\p"
	.string "It must be tiring riding with our things\n"
	.string "in the moving truck.\p"
	.string "Well, this is SOUTHFIELD\p"
	.string "How do you like it?\n"
	.string "This is our new home!\p"
	.string "It has a quaint feel, but it seems to be\n"
	.string "an easy place to live, don't you think?\p"
	.string "And, you get your own room, {PLAYER}!\n"
	.string "Let's go inside.$"

LittlerootTown_Text_WaitPlayer:
	.string "MOM: Wait, {PLAYER}!\n"
	.string "Get over here before I break a femur!$"

LittlerootTown_Text_UseThisVial:
	.string "MOM: {PLAYER}! {PLAYER}! Did you\n"
	.string "introduce yourself to PROF. BIRCH?\p"
	.string "Oh! What an adorable POKéMON!\n"
	.string "You got it from PROF. BIRCH. How nice!\p"
	.string "You're your father's child, all right.\n"
	.string "You look good together with POKéMON!\p"
	.string "Here, honey! If you're going out on an\n"
	.string "adventure, take this vial.\p"
	.string "It'll save you lots of time!$"

LittlerootTown_Text_ExplainPokeVial:
	.string "MOM: {PLAYER}, this vial came with\n"
	.string "instructions.\p"
	.string "“You can heal your party using the\n"
	.string "PokéVial without needing to use a\l"
	.string "“POKéMON Center! But it will run out\l"
	.string "and need replenishing at a Center!”$"

LittlerootTown_Text_ComeHomeIfAnythingHappens:
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "To think that you have your very own\n"
	.string "POKéMON now…\l"
	.string "Your father will be overjoyed.\p"
	.string "…But please be careful.\n"
	.string "If anything happens, you can come home.\p"
	.string "Go on, go get them, honey!$"

LittlerootTown_Text_HeyJaime:
	.string "Hey.\n"
	.string "  - Jaime$"

LittlerootTown_Text_JaimeFirstMints:
	.string "Hey {PLAYER}, I see you have been\n"
	.string "getting badges.\p"
	.string "So you're committed to this trainer\n"
	.string "thing, huh?\p"
	.string "Tell you what, I am taking a break from \n"
	.string "selling shoes to sell NATURE MINTS.\p"
	.string "NATURE MINTS allow you to change the\n"
	.string "nature of a POKEMON from their\l"
	.string "original nature to the one in the\l"
	.string "MINT's name.$"

LittlerootTown_Text_JaimeHasMints:
	.string "I have {STR_VAR_1} that\n"
	.string "I can give away.\p"
	.string "Do you want one?$"

LittlerootTown_Text_JaimeWhichMint:
	.string "Which mint would\n"
	.string "you like?$"

LittlerootTown_Text_JaimeSellingFirstMints:
	.string "Hey {PLAYER}, I see you beat the\n"
	.string "ELITE FOUR. Nice.\p"
	.string "Have you heard of NATURE MINTS\n"
	.string "and CAPS?\p"
	.string "NATURE MINTS allow you to change the\n"
	.string "nature of a POKéMON from their\l"
	.string "original nature to the one in the\l"
	.string "MINT's name and CAPS allow you to\l"
	.string "max the IV of one of you POKéMON.$"


LittlerootTown_Text_JaimeSelling:
	.string "I'm taking a break from\n"
	.string "dealing shoes.\p"
	.string "I have some Vitamins I'm selling.\n"
	.string "You interested?\p"
	.string "I'll give you a discount\n"
	.string "since you're cool.$"

LittlerootTown_Text_JaimeSold:
	.string "Always a pleasure.$"

LittlerootTown_Text_BirchSpendsDaysInLab:
	.string "PROF. BIRCH spends days in his LAB\n"
	.string "studying, then he'll suddenly go out in\l"
	.string "the wild to do more research…\p"
	.string "When does PROF. BIRCH spend time\n"
	.string "at home?$"

LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut:
	.string "Um, um, um!\p"
	.string "If you go outside and go in the grass,\n"
	.string "wild POKéMON will jump out!$"

LittlerootTown_Text_DangerousIfYouDontHavePokemon:
	.string "It's dangerous if you don't have\n"
	.string "your own POKéMON.$"

LittlerootTown_Text_CanYouGoSeeWhatsHappening:
	.string "Um, hi!\p"
	.string "There are scary POKéMON outside!\n"
	.string "I can hear their cries!\p"
	.string "I want to go see what's going on,\n"
	.string "but I don't have any POKéMON…\p"
	.string "Can you go see what's happening\n"
	.string "for me?$"

LittlerootTown_Text_YouSavedBirch:
	.string "You saved PROF. BIRCH!\n"
	.string "I'm so glad!$"

LittlerootTown_Text_GoodLuckCatchingPokemon:
	.string "Are you going to catch POKéMON?\n"
	.string "Good luck!$"

LittlerootTown_Text_TownSign:
	.string "SOUTHFIELD\n"
	.string "“The center of it all.”$"

LittlerootTown_Text_ProfBirchsLab:
	.string "PROF. BIRCH'S POKéMON LAB$"

LittlerootTown_Text_PlayersHouse:
	.string "19790 Silver Spring$"

LittlerootTown_Text_ProfBirchsHouse:
	.string "PROF. BIRCH'S HOUSE$"

LittlerootTown_Text_BasketballSign:
	.string "This is your basketball hoop.$"

LittlerootTown_Text_BasketballShotSignAttempt:
	.string "Attempting LeBron-James-I-am-not shot.$"

LittlerootTown_Text_BasketballShotSignMiss:
	.string "Shot missed.$"

LittlerootTown_Text_BasketballShotSignMade:
	.string "Shot was made!$"

LittlerootTown_Text_BackOfHoop:
	.string "{PLAYER}, we both know you can't make\n"
	.string "a shot behind the hoop.$"

LittlerootTown_Text_BirchSomethingToShowYouAtLab:
	.string "PROF. BIRCH: Well, well, {PLAYER}{KUN}!\n"
	.string "That was good work out there!\p"
	.string "I knew there was something special\n"
	.string "about you when I first saw you,\l"
	.string "but I never expected this.\p"
	.string "Oh, yes. Do you still have the POKéDEX\n"
	.string "I gave you?\p"
	.string "I have something to show you.\n"
	.string "Let's go to my LAB.$"

