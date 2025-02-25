#include "global.h"
#include "new_game.h"
#include "random.h"
#include "pokemon.h"
#include "roamer.h"
#include "pokemon_size_record.h"
#include "script.h"
#include "lottery_corner.h"
#include "play_time.h"
#include "mauville_old_man.h"
#include "match_call.h"
#include "lilycove_lady.h"
#include "load_save.h"
#include "pokeblock.h"
#include "dewford_trend.h"
#include "berry.h"
#include "rtc.h"
#include "easy_chat.h"
#include "event_data.h"
#include "money.h"
#include "trainer_hill.h"
#include "tv.h"
#include "coins.h"
#include "text.h"
#include "overworld.h"
#include "mail.h"
#include "battle_records.h"
#include "item.h"
#include "pokedex.h"
#include "apprentice.h"
#include "frontier_util.h"
#include "pokedex.h"
#include "save.h"
#include "link_rfu.h"
#include "main.h"
#include "contest.h"
#include "item_menu.h"
#include "pokemon_storage_system.h"
#include "pokemon_jump.h"
#include "decoration_inventory.h"
#include "secret_base.h"
#include "player_pc.h"
#include "field_specials.h"
#include "berry_powder.h"
#include "mystery_gift.h"
#include "union_room_chat.h"
#include "constants/decorations.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/map_groups.h"
#include "constants/secret_bases.h"

extern const u8 EventScript_ResetAllMapFlags[];

static void ClearFrontierRecord(void);
static void WarpToTruck(void);
static void ResetMiniGamesRecords(void);

EWRAM_DATA bool8 gDifferentSaveFile = FALSE;
EWRAM_DATA bool8 gEnableContestDebugging = FALSE;

static const struct ContestWinner sContestWinnerPicDummy =
{
    .monName = _(""),
    .trainerName = _("")
};

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

u32 GetTrainerId(u8 *trainerId)
{
    return (trainerId[3] << 24) | (trainerId[2] << 16) | (trainerId[1] << 8) | (trainerId[0]);
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < TRAINER_ID_LENGTH; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = Random32(&gPCGRng);
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

static void SetDefaultOptions(void)
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_L_EQUALS_A;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_MONO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SHIFT;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsRumble = FALSE;
    gSaveBlock2Ptr->vSyncOff = FALSE;
    gSaveBlock2Ptr->optionsRumble = FALSE;
    FlagSet(FLAG_TYPE_EFFECTIVENESS_BATTLE_SHOW);
    FlagSet(FLAG_SHOW_BALL_SUGGESTION);
    FlagSet(FLAG_BALL_SUGGEST_NOT_LAST);
    FlagSet(FLAG_BALL_SUGGEST_COMPLEX);
	FlagSet(FLAG_USE_FROSTBITE);
	FlagSet(FLAG_ALLOW_RUNNING_TOGGLE);
	FlagSet(FLAG_POKEMON_FOLLOWERS);
	FlagSet(FLAG_SHOW_DAY_NIGHT);
	FlagSet(FLAG_NUZLOCKE_DUPES_CLAUSE);
	FlagSet(FLAG_RELEARN_IN_PARTY_MENU);
    VarSet(VAR_DIFFICULTY, DIFFICULTY_NORMAL);
}

static void ClearPokedexFlags(void)
{
    gUnusedPokedexU8 = 0;
    memset(&gSaveBlock2Ptr->pokedex.owned, 0, sizeof(gSaveBlock2Ptr->pokedex.owned));
    memset(&gSaveBlock2Ptr->pokedex.seen, 0, sizeof(gSaveBlock2Ptr->pokedex.seen));
}

void ClearAllContestWinnerPics(void)
{
    s32 i;

    ClearContestWinnerPicsInContestHall();

    // Clear Museum paintings
    for (i = MUSEUM_CONTEST_WINNERS_START; i < NUM_CONTEST_WINNERS; i++)
        gSaveBlock1Ptr->contestWinners[i] = sContestWinnerPicDummy;
}

static void ClearFrontierRecord(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->frontier, sizeof(gSaveBlock2Ptr->frontier));

    gSaveBlock2Ptr->frontier.opponentNames[0][0] = EOS;
    gSaveBlock2Ptr->frontier.opponentNames[1][0] = EOS;
}

