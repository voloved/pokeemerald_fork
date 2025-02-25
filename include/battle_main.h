#ifndef GUARD_BATTLE_MAIN_H
#define GUARD_BATTLE_MAIN_H

struct TrainerMoney
{
    u8 classId;
    u8 value;
};

// For displaying a multi battle partner's Pokémon in the party menu
struct MultiPartnerMenuPokemon
{
    /*0x00*/ u16 species;
    /*0x02*/ u16 heldItem;
    /*0x04*/ u8 nickname[POKEMON_NAME_LENGTH + 1];
    /*0x0F*/ u8 level;
    /*0x10*/ u16 hp;
    /*0x12*/ u16 maxhp;
    /*0x14*/ u32 status;
    /*0x18*/ u32 personality;
    /*0x1C*/ u8 gender;
    /*0x1D*/ u8 language;
};

struct BattleOddsModifierButtonPress
{
    u8 ballShakesArray;
    u32 odds;
    u8 shakes;
};

/*
ballShakesArray: 76543210
76: The amount of shakes we've done
 5: If the B button was pressed on the 3rd shake
 4: If the B button was held just before the 3rd shake
 3: If the B button was pressed on the 2nd shake
 2: If the B button was held just before the 2nd shake
 1: If the B button was pressed on the 1st shake
 0: If the B button was held just before the 1st shake
*/


// defines for the u8 array gTypeEffectiveness
#define TYPE_EFFECT_ATK_TYPE(i)((gTypeEffectiveness[i + 0]))
#define TYPE_EFFECT_DEF_TYPE(i)((gTypeEffectiveness[i + 1]))
#define TYPE_EFFECT_MULTIPLIER(i)((gTypeEffectiveness[i + 2]))

// defines for the gTypeEffectiveness multipliers
#define TYPE_MUL_NO_EFFECT          0
#define TYPE_MUL_NOT_EFFECTIVE      5
#define TYPE_MUL_NORMAL             10
#define TYPE_MUL_SUPER_EFFECTIVE    20

// defines for the gTypeEffectiveness multipliers for Tri-Attack
#define TYPE_MUL_NO_EFFECT_TRI_ATTACK               0
#define TYPE_MUL_NOT_EFFECTIVE_3_TRI_ATTACK         25
#define TYPE_MUL_NOT_EFFECTIVE_2_TRI_ATTACK         50
#define TYPE_MUL_NOT_EFFECTIVE_1_TRI_ATTACK         75
#define TYPE_MUL_NORMAL_TRI_ATTACK                  100
#define TYPE_MUL_SE_NE_SAME_TRI_ATTACK              150
#define TYPE_MUL_SUPER_EFFECTIVE_1_TRI_ATTACK       200
#define TYPE_MUL_SUPER_EFFECTIVE_2_TRI_ATTACK       250
#define TYPE_MUL_SUPER_EFFECTIVE_3_TRI_ATTACK       300
#define TYPE_MUL_BLANK                              0xFF

// special type table Ids
#define TYPE_FORESIGHT  0xFE
#define TYPE_ENDTABLE   0xFF

// defines for the 'DoBounceEffect' function
#define BOUNCE_MON          0x0
#define BOUNCE_HEALTHBOX    0x1

// Rival's Stolen Pokemon
#define STOLE_STARTER       (1 << 0)
#define STOLE_WINGULL       (1 << 1)
#define STOLE_SLUGMA        (1 << 2)
#define STOLE_LOTAD         (1 << 3)
#define STOLE_TROPIUS       (1 << 4)
#define STOLE_TORKOAL       (1 << 5)
#define STOLE_LEGENDARY     (1 << 6)
#define STOLE_RALTS         (1 << 7)
#define STOLE_ALTARIA       (1 << 8)
#define STOLE_DELCATTY      (1 << 9)
#define STOLE_ROSELIA       (1 << 10)
#define STOLE_MAGNETON      (1 << 11)
#define STOLE_SLAKING       (1 << 12)

#define STOLE_SIDNEY_START     0
#define STOLE_PHEOBE_START     5
#define STOLE_GLACIA_START     10
#define STOLE_DRAKE_START      0

