#include <stdint.h>

#include "CPU.h"
#include "Display.h"
#include "KeyBoard.h"

int main() {
    CPU_t      CPU;
    RAM_t      RAM;
    KeyBoard_t KeyBoard;
    Display_t  Display;

    initCPU(&CPU);
    read_rom(&RAM, "./games/PONG");
    runCPU(&CPU, &RAM);
}