static void WarpToTruck(void)
{
    SetWarpDestination(MAP_GROUP(INSIDE_OF_TRUCK), MAP_NUM(INSIDE_OF_TRUCK), WARP_ID_NONE, -1, -1);
    WarpIntoMap();
}

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ResetPokedexScrollPositions();
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagScrollPositions();
    ResetPokeblockScrollPositions();
}

void NewGameInitData(void)
{
    bool8 typeEffectPrev = FlagGet(FLAG_TYPE_EFFECTIVENESS_BATTLE_SHOW);
    bool8 nuzlockePrev = FlagGet(FLAG_NUZLOCKE);
    bool8 showBallSuggestPrev = FlagGet(FLAG_SHOW_BALL_SUGGESTION);
    bool8 showBallNotLastPrev = FlagGet(FLAG_BALL_SUGGEST_NOT_LAST);
    bool8 showBallComplexPrev = FlagGet(FLAG_BALL_SUGGEST_COMPLEX);
    bool8 useFrostbite = FlagGet(FLAG_USE_FROSTBITE);
    bool8 runningShoesToggle = FlagGet(FLAG_ALLOW_RUNNING_TOGGLE);
    bool8 showFollowers = FlagGet(FLAG_POKEMON_FOLLOWERS);
    bool8 showDayNight = FlagGet(FLAG_SHOW_DAY_NIGHT);
    bool8 nuzlockeDupes = FlagGet(FLAG_NUZLOCKE_DUPES_CLAUSE);
    bool8 relearnMoveInPartyMenu = FlagGet(FLAG_RELEARN_IN_PARTY_MENU);
    bool8 useOriginalSplit = FlagGet(FLAG_MOVE_SPLIT_USE_ORIGINAL);
    bool8 midBattleEvo = FlagGet(FLAG_MID_BATTLE_EVOLUTION);
    bool8 noLowHealthBeep = FlagGet(FLAG_NO_LOW_HEALTH_BEEP);
    bool8 nuzlockeSet = FlagGet(FLAG_NUZLOCKE_BATTLE_SET);
    bool8 nuzlockeLevelCap = FlagGet(FLAG_NUZLOCKE_LEVEL_CAP);
    bool8 nuzlockeHeldItems = FlagGet(FLAG_NUZLOCKE_NO_HELD_ITEMS);
    bool8 nuzlockeNoBattleItems = FlagGet(FLAG_NUZLOCKE_NO_BATTLE_ITEMS);
    bool8 nuzlockeRandomizeWild = FlagGet(FLAG_NUZLOCKE_RANDOMIZE_WILD);
    bool8 nuzlockeRandomizeFirst = FlagGet(FLAG_NUZLOCKE_RANDOMIZE_FIRST);
    u16 difficulty = VarGet(VAR_DIFFICULTY);
    u16 expMult = VarGet(VAR_EXP_MULT);
    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
        RtcReset();

    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetPokedex();
    ClearFrontierRecord();
    ClearSav1();
    ClearAllMail();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    ClearTVShowData();
    ResetGabbyAndTy();
    ClearSecretBases();
    ClearBerryTrees();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    SetCoins(0);
    ResetLinkContestBoolean();
    ResetGameStats();
    ClearAllContestWinnerPics();
    ClearPlayerLinkBattleRecords();
    InitSeedotSizeRecord();
    InitLotadSizeRecord();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    ClearRoamerData();
    ClearRoamerLocationData();
    gSaveBlock1Ptr->registeredItem = 0;
    gSaveBlock1Ptr->registeredLongItem = 0;
    ClearBag();
    NewGameInitPCItems(nuzlockePrev);
    ClearPokeblocks();
    ClearDecorationInventories();
    SetPlayerSecretBaseAtId(SECRET_BASE_GARAGE); 
    addDecorationToBaseStart(SECRET_BASE_GARAGE, DECOR_SOLID_BOARD, 102);  // Places board on the garage's hole
    InitEasyChatPhrases();
    SetMauvilleOldMan();
    InitDewfordTrend();
    ResetFanClub();
    ResetLotteryCorner();
    WarpToTruck();
    RunScriptImmediately(EventScript_ResetAllMapFlags);
    ResetMiniGamesRecords();
    InitUnionRoomChatRegisteredTexts();
    InitLilycoveLady();
    ResetAllApprenticeData();
    ClearRankingHallRecords();
    InitMatchCallCounters();
    ClearMysteryGift();
    WipeTrainerNameRecords();
    ResetTrainerHillResults();
    ResetContestLinkResults();
    gSaveBlock2Ptr->lastUsedBall = ITEM_POKE_BALL;
    typeEffectPrev ? FlagSet(FLAG_TYPE_EFFECTIVENESS_BATTLE_SHOW) : FlagClear(FLAG_TYPE_EFFECTIVENESS_BATTLE_SHOW);
    nuzlockePrev ? FlagSet(FLAG_NUZLOCKE) : FlagClear(FLAG_NUZLOCKE);
    showBallSuggestPrev ? FlagSet(FLAG_SHOW_BALL_SUGGESTION) : FlagClear(FLAG_SHOW_BALL_SUGGESTION);
    showBallNotLastPrev ? FlagSet(FLAG_BALL_SUGGEST_NOT_LAST) : FlagClear(FLAG_BALL_SUGGEST_NOT_LAST);
    showBallComplexPrev ? FlagSet(FLAG_BALL_SUGGEST_COMPLEX) : FlagClear(FLAG_BALL_SUGGEST_COMPLEX);
    useFrostbite ? FlagSet(FLAG_USE_FROSTBITE) : FlagClear(FLAG_USE_FROSTBITE);
    runningShoesToggle ? FlagSet(FLAG_ALLOW_RUNNING_TOGGLE) : FlagClear(FLAG_ALLOW_RUNNING_TOGGLE);
    showFollowers ? FlagSet(FLAG_POKEMON_FOLLOWERS) : FlagClear(FLAG_POKEMON_FOLLOWERS);
    showDayNight ? FlagSet(FLAG_SHOW_DAY_NIGHT) : FlagClear(FLAG_SHOW_DAY_NIGHT);
    nuzlockeDupes ? FlagSet(FLAG_NUZLOCKE_DUPES_CLAUSE) : FlagClear(FLAG_NUZLOCKE_DUPES_CLAUSE);
    relearnMoveInPartyMenu ? FlagSet(FLAG_RELEARN_IN_PARTY_MENU) : FlagClear(FLAG_RELEARN_IN_PARTY_MENU);
    useOriginalSplit ? FlagGet(FLAG_MOVE_SPLIT_USE_ORIGINAL) : FlagClear(FLAG_MOVE_SPLIT_USE_ORIGINAL);
    midBattleEvo ? FlagGet(FLAG_MID_BATTLE_EVOLUTION) : FlagClear(FLAG_MID_BATTLE_EVOLUTION);
    noLowHealthBeep ? FlagGet(FLAG_NO_LOW_HEALTH_BEEP) : FlagClear(FLAG_NO_LOW_HEALTH_BEEP);
    nuzlockeSet ? FlagGet(FLAG_NUZLOCKE_BATTLE_SET) : FlagClear(FLAG_NUZLOCKE_BATTLE_SET);
    nuzlockeLevelCap ? FlagGet(FLAG_NUZLOCKE_LEVEL_CAP) : FlagClear(FLAG_NUZLOCKE_LEVEL_CAP);
    nuzlockeHeldItems ? FlagGet(FLAG_NUZLOCKE_NO_HELD_ITEMS) : FlagClear(FLAG_NUZLOCKE_NO_HELD_ITEMS);
    nuzlockeNoBattleItems ? FlagGet(FLAG_NUZLOCKE_NO_BATTLE_ITEMS) : FlagClear(FLAG_NUZLOCKE_NO_BATTLE_ITEMS);
    nuzlockeRandomizeWild ? FlagGet(FLAG_NUZLOCKE_RANDOMIZE_WILD) : FlagClear(FLAG_NUZLOCKE_RANDOMIZE_WILD);
    nuzlockeRandomizeFirst ? FlagGet(FLAG_NUZLOCKE_RANDOMIZE_FIRST) : FlagClear(FLAG_NUZLOCKE_RANDOMIZE_FIRST);
    VarSet(VAR_DIFFICULTY, difficulty);
    VarSet(VAR_EXP_MULT, expMult);
    memset(&gSaveBlock2Ptr->itemFlags, 0, sizeof(gSaveBlock2Ptr->itemFlags));
    gSaveBlock1Ptr->dexNavChain = 0;
}

static void ResetMiniGamesRecords(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    ResetPokemonJumpRecords();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}
