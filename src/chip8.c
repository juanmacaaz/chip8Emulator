#include <stdint.h>

#include "CPU.h"
#include "KeyBoard.h"

int main() {
    CPU_t      CPU;
    RAM_t      RAM;
    KeyBoard_t KeyBoard;
    Display_t  DISPLAY;

    initCPU(&CPU);
    initDisplay(&DISPLAY);
    read_rom(&RAM, "./games/TETRIS");
    runCPU(&CPU, &RAM, &DISPLAY);
}