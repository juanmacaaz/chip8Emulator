#include "Display.h"
#include "stdio.h"

void initDisplay(Display_t *DISPLAY) {
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++){
            DISPLAY->screen_area[j][i] = false;
        }
    }
    gfx_open(WIDTH*SCALE, HEIGHT*SCALE, "Emulator");
    gfx_color(255,255,0);
}

void printFrame(Display_t *DISPLAY) {
    gfx_clear();
    gfx_points(WIDTH, HEIGHT, DISPLAY->screen_area);
}

void clsDisplay(Display_t *DISPLAY) {
    for(int i = 0; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++){
            DISPLAY->screen_area[j][i] = false;
        }
    }
}