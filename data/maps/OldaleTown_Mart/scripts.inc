OldaleTown_Mart_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Common_Mart_OnTransition
	.byte 0

Common_Mart_OnTransition::
	goto_if_unset FLAG_NUZLOCKE, Common_Mart_No_InfRare
	goto_if_unset FLAG_NUZLOCKE_LEVEL_CAP, Common_Mart_No_InfRare
	clearflag FLAG_HIDE_INF_RARE_CANDY_SAMPLES
	end
Common_Mart_No_InfRare::
	setflag FLAG_HIDE_INF_RARE_CANDY_SAMPLES
	end

OldaleTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_ExpandedItems
	pokemart OldaleTown_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_Mart_Pokemart_Basic:
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_NONE
	release
	end

OldaleTown_Mart_ExpandedItems::
	pokemart OldaleTown_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_NONE
	release
	end

OldaleTown_Mart_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_EventScript_PokeBallsInStock
	msgbox OldaleTown_Mart_Text_PokeBallsAreSoldOut, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_PokeBallsInStock::
	msgbox OldaleTown_Mart_Text_ImGoingToBuyPokeBalls, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_Boy::
	msgbox OldaleTown_Mart_Text_RestoreHPWithPotion, MSGBOX_NPC
	end

Common_Mart_EventScript_InfRareCandy::
	lock
	faceplayer
	goto_if_unset FLAG_NUZLOCKE, Common_Mart_EventScript_NoSamples
	goto_if_unset FLAG_NUZLOCKE_LEVEL_CAP, Common_Mart_EventScript_NoSamples
	msgbox LittlerootTown_Text_MartNuzlockeOverlevel, MSGBOX_DEFAULT
	msgbox LittlerootTown_Text_MartNuzlockeOverlevel_YesNo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Common_Mart_EventScript_InfRareCandyEnd
	callnative PartyIsFullyLevelCapped
	goto_if_eq VAR_RESULT, TRUE, Common_Mart_EventScript_InfRareCandyNoEffect
	callnative FieldUseInfiniteRareCandy
	goto Common_Mart_EventScript_InfRareCandyEnd
	end
Common_Mart_EventScript_NoSamples::
	msgbox LittlerootTown_Text_MartNoSamples, MSGBOX_SIGN
	end
Common_Mart_EventScript_InfRareCandyNoEffect::
	msgbox LittlerootTown_Text_MartNuzlockeOverlevel_NoEffect, MSGBOX_SIGN
	end
Common_Mart_EventScript_InfRareCandyEnd::
	msgbox gText_PleaseComeAgain, MSGBOX_SIGN
	end

LittlerootTown_Text_MartNuzlockeOverlevel:
	.string "I see you're running a Nuzlocke where \n"
	.string "you can't overlevel leaders.\p"
	.string "That's impressive! We have an item we're\n"
	.string "sampling called the INF. RARE CANDY.$"

LittlerootTown_Text_MartNuzlockeOverlevel_YesNo:
	.string "Do you want to try it on your\n"
	.string "POKéMON right?$"

LittlerootTown_Text_MartNuzlockeOverlevel_NoEffect:
	.string "All of your POKéMON are\n"
	.string "already at their max. $"

LittlerootTown_Text_MartNoSamples:
	.string "Hello, I am all out\n"
	.string "of samples. $"

OldaleTown_Mart_Text_PokeBallsAreSoldOut:
	.string "The clerk says they're all sold out.\n"
	.string "I can't buy any POKé BALLS.$"

OldaleTown_Mart_Text_ImGoingToBuyPokeBalls:
	.string "I'm going to buy a bunch of POKé BALLS\n"
	.string "and catch a bunch of POKéMON!$"

OldaleTown_Mart_Text_RestoreHPWithPotion:
	.string "If a POKéMON gets hurt and loses its HP\n"
	.string "and faints, it won't be able to battle.\p"
	.string "To prevent your POKéMON from fainting,\n"
	.string "restore its HP with a POTION.$"