void CB2_InitBattle(void);
void BattleMainCB2(void);
void CB2_QuitRecordedBattle(void);
void VBlankCB_Battle(void);
void SpriteCB_VsLetterDummy(struct Sprite *sprite);
void SpriteCB_VsLetterInit(struct Sprite *sprite);
void CB2_InitEndLinkBattle(void);
u32 GetBattleBgTemplateData(u8 arrayId, u8 caseId);
u32 GetBattleWindowTemplatePixelWidth(u32 setId, u32 tableId);
void SpriteCB_WildMon(struct Sprite *sprite);
void SpriteCallbackDummy_2(struct Sprite *sprite);
void SpriteCB_FaintOpponentMon(struct Sprite *sprite);
void SpriteCB_ShowAsMoveTarget(struct Sprite *sprite);
void SpriteCB_HideAsMoveTarget(struct Sprite *sprite);
void SpriteCB_OpponentMonFromBall(struct Sprite *sprite);
void SpriteCB_BattleSpriteStartSlideLeft(struct Sprite *sprite);
void SpriteCB_FaintSlideAnim(struct Sprite *sprite);
void DoBounceEffect(u8 battler, u8 which, s8 delta, s8 amplitude);
void EndBounceEffect(u8 battler, u8 which);
void SpriteCB_PlayerMonFromBall(struct Sprite *sprite);
void SpriteCB_PlayerMonSlideIn(struct Sprite *sprite);
void SpriteCB_TrainerThrowObject(struct Sprite *sprite);
void AnimSetCenterToCornerVecX(struct Sprite *sprite);
void BeginBattleIntroDummy(void);
void BeginBattleIntro(void);
void SwitchInClearSetData(void);
void FaintClearSetData(void);
void BattleTurnPassed(void);
u8 IsRunningFromBattleImpossible(void);
u8 IsTrainerCantRunFrom(void);
void SwitchPartyOrder(u8 battlerId);
void SwapTurnOrder(u8 id1, u8 id2);
u8 GetWhoStrikesFirst(u8 battlerId1, u8 battlerId2, bool8 ignoreChosenMoves);
void RunBattleScriptCommands_PopCallbacksStack(void);
void RunBattleScriptCommands(void);
bool8 TryRunFromBattle(u8 battlerId);
void SpecialStatusesClear(void);
u16 checkStolenPokemon(u16 trainerNum, u16 speciesType, u16 partyIndex, bool8 set);
u8 isMovePhysicalTyping(u16);
u8 isMovePhysicalTyping(u16);
u8 isMovePhysical(u16);
u8 isMoveSpecial(u16);
u8 isMoveStatus(u16);

extern struct MultiPartnerMenuPokemon gMultiPartnerParty[MULTI_PARTY_SIZE];

extern const struct SpriteTemplate gUnusedBattleInitSprite;
extern const struct OamData gOamData_BattleSpriteOpponentSide;
extern const struct OamData gOamData_BattleSpritePlayerSide;
extern const u8 gTypeEffectiveness[372];  // 3 elements for each entry in the table (124 entries * 3 = 372)
extern const u8 gTypeNames[NUMBER_OF_MON_TYPES][TYPE_NAME_LENGTH + 1];
extern const struct TrainerMoney gTrainerMoneyTable[];
extern const u8 gAbilityNames[][ABILITY_NAME_LENGTH + 1];
extern const u8 *const gAbilityDescriptionPointers[];

extern const u8 gStatusConditionString_PoisonJpn[8];
extern const u8 gStatusConditionString_SleepJpn[8];
extern const u8 gStatusConditionString_ParalysisJpn[8];
extern const u8 gStatusConditionString_BurnJpn[8];
extern const u8 gStatusConditionString_IceJpn[8];
extern const u8 gStatusConditionString_ConfusionJpn[8];
extern const u8 gStatusConditionString_LoveJpn[8];

extern const u8 *const gStatusConditionStringsTable[7][2];

#endif // GUARD_BATTLE_MAIN_H
