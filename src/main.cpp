#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include "gfx.hpp"

PSP_MODULE_INFO("Tutorial", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int x = 10;
int y = 10;

auto exit_callback(int arg1, int arg2, void* common) {
    sceKernelExitGame();
    return 0;
}

auto callBackThread(SceSize args, void* argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    
    sceKernelSleepThread();
    return 0;
}

auto setupCallBacks() {
    int thid = sceKernelCreateThread("update_thread", callBackThread, 0x11, 0xFA0, 0, NULL);
        if (thid >= 0) {
            sceKernelStartThread(thid, 0, NULL);
    }
}

auto main() -> int {
    setupCallBacks();
    GFX::init();
    pspDebugScreenInit();

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    int running = 1;
    SceCtrlData ctrlData;

    while (running) {
        GFX::clear(0xFFFFCA82);
        GFX::drawLine(10, 30, x, y, 0xFF00FFFF);
        sceCtrlReadBufferPositive(&ctrlData, 1);

        if (ctrlData.Buttons & PSP_CTRL_TRIANGLE) {
            y -= 2;
        } else if (ctrlData.Buttons & PSP_CTRL_CROSS) {
            y += 2;
        } else if (ctrlData.Buttons & PSP_CTRL_CIRCLE) {
            x += 2;
        } else if (ctrlData.Buttons & PSP_CTRL_SQUARE) {
            x -= 2;
        }

        if (ctrlData.Buttons & PSP_CTRL_HOME) {
            running = 0;
        }

        GFX::swapBuffers();
        
        sceDisplayWaitVblankStart();
    }
}