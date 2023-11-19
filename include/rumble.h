#ifndef GUARD_RUMBLE_H
#define GUARD_RUMBLE_H


enum{
    RUMBLE_TYPE_OFF,
    RUMBLE_TYPE_CONT,
    RUMBLE_TYPE_SFX,
    RUMBLE_TYPE_TIMED
};

void RumbleFrameUpdate();
bool32 SetTimedRumble(u8 frames);
bool32 RumbleStart(void);
bool32 RumbleStartForSfx(void);
bool32 RumbleStop(void);
u32 GetRumbleState(void);


#endif // GUARD_RUMBLE_H