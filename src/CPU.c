#include "CPU.h"

void initCPU(CPU_t* CPU) {
    CPU->I  = 0x0;
    CPU->PC = INI_ROM;
    CPU->SP = 0x0;

    for (int i = 0; i < MAX_REG; i++)
        CPU->SR[i] = 0x0;
    
    for (int i = 0; i < MAX_REG; i++)
        CPU->Vx[i] = 0x0;
}

void runCPU(CPU_t* CPU, RAM_t* RAM) {
    uint8_t type, a , b, c;
    while(1){   
        read_mem(RAM , CPU->PC, &type, &a, &b, &c);
        exeOPC(CPU, type, a, b, c);
        CPU->PC += 2;
    }
}

void exeOPC(CPU_t *CPU , uint8_t type, uint8_t a, uint8_t b, uint8_t c) {
    switch (type)
    {
    case 0: if (c == 0) {} else CPU->PC = CPU->SP; CPU-> SP--;          break;
    case 1: CPU->PC = concat3Bits(a, b, c);                             break;
    case 2: CPU->SP++; CPU->SP = CPU->PC; CPU->PC = concat3Bits(a,b,c); break;
    case 3: if (CPU->Vx[a] == concat2Bits(b,c)) { CPU->PC+=2; }         break;
    case 4: if (CPU->Vx[a] != concat2Bits(b,c)) { CPU->PC+=2; }         break;
    case 5: if (CPU->Vx[a] != CPU->Vx[b])       { CPU->PC+=2; }         break;
    case 6: CPU->Vx[a] = concat2Bits(a,b);                              break;
    case 7: CPU->Vx[a] += concat2Bits(a,b);                             break;
    case 8:
        switch (c)
        {
        case 0: CPU->Vx[a] = CPU->Vx[b];              break;
        case 1: CPU->Vx[a] = CPU->Vx[a] | CPU->Vx[b]; break;
        case 2: CPU->Vx[a] = CPU->Vx[a] & CPU->Vx[b]; break;
        case 3: CPU->Vx[a] = CPU->Vx[a] & CPU->Vx[b]; break;
        }
        break;
    default:
        break;
    }
}

uint8_t concat2Bits(uint8_t a, uint8_t b) {
    a = a << 4;
    return b | a;
}

uint16_t concat3Bits(uint8_t a, uint8_t b, uint8_t c) {
    a = a << 8;
    b = b << 4;
    return a | b | c;
}