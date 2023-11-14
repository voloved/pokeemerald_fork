RustboroCity_House1_MapScripts::
	.byte 0

RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_SEEDOT
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox RustboroCity_House1_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, RustboroCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, RustboroCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox RustboroCity_House1_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
	release
	end

RustboroCity_House1_EventScript_DeclineTrade::
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradeCompleted::
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	call_if_set FLAG_NUZLOCKE, RustboroCity_House1_EventScript_QuitNuzlocke
	call_if_unset FLAG_NUZLOCKE_LOST, RustboroCity_House1_EventScript_StartNuzlocke
	goto RustboroCity_House1_EventScript_ContinueNuzlocke

RustboroCity_House1_EventScript_HikerDefault::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
	end

RustboroCity_House1_EventScript_StartNuzlocke::
	lock
	faceplayer
	message RustboroCity_House1_Text_StartNuzlocke
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 1, RustboroCity_House1_EventScript_StartNuzlockeNo
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, RustboroCity_House1_EventScript_StartNuzlockeNo
	setflag FLAG_NUZLOCKE_LOST @ To disallow benfits that come with doing an uninterrupted Nuzlocke
	setflag FLAG_NUZLOCKE
	msgbox RustboroCity_House1_Text_StartNuzlockeYes, MSGBOX_SIGN
	release
	end

RustboroCity_House1_EventScript_StartNuzlockeNo::
	msgbox RustboroCity_House1_Text_StartNuzlockeNo, MSGBOX_SIGN
	release
	end

RustboroCity_House1_EventScript_ContinueNuzlocke::
	lock
	faceplayer
	message RustboroCity_House1_Text_ContinueNuzlocke
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 1, RustboroCity_House1_EventScript_ContinueNuzlockeNo
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, RustboroCity_House1_EventScript_ContinueNuzlockeNo
	setflag FLAG_NUZLOCKE
	msgbox RustboroCity_House1_Text_ContinueNuzlockeYes, MSGBOX_SIGN
	release
	end

RustboroCity_House1_EventScript_ContinueNuzlockeNo::
	msgbox RustboroCity_House1_Text_ContinueNuzlockeNo, MSGBOX_SIGN
	release
	end

RustboroCity_House1_EventScript_QuitNuzlocke::
	lock
	faceplayer
	message RustboroCity_House1_Text_QuitNuzlocke
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 1, RustboroCity_House1_EventScript_QuitNuzlockeNo
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, RustboroCity_House1_EventScript_QuitNuzlockeNo
	setflag FLAG_NUZLOCKE_LOST @ To disallow benfits that come with doing an uninterrupted Nuzlocke
	clearflag FLAG_NUZLOCKE
	msgbox RustboroCity_House1_Text_QuitNuzlockeYes, MSGBOX_SIGN
	release
	end

RustboroCity_House1_EventScript_QuitNuzlockeNo::
	msgbox RustboroCity_House1_Text_QuitNuzlockeNo, MSGBOX_SIGN
	release
	end

RustboroCity_House1_Text_StartNuzlocke:
	.string "It looks like you haven't started\n"
	.string "the Nuzlocke challenge?\l"
	.string "Would you like to?$"

RustboroCity_House1_Text_StartNuzlockeYes:
	.string "Nuzlocke challenge\n"
	.string "is started.$"

RustboroCity_House1_Text_StartNuzlockeNo:
	.string "Nuzlocke challenge will\n"
	.string "not be started.$"

RustboroCity_House1_Text_ContinueNuzlocke:
	.string "Would you like to continue\n"
	.string "the Nuzlocke challenge?$"

RustboroCity_House1_Text_ContinueNuzlockeYes:
	.string "Nuzlocke challenge\n"
	.string "is continued.$"

RustboroCity_House1_Text_ContinueNuzlockeNo:
	.string "Nuzlocke challenge will\n"
	.string "not be continued.$"

RustboroCity_House1_Text_QuitNuzlocke:
	.string "Quit the\n"
	.string "Nuzlocke challenge?$"

RustboroCity_House1_Text_QuitNuzlockeYes:
	.string "Nuzlocke challenge\n"
	.string "has been quit.$"

RustboroCity_House1_Text_QuitNuzlockeNo:
	.string "Nuzlocke challenge\n"
	.string "will continue.$"

RustboroCity_House1_Text_IllTradeIfYouWant:
	.string "Huh? My POKéMON is cute?\n"
	.string "Sure, I knew that.\p"
	.string "But if you really want, I'm willing\n"
	.string "to trade it to you.\p"
	.string "I'll trade you my {STR_VAR_2} for\n"
	.string "a {STR_VAR_1} if you want.$"

RustboroCity_House1_Text_PleaseBeGoodToMyPokemon:
	.string "Eheheh…\n"
	.string "Please be good to my POKéMON.$"

RustboroCity_House1_Text_DoesntLookLikeMonToMe:
	.string "Huh? That doesn't look anything like\n"
	.string "a {STR_VAR_1} to me.$"

RustboroCity_House1_Text_YouDontWantToThatsOkay:
	.string "Oh, if you don't want to, that's okay.\n"
	.string "But my POKéMON is cute, you know…$"

RustboroCity_House1_Text_AnyPokemonCanBeCute:
	.string "Any POKéMON can be cute if you raise\n"
	.string "it with care and kindness.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "In all sorts of places, there are all\n"
	.string "sorts of POKéMON and people.\p"
	.string "I find that fascinating, so I go to all\n"
	.string "sorts of places.$"

