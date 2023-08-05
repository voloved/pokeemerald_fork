#include "global.h"
#include "event_data.h"
#include "event_scripts.h"
#include "field_effect.h"
#include "fldeff.h"
#include "party_menu.h"
#include "script.h"
#include "string_util.h"
#include "task.h"
#include "overworld.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"
#include "constants/region_map_sections.h"

// static functions
static void FieldCallback_Strength(void);
static void StartStrengthFieldEffect(void);

// text
bool8 SetUpFieldMove_Strength(void)
{
    if (CheckObjectGraphicsInFrontOfPlayer(OBJ_EVENT_GFX_PUSHABLE_BOULDER) == TRUE
    || (CheckObjectGraphicsInFrontOfPlayer(OBJ_EVENT_GFX_MEW) == TRUE && GetCurrentRegionMapSectionId() == MAPSEC_LILYCOVE_CITY)) // If using strength in front of Mew in Lilycove
    {
        gSpecialVar_Result = GetCursorSelectionMonId();
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_Strength;
        return TRUE;
    }
    return FALSE;
}

static void FieldCallback_Strength(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    ScriptContext_SetupScript(EventScript_UseStrength);
}

bool8 FldEff_UseStrength(void)
{
    u8 taskId = CreateFieldMoveTask();
    gTasks[taskId].data[8] = (u32)StartStrengthFieldEffect >> 16;
    gTasks[taskId].data[9] = (u32)StartStrengthFieldEffect;

    if (gFieldEffectArguments[0] > PARTY_SIZE)
        StringCopy_PlayerName(gStringVar1, gSaveBlock2Ptr->playerName);
    else
        GetMonNickname(&gPlayerParty[gFieldEffectArguments[0]], gStringVar1);
    return FALSE;
}

// Just passes control back to EventScript_UseStrength
static void StartStrengthFieldEffect(void)
{
    FieldEffectActiveListRemove(FLDEFF_USE_STRENGTH);
    ScriptContext_Enable();
}
