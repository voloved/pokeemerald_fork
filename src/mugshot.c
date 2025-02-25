#include "global.h"
#include "blit.h"
#include "window.h"
#include "menu.h"
#include "palette.h"
#include "event_data.h"
#include "constants/mugshot.h"

#define MUGSHOT_PALETTE_NUM 13
#define MUGSHOT_BASEBLOCK   0x40

struct Mugshot{
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 baseBlock;
    const u32* const image;
    const u16* const palette;
};

void DrawMugshot(void); //VAR_0x8000 = mugshot id
void DrawMugshotAtPos(void); //VAR_0x8000 = mugshot id, VAR_0x8001 = x, VAR_0x8002 = y
void ClearMugshot(void);

static const u32 sMugshotImg_TypeChart[] = INCBIN_U32("graphics/mugshots/TypeChart.4bpp.lz");
static const u16 sMugshotPal_TypeChart[] = INCBIN_U16("graphics/mugshots/TypeChart.gbapal");
static const u32 sMugshotImg_NatureChart[] = INCBIN_U32("graphics/mugshots/NatureChart.4bpp.lz");
static const u16 sMugshotPal_NatureChart[] = INCBIN_U16("graphics/mugshots/NatureChart.gbapal");
static const u32 sMugshotImg_NatureChartSmall[] = INCBIN_U32("graphics/mugshots/NatureChartSmall.4bpp.lz");
static const u16 sMugshotPal_NatureChartSmall[] = INCBIN_U16("graphics/mugshots/NatureChartSmall.gbapal");

static const struct Mugshot sMugshots[] = {
    [MUGSHOT_TYPECHART] = {.x = 5, .y = 0, .width = 160, .height = 160, .image = sMugshotImg_TypeChart, .palette = sMugshotPal_TypeChart},
    [MUGSHOT_NATURECHART] = {.x = 0, .y = 4, .width = 240, .height = 88, .image = sMugshotImg_NatureChart, .palette = sMugshotPal_NatureChart},
    [MUGSHOT_NATURECHARTSMALL] = {.x = 0, .y = 1, .width = 128, .height = 88, .image = sMugshotImg_NatureChartSmall, .palette = sMugshotPal_NatureChartSmall},
};


//WindowId + 1, 0 if window is not open
static EWRAM_DATA u8 sMugshotWindow = 0;

void ClearMugshot(void){
    if(sMugshotWindow != 0){
        ClearStdWindowAndFrameToTransparent(sMugshotWindow - 1, 0);
        CopyWindowToVram(sMugshotWindow - 1, 3);
        RemoveWindow(sMugshotWindow - 1);
        sMugshotWindow = 0;
    }
}

static void DrawMugshotCore(const struct Mugshot* const mugshot, int x, int y, u16 baseBlock){
    struct WindowTemplate t;
    u16 windowId;
    
    if(sMugshotWindow != 0){
        ClearMugshot();
    }
    #if GAME_VERSION==VERSION_EMERALD
    SetWindowTemplateFields(&t, 0, x, y, mugshot->width/8, mugshot->height/8, MUGSHOT_PALETTE_NUM, baseBlock);
    #else
    t = SetWindowTemplateFields(0, x, y, mugshot->width/8, mugshot->height/8, MUGSHOT_PALETTE_NUM, baseBlock);
    #endif
    windowId = AddWindow(&t);
    sMugshotWindow = windowId + 1;
    
    LoadPalette(mugshot->palette, 16 * MUGSHOT_PALETTE_NUM, 32);
    CopyToWindowPixelBuffer(windowId, (const void*)mugshot->image, 0, 0);
    PutWindowRectTilemap(windowId, 0, 0, mugshot->width/8, mugshot->height/8);
    CopyWindowToVram(windowId, 3);
}

void DrawMugshot(void){
    const struct Mugshot* const mugshot = sMugshots + VarGet(VAR_0x8000);
    DrawMugshotCore(mugshot, mugshot->x, mugshot->y, MUGSHOT_BASEBLOCK);
}

void DrawMugshotAtPos(void){
    DrawMugshotCore(sMugshots + VarGet(VAR_0x8000), VarGet(VAR_0x8001), VarGet(VAR_0x8002), MUGSHOT_BASEBLOCK);
}

void DrawMugshotAtBaseBlock(void){
    const struct Mugshot* const mugshot = sMugshots + VarGet(VAR_0x8000);
    DrawMugshotCore(mugshot, mugshot->x, mugshot->y, VarGet(VAR_0x8001));
}