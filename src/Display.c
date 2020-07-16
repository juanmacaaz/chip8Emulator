#include "Display.h"

void initDisplay(Display_t *DISPLAY) {
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++){
            DISPLAY->screen_area[j][i] = false;
        }
    }
    gfx_open(WIDTH*SCALE, HEIGHT*SCALE, "Emulator");
    gfx_color(255,255,255);
}

void printFrame(Display_t *DISPLAY) {
    gfx_clear();
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++){
            if (DISPLAY->screen_area[j][i])
                for(int x = i*SCALE; x < (i*SCALE)+SCALE; x++) {
                    for(int y = j*SCALE; y < (j*SCALE)+SCALE; y++) {
                        gfx_point(x,y);
                    }
                }
        }
    }
}