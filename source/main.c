#include <3ds.h>
#include <citro2d.h>

#define SCREEN_W 400
#define SCREEN_H 240

int main(void)
{
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    C3D_RenderTarget* top =
        C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget* bottom =
        C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    float x = 180.0f;
    float y = 110.0f;

    while (aptMainLoop()) {
        hidScanInput();

        u32 held = hidKeysHeld();

        if (held & KEY_START)
            break;
        if (held & KEY_DLEFT)
            x -= 3.0f;
        if (held & KEY_DRIGHT)
            x += 3.0f;
        if (held & KEY_DUP)
            y -= 3.0f;
        if (held & KEY_DDOWN)
            y += 3.0f;

        if (x < 8.0f)
            x = 8.0f;
        if (x > SCREEN_W - 28.0f)
            x = SCREEN_W - 28.0f;
        if (y < 8.0f)
            y = 8.0f;
        if (y > SCREEN_H - 28.0f)
            y = SCREEN_H - 28.0f;

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        C2D_TargetClear(top,
            C2D_Color32(20, 28, 48, 255));
        C2D_SceneBegin(top);
        C2D_DrawRectSolid(
            x, y, 0.5f, 20.0f, 20.0f,
            C2D_Color32(80, 220, 255, 255));

        C2D_TargetClear(bottom,
            C2D_Color32(12, 16, 24, 255));
        C2D_SceneBegin(bottom);
        C2D_DrawRectSolid(
            140.0f, 100.0f, 0.5f,
            40.0f, 40.0f,
            C2D_Color32(255, 120, 80, 255));

        C3D_FrameEnd(0);
    }

    C2D_Fini();
    C3D_Fini();
    gfxExit();

    return 0;
}
