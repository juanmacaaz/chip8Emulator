#include "Display.h"

void initDisplay(Display_t *DISPLAY) {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            DISPLAY->screen_area[i][j] = false;
        }
    }
}