EventScript_UseSurf::
	checkpartymove MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_SurfWithoutPokemon
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
EventScript_SurfContinue::
	lockall
	msgbox gText_WantToUseSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_ReleaseUseSurf
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF
EventScript_ReleaseUseSurf::
	releaseall
EventScript_EndUseSurf::
	end

EventScript_SurfWithoutPokemon::
	checkitem ITEM_HM03_SURF
	goto_if_eq VAR_RESULT, FALSE, EventScript_EndUseSurf
	bufferpartymonnick STR_VAR_1, 0
	setfieldeffectargument 0, 0
	goto EventScript_SurfContinue
	end


