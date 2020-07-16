#include "RAM.h"
#include "Display.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
 
#define MAX_REG 16      // Numero de registros

struct CPU_t
{

    uint16_t SR [MAX_REG];  //Pila

    uint8_t  Vx [MAX_REG];  //Registros de uso general
    uint16_t I;             //Registro de almacenamiento de memoria

    uint16_t PC;            // Program counter
    uint8_t  SP;            // Stack Pointer

} typedef CPU_t;

void initCPU(CPU_t* CPU);
void runCPU(CPU_t* CPU, RAM_t* RAM, Display_t *DISPLAY);
void exeOPC(CPU_t *CPU , RAM_t *RAM, Display_t *DISPLAY, uint8_t type, uint8_t a, uint8_t b, uint8_t c);

uint8_t concat2Bits(uint8_t a, uint8_t b);
uint16_t concat3Bits(uint8_t a, uint8_t b, uint8_t c);